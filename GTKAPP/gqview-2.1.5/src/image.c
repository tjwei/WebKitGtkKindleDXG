/*
 * GQview
 * (C) 2006 John Ellis
 *
 * Author: John Ellis
 *
 * This software is released under the GNU General Public License (GNU GPL).
 * Please read the included file COPYING for more information.
 * This software comes with no warranty of any kind, use at your own risk!
 */


#include "gqview.h"
#include "image.h"


#include "image-load.h"
#include "collect.h"
#include "color-man.h"
#include "exif.h"
#include "pixbuf-renderer.h"
#include "pixbuf_util.h"
#include "ui_fileops.h"

#include <math.h>


/* size of the image loader buffer (512 bytes x defined number) */
#define IMAGE_LOAD_BUFFER_COUNT 8

/* define this so that more bytes are read per idle loop on larger images (> 1MB) */
#define IMAGE_THROTTLE_LARGER_IMAGES 1

/* throttle factor to increase read bytes by (2 is double, 3 is triple, etc.) */
#define IMAGE_THROTTLE_FACTOR 4

/* the file size at which throttling take place */
#define IMAGE_THROTTLE_THRESHOLD 1048576

#define IMAGE_AUTO_REFRESH_TIME 3000


static GList *image_list = NULL;


static void image_update_title(ImageWindow *imd);
static void image_post_process(ImageWindow *imd, gint clamp);
static void image_read_ahead_start(ImageWindow *imd);

/*
 *-------------------------------------------------------------------
 * 'signals'
 *-------------------------------------------------------------------
 */

static void image_click_cb(PixbufRenderer *pr, GdkEventButton *event, gpointer data)
{
	ImageWindow *imd = data;

	if (imd->func_button)
		{
		imd->func_button(imd, event->button, event->time,
				 event->x, event->y, event->state, imd->data_button);
		}
}

static void image_scroll_notify_cb(PixbufRenderer *pr, gpointer data)
{
	ImageWindow *imd = data;

	if (imd->func_scroll_notify && pr->scale)
		{
		imd->func_scroll_notify(imd,
					(gint)((gdouble)pr->x_scroll / pr->scale),
					(gint)((gdouble)pr->y_scroll / pr->scale),
					(gint)((gdouble)pr->image_width - pr->vis_width / pr->scale),
					(gint)((gdouble)pr->image_height - pr->vis_height / pr->scale),
					imd->data_scroll_notify);
		}
}

static void image_update_util(ImageWindow *imd)
{
	if (imd->func_update) imd->func_update(imd, imd->data_update);
}

static void image_zoom_cb(PixbufRenderer *pr, gdouble zoom, gpointer data)
{
	ImageWindow *imd = data;

	if (imd->title_show_zoom) image_update_title(imd);
	image_update_util(imd);
}

static void image_complete_util(ImageWindow *imd, gint preload)
{
	if (imd->il && image_get_pixbuf(imd) != image_loader_get_pixbuf(imd->il)) return;

	if (debug) printf("image load completed \"%s\" (%s)\n",
			  (preload) ? imd->read_ahead_path : imd->image_path,
			  (preload) ? "preload" : "current");

	if (!preload) imd->completed = TRUE;
	if (imd->func_complete) imd->func_complete(imd, preload, imd->data_complete);
}

static void image_render_complete_cb(PixbufRenderer *pr, gpointer data)
{
	ImageWindow *imd = data;

	image_complete_util(imd, FALSE);
}

static void image_state_set(ImageWindow *imd, ImageState state)
{
	if (state == IMAGE_STATE_NONE)
		{
		imd->state = state;
		}
	else
		{
		imd->state |= state;
		}
	if (imd->func_state) imd->func_state(imd, state, imd->data_state);
}

static void image_state_unset(ImageWindow *imd, ImageState state)
{
	imd->state &= ~state;
	if (imd->func_state) imd->func_state(imd, state, imd->data_state);
}

/*
 *-------------------------------------------------------------------
 * misc
 *-------------------------------------------------------------------
 */

static void image_update_title(ImageWindow *imd)
{
	gchar *title = NULL;
	gchar *zoom = NULL;
	gchar *collection = NULL;

	if (!imd->top_window) return;

	if (imd->collection && collection_to_number(imd->collection) >= 0)
		{
		const gchar *name;
		name = imd->collection->name;
		if (!name) name = _("Untitled");
		collection = g_strdup_printf(" (Collection %s)", name);
		}

	if (imd->title_show_zoom)
		{
		gchar *buf = image_zoom_get_as_text(imd);
		zoom = g_strconcat(" [", buf, "]", NULL);
		g_free(buf);
		}

	title = g_strdup_printf("%s%s%s%s%s%s",
		imd->title ? imd->title : "",
		imd->image_name ? imd->image_name : "",
		zoom ? zoom : "",
		collection ? collection : "",
		imd->image_name ? " - " : "",
		imd->title_right ? imd->title_right : "");

	gtk_window_set_title(GTK_WINDOW(imd->top_window), title);

	g_free(title);
	g_free(zoom);
	g_free(collection);
}

/*
 *-------------------------------------------------------------------
 * rotation, flip, etc.
 *-------------------------------------------------------------------
 */

static void image_alter_real(ImageWindow *imd, AlterType type, gint clamp)
{
	PixbufRenderer *pr;
	GdkPixbuf *new = NULL;
	gint exif_rotate;
	gint x, y;
	gint t;

	pr = (PixbufRenderer *)imd->pr;

	exif_rotate = (imd->delay_alter_type != ALTER_NONE && (imd->state & IMAGE_STATE_ROTATE_AUTO));
	imd->delay_alter_type = ALTER_NONE;

	if (!pr->pixbuf) return;

	x = pr->x_scroll + (pr->vis_width / 2);
	y = pr->y_scroll + (pr->vis_height / 2);

	switch (type)
		{
		case ALTER_ROTATE_90:
			new = pixbuf_copy_rotate_90(pr->pixbuf, FALSE);
			t = x;
			x = pr->height - y;
			y = t;
			break;
		case ALTER_ROTATE_90_CC:
			new = pixbuf_copy_rotate_90(pr->pixbuf, TRUE);
			t = x;
			x = y;
			y = pr->width - t;
			break;
		case ALTER_ROTATE_180:
			new = pixbuf_copy_mirror(pr->pixbuf, TRUE, TRUE);
			x = pr->width - x;
			y = pr->height - y;
			break;
		case ALTER_MIRROR:
			new = pixbuf_copy_mirror(pr->pixbuf, TRUE, FALSE);
			x = pr->width - x;
			break;
		case ALTER_FLIP:
			new = pixbuf_copy_mirror(pr->pixbuf, FALSE, TRUE);
			y = pr->height - y;
			break;
		case ALTER_DESATURATE:
			pixbuf_desaturate_rect(pr->pixbuf,
					       0, 0,  pr->image_width, pr->image_height);
			image_area_changed(imd, 0, 0, pr->image_width, pr->image_height);
			break;
		case ALTER_NONE:
		default:
			return;
			break;
		}

	if (!new) return;

	pixbuf_renderer_set_pixbuf(pr, new, pr->zoom);
	g_object_unref(new);

	if (clamp && pr->zoom != 0.0 && pr->scale != 0.0)
		{
		if (exif_rotate)
			{
			switch (pr->scroll_reset)
				{
				case PR_SCROLL_RESET_NOCHANGE:
					break;
				case PR_SCROLL_RESET_CENTER:
					x = (gint)((gdouble)pr->image_width / 2.0 * pr->scale);
					y = (gint)((gdouble)pr->image_height / 2.0 * pr->scale);
					break;
				case PR_SCROLL_RESET_TOPLEFT:
				default:
					x = 0;
					y = 0;
					break;
				}
			}
		pixbuf_renderer_scroll_to_point(pr, (gint)((gdouble)x / pr->scale),
						    (gint)((gdouble)y / pr->scale),
						    0.50, 0.50);
		}

	if (exif_rotate) image_state_set(imd, IMAGE_STATE_ROTATE_AUTO);
}

static void image_post_process_alter(ImageWindow *imd, gint clamp)
{
	if (imd->delay_alter_type != ALTER_NONE)
		{
		image_alter_real(imd, imd->delay_alter_type, clamp);
		}
}

static void image_post_process_color_cb(ColorMan *cm, ColorManReturnType type, gpointer data)
{
	ImageWindow *imd = data;

	color_man_free(cm);
	if (type == COLOR_RETURN_IMAGE_CHANGED)
		{
		if (cm == imd->cm) imd->cm = NULL;
		return;
		}

	imd->cm = NULL;
	image_state_set(imd, IMAGE_STATE_COLOR_ADJ);

	image_post_process_alter(imd, FALSE);

	image_read_ahead_start(imd);
}

static gint image_post_process_color(ImageWindow *imd, gint start_row, ExifData *exif)
{
	ColorMan *cm;
	ColorManProfileType input_type;
	ColorManProfileType screen_type;
	const gchar *input_file;
	const gchar *screen_file;
	ExifItem *item = NULL;

	if (imd->cm) return FALSE;

	if (imd->color_profile_input >= 1 &&
	    imd->color_profile_input <= COLOR_PROFILE_INPUTS)
		{
		gint n;

		n = imd->color_profile_input - 1;
		if (!color_profile_input_file[n]) return FALSE;

		input_type = COLOR_PROFILE_FILE;
		input_file = color_profile_input_file[n];
		}
	else if (imd->color_profile_input == 0)
		{
		input_type = COLOR_PROFILE_SRGB;
		input_file = NULL;
		}
	else
		{
		return FALSE;
		}

	if (imd->color_profile_screen == 1 &&
	    color_profile_screen_file)
		{
		screen_type = COLOR_PROFILE_FILE;
		screen_file = color_profile_screen_file;
		}
	else if (imd->color_profile_screen == 0)
		{
		screen_type = COLOR_PROFILE_SRGB;
		screen_file = NULL;
		}
	else
		{
		return FALSE;
		}

	if (imd->color_profile_use_image && exif)
		{
		item = exif_get_item(exif, "ColorProfile");
		if (!item)
			{
			gint cs;

			/* ColorSpace == 1 specifies sRGB per EXIF 2.2 */
			if (exif_get_integer(exif, "ColorSpace", &cs) &&
			    cs == 1)
				{
				input_type = COLOR_PROFILE_SRGB;
				input_file = NULL;

				if (debug) printf("Found EXIF ColorSpace of sRGB\n");
				}
			}
		}
	if (item && item->format == EXIF_FORMAT_UNDEFINED)
		{
		if (debug) printf("Found embedded color profile\n");

		cm = color_man_new_embedded(imd, NULL,
					    item->data, item->data_len,
					    screen_type, screen_file,
					    image_post_process_color_cb, imd);
		}
	else
		{
		cm = color_man_new(imd, NULL,
				   input_type, input_file,
				   screen_type, screen_file,
				   image_post_process_color_cb, imd);
		}

	if (cm)
		{
		if (start_row > 0)
			{
			cm->row = start_row;
			cm->incremental_sync = TRUE;
			}

		imd->cm = (gpointer)cm;
		return TRUE;
		}

	return FALSE;
}

static void image_post_process(ImageWindow *imd, gint clamp)
{
	ExifData *exif = NULL;

	if (!image_get_pixbuf(imd)) return;

	if (exif_rotate_enable ||
	    (imd->color_profile_enable && imd->color_profile_use_image) )
		{
		exif = exif_read(imd->image_path, (imd->color_profile_enable && imd->color_profile_use_image));
		}

	if (exif_rotate_enable && exif)
		{
		gint orientation;

		if (exif_get_integer(exif, "Orientation", &orientation))
			{
			gint rotate = TRUE;

			/* see http://jpegclub.org/exif_orientation.html 
			  1        2       3      4         5            6           7          8

			888888  888888      88  88      8888888888  88                  88  8888888888
			88          88      88  88      88  88      88  88          88  88      88  88
			8888      8888    8888  8888    88          8888888888  8888888888          88
			88          88      88  88
			88          88  888888  888888
			*/
			switch (orientation)
				{
				case EXIF_ORIENTATION_TOP_LEFT:
					/* normal -- nothing to do */
					rotate = FALSE;
					break;
				case EXIF_ORIENTATION_TOP_RIGHT:
					/* mirrored */
					imd->delay_alter_type = ALTER_MIRROR;
					break;
				case EXIF_ORIENTATION_BOTTOM_RIGHT:
					/* upside down */
					imd->delay_alter_type = ALTER_ROTATE_180;
					break;
				case EXIF_ORIENTATION_BOTTOM_LEFT:
					/* flipped */
					imd->delay_alter_type = ALTER_FLIP;
					break;
				case EXIF_ORIENTATION_LEFT_TOP:
					/* not implemented -- too wacky to fix in one step */
					rotate = FALSE;
					break;
				case EXIF_ORIENTATION_RIGHT_TOP:
					/* rotated -90 (270) */
					imd->delay_alter_type = ALTER_ROTATE_90;
					break;
				case EXIF_ORIENTATION_RIGHT_BOTTOM:
					/* not implemented -- too wacky to fix in one step */
					rotate = FALSE;
					break;
				case EXIF_ORIENTATION_LEFT_BOTTOM:
					/* rotated 90 */
					imd->delay_alter_type = ALTER_ROTATE_90_CC;
					break;
				default:
					/* The other values are out of range */
					rotate = FALSE;
					break;
				}

			if (rotate) image_state_set(imd, IMAGE_STATE_ROTATE_AUTO);
			}
		}

	if (imd->color_profile_enable)
		{
		if (!image_post_process_color(imd, 0, exif))
			{
			/* fixme: note error to user */
			image_state_set(imd, IMAGE_STATE_COLOR_ADJ);
			}
		}

	if (!imd->cm) image_post_process_alter(imd, clamp);

	exif_free(exif);
}

/*
 *-------------------------------------------------------------------
 * read ahead (prebuffer)
 *-------------------------------------------------------------------
 */

static void image_read_ahead_cancel(ImageWindow *imd)
{
	if (debug) printf("read ahead cancelled for :%s\n", imd->read_ahead_path);

	image_loader_free(imd->read_ahead_il);
	imd->read_ahead_il = NULL;

	if (imd->read_ahead_pixbuf) g_object_unref(imd->read_ahead_pixbuf);
	imd->read_ahead_pixbuf = NULL;

	g_free(imd->read_ahead_path);
	imd->read_ahead_path = NULL;
}

static void image_read_ahead_done_cb(ImageLoader *il, gpointer data)
{
	ImageWindow *imd = data;

	if (debug) printf("read ahead done for :%s\n", imd->read_ahead_path);

	imd->read_ahead_pixbuf = image_loader_get_pixbuf(imd->read_ahead_il);
	if (imd->read_ahead_pixbuf)
		{
		g_object_ref(imd->read_ahead_pixbuf);
		}
	else
		{
		imd->read_ahead_pixbuf = pixbuf_inline(PIXBUF_INLINE_BROKEN);
		}
	image_loader_free(imd->read_ahead_il);
	imd->read_ahead_il = NULL;

	image_complete_util(imd, TRUE);
}

static void image_read_ahead_error_cb(ImageLoader *il, gpointer data)
{
	/* we even treat errors as success, maybe at least some of the file was ok */
	image_read_ahead_done_cb(il, data);
}

static void image_read_ahead_start(ImageWindow *imd)
{
	/* already started ? */
	if (!imd->read_ahead_path || imd->read_ahead_il || imd->read_ahead_pixbuf) return;

	/* still loading ?, do later */
	if (imd->il || imd->cm) return;

	if (debug) printf("read ahead started for :%s\n", imd->read_ahead_path);

	imd->read_ahead_il = image_loader_new(imd->read_ahead_path);

	image_loader_set_error_func(imd->read_ahead_il, image_read_ahead_error_cb, imd);
	if (!image_loader_start(imd->read_ahead_il, image_read_ahead_done_cb, imd))
		{
		image_read_ahead_cancel(imd);
		image_complete_util(imd, TRUE);
		}
}

static void image_read_ahead_set(ImageWindow *imd, const gchar *path)
{
	if (imd->read_ahead_path && path && strcmp(imd->read_ahead_path, path) == 0) return;

	image_read_ahead_cancel(imd);

	imd->read_ahead_path = g_strdup(path);

	if (debug) printf("read ahead set to :%s\n", imd->read_ahead_path);

	image_read_ahead_start(imd);
}

/*
 *-------------------------------------------------------------------
 * post buffering
 *-------------------------------------------------------------------
 */

static void image_post_buffer_set(ImageWindow *imd, const gchar *path, GdkPixbuf *pixbuf, gint color_row)
{
	g_free(imd->prev_path);
	if (imd->prev_pixbuf) g_object_unref(imd->prev_pixbuf);

	if (path && pixbuf)
		{
		imd->prev_path = g_strdup(path);
			
		g_object_ref(pixbuf);
		imd->prev_pixbuf = pixbuf;
		imd->prev_color_row = color_row;
		}
	else
		{
		imd->prev_path = NULL;
		imd->prev_pixbuf = NULL;
		imd->prev_color_row = -1;
		}

	if (debug) printf("post buffer set: %s\n", path);
}

static gint image_post_buffer_get(ImageWindow *imd)
{
	gint success;

	if (imd->prev_pixbuf &&
	    imd->image_path && imd->prev_path && strcmp(imd->image_path, imd->prev_path) == 0)
		{
		image_change_pixbuf(imd, imd->prev_pixbuf, image_zoom_get(imd));
		if (imd->prev_color_row >= 0)
			{
			ExifData *exif = NULL;

			if (imd->color_profile_use_image) exif = exif_read(imd->image_path, TRUE);
			image_post_process_color(imd, imd->prev_color_row, exif);
			exif_free(exif);
			}
		success = TRUE;
		}
	else
		{
		success = FALSE;
		}

	if (imd->prev_pixbuf) g_object_unref(imd->prev_pixbuf);
	imd->prev_pixbuf = NULL;

	g_free(imd->prev_path);
	imd->prev_path = NULL;

	return success;
}

/*
 *-------------------------------------------------------------------
 * loading
 *-------------------------------------------------------------------
 */

static void image_load_pixbuf_ready(ImageWindow *imd)
{
	if (image_get_pixbuf(imd) || !imd->il) return;

	image_change_pixbuf(imd, image_loader_get_pixbuf(imd->il), image_zoom_get(imd));
}

static void image_load_area_cb(ImageLoader *il, guint x, guint y, guint w, guint h, gpointer data)
{
	ImageWindow *imd = data;
	PixbufRenderer *pr;

	pr = (PixbufRenderer *)imd->pr;

	if (imd->delay_flip &&
	    pr->pixbuf != image_loader_get_pixbuf(il))
		{
		return;
		}

	if (!pr->pixbuf) image_load_pixbuf_ready(imd);

	pixbuf_renderer_area_changed(pr, x, y, w, h);
}

static void image_load_done_cb(ImageLoader *il, gpointer data)
{
	ImageWindow *imd = data;

	if (debug) printf ("image done\n");

	g_object_set(G_OBJECT(imd->pr), "loading", FALSE, NULL);
	image_state_unset(imd, IMAGE_STATE_LOADING);

	if (imd->delay_flip &&
	    image_get_pixbuf(imd) != image_loader_get_pixbuf(imd->il))
		{
		g_object_set(G_OBJECT(imd->pr), "complete", FALSE, NULL);
		image_change_pixbuf(imd, image_loader_get_pixbuf(imd->il), image_zoom_get(imd));
		}

	image_loader_free(imd->il);
	imd->il = NULL;

	image_post_process(imd, TRUE);

	image_read_ahead_start(imd);
}

static void image_load_error_cb(ImageLoader *il, gpointer data)
{
	if (debug) printf ("image error\n");

	/* even on error handle it like it was done,
	 * since we have a pixbuf with _something_ */

	image_load_done_cb(il, data);
}

#ifdef IMAGE_THROTTLE_LARGER_IMAGES
static void image_load_buffer_throttle(ImageLoader *il)
{
	if (!il || il->bytes_total < IMAGE_THROTTLE_THRESHOLD) return;

	/* Larger image files usually have larger chunks of data per pixel...
	 * So increase the buffer read size so that the rendering chunks called
	 * are also larger.
	 */

	image_loader_set_buffer_size(il, IMAGE_LOAD_BUFFER_COUNT * IMAGE_THROTTLE_FACTOR);
}
#endif

/* this read ahead is located here merely for the callbacks, above */

static gint image_read_ahead_check(ImageWindow *imd)
{
	if (!imd->read_ahead_path) return FALSE;
	if (imd->il) return FALSE;

	if (!imd->image_path || strcmp(imd->read_ahead_path, imd->image_path) != 0)
		{
		image_read_ahead_cancel(imd);
		return FALSE;
		}

	if (imd->read_ahead_il)
		{
		imd->il = imd->read_ahead_il;
		imd->read_ahead_il = NULL;

		/* override the old signals */
		image_loader_set_area_ready_func(imd->il, image_load_area_cb, imd);
		image_loader_set_error_func(imd->il, image_load_error_cb, imd);
		image_loader_set_buffer_size(imd->il, IMAGE_LOAD_BUFFER_COUNT);

#ifdef IMAGE_THROTTLE_LARGER_IMAGES
		image_load_buffer_throttle(imd->il);
#endif

		/* do this one directly (probably should add a set func) */
		imd->il->func_done = image_load_done_cb;

		g_object_set(G_OBJECT(imd->pr), "loading", TRUE, NULL);
		image_state_set(imd, IMAGE_STATE_LOADING);

		if (!imd->delay_flip)
			{
			image_change_pixbuf(imd, image_loader_get_pixbuf(imd->il), image_zoom_get(imd));
			}

		image_read_ahead_cancel(imd);
		return TRUE;
		}
	else if (imd->read_ahead_pixbuf)
		{
		image_change_pixbuf(imd, imd->read_ahead_pixbuf, image_zoom_get(imd));
		g_object_unref(imd->read_ahead_pixbuf);
		imd->read_ahead_pixbuf = NULL;

		image_read_ahead_cancel(imd);

		image_post_process(imd, FALSE);
		return TRUE;
		}

	image_read_ahead_cancel(imd);
	return FALSE;
}

static gint image_load_begin(ImageWindow *imd, const gchar *path)
{
	if (debug) printf ("image begin \n");

	if (imd->il) return FALSE;

	imd->completed = FALSE;
	g_object_set(G_OBJECT(imd->pr), "complete", FALSE, NULL);

	if (image_post_buffer_get(imd))
		{
		if (debug) printf("from post buffer: %s\n", imd->image_path);
		return TRUE;
		}

	if (image_read_ahead_check(imd))
		{
		if (debug) printf("from read ahead buffer: %s\n", imd->image_path);
		return TRUE;
		}

	if (!imd->delay_flip && image_get_pixbuf(imd))
		{
		PixbufRenderer *pr;

		pr = PIXBUF_RENDERER(imd->pr);
		if (pr->pixbuf) g_object_unref(pr->pixbuf);
		pr->pixbuf = NULL;
		}

	g_object_set(G_OBJECT(imd->pr), "loading", TRUE, NULL);

	imd->il = image_loader_new(path);

	image_loader_set_area_ready_func(imd->il, image_load_area_cb, imd);
	image_loader_set_error_func(imd->il, image_load_error_cb, imd);
	image_loader_set_buffer_size(imd->il, IMAGE_LOAD_BUFFER_COUNT);

	if (!image_loader_start(imd->il, image_load_done_cb, imd))
		{
		if (debug) printf("image start error\n");

		g_object_set(G_OBJECT(imd->pr), "loading", FALSE, NULL);

		image_loader_free(imd->il);
		imd->il = NULL;

		image_complete_util(imd, FALSE);

		return FALSE;
		}

	image_state_set(imd, IMAGE_STATE_LOADING);

#ifdef IMAGE_THROTTLE_LARGER_IMAGES
	image_load_buffer_throttle(imd->il);
#endif

	if (!imd->delay_flip && !image_get_pixbuf(imd)) image_load_pixbuf_ready(imd);

	return TRUE;
}

static void image_reset(ImageWindow *imd)
{
	/* stops anything currently being done */

	if (debug) printf("image reset\n");

	g_object_set(G_OBJECT(imd->pr), "loading", FALSE, NULL);

	image_loader_free(imd->il);
	imd->il = NULL;

	color_man_free((ColorMan *)imd->cm);
	imd->cm = NULL;

	imd->delay_alter_type = ALTER_NONE;

	image_state_set(imd, IMAGE_STATE_NONE);
}

/*
 *-------------------------------------------------------------------
 * image changer
 *-------------------------------------------------------------------
 */

static void image_change_complete(ImageWindow *imd, gdouble zoom, gint new)
{
	image_reset(imd);

	if (imd->image_path && isfile(imd->image_path))
		{
		PixbufRenderer *pr;

		pr = PIXBUF_RENDERER(imd->pr);
		pr->zoom = zoom;	/* store the zoom, needed by the loader */

		if (image_load_begin(imd, imd->image_path))
			{
			imd->unknown = FALSE;
			}
		else
			{
			GdkPixbuf *pixbuf;

			pixbuf = pixbuf_inline(PIXBUF_INLINE_BROKEN);
			image_change_pixbuf(imd, pixbuf, zoom);
			g_object_unref(pixbuf);

			imd->unknown = TRUE;
			}
		imd->size = filesize(imd->image_path);
		imd->mtime = filetime(imd->image_path);
		}
	else
		{
		if (imd->image_path)
			{
			GdkPixbuf *pixbuf;

			pixbuf = pixbuf_inline(PIXBUF_INLINE_BROKEN);
			image_change_pixbuf(imd, pixbuf, zoom);
			g_object_unref(pixbuf);
			imd->mtime = filetime(imd->image_path);
			}
		else
			{
			image_change_pixbuf(imd, NULL, zoom);
			imd->mtime = 0;
			}
		imd->unknown = TRUE;
		imd->size = 0;
		}

	image_update_util(imd);
}

static void image_change_real(ImageWindow *imd, const gchar *path,
			      CollectionData *cd, CollectInfo *info, gdouble zoom)
{
	GdkPixbuf *pixbuf;
	GdkPixbuf *prev_pixbuf = NULL;
	gchar *prev_path = NULL;
	gint prev_clear = FALSE;
	gint prev_color_row = -1;

	imd->collection = cd;
	imd->collection_info = info;

	pixbuf = image_get_pixbuf(imd);

	if (enable_read_ahead && imd->image_path && pixbuf)
		{
		if (imd->il)
			{
			/* current image is not finished */
			prev_clear = TRUE;
			}
		else
			{
			prev_path = g_strdup(imd->image_path);
			prev_pixbuf = pixbuf;
			g_object_ref(prev_pixbuf);

			if (imd->cm)
				{
				ColorMan *cm;

				cm = (ColorMan *)imd->cm;
				prev_color_row = cm->row;
				}
			}
		}

	g_free(imd->image_path);
	imd->image_path = g_strdup(path);
	imd->image_name = filename_from_path(imd->image_path);

	image_change_complete(imd, zoom, TRUE);

	if (prev_pixbuf)
		{
		image_post_buffer_set(imd, prev_path, prev_pixbuf, prev_color_row);
		g_free(prev_path);
		g_object_unref(prev_pixbuf);
		}
	else if (prev_clear)
		{
		image_post_buffer_set(imd, NULL, NULL, -1);
		}

	image_update_title(imd);
	image_state_set(imd, IMAGE_STATE_IMAGE);
}

/*
 *-------------------------------------------------------------------
 * focus stuff
 *-------------------------------------------------------------------
 */

static void image_focus_paint(ImageWindow *imd, gint has_focus, GdkRectangle *area)
{
	GtkWidget *widget;

	widget = imd->widget;
	if (!widget->window) return;

	if (has_focus)
		{
		gtk_paint_focus (widget->style, widget->window, GTK_STATE_ACTIVE,
				 area, widget, "image_window",
				 widget->allocation.x, widget->allocation.y,
				 widget->allocation.width - 1, widget->allocation.height - 1);	
		}
	else
		{
		gtk_paint_shadow (widget->style, widget->window, GTK_STATE_NORMAL, GTK_SHADOW_IN,
				  area, widget, "image_window",
				  widget->allocation.x, widget->allocation.y,
				  widget->allocation.width - 1, widget->allocation.height - 1);
		}
}

static gint image_focus_expose(GtkWidget *widget, GdkEventExpose *event, gpointer data)
{
	ImageWindow *imd = data;

	image_focus_paint(imd, GTK_WIDGET_HAS_FOCUS(widget), &event->area);
	return TRUE;
}

static gint image_focus_in_cb(GtkWidget *widget, GdkEventFocus *event, gpointer data)
{
	ImageWindow *imd = data;

	GTK_WIDGET_SET_FLAGS(imd->widget, GTK_HAS_FOCUS);
	image_focus_paint(imd, TRUE, NULL);

	return TRUE;
}

static gint image_focus_out_cb(GtkWidget *widget, GdkEventFocus *event, gpointer data)
{
	ImageWindow *imd = data;

	GTK_WIDGET_UNSET_FLAGS(imd->widget, GTK_HAS_FOCUS);
	image_focus_paint(imd, FALSE, NULL);

	return TRUE;
}

gint image_overlay_add(ImageWindow *imd, GdkPixbuf *pixbuf, gint x, gint y,
		       gint relative, gint always)
{
	return pixbuf_renderer_overlay_add((PixbufRenderer *)imd->pr, pixbuf, x, y, relative, always);
}

void image_overlay_set(ImageWindow *imd, gint id, GdkPixbuf *pixbuf, gint x, gint y)
{
	pixbuf_renderer_overlay_set((PixbufRenderer *)imd->pr, id, pixbuf, x, y);
}

gint image_overlay_get(ImageWindow *imd, gint id, GdkPixbuf **pixbuf, gint *x, gint *y)
{
	return pixbuf_renderer_overlay_get((PixbufRenderer *)imd->pr, id, pixbuf, x, y);
}

void image_overlay_remove(ImageWindow *imd, gint id)
{
	pixbuf_renderer_overlay_remove((PixbufRenderer *)imd->pr, id);
}

static gint image_scroll_cb(GtkWidget *widget, GdkEventScroll *event, gpointer data)
{
	ImageWindow *imd = data;

	if (imd->func_scroll &&
	    event && event->type == GDK_SCROLL)
	        {
		imd->func_scroll(imd, event->direction, event->time,
				 event->x, event->y, event->state, imd->data_scroll);
		return TRUE;
		}

	return FALSE;
}

/*
 *-------------------------------------------------------------------
 * public interface
 *-------------------------------------------------------------------
 */

void image_attach_window(ImageWindow *imd, GtkWidget *window,
			 const gchar *title, const gchar *title_right, gint show_zoom)
{
	imd->top_window = window;
	g_free(imd->title);
	imd->title = g_strdup(title);
	g_free(imd->title_right);
	imd->title_right = g_strdup(title_right);
	imd->title_show_zoom = show_zoom;

	if (!fit_window) window = NULL;

	pixbuf_renderer_set_parent((PixbufRenderer *)imd->pr, (GtkWindow *)window);

	image_update_title(imd);
}

void image_set_update_func(ImageWindow *imd,
			   void (*func)(ImageWindow *imd, gpointer data),
			   gpointer data)
{
	imd->func_update = func;
	imd->data_update = data;
}

void image_set_complete_func(ImageWindow *imd,
			     void (*func)(ImageWindow *imd, gint preload, gpointer data),
			     gpointer data)
{
	imd->func_complete = func;
	imd->data_complete = data;
}

void image_set_state_func(ImageWindow *imd,
			void (*func)(ImageWindow *imd, ImageState state, gpointer data),
			gpointer data)
{
	imd->func_state = func;
	imd->data_state = data;
}


void image_set_button_func(ImageWindow *imd,
			   void (*func)(ImageWindow *, gint button, guint32 time, gdouble x, gdouble y, guint state, gpointer),
			   gpointer data)
{
	imd->func_button = func;
	imd->data_button = data;
}

void image_set_scroll_func(ImageWindow *imd,
			   void (*func)(ImageWindow *, GdkScrollDirection direction, guint32 time, gdouble x, gdouble y, guint state, gpointer),
			   gpointer data)
{
	imd->func_scroll = func;
	imd->data_scroll = data;
}

void image_set_scroll_notify_func(ImageWindow *imd,
				  void (*func)(ImageWindow *imd, gint x, gint y, gint width, gint height, gpointer data),
				  gpointer data)
{
	imd->func_scroll_notify = func;
	imd->data_scroll_notify = data;
}

/* path, name */

const gchar *image_get_path(ImageWindow *imd)
{
	return imd->image_path;
}

const gchar *image_get_name(ImageWindow *imd)
{
	return imd->image_name;
}

/* merely changes path string, does not change the image! */
void image_set_path(ImageWindow *imd, const gchar *newpath)
{
	g_free(imd->image_path);
	imd->image_path = g_strdup(newpath);
	imd->image_name = filename_from_path(imd->image_path);

	image_update_title(imd);
	image_state_set(imd, IMAGE_STATE_IMAGE);
}

/* load a new image */

void image_change_path(ImageWindow *imd, const gchar *path, gdouble zoom)
{
	if (imd->image_path == path ||
	    (path && imd->image_path && !strcmp(path, imd->image_path)) ) return;

	image_change_real(imd, path, NULL, NULL, zoom);
}

GdkPixbuf *image_get_pixbuf(ImageWindow *imd)
{
	return pixbuf_renderer_get_pixbuf((PixbufRenderer *)imd->pr);
}

void image_change_pixbuf(ImageWindow *imd, GdkPixbuf *pixbuf, gdouble zoom)
{
	pixbuf_renderer_set_pixbuf((PixbufRenderer *)imd->pr, pixbuf, zoom);
	image_state_set(imd, IMAGE_STATE_IMAGE);
}

void image_change_from_collection(ImageWindow *imd, CollectionData *cd, CollectInfo *info, gdouble zoom)
{
	if (!cd || !info || !g_list_find(cd->list, info)) return;

	image_change_real(imd, info->path, cd, info, zoom);
}

CollectionData *image_get_collection(ImageWindow *imd, CollectInfo **info)
{
	if (collection_to_number(imd->collection) >= 0)
		{
		if (g_list_find(imd->collection->list, imd->collection_info) != NULL)
			{
			if (info) *info = imd->collection_info;
			}
		else
			{
			if (info) *info = NULL;
			}
		return imd->collection;
		}

	if (info) *info = NULL;
	return NULL;
}

static void image_loader_sync_data(ImageLoader *il, gpointer data)
{
	/* change data for the callbacks directly */

	il->data_area_ready = data;
	il->data_error = data;
	il->data_done = data;
	il->data_percent = data;
}

/* this is more like a move function
 * it moves most data from source to imd
 */
void image_change_from_image(ImageWindow *imd, ImageWindow *source)
{
	if (imd == source) return;

	imd->unknown = source->unknown;

	imd->collection = source->collection;
	imd->collection_info = source->collection_info;
	imd->size = source->size;
	imd->mtime = source->mtime;

	image_set_path(imd, image_get_path(source));

	image_loader_free(imd->il);
	imd->il = NULL;

	if (source->il)
		{
		imd->il = source->il;
		source->il = NULL;

		image_loader_sync_data(imd->il, imd);

		imd->delay_alter_type = source->delay_alter_type;
		source->delay_alter_type = ALTER_NONE;
		}

	imd->color_profile_enable = source->color_profile_enable;
	imd->color_profile_input = source->color_profile_input;
	imd->color_profile_screen = source->color_profile_screen;
	imd->color_profile_use_image = source->color_profile_use_image;
	color_man_free((ColorMan *)imd->cm);
	imd->cm = NULL;
	if (source->cm)
		{
		ColorMan *cm;

		imd->cm = source->cm;
		source->cm = NULL;

		cm = (ColorMan *)imd->cm;
		cm->imd = imd;
		cm->func_done_data = imd;
		}

	image_loader_free(imd->read_ahead_il);
	imd->read_ahead_il = source->read_ahead_il;
	source->read_ahead_il = NULL;
	if (imd->read_ahead_il) image_loader_sync_data(imd->read_ahead_il, imd);

	if (imd->read_ahead_pixbuf) g_object_unref(imd->read_ahead_pixbuf);
	imd->read_ahead_pixbuf = source->read_ahead_pixbuf;
	source->read_ahead_pixbuf = NULL;

	g_free(imd->read_ahead_path);
	imd->read_ahead_path = source->read_ahead_path;
	source->read_ahead_path = NULL;

	if (imd->prev_pixbuf) g_object_unref(imd->prev_pixbuf);
	imd->prev_pixbuf = source->prev_pixbuf;
	source->prev_pixbuf = NULL;
	imd->prev_color_row = source->prev_color_row;
	source->prev_color_row = -1;

	g_free(imd->prev_path);
	imd->prev_path = source->prev_path;
	source->prev_path = NULL;

	imd->completed = source->completed;
	imd->state = source->state;
	source->state = IMAGE_STATE_NONE;

	pixbuf_renderer_move(PIXBUF_RENDERER(imd->pr), PIXBUF_RENDERER(source->pr));
}

/* manipulation */

void image_area_changed(ImageWindow *imd, gint x, gint y, gint width, gint height)
{
	pixbuf_renderer_area_changed((PixbufRenderer *)imd->pr, x, y, width, height);
}

void image_reload(ImageWindow *imd)
{
	if (pixbuf_renderer_get_tiles((PixbufRenderer *)imd->pr)) return;

	image_change_complete(imd, image_zoom_get(imd), FALSE);
}

void image_scroll(ImageWindow *imd, gint x, gint y)
{
	pixbuf_renderer_scroll((PixbufRenderer *)imd->pr, x, y);
}

void image_scroll_to_point(ImageWindow *imd, gint x, gint y,
			   gdouble x_align, gdouble y_align)
{
	pixbuf_renderer_scroll_to_point((PixbufRenderer *)imd->pr, x, y, x_align, y_align);
}

void image_alter(ImageWindow *imd, AlterType type)
{
	if (pixbuf_renderer_get_tiles((PixbufRenderer *)imd->pr)) return;

	if (imd->il || imd->cm)
		{
		/* still loading, wait till done */
		imd->delay_alter_type = type;
		image_state_set(imd, IMAGE_STATE_ROTATE_USER);

		if (imd->cm && (imd->state & IMAGE_STATE_ROTATE_AUTO))
			{
			image_state_unset(imd, IMAGE_STATE_ROTATE_AUTO);
			}
		return;
		}

	image_alter_real(imd, type, TRUE);
}

void image_zoom_adjust(ImageWindow *imd, gdouble increment)
{
	pixbuf_renderer_zoom_adjust((PixbufRenderer *)imd->pr, increment);
}

void image_zoom_adjust_at_point(ImageWindow *imd, gdouble increment, gint x, gint y)
{
	pixbuf_renderer_zoom_adjust_at_point((PixbufRenderer *)imd->pr, increment, x, y);
}

void image_zoom_set_limits(ImageWindow *imd, gdouble min, gdouble max)
{
	pixbuf_renderer_zoom_set_limits((PixbufRenderer *)imd->pr, min, max);
}

void image_zoom_set(ImageWindow *imd, gdouble zoom)
{
	pixbuf_renderer_zoom_set((PixbufRenderer *)imd->pr, zoom);
}

void image_zoom_set_fill_geometry(ImageWindow *imd, gint vertical)
{
	PixbufRenderer *pr;
	gdouble zoom;
	gint width, height;

	pr = (PixbufRenderer *)imd->pr;

	if (!pixbuf_renderer_get_pixbuf(pr) ||
	    !pixbuf_renderer_get_image_size(pr, &width, &height)) return;

	if (vertical)
		{
		zoom = (gdouble)pr->window_height / height;
		}
	else
		{
		zoom = (gdouble)pr->window_width / width;
		}

	if (zoom < 1.0)
		{
		zoom = 0.0 - 1.0 / zoom;
		}

	pixbuf_renderer_zoom_set(pr, zoom);
}

gdouble image_zoom_get(ImageWindow *imd)
{
	return pixbuf_renderer_zoom_get((PixbufRenderer *)imd->pr);
}

gdouble image_zoom_get_real(ImageWindow *imd)
{
	return pixbuf_renderer_zoom_get_scale((PixbufRenderer *)imd->pr);
}

gchar *image_zoom_get_as_text(ImageWindow *imd)
{
	gdouble zoom;
	gdouble scale;
	gdouble l = 1.0;
	gdouble r = 1.0;
	gint pl = 0;
	gint pr = 0;
	gchar *approx = " ";

	zoom = image_zoom_get(imd);
	scale = image_zoom_get_real(imd);

	if (zoom > 0.0)
		{
		l = zoom;
		}
	else if (zoom < 0.0)
		{
		r = 0.0 - zoom;
		}
	else if (zoom == 0.0 && scale != 0.0)
		{
		if (scale >= 1.0)
			{
			l = scale;
			}
		else
			{
			r = 1.0 / scale;
			}
		approx = " ~";
		}

	if (rint(l) != l) pl = 1;
	if (rint(r) != r) pr = 1;

	return g_strdup_printf("%.*f :%s%.*f", pl, l, approx, pr, r);
}

gdouble image_zoom_get_default(ImageWindow *imd, gint mode)
{
	gdouble zoom;

	if (mode == ZOOM_RESET_ORIGINAL)
		{
		zoom = 1.0;
		}
	else if (mode == ZOOM_RESET_FIT_WINDOW)
		{
		zoom = 0.0;
		}
	else
		{
		if (imd)
			{
			zoom = image_zoom_get(imd);
			}
		else
			{
			zoom = 1.0;
			}
		}

	return zoom;
}

/* read ahead */

void image_prebuffer_set(ImageWindow *imd, const gchar *path)
{
	if (pixbuf_renderer_get_tiles((PixbufRenderer *)imd->pr)) return;

	if (path)
		{
		image_read_ahead_set(imd, path);
		}
	else
		{
		image_read_ahead_cancel(imd);
		}
}

static gint image_auto_refresh_cb(gpointer data)
{
	ImageWindow *imd = data;
	time_t newtime;
	
	if (!imd || !image_get_pixbuf(imd) ||
	    imd->il || !imd->image_path ||
	    !update_on_time_change) return TRUE;

	newtime = filetime(imd->image_path);
	if (newtime > 0 && newtime != imd->mtime)
		{
		imd->mtime = newtime;
		image_reload(imd);
		}

	return TRUE;
}

/* image auto refresh on time stamp change, in 1/1000's second, -1 disables */

void image_auto_refresh(ImageWindow *imd, gint interval)
{
	if (!imd) return;
	if (pixbuf_renderer_get_tiles((PixbufRenderer *)imd->pr)) return;

	if (imd->auto_refresh_id > -1)
		{
		g_source_remove(imd->auto_refresh_id);
		imd->auto_refresh_id = -1;
		imd->auto_refresh_interval = -1;
		}

	if (interval < 0) return;

	if (interval == 0) interval = IMAGE_AUTO_REFRESH_TIME;

	imd->auto_refresh_id = g_timeout_add((guint32)interval, image_auto_refresh_cb, imd);
	imd->auto_refresh_interval = interval;
}

void image_top_window_set_sync(ImageWindow *imd, gint allow_sync)
{
	imd->top_window_sync = allow_sync;

	g_object_set(G_OBJECT(imd->pr), "window_fit", allow_sync, NULL);
}

void image_background_set_black(ImageWindow *imd, gint black)
{
	pixbuf_renderer_set_black((PixbufRenderer *)imd->pr, black);
}

void image_background_set_color(ImageWindow *imd, GdkColor *color)
{
	pixbuf_renderer_set_color((PixbufRenderer *)imd->pr, color);
}

void image_color_profile_set(ImageWindow *imd,
			     gint input_type, gint screen_type,
			     gint use_image)
{
	if (!imd) return;

	if (input_type < 0 || input_type > COLOR_PROFILE_INPUTS ||
	    screen_type < 0 || screen_type > 1)
		{
		return;
		}

	imd->color_profile_input = input_type;
	imd->color_profile_screen = screen_type;
	imd->color_profile_use_image = use_image;
}

gint image_color_profile_get(ImageWindow *imd,
			     gint *input_type, gint *screen_type,
			     gint *use_image)
{
	if (!imd) return FALSE;

	if (input_type) *input_type = imd->color_profile_input;
	if (screen_type) *screen_type = imd->color_profile_screen;
	if (use_image) *use_image = imd->color_profile_use_image;

	return TRUE;
}

void image_color_profile_set_use(ImageWindow *imd, gint enable)
{
	if (!imd) return;

	if (imd->color_profile_enable == enable) return;

	imd->color_profile_enable = enable;
}

gint image_color_profile_get_use(ImageWindow *imd)
{
	if (!imd) return FALSE;

	return imd->color_profile_enable;
}

void image_set_delay_flip(ImageWindow *imd, gint delay)
{
	if (!imd ||
	    imd->delay_flip == delay) return;

	imd->delay_flip = delay;

	g_object_set(G_OBJECT(imd->pr), "delay_flip", delay, NULL);

	if (!imd->delay_flip && imd->il)
		{
		PixbufRenderer *pr;

		pr = PIXBUF_RENDERER(imd->pr);
		if (pr->pixbuf) g_object_unref(pr->pixbuf);
		pr->pixbuf = NULL;

		image_load_pixbuf_ready(imd);
		}
}

void image_to_root_window(ImageWindow *imd, gint scaled)
{
	GdkScreen *screen;
	GdkWindow *rootwindow;
	GdkPixmap *pixmap;
	GdkPixbuf *pixbuf;
	GdkPixbuf *pb;
	gint width, height;

	if (!imd) return;

	pixbuf = image_get_pixbuf(imd);
	if (!pixbuf) return;

	screen = gtk_widget_get_screen(imd->widget);
	rootwindow = gdk_screen_get_root_window(screen);
	if (gdk_drawable_get_visual(rootwindow) != gdk_visual_get_system()) return;

	if (scaled)
		{
		width = gdk_screen_width();
		height = gdk_screen_height();
		}
	else
		{
		pixbuf_renderer_get_scaled_size((PixbufRenderer *)imd->pr, &width, &height);
		}

	pb = gdk_pixbuf_scale_simple(pixbuf, width, height, (GdkInterpType)zoom_quality);

	gdk_pixbuf_render_pixmap_and_mask (pb, &pixmap, NULL, 128);
	gdk_window_set_back_pixmap(rootwindow, pixmap, FALSE);
	gdk_window_clear(rootwindow);
	g_object_unref(pb);
	g_object_unref(pixmap);

	gdk_flush();
}

/*
 *-------------------------------------------------------------------
 * prefs sync
 *-------------------------------------------------------------------
 */

static void image_options_set(ImageWindow *imd)
{
	g_object_set(G_OBJECT(imd->pr), "zoom_quality", zoom_quality,
					"zoom_2pass", two_pass_zoom,
					"zoom_expand", zoom_to_fit_expands,
					"dither_quality", dither_quality,
					"scroll_reset", scroll_reset_method,
					"cache_display", tile_cache_max,
					"window_fit", (imd->top_window_sync && fit_window),
					"window_limit", limit_window_size,
					"window_limit_value", max_window_size,
					NULL);

	pixbuf_renderer_set_parent((PixbufRenderer *)imd->pr, (GtkWindow *)imd->top_window);
}

void image_options_sync(void)
{
	GList *work;

	work = image_list;
	while (work)
		{
		ImageWindow *imd;

		imd = work->data;
		work = work->next;

		image_options_set(imd);
		}
}

/*
 *-------------------------------------------------------------------
 * init / destroy
 *-------------------------------------------------------------------
 */

static void image_free(ImageWindow *imd)
{
	image_list = g_list_remove(image_list, imd);

	image_reset(imd);

	image_read_ahead_cancel(imd);
	image_post_buffer_set(imd, NULL, NULL, -1);
	image_auto_refresh(imd, -1);

	g_free(imd->image_path);
	g_free(imd->title);
	g_free(imd->title_right);

	g_free(imd);
}

static void image_destroy_cb(GtkObject *widget, gpointer data)
{
	ImageWindow *imd = data;
	image_free(imd);
}

ImageWindow *image_new(gint frame)
{
	ImageWindow *imd;

	imd = g_new0(ImageWindow, 1);

	imd->top_window = NULL;
	imd->title = NULL;
	imd->title_right = NULL;
	imd->title_show_zoom = FALSE;

	imd->unknown = TRUE;

	imd->has_frame = frame;
	imd->top_window_sync = FALSE;

	imd->delay_alter_type = ALTER_NONE;

	imd->read_ahead_il = NULL;
	imd->read_ahead_pixbuf = NULL;
	imd->read_ahead_path = NULL;

	imd->completed = FALSE;
	imd->state = IMAGE_STATE_NONE;

	imd->color_profile_enable = FALSE;
	imd->color_profile_input = 0;
	imd->color_profile_screen = 0;
	imd->color_profile_use_image = FALSE;

	imd->auto_refresh_id = -1;
	imd->auto_refresh_interval = -1;

	imd->delay_flip = FALSE;

	imd->func_update = NULL;
	imd->func_complete = NULL;
	imd->func_tile_request = NULL;
	imd->func_tile_dispose = NULL;

	imd->func_button = NULL;
	imd->func_scroll = NULL;

	imd->pr = GTK_WIDGET(pixbuf_renderer_new());

	image_options_set(imd);

	if (imd->has_frame)
		{
		imd->widget = gtk_frame_new(NULL);
		gtk_frame_set_shadow_type(GTK_FRAME(imd->widget), GTK_SHADOW_IN);
		gtk_container_add(GTK_CONTAINER(imd->widget), imd->pr);
		gtk_widget_show(imd->pr);

		GTK_WIDGET_SET_FLAGS(imd->widget, GTK_CAN_FOCUS);
		g_signal_connect(G_OBJECT(imd->widget), "focus_in_event",
				 G_CALLBACK(image_focus_in_cb), imd);
		g_signal_connect(G_OBJECT(imd->widget), "focus_out_event",
				 G_CALLBACK(image_focus_out_cb), imd);

		g_signal_connect_after(G_OBJECT(imd->widget), "expose_event",
				       G_CALLBACK(image_focus_expose), imd);
		}
	else
		{
		imd->widget = imd->pr;
		}

	g_signal_connect(G_OBJECT(imd->pr), "clicked",
			 G_CALLBACK(image_click_cb), imd);
	g_signal_connect(G_OBJECT(imd->pr), "scroll_notify",
			 G_CALLBACK(image_scroll_notify_cb), imd);

	g_signal_connect(G_OBJECT(imd->pr), "scroll_event",
			 G_CALLBACK(image_scroll_cb), imd);

	g_signal_connect(G_OBJECT(imd->pr), "destroy",
			 G_CALLBACK(image_destroy_cb), imd);

	g_signal_connect(G_OBJECT(imd->pr), "zoom",
			 G_CALLBACK(image_zoom_cb), imd);
	g_signal_connect(G_OBJECT(imd->pr), "render_complete",
			 G_CALLBACK(image_render_complete_cb), imd);

	image_list = g_list_append(image_list, imd);

	return imd;
}

