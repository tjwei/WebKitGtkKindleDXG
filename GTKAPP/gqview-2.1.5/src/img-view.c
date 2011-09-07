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
#include "img-view.h"

#include "collect.h"
#include "collect-io.h"
#include "dnd.h"
#include "editors.h"
#include "filelist.h"
#include "fullscreen.h"
#include "image.h"
#include "image-overlay.h"
#include "info.h"
#include "menu.h"
#include "pixbuf-renderer.h"
#include "pixbuf_util.h"
#include "print.h"
#include "slideshow.h"
#include "utilops.h"
#include "ui_bookmark.h"
#include "ui_fileops.h"
#include "ui_menu.h"

#include <gdk/gdkkeysyms.h> /* for keyboard values */


typedef struct _ViewWindow ViewWindow;
struct _ViewWindow
{
	GtkWidget *window;
	ImageWindow *imd;
	FullScreenData *fs;
	SlideShowData *ss;

	GList *list;
	GList *list_pointer;
};


static GList *view_window_list = NULL;


static GtkWidget *view_popup_menu(ViewWindow *vw);
static void view_fullscreen_toggle(ViewWindow *vw, gint force_off);
static void view_overlay_toggle(ViewWindow *vw);

static void view_slideshow_next(ViewWindow *vw);
static void view_slideshow_prev(ViewWindow *vw);
static void view_slideshow_start(ViewWindow *vw);
static void view_slideshow_stop(ViewWindow *vw);

static void view_window_close(ViewWindow *vw);

static void view_window_dnd_init(ViewWindow *vw);


/*
 *-----------------------------------------------------------------------------
 * misc
 *-----------------------------------------------------------------------------
 */ 

static ImageWindow *view_window_active_image(ViewWindow *vw)
{
	if (vw->fs) return vw->fs->imd;

	return vw->imd;
}

static void view_window_set_list(ViewWindow *vw, GList *list)
{

	path_list_free(vw->list);
	vw->list = NULL;
	vw->list_pointer = NULL;

	vw->list = path_list_copy(list);
}

static gint view_window_contains_collection(ViewWindow *vw)
{
	CollectionData *cd;
	CollectInfo *info;

	cd = image_get_collection(view_window_active_image(vw), &info);

	return (cd && info);
}

static void view_collection_step(ViewWindow *vw, gint next)
{
	ImageWindow *imd = view_window_active_image(vw);
	CollectionData *cd;
	CollectInfo *info;
	CollectInfo *read_ahead_info = NULL;

	cd = image_get_collection(imd, &info);

	if (!cd || !info) return;

	if (next)
		{
		info = collection_next_by_info(cd, info);
		if (enable_read_ahead)
			{
			read_ahead_info = collection_next_by_info(cd, info);
			if (!read_ahead_info) read_ahead_info = collection_prev_by_info(cd, info);
			}
		}
	else
		{
		info = collection_prev_by_info(cd, info);
		if (enable_read_ahead)
			{
			read_ahead_info = collection_prev_by_info(cd, info);
			if (!read_ahead_info) read_ahead_info = collection_next_by_info(cd, info);
			}
		}

	if (info)
		{
		image_change_from_collection(imd, cd, info, image_zoom_get_default(imd, zoom_mode));

		if (read_ahead_info) image_prebuffer_set(imd, read_ahead_info->path);
		}
	
}

static void view_collection_step_to_end(ViewWindow *vw, gint last)
{
	ImageWindow *imd = view_window_active_image(vw);
	CollectionData *cd;
	CollectInfo *info;
	CollectInfo *read_ahead_info = NULL;

	cd = image_get_collection(imd, &info);

	if (!cd || !info) return;

	if (last)
		{
		info = collection_get_last(cd);
		if (enable_read_ahead) read_ahead_info = collection_prev_by_info(cd, info);
		}
	else
		{
		info = collection_get_first(cd);
		if (enable_read_ahead) read_ahead_info = collection_next_by_info(cd, info);
		}

	if (info)
		{
		image_change_from_collection(imd, cd, info, image_zoom_get_default(imd, zoom_mode));
		if (read_ahead_info) image_prebuffer_set(imd, read_ahead_info->path);
		}
}

static void view_list_step(ViewWindow *vw, gint next)
{
	ImageWindow *imd = view_window_active_image(vw);
	const gchar *path;
	GList *work;
	GList *work_ahead;

	if (!vw->list) return;

	path = image_get_path(imd);
	if (!path) return;

	if (g_list_position(vw->list, vw->list_pointer) >= 0)
		{
		work = vw->list_pointer;
		}
	else
		{
		gint found = FALSE;

		work = vw->list;
		while (work && !found)
			{
			gchar *temp;

			temp = work->data;

			if (strcmp(path, temp) == 0)
				{
				found = TRUE;
				}
			else
				{
				work = work->next;
				}
			}
		}
	if (!work) return;

	work_ahead = NULL;
	if (next)
		{
		work = work->next;
		if (work) work_ahead = work->next;
		}
	else
		{
		work = work->prev;
		if (work) work_ahead = work->prev;
		}

	if (!work) return;

	vw->list_pointer = work;
	path = work->data;
	image_change_path(imd, path, image_zoom_get_default(imd, zoom_mode));

	if (enable_read_ahead && work_ahead)
		{
		const gchar *next_path = work_ahead->data;
		image_prebuffer_set(imd, next_path);
		}
}

static void view_list_step_to_end(ViewWindow *vw, gint last)
{
	ImageWindow *imd = view_window_active_image(vw);
	const gchar *path;
	GList *work;
	GList *work_ahead;

	if (!vw->list) return;

	if (last)
		{
		work = g_list_last(vw->list);
		work_ahead = work->prev;
		}
	else
		{
		work = vw->list;
		work_ahead = work->next;
		}

	vw->list_pointer = work;
	path = work->data;
	image_change_path(imd, path, image_zoom_get_default(imd, zoom_mode));

	if (enable_read_ahead && work_ahead)
		{
		const gchar *next_path = work_ahead->data;
		image_prebuffer_set(imd, next_path);
		}
}

static void view_step_next(ViewWindow *vw)
{
	if (vw->ss)
		{
		view_slideshow_next(vw);
		}
	else if (vw->list)
		{
		view_list_step(vw, TRUE);
		}
	else
		{
		view_collection_step(vw, TRUE);
		}
}

static void view_step_prev(ViewWindow *vw)
{
	if (vw->ss)
		{
		view_slideshow_prev(vw);
		}
	else if (vw->list)
		{
		view_list_step(vw, FALSE);
		}
	else
		{
		view_collection_step(vw, FALSE);
		}
}

static void view_step_to_end(ViewWindow *vw, gint last)
{
	if (vw->list)
		{
		view_list_step_to_end(vw, last);
		}
	else
		{
		view_collection_step_to_end(vw, last);
		}
}

/*
 *-----------------------------------------------------------------------------
 * view window keyboard
 *-----------------------------------------------------------------------------
 */

static void view_window_menu_pos_cb(GtkMenu *menu, gint *x, gint *y, gboolean *push_in, gpointer data)
{
	ViewWindow *vw = data;
	ImageWindow *imd;

	imd = view_window_active_image(vw);
	gdk_window_get_origin(imd->pr->window, x, y);
	popup_menu_position_clamp(menu, x, y, 0);
}

static gint view_window_key_press_cb(GtkWidget *widget, GdkEventKey *event, gpointer data)
{
	ViewWindow *vw = data;
	ImageWindow *imd;
	gint stop_signal;
	GtkWidget *menu;
	gint x = 0;
	gint y = 0;

	imd = view_window_active_image(vw);

	stop_signal = TRUE;
	switch (event->keyval)
		{
		case GDK_Left: case GDK_KP_Left:
			x -= 1;
			break;
		case GDK_Right: case GDK_KP_Right:
			x += 1;
			break;
		case GDK_Up: case GDK_KP_Up:
			y -= 1;
			break;
		case GDK_Down: case GDK_KP_Down:
			y += 1;
			break;
		default:
			stop_signal = FALSE;
			break;
		}

	if (x != 0 || y!= 0)
		{
		if (event->state & GDK_SHIFT_MASK)
			{
			x *= 3;
			y *= 3;
			}

		keyboard_scroll_calc(&x, &y, event);
		image_scroll(imd, x, y);
		}

	if (stop_signal) return stop_signal;

	if (event->state & GDK_CONTROL_MASK)
		{
		gint n = -1;

		stop_signal = TRUE;
		switch (event->keyval)
			{
			case '1':
				n = 0;
				break;
			case '2':
				n = 1;
				break;
			case '3':
				n = 2;
				break;
			case '4':
				n = 3;
				break;
			case '5':
				n = 4;
				break;
			case '6':
				n = 5;
				break;
			case '7':
				n = 6;
				break;
			case '8':
				n = 7;
				break;
			case '9':
				n = 8;
				break;
			case '0':
				n = 9;
				break;
			case 'C': case 'c':
				file_util_copy(image_get_path(imd), NULL, NULL, imd->widget);
				break;
			case 'M': case 'm':
				file_util_move(image_get_path(imd), NULL, NULL, imd->widget);
				break;
			case 'R': case 'r':
				file_util_rename(image_get_path(imd), NULL, imd->widget);
				break;
			case 'D': case 'd':
				file_util_delete(image_get_path(imd), NULL, imd->widget);
				break;
			case 'P': case 'p':
				info_window_new(image_get_path(imd), NULL);
				break;
			case 'W': case 'w':
				view_window_close(vw);
				break;
			default:
				stop_signal = FALSE;
				break;
			}
		if (n != -1)
			{
			if (!editor_window_flag_set(n))
				{
				view_fullscreen_toggle(vw, TRUE);
				}
			imd = view_window_active_image(vw);
			start_editor_from_file(n, image_get_path(imd));
			}
		}
	else if (event->state & GDK_SHIFT_MASK)
		{
		stop_signal = TRUE;
		switch (event->keyval)
			{
			case 'R': case 'r':
				image_alter(imd, ALTER_ROTATE_180);
				break;
			case 'M': case 'm':
				image_alter(imd, ALTER_MIRROR);
				break;
			case 'F': case 'f':
				image_alter(imd, ALTER_FLIP);
				break;
			case 'G': case 'g':
				image_alter(imd, ALTER_DESATURATE);
				break;
			case 'P': case 'p':
				{
				const gchar *path;

				view_fullscreen_toggle(vw, TRUE);
				imd = view_window_active_image(vw);
				path = image_get_path(imd);
				print_window_new(path,
						 (path) ? g_list_append(NULL, g_strdup(path)) : NULL,
						 path_list_copy(vw->list), vw->window);
				}
				break;
			default:
				stop_signal = FALSE;
				break;
			}
		}
	else 
		{
		stop_signal = TRUE;
		switch (event->keyval)
			{
			case GDK_Page_Up: case GDK_KP_Page_Up:
			case GDK_BackSpace:
			case 'B': case 'b':
				view_step_prev(vw);
				break;
			case GDK_Page_Down: case GDK_KP_Page_Down:
			case GDK_space:
			case 'N': case 'n':
				view_step_next(vw);
				break;
			case GDK_Home: case GDK_KP_Home:
				view_step_to_end(vw, FALSE);
				break;
			case GDK_End: case GDK_KP_End:
				view_step_to_end(vw, TRUE);
				break;
			case '+': case '=': case GDK_KP_Add:
				image_zoom_adjust(imd, get_zoom_increment());
				break;
			case '-': case GDK_KP_Subtract:
				image_zoom_adjust(imd, -get_zoom_increment());
				break;
			case 'X': case 'x': case GDK_KP_Multiply:
				image_zoom_set(imd, 0.0);
				break;
			case 'Z': case 'z': case GDK_KP_Divide: case '1':
				image_zoom_set(imd, 1.0);
				break;
			case '2':
				image_zoom_set(imd, 2.0);
				break;
			case '3':
				image_zoom_set(imd, 3.0);
				break;
			case '4':
				image_zoom_set(imd, 4.0);
				break;
			case '7':
				image_zoom_set(imd, -4.0);
				break;
			case '8':
				image_zoom_set(imd, -3.0);
				break;
			case '9':
				image_zoom_set(imd, -2.0);
				break;
			case 'W': case 'w':
				image_zoom_set_fill_geometry(imd, FALSE);
				break;
			case 'H': case 'h':
				image_zoom_set_fill_geometry(imd, TRUE);
				break;
			case 'R': case 'r':
				image_reload(imd);
				break;
			case 'S': case 's':
				if (vw->ss)
					{
					view_slideshow_stop(vw);
					}
				else
					{
					view_slideshow_start(vw);
					}
				break;
			case 'P': case 'p':
				slideshow_pause_toggle(vw->ss);
				break;
			case 'F': case 'f':
			case 'V': case 'v':
			case GDK_F11:
				view_fullscreen_toggle(vw, FALSE);
				break;
			case 'I': case 'i':
				view_overlay_toggle(vw);
				break;
			case ']':
				image_alter(imd, ALTER_ROTATE_90);
				break;
			case '[':
				image_alter(imd, ALTER_ROTATE_90_CC);
				break;
			case GDK_Delete: case GDK_KP_Delete:
				if (enable_delete_key)
					{
					file_util_delete(image_get_path(imd), NULL, imd->widget);
					}
				break;
			case GDK_Escape:
				if (vw->fs)
					{
					view_fullscreen_toggle(vw, TRUE);
					}
				else
					{
					view_window_close(vw);
					}
				break;
			case GDK_Menu:
			case GDK_F10:
				menu = view_popup_menu(vw);
				gtk_menu_popup(GTK_MENU(menu), NULL, NULL,
					       view_window_menu_pos_cb, vw, 0, GDK_CURRENT_TIME);
				break;
			default:
				stop_signal = FALSE;
				break;
			}
		}

	return stop_signal;
}

/*
 *-----------------------------------------------------------------------------
 * view window main routines
 *-----------------------------------------------------------------------------
 */ 

static void button_cb(ImageWindow *imd, gint button, guint32 time,
		      gdouble x, gdouble y, guint state, gpointer data)
{
	ViewWindow *vw = data;
	GtkWidget *menu;

	switch (button)
		{
		case 1:
			view_step_next(vw);
			break;
		case 2:
			view_step_prev(vw);
			break;
		case 3:
			menu = view_popup_menu(vw);
			gtk_menu_popup (GTK_MENU(menu), NULL, NULL, NULL, NULL, 3, time);
			break;
		default:
			break;
		}
}

static void scroll_cb(ImageWindow *imd, GdkScrollDirection direction, guint32 time,
		      gdouble x, gdouble y, guint state, gpointer data)
{
	ViewWindow *vw = data;

	if (state & GDK_CONTROL_MASK)
		{
		switch (direction)
			{
			case GDK_SCROLL_UP:
				image_zoom_adjust_at_point(imd, get_zoom_increment(), x, y);
				break;
			case GDK_SCROLL_DOWN:
				image_zoom_adjust_at_point(imd, -get_zoom_increment(), x, y);
				break;
			default:
				break;
			}
		}
	else if ( (state & GDK_SHIFT_MASK) != (mousewheel_scrolls))
		{
		switch (direction)
			{
			case GDK_SCROLL_UP:
				image_scroll(imd, 0, -MOUSEWHEEL_SCROLL_SIZE);
				break;
			case GDK_SCROLL_DOWN:
				image_scroll(imd, 0, MOUSEWHEEL_SCROLL_SIZE);
				break;
			case GDK_SCROLL_LEFT:
				image_scroll(imd, -MOUSEWHEEL_SCROLL_SIZE, 0);
				break;
			case GDK_SCROLL_RIGHT:
				image_scroll(imd, MOUSEWHEEL_SCROLL_SIZE, 0);
				break;
			default:
				break;
			}
		}
	else
		{
		switch (direction)
			{
			case GDK_SCROLL_UP:
				view_step_prev(vw);
				break;
			case GDK_SCROLL_DOWN:
				view_step_next(vw);
				break;
			default:
				break;
			}
		}
}

static void view_image_set_buttons(ViewWindow *vw, ImageWindow *imd)
{
	image_set_button_func(imd, button_cb, vw);
	image_set_scroll_func(imd, scroll_cb, vw);
}

static void view_fullscreen_stop_func(FullScreenData *fs, gpointer data)
{
	ViewWindow *vw = data;

	vw->fs = NULL;

	if (vw->ss) vw->ss->imd = vw->imd;
}

static void view_fullscreen_toggle(ViewWindow *vw, gint force_off)
{
	if (force_off && !vw->fs) return;

	if (vw->fs)
		{
		if (image_osd_get(vw->fs->imd, NULL, NULL))
			{
			image_osd_set(vw->imd, TRUE, TRUE);
			}

		fullscreen_stop(vw->fs);
		}
	else
		{
		vw->fs = fullscreen_start(vw->window, vw->imd, view_fullscreen_stop_func, vw);

		view_image_set_buttons(vw, vw->fs->imd);
		g_signal_connect(G_OBJECT(vw->fs->window), "key_press_event",
				 G_CALLBACK(view_window_key_press_cb), vw);

		if (vw->ss) vw->ss->imd = vw->fs->imd;

		if (image_osd_get(vw->imd, NULL, NULL))
			{
			image_osd_set(vw->imd, FALSE, FALSE);
			image_osd_set(vw->fs->imd, TRUE, TRUE);
			}
		}
}

static void view_overlay_toggle(ViewWindow *vw)
{
	ImageWindow *imd;

	imd = view_window_active_image(vw);

	if (!image_osd_get(imd, NULL, NULL))
		{
		image_osd_set(imd, TRUE, TRUE);
		image_osd_icon(imd, IMAGE_OSD_ICON, -1);
		}
	else
		{
		image_osd_set(imd, FALSE, FALSE);
		}
}

static void view_slideshow_next(ViewWindow *vw)
{
	if (vw->ss) slideshow_next(vw->ss);
}

static void view_slideshow_prev(ViewWindow *vw)
{
	if (vw->ss) slideshow_prev(vw->ss);
}

static void view_slideshow_stop_func(SlideShowData *fs, gpointer data)
{
	ViewWindow *vw = data;
	GList *work;
	const gchar *path;

	vw->ss = NULL;

	work = vw->list;
	path = image_get_path(view_window_active_image(vw));
	while (work)
		{
		gchar *temp;

		temp = work->data;
		if (strcmp(path, temp) == 0)
			{
			vw->list_pointer = work;
			work = NULL;
			}
		else
			{
			work = work->next;
			}
		}
}

static void view_slideshow_start(ViewWindow *vw)
{
	if (!vw->ss)
		{
		CollectionData *cd;
		CollectInfo *info;

		if (vw->list)
			{
			vw->ss = slideshow_start_from_path_list(view_window_active_image(vw),
								path_list_copy(vw->list),
								view_slideshow_stop_func, vw);
			vw->list_pointer = NULL;
			return;
			}

		cd = image_get_collection(view_window_active_image(vw), &info);
		if (cd && info)
			{
			vw->ss = slideshow_start_from_collection(view_window_active_image(vw), cd,
								 view_slideshow_stop_func, vw, info);
			}
		}
}

static void view_slideshow_stop(ViewWindow *vw)
{
	if (vw->ss) slideshow_free(vw->ss);
}

static void view_window_destroy_cb(GtkWidget *widget, gpointer data)
{
	ViewWindow *vw = data;

	view_window_list = g_list_remove(view_window_list, vw);

	view_slideshow_stop(vw);
	fullscreen_stop(vw->fs);

	path_list_free(vw->list);
	g_free(vw);
}

static void view_window_close(ViewWindow *vw)
{
	view_slideshow_stop(vw);
	view_fullscreen_toggle(vw, TRUE);
	gtk_widget_destroy(vw->window);
}

static gint view_window_delete_cb(GtkWidget *w, GdkEventAny *event, gpointer data)
{
	ViewWindow *vw = data;

	view_window_close(vw);
	return TRUE;
}

static ViewWindow *real_view_window_new(const gchar *path, GList *list, CollectionData *cd, CollectInfo *info)
{
	ViewWindow *vw;
	GtkAllocation req_size;
	GdkGeometry geometry;
	gint w, h;

	if (!path && !list && (!cd || !info)) return NULL;

	vw = g_new0(ViewWindow, 1);
	vw->fs = NULL;
	vw->ss = NULL;
	vw->list = NULL;
	vw->list_pointer = NULL;

	vw->window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

	geometry.min_width = 8;
	geometry.min_height = 8;
	gtk_window_set_geometry_hints(GTK_WINDOW(vw->window), NULL, &geometry, GDK_HINT_MIN_SIZE);

	gtk_window_set_resizable(GTK_WINDOW(vw->window), TRUE);
	gtk_window_set_title (GTK_WINDOW(vw->window), "GQview");
        gtk_window_set_wmclass(GTK_WINDOW(vw->window), "view", "GQview");
        gtk_container_set_border_width(GTK_CONTAINER(vw->window), 0);

	window_set_icon(vw->window, PIXBUF_INLINE_ICON_VIEW, NULL);

	vw->imd = image_new(FALSE);

	if (black_window_background) image_background_set_black(vw->imd, TRUE);

	image_attach_window(vw->imd, vw->window, NULL, "GQview", TRUE);

	image_auto_refresh(vw->imd, 0);
	image_top_window_set_sync(vw->imd, TRUE);

	gtk_container_add(GTK_CONTAINER(vw->window), vw->imd->widget);
	gtk_widget_show(vw->imd->widget);

	view_window_dnd_init(vw);

	view_image_set_buttons(vw, vw->imd);

	g_signal_connect(G_OBJECT(vw->window), "destroy",
			 G_CALLBACK(view_window_destroy_cb), vw);
	g_signal_connect(G_OBJECT(vw->window), "delete_event",
			 G_CALLBACK(view_window_delete_cb), vw);
	g_signal_connect(G_OBJECT(vw->window), "key_press_event",
			 G_CALLBACK(view_window_key_press_cb), vw);
	if (cd && info)
		{
		image_change_from_collection(vw->imd, cd, info, image_zoom_get_default(NULL, zoom_mode));
		if (enable_read_ahead)
			{
			CollectInfo * r_info = collection_next_by_info(cd, info);
			if (!r_info) r_info = collection_prev_by_info(cd, info);
			if (r_info) image_prebuffer_set(vw->imd, r_info->path);
			}
		}
	else if (list)
		{
		view_window_set_list(vw, list);
		vw->list_pointer = vw->list;
		image_change_path(vw->imd, (gchar *)vw->list->data, image_zoom_get_default(NULL, zoom_mode));

		if (enable_read_ahead)
			{
			GList *work = vw->list->next;
			if (work) image_prebuffer_set(vw->imd, (gchar *)work->data);
			}
		}
	else
		{
		image_change_path(vw->imd, path, image_zoom_get_default(NULL, zoom_mode));
		}

	if (image_zoom_get(vw->imd) == 0.0)
		{
		pixbuf_renderer_get_image_size(PIXBUF_RENDERER(vw->imd->pr), &w, &h);
		}
	else
		{
		pixbuf_renderer_get_scaled_size(PIXBUF_RENDERER(vw->imd->pr), &w, &h);
		}
	if (limit_window_size)
		{
		gint mw = gdk_screen_width() * max_window_size / 100;
		gint mh = gdk_screen_height() * max_window_size / 100;

		if (w > mw) w = mw;
		if (h > mh) h = mh;
		}

	gtk_window_set_default_size(GTK_WINDOW(vw->window), w, h);
	req_size.x = req_size.y = 0;
	req_size.width = w;
	req_size.height = h;
	gtk_widget_size_allocate(GTK_WIDGET(vw->window), &req_size);

	gtk_widget_set_size_request(vw->imd->pr, w, h);

	gtk_widget_show(vw->window);

	view_window_list = g_list_append(view_window_list, vw);

	return vw;
}

static void view_window_collection_unref_cb(GtkWidget *widget, gpointer data)
{
	CollectionData *cd = data;

	collection_unref(cd);
}

void view_window_new(const gchar *path)
{
	if (file_extension_match(path, ".gqv"))
		{
		ViewWindow *vw;
		CollectionData *cd;
		CollectInfo *info;

		cd = collection_new(path);
		if (collection_load(cd, path, FALSE))
			{
			info = collection_get_first(cd);
			}
		else
			{
			collection_unref(cd);
			cd = NULL;
			info = NULL;
			}
		vw = real_view_window_new(NULL, NULL, cd, info);
		if (vw && cd)
			{
			g_signal_connect(G_OBJECT(vw->window), "destroy",
					 G_CALLBACK(view_window_collection_unref_cb), cd);
			}
		}
	else if (isdir(path))
		{
		GList *list = NULL;

		if (path_list(path, &list, NULL))
			{
			list = path_list_sort(list);
			list = path_list_filter(list, FALSE);
			}
		real_view_window_new(NULL, list, NULL, NULL);
		path_list_free(list);
		}
	else
		{
		real_view_window_new(path, NULL, NULL, NULL);
		}
}

void view_window_new_from_list(GList *list)
{
	real_view_window_new(NULL, list, NULL, NULL);
}

void view_window_new_from_collection(CollectionData *cd, CollectInfo *info)
{
	real_view_window_new(NULL, NULL, cd, info);
}

/*
 *-----------------------------------------------------------------------------
 * public
 *-----------------------------------------------------------------------------
 */

void view_window_colors_update(void)
{
	GList *work;

	work = view_window_list;
	while (work)
		{
		ViewWindow *vw = work->data;
		work = work->next;

		image_background_set_black(vw->imd, black_window_background);
		}
}

gint view_window_find_image(ImageWindow *imd, gint *index, gint *total)
{
	GList *work;

	work = view_window_list;
	while (work)
		{
		ViewWindow *vw = work->data;
		work = work->next;

		if (vw->imd == imd ||
		    (vw->fs && vw->fs->imd == imd))
			{
			if (vw->ss)
				{
				gint n;
				gint t;

				n = g_list_length(vw->ss->list_done);
				t = n + g_list_length(vw->ss->list);
				if (n == 0) n = t;
				if (index) *index = n - 1;
				if (total) *total = t;
				}
			else
				{
				if (index) *index = g_list_position(vw->list, vw->list_pointer);
				if (total) *total = g_list_length(vw->list);
				}
			return TRUE;
			}
		}

	return FALSE;
}

/*
 *-----------------------------------------------------------------------------
 * view window menu routines and callbacks
 *-----------------------------------------------------------------------------
 */ 

static void view_new_window_cb(GtkWidget *widget, gpointer data)
{
	ViewWindow *vw = data;
	CollectionData *cd;
	CollectInfo *info;

	cd = image_get_collection(vw->imd, &info);

	if (cd && info)
		{
		view_window_new_from_collection(cd, info);
		}
	else
		{
		view_window_new(image_get_path(vw->imd));
		}
}

static void view_edit_cb(GtkWidget *widget, gpointer data)
{
	ViewWindow *vw;
	ImageWindow *imd;
	gint n;

	vw = submenu_item_get_data(widget);
	n = GPOINTER_TO_INT(data);
	if (!vw) return;

	if (!editor_window_flag_set(n))
		{
		view_fullscreen_toggle(vw, TRUE);
		}

	imd = view_window_active_image(vw);
	start_editor_from_file(n, image_get_path(imd));
}

static void view_alter_cb(GtkWidget *widget, gpointer data)
{
	ViewWindow *vw;
	AlterType type;

	vw = submenu_item_get_data(widget);
	type = GPOINTER_TO_INT(data);

	if (!vw) return;
	image_alter(vw->imd, type);
}

static void view_info_cb(GtkWidget *widget, gpointer data)
{
	ViewWindow *vw = data;
	ImageWindow *imd;

	imd = view_window_active_image(vw);
	info_window_new(image_get_path(imd), NULL);
}

static void view_wallpaper_cb(GtkWidget *widget, gpointer data)
{
	ViewWindow *vw = data;
	ImageWindow *imd;

	imd = view_window_active_image(vw);
	image_to_root_window(imd, (image_zoom_get(imd) == 0.0));
}

static void view_zoom_in_cb(GtkWidget *widget, gpointer data)
{
	ViewWindow *vw = data;

	image_zoom_adjust(view_window_active_image(vw), get_zoom_increment());
}

static void view_zoom_out_cb(GtkWidget *widget, gpointer data)
{
	ViewWindow *vw = data;

	image_zoom_adjust(view_window_active_image(vw), -get_zoom_increment());
}

static void view_zoom_1_1_cb(GtkWidget *widget, gpointer data)
{
	ViewWindow *vw = data;

	image_zoom_set(view_window_active_image(vw), 1.0);
}

static void view_zoom_fit_cb(GtkWidget *widget, gpointer data)
{
	ViewWindow *vw = data;

	image_zoom_set(view_window_active_image(vw), 0.0);
}

static void view_copy_cb(GtkWidget *widget, gpointer data)
{
	ViewWindow *vw = data;
	ImageWindow *imd;

	imd = view_window_active_image(vw);
	file_util_copy(image_get_path(imd), NULL, NULL, imd->widget);
}

static void view_move_cb(GtkWidget *widget, gpointer data)
{
	ViewWindow *vw = data;
	ImageWindow *imd;

	imd = view_window_active_image(vw);
	file_util_move(image_get_path(imd), NULL, NULL, imd->widget);
}

static void view_rename_cb(GtkWidget *widget, gpointer data)
{
	ViewWindow *vw = data;
	ImageWindow *imd;

	imd = view_window_active_image(vw);
	file_util_rename(image_get_path(imd), NULL, imd->widget);
}

static void view_delete_cb(GtkWidget *widget, gpointer data)
{
	ViewWindow *vw = data;
	ImageWindow *imd;

	imd = view_window_active_image(vw);
	file_util_delete(image_get_path(imd), NULL, imd->widget);
}

static void view_fullscreen_cb(GtkWidget *widget, gpointer data)
{
	ViewWindow *vw = data;

	view_fullscreen_toggle(vw, FALSE);
}

static void view_slideshow_start_cb(GtkWidget *widget, gpointer data)
{
	ViewWindow *vw = data;

	view_slideshow_start(vw);
}

static void view_slideshow_stop_cb(GtkWidget *widget, gpointer data)
{
	ViewWindow *vw = data;

	view_slideshow_stop(vw);
}

static void view_slideshow_pause_cb(GtkWidget *widget, gpointer data)
{
	ViewWindow *vw = data;

	slideshow_pause_toggle(vw->ss);
}

static void view_close_cb(GtkWidget *widget, gpointer data)
{
	ViewWindow *vw = data;

	view_window_close(vw);
}

static GtkWidget *view_popup_menu(ViewWindow *vw)
{
	GtkWidget *menu;
	GtkWidget *item;

	menu = popup_menu_short_lived();

	menu_item_add_stock(menu, _("Zoom _in"), GTK_STOCK_ZOOM_IN, G_CALLBACK(view_zoom_in_cb), vw);
	menu_item_add_stock(menu, _("Zoom _out"), GTK_STOCK_ZOOM_OUT, G_CALLBACK(view_zoom_out_cb), vw);
	menu_item_add_stock(menu, _("Zoom _1:1"), GTK_STOCK_ZOOM_100, G_CALLBACK(view_zoom_1_1_cb), vw);
	menu_item_add_stock(menu, _("Fit image to _window"), GTK_STOCK_ZOOM_FIT, G_CALLBACK(view_zoom_fit_cb), vw);
	menu_item_add_divider(menu);

	item = submenu_add_edit(menu, NULL, G_CALLBACK(view_edit_cb), vw);
	menu_item_add_divider(item);
	menu_item_add(item, _("Set as _wallpaper"), G_CALLBACK(view_wallpaper_cb), vw);

	submenu_add_alter(menu, G_CALLBACK(view_alter_cb), vw);

	menu_item_add_stock(menu, _("_Properties"), GTK_STOCK_PROPERTIES, G_CALLBACK(view_info_cb), vw);

	menu_item_add_stock(menu, _("View in _new window"), GTK_STOCK_NEW, G_CALLBACK(view_new_window_cb), vw);

	menu_item_add_divider(menu);
	menu_item_add_stock(menu, _("_Copy..."), GTK_STOCK_COPY, G_CALLBACK(view_copy_cb), vw);
	menu_item_add(menu, _("_Move..."), G_CALLBACK(view_move_cb), vw);
	menu_item_add(menu, _("_Rename..."), G_CALLBACK(view_rename_cb), vw);
	menu_item_add_stock(menu, _("_Delete..."), GTK_STOCK_DELETE, G_CALLBACK(view_delete_cb), vw);

	menu_item_add_divider(menu);

	if (vw->ss)
		{
		menu_item_add(menu, _("_Stop slideshow"), G_CALLBACK(view_slideshow_stop_cb), vw);
		if (slideshow_paused(vw->ss))
			{
			item = menu_item_add(menu, _("Continue slides_how"),
					     G_CALLBACK(view_slideshow_pause_cb), vw);
			}
		else
			{
			item = menu_item_add(menu, _("Pause slides_how"),
					     G_CALLBACK(view_slideshow_pause_cb), vw);
			}
		}
	else
		{
		item = menu_item_add(menu, _("_Start slideshow"), G_CALLBACK(view_slideshow_start_cb), vw);
		gtk_widget_set_sensitive(item, (vw->list != NULL) || view_window_contains_collection(vw));
		item = menu_item_add(menu, _("Pause slides_how"), G_CALLBACK(view_slideshow_pause_cb), vw);
		gtk_widget_set_sensitive(item, FALSE);
		}

	if (vw->fs)
		{
		menu_item_add(menu, _("Exit _full screen"), G_CALLBACK(view_fullscreen_cb), vw);
		}
	else
		{
		menu_item_add(menu, _("_Full screen"), G_CALLBACK(view_fullscreen_cb), vw);
		}

	menu_item_add_divider(menu);
	menu_item_add_stock(menu, _("C_lose window"), GTK_STOCK_CLOSE, G_CALLBACK(view_close_cb), vw);

	return menu;
}

/*
 *-------------------------------------------------------------------
 * dnd confirm dir
 *-------------------------------------------------------------------
 */

typedef struct {
	ViewWindow *vw;
	GList *list;
} CViewConfirmD;

static void view_dir_list_cancel(GtkWidget *widget, gpointer data)
{
	/* do nothing */
}

static void view_dir_list_do(ViewWindow *vw, GList *list, gint skip, gint recurse)
{
	GList *work;

	view_window_set_list(vw, NULL);

	work = list;
	while (work)
		{
		gchar *path = work->data;
		work = work->next;

		if (isdir(path))
			{
			if (!skip)
				{
				GList *list = NULL;

				if (recurse)
					{
					list = path_list_recursive(path);
					}
				else
					{
					path_list(path, &list, NULL);
					list = path_list_sort(list);
					list = path_list_filter(list, FALSE);
					}
				if (list) vw->list = g_list_concat(vw->list, list);
				}
			}
		else
			{
			/* FIXME: no filtering here */
			vw->list = g_list_append(vw->list, g_strdup(path));
			}
		}

	if (vw->list)
		{
		gchar *path;

		vw->list_pointer = vw->list;
		path = vw->list->data;
		image_change_path(vw->imd, path, image_zoom_get_default(vw->imd, zoom_mode));

		work = vw->list->next;
		if (enable_read_ahead && work)
			{
			path = work->data;
			image_prebuffer_set(vw->imd, path);
			}
		}
	else
		{
		image_change_path(vw->imd, NULL, image_zoom_get_default(vw->imd, zoom_mode));
		}
}

static void view_dir_list_add(GtkWidget *widget, gpointer data)
{
	CViewConfirmD *d = data;
	view_dir_list_do(d->vw, d->list, FALSE, FALSE);
}

static void view_dir_list_recurse(GtkWidget *widget, gpointer data)
{
	CViewConfirmD *d = data;
	view_dir_list_do(d->vw, d->list, FALSE, TRUE);
}

static void view_dir_list_skip(GtkWidget *widget, gpointer data)
{
	CViewConfirmD *d = data;
	view_dir_list_do(d->vw, d->list, TRUE, FALSE);
}

static void view_dir_list_destroy(GtkWidget *widget, gpointer data)
{
	CViewConfirmD *d = data;
        path_list_free(d->list);
        g_free(d);
}

static GtkWidget *view_confirm_dir_list(ViewWindow *vw, GList *list)
{
	GtkWidget *menu;
	CViewConfirmD *d;

	d = g_new(CViewConfirmD, 1);
	d->vw = vw;
	d->list = list;

	menu = popup_menu_short_lived();
	g_signal_connect(G_OBJECT(menu), "destroy",
			 G_CALLBACK(view_dir_list_destroy), d);

	menu_item_add_stock(menu, _("Dropped list includes folders."), GTK_STOCK_DND_MULTIPLE, NULL, NULL);
	menu_item_add_divider(menu);
	menu_item_add_stock(menu, _("_Add contents"), GTK_STOCK_OK, G_CALLBACK(view_dir_list_add), d);
	menu_item_add_stock(menu, _("Add contents _recursive"), GTK_STOCK_ADD, G_CALLBACK(view_dir_list_recurse), d);
	menu_item_add_stock(menu, _("_Skip folders"), GTK_STOCK_REMOVE, G_CALLBACK(view_dir_list_skip), d);
	menu_item_add_divider(menu);
	menu_item_add_stock(menu, _("Cancel"), GTK_STOCK_CANCEL, G_CALLBACK(view_dir_list_cancel), d);

	return menu;
}

/*
 *-----------------------------------------------------------------------------
 * image drag and drop routines
 *-----------------------------------------------------------------------------
 */

static void view_window_get_dnd_data(GtkWidget *widget, GdkDragContext *context,
				     gint x, gint y,
				     GtkSelectionData *selection_data, guint info,
				     guint time, gpointer data)
{
	ViewWindow *vw = data;
	ImageWindow *imd;

	if (gtk_drag_get_source_widget(context) == vw->imd->pr) return;

	imd = vw->imd;

	if (info == TARGET_URI_LIST || info == TARGET_APP_COLLECTION_MEMBER)
		{
		CollectionData *source;
		GList *list;
		GList *info_list;

		if (info == TARGET_URI_LIST)
			{
			GList *work;

			list = uri_list_from_text((gchar *)selection_data->data, TRUE);

			work = list;
			while (work)
				{
				if (isdir((gchar *)work->data))
					{
					GtkWidget *menu;
					menu = view_confirm_dir_list(vw, list);
					gtk_menu_popup(GTK_MENU(menu), NULL, NULL, NULL, NULL, 0, time);
					return;
					}
				work = work->next;
				}

			list = path_list_filter(list, FALSE);

			source = NULL;
			info_list = NULL;
			}
		else
			{
			source = collection_from_dnd_data((gchar *)selection_data->data, &list, &info_list);
			}

		if (list)
			{
			gchar *path;

			path = list->data;
			if (isfile(path))
				{
				view_slideshow_stop(vw);
				view_window_set_list(vw, NULL);

				if (source && info_list)
					{
					image_change_from_collection(imd, source, info_list->data, image_zoom_get_default(imd, zoom_mode));
					}
				else
					{
					if (list->next)
						{
						vw->list = list;
						list = NULL;

						vw->list_pointer = vw->list;
						}
					image_change_path(imd, path, image_zoom_get_default(imd, zoom_mode));
					}
				}
			}
		path_list_free(list);
		g_list_free(info_list);
		}
}

static void view_window_set_dnd_data(GtkWidget *widget, GdkDragContext *context,
				     GtkSelectionData *selection_data, guint info,
				     guint time, gpointer data)
{
	ViewWindow *vw = data;
	const gchar *path;

	path = image_get_path(vw->imd);

	if (path)
		{
		gchar *text = NULL;
		gint len;
		gint plain_text;
		GList *list;

		switch (info)
			{
			case TARGET_URI_LIST:
				plain_text = FALSE;
				break;
			case TARGET_TEXT_PLAIN:
			default:
				plain_text = TRUE;
				break;
			}
		list = g_list_append(NULL, (gchar *)path);
		text = uri_text_from_list(list, &len, plain_text);
		g_list_free(list);
		if (text)
			{
			gtk_selection_data_set (selection_data, selection_data->target,
						8, (guchar *)text, len);
			g_free(text);
			}
		}
	else
		{
		gtk_selection_data_set (selection_data, selection_data->target,
					8, NULL, 0);
		}
}

static void view_window_dnd_init(ViewWindow *vw)
{
	ImageWindow *imd;

	imd = vw->imd;

	gtk_drag_source_set(imd->pr, GDK_BUTTON2_MASK,
			    dnd_file_drag_types, dnd_file_drag_types_count,
			    GDK_ACTION_COPY | GDK_ACTION_MOVE | GDK_ACTION_LINK);
	g_signal_connect(G_OBJECT(imd->pr), "drag_data_get",
			 G_CALLBACK(view_window_set_dnd_data), vw);

	gtk_drag_dest_set(imd->pr,
			  GTK_DEST_DEFAULT_MOTION | GTK_DEST_DEFAULT_DROP,
			  dnd_file_drop_types, dnd_file_drop_types_count,
                          GDK_ACTION_COPY | GDK_ACTION_MOVE | GDK_ACTION_LINK);
	g_signal_connect(G_OBJECT(imd->pr), "drag_data_received",
			 G_CALLBACK(view_window_get_dnd_data), vw);
}

/*
 *-----------------------------------------------------------------------------
 * maintenance (for rename, move, remove)
 *-----------------------------------------------------------------------------
 */

static void view_real_removed(ViewWindow *vw, const gchar *path, GList *ignore_list)
{
	ImageWindow *imd;
	const gchar *image_path;

	imd = view_window_active_image(vw);
	image_path = image_get_path(imd);

	if (image_path && strcmp(image_path, path) == 0)
		{
		if (vw->list)
			{
			view_list_step(vw, TRUE);
			if (image_get_path(imd) == image_path)
				{
				view_list_step(vw, FALSE);
				}
			}
		else if (view_window_contains_collection(vw))
			{
			view_collection_step(vw, TRUE);
			if (image_get_path(imd) == image_path)
				{
				view_collection_step(vw, FALSE);
				}
			}
		if (image_get_path(imd) == image_path)
			{
			image_change_path(imd, NULL, image_zoom_get_default(imd, zoom_mode));
			}
		}

	if (vw->list)
		{
		GList *work;
		GList *old;

		old = vw->list_pointer;

		work = vw->list;
		while (work)
			{
			gchar *chk_path;
			GList *chk_link;

			chk_path = work->data;
			chk_link = work;
			work = work->next;

			if (strcmp(chk_path, path) == 0)
				{
				if (vw->list_pointer == chk_link)
					{
					vw->list_pointer = (chk_link->next) ? chk_link->next : chk_link->prev;
					}
				vw->list = g_list_remove(vw->list, chk_path);
				g_free(chk_path);
				}
			}

		/* handles stepping correctly when same image is in the list more than once */
		if (old && old != vw->list_pointer)
			{
			gchar *path;

			if (vw->list_pointer)
				{
				path = vw->list_pointer->data;
				}
			else
				{
				path = NULL;
				}

			image_change_path(imd, path, image_zoom_get_default(imd, zoom_mode));
			}
		}

	image_osd_update(imd);
}

static void view_real_moved(ViewWindow *vw, const gchar *source, const gchar *dest)
{
	ImageWindow *imd;
	const gchar *image_path;

	imd = view_window_active_image(vw);
	image_path = image_get_path(imd);

	if (image_path && strcmp(image_path, source) == 0)
		{
		image_set_path(imd, dest);
		}

	if (vw->list)
		{
		GList *work;
		work = vw->list;
		while (work)
			{
			gchar *chk_path;

			chk_path = work->data;

			if (strcmp(chk_path, source) == 0)
				{
				work->data = g_strdup(dest);
				g_free(chk_path);
				}

			work = work->next;
			}
		}
}

void view_window_maint_removed(const gchar *path, GList *ignore_list)
{
	GList *work = view_window_list;
	while (work)
		{
		ViewWindow *vw = work->data;
		work = work->next;

		view_real_removed(vw, path, ignore_list);
		}
}

void view_window_maint_moved(const gchar *source, const gchar *dest)
{
	GList *work = view_window_list;
	while (work)
		{
		ViewWindow *vw = work->data;
		work = work->next;

		view_real_moved(vw, source, dest);
		}
}

