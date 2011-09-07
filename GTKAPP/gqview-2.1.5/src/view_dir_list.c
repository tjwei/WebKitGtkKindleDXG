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
#include "view_dir_list.h"

#include "dnd.h"
#include "dupe.h"
#include "filelist.h"
#include "layout.h"
#include "layout_image.h"
#include "layout_util.h"
#include "utilops.h"
#include "ui_bookmark.h"
#include "ui_fileops.h"
#include "ui_menu.h"
#include "ui_tree_edit.h"

#include <gdk/gdkkeysyms.h> /* for keyboard values */


#define VDLIST_PAD 4


enum {
	DIR_COLUMN_POINTER = 0,
	DIR_COLUMN_ICON,
	DIR_COLUMN_NAME,
	DIR_COLUMN_COLOR,
	DIR_COLUMN_COUNT
};


static void vdlist_popup_destroy_cb(GtkWidget *widget, gpointer data);
static gint vdlist_auto_scroll_notify_cb(GtkWidget *widget, gint x, gint y, gpointer data);

/*
 *-----------------------------------------------------------------------------
 * misc
 *-----------------------------------------------------------------------------
 */

static gint vdlist_find_row(ViewDirList *vdl, FileData *fd, GtkTreeIter *iter)
{
	GtkTreeModel *store;
	gint valid;
	gint row = 0;

	store = gtk_tree_view_get_model(GTK_TREE_VIEW(vdl->listview));
	valid = gtk_tree_model_get_iter_first(store, iter);
	while (valid)
		{
		FileData *fd_n;
		gtk_tree_model_get(GTK_TREE_MODEL(store), iter, DIR_COLUMN_POINTER, &fd_n, -1);
		if (fd_n == fd) return row;

		valid = gtk_tree_model_iter_next(GTK_TREE_MODEL(store), iter);
		row++;
		}

	return -1;
}

static gint vdlist_rename_row_cb(TreeEditData *td, const gchar *old, const gchar *new, gpointer data)
{
	ViewDirList *vdl = data;
	GtkTreeModel *store;
	GtkTreeIter iter;
	FileData *fd;
	gchar *old_path;
	gchar *new_path;
	gchar *base;

	store = gtk_tree_view_get_model(GTK_TREE_VIEW(vdl->listview));
	if (!gtk_tree_model_get_iter(store, &iter, td->path)) return FALSE;
	gtk_tree_model_get(store, &iter, DIR_COLUMN_POINTER, &fd, -1);
	if (!fd) return FALSE;
	
	old_path = g_strdup(fd->path);

	base = remove_level_from_path(old_path);
	new_path = concat_dir_and_file(base, new);
	g_free(base);

	if (file_util_rename_dir(old_path, new_path, vdl->listview))
		{
		if (vdl->layout && strcmp(vdl->path, old_path) == 0)
			{
			layout_set_path(vdl->layout, new_path);
			}
		else
			{
			vdlist_refresh(vdl);
			}
		}

	g_free(old_path);
	g_free(new_path);
	return FALSE;
}

static void vdlist_rename_by_row(ViewDirList *vdl, FileData *fd)
{
	GtkTreeModel *store;
	GtkTreePath *tpath;
	GtkTreeIter iter;

	if (vdlist_find_row(vdl, fd, &iter) < 0) return;
	store = gtk_tree_view_get_model(GTK_TREE_VIEW(vdl->listview));
	tpath = gtk_tree_model_get_path(store, &iter);

	tree_edit_by_path(GTK_TREE_VIEW(vdl->listview), tpath, 0, fd->name,
			  vdlist_rename_row_cb, vdl);
	gtk_tree_path_free(tpath);
}

static FileData *vdlist_row_by_path(ViewDirList *vdl, const gchar *path, gint *row)
{
	GList *work;
	gint n;

	if (!path)
		{
		if (row) *row = -1;
		return NULL;
		}

	n = 0;
	work = vdl->list;
	while (work)
		{
		FileData *fd = work->data;
		if (strcmp(fd->path, path) == 0)
			{
			if (row) *row = n;
			return fd;
			}
		work = work->next;
		n++;
		}

	if (row) *row = -1;
	return NULL;
}

static void vdlist_color_set(ViewDirList *vdl, FileData *fd, gint color_set)
{
	GtkTreeModel *store;
	GtkTreeIter iter;

	if (vdlist_find_row(vdl, fd, &iter) < 0) return;
	store = gtk_tree_view_get_model(GTK_TREE_VIEW(vdl->listview));
	gtk_list_store_set(GTK_LIST_STORE(store), &iter, DIR_COLUMN_COLOR, color_set, -1);
}

/*
 *-----------------------------------------------------------------------------
 * drop menu (from dnd)
 *-----------------------------------------------------------------------------
 */

static void vdlist_drop_menu_copy_cb(GtkWidget *widget, gpointer data)
{
	ViewDirList *vdl = data;
	const gchar *path;
	GList *list;

	if (!vdl->drop_fd) return;

	path = vdl->drop_fd->path;
	list = vdl->drop_list;
	vdl->drop_list = NULL;

	file_util_copy_simple(list, path);
}

static void vdlist_drop_menu_move_cb(GtkWidget *widget, gpointer data)
{
	ViewDirList *vdl = data;
	const gchar *path;
	GList *list;

	if (!vdl->drop_fd) return;

	path = vdl->drop_fd->path;
	list = vdl->drop_list;

	vdl->drop_list = NULL;

	file_util_move_simple(list, path);
}

static GtkWidget *vdlist_drop_menu(ViewDirList *vdl, gint active)
{
	GtkWidget *menu;

	menu = popup_menu_short_lived();
	g_signal_connect(G_OBJECT(menu), "destroy",
			 G_CALLBACK(vdlist_popup_destroy_cb), vdl);

	menu_item_add_stock_sensitive(menu, _("_Copy"), GTK_STOCK_COPY, active,
				      G_CALLBACK(vdlist_drop_menu_copy_cb), vdl);
	menu_item_add_sensitive(menu, _("_Move"), active, G_CALLBACK(vdlist_drop_menu_move_cb), vdl);

	menu_item_add_divider(menu);
	menu_item_add_stock(menu, _("Cancel"), GTK_STOCK_CANCEL, NULL, vdl);

	return menu;
}

/*
 *-----------------------------------------------------------------------------
 * pop-up menu
 *-----------------------------------------------------------------------------
 */ 

static void vdlist_pop_menu_up_cb(GtkWidget *widget, gpointer data)
{
	ViewDirList *vdl = data;
	gchar *path;

	if (!vdl->path || strcmp(vdl->path, "/") == 0) return;
	path = remove_level_from_path(vdl->path);

	if (vdl->select_func)
		{
		vdl->select_func(vdl, path, vdl->select_data);
		}

	g_free(path);
}

static void vdlist_pop_menu_slide_cb(GtkWidget *widget, gpointer data)
{
	ViewDirList *vdl = data;
	gchar *path;

	if (!vdl->layout || !vdl->click_fd) return;

	path = g_strdup(vdl->click_fd->path);

	layout_set_path(vdl->layout, path);
	layout_select_none(vdl->layout);
	layout_image_slideshow_stop(vdl->layout);
	layout_image_slideshow_start(vdl->layout);

	g_free(path);
}

static void vdlist_pop_menu_slide_rec_cb(GtkWidget *widget, gpointer data)
{
	ViewDirList *vdl = data;
	gchar *path;
	GList *list;

	if (!vdl->layout || !vdl->click_fd) return;

	path = g_strdup(vdl->click_fd->path);

	list = path_list_recursive(path);

	layout_image_slideshow_stop(vdl->layout);
	layout_image_slideshow_start_from_list(vdl->layout, list);

	g_free(path);
}

static void vdlist_pop_menu_dupe(ViewDirList *vdl, gint recursive)
{
	DupeWindow *dw;
	const gchar *path;
	GList *list = NULL;

	if (!vdl->click_fd) return;
	path = vdl->click_fd->path;

	if (recursive)
		{
		list = g_list_append(list, g_strdup(path));
		}
	else
		{
		path_list(path, &list, NULL);
		list = path_list_filter(list, FALSE);
		}

	dw = dupe_window_new(DUPE_MATCH_NAME);
	dupe_window_add_files(dw, list, recursive);

	path_list_free(list);
}

static void vdlist_pop_menu_dupe_cb(GtkWidget *widget, gpointer data)
{
	ViewDirList *vdl = data;
	vdlist_pop_menu_dupe(vdl, FALSE);
}

static void vdlist_pop_menu_dupe_rec_cb(GtkWidget *widget, gpointer data)
{
	ViewDirList *vdl = data;
	vdlist_pop_menu_dupe(vdl, TRUE);
}

static void vdlist_pop_menu_new_cb(GtkWidget *widget, gpointer data)
{
	ViewDirList *vdl = data;
	gchar *new_path;
	gchar *buf;

	if (!vdl->path) return;

	buf = concat_dir_and_file(vdl->path, _("new_folder"));
	new_path = unique_filename(buf, NULL, NULL, FALSE);
	g_free(buf);
	if (!new_path) return;

	if (!mkdir_utf8(new_path, 0755))
		{
		gchar *text;

		text = g_strdup_printf(_("Unable to create folder:\n%s"), new_path);
		file_util_warning_dialog(_("Error creating folder"), text, GTK_STOCK_DIALOG_ERROR, vdl->listview);
		g_free(text);
		}
	else
		{
		FileData *fd;

		vdlist_refresh(vdl);
		fd = vdlist_row_by_path(vdl, new_path, NULL);

		vdlist_rename_by_row(vdl, fd);
		}

	g_free(new_path);
}

static void vdlist_pop_menu_rename_cb(GtkWidget *widget, gpointer data)
{
	ViewDirList *vdl = data;

	vdlist_rename_by_row(vdl, vdl->click_fd);
}

static void vdlist_pop_menu_delete_cb(GtkWidget *widget, gpointer data)
{
	ViewDirList *vdl = data;

	if (!vdl->click_fd) return;
	file_util_delete_dir(vdl->click_fd->path, vdl->widget);
}

static void vdlist_pop_menu_tree_cb(GtkWidget *widget, gpointer data)
{
	ViewDirList *vdl = data;

	if (vdl->layout) layout_views_set(vdl->layout, TRUE, vdl->layout->icon_view);
}

static void vdlist_pop_menu_refresh_cb(GtkWidget *widget, gpointer data)
{
	ViewDirList *vdl = data;

	if (vdl->layout) layout_refresh(vdl->layout);
}

static GtkWidget *vdlist_pop_menu(ViewDirList *vdl, FileData *fd)
{
	GtkWidget *menu;
	gint active;

	active = (fd != NULL);

	menu = popup_menu_short_lived();
	g_signal_connect(G_OBJECT(menu), "destroy",
			 G_CALLBACK(vdlist_popup_destroy_cb), vdl);

	menu_item_add_stock_sensitive(menu, _("_Up to parent"), GTK_STOCK_GO_UP,
				      (vdl->path && strcmp(vdl->path, "/") != 0),
				      G_CALLBACK(vdlist_pop_menu_up_cb), vdl);

	menu_item_add_divider(menu);
	menu_item_add_sensitive(menu, _("_Slideshow"), active,
				G_CALLBACK(vdlist_pop_menu_slide_cb), vdl);
	menu_item_add_sensitive(menu, _("Slideshow recursive"), active,
				G_CALLBACK(vdlist_pop_menu_slide_rec_cb), vdl);

	menu_item_add_divider(menu);
	menu_item_add_stock_sensitive(menu, _("Find _duplicates..."), GTK_STOCK_FIND, active,
				      G_CALLBACK(vdlist_pop_menu_dupe_cb), vdl);
	menu_item_add_stock_sensitive(menu, _("Find duplicates recursive..."), GTK_STOCK_FIND, active,
				      G_CALLBACK(vdlist_pop_menu_dupe_rec_cb), vdl);

	menu_item_add_divider(menu);

	/* check using . (always row 0) */
	active = (vdl->path && access_file(vdl->path , W_OK | X_OK));
	menu_item_add_sensitive(menu, _("_New folder..."), active,
				G_CALLBACK(vdlist_pop_menu_new_cb), vdl);

	/* ignore .. and . */
	active = (active && fd &&
		  strcmp(fd->name, ".") != 0 &&
		  strcmp(fd->name, "..") != 0 &&
		  access_file(fd->path, W_OK | X_OK));
	menu_item_add_sensitive(menu, _("_Rename..."), active,
				G_CALLBACK(vdlist_pop_menu_rename_cb), vdl);
	menu_item_add_stock_sensitive(menu, _("_Delete..."), GTK_STOCK_DELETE, active,
				      G_CALLBACK(vdlist_pop_menu_delete_cb), vdl);

	menu_item_add_divider(menu);
	menu_item_add_check(menu, _("View as _tree"), FALSE,
			    G_CALLBACK(vdlist_pop_menu_tree_cb), vdl);
	menu_item_add_stock(menu, _("Re_fresh"), GTK_STOCK_REFRESH,
			    G_CALLBACK(vdlist_pop_menu_refresh_cb), vdl);

	return menu;
}

static void vdlist_popup_destroy_cb(GtkWidget *widget, gpointer data)
{
	ViewDirList *vdl = data;

	vdlist_color_set(vdl, vdl->click_fd, FALSE);
	vdl->click_fd = NULL;
	vdl->popup = NULL;

	vdlist_color_set(vdl, vdl->drop_fd, FALSE);
	path_list_free(vdl->drop_list);
	vdl->drop_list = NULL;
	vdl->drop_fd = NULL;
}

/*
 *-----------------------------------------------------------------------------
 * dnd
 *-----------------------------------------------------------------------------
 */

static GtkTargetEntry vdlist_dnd_drop_types[] = {
	{ "text/uri-list", 0, TARGET_URI_LIST }
};
static gint vdlist_dnd_drop_types_count = 1;

static void vdlist_dest_set(ViewDirList *vdl, gint enable)
{
	if (enable)
		{
		gtk_drag_dest_set(vdl->listview,
				  GTK_DEST_DEFAULT_MOTION | GTK_DEST_DEFAULT_DROP,
				  vdlist_dnd_drop_types, vdlist_dnd_drop_types_count,
				  GDK_ACTION_MOVE | GDK_ACTION_COPY);
		}
	else
		{
		gtk_drag_dest_unset(vdl->listview);
		}
}

static void vdlist_dnd_get(GtkWidget *widget, GdkDragContext *context,
			   GtkSelectionData *selection_data, guint info,
			   guint time, gpointer data)
{
	ViewDirList *vdl = data;
	gchar *path;
	GList *list;
	gchar *text = NULL;
	gint length = 0;

	if (!vdl->click_fd) return;
	path = vdl->click_fd->path;

	switch (info)
		{
		case TARGET_URI_LIST:
		case TARGET_TEXT_PLAIN:
			list = g_list_prepend(NULL, path);
			text = uri_text_from_list(list, &length, (info == TARGET_TEXT_PLAIN));
			g_list_free(list);
			break;
		}
	if (text)
		{
		gtk_selection_data_set (selection_data, selection_data->target,
				8, (guchar *)text, length);
		g_free(text);
		}
}

static void vdlist_dnd_begin(GtkWidget *widget, GdkDragContext *context, gpointer data)
{
	ViewDirList *vdl = data;

	vdlist_color_set(vdl, vdl->click_fd, TRUE);
	vdlist_dest_set(vdl, FALSE);
}

static void vdlist_dnd_end(GtkWidget *widget, GdkDragContext *context, gpointer data)
{
	ViewDirList *vdl = data;

	vdlist_color_set(vdl, vdl->click_fd, FALSE);

	if (context->action == GDK_ACTION_MOVE)
		{
		vdlist_refresh(vdl);
		}
	vdlist_dest_set(vdl, TRUE);
}

static void vdlist_dnd_drop_receive(GtkWidget *widget,
				    GdkDragContext *context, gint x, gint y,
				    GtkSelectionData *selection_data, guint info,
				    guint time, gpointer data)
{
	ViewDirList *vdl = data;
	GtkTreePath *tpath;
	GtkTreeIter iter;
	FileData *fd = NULL;

	vdl->click_fd = NULL;

	if (gtk_tree_view_get_path_at_pos(GTK_TREE_VIEW(widget), x, y,
					  &tpath, NULL, NULL, NULL))
		{
		GtkTreeModel *store;

		store = gtk_tree_view_get_model(GTK_TREE_VIEW(widget));
		gtk_tree_model_get_iter(store, &iter, tpath);
		gtk_tree_model_get(store, &iter, DIR_COLUMN_POINTER, &fd, -1);
		gtk_tree_path_free(tpath);
		}

	if (!fd) return;

	if (info == TARGET_URI_LIST)
		{
		GList *list;
		gint active;

		list = uri_list_from_text((gchar *)selection_data->data, TRUE);
		if (!list) return;

		active = access_file(fd->path, W_OK | X_OK);

		vdlist_color_set(vdl, fd, TRUE);
		vdl->popup = vdlist_drop_menu(vdl, active);
		gtk_menu_popup(GTK_MENU(vdl->popup), NULL, NULL, NULL, NULL, 0, time);

		vdl->drop_fd = fd;
		vdl->drop_list = list;
		}
}

#if 0
static gint vdlist_get_row_visibility(ViewDirList *vdl, FileData *fd)
{
	GtkTreeModel *store;
	GtkTreeViewColumn *column;
	GtkTreePath *tpath;
	GtkTreeIter iter;

	GdkRectangle vrect;
	GdkRectangle crect;

	if (!fd || vdlist_find_row(vdl, fd, &iter) < 0) return 0;

	column = gtk_tree_view_get_column(GTK_TREE_VIEW(vdl->listview), 0);
	store = gtk_tree_view_get_model(GTK_TREE_VIEW(vdl->listview));
	tpath = gtk_tree_model_get_path(store, &iter);

	gtk_tree_view_get_visible_rect(GTK_TREE_VIEW(vdl->listview), &vrect);
	gtk_tree_view_get_cell_area(GTK_TREE_VIEW(vdl->listview), tpath, column, &crect);
printf("window: %d + %d; cell: %d + %d\n", vrect.y, vrect.height, crect.y, crect.height);
	gtk_tree_path_free(tpath);

	if (crect.y + crect.height < vrect.y) return -1;
	if (crect.y > vrect.y + vrect.height) return 1;
	return 0;
}
#endif

static void vdlist_scroll_to_row(ViewDirList *vdl, FileData *fd, gfloat y_align)
{
	GtkTreeIter iter;

	if (GTK_WIDGET_REALIZED(vdl->listview) &&
	    vdlist_find_row(vdl, fd, &iter) >= 0)
		{
		GtkTreeModel *store;
		GtkTreePath *tpath;

		store = gtk_tree_view_get_model(GTK_TREE_VIEW(vdl->listview));
		tpath = gtk_tree_model_get_path(store, &iter);
		gtk_tree_view_scroll_to_cell(GTK_TREE_VIEW(vdl->listview), tpath, NULL, TRUE, y_align, 0.0);
		gtk_tree_view_set_cursor(GTK_TREE_VIEW(vdl->listview), tpath, NULL, FALSE);
		gtk_tree_path_free(tpath);

		if (!GTK_WIDGET_HAS_FOCUS(vdl->listview)) gtk_widget_grab_focus(vdl->listview);
		}
}

static void vdlist_drop_update(ViewDirList *vdl, gint x, gint y)
{
	GtkTreePath *tpath;
	GtkTreeIter iter;
	FileData *fd = NULL;

	if (gtk_tree_view_get_path_at_pos(GTK_TREE_VIEW(vdl->listview), x, y,
					  &tpath, NULL, NULL, NULL))
		{
		GtkTreeModel *store;

		store = gtk_tree_view_get_model(GTK_TREE_VIEW(vdl->listview));
		gtk_tree_model_get_iter(store, &iter, tpath);
		gtk_tree_model_get(store, &iter, DIR_COLUMN_POINTER, &fd, -1);
		gtk_tree_path_free(tpath);
		}

	if (fd != vdl->drop_fd)
		{
		vdlist_color_set(vdl, vdl->drop_fd, FALSE);
		vdlist_color_set(vdl, fd, TRUE);
		}

	vdl->drop_fd = fd;
}

static void vdlist_dnd_drop_scroll_cancel(ViewDirList *vdl)
{
	if (vdl->drop_scroll_id != -1) g_source_remove(vdl->drop_scroll_id);
	vdl->drop_scroll_id = -1;
}

static gint vdlist_auto_scroll_idle_cb(gpointer data)
{
	ViewDirList *vdl = data;

	if (vdl->drop_fd)
		{
		GdkWindow *window;
		gint x, y;
		gint w, h;

		window = vdl->listview->window;
		gdk_window_get_pointer(window, &x, &y, NULL);
		gdk_drawable_get_size(window, &w, &h);
		if (x >= 0 && x < w && y >= 0 && y < h)
			{
			vdlist_drop_update(vdl, x, y);
			}
		}

	vdl->drop_scroll_id = -1;
	return FALSE;
}

static gint vdlist_auto_scroll_notify_cb(GtkWidget *widget, gint x, gint y, gpointer data)
{
	ViewDirList *vdl = data;

	if (!vdl->drop_fd || vdl->drop_list) return FALSE;

	if (vdl->drop_scroll_id == -1) vdl->drop_scroll_id = g_idle_add(vdlist_auto_scroll_idle_cb, vdl);

	return TRUE;
}

static gint vdlist_dnd_drop_motion(GtkWidget *widget, GdkDragContext *context,
				   gint x, gint y, guint time, gpointer data)
{
	ViewDirList *vdl = data;

	vdl->click_fd = NULL;

	if (gtk_drag_get_source_widget(context) == vdl->listview)
		{
		/* from same window */
		gdk_drag_status(context, 0, time);
		return TRUE;
		}
	else
		{
		gdk_drag_status(context, context->suggested_action, time);
		}

	vdlist_drop_update(vdl, x, y);

        if (vdl->drop_fd)
		{
		GtkAdjustment *adj = gtk_tree_view_get_vadjustment(GTK_TREE_VIEW(vdl->listview));
		widget_auto_scroll_start(vdl->listview, adj, -1, -1, vdlist_auto_scroll_notify_cb, vdl);
		}

	return FALSE;
}

static void vdlist_dnd_drop_leave(GtkWidget *widget, GdkDragContext *context, guint time, gpointer data)
{
	ViewDirList *vdl = data;

	if (vdl->drop_fd != vdl->click_fd) vdlist_color_set(vdl, vdl->drop_fd, FALSE);

	vdl->drop_fd = NULL;
}

static void vdlist_dnd_init(ViewDirList *vdl)
{
	gtk_drag_source_set(vdl->listview, GDK_BUTTON1_MASK | GDK_BUTTON2_MASK,
			    dnd_file_drag_types, dnd_file_drag_types_count,
			    GDK_ACTION_COPY | GDK_ACTION_MOVE | GDK_ACTION_LINK);
	g_signal_connect(G_OBJECT(vdl->listview), "drag_data_get",
			 G_CALLBACK(vdlist_dnd_get), vdl);
	g_signal_connect(G_OBJECT(vdl->listview), "drag_begin",
			 G_CALLBACK(vdlist_dnd_begin), vdl);
	g_signal_connect(G_OBJECT(vdl->listview), "drag_end",
			 G_CALLBACK(vdlist_dnd_end), vdl);

	vdlist_dest_set(vdl, TRUE);
	g_signal_connect(G_OBJECT(vdl->listview), "drag_data_received",
			 G_CALLBACK(vdlist_dnd_drop_receive), vdl);
	g_signal_connect(G_OBJECT(vdl->listview), "drag_motion",
			 G_CALLBACK(vdlist_dnd_drop_motion), vdl);
	g_signal_connect(G_OBJECT(vdl->listview), "drag_leave",
			 G_CALLBACK(vdlist_dnd_drop_leave), vdl);
}

/*
 *-----------------------------------------------------------------------------
 * main
 *-----------------------------------------------------------------------------
 */ 

static void vdlist_select_row(ViewDirList *vdl, FileData *fd)
{
	if (fd && vdl->select_func)
		{
		gchar *path;

		path = g_strdup(fd->path);
		vdl->select_func(vdl, path, vdl->select_data);
		g_free(path);
		}
}

const gchar *vdlist_row_get_path(ViewDirList *vdl, gint row)
{
	FileData *fd;

	fd = g_list_nth_data(vdl->list, row);

	if (fd) return fd->path;

	return NULL;
}

static void vdlist_populate(ViewDirList *vdl)
{
	GtkListStore *store;
	GList *work;

	store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(vdl->listview)));
	gtk_list_store_clear(store);

	work = vdl->list;
	while (work)
		{
		FileData *fd;
		GtkTreeIter iter;
		GdkPixbuf *pixbuf;

		fd = work->data;

		if (access_file(fd->path, R_OK | X_OK) && fd->name)
			{
			if (fd->name[0] == '.' && fd->name[1] == '\0')
				{
				pixbuf = vdl->pf->open;
				}
			else if (fd->name[0] == '.' && fd->name[1] == '.' && fd->name[2] == '\0')
				{
				pixbuf = vdl->pf->parent;
				}
			else
				{
				pixbuf = vdl->pf->close;
				}
			}
		else
			{
			pixbuf = vdl->pf->deny;
			}

		gtk_list_store_append(store, &iter);
		gtk_list_store_set(store, &iter,
				   DIR_COLUMN_POINTER, fd,
				   DIR_COLUMN_ICON, pixbuf,
				   DIR_COLUMN_NAME, fd->name, -1);

		work = work->next;
		}

	vdl->click_fd = NULL;
	vdl->drop_fd = NULL;
}

gint vdlist_set_path(ViewDirList *vdl, const gchar *path)
{
	gint ret;
	FileData *fd;
	gchar *old_path = NULL;

	if (!path) return FALSE;
	if (vdl->path && strcmp(path, vdl->path) == 0) return TRUE;

	if (vdl->path)
		{
		gchar *base;

		base = remove_level_from_path(vdl->path);
		if (strcmp(base, path) == 0)
			{
			old_path = g_strdup(filename_from_path(vdl->path));
			}
		g_free(base);
		}

	g_free(vdl->path);
	vdl->path = g_strdup(path);

	filelist_free(vdl->list);
	vdl->list = NULL;

	ret = filelist_read(vdl->path, NULL, &vdl->list);

	vdl->list = filelist_sort(vdl->list, SORT_NAME, TRUE);

	/* add . and .. */

	if (strcmp(vdl->path, "/") != 0)
		{
		fd = g_new0(FileData, 1);
		fd->path = remove_level_from_path(vdl->path);
		fd->name = "..";
		vdl->list = g_list_prepend(vdl->list, fd);
		}

	fd = g_new0(FileData, 1);
	fd->path = g_strdup(vdl->path);
	fd->name = ".";
	vdl->list = g_list_prepend(vdl->list, fd);

	vdlist_populate(vdl);

	if (old_path)
		{
		/* scroll to make last path visible */
		FileData *found = NULL;
		GList *work;

		work = vdl->list;
		while (work && !found)
			{
			FileData *fd = work->data;
			if (strcmp(old_path, fd->name) == 0) found = fd;
			work = work->next;
			}

		if (found) vdlist_scroll_to_row(vdl, found, 0.5);

		g_free(old_path);
		return ret;
		}

	if (GTK_WIDGET_REALIZED(vdl->listview))
		{
		gtk_tree_view_scroll_to_point(GTK_TREE_VIEW(vdl->listview), 0, 0);
		}

	return ret;
}

void vdlist_refresh(ViewDirList *vdl)
{
	gchar *path;

	path = g_strdup(vdl->path);
	vdl->path = NULL;
	vdlist_set_path(vdl, path);
	g_free(path);
}

static void vdlist_menu_position_cb(GtkMenu *menu, gint *x, gint *y, gboolean *push_in, gpointer data)
{
	ViewDirList *vdl = data;
	GtkTreeModel *store;
	GtkTreeIter iter;
	GtkTreePath *tpath;
	gint cw, ch;

	if (vdlist_find_row(vdl, vdl->click_fd, &iter) < 0) return;
	store = gtk_tree_view_get_model(GTK_TREE_VIEW(vdl->listview));
	tpath = gtk_tree_model_get_path(store, &iter);
	tree_view_get_cell_clamped(GTK_TREE_VIEW(vdl->listview), tpath, 0, TRUE, x, y, &cw, &ch);
	gtk_tree_path_free(tpath);
	*y += ch;
	popup_menu_position_clamp(menu, x, y, 0);
}

static gint vdlist_press_key_cb(GtkWidget *widget, GdkEventKey *event, gpointer data)
{
	ViewDirList *vdl = data;
	GtkTreePath *tpath;
	
	if (event->keyval != GDK_Menu) return FALSE;

	gtk_tree_view_get_cursor(GTK_TREE_VIEW(vdl->listview), &tpath, NULL);
	if (tpath)
		{
		GtkTreeModel *store;
		GtkTreeIter iter;

		store = gtk_tree_view_get_model(GTK_TREE_VIEW(widget));
		gtk_tree_model_get_iter(store, &iter, tpath);
		gtk_tree_model_get(store, &iter, DIR_COLUMN_POINTER, &vdl->click_fd, -1);
		
		gtk_tree_path_free(tpath);
		}
	else
		{
		vdl->click_fd = NULL;
		}

	vdlist_color_set(vdl, vdl->click_fd, TRUE);

	vdl->popup = vdlist_pop_menu(vdl, vdl->click_fd);

	gtk_menu_popup(GTK_MENU(vdl->popup), NULL, NULL, vdlist_menu_position_cb, vdl, 0, GDK_CURRENT_TIME);

	return TRUE;
}

static gint vdlist_press_cb(GtkWidget *widget, GdkEventButton *bevent, gpointer data)
{
	ViewDirList *vdl = data;
	GtkTreePath *tpath;
	GtkTreeIter iter;
	FileData *fd = NULL;

	if (gtk_tree_view_get_path_at_pos(GTK_TREE_VIEW(widget), bevent->x, bevent->y,
					  &tpath, NULL, NULL, NULL))
		{
		GtkTreeModel *store;

		store = gtk_tree_view_get_model(GTK_TREE_VIEW(widget));
		gtk_tree_model_get_iter(store, &iter, tpath);
		gtk_tree_model_get(store, &iter, DIR_COLUMN_POINTER, &fd, -1);
		gtk_tree_view_set_cursor(GTK_TREE_VIEW(widget), tpath, NULL, FALSE);
		gtk_tree_path_free(tpath);
		}

	vdl->click_fd = fd;
	vdlist_color_set(vdl, vdl->click_fd, TRUE);

	if (bevent->button == 3)
		{
		vdl->popup = vdlist_pop_menu(vdl, vdl->click_fd);
		gtk_menu_popup(GTK_MENU(vdl->popup), NULL, NULL, NULL, NULL,
			       bevent->button, bevent->time);
		}

	return TRUE;
}

static gint vdlist_release_cb(GtkWidget *widget, GdkEventButton *bevent, gpointer data)
{
	ViewDirList *vdl = data;
	GtkTreePath *tpath;
	GtkTreeIter iter;
	FileData *fd = NULL;

	vdlist_color_set(vdl, vdl->click_fd, FALSE);

	if (bevent->button != 1) return TRUE;

	if ((bevent->x != 0 || bevent->y != 0) &&
	    gtk_tree_view_get_path_at_pos(GTK_TREE_VIEW(widget), bevent->x, bevent->y,
					  &tpath, NULL, NULL, NULL))
		{
		GtkTreeModel *store;

		store = gtk_tree_view_get_model(GTK_TREE_VIEW(widget));
		gtk_tree_model_get_iter(store, &iter, tpath);
		gtk_tree_model_get(store, &iter, DIR_COLUMN_POINTER, &fd, -1);
		gtk_tree_path_free(tpath);
		}

	if (fd && vdl->click_fd == fd)
		{
		vdlist_select_row(vdl, vdl->click_fd);
		}

	return TRUE;
}

static void vdlist_select_cb(GtkTreeView *tview, GtkTreePath *tpath, GtkTreeViewColumn *column, gpointer data)
{
	ViewDirList *vdl = data;
	GtkTreeModel *store;
	GtkTreeIter iter;
	FileData *fd;

	store = gtk_tree_view_get_model(tview);
	gtk_tree_model_get_iter(store, &iter, tpath);
	gtk_tree_model_get(store, &iter, DIR_COLUMN_POINTER, &fd, -1);

	vdlist_select_row(vdl, fd);
}

static GdkColor *vdlist_color_shifted(GtkWidget *widget)
{
	static GdkColor color;
	static GtkWidget *done = NULL;

	if (done != widget)
		{
		GtkStyle *style;

		style = gtk_widget_get_style(widget);
		memcpy(&color, &style->base[GTK_STATE_NORMAL], sizeof(color));
		shift_color(&color, -1, 0);
		done = widget;
		}

	return &color;
}

static void vdlist_color_cb(GtkTreeViewColumn *tree_column, GtkCellRenderer *cell,
			    GtkTreeModel *tree_model, GtkTreeIter *iter, gpointer data)
{
	ViewDirList *vdl = data;
	gboolean set;

	gtk_tree_model_get(tree_model, iter, DIR_COLUMN_COLOR, &set, -1);
	g_object_set(G_OBJECT(cell),
		     "cell-background-gdk", vdlist_color_shifted(vdl->listview),
		     "cell-background-set", set, NULL);
}

static void vdlist_destroy_cb(GtkWidget *widget, gpointer data)
{
	ViewDirList *vdl = data;

	if (vdl->popup)
		{
		g_signal_handlers_disconnect_matched(G_OBJECT(vdl->popup), G_SIGNAL_MATCH_DATA,
						     0, 0, 0, NULL, vdl);
		gtk_widget_destroy(vdl->popup);
		}

	vdlist_dnd_drop_scroll_cancel(vdl);
	widget_auto_scroll_stop(vdl->listview);

	path_list_free(vdl->drop_list);

	folder_icons_free(vdl->pf);

	g_free(vdl->path);
	filelist_free(vdl->list);
	g_free(vdl);
}

ViewDirList *vdlist_new(const gchar *path)
{
	ViewDirList *vdl;
	GtkListStore *store;
	GtkTreeSelection *selection;
	GtkTreeViewColumn *column;
	GtkCellRenderer *renderer;

	vdl = g_new0(ViewDirList, 1);

	vdl->path = NULL;
	vdl->list = NULL;
	vdl->click_fd = NULL;

	vdl->drop_fd = NULL;
	vdl->drop_list = NULL;

	vdl->drop_scroll_id = -1;

	vdl->popup = NULL;

	vdl->widget = gtk_scrolled_window_new(NULL, NULL);
	gtk_scrolled_window_set_shadow_type(GTK_SCROLLED_WINDOW(vdl->widget), GTK_SHADOW_IN);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(vdl->widget),
				       GTK_POLICY_AUTOMATIC, GTK_POLICY_ALWAYS);
	g_signal_connect(G_OBJECT(vdl->widget), "destroy",
			 G_CALLBACK(vdlist_destroy_cb), vdl);

	store = gtk_list_store_new(4, G_TYPE_POINTER, GDK_TYPE_PIXBUF, G_TYPE_STRING, G_TYPE_BOOLEAN);
	vdl->listview = gtk_tree_view_new_with_model(GTK_TREE_MODEL(store));
	g_object_unref(store);

	gtk_tree_view_set_headers_visible(GTK_TREE_VIEW(vdl->listview), FALSE);
	gtk_tree_view_set_enable_search(GTK_TREE_VIEW(vdl->listview), FALSE);
	g_signal_connect(G_OBJECT(vdl->listview), "row_activated",

			 G_CALLBACK(vdlist_select_cb), vdl);

	selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(vdl->listview));
	gtk_tree_selection_set_mode(selection, GTK_SELECTION_NONE);

	column = gtk_tree_view_column_new();
	gtk_tree_view_column_set_sizing(column, GTK_TREE_VIEW_COLUMN_AUTOSIZE);

	renderer = gtk_cell_renderer_pixbuf_new();
	gtk_tree_view_column_pack_start(column, renderer, FALSE);
	gtk_tree_view_column_add_attribute(column, renderer, "pixbuf", DIR_COLUMN_ICON);
	gtk_tree_view_column_set_cell_data_func(column, renderer, vdlist_color_cb, vdl, NULL);

	renderer = gtk_cell_renderer_text_new();
	gtk_tree_view_column_pack_start(column, renderer, TRUE);
	gtk_tree_view_column_add_attribute(column, renderer, "text", DIR_COLUMN_NAME);
	gtk_tree_view_column_set_cell_data_func(column, renderer, vdlist_color_cb, vdl, NULL);

	gtk_tree_view_append_column(GTK_TREE_VIEW(vdl->listview), column);

	g_signal_connect(G_OBJECT(vdl->listview), "key_press_event",
			   G_CALLBACK(vdlist_press_key_cb), vdl);
	gtk_container_add(GTK_CONTAINER(vdl->widget), vdl->listview);
	gtk_widget_show(vdl->listview);

	vdl->pf = folder_icons_new();

	vdlist_dnd_init(vdl);

	g_signal_connect(G_OBJECT(vdl->listview), "button_press_event",
			 G_CALLBACK(vdlist_press_cb), vdl);
	g_signal_connect(G_OBJECT(vdl->listview), "button_release_event",
			 G_CALLBACK(vdlist_release_cb), vdl);

	if (path) vdlist_set_path(vdl, path);

	return vdl;
}

void vdlist_set_select_func(ViewDirList *vdl,
			    void (*func)(ViewDirList *vdl, const gchar *path, gpointer data), gpointer data)
{
	vdl->select_func = func;
	vdl->select_data = data;
}

void vdlist_set_layout(ViewDirList *vdl, LayoutWindow *layout)
{
	vdl->layout = layout;
}

