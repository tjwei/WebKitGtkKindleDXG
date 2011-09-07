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


#ifndef THUMB_H
#define THUMB_H


ThumbLoader *thumb_loader_new(gint width, gint height);
void thumb_loader_set_callbacks(ThumbLoader *tl,
				ThumbLoaderFunc func_done,
				ThumbLoaderFunc func_error,
				ThumbLoaderFunc func_progress,
				gpointer data);
void thumb_loader_set_cache(ThumbLoader *tl, gint enable_cache, gint local, gint retry_failed);

gint thumb_loader_start(ThumbLoader *tl, const gchar *path);
void thumb_loader_free(ThumbLoader *tl);

GdkPixbuf *thumb_loader_get_pixbuf(ThumbLoader *tl, gint with_fallback);


#endif
