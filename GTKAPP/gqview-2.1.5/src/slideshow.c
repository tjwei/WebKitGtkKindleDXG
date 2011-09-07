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
#include "collect.h"
#include "image.h"
#include "slideshow.h"

#include "layout.h"
#include "layout_image.h"
#include "ui_fileops.h"


static void slideshow_timer_reset(SlideShowData *ss, gint reset);


void slideshow_free(SlideShowData *ss)
{
	if (!ss) return;

	slideshow_timer_reset(ss, FALSE);

	if (ss->stop_func) ss->stop_func(ss, ss->stop_data);

	if (ss->path_list) path_list_free(ss->path_list);
	if (ss->cd) collection_unref(ss->cd);
	g_free(ss->layout_path);

	g_list_free(ss->list);
	g_list_free(ss->list_done);

	g_free(ss->slide_path);

	g_free(ss);
}

static GList *generate_list(SlideShowData *ss)
{
	GList *list = NULL;

	if (ss->from_selection)
		{
		list = layout_selection_list_by_index(ss->layout);
		}
	else
		{
		gint i;
		for(i = 0; i < ss->slide_count; i++)
			{
			list = g_list_prepend(list, GINT_TO_POINTER(i));
			}
		list = g_list_reverse(list);
		}

	return list;
}

static GList *generate_random_list(SlideShowData *ss)
{
	GList *src_list = NULL;
	GList *list = NULL;
	GList *work;

	src_list = generate_list(ss);

	while(src_list)
		{
		gint p = (double)rand() / ((double)RAND_MAX + 1.0) * g_list_length(src_list);
		work = g_list_nth(src_list, p);
		list = g_list_prepend(list, work->data);
		src_list = g_list_remove(src_list, work->data);
		}

	return list;
}

static void slideshow_list_init(SlideShowData *ss, gint start_index)
{
	if (ss->list_done)
		{
		g_list_free(ss->list_done);
		ss->list_done = NULL;
		}

	if (ss->list) g_list_free(ss->list);

	if (slideshow_random)
		{
		ss->list = generate_random_list(ss);
		}
	else
		{
		ss->list = generate_list(ss);
		if (start_index >= 0)
			{
			/* start with specified image by skipping to it */
			gint i = 0;

			while(ss->list && i < start_index)
				{
				ss->list_done = g_list_prepend (ss->list_done, ss->list->data);
				ss->list = g_list_remove(ss->list, ss->list->data);
				i++;
				}
			}
		}
}

gint slideshow_should_continue(SlideShowData *ss)
{
	const gchar *imd_path;
	const gchar *path;

	if (!ss) return FALSE;

	imd_path = image_get_path(ss->imd);

	if ( ((imd_path == NULL) != (ss->slide_path == NULL)) ||
	    (imd_path && ss->slide_path && strcmp(imd_path, ss->slide_path) != 0) ) return FALSE;

	if (ss->path_list) return TRUE;

	if (ss->cd)
		{
		if (g_list_length(ss->cd->list) == ss->slide_count)
			return TRUE;
		else
			return FALSE;
		}

	if (!ss->layout) return FALSE;
	path = layout_get_path(ss->layout);

	if (path && ss->layout_path &&
	    strcmp(path, ss->layout_path) == 0)
		{
		if (ss->from_selection && ss->slide_count == layout_selection_count(ss->layout, NULL)) return TRUE;
		if (!ss->from_selection && ss->slide_count == layout_list_count(ss->layout, NULL)) return TRUE;
		}

	return FALSE;
}

static gint slideshow_step(SlideShowData *ss, gint forward)
{
	gint row;

	if (!slideshow_should_continue(ss))
		{
		return FALSE;
		}

	if (forward)
		{
		if (!ss->list) return TRUE;

		row = GPOINTER_TO_INT(ss->list->data);
		ss->list_done = g_list_prepend (ss->list_done, ss->list->data);
		ss->list = g_list_remove(ss->list, ss->list->data);
		}
	else
		{
		if (!ss->list_done || !ss->list_done->next) return TRUE;

		ss->list = g_list_prepend(ss->list, ss->list_done->data);
		ss->list_done = g_list_remove(ss->list_done, ss->list_done->data);
		row = GPOINTER_TO_INT(ss->list_done->data);
		}

	g_free(ss->slide_path);
	ss->slide_path = NULL;

	if (ss->path_list)
		{
		ss->slide_path = g_strdup(g_list_nth_data(ss->path_list, row));
		image_change_path(ss->imd, ss->slide_path, image_zoom_get_default(ss->imd, zoom_mode));
		}
	else if (ss->cd)
		{
		CollectInfo *info;

		info = g_list_nth_data(ss->cd->list, row);
		ss->slide_path = g_strdup(info->path);

		image_change_from_collection(ss->imd, ss->cd, info, image_zoom_get_default(ss->imd, zoom_mode));
		}
	else
		{
		ss->slide_path = g_strdup(layout_list_get_path(ss->layout, row));

		if (ss->from_selection)
			{
			image_change_path(ss->imd, ss->slide_path, image_zoom_get_default(ss->imd, zoom_mode));
			layout_status_update_info(ss->layout, NULL);
			}
		else
			{
			layout_image_set_index(ss->layout, row);
			}
		}

	if (!ss->list && slideshow_repeat)
		{
		slideshow_list_init(ss, -1);
		}

	if (!ss->list)
		{
		return FALSE;
		}

	/* read ahead */

	if (enable_read_ahead)
		{
		gint r;
		if (forward)
			{
			if (!ss->list) return TRUE;
			r = GPOINTER_TO_INT(ss->list->data);
			}
		else
			{
			if (!ss->list_done || !ss->list_done->next) return TRUE;
			r = GPOINTER_TO_INT(ss->list_done->next->data);
			}

		if (ss->path_list)
			{
			image_prebuffer_set(ss->imd, g_list_nth_data(ss->path_list, r));
			}
		else if (ss->cd)
			{
			CollectInfo *info;
			info = g_list_nth_data(ss->cd->list, r);
			if (info) image_prebuffer_set(ss->imd, info->path);
			}
		else if (ss->from_selection)
			{
			image_prebuffer_set(ss->imd, layout_list_get_path(ss->layout, r));
			}
		}

	return TRUE;
}

static gint slideshow_loop_cb(gpointer data)
{
	SlideShowData *ss = data;

	if (ss->paused) return TRUE;

	if (!slideshow_step(ss, TRUE))
		{
		ss->timeout_id = -1;
		slideshow_free(ss);
		return FALSE;
		}

	return TRUE;
}

static void slideshow_timer_reset(SlideShowData *ss, gint reset)
{
	if (reset)
		{
		if (slideshow_delay < 1) slideshow_delay = 1;

		if (ss->timeout_id != -1) g_source_remove(ss->timeout_id);
		ss->timeout_id = g_timeout_add(slideshow_delay * 1000 / SLIDESHOW_SUBSECOND_PRECISION,
					       slideshow_loop_cb, ss);
		}
	else if (ss->timeout_id != -1)
		{
		g_source_remove(ss->timeout_id);
		ss->timeout_id = -1;
		}
}

void slideshow_next(SlideShowData *ss)
{
	if (!ss) return;

	if (!slideshow_step(ss, TRUE))
		{
		slideshow_free(ss);
		return;
		}

	slideshow_timer_reset(ss, TRUE);
}

void slideshow_prev(SlideShowData *ss)
{
	if (!ss) return;

	if (!slideshow_step(ss, FALSE))
		{
		slideshow_free(ss);
		return;
		}

	slideshow_timer_reset(ss, TRUE);
}

static SlideShowData *real_slideshow_start(ImageWindow *imd, LayoutWindow *lw,
					   GList *path_list, gint start_point,
					   CollectionData *cd, CollectInfo *start_info,
					   void (*stop_func)(SlideShowData *, gpointer), gpointer stop_data)
{
	SlideShowData *ss;
	gint start_index = -1;

	if (!path_list && !cd && layout_list_count(lw, NULL) < 1) return NULL;

	ss = g_new0(SlideShowData, 1);

	ss->imd = imd;

	ss->path_list = path_list;
	ss->cd = cd;
	ss->layout = lw;
	ss->layout_path = NULL;

	ss->list = NULL;
	ss->list_done = NULL;

	ss->from_selection = FALSE;

	ss->stop_func = NULL;

	ss->timeout_id = -1;
	ss->paused = FALSE;

	if (ss->path_list)
		{
		ss->slide_count = g_list_length(ss->path_list);
		}
	else if (ss->cd)
		{
		collection_ref(ss->cd);
		ss->slide_count = g_list_length(ss->cd->list);
		if (!slideshow_random && start_info)
			{
			start_index = g_list_index(ss->cd->list, start_info);
			}
		}
	else
		{
		/* layout method */

		ss->slide_count = layout_selection_count(ss->layout, NULL);
		ss->layout_path = g_strdup(layout_get_path(ss->layout));
		if (ss->slide_count < 2)
			{
			ss->slide_count = layout_list_count(ss->layout, NULL);
			if (!slideshow_random && start_point >= 0 && start_point < ss->slide_count)
				{
				start_index = start_point;
				}
			}
		else
			{
			ss->from_selection = TRUE;
			}
		}

	slideshow_list_init(ss, start_index);

	ss->slide_path = g_strdup(image_get_path(ss->imd));
	if (slideshow_step(ss, TRUE))
		{
		slideshow_timer_reset(ss, TRUE);

		ss->stop_func = stop_func;
		ss->stop_data = stop_data;
		}
	else
		{
		slideshow_free(ss);
		ss = NULL;
		}

	return ss;
}

SlideShowData *slideshow_start_from_path_list(ImageWindow *imd, GList *list,
					      void (*stop_func)(SlideShowData *, gpointer), gpointer stop_data)
{
	return real_slideshow_start(imd, NULL, list, -1, NULL, NULL, stop_func, stop_data);
}

SlideShowData *slideshow_start_from_collection(ImageWindow *imd, CollectionData *cd,
					       void (*stop_func)(SlideShowData *, gpointer), gpointer stop_data,
					       CollectInfo *start_info)
{
	return real_slideshow_start(imd, NULL, NULL, -1, cd, start_info, stop_func, stop_data);
}

SlideShowData *slideshow_start(ImageWindow *imd, LayoutWindow *lw, gint start_point,
			       void (*stop_func)(SlideShowData *, gpointer), gpointer stop_data)
{
	return real_slideshow_start(imd, lw, NULL, start_point, NULL, NULL, stop_func, stop_data);
}

gint slideshow_paused(SlideShowData *ss)
{
	if (!ss) return FALSE;

	return ss->paused;
}

void slideshow_pause_set(SlideShowData *ss, gint paused)
{
	if (!ss) return;

	ss->paused = paused;
}

gint slideshow_pause_toggle(SlideShowData *ss)
{
	slideshow_pause_set(ss, !slideshow_paused(ss));
	return slideshow_paused(ss);
}


