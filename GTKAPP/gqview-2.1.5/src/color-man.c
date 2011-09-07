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
#include "color-man.h"

#include "image.h"
#include "ui_fileops.h"


#ifdef HAVE_LCMS
/*** color support enabled ***/

#ifdef HAVE_LCMS_LCMS_H
  #include <lcms/lcms.h>
#else
  #include <lcms.h>
#endif


typedef struct _ColorManCache ColorManCache;
struct _ColorManCache {
	cmsHPROFILE   profile_in;
	cmsHPROFILE   profile_out;
	cmsHTRANSFORM transform;

	ColorManProfileType profile_in_type;
	gchar *profile_in_file;

	ColorManProfileType profile_out_type;
	gchar *profile_out_file;

	gint has_alpha;

	gint refcount;
};

/* pixels to transform per idle call */
#define COLOR_MAN_CHUNK_SIZE 81900


static void color_man_lib_init(void)
{
	static gint init_done = FALSE;

	if (init_done) return;
	init_done = TRUE;

	cmsErrorAction(LCMS_ERROR_IGNORE);
}


/*
 *-------------------------------------------------------------------
 * color transform cache
 *-------------------------------------------------------------------
 */

static GList *cm_cache_list = NULL;


static void color_man_cache_ref(ColorManCache *cc)
{
	if (!cc) return;

	cc->refcount++;
}

static void color_man_cache_unref(ColorManCache *cc)
{
	if (!cc) return;

	cc->refcount--;
	if (cc->refcount < 1)
		{
		if (cc->transform) cmsDeleteTransform(cc->transform);
		if (cc->profile_in) cmsCloseProfile(cc->profile_in);
		if (cc->profile_out) cmsCloseProfile(cc->profile_out);

		g_free(cc->profile_in_file);
		g_free(cc->profile_out_file);

		g_free(cc);
		}
}

static cmsHPROFILE color_man_cache_load_profile(ColorManProfileType type, const gchar *file,
						unsigned char *data, guint data_len)
{
	cmsHPROFILE profile = NULL;

	switch (type)
		{
		case COLOR_PROFILE_FILE:
			if (file)
				{
				gchar *pathl;

				pathl = path_from_utf8(file);
				profile = cmsOpenProfileFromFile(pathl, "r");
				g_free(pathl);
				}
			break;
		case COLOR_PROFILE_SRGB:
			profile = cmsCreate_sRGBProfile();
			break;
		case COLOR_PROFILE_MEM:
			if (data)
				{
				profile = cmsOpenProfileFromMem(data, data_len);
				}
			break;
		case COLOR_PROFILE_NONE:
		default:
			break;
		}

	return profile;
}

static ColorManCache *color_man_cache_new(ColorManProfileType in_type, const gchar *in_file,
					  unsigned char *in_data, guint in_data_len,
					  ColorManProfileType out_type, const gchar *out_file,
					  gint has_alpha)
{
	ColorManCache *cc;

	color_man_lib_init();

	cc = g_new0(ColorManCache, 1);
	cc->refcount = 1;

	cc->profile_in_type = in_type;
	cc->profile_in_file = g_strdup(in_file);

	cc->profile_out_type = out_type;
	cc->profile_out_file = g_strdup(out_file);

	cc->has_alpha = has_alpha;

	cc->profile_in = color_man_cache_load_profile(cc->profile_in_type, cc->profile_in_file,
						      in_data, in_data_len);
	cc->profile_out = color_man_cache_load_profile(cc->profile_out_type, cc->profile_out_file,
						       NULL, 0);

	if (!cc->profile_in || !cc->profile_out)
		{
		if (debug) printf("failed to load color profile for %s: %d %s\n",
				  (!cc->profile_in) ? "input" : "screen",
				  (!cc->profile_in) ? cc->profile_in_type : cc->profile_out_type,
				  (!cc->profile_in) ? cc->profile_in_file : cc->profile_out_file);

		color_man_cache_unref(cc);
		return NULL;
		}

	cc->transform = cmsCreateTransform(cc->profile_in,
					   (has_alpha) ? TYPE_RGBA_8 : TYPE_RGB_8,
					   cc->profile_out,
					   (has_alpha) ? TYPE_RGBA_8 : TYPE_RGB_8,
					   INTENT_PERCEPTUAL, 0);

	if (!cc->transform)
		{
		if (debug) printf("failed to create color profile transform\n");

		color_man_cache_unref(cc);
		return NULL;
		}

	if (cc->profile_in_type != COLOR_PROFILE_MEM)
		{
		cm_cache_list = g_list_append(cm_cache_list, cc);
		color_man_cache_ref(cc);
		}

	return cc;
}

static void color_man_cache_free(ColorManCache *cc)
{
	if (!cc) return;

	cm_cache_list = g_list_remove(cm_cache_list, cc);
	color_man_cache_unref(cc);
}

static void color_man_cache_reset(void)
{
	while (cm_cache_list)
		{
		ColorManCache *cc;

		cc = cm_cache_list->data;
		color_man_cache_free(cc);
		}
}

static ColorManCache *color_man_cache_find(ColorManProfileType in_type, const gchar *in_file,
					   ColorManProfileType out_type, const gchar *out_file,
					   gint has_alpha)
{
	GList *work;

	work = cm_cache_list;
	while (work)
		{
		ColorManCache *cc;
		gint match = FALSE;

		cc = work->data;
		work = work->next;

		if (cc->profile_in_type == in_type &&
		    cc->profile_out_type == out_type &&
		    cc->has_alpha == has_alpha)
			{
			match = TRUE;
			}

		if (match && cc->profile_in_type == COLOR_PROFILE_FILE)
			{
			match = (cc->profile_in_file && in_file &&
				 strcmp(cc->profile_in_file, in_file) == 0);
			}
		if (match && cc->profile_out_type == COLOR_PROFILE_FILE)
			{
			match = (cc->profile_out_file && out_file &&
				 strcmp(cc->profile_out_file, out_file) == 0);
			}

		if (match) return cc;
		}

	return NULL;
}

static ColorManCache *color_man_cache_get(ColorManProfileType in_type, const gchar *in_file,
					  unsigned char *in_data, guint in_data_len,
					  ColorManProfileType out_type, const gchar *out_file,
					  gint has_alpha)
{
	ColorManCache *cc;

	cc = color_man_cache_find(in_type, in_file, out_type, out_file, has_alpha);
	if (cc)
		{
		color_man_cache_ref(cc);
		return cc;
		}

	return color_man_cache_new(in_type, in_file, in_data, in_data_len,
				   out_type, out_file, has_alpha);
}


/*
 *-------------------------------------------------------------------
 * color manager
 *-------------------------------------------------------------------
 */

static void color_man_done(ColorMan *cm, ColorManReturnType type)
{
	if (cm->func_done)
		{
		cm->func_done(cm, type, cm->func_done_data);
		}
}

static void color_man_correct_region(ColorMan *cm, gint x, gint y, gint w, gint h,
				     gint pixbuf_width, gint pixbuf_height)
{
	ColorManCache *cc;
	guchar *pix;
	gint rs;
	gint i;

	cc = cm->profile;

	pix = gdk_pixbuf_get_pixels(cm->pixbuf);
	rs = gdk_pixbuf_get_rowstride(cm->pixbuf);

	w = MIN(w, pixbuf_width - x);
	h = MIN(h, pixbuf_height - y);

	pix += x * ((cc->has_alpha) ? 4 : 3);
	for (i = 0; i < h; i++)
		{
		guchar *pbuf;

		pbuf = pix + ((y + i) * rs);
		cmsDoTransform(cc->transform, pbuf, pbuf, w);
		}

	if (cm->incremental_sync && cm->imd) image_area_changed(cm->imd, x, y, w, h);
}

static gint color_man_idle_cb(gpointer data)
{
	ColorMan *cm = data;
	gint width, height;
	gint rh;

	if (cm->imd &&
	    cm->pixbuf != image_get_pixbuf(cm->imd))
		{
		cm->idle_id = -1;
		color_man_done(cm, COLOR_RETURN_IMAGE_CHANGED);
		return FALSE;
		}

	width = gdk_pixbuf_get_width(cm->pixbuf);
	height = gdk_pixbuf_get_height(cm->pixbuf);

	if (cm->row > height)
		{
		if (!cm->incremental_sync && cm->imd)
			{
			image_area_changed(cm->imd, 0, 0, width, height);
			}

		cm->idle_id = -1;
		color_man_done(cm, COLOR_RETURN_SUCCESS);
		return FALSE;
		}

	rh = COLOR_MAN_CHUNK_SIZE / width + 1;
	color_man_correct_region(cm, 0, cm->row, width, rh, width, height);
	cm->row += rh;

	return TRUE;
}

static ColorMan *color_man_new_real(ImageWindow *imd, GdkPixbuf *pixbuf,
				    ColorManProfileType input_type, const gchar *input_file,
				    unsigned char *input_data, guint input_data_len,
				    ColorManProfileType screen_type, const gchar *screen_file,
				    ColorManDoneFunc done_func, gpointer done_data)
{
	ColorMan *cm;
	gint has_alpha;

	if (imd) pixbuf = image_get_pixbuf(imd);
	if (!pixbuf) return NULL;

	cm = g_new0(ColorMan, 1);
	cm->imd = imd;
	cm->pixbuf = pixbuf;
	g_object_ref(cm->pixbuf);

	cm->incremental_sync = FALSE;
	cm->row = 0;
	cm->idle_id = -1;

	cm->func_done = done_func;
	cm->func_done_data = done_data;

	has_alpha = gdk_pixbuf_get_has_alpha(pixbuf);
	cm->profile = color_man_cache_get(input_type, input_file, input_data, input_data_len,
					  screen_type, screen_file, has_alpha);
	if (!cm->profile)
		{
		color_man_free(cm);
		return NULL;
		}

	cm->idle_id = g_idle_add(color_man_idle_cb, cm);

	return cm;
}

ColorMan *color_man_new(ImageWindow *imd, GdkPixbuf *pixbuf,
			ColorManProfileType input_type, const gchar *input_file,
			ColorManProfileType screen_type, const gchar *screen_file,
			ColorManDoneFunc done_func, gpointer done_data)
{
	return color_man_new_real(imd, pixbuf,
				  input_type, input_file, NULL, 0,
				  screen_type, screen_file,
				  done_func, done_data);
}

ColorMan *color_man_new_embedded(ImageWindow *imd, GdkPixbuf *pixbuf,
				 unsigned char *input_data, guint input_data_len,
				 ColorManProfileType screen_type, const gchar *screen_file,
				 ColorManDoneFunc done_func, gpointer done_data)
{
	return color_man_new_real(imd, pixbuf,
				  COLOR_PROFILE_MEM, NULL, input_data, input_data_len,
				  screen_type, screen_file,
				  done_func, done_data);
}

void color_man_free(ColorMan *cm)
{
	if (!cm) return;

	if (cm->idle_id != -1) g_source_remove(cm->idle_id);
	if (cm->pixbuf) g_object_unref(cm->pixbuf);

	color_man_cache_unref(cm->profile);

	g_free(cm);
}

void color_man_update(void)
{
	color_man_cache_reset();
}

#else
/*** color support not enabled ***/


ColorMan *color_man_new(ImageWindow *imd, GdkPixbuf *pixbuf,
			ColorManProfileType input_type, const gchar *input_file,
			ColorManProfileType screen_type, const gchar *screen_file,
			ColorManDoneFunc don_func, gpointer done_data)
{
	/* no op */
	return NULL;
}

ColorMan *color_man_new_embedded(ImageWindow *imd, GdkPixbuf *pixbuf,
				 unsigned char *input_data, guint input_data_len,
				 ColorManProfileType screen_type, const gchar *screen_file,
				 ColorManDoneFunc done_func, gpointer done_data)
{
	/* no op */
	return NULL;
}

void color_man_free(ColorMan *cm)
{
	/* no op */
}

void color_man_update(void)
{
	/* no op */
}


#endif


