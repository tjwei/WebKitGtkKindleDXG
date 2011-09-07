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


#ifndef THUMB_STANDARD_H
#define THUMB_STANDARD_H


#define THUMB_FOLDER_GLOBAL ".thumbnails"
#define THUMB_FOLDER_LOCAL  ".thumblocal"
#define THUMB_FOLDER_NORMAL "normal"
#define THUMB_FOLDER_LARGE  "large"
#define THUMB_FOLDER_FAIL   "fail/gqview-1.0"
#define THUMB_NAME_EXTENSION ".png"


typedef struct _ThumbLoaderStd ThumbLoaderStd;
typedef void (* ThumbLoaderStdFunc)(ThumbLoaderStd *tl, gpointer data);

struct _ThumbLoaderStd
{
	gint standard_loader;

	GdkPixbuf *pixbuf;
	ImageLoader *il;

	gchar *source_path;

	time_t source_mtime;
	off_t source_size;
	mode_t source_mode;

	gchar *thumb_path;
	gchar *thumb_uri;
	const gchar *local_uri;

	gint thumb_path_local;

	gint requested_width;
	gint requested_height;

	gint cache_enable;
	gint cache_local;
	gint cache_hit;
	gint cache_retry;

	gdouble progress;

	ThumbLoaderStdFunc func_done;
	ThumbLoaderStdFunc func_error;
	ThumbLoaderStdFunc func_progress;

	gpointer data;
};


ThumbLoaderStd *thumb_loader_std_new(gint width, gint height);
void thumb_loader_std_set_callbacks(ThumbLoaderStd *tl,
				    ThumbLoaderStdFunc func_done,
				    ThumbLoaderStdFunc func_error,
				    ThumbLoaderStdFunc func_progress,
				    gpointer data);
void thumb_loader_std_set_cache(ThumbLoaderStd *tl, gint enable_cache, gint local, gint retry_failed);
gint thumb_loader_std_start(ThumbLoaderStd *tl, const gchar *path);
void thumb_loader_std_free(ThumbLoaderStd *tl);

GdkPixbuf *thumb_loader_std_get_pixbuf(ThumbLoaderStd *tl, gint with_fallback);


/* validates a non local thumbnail file,
 * calling func_valid with the information when app is idle
 * for thumbnail's without a file: uri, validates against allowed_age in days
 */
ThumbLoaderStd *thumb_loader_std_thumb_file_validate(const gchar *thumb_path, gint allowed_age,
						     void (*func_valid)(const gchar *path, gint valid, gpointer data),
						     gpointer data);
void thumb_loader_std_thumb_file_validate_cancel(ThumbLoaderStd *tl);


void thumb_std_maint_removed(const gchar *source);
void thumb_std_maint_moved(const gchar *source, const gchar *dest);


#endif
