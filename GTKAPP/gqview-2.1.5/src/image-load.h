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


#ifndef IMAGE_LOAD_H
#define IMAGE_LOAD_H


ImageLoader *image_loader_new(const gchar *path);
void image_loader_free(ImageLoader *il);

void image_loader_set_area_ready_func(ImageLoader *il,
				      void (*func_area_ready)(ImageLoader *, guint, guint, guint, guint, gpointer),
				      gpointer data_area_ready);
void image_loader_set_error_func(ImageLoader *il,
				 void (*func_error)(ImageLoader *, gpointer),
				 gpointer data_error);
void image_loader_set_percent_func(ImageLoader *il,
				   void (*func_percent)(ImageLoader *, gdouble, gpointer),
				   gpointer data_percent);

/* Speed up loading when you only need at most width x height size image,
 * only the jpeg GdkPixbuf loader benefits from it - so there is no
 * guarantee that the image will scale down to the requested size..
 */
void image_loader_set_requested_size(ImageLoader *il, gint width, gint height);

void image_loader_set_buffer_size(ImageLoader *il, guint size);

/* this only has effect if used before image_loader_start()
 * default is G_PRIORITY_DEFAULT_IDLE
 */
void image_loader_set_priority(ImageLoader *il, gint priority);

gint image_loader_start(ImageLoader *il, void (*func_done)(ImageLoader *, gpointer), gpointer data_done);


GdkPixbuf *image_loader_get_pixbuf(ImageLoader *il);
gchar *image_loader_get_format(ImageLoader *il);
gdouble image_loader_get_percent(ImageLoader *il);
gint image_loader_get_is_done(ImageLoader *il);

gint image_load_dimensions(const gchar *path, gint *width, gint *height);

#endif

