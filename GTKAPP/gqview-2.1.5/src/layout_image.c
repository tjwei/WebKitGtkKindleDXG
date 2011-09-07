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
#include "layout_image.h"

#include "collect.h"
#include "dnd.h"
#include "editors.h"
#include "filelist.h"
#include "fullscreen.h"
#include "image.h"
#include "image-overlay.h"
#include "img-view.h"
#include "info.h"
#include "layout.h"
#include "layout_util.h"
#include "menu.h"
#include "pixbuf_util.h"
#include "utilops.h"
#include "slideshow.h"
#include "ui_bookmark.h"
#include "ui_fileops.h"
#include "ui_menu.h"

#include <gdk/gdkkeysyms.h> /* for keyboard values */


static GtkWidget *layout_image_pop_menu(LayoutWindow *lw);
static void layout_image_set_buttons(LayoutWindow *lw);

/*
 *----------------------------------------------------------------------------
 * full screen overlay
 *----------------------------------------------------------------------------
 */

void layout_image_overlay_toggle(LayoutWindow *lw)
{
	if (image_osd_get(lw->image, NULL, NULL))
		{
		image_osd_set(lw->image, FALSE, FALSE);
		}
	else
		{
		image_osd_set(lw->image, (lw->full_screen != NULL), TRUE);
		image_osd_icon(lw->image, IMAGE_OSD_ICON, -1);
		}
}

void layout_image_overlay_update(LayoutWindow *lw)
{
	if (!lw) return;

	image_osd_update(lw->image);
}

/*
 *----------------------------------------------------------------------------
 * full screen
 *----------------------------------------------------------------------------
 */

static void layout_image_fullscreen_menu_pos_cb(GtkMenu *menu, gint *x, gint *y, gboolean *push_in, gpointer data)
{
	LayoutWindow *lw = data;

	if (!lw->full_screen) return;

	gdk_window_get_origin(lw->full_screen->imd->pr->window, x, y);
	popup_menu_position_clamp(menu, x, y, 0);
}

static void layout_image_full_screen_menu_popup(LayoutWindow *lw)
{
	GtkWidget *menu;

	menu = layout_image_pop_menu(lw);
	gtk_menu_popup(GTK_MENU(menu), NULL, NULL, layout_image_fullscreen_menu_pos_cb, lw, 0, GDK_CURRENT_TIME);
}

static gint layout_image_full_screen_key_press_cb(GtkWidget *widget, GdkEventKey *event, gpointer data)
{
	LayoutWindow *lw = data;
	gint stop_signal;
	gint x = 0;
	gint y = 0;

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
		layout_image_scroll(lw, x, y);
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
				file_util_copy(layout_image_get_path(lw), NULL, NULL, widget);
				break;
			case 'M': case 'm':
				file_util_move(layout_image_get_path(lw), NULL, NULL, widget);
				break;
			case 'R': case 'r':
				file_util_rename(layout_image_get_path(lw), NULL, widget);
				break;
			case 'D': case 'd':
				file_util_delete(layout_image_get_path(lw), NULL, widget);
				break;
			case 'P': case 'p':
				info_window_new(layout_image_get_path(lw), NULL);
				break;
			case 'Q': case 'q':
				exit_gqview();
				return FALSE;
				break;
			default:
				stop_signal = FALSE;
				break;
			}
		if (n != -1)
			{
			if (!editor_window_flag_set(n))
				{
				layout_image_full_screen_stop(lw);
				}
			start_editor_from_file(n, layout_image_get_path(lw));
			}
		}
	else if (event->state & GDK_SHIFT_MASK)
		{
		stop_signal = TRUE;
		switch (event->keyval)
			{
			case 'R': case 'r':
				layout_image_alter(lw, ALTER_ROTATE_180);
				break;
			case 'M': case 'm':
				layout_image_alter(lw, ALTER_MIRROR);
				break;
			case 'F': case 'f':
				layout_image_alter(lw, ALTER_FLIP);
				break;
			case 'G': case 'g':
				layout_image_alter(lw, ALTER_DESATURATE);
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
			case '+': case '=': case GDK_KP_Add:
				layout_image_zoom_adjust(lw, get_zoom_increment());
				break;
			case '-': case GDK_KP_Subtract:
				layout_image_zoom_adjust(lw, -get_zoom_increment());
				break;
			case 'X': case 'x': case GDK_KP_Multiply:
				layout_image_zoom_set(lw, 0.0);
				break;
			case 'Z': case 'z': case GDK_KP_Divide:
			case '1':
				layout_image_zoom_set(lw, 1.0);
				break;
			case '2':
				layout_image_zoom_set(lw, 2.0);
				break;
			case '3':
				layout_image_zoom_set(lw, 3.0);
				break;
			case '4':
				layout_image_zoom_set(lw, 4.0);
				break;
			case '7':
				layout_image_zoom_set(lw, -4.0);
				break;
			case '8':
				layout_image_zoom_set(lw, -3.0);
				break;
			case '9':
				layout_image_zoom_set(lw, -2.0);
				break;
			case 'W': case 'w':
				layout_image_zoom_set_fill_geometry(lw, FALSE);
				break;
			case 'H': case 'h':
				layout_image_zoom_set_fill_geometry(lw, TRUE);
				break;
			case GDK_Page_Up: case GDK_KP_Page_Up:
			case GDK_BackSpace:
			case 'B': case 'b':
				layout_image_prev(lw);
				break;
			case GDK_Page_Down: case GDK_KP_Page_Down:
			case GDK_space:
			case 'N': case 'n':
				layout_image_next(lw);
				break;
			case GDK_Home: case GDK_KP_Home:
				layout_image_first(lw);
				break;
			case GDK_End: case GDK_KP_End:
				layout_image_last(lw);
				break;
			case ']':
				layout_image_alter(lw, ALTER_ROTATE_90);
				break;
			case '[':
				layout_image_alter(lw, ALTER_ROTATE_90_CC);
				break;
			case GDK_Delete: case GDK_KP_Delete:
				if (enable_delete_key)
					{
					file_util_delete(layout_image_get_path(lw), NULL, widget);
					}
				break;
			case GDK_Escape:
				layout_image_full_screen_stop(lw);
				break;
			case 'R': case 'r':
				layout_refresh(lw);
				break;
			case 'S': case 's':
				layout_image_slideshow_toggle(lw);
				break;
			case 'P': case 'p':
				layout_image_slideshow_pause_toggle(lw);
				break;
			case 'F': case 'f':
			case 'V': case 'v':
			case GDK_F11:
				layout_image_full_screen_stop(lw);
				break;
			case GDK_Menu:
			case GDK_F10:
				layout_image_full_screen_menu_popup(lw);
				break;
			case 'I': case 'i':
				layout_image_overlay_toggle(lw);
				break;
			default:
				stop_signal = FALSE;
				break;
			}
		}

	return stop_signal;
}

static void layout_image_full_screen_stop_func(FullScreenData *fs, gpointer data)
{
	LayoutWindow *lw = data;

	/* restore image window */
	lw->image = fs->normal_imd;

	if (lw->slideshow)
		{
		lw->slideshow->imd = lw->image;
		}

	lw->full_screen = NULL;
}

void layout_image_full_screen_start(LayoutWindow *lw)
{
	if (!layout_valid(&lw)) return;

	if (lw->full_screen) return;

	lw->full_screen = fullscreen_start(lw->window, lw->image,
					   layout_image_full_screen_stop_func, lw);

	/* set to new image window */
	lw->image = lw->full_screen->imd;

	if (lw->slideshow)
		{
		lw->slideshow->imd = lw->image;
		}

	layout_image_set_buttons(lw);

	g_signal_connect(G_OBJECT(lw->full_screen->window), "key_press_event",
			 G_CALLBACK(layout_image_full_screen_key_press_cb), lw);

#if 0
	gtk_widget_set_sensitive(lw->window, FALSE);
	if (lw->tools) gtk_widget_set_sensitive(lw->tools, FALSE);
#endif

	if (image_osd_get(lw->full_screen->normal_imd, NULL, NULL))
		{
		image_osd_set(lw->image, TRUE, TRUE);
		image_osd_set(lw->full_screen->normal_imd, FALSE, FALSE);
		}
}

void layout_image_full_screen_stop(LayoutWindow *lw)
{
	if (!layout_valid(&lw)) return;
	if (!lw->full_screen) return;

	if (image_osd_get(lw->image, NULL, NULL))
		{
		image_osd_set(lw->full_screen->normal_imd, FALSE, TRUE);
		}
	fullscreen_stop(lw->full_screen);

#if 0
	gtk_widget_set_sensitive(lw->window, TRUE);
	if (lw->tools) gtk_widget_set_sensitive(lw->tools, TRUE);
#endif
}

void layout_image_full_screen_toggle(LayoutWindow *lw)
{
	if (!layout_valid(&lw)) return;
	if (lw->full_screen)
		{
		layout_image_full_screen_stop(lw);
		}
	else
		{
		layout_image_full_screen_start(lw);
		}
}

gint layout_image_full_screen_active(LayoutWindow *lw)
{
	if (!layout_valid(&lw)) return FALSE;

	return (lw->full_screen != NULL);
}

/*
 *----------------------------------------------------------------------------
 * slideshow
 *----------------------------------------------------------------------------
 */

static void layout_image_slideshow_next(LayoutWindow *lw)
{
	if (lw->slideshow) slideshow_next(lw->slideshow);
}

static void layout_image_slideshow_prev(LayoutWindow *lw)
{
	if (lw->slideshow) slideshow_prev(lw->slideshow);
}

static void layout_image_slideshow_stop_func(SlideShowData *ss, gpointer data)
{
	LayoutWindow *lw = data;

	lw->slideshow = NULL;
	layout_status_update_info(lw, NULL);
}

void layout_image_slideshow_start(LayoutWindow *lw)
{
	CollectionData *cd;
	CollectInfo *info;

	if (!layout_valid(&lw)) return;
	if (lw->slideshow) return;

	cd = image_get_collection(lw->image, &info);

	if (cd && info)
		{
		lw->slideshow = slideshow_start_from_collection(lw->image, cd,
				layout_image_slideshow_stop_func, lw, info);
		}
	else
		{
		lw->slideshow = slideshow_start(lw->image, lw,
				layout_list_get_index(lw, layout_image_get_path(lw)),
				layout_image_slideshow_stop_func, lw);
		}

	layout_status_update_info(lw, NULL);
}

/* note that slideshow will take ownership of the list, do not free it */
void layout_image_slideshow_start_from_list(LayoutWindow *lw, GList *list)
{
	if (!layout_valid(&lw)) return;

	if (lw->slideshow || !list)
		{
		path_list_free(list);
		return;
		}

	lw->slideshow = slideshow_start_from_path_list(lw->image, list,
						       layout_image_slideshow_stop_func, lw);

	layout_status_update_info(lw, NULL);
}

void layout_image_slideshow_stop(LayoutWindow *lw)
{
	if (!layout_valid(&lw)) return;

	if (!lw->slideshow) return;

	slideshow_free(lw->slideshow);
	/* the stop_func sets lw->slideshow to NULL for us */
}

void layout_image_slideshow_toggle(LayoutWindow *lw)
{
	if (!layout_valid(&lw)) return;

	if (lw->slideshow)
		{
		layout_image_slideshow_stop(lw);
		}
	else
		{
		layout_image_slideshow_start(lw);
		}
}

gint layout_image_slideshow_active(LayoutWindow *lw)
{
	if (!layout_valid(&lw)) return FALSE;

	return (lw->slideshow != NULL);
}

gint layout_image_slideshow_pause_toggle(LayoutWindow *lw)
{
	gint ret;

	if (!layout_valid(&lw)) return FALSE;

	ret = slideshow_pause_toggle(lw->slideshow);

	layout_status_update_info(lw, NULL);

	return ret;
}

gint layout_image_slideshow_paused(LayoutWindow *lw)
{
	if (!layout_valid(&lw)) return FALSE;

	return (slideshow_paused(lw->slideshow));
}

static gint layout_image_slideshow_continue_check(LayoutWindow *lw)
{
	if (!lw->slideshow) return FALSE;

	if (!slideshow_should_continue(lw->slideshow))
		{
		layout_image_slideshow_stop(lw);
		return FALSE;
		}

	return TRUE;
}

/*
 *----------------------------------------------------------------------------
 * pop-up menus
 *----------------------------------------------------------------------------
 */

static void li_pop_menu_zoom_in_cb(GtkWidget *widget, gpointer data)
{
	LayoutWindow *lw = data;

	image_zoom_adjust(lw->image, get_zoom_increment());
}

static void li_pop_menu_zoom_out_cb(GtkWidget *widget, gpointer data)
{
	LayoutWindow *lw = data;
	image_zoom_adjust(lw->image, -get_zoom_increment());
}

static void li_pop_menu_zoom_1_1_cb(GtkWidget *widget, gpointer data)
{
	LayoutWindow *lw = data;

	image_zoom_set(lw->image, 1.0);
}

static void li_pop_menu_zoom_fit_cb(GtkWidget *widget, gpointer data)
{
	LayoutWindow *lw = data;

	image_zoom_set(lw->image, 0.0);
}

static void li_pop_menu_edit_cb(GtkWidget *widget, gpointer data)
{
	LayoutWindow *lw;
	gint n;

	lw = submenu_item_get_data(widget);
	n = GPOINTER_TO_INT(data);

	if (!editor_window_flag_set(n))
		{
		layout_image_full_screen_stop(lw);
		}
	start_editor_from_file(n, layout_image_get_path(lw));
}

static void li_pop_menu_wallpaper_cb(GtkWidget *widget, gpointer data)
{
	LayoutWindow *lw = data;

	layout_image_to_root(lw);
}

static void li_pop_menu_alter_cb(GtkWidget *widget, gpointer data)
{
	LayoutWindow *lw = data;
	AlterType type;

	lw = submenu_item_get_data(widget);
	type = (AlterType)GPOINTER_TO_INT(data);

	image_alter(lw->image, type);
}

static void li_pop_menu_info_cb(GtkWidget *widget, gpointer data)
{
	LayoutWindow *lw = data;

	info_window_new(layout_image_get_path(lw), NULL);
}

static void li_pop_menu_new_cb(GtkWidget *widget, gpointer data)
{
	LayoutWindow *lw = data;

	view_window_new(layout_image_get_path(lw));
}

static GtkWidget *li_pop_menu_click_parent(GtkWidget *widget, LayoutWindow *lw)
{
	GtkWidget *menu;
	GtkWidget *parent;

	menu = gtk_widget_get_toplevel(widget);
	if (!menu) return NULL;

	parent = g_object_get_data(G_OBJECT(menu), "click_parent");

	if (!parent && lw->full_screen)
		{
		parent = lw->full_screen->imd->widget;
		}

	return parent;
}

static void li_pop_menu_copy_cb(GtkWidget *widget, gpointer data)
{
	LayoutWindow *lw = data;

	file_util_copy(layout_image_get_path(lw), NULL, NULL,
		       li_pop_menu_click_parent(widget, lw));
}

static void li_pop_menu_move_cb(GtkWidget *widget, gpointer data)
{
	LayoutWindow *lw = data;

	file_util_move(layout_image_get_path(lw), NULL, NULL,
		       li_pop_menu_click_parent(widget, lw));
}

static void li_pop_menu_rename_cb(GtkWidget *widget, gpointer data)
{
	LayoutWindow *lw = data;

	file_util_rename(layout_image_get_path(lw), NULL,
			 li_pop_menu_click_parent(widget, lw));
}

static void li_pop_menu_delete_cb(GtkWidget *widget, gpointer data)
{
	LayoutWindow *lw = data;

	file_util_delete(layout_image_get_path(lw), NULL,
			 li_pop_menu_click_parent(widget, lw));
}

static void li_pop_menu_slide_start_cb(GtkWidget *widget, gpointer data)
{
	LayoutWindow *lw = data;

	layout_image_slideshow_start(lw);
}

static void li_pop_menu_slide_stop_cb(GtkWidget *widget, gpointer data)
{
	LayoutWindow *lw = data;

	layout_image_slideshow_stop(lw);
}

static void li_pop_menu_slide_pause_cb(GtkWidget *widget, gpointer data)
{
	LayoutWindow *lw = data;

	layout_image_slideshow_pause_toggle(lw);
}

static void li_pop_menu_full_screen_cb(GtkWidget *widget, gpointer data)
{
	LayoutWindow *lw = data;

	layout_image_full_screen_toggle(lw);
}

static void li_pop_menu_hide_cb(GtkWidget *widget, gpointer data)
{
	LayoutWindow *lw = data;

	layout_tools_hide_toggle(lw);
}

static GtkWidget *layout_image_pop_menu(LayoutWindow *lw)
{
	GtkWidget *menu;
	GtkWidget *item;
	GtkWidget *submenu;
	const gchar *path;
	gint fullscreen;

	path = layout_image_get_path(lw);
	fullscreen = layout_image_full_screen_active(lw);

	menu = popup_menu_short_lived();

	menu_item_add_stock(menu, _("Zoom _in"), GTK_STOCK_ZOOM_IN, G_CALLBACK(li_pop_menu_zoom_in_cb), lw);
	menu_item_add_stock(menu, _("Zoom _out"), GTK_STOCK_ZOOM_OUT, G_CALLBACK(li_pop_menu_zoom_out_cb), lw);
	menu_item_add_stock(menu, _("Zoom _1:1"), GTK_STOCK_ZOOM_100, G_CALLBACK(li_pop_menu_zoom_1_1_cb), lw);
	menu_item_add_stock(menu, _("Fit image to _window"), GTK_STOCK_ZOOM_FIT, G_CALLBACK(li_pop_menu_zoom_fit_cb), lw);
	menu_item_add_divider(menu);

	submenu = submenu_add_edit(menu, &item, G_CALLBACK(li_pop_menu_edit_cb), lw);
	if (!path) gtk_widget_set_sensitive(item, FALSE);
	menu_item_add_divider(submenu);
	menu_item_add(submenu, _("Set as _wallpaper"), G_CALLBACK(li_pop_menu_wallpaper_cb), lw);

	item = submenu_add_alter(menu, G_CALLBACK(li_pop_menu_alter_cb), lw);

	item = menu_item_add_stock(menu, _("_Properties"), GTK_STOCK_PROPERTIES, G_CALLBACK(li_pop_menu_info_cb), lw);
	if (!path) gtk_widget_set_sensitive(item, FALSE);

	item = menu_item_add_stock(menu, _("View in _new window"), GTK_STOCK_NEW, G_CALLBACK(li_pop_menu_new_cb), lw);
	if (!path || fullscreen) gtk_widget_set_sensitive(item, FALSE);

	menu_item_add_divider(menu);

	item = menu_item_add_stock(menu, _("_Copy..."), GTK_STOCK_COPY, G_CALLBACK(li_pop_menu_copy_cb), lw);
	if (!path) gtk_widget_set_sensitive(item, FALSE);
	item = menu_item_add(menu, _("_Move..."), G_CALLBACK(li_pop_menu_move_cb), lw);
	if (!path) gtk_widget_set_sensitive(item, FALSE);
	item = menu_item_add(menu, _("_Rename..."), G_CALLBACK(li_pop_menu_rename_cb), lw);
	if (!path) gtk_widget_set_sensitive(item, FALSE);
	item = menu_item_add_stock(menu, _("_Delete..."), GTK_STOCK_DELETE, G_CALLBACK(li_pop_menu_delete_cb), lw);
	if (!path) gtk_widget_set_sensitive(item, FALSE);

	menu_item_add_divider(menu);

	if (layout_image_slideshow_active(lw))
		{
		menu_item_add(menu, _("_Stop slideshow"), G_CALLBACK(li_pop_menu_slide_stop_cb), lw);
		if (layout_image_slideshow_paused(lw))
			{
			item = menu_item_add(menu, _("Continue slides_how"),
					     G_CALLBACK(li_pop_menu_slide_pause_cb), lw);
			}
		else
			{
			item = menu_item_add(menu, _("Pause slides_how"),
					     G_CALLBACK(li_pop_menu_slide_pause_cb), lw);
			}
		}
	else
                {
		menu_item_add(menu, _("_Start slideshow"), G_CALLBACK(li_pop_menu_slide_start_cb), lw);
		item = menu_item_add(menu, _("Pause slides_how"), G_CALLBACK(li_pop_menu_slide_pause_cb), lw);
		gtk_widget_set_sensitive(item, FALSE);
		}

	if (!fullscreen)
		{
		menu_item_add(menu, _("_Full screen"), G_CALLBACK(li_pop_menu_full_screen_cb), lw);
		}
	else
		{
		menu_item_add(menu, _("Exit _full screen"), G_CALLBACK(li_pop_menu_full_screen_cb), lw);
		}

	menu_item_add_divider(menu);

	item = menu_item_add_check(menu, _("Hide file _list"), lw->tools_hidden,
				   G_CALLBACK(li_pop_menu_hide_cb), lw);
	if (fullscreen) gtk_widget_set_sensitive(item, FALSE);

	return menu;
}

static void layout_image_menu_pos_cb(GtkMenu *menu, gint *x, gint *y, gboolean *push_in, gpointer data)
{
	LayoutWindow *lw = data;

	gdk_window_get_origin(lw->image->pr->window, x, y);
	popup_menu_position_clamp(menu, x, y, 0);
}

void layout_image_menu_popup(LayoutWindow *lw)
{
	GtkWidget *menu;

	menu = layout_image_pop_menu(lw);
	gtk_menu_popup(GTK_MENU(menu), NULL, NULL, layout_image_menu_pos_cb, lw, 0, GDK_CURRENT_TIME);
}

/*
 *----------------------------------------------------------------------------
 * dnd
 *----------------------------------------------------------------------------
 */

static void layout_image_dnd_receive(GtkWidget *widget, GdkDragContext *context,
				     gint x, gint y,
				     GtkSelectionData *selection_data, guint info,
				     guint time, gpointer data)
{
	LayoutWindow *lw = data;

	if (info == TARGET_URI_LIST || info == TARGET_APP_COLLECTION_MEMBER)
		{
		CollectionData *source;
		GList *list;
		GList *info_list;

		if (info == TARGET_URI_LIST)
			{
			list = uri_list_from_text((gchar *)selection_data->data, TRUE);
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
				gchar *base;
				gint row;

				base = remove_level_from_path(path);
				if (strcmp(base, layout_get_path(lw)) != 0)
					{
					layout_set_path(lw, base);
					}
				g_free(base);

				row = layout_list_get_index(lw, path);
				if (source && info_list)
					{
					layout_image_set_collection(lw, source, info_list->data);
					}
				else if (row == -1)
					{
					layout_image_set_path(lw, path);
					}
				else
					{
					layout_image_set_index(lw, row);
					}
				}
			else if (isdir(path))
				{
				layout_set_path(lw, path);
				layout_image_set_path(lw, NULL);
				}
			}

		path_list_free(list);
		g_list_free(info_list);
		}
}

static void layout_image_dnd_get(GtkWidget *widget, GdkDragContext *context,
				 GtkSelectionData *selection_data, guint info,
				 guint time, gpointer data)
{
	LayoutWindow *lw = data;
	const gchar *path;

	path = layout_image_get_path(lw);

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

static void layout_image_dnd_end(GtkWidget *widget, GdkDragContext *context, gpointer data)
{
	LayoutWindow *lw = data;
	if (context->action == GDK_ACTION_MOVE)
		{
		const gchar *path;
		gint row;

		path = layout_image_get_path(lw);
		row = layout_list_get_index(lw, path);
		if (row < 0) return;

		if (!isfile(path))
			{
			if (row < layout_list_count(lw, NULL) - 1)
				{
				layout_image_next(lw);
				}
			else
				{
				layout_image_prev(lw);
				}
			}
		layout_refresh(lw);
		}
}

static void layout_image_dnd_init(LayoutWindow *lw)
{
	gtk_drag_source_set(lw->image->pr, GDK_BUTTON2_MASK,
			    dnd_file_drag_types, dnd_file_drag_types_count,
			    GDK_ACTION_COPY | GDK_ACTION_MOVE | GDK_ACTION_LINK);
	g_signal_connect(G_OBJECT(lw->image->pr), "drag_data_get",
			 G_CALLBACK(layout_image_dnd_get), lw);
	g_signal_connect(G_OBJECT(lw->image->pr), "drag_end",
			 G_CALLBACK(layout_image_dnd_end), lw);

	gtk_drag_dest_set(lw->image->pr,
			  GTK_DEST_DEFAULT_MOTION | GTK_DEST_DEFAULT_DROP,
			  dnd_file_drop_types, dnd_file_drop_types_count,
                          GDK_ACTION_COPY | GDK_ACTION_MOVE | GDK_ACTION_LINK);
	g_signal_connect(G_OBJECT(lw->image->pr), "drag_data_received",
			 G_CALLBACK(layout_image_dnd_receive), lw);
}


/*
 *----------------------------------------------------------------------------
 * misc
 *----------------------------------------------------------------------------
 */

void layout_image_to_root(LayoutWindow *lw)
{
	image_to_root_window(lw->image, (image_zoom_get(lw->image) == 0));
}

/*
 *----------------------------------------------------------------------------
 * manipulation + accessors
 *----------------------------------------------------------------------------
 */

void layout_image_scroll(LayoutWindow *lw, gint x, gint y)
{
	if (!layout_valid(&lw)) return;

	image_scroll(lw->image, x, y);
}

void layout_image_zoom_adjust(LayoutWindow *lw, gdouble increment)
{
	if (!layout_valid(&lw)) return;

	image_zoom_adjust(lw->image, increment);
}

void layout_image_zoom_set(LayoutWindow *lw, gdouble zoom)
{
	if (!layout_valid(&lw)) return;

	image_zoom_set(lw->image, zoom);
}

void layout_image_zoom_set_fill_geometry(LayoutWindow *lw, gint vertical)
{
	if (!layout_valid(&lw)) return;

	image_zoom_set_fill_geometry(lw->image, vertical);
}

void layout_image_alter(LayoutWindow *lw, AlterType type)
{
	if (!layout_valid(&lw)) return;

	image_alter(lw->image, type);
}

const gchar *layout_image_get_path(LayoutWindow *lw)
{
	if (!layout_valid(&lw)) return NULL;

	return image_get_path(lw->image);
}

const gchar *layout_image_get_name(LayoutWindow *lw)
{
	if (!layout_valid(&lw)) return NULL;

	return image_get_name(lw->image);
}

CollectionData *layout_image_get_collection(LayoutWindow *lw, CollectInfo **info)
{
	if (!layout_valid(&lw)) return NULL;

	return image_get_collection(lw->image, info);
}

gint layout_image_get_index(LayoutWindow *lw)
{
	return layout_list_get_index(lw, image_get_path(lw->image));
}

/*
 *----------------------------------------------------------------------------
 * image changers
 *----------------------------------------------------------------------------
 */

void layout_image_set_path(LayoutWindow *lw, const gchar *path)
{
	if (!layout_valid(&lw)) return;

	image_change_path(lw->image, path, image_zoom_get_default(lw->image, zoom_mode));

	layout_list_sync_path(lw, path);
	layout_image_slideshow_continue_check(lw);
	layout_bars_new_image(lw);
}

void layout_image_set_with_ahead(LayoutWindow *lw, const gchar *path, const gchar *read_ahead_path)
{
	if (!layout_valid(&lw)) return;

	if (path)
		{
		const gchar *old_path;

		old_path = layout_image_get_path(lw);
		if (old_path && strcmp(path, old_path) == 0) return;
		}

	layout_image_set_path(lw, path);
	if (enable_read_ahead) image_prebuffer_set(lw->image, read_ahead_path);
}

void layout_image_set_index(LayoutWindow *lw, gint index)
{
	const gchar *path;
	const gchar *read_ahead_path;
	gint old;

	if (!layout_valid(&lw)) return;

	old = layout_list_get_index(lw, layout_image_get_path(lw));
	path = layout_list_get_path(lw, index);

	if (old > index)
		{
		read_ahead_path = layout_list_get_path(lw, index - 1);
		}
	else
		{
		read_ahead_path = layout_list_get_path(lw, index + 1);
		}

	layout_image_set_with_ahead(lw, path, read_ahead_path);
}

static void layout_image_set_collection_real(LayoutWindow *lw, CollectionData *cd, CollectInfo *info, gint forward)
{
	if (!layout_valid(&lw)) return;

	image_change_from_collection(lw->image, cd, info, image_zoom_get_default(lw->image, zoom_mode));
	if (enable_read_ahead)
		{
		CollectInfo *r_info;
		if (forward)
			{
			r_info = collection_next_by_info(cd, info);
			if (!r_info) r_info = collection_prev_by_info(cd, info);
			}
		else
			{
			r_info = collection_prev_by_info(cd, info);
			if (!r_info) r_info = collection_next_by_info(cd, info);
			}
		if (r_info) image_prebuffer_set(lw->image, r_info->path);
		}

	layout_image_slideshow_continue_check(lw);
	layout_bars_new_image(lw);
}

void layout_image_set_collection(LayoutWindow *lw, CollectionData *cd, CollectInfo *info)
{
	layout_image_set_collection_real(lw, cd, info, TRUE);
	layout_list_sync_path(lw, layout_image_get_path(lw));
}

void layout_image_refresh(LayoutWindow *lw)
{
	if (!layout_valid(&lw)) return;

	image_reload(lw->image);
}

void layout_image_color_profile_set(LayoutWindow *lw,
				    gint input_type, gint screen_type,
				    gint use_image)
{
	if (!layout_valid(&lw)) return;

	image_color_profile_set(lw->image, input_type, screen_type, use_image);
}

gint layout_image_color_profile_get(LayoutWindow *lw,
				    gint *input_type, gint *screen_type,
				    gint *use_image)
{
	if (!layout_valid(&lw)) return FALSE;

	return image_color_profile_get(lw->image, input_type, screen_type, use_image);
}

void layout_image_color_profile_set_use(LayoutWindow *lw, gint enable)
{
	if (!layout_valid(&lw)) return;

	image_color_profile_set_use(lw->image, enable);

	if (lw->info_color)
		{
#ifndef HAVE_LCMS
		enable = FALSE;
#endif
		gtk_widget_set_sensitive(GTK_BIN(lw->info_color)->child, enable);
		}
}

gint layout_image_color_profile_get_use(LayoutWindow *lw)
{
	if (!layout_valid(&lw)) return FALSE;

	return image_color_profile_get_use(lw->image);
}

/*
 *----------------------------------------------------------------------------
 * list walkers
 *----------------------------------------------------------------------------
 */

void layout_image_next(LayoutWindow *lw)
{
	gint current;
	CollectionData *cd;
	CollectInfo *info;

	if (!layout_valid(&lw)) return;

	if (layout_image_slideshow_active(lw))
		{
		layout_image_slideshow_next(lw);
		return;
		}

	cd = image_get_collection(lw->image, &info);

	if (cd && info)
		{
		info = collection_next_by_info(cd, info);
		if (info)
			{
			layout_image_set_collection_real(lw, cd, info, TRUE);
			}
		else
			{
			image_osd_icon(lw->image, IMAGE_OSD_LAST, -1);
			}
		return;
		}

	current = layout_image_get_index(lw);

	if (current >= 0)
		{
		if (current < layout_list_count(lw, NULL) - 1)
			{
			layout_image_set_index(lw, current + 1);
			}
		else
			{
			image_osd_icon(lw->image, IMAGE_OSD_LAST, -1);
			}
		}
	else
		{
		layout_image_set_index(lw, 0);
		}
}

void layout_image_prev(LayoutWindow *lw)
{
	gint current;
	CollectionData *cd;
	CollectInfo *info;

	if (!layout_valid(&lw)) return;

	if (layout_image_slideshow_active(lw))
		{
		layout_image_slideshow_prev(lw);
		return;
		}

	cd = image_get_collection(lw->image, &info);

	if (cd && info)
		{
		info = collection_prev_by_info(cd, info);
		if (info)
			{
			layout_image_set_collection_real(lw, cd, info, FALSE);
			}
		else
			{
			image_osd_icon(lw->image, IMAGE_OSD_FIRST, -1);
			}
		return;
		}

	current = layout_image_get_index(lw);

	if (current >= 0)
		{
		if (current > 0)
			{
			layout_image_set_index(lw, current - 1);
			}
		else
			{
			image_osd_icon(lw->image, IMAGE_OSD_FIRST, -1);
			}
		}
	else
		{
		layout_image_set_index(lw, layout_list_count(lw, NULL) - 1);
		}
}

void layout_image_first(LayoutWindow *lw)
{
	gint current;
	CollectionData *cd;
	CollectInfo *info;

	if (!layout_valid(&lw)) return;

	cd = image_get_collection(lw->image, &info);

	if (cd && info)
		{
		CollectInfo *new;
		new = collection_get_first(cd);
		if (new != info) layout_image_set_collection_real(lw, cd, new, TRUE);
		return;
		}

	current = layout_image_get_index(lw);
	if (current != 0 && layout_list_count(lw, NULL) > 0)
		{
		layout_image_set_index(lw, 0);
		}
}

void layout_image_last(LayoutWindow *lw)
{
	gint current;
	gint count;
	CollectionData *cd;
	CollectInfo *info;

	if (!layout_valid(&lw)) return;

	cd = image_get_collection(lw->image, &info);

	if (cd && info)
		{
		CollectInfo *new;
		new = collection_get_last(cd);
		if (new != info) layout_image_set_collection_real(lw, cd, new, FALSE);
		return;
		}

	current = layout_image_get_index(lw);
	count = layout_list_count(lw, NULL);
	if (current != count - 1 && count > 0)
		{
		layout_image_set_index(lw, count - 1);
		}
}

/*
 *----------------------------------------------------------------------------
 * mouse callbacks
 *----------------------------------------------------------------------------
 */

static void layout_image_button_cb(ImageWindow *imd, gint button, guint32 time,
				   gdouble x, gdouble y, guint state, gpointer data)
{
	LayoutWindow *lw = data;
	GtkWidget *menu;

	switch (button)
		{
		case 1:
			layout_image_next(lw);
			break;
		case 2:
			layout_image_prev(lw);
			break;
		case 3:
			menu = layout_image_pop_menu(lw);
			if (imd == lw->image)
				{
				g_object_set_data(G_OBJECT(menu), "click_parent", imd->widget);
				}
			gtk_menu_popup(GTK_MENU(menu), NULL, NULL, NULL, NULL, 3, time);
			break;
		default:
			break;
		}
}

static void layout_image_scroll_cb(ImageWindow *imd, GdkScrollDirection direction, guint32 time,
				   gdouble x, gdouble y, guint state, gpointer data)
{
	LayoutWindow *lw = data;

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
				layout_image_prev(lw);
				break;
			case GDK_SCROLL_DOWN:
				layout_image_next(lw);
				break;
			default:
				break;
			}
		}
}

static void layout_image_set_buttons(LayoutWindow *lw)
{
	image_set_button_func(lw->image, layout_image_button_cb, lw);
	image_set_scroll_func(lw->image, layout_image_scroll_cb, lw);
}

/*
 *----------------------------------------------------------------------------
 * setup
 *----------------------------------------------------------------------------
 */

static void layout_image_update_cb(ImageWindow *imd, gpointer data)
{
	LayoutWindow *lw = data;
	layout_status_update_image(lw);
}

GtkWidget *layout_image_new(LayoutWindow *lw, const gchar *path)
{
	if (!lw->image) 
		{
		lw->image = image_new( (!lw->tools_float && !lw->tools_hidden) );
		if (black_window_background) image_background_set_black(lw->image, TRUE);
		image_set_update_func(lw->image, layout_image_update_cb, lw);
		layout_image_set_buttons(lw);
		layout_image_dnd_init(lw);

		image_attach_window(lw->image, lw->window, NULL, "GQview", FALSE);

		image_auto_refresh(lw->image, 0);

		image_color_profile_set(lw->image,
					color_profile_input_type, color_profile_screen_type,
					color_profile_use_image);
		image_color_profile_set_use(lw->image, color_profile_enabled);
		}

	return lw->image->widget;
}

/*
 *-----------------------------------------------------------------------------
 * maintenance (for rename, move, remove)
 *-----------------------------------------------------------------------------
 */

void layout_image_maint_renamed(LayoutWindow *lw, const gchar *source, const gchar *dest)
{
	const gchar *img_path;

	img_path = layout_image_get_path(lw);
	if (img_path && strcmp(img_path, source) == 0)
		{
		image_set_path(lw->image, dest);
		layout_bars_maint_renamed(lw);
		}
}

void layout_image_maint_removed(LayoutWindow *lw, const gchar *path)
{
	const gchar *img_path;

	img_path = layout_image_get_path(lw);
	if (img_path && strcmp(img_path, path) == 0)
		{
		CollectionData *cd;
		CollectInfo *info;

		cd = image_get_collection(lw->image, &info);
		if (cd && info)
			{
			CollectInfo *new;

			new = collection_next_by_info(cd, info);
			if (!new) new = collection_prev_by_info(cd, info);

			if (new)
				{
				layout_image_set_collection(lw, cd, new);
				return;
				}
			}

		layout_image_set_path(lw, NULL);
		}
}

void layout_image_maint_moved(LayoutWindow *lw, const gchar *source, const gchar *dest)
{
	layout_image_maint_renamed(lw, source, dest);
}

