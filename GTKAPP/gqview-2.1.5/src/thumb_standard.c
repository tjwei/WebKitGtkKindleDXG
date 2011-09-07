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
#include "thumb_standard.h"

#include "cache.h"	/* for cache_ensure_dir_exists */
#include "image-load.h"
#include "md5-util.h"
#include "pixbuf_util.h"
#include "ui_fileops.h"


/*
 * This thumbnail caching implementation attempts to conform
 * to the Thumbnail Managing Standard proposed on freedesktop.org
 * The standard is documented here:
 *   http://triq.net/~jens/thumbnail-spec/index.html
 *  (why isn't it actually hosted on freedesktop.org?)
 *
 * This code attempts to conform to version 0.7.0 of the standard.
 *
 * Notes:
 *   > Validation of the thumb's embedded uri is a simple strcmp between our
 *     version of the escaped uri and the thumb's escaped uri. But not all uri
 *     escape functions escape the same set of chars, comparing the unescaped
 *     versions may be more accurate.
 *   > Only Thumb::URI and Thumb::MTime are stored in a thumb at this time.
 *     Storing the Size, Width, Height should probably be implemented.
 */


#define THUMB_SIZE_NORMAL 128
#define THUMB_SIZE_LARGE  256

#define THUMB_MARKER_URI    "tEXt::Thumb::URI"
#define THUMB_MARKER_MTIME  "tEXt::Thumb::MTime"
#define THUMB_MARKER_SIZE   "tEXt::Thumb::Size"
#define THUMB_MARKER_WIDTH  "tEXt::Thumb::Image::Width"
#define THUMB_MARKER_HEIGHT "tEXt::Thumb::Image::Height"
#define THUMB_MARKER_APP    "tEXt::Software"

#define THUMB_PERMS_FOLDER 0700
#define THUMB_PERMS_THUMB  0600



/*
 *-----------------------------------------------------------------------------
 * thumbnail loader
 *-----------------------------------------------------------------------------
 */


static void thumb_loader_std_error_cb(ImageLoader *il, gpointer data);
static gint thumb_loader_std_setup(ThumbLoaderStd *tl, const gchar *path);


ThumbLoaderStd *thumb_loader_std_new(gint width, gint height)
{
	ThumbLoaderStd *tl;

	tl = g_new0(ThumbLoaderStd, 1);

	tl->standard_loader = TRUE;

	tl->requested_width = width;
	tl->requested_height = height;

	tl->pixbuf = NULL;
	tl->il = NULL;
	tl->source_path = NULL;

	tl->cache_enable = enable_thumb_caching;
	tl->cache_local = FALSE;
	tl->cache_retry = FALSE;

	return tl;
}

void thumb_loader_std_set_callbacks(ThumbLoaderStd *tl,
				    ThumbLoaderStdFunc func_done,
				    ThumbLoaderStdFunc func_error,
				    ThumbLoaderStdFunc func_progress,
				    gpointer data)
{
	if (!tl) return;

	tl->func_done = func_done;
	tl->func_error = func_error;
	tl->func_progress = func_progress;
	tl->data = data;
}

static void thumb_loader_std_reset(ThumbLoaderStd *tl)
{
	if (tl->pixbuf) g_object_unref(tl->pixbuf);
	tl->pixbuf = NULL;

	image_loader_free(tl->il);
	tl->il = NULL;

	g_free(tl->source_path);
	tl->source_path = NULL;

	g_free(tl->thumb_path);
	tl->thumb_path = NULL;

	g_free(tl->thumb_uri);
	tl->thumb_uri = NULL;
	tl->local_uri = NULL;

	tl->thumb_path_local = FALSE;

	tl->cache_hit = FALSE;

	tl->source_mtime = 0;
	tl->source_size = 0;
	tl->source_mode = 0;

	tl->progress = 0.0;
}

static gchar *thumb_std_cache_path(const gchar *path, const gchar *uri, gint local,
				   const gchar *cache_subfolder)
{
	gchar *result = NULL;
	gchar *cache_base;
	gchar *md5_text;
	guchar digest[16];

	if (!path || !uri || !cache_subfolder) return NULL;

	if (local)
		{
		gchar *base;

		base = remove_level_from_path(path);
		cache_base = g_strconcat(base, "/", THUMB_FOLDER_LOCAL, "/", cache_subfolder, NULL);
		g_free(base);
		}
	else
		{
		cache_base = g_strconcat(homedir(), "/", THUMB_FOLDER_GLOBAL, "/", cache_subfolder, NULL);
		}

	md5_get_digest((guchar *)uri, strlen(uri), digest);
	md5_text = md5_digest_to_text(digest);

	if (cache_base && md5_text)
		{
		result = g_strconcat(cache_base, "/", md5_text, THUMB_NAME_EXTENSION, NULL);
		}

	g_free(cache_base);
	g_free(md5_text);

	return result;
}

static gchar *thumb_loader_std_cache_path(ThumbLoaderStd *tl, gint local, GdkPixbuf *pixbuf, gint fail)
{
	const gchar *folder_size;
	gint w, h;

	if (!tl->source_path || !tl->thumb_uri) return NULL;

	if (pixbuf)
		{
		w = gdk_pixbuf_get_width(pixbuf);
		h = gdk_pixbuf_get_height(pixbuf);
		}
	else
		{
		w = tl->requested_width;
		h = tl->requested_height;
		}

	if (fail)
		{
		folder_size = THUMB_FOLDER_FAIL;
		}
	else if (w > THUMB_SIZE_NORMAL || h > THUMB_SIZE_NORMAL)
		{
		folder_size = THUMB_FOLDER_LARGE;
		}
	else
		{
		folder_size = THUMB_FOLDER_NORMAL;
		}

	return thumb_std_cache_path(tl->source_path,
				    (local) ?  tl->local_uri : tl->thumb_uri,
				    local, folder_size);
}

static gint thumb_loader_std_fail_check(ThumbLoaderStd *tl)
{
	gchar *fail_path;
	gint result = FALSE;

	fail_path = thumb_loader_std_cache_path(tl, FALSE, NULL, TRUE);
	if (isfile(fail_path))
		{
		GdkPixbuf *pixbuf;

		if (tl->cache_retry)
			{
			pixbuf = NULL;
			}
		else
			{
			gchar *pathl;

			pathl = path_from_utf8(fail_path);
			pixbuf = gdk_pixbuf_new_from_file(pathl, NULL);
			g_free(pathl);
			}

		if (pixbuf)
			{
			const gchar *mtime_str;

			mtime_str = gdk_pixbuf_get_option(pixbuf, THUMB_MARKER_MTIME);
			if (mtime_str && strtol(mtime_str, NULL, 10) == tl->source_mtime)
				{
				result = TRUE;
				if (debug)
					{
					printf("thumb fail valid: %s\n", tl->source_path);
					printf("           thumb: %s\n", fail_path);
					}
				}

			g_object_unref(G_OBJECT(pixbuf));
			}

		if (!result) unlink_file(fail_path);
		}
	g_free(fail_path);

	return result;
}

static gint thumb_loader_std_validate(ThumbLoaderStd *tl, GdkPixbuf *pixbuf)
{
	const gchar *valid_uri;
	const gchar *uri;
	const gchar *mtime_str;
	time_t mtime;
	gint w, h;

	if (!pixbuf) return FALSE;

	w = gdk_pixbuf_get_width(pixbuf);
	h = gdk_pixbuf_get_height(pixbuf);

	if (w != THUMB_SIZE_NORMAL && w != THUMB_SIZE_LARGE &&
	    h != THUMB_SIZE_NORMAL && h != THUMB_SIZE_LARGE) return FALSE;

	valid_uri = (tl->thumb_path_local) ? tl->local_uri : tl->thumb_uri;

	uri = gdk_pixbuf_get_option(pixbuf, THUMB_MARKER_URI);
	mtime_str = gdk_pixbuf_get_option(pixbuf, THUMB_MARKER_MTIME);

	if (!mtime_str || !uri || !valid_uri) return FALSE;
	if (strcmp(uri, valid_uri) != 0) return FALSE;

	mtime = strtol(mtime_str, NULL, 10);
	if (tl->source_mtime != mtime) return FALSE;

	return TRUE;
}

static void thumb_loader_std_save(ThumbLoaderStd *tl, GdkPixbuf *pixbuf)
{
	gchar *base_path;
	gchar *tmp_path;
	gint fail;

	if (!tl->cache_enable || tl->cache_hit) return;
	if (tl->thumb_path) return;

	if (!pixbuf)
		{
		/* local failures are not stored */
		if (tl->cache_local) return;

		pixbuf = gdk_pixbuf_new (GDK_COLORSPACE_RGB, TRUE, 8, 1, 1);
		fail = TRUE;
		}
	else
		{
		g_object_ref(G_OBJECT(pixbuf));
		fail = FALSE;
		}

	tl->thumb_path = thumb_loader_std_cache_path(tl, tl->cache_local, pixbuf, fail);
	if (!tl->thumb_path)
		{
		g_object_unref(G_OBJECT(pixbuf));
		return;
		}
	tl->thumb_path_local = tl->cache_local;

	/* create thumbnail dir if needed */
	base_path = remove_level_from_path(tl->thumb_path);
	if (tl->cache_local)
		{
		if (!isdir(base_path))
			{
			struct stat st;
			gchar *source_base;

			source_base = remove_level_from_path(tl->source_path);
			if (stat_utf8(source_base, &st))
				{
				cache_ensure_dir_exists(base_path, st.st_mode);
				}
			g_free(source_base);
			}
		}
	else
		{
		cache_ensure_dir_exists(base_path, THUMB_PERMS_FOLDER);
		}
	g_free(base_path);

	if (debug)
		{
		printf("thumb saving: %s\n", tl->source_path);
		printf("       saved: %s\n", tl->thumb_path);
		}

	/* save thumb, using a temp file then renaming into place */
	tmp_path = unique_filename(tl->thumb_path, ".tmp", "_", 2);
	if (tmp_path)
		{
		const gchar *mark_uri;
		gchar *mark_app;
		gchar *mark_mtime;
		gchar *pathl;
		gint success;

		mark_uri = (tl->cache_local) ? tl->local_uri :tl->thumb_uri;

		mark_app = g_strdup_printf("GQview %s", VERSION);
		mark_mtime = g_strdup_printf("%lu", tl->source_mtime);

		pathl = path_from_utf8(tmp_path);
		success = gdk_pixbuf_save(pixbuf, pathl, "png", NULL,
					  THUMB_MARKER_URI, mark_uri,
					  THUMB_MARKER_MTIME, mark_mtime,
					  THUMB_MARKER_APP, mark_app,
					  NULL);
		if (success)
			{
			chmod(pathl, (tl->cache_local) ? tl->source_mode : THUMB_PERMS_THUMB);
			success = rename_file(tmp_path, tl->thumb_path);
			}

		g_free(pathl);

		g_free(mark_mtime);
		g_free(mark_app);

		g_free(tmp_path);
		if (!success && debug)
			{
			printf("thumb save failed: %s\n", tl->source_path);
			printf("            thumb: %s\n", tl->thumb_path);
			}

		}

	g_object_unref(G_OBJECT(pixbuf));
}

static gint thumb_loader_std_scale_aspect(gint req_w, gint req_h, gint old_w, gint old_h,
					  gint *new_w, gint *new_h)
{
	if (((gdouble)req_w / old_w) < ((gdouble)req_h / old_h))
		{
		*new_w = req_w;
		*new_h = (gdouble)*new_w / old_w * old_h;
		if (*new_h < 1) *new_h = 1;
		}
	else
		{
		*new_h = req_h;
		*new_w = (gdouble)*new_h / old_h * old_w;
		if (*new_w < 1) *new_w = 1;
		}

	return (*new_w != old_w || *new_h != old_h);
}

static GdkPixbuf *thumb_loader_std_finish(ThumbLoaderStd *tl, GdkPixbuf *pixbuf, gint shrunk)
{
	GdkPixbuf *pixbuf_thumb = NULL;
	GdkPixbuf *result;
	gint sw, sh;

	sw = gdk_pixbuf_get_width(pixbuf);
	sh = gdk_pixbuf_get_height(pixbuf);

	if (tl->cache_enable)
		{
		if (!tl->cache_hit)
			{
			gint cache_w, cache_h;

			if (tl->requested_width > THUMB_SIZE_NORMAL || tl->requested_height > THUMB_SIZE_NORMAL)
				{
				cache_w = cache_h = THUMB_SIZE_LARGE;
				}
			else
				{
				cache_w = cache_h = THUMB_SIZE_NORMAL;
				}

			if (sw > cache_w || sh > cache_h || shrunk)
				{
				gint thumb_w, thumb_h;

				if (thumb_loader_std_scale_aspect(cache_w, cache_h, sw, sh,
								  &thumb_w, &thumb_h))
					{
					pixbuf_thumb = gdk_pixbuf_scale_simple(pixbuf, thumb_w, thumb_h,
									       (GdkInterpType)thumbnail_quality);
					}
				else
					{
					pixbuf_thumb = pixbuf;
					g_object_ref(G_OBJECT(pixbuf_thumb));
					}

				thumb_loader_std_save(tl, pixbuf_thumb);
				}
			}
		else if (tl->cache_hit &&
			 tl->cache_local && !tl->thumb_path_local)
			{
			/* A local cache save was requested, but a valid thumb is in $HOME,
			 * so specifically save as a local thumbnail.
			 */
			g_free(tl->thumb_path);
			tl->thumb_path = NULL;

			tl->cache_hit = FALSE;

			if (debug) printf("thumb copied: %s\n", tl->source_path);

			thumb_loader_std_save(tl, pixbuf);
			}
		}

	if (sw <= tl->requested_width && sh <= tl->requested_height)
		{
		result = pixbuf;
		g_object_ref(result);
		}
	else
		{
		gint thumb_w, thumb_h;

		if (pixbuf_thumb)
			{
			pixbuf = pixbuf_thumb;
			sw = gdk_pixbuf_get_width(pixbuf);
			sh = gdk_pixbuf_get_height(pixbuf);
			}

		if (thumb_loader_std_scale_aspect(tl->requested_width, tl->requested_height, sw, sh,
						  &thumb_w, &thumb_h))
			{
			result = gdk_pixbuf_scale_simple(pixbuf, thumb_w, thumb_h,
							 (GdkInterpType)thumbnail_quality);
			}
		else
			{
			result = pixbuf;
			g_object_ref(result);
			}
		}

	if (pixbuf_thumb) g_object_unref(pixbuf_thumb);

	return result;
}

static gint thumb_loader_std_next_source(ThumbLoaderStd *tl, gint remove_broken)
{
	image_loader_free(tl->il);
	tl->il = NULL;

	if (tl->thumb_path)
		{
		if (!tl->thumb_path_local && remove_broken)
			{
			if (debug) printf("thumb broken, unlinking: %s\n", tl->thumb_path);
			unlink_file(tl->thumb_path);
			}

		g_free(tl->thumb_path);
		tl->thumb_path = NULL;

		if (!tl->thumb_path_local)
			{
			tl->thumb_path = thumb_loader_std_cache_path(tl, TRUE, NULL, FALSE);
			if (isfile(tl->thumb_path) && thumb_loader_std_setup(tl, tl->thumb_path))
				{
				tl->thumb_path_local = TRUE;
				return TRUE;
				}

			g_free(tl->thumb_path);
			tl->thumb_path = NULL;
			}

		if (thumb_loader_std_setup(tl, tl->source_path)) return TRUE;
		}

	thumb_loader_std_save(tl, NULL);
	return FALSE;
}

static void thumb_loader_std_done_cb(ImageLoader *il, gpointer data)
{
	ThumbLoaderStd *tl = data;
	GdkPixbuf *pixbuf;

	if (debug)
		{
		printf("thumb image done: %s\n", tl->source_path);
		printf("            from: %s\n", tl->il->path);
		}

	pixbuf = image_loader_get_pixbuf(tl->il);
	if (!pixbuf)
		{
		if (debug) printf("...but no pixbuf\n");
		thumb_loader_std_error_cb(il, data);
		return;
		}

	if (tl->thumb_path && !thumb_loader_std_validate(tl, pixbuf))
		{
		if (thumb_loader_std_next_source(tl, TRUE)) return;

		if (tl->func_error) tl->func_error(tl, tl->data);
		return;
		}

	tl->cache_hit = (tl->thumb_path != NULL);

	tl->pixbuf = thumb_loader_std_finish(tl, pixbuf, il->shrunk);

	if (tl->func_done) tl->func_done(tl, tl->data);
}

static void thumb_loader_std_error_cb(ImageLoader *il, gpointer data)
{
	ThumbLoaderStd *tl = data;

	/* if at least some of the image is available, go to done */
	if (image_loader_get_pixbuf(tl->il) != NULL)
		{
		thumb_loader_std_done_cb(il, data);
		return;
		}

	if (debug)
		{
		printf("thumb image error: %s\n", tl->source_path);
		printf("             from: %s\n", tl->il->path);
		}

	if (thumb_loader_std_next_source(tl, TRUE)) return;

	if (tl->func_error) tl->func_error(tl, tl->data);
}

static void thumb_loader_std_progress_cb(ImageLoader *il, gdouble percent, gpointer data)
{
	ThumbLoaderStd *tl = data;

	tl->progress = (gdouble)percent;

	if (tl->func_progress) tl->func_progress(tl, tl->data);
}

static gint thumb_loader_std_setup(ThumbLoaderStd *tl, const gchar *path)
{
	tl->il = image_loader_new(path);

	if (thumbnail_fast)
		{
		/* this will speed up jpegs by up to 3x in some cases */
		if (tl->requested_width <= THUMB_SIZE_NORMAL &&
		    tl->requested_height <= THUMB_SIZE_NORMAL)
			{
			image_loader_set_requested_size(tl->il, THUMB_SIZE_NORMAL, THUMB_SIZE_NORMAL);
			}
		else
			{
			image_loader_set_requested_size(tl->il, THUMB_SIZE_LARGE, THUMB_SIZE_LARGE);
			}
		}

	image_loader_set_error_func(tl->il, thumb_loader_std_error_cb, tl);
	if (tl->func_progress)
		{
		image_loader_set_percent_func(tl->il, thumb_loader_std_progress_cb, tl);
		}

	if (image_loader_start(tl->il, thumb_loader_std_done_cb, tl))
		{
		return TRUE;
		}

	image_loader_free(tl->il);
	tl->il = NULL;
	return FALSE;
}

/*
 * Note: Currently local_cache only specifies where to save a _new_ thumb, if
 *       a valid existing thumb is found anywhere the local thumb will not be created.
 */
void thumb_loader_std_set_cache(ThumbLoaderStd *tl, gint enable_cache, gint local, gint retry_failed)
{
	if (!tl) return;

	tl->cache_enable = enable_cache;
	tl->cache_local = local;
	tl->cache_retry = retry_failed;
}

gint thumb_loader_std_start(ThumbLoaderStd *tl, const gchar *path)
{
	static gchar *thumb_cache = NULL;
	struct stat st;

	if (!tl || !path) return FALSE;

	thumb_loader_std_reset(tl);

	if (!stat_utf8(path, &st)) return FALSE;

	tl->source_path = g_strdup(path);
	tl->source_mtime = st.st_mtime;
	tl->source_size = st.st_size;
	tl->source_mode = st.st_mode;

	if (!thumb_cache) thumb_cache = g_strconcat(homedir(), "/", THUMB_FOLDER_GLOBAL, NULL);
	if (strncmp(tl->source_path, thumb_cache, strlen(thumb_cache)) != 0)
		{
		gchar *pathl;

		pathl = path_from_utf8(path);
		tl->thumb_uri = g_filename_to_uri(pathl, NULL, NULL);
		tl->local_uri = filename_from_path(tl->thumb_uri);
		g_free(pathl);
		}

	if (tl->cache_enable)
		{
		gint found;

		tl->thumb_path = thumb_loader_std_cache_path(tl, FALSE, NULL, FALSE);
		tl->thumb_path_local = FALSE;

		found = isfile(tl->thumb_path);
		if (found && thumb_loader_std_setup(tl, tl->thumb_path)) return TRUE;

		if (thumb_loader_std_fail_check(tl)) return FALSE;

		return thumb_loader_std_next_source(tl, found);
		}

	if (!thumb_loader_std_setup(tl, tl->source_path))
		{
		thumb_loader_std_save(tl, NULL);
		return FALSE;
		}

	return TRUE;
}

void thumb_loader_std_free(ThumbLoaderStd *tl)
{
	if (!tl) return;

	thumb_loader_std_reset(tl);
	g_free(tl);
}

GdkPixbuf *thumb_loader_std_get_pixbuf(ThumbLoaderStd *tl, gint with_fallback)
{
	GdkPixbuf *pixbuf;

	if (tl && tl->pixbuf)
		{
		pixbuf = tl->pixbuf;
		g_object_ref(pixbuf);
		}
	else if (with_fallback)
		{
		gint w, h;

		pixbuf = pixbuf_inline(PIXBUF_INLINE_BROKEN);
		w = gdk_pixbuf_get_width(pixbuf);
		h = gdk_pixbuf_get_height(pixbuf);

		if (w > tl->requested_width || h > tl->requested_height)
			{
			gint nw, nh;

			if (thumb_loader_std_scale_aspect(tl->requested_width, tl->requested_height,
							  w, h, &nw, &nh))
				{
				GdkPixbuf *tmp;

				tmp = pixbuf;
				pixbuf = gdk_pixbuf_scale_simple(tmp, nw, nh, GDK_INTERP_TILES);
				g_object_unref(G_OBJECT(tmp));
				}
			}
		}
	else
		{
		pixbuf = NULL;
		}

	return pixbuf;
}


typedef struct _ThumbValidate ThumbValidate;
struct _ThumbValidate
{
	ThumbLoaderStd *tl;
	gchar *path;
	gint days;

	void (*func_valid)(const gchar *path, gint valid, gpointer data);
	gpointer data;

	gint idle_id;
};

static void thumb_loader_std_thumb_file_validate_free(ThumbValidate *tv)
{
	thumb_loader_std_free(tv->tl);
	g_free(tv->path);
	g_free(tv);
}

void thumb_loader_std_thumb_file_validate_cancel(ThumbLoaderStd *tl)
{
	ThumbValidate *tv;

	if (!tl) return;

	tv = tl->data;

	if (tv->idle_id != -1) g_source_remove(tv->idle_id);
	tv->idle_id = -1;

	thumb_loader_std_thumb_file_validate_free(tv);
}

static void thumb_loader_std_thumb_file_validate_finish(ThumbValidate *tv, gint valid)
{
	if (tv->func_valid) tv->func_valid(tv->path, valid, tv->data);

	thumb_loader_std_thumb_file_validate_free(tv);
}

static void thumb_loader_std_thumb_file_validate_done_cb(ThumbLoaderStd *tl, gpointer data)
{
	ThumbValidate *tv = data;
	GdkPixbuf *pixbuf;
	gint valid = FALSE;

	pixbuf = thumb_loader_std_get_pixbuf(tv->tl, FALSE);
	if (pixbuf)
		{
		const gchar *uri;
		const gchar *mtime_str;

		uri = gdk_pixbuf_get_option(pixbuf, THUMB_MARKER_URI);
		mtime_str = gdk_pixbuf_get_option(pixbuf, THUMB_MARKER_MTIME);
		if (uri && mtime_str)
			{
			if (strncmp(uri, "file:", strlen("file:")) == 0)
				{
				struct stat st;
				gchar *target;

				target = g_filename_from_uri(uri, NULL, NULL);
				if (stat(target, &st) == 0 &&
				    st.st_mtime == strtol(mtime_str, NULL, 10))
					{
					valid = TRUE;
					}
				g_free(target);
				}
			else
				{
				struct stat st;

				if (debug) printf("thumb uri foreign, doing day check: %s\n", uri);

				if (stat_utf8(tv->path, &st))
					{
					time_t now;

					now = time(NULL);
					if (st.st_atime >= now - (time_t)tv->days * 24 * 60 * 60)
						{
						valid = TRUE;
						}
					}
				}
			}

		g_object_unref(pixbuf);
		}

	thumb_loader_std_thumb_file_validate_finish(tv, valid);
}

static void thumb_loader_std_thumb_file_validate_error_cb(ThumbLoaderStd *tl, gpointer data)
{
	ThumbValidate *tv = data;

	thumb_loader_std_thumb_file_validate_finish(tv, FALSE);
}

static gint thumb_loader_std_thumb_file_validate_idle_cb(gpointer data)
{
	ThumbValidate *tv = data;

	tv->idle_id = -1;
	thumb_loader_std_thumb_file_validate_finish(tv, FALSE);

	return FALSE;
}

ThumbLoaderStd *thumb_loader_std_thumb_file_validate(const gchar *thumb_path, gint allowed_days,
						     void (*func_valid)(const gchar *path, gint valid, gpointer data),
						     gpointer data)
{
	ThumbValidate *tv;

	tv = g_new0(ThumbValidate, 1);

	tv->tl = thumb_loader_std_new(THUMB_SIZE_LARGE, THUMB_SIZE_LARGE);
	thumb_loader_std_set_callbacks(tv->tl,
				       thumb_loader_std_thumb_file_validate_done_cb,
				       thumb_loader_std_thumb_file_validate_error_cb,
				       NULL,
				       tv);
	thumb_loader_std_reset(tv->tl);

	tv->path = g_strdup(thumb_path);
	tv->days = allowed_days;
	tv->func_valid = func_valid;
	tv->data = data;

	if (!thumb_loader_std_setup(tv->tl, thumb_path))
		{
		tv->idle_id = g_idle_add(thumb_loader_std_thumb_file_validate_idle_cb, tv);
		}
	else
		{
		tv->idle_id = -1;
		}

	return tv->tl;
}

static void thumb_std_maint_remove_one(const gchar *source, const gchar *uri, gint local,
				       const gchar *subfolder)
{
	gchar *thumb_path;

	thumb_path = thumb_std_cache_path(source,
					  (local) ? filename_from_path(uri) : uri,
					  local, subfolder);
	if (isfile(thumb_path))
		{
		if (debug) printf("thumb removing: %s\n", thumb_path);
		unlink_file(thumb_path);
		}
	g_free(thumb_path);
}

/* this also removes local thumbnails (the source is gone so it makes sense) */
void thumb_std_maint_removed(const gchar *source)
{
	gchar *uri;
	gchar *sourcel;

	sourcel = path_from_utf8(source);
	uri = g_filename_to_uri(sourcel, NULL, NULL);
	g_free(sourcel);

	/* all this to remove a thumbnail? */

	thumb_std_maint_remove_one(source, uri, FALSE, THUMB_FOLDER_NORMAL);
	thumb_std_maint_remove_one(source, uri, FALSE, THUMB_FOLDER_LARGE);
	thumb_std_maint_remove_one(source, uri, FALSE, THUMB_FOLDER_FAIL);
	thumb_std_maint_remove_one(source, uri, TRUE, THUMB_FOLDER_NORMAL);
	thumb_std_maint_remove_one(source, uri, TRUE, THUMB_FOLDER_LARGE);

	g_free(uri);
}

typedef struct _TMaintMove TMaintMove;
struct _TMaintMove
{
	gchar *source;
	gchar *dest;

	ThumbLoaderStd *tl;
	gchar *source_uri;
	gchar *thumb_path;

	gint pass;
};

static GList *thumb_std_maint_move_list = NULL;
static GList *thumb_std_maint_move_tail = NULL;


static void thumb_std_maint_move_step(TMaintMove *tm);
static gint thumb_std_maint_move_idle(gpointer data);


static void thumb_std_maint_move_validate_cb(const gchar *path, gint valid, gpointer data)
{
	TMaintMove *tm = data;
	GdkPixbuf *pixbuf;

	pixbuf = thumb_loader_std_get_pixbuf(tm->tl, FALSE);
	if (pixbuf)
		{
		const gchar *uri;
		const gchar *mtime_str;

		uri = gdk_pixbuf_get_option(pixbuf, THUMB_MARKER_URI);
		mtime_str = gdk_pixbuf_get_option(pixbuf, THUMB_MARKER_MTIME);

		if (uri && mtime_str && strcmp(uri, tm->source_uri) == 0)
			{
			gchar *pathl;

			/* The validation utility abuses ThumbLoader, and we
			 * abuse the utility just to load the thumbnail,
			 * but the loader needs to look sane for the save to complete.
			 */

			tm->tl->cache_enable = TRUE;
			tm->tl->cache_hit = FALSE;
			tm->tl->cache_local = FALSE;

			g_free(tm->tl->source_path);
			tm->tl->source_path = g_strdup(tm->dest);
			tm->tl->source_mtime = strtol(mtime_str, NULL, 10);

			pathl = path_from_utf8(tm->tl->source_path);
			g_free(tm->tl->thumb_uri);
			tm->tl->thumb_uri = g_filename_to_uri(pathl, NULL, NULL);
			tm->tl->local_uri = filename_from_path(tm->tl->thumb_uri);
			g_free(pathl);

			g_free(tm->tl->thumb_path);
			tm->tl->thumb_path = NULL;
			tm->tl->thumb_path_local = FALSE;

			if (debug) printf("thumb move attempting save:\n");

			thumb_loader_std_save(tm->tl, pixbuf);
			}

		if (debug) printf("thumb move unlink: %s\n", tm->thumb_path);
		unlink_file(tm->thumb_path);
		}

	thumb_std_maint_move_step(tm);
}

static void thumb_std_maint_move_step(TMaintMove *tm)
{
	const gchar *folder;

	tm->pass++;
	if (tm->pass > 2)
		{
		g_free(tm->source);
		g_free(tm->dest);
		g_free(tm->source_uri);
		g_free(tm->thumb_path);
		g_free(tm);

		if (thumb_std_maint_move_list)
			{
			g_idle_add_full(G_PRIORITY_LOW, thumb_std_maint_move_idle, NULL, NULL);
			}

		return;
		}

	folder = (tm->pass == 1) ? THUMB_FOLDER_NORMAL : THUMB_FOLDER_LARGE;
	
	g_free(tm->thumb_path);
	tm->thumb_path = thumb_std_cache_path(tm->source, tm->source_uri, FALSE, folder);
	tm->tl = thumb_loader_std_thumb_file_validate(tm->thumb_path, 0,
						      thumb_std_maint_move_validate_cb, tm);
}

static gint thumb_std_maint_move_idle(gpointer data)
{
	TMaintMove *tm;
	gchar *pathl;

	if (!thumb_std_maint_move_list) return FALSE;

	tm = thumb_std_maint_move_list->data;

	thumb_std_maint_move_list = g_list_remove(thumb_std_maint_move_list, tm);
	if (!thumb_std_maint_move_list) thumb_std_maint_move_tail = NULL;

	pathl = path_from_utf8(tm->source);
	tm->source_uri = g_filename_to_uri(pathl, NULL, NULL);
	g_free(pathl);

	tm->pass = 0;

	thumb_std_maint_move_step(tm);

	return FALSE;
}

/* This will schedule a move of the thumbnail for source image to dest when idle.
 * We do this so that file renaming or moving speed is not sacrificed by
 * moving the thumbnails at the same time because:
 *
 * This cache design requires the tedious task of loading the png thumbnails and saving them.
 *
 * The thumbnails are processed when the app is idle. If the app
 * exits early well too bad - they can simply be regenerated from scratch.
 *
 * This does not manage local thumbnails (fixme ?)
 */
void thumb_std_maint_moved(const gchar *source, const gchar *dest)
{
	TMaintMove *tm;

	tm = g_new0(TMaintMove, 1);
	tm->source = g_strdup(source);
	tm->dest = g_strdup(dest);

	if (!thumb_std_maint_move_list)
		{
		g_idle_add_full(G_PRIORITY_LOW, thumb_std_maint_move_idle, NULL, NULL);
		}

	if (thumb_std_maint_move_tail)
		{
		thumb_std_maint_move_tail = g_list_append(thumb_std_maint_move_tail, tm);
		thumb_std_maint_move_tail = thumb_std_maint_move_tail->next;
		}
	else
		{
		thumb_std_maint_move_list = g_list_append(thumb_std_maint_move_list, tm);
		thumb_std_maint_move_tail = thumb_std_maint_move_list;
		}
}


