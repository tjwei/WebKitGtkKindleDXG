/*
 * GQview
 * (C) 2004 John Ellis
 *
 * Author: John Ellis
 *
 * This software is released under the GNU General Public License (GNU GPL).
 * Please read the included file COPYING for more information.
 * This software comes with no warranty of any kind, use at your own risk!
 */


#include "gqview.h"
#include "image-load.h"

#include "format_raw.h"
#include "ui_fileops.h"

#include <fcntl.h>


/* bytes to read from file per read() */
#define IMAGE_LOADER_BUFFER_SIZE 512

/* the number of bytes to read per idle call (define x IMAGE_LOADER_BUFFER_SIZE) */
#define IMAGE_LOADER_BUFFER_DEFAULT_COUNT 1

static void image_loader_sync_pixbuf(ImageLoader *il)
{
	GdkPixbuf *pb;

	if (!il->loader) return;

	pb = gdk_pixbuf_loader_get_pixbuf(il->loader);

	if (pb == il->pixbuf) return;

	if (il->pixbuf) gdk_pixbuf_unref(il->pixbuf);
	il->pixbuf = pb;
	if (il->pixbuf) gdk_pixbuf_ref(il->pixbuf);
}

static void image_loader_area_cb(GdkPixbufLoader *loader,
				 guint x, guint y, guint w, guint h,
				 gpointer data)
{
	ImageLoader *il = data;

	if (il->func_area_ready)
		{
		if (!il->pixbuf)
			{
			image_loader_sync_pixbuf(il);
			if (!il->pixbuf)
				{
				printf("critical: area_ready signal with NULL pixbuf (out of mem?)\n");
				}
			}
		il->func_area_ready(il, x, y, w, h, il->data_area_ready);
		}
}

static void image_loader_size_cb(GdkPixbufLoader *loader,
				 gint width, gint height, gpointer data)
{
	ImageLoader *il = data;
	GdkPixbufFormat *format;
	gchar **mime_types;
	gint scale = FALSE;
	gint n;

	if (il->requested_width < 1 || il->requested_height < 1) return;

	format = gdk_pixbuf_loader_get_format(loader);
	if (!format) return;

	mime_types = gdk_pixbuf_format_get_mime_types(format);
	n = 0;
	while (mime_types[n])
		{
		if (strstr(mime_types[n], "jpeg")) scale = TRUE;
		n++;
		}
	g_strfreev(mime_types);
	
	if (!scale) return;

	if (width > il->requested_width || height > il->requested_height)
		{
		gint nw, nh;

		if (((gdouble)il->requested_width / width) < ((gdouble)il->requested_height / height))
			{
			nw = il->requested_width;
			nh = (gdouble)nw / width * height;
			if (nh < 1) nh = 1;
			}
		else
			{
			nh = il->requested_height;
			nw = (gdouble)nh / height * width;
			if (nw < 1) nw = 1;
			}
		
		gdk_pixbuf_loader_set_size(loader, nw, nh);
		il->shrunk = TRUE;
		}
}

static void image_loader_stop(ImageLoader *il)
{
	if (!il) return;

	if (il->idle_id != -1)
		{
		g_source_remove(il->idle_id);
		il->idle_id = -1;
		}

	if (il->loader)
		{
		/* some loaders do not have a pixbuf till close, order is important here */
		gdk_pixbuf_loader_close(il->loader, NULL);
		image_loader_sync_pixbuf(il);
		g_object_unref(G_OBJECT(il->loader));
		il->loader = NULL;
		}

	if (il->load_fd != -1)
		{
		close(il->load_fd);
		il->load_fd = -1;
		}

	il->done = TRUE;
}

static void image_loader_done(ImageLoader *il)
{
	image_loader_stop(il);

	if (il->func_done) il->func_done(il, il->data_done);
}

static gint image_loader_done_delay_cb(gpointer data)
{
	ImageLoader *il = data;

	il->idle_done_id = -1;
	image_loader_done(il);
	return FALSE;
}

static void image_loader_done_delay(ImageLoader *il)
{
	if (il->idle_done_id == -1) il->idle_done_id = g_idle_add_full(il->idle_priority,
								       image_loader_done_delay_cb, il, NULL);
}

static void image_loader_error(ImageLoader *il)
{
	image_loader_stop(il);

	if (debug) printf("pixbuf_loader reported load error for: %s\n", il->path);

	if (il->func_error) il->func_error(il, il->data_error);
}

static gint image_loader_idle_cb(gpointer data)
{
	ImageLoader *il = data;
	guchar buf[IMAGE_LOADER_BUFFER_SIZE];
	gint b;
	gint c;

	if (!il) return FALSE;

	if (il->idle_id == -1) return FALSE;

	c = il->buffer_size ? il->buffer_size : 1;
	while (c > 0)
		{
		b = read(il->load_fd, &buf, sizeof(buf));

		if (b == 0)
			{
			image_loader_done(il);
			return FALSE;
			}

		if (b < 0 || (b > 0 && !gdk_pixbuf_loader_write(il->loader, buf, b, NULL)))
			{
			image_loader_error(il);
			return FALSE;
			}

		il->bytes_read += b;

		c--;
		}

	if (il->func_percent && il->bytes_total > 0)
		{
		il->func_percent(il, (gdouble)il->bytes_read / il->bytes_total, il->data_percent);
		}

	return TRUE;
}

static gint image_loader_begin(ImageLoader *il)
{
	guchar buf[IMAGE_LOADER_BUFFER_SIZE];
	int b;
	unsigned int offset = 0;

	if (!il->loader || il->pixbuf) return FALSE;

	b = read(il->load_fd, &buf, sizeof(buf));

	if (b > 0 &&
	    format_raw_img_exif_offsets_fd(il->load_fd, il->path, buf, b, &offset, NULL))
		{
		if (debug) printf("Raw file %s contains embedded image\n", il->path);

		b = read(il->load_fd, &buf, sizeof(buf));
		}

	if (b < 1)
		{
		image_loader_stop(il);
		return FALSE;
		}

	if (!gdk_pixbuf_loader_write(il->loader, buf, b, NULL))
		{
		image_loader_stop(il);
		return FALSE;
		}

	il->bytes_read += b + offset;

	/* read until size is known */
	while (il->loader && !gdk_pixbuf_loader_get_pixbuf(il->loader) && b > 0)
		{
		b = read(il->load_fd, &buf, sizeof(buf));
		if (b < 0 || (b > 0 && !gdk_pixbuf_loader_write(il->loader, buf, b, NULL)))
			{
			image_loader_stop(il);
			return FALSE;
			}
		il->bytes_read += b;
		}
	if (!il->pixbuf) image_loader_sync_pixbuf(il);

	if (il->bytes_read == il->bytes_total || b < 1)
		{
		/* done, handle (broken) loaders that do not have pixbuf till close */
		image_loader_stop(il);

		if (!il->pixbuf) return FALSE;

		image_loader_done_delay(il);
		return TRUE;
		}

	if (!il->pixbuf)
		{
		image_loader_stop(il);
		return FALSE;
		}

	/* finally, progressive loading :) */
	il->idle_id = g_idle_add_full(il->idle_priority, image_loader_idle_cb, il, NULL);

	return TRUE;
}

static gint image_loader_setup(ImageLoader *il)
{
	struct stat st;
	gchar *pathl;

	if (!il || il->load_fd != -1 || il->loader) return FALSE;

	pathl = path_from_utf8(il->path);
	il->load_fd = open(pathl, O_RDONLY | O_NONBLOCK);
	g_free(pathl);
	if (il->load_fd == -1) return FALSE;

	if (fstat(il->load_fd, &st) == 0)
		{
		il->bytes_total = st.st_size;
		}

	il->loader = gdk_pixbuf_loader_new();
	g_signal_connect(G_OBJECT(il->loader), "area_updated",
		 	 G_CALLBACK(image_loader_area_cb), il);
	g_signal_connect(G_OBJECT(il->loader), "size_prepared",
			 G_CALLBACK(image_loader_size_cb), il);

	il->shrunk = FALSE;

	return image_loader_begin(il);
}

ImageLoader *image_loader_new(const gchar *path)
{
	ImageLoader *il;

	if (!path) return NULL;

	il = g_new0(ImageLoader, 1);
	if (path) il->path = g_strdup(path);
	il->pixbuf = NULL;
	il->idle_id = -1;
	il->idle_priority = G_PRIORITY_DEFAULT_IDLE;
	il->done = FALSE;
	il->loader = NULL;
	il->load_fd = -1;

	il->bytes_read = 0;
	il->bytes_total = 0;

	il->idle_done_id = -1;

	il->buffer_size = IMAGE_LOADER_BUFFER_DEFAULT_COUNT;

	il->requested_width = 0;
	il->requested_height = 0;
	il->shrunk = FALSE;

	return il;
}

void image_loader_free(ImageLoader *il)
{
	if (!il) return;

	image_loader_stop(il);
	if (il->idle_done_id != -1) g_source_remove(il->idle_done_id);
	if (il->pixbuf) gdk_pixbuf_unref(il->pixbuf);
	g_free(il->path);
	g_free(il);
}

/* don't forget to gdk_pixbuf_ref() it if you want to use it after image_loader_free() */
GdkPixbuf *image_loader_get_pixbuf(ImageLoader *il)
{
	if (!il) return NULL;

	return il->pixbuf;
}

gchar *image_loader_get_format(ImageLoader *il)
{
	GdkPixbufFormat *format;
	gchar **mimev;
	gchar *mime;

	if (!il || !il->loader) return NULL;

	format = gdk_pixbuf_loader_get_format(il->loader);
	if (!format) return NULL;

	mimev = gdk_pixbuf_format_get_mime_types(format);
	if (!mimev) return NULL;

	/* return first member of mimev, as GdkPixbufLoader has no way to tell us which exact one ? */
	mime = g_strdup(mimev[0]);
	g_strfreev(mimev);

	return mime;
}

void image_loader_set_area_ready_func(ImageLoader *il,
				      void (*func_area_ready)(ImageLoader *, guint, guint, guint, guint, gpointer),
				      gpointer data_area_ready)
{
	if (!il) return;

	il->func_area_ready = func_area_ready;
	il->data_area_ready = data_area_ready;
}

void image_loader_set_error_func(ImageLoader *il,
				 void (*func_error)(ImageLoader *, gpointer),
				 gpointer data_error)
{
	if (!il) return;

	il->func_error = func_error;
	il->data_error = data_error;
}

void image_loader_set_percent_func(ImageLoader *il,
				   void (*func_percent)(ImageLoader *, gdouble, gpointer),
				   gpointer data_percent)
{
	if (!il) return;

	il->func_percent = func_percent;
	il->data_percent = data_percent;
}

void image_loader_set_requested_size(ImageLoader *il, gint width, gint height)
{
	if (!il) return;

	il->requested_width = width;
	il->requested_height = height;
}

void image_loader_set_buffer_size(ImageLoader *il, guint size)
{
	if (!il) return;

	il->buffer_size = size ? size : 1;
}

void image_loader_set_priority(ImageLoader *il, gint priority)
{
	if (!il) return;

	il->idle_priority = priority;
}

gint image_loader_start(ImageLoader *il, void (*func_done)(ImageLoader *, gpointer), gpointer data_done)
{
	if (!il) return FALSE;

	if (!il->path) return FALSE;

	il->func_done = func_done;
	il->data_done = data_done;

	return image_loader_setup(il);
}

gdouble image_loader_get_percent(ImageLoader *il)
{
	if (!il || il->bytes_total == 0) return 0.0;

	return (gdouble)il->bytes_read / il->bytes_total;
}

gint image_loader_get_is_done(ImageLoader *il)
{
	if (!il) return FALSE;

	return il->done;
}

gint image_load_dimensions(const gchar *path, gint *width, gint *height)
{
	ImageLoader *il;
	gint success;

	il = image_loader_new(path);

	success = image_loader_start(il, NULL, NULL);

	if (success && il->pixbuf)
		{
		if (width) *width = gdk_pixbuf_get_width(il->pixbuf);
		if (height) *height = gdk_pixbuf_get_height(il->pixbuf);;
		}
	else
		{
		if (width) *width = -1;
		if (height) *height = -1;
		}

	image_loader_free(il);

	return success;
}

