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
#include "view_file_icon.h"

#include "cellrenderericon.h"
#include "collect.h"
#include "collect-io.h"
#include "collect-table.h"
#include "dnd.h"
#include "editors.h"
#include "img-view.h"
#include "info.h"
#include "filelist.h"
#include "layout.h"
#include "layout_image.h"
#include "menu.h"
#include "thumb.h"
#include "utilops.h"
#include "ui_bookmark.h"
#include "ui_fileops.h"
#include "ui_menu.h"
#include "ui_tree_edit.h"


#include <gdk/gdkkeysyms.h> /* for keyboard values */

/* between these, the icon width is increased by thumb_max_width / 2 */
#define THUMB_MIN_ICON_WIDTH 128
#define THUMB_MAX_ICON_WIDTH 150

#define VFICON_MAX_COLUMNS 32
#define THUMB_BORDER_PADDING 2

#define VFICON_TIP_DELAY 500

#define ICON_DATA(x) ((IconData *)x)
#define FILE_DATA(x) ((FileData *)x)


enum {
	FILE_COLUMN_POINTER = 0,
	FILE_COLUMN_COUNT
};

typedef enum {
	SELECTION_NONE		= 0,
	SELECTION_SELECTED	= 1 << 0,
	SELECTION_PRELIGHT	= 1 << 1,
	SELECTION_FOCUS		= 1 << 2
} SelectionType;

typedef struct _IconData IconData;
struct _IconData
{
	FileData fd;
	SelectionType selected;
	gint row;
};


static gint iconlist_read(const gchar *path, GList **list)
{
	GList *temp;
	GList *work;

	if (!filelist_read(path, &temp, NULL)) return FALSE;

	work = temp;
	while (work)
		{
		FileData *fd;
		IconData *id;

		fd = work->data;
		id = g_new0(IconData, 1);

		memcpy(id, fd, sizeof(FileData));
		id->selected = SELECTION_NONE;
		id->row = -1;

		work->data = id;
		g_free(fd);

		work = work->next;
		}

	*list = temp;

	return TRUE;
}

static void iconlist_free(GList *list)
{
	filelist_free(list);
}


static void vficon_toggle_filenames(ViewFileIcon *vfi);
static void vficon_selection_remove(ViewFileIcon *vfi, FileData *fd, SelectionType mask, GtkTreeIter *iter);
static void vficon_move_focus(ViewFileIcon *vfi, gint row, gint col, gint relative);
static void vficon_set_focus(ViewFileIcon *vfi, FileData *fd);
static void vficon_thumb_update(ViewFileIcon *vfi);
static void vficon_populate_at_new_size(ViewFileIcon *vfi, gint w, gint h, gint force);


/*
 *-----------------------------------------------------------------------------
 * pop-up menu
 *-----------------------------------------------------------------------------
 */

static GList *vficon_pop_menu_file_list(ViewFileIcon *vfi)
{
	if (!vfi->click_fd) return NULL;

	if (ICON_DATA(vfi->click_fd)->selected & SELECTION_SELECTED)
		{
		return vficon_selection_get_list(vfi);
		}

	return g_list_append(NULL, g_strdup(vfi->click_fd->path));
}

static void vficon_pop_menu_edit_cb(GtkWidget *widget, gpointer data)
{
	ViewFileIcon *vfi;
	gint n;
	GList *list;

	vfi = submenu_item_get_data(widget);
	n = GPOINTER_TO_INT(data);

	if (!vfi) return;

	list = vficon_pop_menu_file_list(vfi);
	start_editor_from_path_list(n, list);
	path_list_free(list);
}

static void vficon_pop_menu_info_cb(GtkWidget *widget, gpointer data)
{
	ViewFileIcon *vfi = data;

	info_window_new(NULL, vficon_pop_menu_file_list(vfi));
}

static void vficon_pop_menu_view_cb(GtkWidget *widget, gpointer data)
{
	ViewFileIcon *vfi = data;

	if (!vfi->click_fd) return;

	if (ICON_DATA(vfi->click_fd)->selected & SELECTION_SELECTED)
		{
		GList *list;
		
		list = vficon_selection_get_list(vfi);
		view_window_new_from_list(list);
		path_list_free(list);
		}
	else
		{
		view_window_new(vfi->click_fd->path);
		}
}

static void vficon_pop_menu_copy_cb(GtkWidget *widget, gpointer data)
{
	ViewFileIcon *vfi = data;

	file_util_copy(NULL, vficon_pop_menu_file_list(vfi), NULL, vfi->listview);
}

static void vficon_pop_menu_move_cb(GtkWidget *widget, gpointer data)
{
	ViewFileIcon *vfi = data;

	file_util_move(NULL, vficon_pop_menu_file_list(vfi), NULL, vfi->listview);
}

static void vficon_pop_menu_rename_cb(GtkWidget *widget, gpointer data)
{
	ViewFileIcon *vfi = data;

	file_util_rename(NULL, vficon_pop_menu_file_list(vfi), vfi->listview);
}

static void vficon_pop_menu_delete_cb(GtkWidget *widget, gpointer data)
{
	ViewFileIcon *vfi = data;

	file_util_delete(NULL, vficon_pop_menu_file_list(vfi), vfi->listview);
}

static void vficon_pop_menu_sort_cb(GtkWidget *widget, gpointer data)
{
	ViewFileIcon *vfi;
	SortType type;

	if (!gtk_check_menu_item_get_active(GTK_CHECK_MENU_ITEM(widget))) return;
	
	vfi = submenu_item_get_data(widget);
	if (!vfi) return;

	type = (SortType)GPOINTER_TO_INT(data);

	if (vfi->layout)
		{
		layout_sort_set(vfi->layout, type, vfi->sort_ascend);
		}
	else
		{
		vficon_sort_set(vfi, type, vfi->sort_ascend);
		}
}

static void vficon_pop_menu_sort_ascend_cb(GtkWidget *widget, gpointer data)
{
	ViewFileIcon *vfi = data;

	if (vfi->layout)
		{
		layout_sort_set(vfi->layout, vfi->sort_method, !vfi->sort_ascend);
		}
	else
		{
		vficon_sort_set(vfi, vfi->sort_method, !vfi->sort_ascend);
		}
}

static void vficon_pop_menu_list_cb(GtkWidget *widget, gpointer data)
{
	ViewFileIcon *vfi = data;

	if (vfi->layout) layout_views_set(vfi->layout, vfi->layout->tree_view, FALSE);
}

static void vficon_pop_menu_show_names_cb(GtkWidget *widget, gpointer data)
{
	ViewFileIcon *vfi = data;

	vficon_toggle_filenames(vfi);
}

static void vficon_pop_menu_refresh_cb(GtkWidget *widget, gpointer data)
{
	ViewFileIcon *vfi = data;

	vficon_refresh(vfi);
}

static void vficon_popup_destroy_cb(GtkWidget *widget, gpointer data)
{
	ViewFileIcon *vfi = data;                                                                                                                               
	vficon_selection_remove(vfi, vfi->click_fd, SELECTION_PRELIGHT, NULL);
	vfi->click_fd = NULL;
	vfi->popup = NULL;
}

static GtkWidget *vficon_pop_menu(ViewFileIcon *vfi, gint active)
{
	GtkWidget *menu;
	GtkWidget *item;
	GtkWidget *submenu;

	menu = popup_menu_short_lived();

	g_signal_connect(G_OBJECT(menu), "destroy",
			 G_CALLBACK(vficon_popup_destroy_cb), vfi);

	submenu_add_edit(menu, &item, G_CALLBACK(vficon_pop_menu_edit_cb), vfi);
	gtk_widget_set_sensitive(item, active);

	item = menu_item_add_stock(menu, _("_Properties"), GTK_STOCK_PROPERTIES, G_CALLBACK(vficon_pop_menu_info_cb), vfi);
	gtk_widget_set_sensitive(item, active);

	item = menu_item_add_stock(menu, _("View in _new window"), GTK_STOCK_NEW, G_CALLBACK(vficon_pop_menu_view_cb), vfi);
	gtk_widget_set_sensitive(item, active);

	menu_item_add_divider(menu);
	item = menu_item_add_stock(menu, _("_Copy..."), GTK_STOCK_COPY, G_CALLBACK(vficon_pop_menu_copy_cb), vfi);
	gtk_widget_set_sensitive(item, active);
	item = menu_item_add(menu, _("_Move..."), G_CALLBACK(vficon_pop_menu_move_cb), vfi);
	gtk_widget_set_sensitive(item, active);
	item = menu_item_add(menu, _("_Rename..."), G_CALLBACK(vficon_pop_menu_rename_cb), vfi);
	gtk_widget_set_sensitive(item, active);
	item = menu_item_add_stock(menu, _("_Delete..."), GTK_STOCK_DELETE, G_CALLBACK(vficon_pop_menu_delete_cb), vfi);
	gtk_widget_set_sensitive(item, active);

	menu_item_add_divider(menu);

	submenu = submenu_add_sort(NULL, G_CALLBACK(vficon_pop_menu_sort_cb), vfi,
				   FALSE, FALSE, TRUE, vfi->sort_method);
	menu_item_add_divider(submenu);
	menu_item_add_check(submenu, _("Ascending"), vfi->sort_ascend,
			    G_CALLBACK(vficon_pop_menu_sort_ascend_cb), vfi);

	item = menu_item_add(menu, _("_Sort"), NULL, NULL);
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(item), submenu);

	menu_item_add_check(menu, _("View as _icons"), TRUE,
			    G_CALLBACK(vficon_pop_menu_list_cb), vfi);
	menu_item_add_check(menu, _("Show filename _text"), vfi->show_text,
			    G_CALLBACK(vficon_pop_menu_show_names_cb), vfi);
	menu_item_add_stock(menu, _("Re_fresh"), GTK_STOCK_REFRESH, G_CALLBACK(vficon_pop_menu_refresh_cb), vfi);

	return menu;
}

/*
 *-------------------------------------------------------------------
 * signals
 *-------------------------------------------------------------------
 */

static void vficon_send_update(ViewFileIcon *vfi)
{
	if (vfi->func_status) vfi->func_status(vfi, vfi->data_status);
}

static void vficon_send_layout_select(ViewFileIcon *vfi, FileData *fd)
{
	const gchar *read_ahead_path = NULL;

	if (!vfi->layout || !fd) return;

	if (enable_read_ahead)
		{
		FileData *fd_n;
		gint row;

		row = g_list_index(vfi->list, fd);
		if (row > vficon_index_by_path(vfi, layout_image_get_path(vfi->layout)) &&
		    row + 1 < vficon_count(vfi, NULL))
			{
			fd_n = vficon_index_get_data(vfi, row + 1);
			}
		else if (row > 0)
			{
			fd_n = vficon_index_get_data(vfi, row - 1);
			}
		else
			{
			fd_n = NULL;
			}
		if (fd_n) read_ahead_path = fd_n->path;
		}

	layout_image_set_with_ahead(vfi->layout, fd->path, read_ahead_path);
}

static void vficon_toggle_filenames(ViewFileIcon *vfi)
{
	vfi->show_text = !vfi->show_text;
	show_icon_names = vfi->show_text;

	vficon_populate_at_new_size(vfi, vfi->listview->allocation.width, vfi->listview->allocation.height, TRUE);
}

static gint vficon_get_icon_width(ViewFileIcon *vfi)
{
	gint width;

	if (!vfi->show_text) return thumb_max_width;

	width = thumb_max_width + thumb_max_width / 2;
	if (width < THUMB_MIN_ICON_WIDTH) width = THUMB_MIN_ICON_WIDTH;
	if (width > THUMB_MAX_ICON_WIDTH) width = thumb_max_width;

	return width;
}

/*
 *-------------------------------------------------------------------
 * misc utils
 *-------------------------------------------------------------------
 */

static gint vficon_find_position(ViewFileIcon *vfi, FileData *fd, gint *row, gint *col)
{
	gint n;

	n = g_list_index(vfi->list, fd);

	if (n < 0) return FALSE;

	*row = n / vfi->columns;
	*col = n - (*row * vfi->columns);

	return TRUE;
}

static gint vficon_find_iter(ViewFileIcon *vfi, FileData *fd, GtkTreeIter *iter, gint *column)
{
	GtkTreeModel *store;
	gint row, col;

	store = gtk_tree_view_get_model(GTK_TREE_VIEW(vfi->listview));
	if (!vficon_find_position(vfi, fd, &row, &col)) return FALSE;
	if (!gtk_tree_model_iter_nth_child(store, iter, NULL, row)) return FALSE;
	if (column) *column = col;

	return TRUE;
}

static FileData *vficon_find_data(ViewFileIcon *vfi, gint row, gint col, GtkTreeIter *iter)
{
	GtkTreeModel *store;
	GtkTreeIter p;

	if (row < 0 || col < 0) return NULL;

	store = gtk_tree_view_get_model(GTK_TREE_VIEW(vfi->listview));
	if (gtk_tree_model_iter_nth_child(store, &p, NULL, row))
		{
		GList *list;

		gtk_tree_model_get(store, &p, FILE_COLUMN_POINTER, &list, -1);
		if (!list) return NULL;

		if (iter) *iter = p;

		return g_list_nth_data(list, col);
		}

	return NULL;
}

static FileData *vficon_find_data_by_coord(ViewFileIcon *vfi, gint x, gint y, GtkTreeIter *iter)
{
	GtkTreePath *tpath;
	GtkTreeViewColumn *column;

	if (gtk_tree_view_get_path_at_pos(GTK_TREE_VIEW(vfi->listview), x, y,
					  &tpath, &column, NULL, NULL))
		{
		GtkTreeModel *store;
		GtkTreeIter row;
		GList *list;
		gint n;

		store = gtk_tree_view_get_model(GTK_TREE_VIEW(vfi->listview));
		gtk_tree_model_get_iter(store, &row, tpath);
		gtk_tree_path_free(tpath);

		gtk_tree_model_get(store, &row, FILE_COLUMN_POINTER, &list, -1);

		n = GPOINTER_TO_INT(g_object_get_data(G_OBJECT(column), "column_number"));
		if (list)
			{
			if (iter) *iter = row;
			return g_list_nth_data(list, n);
			}
		}

	return NULL;
}

/*
 *-------------------------------------------------------------------
 * tooltip type window
 *-------------------------------------------------------------------
 */

static void tip_show(ViewFileIcon *vfi)
{
	GtkWidget *label;
	gint x, y;

	if (vfi->tip_window) return;

	gdk_window_get_pointer(gtk_tree_view_get_bin_window(GTK_TREE_VIEW(vfi->listview)), &x, &y, NULL);

	vfi->tip_fd = vficon_find_data_by_coord(vfi, x, y, NULL);
	if (!vfi->tip_fd) return;

	vfi->tip_window = gtk_window_new(GTK_WINDOW_POPUP);
	gtk_window_set_resizable(GTK_WINDOW(vfi->tip_window), FALSE);
	gtk_container_set_border_width(GTK_CONTAINER(vfi->tip_window), 2);

	label = gtk_label_new(vfi->tip_fd->name);

	g_object_set_data(G_OBJECT(vfi->tip_window), "tip_label", label);
	gtk_container_add(GTK_CONTAINER(vfi->tip_window), label);
	gtk_widget_show(label);

	gdk_window_get_pointer(NULL, &x, &y, NULL);

	if (!GTK_WIDGET_REALIZED(vfi->tip_window)) gtk_widget_realize(vfi->tip_window);
	gtk_window_move(GTK_WINDOW(vfi->tip_window), x + 16, y + 16);
	gtk_widget_show(vfi->tip_window);
}

static void tip_hide(ViewFileIcon *vfi)
{
	if (vfi->tip_window) gtk_widget_destroy(vfi->tip_window);
	vfi->tip_window = NULL;
}

static gint tip_schedule_cb(gpointer data)
{
	ViewFileIcon *vfi = data;
	GtkWidget *window;

	if (vfi->tip_delay_id == -1) return FALSE;

	window = gtk_widget_get_toplevel(vfi->listview);

	if (GTK_WIDGET_SENSITIVE(window) &&
	    GTK_WINDOW(window)->has_focus)
		{
		tip_show(vfi);
		}

	vfi->tip_delay_id = -1;
	return FALSE;
}

static void tip_schedule(ViewFileIcon *vfi)
{
	tip_hide(vfi);

	if (vfi->tip_delay_id != -1)
		{
		g_source_remove(vfi->tip_delay_id);
		vfi->tip_delay_id = -1;
		}

	if (!vfi->show_text)
		{
		vfi->tip_delay_id = g_timeout_add(VFICON_TIP_DELAY, tip_schedule_cb, vfi);
		}
}

static void tip_unschedule(ViewFileIcon *vfi)
{
	tip_hide(vfi);

	if (vfi->tip_delay_id != -1) g_source_remove(vfi->tip_delay_id);
	vfi->tip_delay_id = -1;
}

static void tip_update(ViewFileIcon *vfi, FileData *fd)
{
	if (vfi->tip_window)
		{
		gint x, y;

		gdk_window_get_pointer(NULL, &x, &y, NULL);
		gtk_window_move(GTK_WINDOW(vfi->tip_window), x + 16, y + 16);

		if (fd != vfi->tip_fd)
			{
			GtkWidget *label;

			vfi->tip_fd = fd;

			if (!vfi->tip_fd)
				{
				tip_hide(vfi);
				tip_schedule(vfi);
				return;
				}

			label = g_object_get_data(G_OBJECT(vfi->tip_window), "tip_label");
			gtk_label_set_text(GTK_LABEL(label), vfi->tip_fd->name);
			}
		}
	else
		{
		tip_schedule(vfi);
		}
}

/*
 *-------------------------------------------------------------------
 * dnd
 *-------------------------------------------------------------------
 */

static void vficon_dnd_get(GtkWidget *widget, GdkDragContext *context,
			   GtkSelectionData *selection_data, guint info,
			   guint time, gpointer data)
{
	ViewFileIcon *vfi = data;
	GList *list = NULL;
	gchar *uri_text = NULL;
	gint total;

	if (!vfi->click_fd) return;

	if (ICON_DATA(vfi->click_fd)->selected & SELECTION_SELECTED)
		{
		list = vficon_selection_get_list(vfi);
		}
	else
		{
		const gchar *path = vfi->click_fd->path;

		list = g_list_append(NULL, g_strdup(path));
		}

	if (!list) return;
	uri_text = uri_text_from_list(list, &total, (info == TARGET_TEXT_PLAIN));
	path_list_free(list);

	if (debug) printf(uri_text);

	gtk_selection_data_set(selection_data, selection_data->target,
			       8, (guchar *)uri_text, total);
	g_free(uri_text);
}

static void vficon_dnd_begin(GtkWidget *widget, GdkDragContext *context, gpointer data)
{
	ViewFileIcon *vfi = data;

	tip_unschedule(vfi);

	if (vfi->click_fd && vfi->click_fd->pixbuf)
		{
		gint items;

		if (ICON_DATA(vfi->click_fd)->selected & SELECTION_SELECTED)
			items = g_list_length(vfi->selection);
		else
			items = 1;

		dnd_set_drag_icon(widget, context, vfi->click_fd->pixbuf, items);
		}
}

static void vficon_dnd_end(GtkWidget *widget, GdkDragContext *context, gpointer data)
{
	ViewFileIcon *vfi = data;

	vficon_selection_remove(vfi, vfi->click_fd, SELECTION_PRELIGHT, NULL);

	if (context->action == GDK_ACTION_MOVE)
		{
		vficon_refresh(vfi);
		}

	tip_unschedule(vfi);
}

static void vficon_dnd_init(ViewFileIcon *vfi)
{
	gtk_drag_source_set(vfi->listview, GDK_BUTTON1_MASK | GDK_BUTTON2_MASK,
			    dnd_file_drag_types, dnd_file_drag_types_count,
			    GDK_ACTION_COPY | GDK_ACTION_MOVE | GDK_ACTION_LINK);
	g_signal_connect(G_OBJECT(vfi->listview), "drag_data_get",
			 G_CALLBACK(vficon_dnd_get), vfi);
	g_signal_connect(G_OBJECT(vfi->listview), "drag_begin",
			 G_CALLBACK(vficon_dnd_begin), vfi);
	g_signal_connect(G_OBJECT(vfi->listview), "drag_end",
			 G_CALLBACK(vficon_dnd_end), vfi);
}

/*
 *-------------------------------------------------------------------
 * cell updates
 *-------------------------------------------------------------------
 */

static void vficon_selection_set(ViewFileIcon *vfi, FileData *fd, SelectionType value, GtkTreeIter *iter)
{
	IconData *id;
	GtkTreeModel *store;
	GList *list;

	if (!fd) return;

	id = ICON_DATA(fd);

	if (id->selected == value) return;
	id->selected = value;

	store = gtk_tree_view_get_model(GTK_TREE_VIEW(vfi->listview));
	if (iter)
		{
		gtk_tree_model_get(store, iter, FILE_COLUMN_POINTER, &list, -1);
		if (list) gtk_list_store_set(GTK_LIST_STORE(store), iter, FILE_COLUMN_POINTER, list, -1);
		}
	else
		{
		GtkTreeIter row;

		if (vficon_find_iter(vfi, fd, &row, NULL))
			{
			gtk_tree_model_get(store, &row, FILE_COLUMN_POINTER, &list, -1);
			if (list) gtk_list_store_set(GTK_LIST_STORE(store), &row, FILE_COLUMN_POINTER, list, -1);
			}
		}
}

static void vficon_selection_add(ViewFileIcon *vfi, FileData *fd, SelectionType mask, GtkTreeIter *iter)
{
	if (!fd) return;

	vficon_selection_set(vfi, fd, ICON_DATA(fd)->selected | mask, iter);
}

static void vficon_selection_remove(ViewFileIcon *vfi, FileData *fd, SelectionType mask, GtkTreeIter *iter)
{
	if (!fd) return;

	vficon_selection_set(vfi, fd, ICON_DATA(fd)->selected & ~mask, iter);
}

/*
 *-------------------------------------------------------------------
 * selections
 *-------------------------------------------------------------------
 */

static void vficon_verify_selections(ViewFileIcon *vfi)
{
	GList *work;

	work = vfi->selection;
	while (work)
		{
		FileData *fd = work->data;
		work = work->next;
		if (!g_list_find(vfi->list, fd))
			{
			vfi->selection = g_list_remove(vfi->selection, fd);
			}
		}
}

void vficon_select_all(ViewFileIcon *vfi)
{
	GList *work;

	g_list_free(vfi->selection);
	vfi->selection = NULL;

	work = vfi->list;
	while (work)
		{
		vfi->selection = g_list_append(vfi->selection, work->data);
		vficon_selection_add(vfi, work->data, SELECTION_SELECTED, NULL);
		work = work->next;
		}

	vficon_send_update(vfi);
}

void vficon_select_none(ViewFileIcon *vfi)
{
	GList *work;

	work = vfi->selection;
	while (work)
		{
		vficon_selection_remove(vfi, work->data, SELECTION_SELECTED, NULL);
		work = work->next;
		}

	g_list_free(vfi->selection);
	vfi->selection = NULL;

	vficon_send_update(vfi);
}

static void vficon_select(ViewFileIcon *vfi, FileData *fd)
{
	vfi->prev_selection = fd;

	if (!fd || ICON_DATA(fd)->selected & SELECTION_SELECTED) return;

	vfi->selection = g_list_append(vfi->selection, fd);
	vficon_selection_add(vfi, fd, SELECTION_SELECTED, NULL);

	vficon_send_update(vfi);
}

static void vficon_unselect(ViewFileIcon *vfi, FileData *fd)
{
	vfi->prev_selection = fd;

	if (!fd || !(ICON_DATA(fd)->selected & SELECTION_SELECTED) ) return;

	vfi->selection = g_list_remove(vfi->selection, fd);
	vficon_selection_remove(vfi, fd, SELECTION_SELECTED, NULL);

	vficon_send_update(vfi);
}

static void vficon_select_util(ViewFileIcon *vfi, FileData *fd, gint select)
{
	if (select)
		{
		vficon_select(vfi, fd);
		}
	else
		{
		vficon_unselect(vfi, fd);
		}
}

static void vficon_select_region_util(ViewFileIcon *vfi, FileData *start, FileData *end, gint select)
{
	gint row1, col1;
	gint row2, col2;
	gint t;
	gint i, j;

	if (!vficon_find_position(vfi, start, &row1, &col1) ||
	    !vficon_find_position(vfi, end, &row2, &col2) ) return;

	vfi->prev_selection = end;

	if (!collection_rectangular_selection)
		{
		GList *work;
		FileData *fd;

		if (g_list_index(vfi->list, start) > g_list_index(vfi->list, end))
			{
			fd = start;
			start = end;
			end = fd;
			}

		work = g_list_find(vfi->list, start);
		while (work)
			{
			fd = work->data;
			vficon_select_util(vfi, fd, select);
			
			if (work->data != end)
				work = work->next;
			else
				work = NULL;
			}
		return;
		}

	if (row2 < row1)
		{
		t = row1;
		row1 = row2;
		row2 = t;
		}
	if (col2 < col1)
		{
		t = col1;
		col1 = col2;
		col2 = t;
		}

	if (debug) printf("table: %d x %d to %d x %d\n", row1, col1, row2, col2);

	for (i = row1; i <= row2; i++)
		{
		for (j = col1; j <= col2; j++)
			{
			FileData *fd = vficon_find_data(vfi, i, j, NULL);
			if (fd) vficon_select_util(vfi, fd, select);
			}
		}
}

gint vficon_index_is_selected(ViewFileIcon *vfi, gint row)
{
	FileData *fd = g_list_nth_data(vfi->list, row);

	if (!fd) return FALSE;

	return (ICON_DATA(fd)->selected & SELECTION_SELECTED);
}

gint vficon_selection_count(ViewFileIcon *vfi, gint64 *bytes)
{
	if (bytes)
		{
		gint64 b = 0;
		GList *work;

		work = vfi->selection;
		while (work)
			{
			FileData *fd = work->data;
			b += fd->size;

			work = work->next;
			}

		*bytes = b;
		}

	return g_list_length(vfi->selection);
}

GList *vficon_selection_get_list(ViewFileIcon *vfi)
{
	GList *list = NULL;
	GList *work;

	work = vfi->selection;
	while (work)
		{
		FileData *fd = work->data;

		list = g_list_prepend(list, g_strdup(fd->path));

		work = work->next;
		}

	list = g_list_reverse(list);

	return list;
}

GList *vficon_selection_get_list_by_index(ViewFileIcon *vfi)
{
	GList *list = NULL;
	GList *work;

	work = vfi->selection;	
	while (work)
		{
		list = g_list_prepend(list, GINT_TO_POINTER(g_list_index(vfi->list, work->data)));
		work = work->next;
		}

	return g_list_reverse(list);
}

void vficon_select_by_path(ViewFileIcon *vfi, const gchar *path)
{
	FileData *fd;
	GList *work;

	if (!path) return;

	fd = NULL;
	work = vfi->list;
	while (work && !fd)
		{
		FileData *chk = work->data;
		work = work->next;
		if (strcmp(chk->path, path) == 0) fd = chk;
		}

	if (!fd) return;

	if (!(ICON_DATA(fd)->selected & SELECTION_SELECTED))
		{
		vficon_select_none(vfi);
		vficon_select(vfi, fd);
		}

	vficon_set_focus(vfi, fd);
}

/*
 *-------------------------------------------------------------------
 * focus
 *-------------------------------------------------------------------
 */

static void vficon_move_focus(ViewFileIcon *vfi, gint row, gint col, gint relative)
{
	gint new_row;
	gint new_col;

	if (relative)
		{
		new_row = vfi->focus_row;
		new_col = vfi->focus_column;

		new_row += row;
		if (new_row < 0) new_row = 0;
		if (new_row >= vfi->rows) new_row = vfi->rows - 1;

		while(col != 0)
			{
			if (col < 0)
				{
				new_col--;
				col++;
				}
			else
				{
				new_col++;
				col--;
				}

			if (new_col < 0)
				{
				if (new_row > 0)
					{
					new_row--;
					new_col = vfi->columns - 1;
					}
				else
					{
					new_col = 0;
					}
				}
			if (new_col >= vfi->columns)
				{
				if (new_row < vfi->rows - 1)
					{
					new_row++;
					new_col = 0;
					}
				else
					{
					new_col = vfi->columns - 1;
					}
				}
			}
		}
	else
		{
		new_row = row;
		new_col = col;

		if (new_row >= vfi->rows)
			{
			if (vfi->rows > 0)
				new_row = vfi->rows - 1;
			else
				new_row = 0;
			new_col = vfi->columns - 1;
			}
		if (new_col >= vfi->columns) new_col = vfi->columns - 1;
		}

	if (new_row == vfi->rows - 1)
		{
		gint l;

		/* if we moved beyond the last image, go to the last image */

		l = g_list_length(vfi->list);
		if (vfi->rows > 1) l -= (vfi->rows - 1) * vfi->columns;
		if (new_col >= l) new_col = l - 1;
		}

	vficon_set_focus(vfi, vficon_find_data(vfi, new_row, new_col, NULL));
}

static void vficon_set_focus(ViewFileIcon *vfi, FileData *fd)
{
	GtkTreeIter iter;
	gint row, col;

	if (g_list_find(vfi->list, vfi->focus_fd))
		{
		if (fd == vfi->focus_fd)
			{
			/* ensure focus row col are correct */
			vficon_find_position(vfi, vfi->focus_fd, &vfi->focus_row, &vfi->focus_column);
			return;
			}
		vficon_selection_remove(vfi, vfi->focus_fd, SELECTION_FOCUS, NULL);
		}

	if (!vficon_find_position(vfi, fd, &row, &col))
		{
		vfi->focus_fd = NULL;
		vfi->focus_row = -1;
		vfi->focus_column = -1;
		return;
		}

	vfi->focus_fd = fd;
	vfi->focus_row = row;
	vfi->focus_column = col;
	vficon_selection_add(vfi, vfi->focus_fd, SELECTION_FOCUS, NULL);

	if (vficon_find_iter(vfi, vfi->focus_fd, &iter, NULL))
		{
		GtkTreePath *tpath;
		GtkTreeViewColumn *column;
		GtkTreeModel *store;

		tree_view_row_make_visible(GTK_TREE_VIEW(vfi->listview), &iter, FALSE);

		store = gtk_tree_view_get_model(GTK_TREE_VIEW(vfi->listview));
		tpath = gtk_tree_model_get_path(store, &iter);
		/* focus is set to an extra column with 0 width to hide focus, we draw it ourself */
		column = gtk_tree_view_get_column(GTK_TREE_VIEW(vfi->listview), VFICON_MAX_COLUMNS);
		gtk_tree_view_set_cursor(GTK_TREE_VIEW(vfi->listview), tpath, column, FALSE);
		gtk_tree_path_free(tpath);
		}
}

static void vficon_update_focus(ViewFileIcon *vfi)
{
	gint new_row = 0;
	gint new_col = 0;

	if (vfi->focus_fd && vficon_find_position(vfi, vfi->focus_fd, &new_row, &new_col))
		{
		/* first find the old focus, if it exists and is valid */
		}
	else
		{
		/* (try to) stay where we were */
		new_row = vfi->focus_row;
		new_col = vfi->focus_column;
		}

	vficon_move_focus(vfi, new_row, new_col, FALSE);
}

/* used to figure the page up/down distances */
static gint page_height(ViewFileIcon *vfi)
{
	GtkAdjustment *adj;
	gint page_size;
	gint row_height;
	gint ret;

	adj = gtk_tree_view_get_vadjustment(GTK_TREE_VIEW(vfi->listview));
	page_size = (gint)adj->page_increment;

	row_height = thumb_max_height + THUMB_BORDER_PADDING * 2;
	if (vfi->show_text) row_height += thumb_max_height / 3;

	ret = page_size / row_height;
	if (ret < 1) ret = 1;

	return ret;
}

/*
 *-------------------------------------------------------------------
 * keyboard
 *-------------------------------------------------------------------
 */

static void vfi_menu_position_cb(GtkMenu *menu, gint *x, gint *y, gboolean *push_in, gpointer data)
{
	ViewFileIcon *vfi = data;
	GtkTreeModel *store;
	GtkTreeIter iter;
	gint column;
	GtkTreePath *tpath;
	gint cw, ch;

	if (!vficon_find_iter(vfi, vfi->click_fd, &iter, &column)) return;
	store = gtk_tree_view_get_model(GTK_TREE_VIEW(vfi->listview));
	tpath = gtk_tree_model_get_path(store, &iter);
	tree_view_get_cell_clamped(GTK_TREE_VIEW(vfi->listview), tpath, column, FALSE, x, y, &cw, &ch);
	gtk_tree_path_free(tpath);
	*y += ch;
	popup_menu_position_clamp(menu, x, y, 0);
}

static gint vficon_press_key_cb(GtkWidget *widget, GdkEventKey *event, gpointer data)
{
	ViewFileIcon *vfi = data;
	gint focus_row = 0;
	gint focus_col = 0;
	FileData *fd;
	gint stop_signal;

	stop_signal = TRUE;
	switch (event->keyval)
		{
		case GDK_Left: case GDK_KP_Left:
			focus_col = -1;
			break;
		case GDK_Right: case GDK_KP_Right:
			focus_col = 1;
			break;
		case GDK_Up: case GDK_KP_Up:
			focus_row = -1;
			break;
		case GDK_Down: case GDK_KP_Down:
			focus_row = 1;
			break;
		case GDK_Page_Up: case GDK_KP_Page_Up:
			focus_row = -page_height(vfi);
			break;
		case GDK_Page_Down: case GDK_KP_Page_Down:
			focus_row = page_height(vfi);
			break;
		case GDK_Home: case GDK_KP_Home:
			focus_row = -vfi->focus_row;
			focus_col = -vfi->focus_column;
			break;
		case GDK_End: case GDK_KP_End:
			focus_row = vfi->rows - 1 - vfi->focus_row;
			focus_col = vfi->columns - 1 - vfi->focus_column;
			break;
		case GDK_space:
			fd = vficon_find_data(vfi, vfi->focus_row, vfi->focus_column, NULL);
			if (fd)
				{
				vfi->click_fd = fd;
				if (event->state & GDK_CONTROL_MASK)
					{
					gint selected;

					selected = ICON_DATA(fd)->selected & SELECTION_SELECTED;
					if (selected)
						{
						vficon_unselect(vfi, fd);
						}
					else
						{
						vficon_select(vfi, fd);
						vficon_send_layout_select(vfi, fd);
						}
					}
				else
					{
					vficon_select_none(vfi);
					vficon_select(vfi, fd);
					vficon_send_layout_select(vfi, fd);
					}
				}
			break;
		case GDK_Menu:
			fd = vficon_find_data(vfi, vfi->focus_row, vfi->focus_column, NULL);
			vfi->click_fd = fd;

			vficon_selection_add(vfi, vfi->click_fd, SELECTION_PRELIGHT, NULL);
			tip_unschedule(vfi);

			vfi->popup = vficon_pop_menu(vfi, (fd != NULL));
			gtk_menu_popup(GTK_MENU(vfi->popup), NULL, NULL, vfi_menu_position_cb, vfi, 0, GDK_CURRENT_TIME);
			break;
		default:
			stop_signal = FALSE;
			break;
		}

	if (focus_row != 0 || focus_col != 0)
		{
		FileData *new_fd;
		FileData *old_fd;

		old_fd = vficon_find_data(vfi, vfi->focus_row, vfi->focus_column, NULL);
		vficon_move_focus(vfi, focus_row, focus_col, TRUE);
		new_fd = vficon_find_data(vfi, vfi->focus_row, vfi->focus_column, NULL);

		if (new_fd != old_fd)
			{
			if (event->state & GDK_SHIFT_MASK)
				{
				if (!collection_rectangular_selection)
					{
					vficon_select_region_util(vfi, old_fd, new_fd, FALSE);
					}
				else
					{
					vficon_select_region_util(vfi, vfi->click_fd, old_fd, FALSE);
					}
				vficon_select_region_util(vfi, vfi->click_fd, new_fd, TRUE);
				vficon_send_layout_select(vfi, new_fd);
				}
			else if (event->state & GDK_CONTROL_MASK)
				{
				vfi->click_fd = new_fd;
				}
			else
				{
				vfi->click_fd = new_fd;
				vficon_select_none(vfi);
				vficon_select(vfi, new_fd);
				vficon_send_layout_select(vfi, new_fd);
				}
			}
		}

	if (stop_signal)
		{
#if 0
		g_signal_stop_emission_by_name(GTK_OBJECT(widget), "key_press_event");
#endif
		tip_unschedule(vfi);
		}

	return stop_signal;
}

/*
 *-------------------------------------------------------------------
 * mouse
 *-------------------------------------------------------------------
 */

static gint vficon_motion_cb(GtkWidget *widget, GdkEventButton *bevent, gpointer data)
{
	ViewFileIcon *vfi = data;
	FileData *fd;

	fd = vficon_find_data_by_coord(vfi, (gint)bevent->x, (gint)bevent->y, NULL);
	tip_update(vfi, fd);

	return FALSE;
}

static gint vficon_press_cb(GtkWidget *widget, GdkEventButton *bevent, gpointer data)
{
	ViewFileIcon *vfi = data;
	GtkTreeIter iter;
	FileData *fd;

	tip_unschedule(vfi);
	
	fd = vficon_find_data_by_coord(vfi, (gint)bevent->x, (gint)bevent->y, &iter);

	vfi->click_fd = fd;
	vficon_selection_add(vfi, vfi->click_fd, SELECTION_PRELIGHT, &iter);

	switch (bevent->button)
		{
		case 1:
			if (!GTK_WIDGET_HAS_FOCUS(vfi->listview))
				{
				gtk_widget_grab_focus(vfi->listview);
				}
#if 0
			if (bevent->type == GDK_2BUTTON_PRESS &&
			    vfi->layout)
				{
				vficon_selection_remove(vfi, vfi->click_fd, SELECTION_PRELIGHT, &iter);
				layout_image_full_screen_start(vfi->layout);
				}
#endif
			break;
		case 3:
			vfi->popup = vficon_pop_menu(vfi, (fd != NULL));
			gtk_menu_popup(GTK_MENU(vfi->popup), NULL, NULL, NULL, NULL, bevent->button, bevent->time);
			break;
		default:
			break;
		}

	return TRUE;
}

static gint vficon_release_cb(GtkWidget *widget, GdkEventButton *bevent, gpointer data)
{
	ViewFileIcon *vfi = data;
	GtkTreeIter iter;
	FileData *fd = NULL;
	gint was_selected = FALSE;

	tip_schedule(vfi);

	if ((gint)bevent->x != 0 || (gint) bevent->y != 0)
		{
		fd = vficon_find_data_by_coord(vfi, (gint)bevent->x, (gint)bevent->y, &iter);
		}

	if (vfi->click_fd)
		{
		vficon_selection_remove(vfi, vfi->click_fd, SELECTION_PRELIGHT, NULL);
		}

	if (fd) was_selected = (ICON_DATA(fd)->selected & SELECTION_SELECTED);

	if (bevent->button == 1 &&
	    fd && vfi->click_fd == fd)
		{
		vficon_set_focus(vfi, fd);
		
		if (bevent->state & GDK_CONTROL_MASK)
			{
			gint select;

			select = !(ICON_DATA(fd)->selected & SELECTION_SELECTED);
			if ((bevent->state & GDK_SHIFT_MASK) && vfi->prev_selection)
				{
				vficon_select_region_util(vfi, vfi->prev_selection, fd, select);
				}
			else
				{
				vficon_select_util(vfi, fd, select);
				}
			}
		else
			{
			vficon_select_none(vfi);

			if ((bevent->state & GDK_SHIFT_MASK) &&
			    vfi->prev_selection)
				{
				vficon_select_region_util(vfi, vfi->prev_selection, fd, TRUE);
				}
			else
				{
				vficon_select_util(vfi, fd, TRUE);
				was_selected = FALSE;
				}
			}
		}
	else if (bevent->button == 2 &&
		 fd && vfi->click_fd == fd)
		{
		vficon_select_util(vfi, fd, !(ICON_DATA(fd)->selected & SELECTION_SELECTED));
		}

	if (fd && !was_selected &&
	    (ICON_DATA(fd)->selected & SELECTION_SELECTED))
		{
		vficon_send_layout_select(vfi, fd);
		}

	return TRUE;
}

static gint vficon_leave_cb(GtkWidget *widget, GdkEventCrossing *event, gpointer data)
{
	ViewFileIcon *vfi = data;

	tip_unschedule(vfi);
	return FALSE;
}

/*
 *-------------------------------------------------------------------
 * population
 *-------------------------------------------------------------------
 */

static gboolean vficon_destroy_node_cb(GtkTreeModel *store, GtkTreePath *tpath, GtkTreeIter *iter, gpointer data)
{
	GList *list;

	gtk_tree_model_get(store, iter, FILE_COLUMN_POINTER, &list, -1);
	g_list_free(list);

	return FALSE;
}

static void vficon_clear_store(ViewFileIcon *vfi)
{
	GtkTreeModel *store;

	store = gtk_tree_view_get_model(GTK_TREE_VIEW(vfi->listview));
	gtk_tree_model_foreach(store, vficon_destroy_node_cb, NULL);

	gtk_list_store_clear(GTK_LIST_STORE(store));
}

static void vficon_set_thumb(ViewFileIcon *vfi, FileData *fd, GdkPixbuf *pb)
{
	GtkTreeModel *store;
	GtkTreeIter iter;
	GList *list;

	if (!vficon_find_iter(vfi, fd, &iter, NULL)) return;

	store = gtk_tree_view_get_model(GTK_TREE_VIEW(vfi->listview));

	if (pb) g_object_ref(pb);
	if (fd->pixbuf) g_object_unref(fd->pixbuf);
	fd->pixbuf = pb;

	gtk_tree_model_get(store, &iter, FILE_COLUMN_POINTER, &list, -1);
	gtk_list_store_set(GTK_LIST_STORE(store), &iter, FILE_COLUMN_POINTER, list, -1);
}

static GList *vficon_add_row(ViewFileIcon *vfi, GtkTreeIter *iter)
{
	GtkListStore *store;
	GList *list = NULL;
	gint i;

	for (i = 0; i < vfi->columns; i++) list = g_list_prepend(list, NULL);

	store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(vfi->listview)));
	gtk_list_store_append(store, iter);
	gtk_list_store_set(store, iter, FILE_COLUMN_POINTER, list, -1);

	return list;
}

static void vficon_populate(ViewFileIcon *vfi, gint resize, gint keep_position)
{
	GtkTreeModel *store;
	GtkTreePath *tpath;
	gint row;
	GList *work;
	FileData *visible_fd = NULL;

	vficon_verify_selections(vfi);

	store = gtk_tree_view_get_model(GTK_TREE_VIEW(vfi->listview));

	if (keep_position && GTK_WIDGET_REALIZED(vfi->listview) &&
	    gtk_tree_view_get_path_at_pos(GTK_TREE_VIEW(vfi->listview), 0, 0, &tpath, NULL, NULL, NULL))
		{
		GtkTreeIter iter;
		GList *list;

		gtk_tree_model_get_iter(store, &iter, tpath);
		gtk_tree_path_free(tpath);

		gtk_tree_model_get(store, &iter, FILE_COLUMN_POINTER, &list, -1);
		if (list) visible_fd = list->data;
		}

	vficon_clear_store(vfi);

	if (resize)
		{
		gint i;
		gint thumb_width;

		thumb_width = vficon_get_icon_width(vfi);

		for (i = 0; i < VFICON_MAX_COLUMNS; i++)
			{
			GtkTreeViewColumn *column;
			GtkCellRenderer *cell;
			GList *list;

			column = gtk_tree_view_get_column(GTK_TREE_VIEW(vfi->listview), i);
			gtk_tree_view_column_set_visible(column, (i < vfi->columns));
			gtk_tree_view_column_set_fixed_width(column, thumb_width + (THUMB_BORDER_PADDING * 6));

			list = gtk_tree_view_column_get_cell_renderers(column);
			cell = (list) ? list->data : NULL;
			g_list_free(list);

			if (cell && GQV_IS_CELL_RENDERER_ICON(cell))
				{
				g_object_set(G_OBJECT(cell), "fixed_width", thumb_width,
							     "fixed_height", thumb_max_height,
							     "show_text", vfi->show_text, NULL);
				}
			}
		if (GTK_WIDGET_REALIZED(vfi->listview)) gtk_tree_view_columns_autosize(GTK_TREE_VIEW(vfi->listview));
		}

	row = -1;
	work = vfi->list;
	while (work)
		{
		GList *list;
		GtkTreeIter iter;

		row++;

		list = vficon_add_row(vfi, &iter);
		while (work && list)
			{
			FileData *fd;

			fd = work->data;
			ICON_DATA(fd)->row = row;

			list->data = work->data;
			list = list->next;
			work = work->next;
			}
		}

	if (visible_fd &&
	    gtk_tree_view_get_path_at_pos(GTK_TREE_VIEW(vfi->listview), 0, 0, &tpath, NULL, NULL, NULL))
		{
		GtkTreeIter iter;
		GList *list;

		gtk_tree_model_get_iter(store, &iter, tpath);
		gtk_tree_path_free(tpath);

		gtk_tree_model_get(store, &iter, FILE_COLUMN_POINTER, &list, -1);
		if (g_list_find(list, visible_fd) == NULL &&
		    vficon_find_iter(vfi, visible_fd, &iter, NULL))
			{
			tree_view_row_make_visible(GTK_TREE_VIEW(vfi->listview), &iter, FALSE);
			}
		}

	vfi->rows = row + 1;

	vficon_send_update(vfi);
	vficon_thumb_update(vfi);
}

static void vficon_populate_at_new_size(ViewFileIcon *vfi, gint w, gint h, gint force)
{
	gint new_cols;
	gint thumb_width;

	thumb_width = vficon_get_icon_width(vfi);

	new_cols = w / (thumb_width + (THUMB_BORDER_PADDING * 6));
	if (new_cols < 1) new_cols = 1;

	if (!force && new_cols == vfi->columns) return;

	vfi->columns = new_cols;

	vficon_populate(vfi, TRUE, TRUE);

	if (debug) printf("col tab pop cols=%d rows=%d\n", vfi->columns, vfi->rows);
}

static void vficon_sync(ViewFileIcon *vfi)
{
	GtkTreeModel *store;
	GtkTreeIter iter;
	GList *work;
	gint r, c;

	if (vfi->rows == 0) return;

	store = gtk_tree_view_get_model(GTK_TREE_VIEW(vfi->listview));

	r = -1;
	c = 0;

	work = vfi->list;
	while (work)
		{
		GList *list;
		r++;
		c = 0;
		if (gtk_tree_model_iter_nth_child(store, &iter, NULL, r))
			{
			gtk_tree_model_get(store, &iter, FILE_COLUMN_POINTER, &list, -1);
			gtk_list_store_set(GTK_LIST_STORE(store), &iter, FILE_COLUMN_POINTER, list, -1);
			}
		else
			{
			list = vficon_add_row(vfi, &iter);
			}
		
		while (list)
			{
			FileData *fd;

			if (work)
				{
				fd = work->data;
				work = work->next;
				c++;

				ICON_DATA(fd)->row = r;
				}
			else
				{
				fd = NULL;
				}

			list->data = fd;
			list = list->next;
			}
		}

	r++;
	while (gtk_tree_model_iter_nth_child(store, &iter, NULL, r))
		{
		GList *list;

		gtk_tree_model_get(store, &iter, FILE_COLUMN_POINTER, &list, -1);
		gtk_list_store_remove(GTK_LIST_STORE(store), &iter);
		g_list_free(list);
		}

	vfi->rows = r;

	vficon_update_focus(vfi);
}

static gint vficon_sync_idle_cb(gpointer data)
{
	ViewFileIcon *vfi = data;

	if (vfi->sync_idle_id == -1) return FALSE;
	vfi->sync_idle_id = -1;

	vficon_sync(vfi);
	return FALSE;
}

static void vficon_sync_idle(ViewFileIcon *vfi)
{
	if (vfi->sync_idle_id == -1)
		{
		/* high priority, the view needs to be resynced before a redraw
		 * may contain invalid pointers at this time
		 */
		vfi->sync_idle_id = g_idle_add_full(G_PRIORITY_HIGH, vficon_sync_idle_cb, vfi, NULL);
		}
}

static void vficon_sized_cb(GtkWidget *widget, GtkAllocation *allocation, gpointer data)
{
	ViewFileIcon *vfi = data;

	vficon_populate_at_new_size(vfi, allocation->width, allocation->height, FALSE);
}

/*
 *-----------------------------------------------------------------------------
 * misc
 *-----------------------------------------------------------------------------
 */

void vficon_sort_set(ViewFileIcon *vfi, SortType type, gint ascend)
{
	if (vfi->sort_method == type && vfi->sort_ascend == ascend) return;

	vfi->sort_method = type;
	vfi->sort_ascend = ascend;

	if (!vfi->list) return;

	vfi->list = filelist_sort(vfi->list, vfi->sort_method, vfi->sort_ascend);
	vficon_sync(vfi);
}

/*
 *-----------------------------------------------------------------------------
 * thumb updates
 *-----------------------------------------------------------------------------
 */

static gint vficon_thumb_next(ViewFileIcon *vfi);

static void vficon_thumb_status(ViewFileIcon *vfi, gdouble val, const gchar *text)
{
	if (vfi->func_thumb_status)
		{
		vfi->func_thumb_status(vfi, val, text, vfi->data_thumb_status);
		}
}

static void vficon_thumb_cleanup(ViewFileIcon *vfi)
{
	vficon_thumb_status(vfi, 0.0, NULL);

	g_list_free(vfi->thumbs_list);
	vfi->thumbs_list = NULL;
	vfi->thumbs_count = 0;
	vfi->thumbs_running = FALSE;

	thumb_loader_free(vfi->thumbs_loader);
	vfi->thumbs_loader = NULL;

	vfi->thumbs_fd = NULL;
}

static void vficon_thumb_stop(ViewFileIcon *vfi)
{
	if (vfi->thumbs_running) vficon_thumb_cleanup(vfi);
}

static void vficon_thumb_do(ViewFileIcon *vfi, ThumbLoader *tl, FileData *fd)
{
	GdkPixbuf *pixbuf;

	if (!fd) return;

	pixbuf = thumb_loader_get_pixbuf(tl, TRUE);
	vficon_set_thumb(vfi, fd, pixbuf);
	g_object_unref(pixbuf);

	vficon_thumb_status(vfi, (gdouble)(vfi->thumbs_count) / g_list_length(vfi->list), _("Loading thumbs..."));
}

static void vficon_thumb_error_cb(ThumbLoader *tl, gpointer data)
{
	ViewFileIcon *vfi = data;

	if (vfi->thumbs_fd && vfi->thumbs_loader == tl)
		{
		vficon_thumb_do(vfi, tl, vfi->thumbs_fd);
		}

	while (vficon_thumb_next(vfi));
}

static void vficon_thumb_done_cb(ThumbLoader *tl, gpointer data)
{
	ViewFileIcon *vfi = data;

	if (vfi->thumbs_fd && vfi->thumbs_loader == tl)
		{
		vficon_thumb_do(vfi, tl, vfi->thumbs_fd);
		}

	while (vficon_thumb_next(vfi));
}

static gint vficon_thumb_next(ViewFileIcon *vfi)
{
	GtkTreePath *tpath;
	FileData *fd = NULL;

	if (!GTK_WIDGET_REALIZED(vfi->listview))
		{
		vficon_thumb_status(vfi, 0.0, NULL);
		return FALSE;
		}

	if (gtk_tree_view_get_path_at_pos(GTK_TREE_VIEW(vfi->listview), 0, 0, &tpath, NULL, NULL, NULL))
		{
		GtkTreeModel *store;
		GtkTreeIter iter;
		gint valid = TRUE;

		store = gtk_tree_view_get_model(GTK_TREE_VIEW(vfi->listview));
		gtk_tree_model_get_iter(store, &iter, tpath);
		gtk_tree_path_free(tpath);

		while (!fd && valid && tree_view_row_get_visibility(GTK_TREE_VIEW(vfi->listview), &iter, FALSE) == 0)
			{
			GList *list;

			gtk_tree_model_get(store, &iter, FILE_COLUMN_POINTER, &list, -1);

			while (!fd && list)
				{
				FileData *tfd = list->data;
				if (tfd && !tfd->pixbuf) fd = tfd;
				list = list->next;
				}

			valid = gtk_tree_model_iter_next(store, &iter);
			}
		}

	/* then find first undone */

	if (!fd)
		{
		GList *work = vfi->list;
		while (work && !fd)
			{
			FileData *fd_p = work->data;
			work = work->next;

			if (!fd_p->pixbuf) fd = fd_p;
			}
		}

	if (!fd)
		{
		/* done */
		vficon_thumb_cleanup(vfi);
		return FALSE;
		}

	vfi->thumbs_count++;

	vfi->thumbs_fd = fd;

	thumb_loader_free(vfi->thumbs_loader);

	vfi->thumbs_loader = thumb_loader_new(thumb_max_width, thumb_max_height);
	thumb_loader_set_callbacks(vfi->thumbs_loader,
				   vficon_thumb_done_cb,
				   vficon_thumb_error_cb,
				   NULL,
				   vfi);

	if (!thumb_loader_start(vfi->thumbs_loader, fd->path))
		{
		/* set icon to unknown, continue */
		if (debug) printf("thumb loader start failed %s\n", vfi->thumbs_loader->path);
		vficon_thumb_do(vfi, vfi->thumbs_loader, fd);

		return TRUE;
		}

	return FALSE;
}

static void vficon_thumb_update(ViewFileIcon *vfi)
{
	vficon_thumb_stop(vfi);

	vficon_thumb_status(vfi, 0.0, _("Loading thumbs..."));
	vfi->thumbs_running = TRUE;

	while (vficon_thumb_next(vfi));
}

/*
 *-----------------------------------------------------------------------------
 * row stuff
 *-----------------------------------------------------------------------------
 */

FileData *vficon_index_get_data(ViewFileIcon *vfi, gint row)
{
	return FILE_DATA(g_list_nth_data(vfi->list, row));
}

gchar *vficon_index_get_path(ViewFileIcon *vfi, gint row)
{
	FileData *fd;

	fd = g_list_nth_data(vfi->list, row);

	return (fd ? fd->path : NULL);
}

gint vficon_index_by_path(ViewFileIcon *vfi, const gchar *path)
{
	gint p = 0;
	GList *work;

	if (!path) return -1;

	work = vfi->list;
	while (work)
		{
		FileData *fd = work->data;
		if (strcmp(path, fd->path) == 0) return p;
		work = work->next;
		p++;
		}

	return -1;
}

gint vficon_count(ViewFileIcon *vfi, gint64 *bytes)
{
	if (bytes)
		{
		gint64 b = 0;
		GList *work;

		work = vfi->list;
		while (work)
			{
			FileData *fd = work->data;
			work = work->next;
			b += fd->size;
			}

		*bytes = b;
		}

	return g_list_length(vfi->list);
}

GList *vficon_get_list(ViewFileIcon *vfi)
{
	GList *list = NULL;
	GList *work;

	work = vfi->list;
	while (work)
		{
		FileData *fd = work->data;
		work = work->next;

		list = g_list_prepend(list, g_strdup(fd->path));
		}

	return g_list_reverse(list);
}

/*
 *-----------------------------------------------------------------------------
 *
 *-----------------------------------------------------------------------------
 */

static gint vficon_refresh_real(ViewFileIcon *vfi, gint keep_position)
{
	gint ret = TRUE;
	GList *old_list;
	GList *work;
	FileData *focus_fd;

	focus_fd = vfi->focus_fd;

	old_list = vfi->list;
	vfi->list = NULL;

	if (vfi->path)
		{
		ret = iconlist_read(vfi->path, &vfi->list);
		}

	/* check for same files from old_list */
	work = old_list;
	while (work)
		{
		FileData *fd;
		GList *needle;

		fd = work->data;
		needle = vfi->list;
		while (needle)
			{
			FileData *fdn = needle->data;
			if (strcmp(fd->name, fdn->name) == 0)
				{
				/* swap, to retain old thumb, selection */
				needle->data = fd;
				work->data = fdn;
				needle = NULL;

				if (fd->date != fdn->date || fd->size != fdn->size)
					{
					/* file changed, update */
					fd->date = fdn->date;
					fd->size = fdn->size;
					vficon_set_thumb(vfi, fd, NULL);
					}
				}
			else
				{
				needle = needle->next;
				}
			}

		work = work->next;
		}

	vfi->list = filelist_sort(vfi->list, vfi->sort_method, vfi->sort_ascend);

	work = old_list;
	while (work)
		{
		FileData *fd = work->data;
		work = work->next;

		if (fd == vfi->prev_selection) vfi->prev_selection = NULL;
		if (fd == vfi->click_fd) vfi->click_fd = NULL;
		}

	vficon_populate(vfi, TRUE, keep_position);

	/* attempt to keep focus on same icon when refreshing */
	if (focus_fd && g_list_find(vfi->list, focus_fd))
		{
		vficon_set_focus(vfi, focus_fd);
		}

	iconlist_free(old_list);

	return ret;
}

gint vficon_refresh(ViewFileIcon *vfi)
{
	return vficon_refresh_real(vfi, TRUE);
}

/*
 *-----------------------------------------------------------------------------
 * draw, etc.
 *-----------------------------------------------------------------------------
 */

typedef struct _ColumnData ColumnData;
struct _ColumnData
{
	ViewFileIcon *vfi;
	gint number;
};

static void vficon_cell_data_cb(GtkTreeViewColumn *tree_column, GtkCellRenderer *cell,
				GtkTreeModel *tree_model, GtkTreeIter *iter, gpointer data)
{
	ColumnData *cd = data;
	ViewFileIcon *vfi;
	GtkStyle *style;
	GList *list;
	FileData *fd;
	GdkColor color_fg;
	GdkColor color_bg;

	vfi = cd->vfi;

	gtk_tree_model_get(tree_model, iter, FILE_COLUMN_POINTER, &list, -1);
	fd = g_list_nth_data(list, cd->number);

	style = gtk_widget_get_style(vfi->listview);
	if (fd && ICON_DATA(fd)->selected & SELECTION_SELECTED)
		{
		memcpy(&color_fg, &style->text[GTK_STATE_SELECTED], sizeof(color_fg));
		memcpy(&color_bg, &style->base[GTK_STATE_SELECTED], sizeof(color_bg));
		}
	else
		{
		memcpy(&color_fg, &style->text[GTK_STATE_NORMAL], sizeof(color_fg));
		memcpy(&color_bg, &style->base[GTK_STATE_NORMAL], sizeof(color_bg));
		}

	if (fd && ICON_DATA(fd)->selected & SELECTION_PRELIGHT)
		{
#if 0
		shift_color(&color_fg, -1, 0);
#endif
		shift_color(&color_bg, -1, 0);
		}

	if (GQV_IS_CELL_RENDERER_ICON(cell))
                {
		if (fd)
			{
			g_object_set(cell,	"pixbuf", fd->pixbuf,
						"text", fd->name,
						"cell-background-gdk", &color_bg,
						"cell-background-set", TRUE,
						"foreground-gdk", &color_fg,
						"foreground-set", TRUE,
						"has-focus", (vfi->focus_fd == fd), NULL);
			}
		else
			{
			g_object_set(cell,	"pixbuf", NULL,
						"text", NULL,
						"cell-background-set", FALSE,
						"foreground-set", FALSE,
						"has-focus", FALSE, NULL);
			}	
		}
}

static void vficon_append_column(ViewFileIcon *vfi, gint n)
{
	ColumnData *cd;
	GtkTreeViewColumn *column;
	GtkCellRenderer *renderer;

	column = gtk_tree_view_column_new();
	gtk_tree_view_column_set_min_width(column, 0);

	gtk_tree_view_column_set_sizing(column, GTK_TREE_VIEW_COLUMN_FIXED);
	gtk_tree_view_column_set_alignment(column, 0.5);

	renderer = gqv_cell_renderer_icon_new();
	gtk_tree_view_column_pack_start(column, renderer, FALSE);
	g_object_set(G_OBJECT(renderer), "xpad", THUMB_BORDER_PADDING * 2,
					 "ypad", THUMB_BORDER_PADDING,
					 "mode", GTK_CELL_RENDERER_MODE_ACTIVATABLE, NULL);

	g_object_set_data(G_OBJECT(column), "column_number", GINT_TO_POINTER(n));

	cd = g_new0(ColumnData, 1);
	cd->vfi = vfi;
	cd->number = n;
	gtk_tree_view_column_set_cell_data_func(column, renderer, vficon_cell_data_cb, cd, g_free);

	gtk_tree_view_append_column(GTK_TREE_VIEW(vfi->listview), column);
}

/*
 *-----------------------------------------------------------------------------
 * base
 *-----------------------------------------------------------------------------
 */

gint vficon_set_path(ViewFileIcon *vfi, const gchar *path)
{
	gint ret;

	if (!path) return FALSE;
	if (vfi->path && strcmp(path, vfi->path) == 0) return TRUE;

	g_free(vfi->path);
	vfi->path = g_strdup(path);

	g_list_free(vfi->selection);
	vfi->selection = NULL;

	iconlist_free(vfi->list);
	vfi->list = NULL;

	/* NOTE: populate will clear the store for us */
	ret = vficon_refresh_real(vfi, FALSE);

	vfi->focus_fd = NULL;
	vficon_move_focus(vfi, 0, 0, FALSE);

	return ret;
}

static void vficon_destroy_cb(GtkWidget *widget, gpointer data)
{
	ViewFileIcon *vfi = data;

	if (vfi->popup)
		{
		g_signal_handlers_disconnect_matched(G_OBJECT(vfi->popup), G_SIGNAL_MATCH_DATA,
						     0, 0, 0, NULL, vfi);
		gtk_widget_destroy(vfi->popup);
		}

	if (vfi->sync_idle_id != -1) g_source_remove(vfi->sync_idle_id);

	tip_unschedule(vfi);

	vficon_thumb_cleanup(vfi);

	g_free(vfi->path);

	iconlist_free(vfi->list);
	g_list_free(vfi->selection);
	g_free(vfi);
}

ViewFileIcon *vficon_new(const gchar *path)
{
	ViewFileIcon *vfi;
	GtkListStore *store;
	GtkTreeSelection *selection;
	gint i;

	vfi = g_new0(ViewFileIcon, 1);

	vfi->path = NULL;
	vfi->sort_method = SORT_NAME;
	vfi->sort_ascend = TRUE;

	vfi->selection = NULL;
	vfi->prev_selection = NULL;

	vfi->tip_window = NULL;
	vfi->tip_delay_id = -1;

	vfi->focus_row = 0;
	vfi->focus_column = 0;
	vfi->focus_fd = NULL;

	vfi->show_text = show_icon_names;

	vfi->sync_idle_id = -1;

	vfi->popup = NULL;

	vfi->widget = gtk_scrolled_window_new(NULL, NULL);
	gtk_scrolled_window_set_shadow_type(GTK_SCROLLED_WINDOW(vfi->widget), GTK_SHADOW_IN);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(vfi->widget),
				       GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
	g_signal_connect(G_OBJECT(vfi->widget), "destroy",
			 G_CALLBACK(vficon_destroy_cb), vfi);

	store = gtk_list_store_new(1, G_TYPE_POINTER);
	vfi->listview = gtk_tree_view_new_with_model(GTK_TREE_MODEL(store));
	g_object_unref(store);

	selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(vfi->listview));
	gtk_tree_selection_set_mode(GTK_TREE_SELECTION(selection), GTK_SELECTION_NONE);

	gtk_tree_view_set_headers_visible(GTK_TREE_VIEW(vfi->listview), FALSE);
	gtk_tree_view_set_enable_search(GTK_TREE_VIEW(vfi->listview), FALSE);

	for (i = 0; i < VFICON_MAX_COLUMNS; i++)
		{
		vficon_append_column(vfi, i);
		}

	/* zero width column to hide tree view focus, we draw it ourselves */
	vficon_append_column(vfi, i);
	/* end column to fill white space */
	vficon_append_column(vfi, i);

	g_signal_connect(G_OBJECT(vfi->listview), "size_allocate",
			 G_CALLBACK(vficon_sized_cb), vfi);
	g_signal_connect(G_OBJECT(vfi->listview), "key_press_event",
			 G_CALLBACK(vficon_press_key_cb), vfi);

	gtk_container_add(GTK_CONTAINER(vfi->widget), vfi->listview);
	gtk_widget_show(vfi->listview);

	vficon_dnd_init(vfi);

	gtk_widget_set_events(vfi->listview, GDK_POINTER_MOTION_MASK | GDK_BUTTON_RELEASE_MASK |
			      GDK_BUTTON_PRESS_MASK | GDK_LEAVE_NOTIFY_MASK);
	g_signal_connect(G_OBJECT(vfi->listview), "button_press_event",
			 G_CALLBACK(vficon_press_cb), vfi);
	g_signal_connect(G_OBJECT(vfi->listview), "button_release_event",
			 G_CALLBACK(vficon_release_cb), vfi);
	g_signal_connect(G_OBJECT(vfi->listview),"motion_notify_event",
			 G_CALLBACK(vficon_motion_cb), vfi);
	g_signal_connect(G_OBJECT(vfi->listview), "leave_notify_event",
			 G_CALLBACK(vficon_leave_cb), vfi);

	/* force vfi->columns to be at least 1 (sane) - this will be corrected in the size_cb */
	vficon_populate_at_new_size(vfi, 1, 1, FALSE);

	if (path) vficon_set_path(vfi, path);

	return vfi;
}

void vficon_set_status_func(ViewFileIcon *vfi,
			    void (*func)(ViewFileIcon *vfi, gpointer data), gpointer data)
{
	vfi->func_status = func;
	vfi->data_status = data;
}

void vficon_set_thumb_status_func(ViewFileIcon *vfi,
				  void (*func)(ViewFileIcon *vfi, gdouble val, const gchar *text, gpointer data),
				  gpointer data)
{
	vfi->func_thumb_status = func;
	vfi->data_thumb_status = data;
}

void vficon_set_layout(ViewFileIcon *vfi, LayoutWindow *layout)
{
	vfi->layout = layout;
}

/*
 *-----------------------------------------------------------------------------
 * maintenance (for rename, move, remove)
 *-----------------------------------------------------------------------------
 */

static gint vficon_maint_find_closest(ViewFileIcon *vfi, gint row, gint count, GList *ignore_list)
{
	GList *list = NULL;
	GList *work;
	gint rev = row - 1;
	row ++;

	work = ignore_list;
	while (work)
		{
		gint f = vficon_index_by_path(vfi, work->data);
		if (f >= 0) list = g_list_prepend(list, GINT_TO_POINTER(f));
		work = work->next;
		}

	while (list)
		{
		gint c = TRUE;
		work = list;
		while (work && c)
			{
			gpointer p = work->data;
			work = work->next;
			if (row == GPOINTER_TO_INT(p))
				{
				row++;
				c = FALSE;
				}
			if (rev == GPOINTER_TO_INT(p))
				{
				rev--;
				c = FALSE;
				}
			if (!c) list = g_list_remove(list, p);
			}
		if (c && list)
			{
			g_list_free(list);
			list = NULL;
			}
		}
	if (row > count - 1)
		{
		if (rev < 0)
			return -1;
		else
			return rev;
		}
	else
		{
		return row;
		}
}

gint vficon_maint_renamed(ViewFileIcon *vfi, const gchar *source, const gchar *dest)
{
	gint ret = FALSE;
	gint row;
	gchar *source_base;
	gchar *dest_base;
	GList *work;
	FileData *fd;

	row = vficon_index_by_path(vfi, source);
	if (row < 0) return FALSE;

	source_base = remove_level_from_path(source);
	dest_base = remove_level_from_path(dest);

	work = g_list_nth(vfi->list, row);
	fd = work->data;

	if (strcmp(source_base, dest_base) == 0)
		{
		vfi->list = g_list_remove(vfi->list, fd);
		g_free(fd->path);

		fd->path = g_strdup(dest);
		fd->name = filename_from_path(fd->path);

		vfi->list = filelist_insert_sort(vfi->list, fd, vfi->sort_method, vfi->sort_ascend);

		vficon_sync_idle(vfi);
		ret = TRUE;
		}
	else
		{
		ret = vficon_maint_removed(vfi, source, NULL);
		}

	g_free(source_base);
	g_free(dest_base);

	return ret;
}

gint vficon_maint_removed(ViewFileIcon *vfi, const gchar *path, GList *ignore_list)
{
	FileData *fd;
	gint row;
	gint new_row = -1;
	GtkTreeModel *store;
	GtkTreeIter iter;

	row = vficon_index_by_path(vfi, path);
	if (row < 0) return FALSE;

	fd = g_list_nth_data(vfi->list, row);
	if (!fd) return FALSE;

	if ((ICON_DATA(fd)->selected & SELECTION_SELECTED) &&
	    layout_image_get_collection(vfi->layout, NULL) == NULL)
		{
		vficon_unselect(vfi, fd);

		if (!vfi->selection)
			{
			gint n;

			n = vficon_count(vfi, NULL);
			if (ignore_list)
				{
				new_row = vficon_maint_find_closest(vfi, row, n, ignore_list);
				if (debug) printf("row = %d, closest is %d\n", row, new_row);
				}
			else
				{
				if (row + 1 < n)
					{
					new_row = row + 1;
					}
				else if (row > 0)
					{
					new_row = row - 1;
					}
				}
			}
		else if (ignore_list)
			{
			GList *work;

			work = vfi->selection;
			while (work)
				{
				FileData *ignore_fd;
				GList *tmp;
				gint match = FALSE;

				ignore_fd = work->data;
				work = work->next;

				tmp = ignore_list;
				while (tmp && !match)
					{
					const gchar *ignore_path;

					ignore_path = tmp->data;
					tmp = tmp->next;

					if (strcmp(ignore_fd->path, ignore_path) == 0)
						{
						match = TRUE;
						}
					}
				if (!match)
					{
					new_row = g_list_index(vfi->list, ignore_fd);
					work = NULL;
					}
				}
			if (new_row == -1)
				{
				/* selection all ignored, use closest */
				new_row = vficon_maint_find_closest(vfi, row, vficon_count(vfi, NULL), ignore_list);
				}
			}
		else
			{
			new_row = g_list_index(vfi->list, vfi->selection->data);
			}
		if (new_row >= 0)
			{
			FileData *fdn;

			fdn = g_list_nth_data(vfi->list, new_row);
			vficon_select(vfi, fdn);
			vficon_send_layout_select(vfi, fdn);
			}
		}

	/* Thumb loader check */
	if (fd == vfi->thumbs_fd) vfi->thumbs_fd = NULL;
	if (vfi->thumbs_count > 0) vfi->thumbs_count--;

	if (vfi->prev_selection == fd) vfi->prev_selection = NULL;
	if (vfi->click_fd == fd) vfi->click_fd = NULL;

	/* remove pointer to this fd from grid */
	store = gtk_tree_view_get_model(GTK_TREE_VIEW(vfi->listview));
	if (ICON_DATA(fd)->row >= 0 &&
	    gtk_tree_model_iter_nth_child(store, &iter, NULL, ICON_DATA(fd)->row))
		{
		GList *list;

		gtk_tree_model_get(store, &iter, FILE_COLUMN_POINTER, &list, -1);
		list = g_list_find(list, fd);
		if (list) list->data = NULL;
		}

	vfi->list = g_list_remove(vfi->list, fd);
	file_data_free(fd);

	vficon_sync_idle(vfi);
	vficon_send_update(vfi);

	return TRUE;
}

gint vficon_maint_moved(ViewFileIcon *vfi, const gchar *source, const gchar *dest, GList *ignore_list)
{
	gint ret = FALSE;
	gchar *buf;

	if (!source || !vfi->path) return FALSE;

	buf = remove_level_from_path(source);

	if (strcmp(buf, vfi->path) == 0)
		{
		ret = vficon_maint_removed(vfi, source, ignore_list);
		}

	g_free(buf);

	return ret;
}

