/*
 * GQview
 * (C) 2005 John Ellis
 *
 * Author: John Ellis
 *
 * This software is released under the GNU General Public License (GNU GPL).
 * Please read the included file COPYING for more information.
 * This software comes with no warranty of any kind, use at your own risk!
 */


#include "gqview.h"
#include "search.h"

#include "bar_info.h"
#include "cache.h"
#include "collect.h"
#include "collect-table.h"
#include "dnd.h"
#include "dupe.h"
#include "image-load.h"
#include "info.h"
#include "editors.h"
#include "img-view.h"
#include "filelist.h"
#include "layout_image.h"
#include "menu.h"
#include "print.h"
#include "thumb.h"
#include "utilops.h"
#include "ui_bookmark.h"
#include "ui_fileops.h"
#include "ui_menu.h"
#include "ui_misc.h"
#include "ui_spinner.h"
#include "ui_tabcomp.h"
#include "ui_tree_edit.h"

#include <gdk/gdkkeysyms.h> /* for keyboard values */


#define DEF_SEARCH_WIDTH  700
#define DEF_SEARCH_HEIGHT 450

#define SEARCH_BUFFER_MATCH_LOAD 20
#define SEARCH_BUFFER_MATCH_HIT  5
#define SEARCH_BUFFER_MATCH_MISS 1
#define SEARCH_BUFFER_FLUSH_SIZE 99


typedef enum {
	SEARCH_MATCH_NONE,
	SEARCH_MATCH_EQUAL,
	SEARCH_MATCH_CONTAINS,
	SEARCH_MATCH_UNDER,
	SEARCH_MATCH_OVER,
	SEARCH_MATCH_BETWEEN,
	SEARCH_MATCH_ALL,
	SEARCH_MATCH_ANY
} MatchType;

enum {
	SEARCH_COLUMN_POINTER = 0,
	SEARCH_COLUMN_RANK,
	SEARCH_COLUMN_THUMB,
	SEARCH_COLUMN_NAME,
	SEARCH_COLUMN_SIZE,
	SEARCH_COLUMN_DATE,
	SEARCH_COLUMN_DIMENSIONS,
	SEARCH_COLUMN_PATH,
	SEARCH_COLUMN_COUNT	/* total columns */
};

typedef struct _SearchData SearchData;
struct _SearchData
{
	GtkWidget *window;

	GtkWidget *button_thumbs;
	GtkWidget *label_status;
	GtkWidget *label_progress;
	GtkWidget *button_start;
	GtkWidget *button_stop;
	GtkWidget *spinner;

	GtkWidget *box_search;

	GtkWidget *menu_path;
	GtkWidget *path_entry;
	GtkWidget *check_recurse;

	GtkWidget *result_view;

	GtkWidget *check_name;
	GtkWidget *menu_name;
	GtkWidget *entry_name;
	GtkWidget *check_name_match_case;

	GtkWidget *check_size;
	GtkWidget *menu_size;
	GtkWidget *spin_size;
	GtkWidget *spin_size_end;

	GtkWidget *check_date;
	GtkWidget *menu_date;
	GtkWidget *date_sel;
	GtkWidget *date_sel_end;

	GtkWidget *check_dimensions;
	GtkWidget *menu_dimensions;
	GtkWidget *spin_width;
	GtkWidget *spin_height;
	GtkWidget *spin_width_end;
	GtkWidget *spin_height_end;

	GtkWidget *check_similarity;
	GtkWidget *spin_similarity;
	GtkWidget *entry_similarity;

	GtkWidget *check_keywords;
	GtkWidget *menu_keywords;
	GtkWidget *entry_keywords;

	gchar *search_path;
	gint   search_path_recurse;
	gchar *search_name;
	gint   search_name_match_case;
	gint64 search_size;
	gint64 search_size_end;
	gint   search_date_y;
	gint   search_date_m;
	gint   search_date_d;
	gint   search_date_end_y;
	gint   search_date_end_m;
	gint   search_date_end_d;
	gint   search_width;
	gint   search_height;
	gint   search_width_end;
	gint   search_height_end;
	gint   search_similarity;
	gchar *search_similarity_path;
	CacheData *search_similarity_cd;
	GList *search_keyword_list;

	MatchType search_type;

	MatchType match_name;
	MatchType match_size;
	MatchType match_date;
	MatchType match_dimensions;
	MatchType match_keywords;

	gboolean match_name_enable;
	gboolean match_size_enable;
	gboolean match_date_enable;
	gboolean match_dimensions_enable;
	gboolean match_similarity_enable;
	gboolean match_keywords_enable;

	GList *search_folder_list;
	GList *search_done_list;
	GList *search_file_list;
	GList *search_buffer_list;

	gint search_count;
	gint search_total;
	gint search_buffer_count;

	gint search_idle_id;
	gint update_idle_id;

	ImageLoader *img_loader;
	CacheData   *img_cd;

	FileData *click_fd;

	ThumbLoader *thumb_loader;
	gint thumb_enable;
	FileData *thumb_fd;
};

typedef struct _MatchFileData MatchFileData;
struct _MatchFileData
{
	FileData fd;
	gint width;
	gint height;
	gint rank;
};

typedef struct _MatchList MatchList;
struct _MatchList
{
	const gchar *text;
	const MatchType type;
};

static const MatchList text_search_menu_path[] = {
	{ N_("folder"),		SEARCH_MATCH_NONE },
	{ N_("comments"),	SEARCH_MATCH_ALL },
	{ N_("results"),	SEARCH_MATCH_CONTAINS }
};

static const MatchList text_search_menu_name[] = {
	{ N_("contains"),	SEARCH_MATCH_CONTAINS },
	{ N_("is"),		SEARCH_MATCH_EQUAL }
};

static const MatchList text_search_menu_size[] = {
	{ N_("equal to"),	SEARCH_MATCH_EQUAL },
	{ N_("less than"),	SEARCH_MATCH_UNDER },
	{ N_("greater than"),	SEARCH_MATCH_OVER },
	{ N_("between"),	SEARCH_MATCH_BETWEEN }
};

static const MatchList text_search_menu_date[] = {
	{ N_("equal to"),	SEARCH_MATCH_EQUAL },
	{ N_("before"),		SEARCH_MATCH_UNDER },
	{ N_("after"),		SEARCH_MATCH_OVER },
	{ N_("between"),	SEARCH_MATCH_BETWEEN }
};

static const MatchList text_search_menu_keyword[] = {
	{ N_("match all"),	SEARCH_MATCH_ALL },
	{ N_("match any"),	SEARCH_MATCH_ANY },
	{ N_("exclude"),	SEARCH_MATCH_NONE }
};

static GList *search_window_list = NULL;


static gint search_result_selection_count(SearchData *sd, gint64 *bytes);
static gint search_result_count(SearchData *sd, gint64 *bytes);

static void search_window_close(SearchData *sd);


/*
 *-------------------------------------------------------------------
 * utils
 *-------------------------------------------------------------------
 */

static time_t convert_dmy_to_time(gint day, gint month, gint year)
{
	struct tm lt;

	lt.tm_sec = 0;
	lt.tm_min = 0;
	lt.tm_hour = 0;
	lt.tm_mday = day;
	lt.tm_mon = month - 1;
	lt.tm_year = year - 1900;
	lt.tm_isdst = 0;

	return mktime(&lt);
}

static void search_status_update(SearchData *sd)
{
	gchar *buf;
	gint t;
	gint s;
	gint64 t_bytes;
	gint64 s_bytes;
	gchar *tt;
	gchar *ts;

	t = search_result_count(sd, &t_bytes);
	s = search_result_selection_count(sd, &s_bytes);

	if (s > 0)
		{
		tt = text_from_size_abrev(t_bytes);
		ts = text_from_size_abrev(s_bytes);
		buf = g_strdup_printf(_("%s, %d files (%s, %d)"), tt, t, ts, s);
		g_free(tt);
		g_free(ts);
		}
	else
		{
		tt = text_from_size_abrev(t_bytes);
		buf = g_strdup_printf(_("%s, %d files"), tt, t);
		g_free(tt);
		}

	gtk_label_set_text(GTK_LABEL(sd->label_status), buf);
	g_free(buf);
}

static void search_progress_update(SearchData *sd, gint search, gdouble thumbs)
{

	if (search || thumbs >= 0.0)
		{
		gchar *buf;
		const gchar *message;

		if (search && (sd->search_folder_list || sd->search_file_list))
			message = _("Searching...");
		else if (thumbs >= 0.0)
			message = _("Loading thumbs...");
		else
			message = "";

		buf = g_strdup_printf("%s(%d / %d)", message, sd->search_count, sd->search_total);
		gtk_progress_bar_set_text(GTK_PROGRESS_BAR(sd->label_progress), buf);
		gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(sd->label_progress),
					      (thumbs >= 0.0) ? thumbs : 0.0);
		g_free(buf);
		}
	else
		{
		gtk_progress_bar_set_text(GTK_PROGRESS_BAR(sd->label_progress), "");
		gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(sd->label_progress), 0.0);
		}
}

/*
 *-------------------------------------------------------------------
 * result list
 *-------------------------------------------------------------------
 */

static gint search_result_find_row(SearchData *sd, FileData *fd, GtkTreeIter *iter)
{
	GtkTreeModel *store;
	gint valid;
	gint n = 0;

	store = gtk_tree_view_get_model(GTK_TREE_VIEW(sd->result_view));
	valid = gtk_tree_model_get_iter_first(store, iter);
	while (valid)
		{
		FileData *fd_n;
		n++;

		gtk_tree_model_get(store, iter, SEARCH_COLUMN_POINTER, &fd_n, -1);
		if (fd_n == fd) return n;
		valid = gtk_tree_model_iter_next(store, iter);
		}

	return -1;
}

static gint search_result_row_selected(SearchData *sd, FileData *fd)
{
	GtkTreeModel *store;
	GtkTreeSelection *selection;
	GList *slist;
	GList *work;
	gint found = FALSE;

	selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(sd->result_view));
	slist = gtk_tree_selection_get_selected_rows(selection, &store);
	work = slist;
	while (!found && work)
		{
		GtkTreePath *tpath = work->data;
		FileData *fd_n;
		GtkTreeIter iter;

		gtk_tree_model_get_iter(store, &iter, tpath);
		gtk_tree_model_get(store, &iter, SEARCH_COLUMN_POINTER, &fd_n, -1);
		if (fd_n == fd) found = TRUE;
		work = work->next;
		}
	g_list_foreach(slist, (GFunc)gtk_tree_path_free, NULL);
	g_list_free(slist);

	return found;
}

static gint search_result_selection_util(SearchData *sd, gint64 *bytes, GList **list)
{
	GtkTreeModel *store;
	GtkTreeSelection *selection;
	GList *slist;
	GList *work;
	gint n = 0;
	gint64 total = 0;
	GList *plist = NULL;

	store = gtk_tree_view_get_model(GTK_TREE_VIEW(sd->result_view));
	selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(sd->result_view));
	slist = gtk_tree_selection_get_selected_rows(selection, &store);
	work = slist;
	while (work)
		{
		n++;

		if (bytes || list)
			{
			GtkTreePath *tpath = work->data;
			FileData *fd;
			GtkTreeIter iter;

			gtk_tree_model_get_iter(store, &iter, tpath);
			gtk_tree_model_get(store, &iter, SEARCH_COLUMN_POINTER, &fd, -1);
			total += fd->size;

			if (list) plist = g_list_prepend(plist, g_strdup(fd->path));
			}
			
		work = work->next;
		}
	g_list_foreach(slist, (GFunc)gtk_tree_path_free, NULL);
	g_list_free(slist);

	if (bytes) *bytes = total;
	if (list) *list = g_list_reverse(plist);

	return n;
}

static GList *search_result_selection_list(SearchData *sd)
{
	GList *list;

	search_result_selection_util(sd, NULL, &list);
	return list;
}

static gint search_result_selection_count(SearchData *sd, gint64 *bytes)
{
	return search_result_selection_util(sd, bytes, NULL);
}

static gint search_result_util(SearchData *sd, gint64 *bytes, GList **list)
{
	GtkTreeModel *store;
	GtkTreeIter iter;
	gint valid;
	gint n = 0;
	gint64 total = 0;
	GList *plist = NULL;

	store = gtk_tree_view_get_model(GTK_TREE_VIEW(sd->result_view));

	valid = gtk_tree_model_get_iter_first(store, &iter);
	while (valid)
		{
		n++;
		if (bytes || list)
			{
			FileData *fd;

			gtk_tree_model_get(store, &iter, SEARCH_COLUMN_POINTER, &fd, -1);
			total += fd->size;

			if (list) plist = g_list_prepend(plist, g_strdup(fd->path));
			}
		valid = gtk_tree_model_iter_next(store, &iter);
		}

	if (bytes) *bytes = total;
	if (list) *list = g_list_reverse(plist);

	return n;
}

static GList *search_result_get_path_list(SearchData *sd)
{
	GList *list = NULL;

	search_result_util(sd, NULL, &list);
	return list;
}

static gint search_result_count(SearchData *sd, gint64 *bytes)
{
	return search_result_util(sd, bytes, NULL);
}

static void search_result_append(SearchData *sd, MatchFileData *mfd)
{
	FileData *fd;
	GtkListStore *store;
	GtkTreeIter iter;
	gchar *text_size;
	gchar *text_dim = NULL;

	fd = (FileData *)mfd;

	if (!fd) return;

	text_size = text_from_size(fd->size);
	if (mfd->width > 0 && mfd->height > 0) text_dim = g_strdup_printf("%d x %d", mfd->width, mfd->height);

	store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(sd->result_view)));
	gtk_list_store_append(store, &iter);
	gtk_list_store_set(store, &iter,
				SEARCH_COLUMN_POINTER, fd,
				SEARCH_COLUMN_RANK, mfd->rank,
				SEARCH_COLUMN_THUMB, fd->pixbuf,
				SEARCH_COLUMN_NAME, fd->name,
				SEARCH_COLUMN_SIZE, text_size,
				SEARCH_COLUMN_DATE, text_from_time(fd->date),
				SEARCH_COLUMN_DIMENSIONS, text_dim,
				SEARCH_COLUMN_PATH, fd->path,
				-1);

	g_free(text_size);
	g_free(text_dim);
}

static GList *search_result_refine_list(SearchData *sd)
{
	GList *list = NULL;
	GtkTreeModel *store;
	GtkTreeIter iter;
	gint valid;

	store = gtk_tree_view_get_model(GTK_TREE_VIEW(sd->result_view));

	valid = gtk_tree_model_get_iter_first(store, &iter);
	while (valid)
		{
		FileData *fd;

		gtk_tree_model_get(store, &iter, SEARCH_COLUMN_POINTER, &fd, -1);
		list = g_list_prepend(list, fd);

		valid = gtk_tree_model_iter_next(store, &iter);
		}

	/* clear it here, so that the FileData in list is not freed */
	gtk_list_store_clear(GTK_LIST_STORE(store));

	return g_list_reverse(list);
}

static gboolean search_result_free_node(GtkTreeModel *store, GtkTreePath *tpath,
					GtkTreeIter *iter, gpointer data)
{
	FileData *fd;

	gtk_tree_model_get(store, iter, SEARCH_COLUMN_POINTER, &fd, -1);
	file_data_free(fd);

	return FALSE;
}

static void search_result_clear(SearchData *sd)
{
	GtkListStore *store;

	store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(sd->result_view)));

	gtk_tree_model_foreach(GTK_TREE_MODEL(store), search_result_free_node, sd);
	gtk_list_store_clear(store);

	sd->click_fd = NULL;

	thumb_loader_free(sd->thumb_loader);
	sd->thumb_loader = NULL;
	sd->thumb_fd = NULL;

	search_status_update(sd);
}

static void search_result_remove_item(SearchData *sd, FileData *fd, GtkTreeIter *iter)
{
	GtkTreeModel *store;

	if (!fd || !iter) return;

	store = gtk_tree_view_get_model(GTK_TREE_VIEW(sd->result_view));

	tree_view_move_cursor_away(GTK_TREE_VIEW(sd->result_view), iter, TRUE);

	gtk_list_store_remove(GTK_LIST_STORE(store), iter);
	if (sd->click_fd == fd) sd->click_fd = NULL;
	if (sd->thumb_fd == fd) sd->thumb_fd = NULL;
	file_data_free(fd);
}

static void search_result_remove(SearchData *sd, FileData *fd)
{
	GtkTreeModel *store;
	GtkTreeIter iter;
	gint valid;

	store = gtk_tree_view_get_model(GTK_TREE_VIEW(sd->result_view));
	valid = gtk_tree_model_get_iter_first(store, &iter);
	while (valid)
		{
		FileData *fd_n;

		gtk_tree_model_get(store, &iter, SEARCH_COLUMN_POINTER, &fd_n, -1);
		if (fd_n == fd)
			{
			search_result_remove_item(sd, fd_n, &iter);
			return;
			}

		valid = gtk_tree_model_iter_next(GTK_TREE_MODEL(store), &iter);
		}
}

static void search_result_remove_selection(SearchData *sd)
{
	GtkTreeSelection *selection;
	GtkTreeModel *store;
	GList *slist;
	GList *flist = NULL;
	GList *work;

	selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(sd->result_view));
	slist = gtk_tree_selection_get_selected_rows(selection, &store);
	work = slist;
	while (work)
		{
		GtkTreePath *tpath = work->data;
		GtkTreeIter iter;
		FileData *fd;

		gtk_tree_model_get_iter(store, &iter, tpath);
		gtk_tree_model_get(store, &iter, SEARCH_COLUMN_POINTER, &fd, -1);
		flist = g_list_prepend(flist, fd);
		work = work->next;
		}
	g_list_foreach(slist, (GFunc)gtk_tree_path_free, NULL);
	g_list_free(slist);

	work = flist;
	while (work)
		{
		FileData *fd = work->data;
		work = work->next;

		search_result_remove(sd, fd);
		}
	g_list_free(flist);

	search_status_update(sd);
}

static void search_result_edit_selected(SearchData *sd, gint n)
{
	GList *list;

	list = search_result_selection_list(sd);
	start_editor_from_path_list(n, list);
	path_list_free(list);
}

static void search_result_collection_from_selection(SearchData *sd)
{
	CollectWindow *w;
	GList *list;

	list = search_result_selection_list(sd);
	w = collection_window_new(NULL);
	collection_table_add_path_list(w->table, list);
	path_list_free(list);
}

static gint search_result_update_idle_cb(gpointer data)
{
	SearchData *sd = data;

	search_status_update(sd);

	sd->update_idle_id = -1;
	return FALSE;
}

static void search_result_update_idle_cancel(SearchData *sd)
{
	if (sd->update_idle_id != -1) g_source_remove(sd->update_idle_id);
	sd->update_idle_id = -1;
}

static gboolean search_result_select_cb(GtkTreeSelection *selection, GtkTreeModel *store,
					GtkTreePath *tpath, gboolean selected, gpointer data)
{
	SearchData *sd = data;

	if (sd->update_idle_id == -1)
		{
		sd->update_idle_id = g_idle_add(search_result_update_idle_cb, sd);
		}

	return TRUE;
}

/*
 *-------------------------------------------------------------------
 * result list thumbs
 *-------------------------------------------------------------------
 */

static void search_result_thumb_step(SearchData *sd);


static void search_result_thumb_set(SearchData *sd, FileData *fd, GtkTreeIter *iter)
{
	GtkListStore *store;
	GtkTreeIter iter_n;

	store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(sd->result_view)));
	if (!iter)
		{
		if (search_result_find_row(sd, fd, &iter_n) >= 0) iter = &iter_n;
		}

	if (iter) gtk_list_store_set(store, iter, SEARCH_COLUMN_THUMB, fd->pixbuf, -1);
}

static void search_result_thumb_do(SearchData *sd)
{
	FileData *fd;

	if (!sd->thumb_loader || !sd->thumb_fd) return;
	fd = sd->thumb_fd;

	if (fd->pixbuf) g_object_unref(fd->pixbuf);
	fd->pixbuf = thumb_loader_get_pixbuf(sd->thumb_loader, TRUE);

	search_result_thumb_set(sd, fd, NULL);
}

static void search_result_thumb_done_cb(ThumbLoader *tl, gpointer data)
{
	SearchData *sd = data;

	search_result_thumb_do(sd);
	search_result_thumb_step(sd);
}

static void search_result_thumb_step(SearchData *sd)
{
	GtkTreeModel *store;
	GtkTreeIter iter;
	FileData *fd = NULL;
	gint valid;
	gint row = 0;
	gint length = 0;

	if (!sd->thumb_enable) return;

	store = gtk_tree_view_get_model(GTK_TREE_VIEW(sd->result_view));

	valid = gtk_tree_model_get_iter_first(store, &iter);
	while (!fd && valid)
		{
		GdkPixbuf *pixbuf;

		length++;
		gtk_tree_model_get(store, &iter, SEARCH_COLUMN_POINTER, &fd, SEARCH_COLUMN_THUMB, &pixbuf, -1);
		if (pixbuf || fd->pixbuf)
			{
			if (!pixbuf) gtk_list_store_set(GTK_LIST_STORE(store), &iter, SEARCH_COLUMN_THUMB, fd->pixbuf, -1);
			row++;
			fd = NULL;
			}
		valid = gtk_tree_model_iter_next(store, &iter);
		}
	if (valid)
		{
		while (gtk_tree_model_iter_next(store, &iter)) length++;
		}

	if (!fd)
		{
		sd->thumb_fd = NULL;
		thumb_loader_free(sd->thumb_loader);
		sd->thumb_loader = NULL;

		search_progress_update(sd, TRUE, -1.0);
		return;
		}

	search_progress_update(sd, FALSE, (gdouble)row/length);

	sd->thumb_fd = fd;
	thumb_loader_free(sd->thumb_loader);
	sd->thumb_loader = thumb_loader_new(thumb_max_width, thumb_max_height);

	thumb_loader_set_callbacks(sd->thumb_loader,
				   search_result_thumb_done_cb,
				   search_result_thumb_done_cb,
				   NULL,
				   sd);
	if (!thumb_loader_start(sd->thumb_loader, fd->path))
		{
		search_result_thumb_do(sd);
		search_result_thumb_step(sd);
		}
}

static void search_result_thumb_height(SearchData *sd)
{
	GtkTreeViewColumn *column;
	GtkCellRenderer *cell;
	GList *list;

	column = gtk_tree_view_get_column(GTK_TREE_VIEW(sd->result_view), SEARCH_COLUMN_THUMB - 1);
	if (!column) return;

	gtk_tree_view_column_set_fixed_width(column, (sd->thumb_enable) ? thumb_max_width : 4);

	list = gtk_tree_view_column_get_cell_renderers(column);
	if (!list) return;
	cell = list->data;
	g_list_free(list);

	g_object_set(G_OBJECT(cell), "height", (sd->thumb_enable) ? thumb_max_height : -1, NULL);
	gtk_tree_view_columns_autosize(GTK_TREE_VIEW(sd->result_view));
}

static void search_result_thumb_enable(SearchData *sd, gint enable)
{
	if (sd->thumb_enable == enable) return;

	if (sd->thumb_enable)
		{
		GtkTreeModel *store;
		GtkTreeIter iter;
		gint valid;

		thumb_loader_free(sd->thumb_loader);
		sd->thumb_loader = NULL;

		store = gtk_tree_view_get_model(GTK_TREE_VIEW(sd->result_view));
		valid = gtk_tree_model_get_iter_first(store, &iter);
		while (valid)
			{
			gtk_list_store_set(GTK_LIST_STORE(store), &iter, SEARCH_COLUMN_THUMB, NULL, -1);
			valid = gtk_tree_model_iter_next(store, &iter);
			}
		search_progress_update(sd, TRUE, -1.0);
		}

	sd->thumb_enable = enable;

	search_result_thumb_height(sd);
	if (!sd->search_folder_list && !sd->search_file_list) search_result_thumb_step(sd);
}

/*
 *-------------------------------------------------------------------
 * result list menu
 *-------------------------------------------------------------------
 */

static void sr_menu_view_cb(GtkWidget *widget, gpointer data)
{
	SearchData *sd = data;

	if (sd->click_fd) layout_image_set_path(NULL, sd->click_fd->path);
}

static void sr_menu_viewnew_cb(GtkWidget *widget, gpointer data)
{
	SearchData *sd = data;
	GList *list;

	list = search_result_selection_list(sd);
	view_window_new_from_list(list);
	path_list_free(list);
}

static void sr_menu_select_all_cb(GtkWidget *widget, gpointer data)
{
	SearchData *sd = data;
	GtkTreeSelection *selection;

	selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(sd->result_view));
	gtk_tree_selection_select_all(selection);
}

static void sr_menu_select_none_cb(GtkWidget *widget, gpointer data)
{
	SearchData *sd = data;
	GtkTreeSelection *selection;

	selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(sd->result_view));
	gtk_tree_selection_unselect_all(selection);
}

static void sr_menu_edit_cb(GtkWidget *widget, gpointer data)
{
	SearchData *sd;
	gint n;

	sd = submenu_item_get_data(widget);
	n = GPOINTER_TO_INT(data);
	if (!sd) return;

	search_result_edit_selected(sd, n);
}

static void sr_menu_info_cb(GtkWidget *widget, gpointer data)
{
	SearchData *sd = data;

	info_window_new(NULL, search_result_selection_list(sd));
}

static void sr_menu_collection_cb(GtkWidget *widget, gpointer data)
{
	SearchData *sd = data;

	search_result_collection_from_selection(sd);
}

static void sr_menu_print_cb(GtkWidget *widget, gpointer data)
{
	SearchData *sd = data;
	const gchar *path;

	path = (sd->click_fd) ? sd->click_fd->path : NULL;

	print_window_new(path, search_result_selection_list(sd),
			 search_result_get_path_list(sd), sd->window);
}

static void sr_menu_copy_cb(GtkWidget *widget, gpointer data)
{
	SearchData *sd = data;

	file_util_copy(NULL, search_result_selection_list(sd), NULL, sd->window);
}

static void sr_menu_move_cb(GtkWidget *widget, gpointer data)
{
	SearchData *sd = data;

	file_util_move(NULL, search_result_selection_list(sd), NULL, sd->window);
}

static void sr_menu_rename_cb(GtkWidget *widget, gpointer data)
{
	SearchData *sd = data;

	file_util_rename(NULL, search_result_selection_list(sd), sd->window);
}

static void sr_menu_delete_cb(GtkWidget *widget, gpointer data)
{
	SearchData *sd = data;

	file_util_delete(NULL, search_result_selection_list(sd), sd->window);
}

static void sr_menu_remove_cb(GtkWidget *widget, gpointer data)
{
	SearchData *sd = data;

	search_result_remove_selection(sd);
}

static void sr_menu_clear_cb(GtkWidget *widget, gpointer data)
{
	SearchData *sd = data;

	search_result_clear(sd);
}

static GtkWidget *search_result_menu(SearchData *sd, gint on_row, gint empty)
{
	GtkWidget *menu;
	GtkWidget *item;

	menu = popup_menu_short_lived();
	menu_item_add_sensitive(menu, _("_View"), on_row,
				G_CALLBACK(sr_menu_view_cb), sd);
	menu_item_add_stock_sensitive(menu, _("View in _new window"), GTK_STOCK_NEW, on_row,
				      G_CALLBACK(sr_menu_viewnew_cb), sd);
	menu_item_add_divider(menu);
	menu_item_add_sensitive(menu, _("Select all"), !empty,
				G_CALLBACK(sr_menu_select_all_cb), sd);
	menu_item_add_sensitive(menu, _("Select none"), !empty,
				G_CALLBACK(sr_menu_select_none_cb), sd);
	menu_item_add_divider(menu);
	submenu_add_edit(menu, &item, G_CALLBACK(sr_menu_edit_cb), sd);
	if (!on_row) gtk_widget_set_sensitive(item, FALSE);
	menu_item_add_stock_sensitive(menu, _("_Properties"), GTK_STOCK_PROPERTIES, on_row,
				      G_CALLBACK(sr_menu_info_cb), sd);
	menu_item_add_stock_sensitive(menu, _("Add to new collection"), GTK_STOCK_INDEX, on_row,
				      G_CALLBACK(sr_menu_collection_cb), sd);
	menu_item_add_stock_sensitive(menu, _("Print..."), GTK_STOCK_PRINT, on_row,
				      G_CALLBACK(sr_menu_print_cb), sd);
	menu_item_add_divider(menu);
	menu_item_add_stock_sensitive(menu, _("_Copy..."), GTK_STOCK_COPY, on_row,
				      G_CALLBACK(sr_menu_copy_cb), sd);
	menu_item_add_sensitive(menu, _("_Move..."), on_row,
				G_CALLBACK(sr_menu_move_cb), sd);
	menu_item_add_sensitive(menu, _("_Rename..."), on_row,
				G_CALLBACK(sr_menu_rename_cb), sd);
	menu_item_add_stock_sensitive(menu, _("_Delete..."), GTK_STOCK_DELETE, on_row,
				      G_CALLBACK(sr_menu_delete_cb), sd);
	menu_item_add_divider(menu);
	menu_item_add_stock_sensitive(menu, _("Rem_ove"), GTK_STOCK_REMOVE, on_row,
				      G_CALLBACK(sr_menu_remove_cb), sd);
	menu_item_add_stock_sensitive(menu, _("C_lear"), GTK_STOCK_CLEAR, !empty,
				      G_CALLBACK(sr_menu_clear_cb), sd);

	return menu;
}

static void search_result_menu_pos_cb(GtkMenu *menu, gint *x, gint *y, gboolean *push_in, gpointer data)
{
	SearchData *sd = data;
	GtkTreePath *tpath;
	gint cx, cy, cw, ch;

	gtk_tree_view_get_cursor(GTK_TREE_VIEW(sd->result_view), &tpath, NULL);
	if (!tpath) return;

	tree_view_get_cell_clamped(GTK_TREE_VIEW(sd->result_view), tpath,
				   SEARCH_COLUMN_NAME - 1, TRUE, &cx, &cy, &cw, &ch);
	gtk_tree_path_free(tpath);
	cy += ch;
	popup_menu_position_clamp(menu, &cx, &cy, 0);
	*x = cx;
	*y = cy;
}

/*
 *-------------------------------------------------------------------
 * result list input
 *-------------------------------------------------------------------
 */

static gint search_result_press_cb(GtkWidget *widget, GdkEventButton *bevent, gpointer data)
{
	SearchData *sd = data;
	GtkTreeModel *store;
	GtkTreePath *tpath;
	GtkTreeIter iter;
	FileData *fd = NULL;

	store = gtk_tree_view_get_model(GTK_TREE_VIEW(widget));

	if (gtk_tree_view_get_path_at_pos(GTK_TREE_VIEW(widget), bevent->x, bevent->y,
					  &tpath, NULL, NULL, NULL))
		{
		gtk_tree_model_get_iter(store, &iter, tpath);
		gtk_tree_model_get(store, &iter, SEARCH_COLUMN_POINTER, &fd, -1);
		gtk_tree_path_free(tpath);
		}

	sd->click_fd = fd;

	if (bevent->button == 3)
		{
		GtkWidget *menu;

		menu = search_result_menu(sd, (fd != NULL), (search_result_count(sd, NULL) == 0));
		gtk_menu_popup(GTK_MENU(menu), NULL, NULL, NULL, NULL, bevent->button, bevent->time);
		}

	if (!fd) return FALSE;

	if (bevent->button == 1 && bevent->type == GDK_2BUTTON_PRESS)
		{
		layout_image_set_path(NULL, fd->path);
		}

	if (bevent->button == 2) return TRUE;

	if (bevent->button == 3)
		{
		if (!search_result_row_selected(sd, fd))
			{
			GtkTreeSelection *selection;

			selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(widget));
			gtk_tree_selection_unselect_all(selection);
			gtk_tree_selection_select_iter(selection, &iter);

			tpath = gtk_tree_model_get_path(store, &iter);
			gtk_tree_view_set_cursor(GTK_TREE_VIEW(widget), tpath, NULL, FALSE);
			gtk_tree_path_free(tpath);
			}
		return TRUE;
		}

	if (bevent->button == 1 && bevent->type == GDK_BUTTON_PRESS &&
	    !(bevent->state & GDK_SHIFT_MASK ) &&
	    !(bevent->state & GDK_CONTROL_MASK ) &&
	    search_result_row_selected(sd, fd))
		{
		/* this selection handled on release_cb */
		gtk_widget_grab_focus(widget);
		return TRUE;
		}

	return FALSE;
}

static gint search_result_release_cb(GtkWidget *widget, GdkEventButton *bevent, gpointer data)
{
	SearchData *sd = data;
	GtkTreeModel *store;
	GtkTreePath *tpath;
	GtkTreeIter iter;

	FileData *fd = NULL;

	if (bevent->button != 1 && bevent->button != 2) return TRUE;

	store = gtk_tree_view_get_model(GTK_TREE_VIEW(widget));

	if ((bevent->x != 0 || bevent->y != 0) &&
	    gtk_tree_view_get_path_at_pos(GTK_TREE_VIEW(widget), bevent->x, bevent->y,
					  &tpath, NULL, NULL, NULL))
		{
		gtk_tree_model_get_iter(store, &iter, tpath);
		gtk_tree_model_get(store, &iter, SEARCH_COLUMN_POINTER, &fd, -1);
		gtk_tree_path_free(tpath);
		}

	if (bevent->button == 2)
		{
		if (fd && sd->click_fd == fd)
			{
			GtkTreeSelection *selection;

			selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(widget));
			if (search_result_row_selected(sd, fd))
				{
				gtk_tree_selection_unselect_iter(selection, &iter);
				}
			else
				{
				gtk_tree_selection_select_iter(selection, &iter);
				}
			}
		return TRUE;
		}

	if (fd && sd->click_fd == fd &&
	    !(bevent->state & GDK_SHIFT_MASK ) &&
	    !(bevent->state & GDK_CONTROL_MASK ) &&
	    search_result_row_selected(sd, fd))
		{
		GtkTreeSelection *selection;

		selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(widget));
		gtk_tree_selection_unselect_all(selection);
		gtk_tree_selection_select_iter(selection, &iter);

		tpath = gtk_tree_model_get_path(store, &iter);
		gtk_tree_view_set_cursor(GTK_TREE_VIEW(widget), tpath, NULL, FALSE);
		gtk_tree_path_free(tpath);

		return TRUE;
		}

	return FALSE;
}

static gint search_result_keypress_cb(GtkWidget *widget, GdkEventKey *event, gpointer data)
{
	SearchData *sd = data;
	gint stop_signal = FALSE;
	GtkTreeModel *store;
	GtkTreeSelection *selection;
	GList *slist;
	FileData *fd = NULL;

	selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(sd->result_view));
	slist = gtk_tree_selection_get_selected_rows(selection, &store);
	if (slist)
		{
		GtkTreePath *tpath;
		GtkTreeIter iter;
		GList *last;

		last = g_list_last(slist);
		tpath = last->data;

		/* last is newest selected file */
		gtk_tree_model_get_iter(store, &iter, tpath);
		gtk_tree_model_get(store, &iter, SEARCH_COLUMN_POINTER, &fd, -1);
		}
	g_list_foreach(slist, (GFunc)gtk_tree_path_free, NULL);
	g_list_free(slist);

	if (event->state & GDK_CONTROL_MASK)
		{
		gint edit_val = -1;

		stop_signal = TRUE;
		switch (event->keyval)
			{
			case '1':
				edit_val = 0;
				break;
			case '2':
				edit_val = 1;
				break;
			case '3':
				edit_val = 2;
				break;
			case '4':
				edit_val = 3;
				break;
			case '5':
				edit_val = 4;
				break;
			case '6':
				edit_val = 5;
				break;
			case '7':
				edit_val = 6;
				break;
			case '8':
				edit_val = 7;
				break;
			case '9':
				edit_val = 8;
				break;
			case '0':
				edit_val = 9;
				break;
			case 'C': case 'c':
				file_util_copy(NULL, search_result_selection_list(sd), NULL, widget);
				break;
			case 'M': case 'm':
				file_util_move(NULL, search_result_selection_list(sd), NULL, widget);
				break;
			case 'R': case 'r':
				file_util_rename(NULL, search_result_selection_list(sd), widget);
				break;
			case 'D': case 'd':
				file_util_delete(NULL, search_result_selection_list(sd), widget);
				break;
			case 'P': case 'p':
				info_window_new(NULL,  search_result_selection_list(sd));
				break;
			case 'A': case 'a':
				if (event->state & GDK_SHIFT_MASK)
					{
					gtk_tree_selection_unselect_all(selection);
					}
				else
					{
					gtk_tree_selection_select_all(selection);
					}
				break;
			case GDK_Delete: case GDK_KP_Delete:
				search_result_clear(sd);
				break;
			default:
				stop_signal = FALSE;
				break;
			}

		if (edit_val >= 0)
			{
			search_result_edit_selected(sd, edit_val);
			}
		}
	else
		{
		stop_signal = TRUE;
		switch (event->keyval)
			{
			case GDK_Return: case GDK_KP_Enter:
				if (fd) layout_image_set_path(NULL, fd->path);
				break;
			case 'V': case 'v':
				{
				GList *list;

				list = search_result_selection_list(sd);
				view_window_new_from_list(list);
				path_list_free(list);
				}
				break;
			case GDK_Delete: case GDK_KP_Delete:
				search_result_remove_selection(sd);
				break;
			case 'C': case 'c':
				search_result_collection_from_selection(sd);
				break;
			case GDK_Menu:
			case GDK_F10:
				{
				GtkWidget *menu;

				sd->click_fd = fd;
				menu = search_result_menu(sd, (fd != NULL), (search_result_count(sd, NULL) > 0));
				gtk_menu_popup(GTK_MENU(menu), NULL, NULL,
					       search_result_menu_pos_cb, sd, 0, GDK_CURRENT_TIME);
				}
				break;
			default:
				stop_signal = FALSE;
				break;
			}
		}
		
	return stop_signal;
}

static gint search_window_keypress_cb(GtkWidget *widget, GdkEventKey *event, gpointer data)
{
	SearchData *sd = data;
	gint stop_signal = FALSE;

	if (event->state & GDK_CONTROL_MASK)
		{
		stop_signal = TRUE;
		switch (event->keyval)
			{
			case 'T': case 't':
				gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(sd->button_thumbs),
					!gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(sd->button_thumbs)));
				break;
			case 'W': case 'w':
				search_window_close(sd);
				break;
			default:
				stop_signal = FALSE;
				break;
			}
		}

	return stop_signal;
}

/*
 *-------------------------------------------------------------------
 * dnd
 *-------------------------------------------------------------------
 */

static GtkTargetEntry result_drag_types[] = {
	{ "text/uri-list", 0, TARGET_URI_LIST },
	{ "text/plain", 0, TARGET_TEXT_PLAIN }
};
static gint n_result_drag_types = 2;

static void search_dnd_data_set(GtkWidget *widget, GdkDragContext *context,
				GtkSelectionData *selection_data, guint info,
				guint time, gpointer data)
{
	SearchData *sd = data;
	gchar *uri_text;
	gint length;
	GList *list;

	switch (info)
		{
		case TARGET_URI_LIST:
		case TARGET_TEXT_PLAIN:
			list = search_result_selection_list(sd);
			if (!list) return;
			uri_text = uri_text_from_list(list, &length, (info == TARGET_TEXT_PLAIN));
			path_list_free(list);
			break;
		default:
			uri_text = NULL;
			break;
		}

	if (uri_text) gtk_selection_data_set(selection_data, selection_data->target,
					     8, (guchar *)uri_text, length);
	g_free(uri_text);
}

static void search_dnd_begin(GtkWidget *widget, GdkDragContext *context, gpointer data)
{
	SearchData *sd = data;

	if (sd->click_fd && !search_result_row_selected(sd, sd->click_fd))
		{
		GtkListStore *store;
		GtkTreeIter iter;

		store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(widget)));
		if (search_result_find_row(sd, sd->click_fd, &iter) >= 0)
			{
			GtkTreeSelection *selection;
			GtkTreePath *tpath;

			selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(widget));
			gtk_tree_selection_unselect_all(selection);
			gtk_tree_selection_select_iter(selection, &iter);

			tpath = gtk_tree_model_get_path(GTK_TREE_MODEL(store), &iter);
			gtk_tree_view_set_cursor(GTK_TREE_VIEW(widget), tpath, NULL, FALSE);
			gtk_tree_path_free(tpath);
			}
		}

	if (sd->thumb_enable &&
	    sd->click_fd && sd->click_fd->pixbuf)
		{
		dnd_set_drag_icon(widget, context, sd->click_fd->pixbuf, search_result_selection_count(sd, NULL));
		}
}

static void search_dnd_init(SearchData *sd)
{
	gtk_drag_source_set(sd->result_view, GDK_BUTTON1_MASK | GDK_BUTTON2_MASK,
			    result_drag_types, n_result_drag_types,
			    GDK_ACTION_COPY | GDK_ACTION_MOVE | GDK_ACTION_LINK);
	g_signal_connect(G_OBJECT(sd->result_view), "drag_data_get",
			 G_CALLBACK(search_dnd_data_set), sd);
	g_signal_connect(G_OBJECT(sd->result_view), "drag_begin",
			 G_CALLBACK(search_dnd_begin), sd);
#if 0
	g_signal_connect(G_OBJECT(sd->result_view), "drag_end",
			 G_CALLBACK(search_dnd_end), sd);
#endif
			
}

/*
 *-------------------------------------------------------------------
 * search core
 *-------------------------------------------------------------------
 */

#define MATCH_IS_BETWEEN(val, a, b)  (b > a ? (val >= a && val <= b) : (val >= b && val <= a))

static gint search_step_cb(gpointer data);


static void search_buffer_flush(SearchData *sd)
{
	GList *work;

	work = g_list_last(sd->search_buffer_list);
	while (work)
		{
		MatchFileData *mfd = work->data;
		work = work->prev;

		search_result_append(sd, mfd);
		}

	g_list_free(sd->search_buffer_list);
	sd->search_buffer_list = NULL;
	sd->search_buffer_count = 0;
}

static void search_stop(SearchData *sd)
{
	if (sd->search_idle_id != -1)
		{
		g_source_remove(sd->search_idle_id);
		sd->search_idle_id = -1;
		}

	image_loader_free(sd->img_loader);
	sd->img_loader = NULL;
	cache_sim_data_free(sd->img_cd);
	sd->img_cd = NULL;

	cache_sim_data_free(sd->search_similarity_cd);
	sd->search_similarity_cd = NULL;

	search_buffer_flush(sd);

	filelist_free(sd->search_folder_list);
	sd->search_folder_list = NULL;

	g_list_free(sd->search_done_list);
	sd->search_done_list = NULL;

	filelist_free(sd->search_file_list);
	sd->search_file_list = NULL;

	gtk_widget_set_sensitive(sd->box_search, TRUE);
	spinner_set_interval(sd->spinner, -1);
	gtk_widget_set_sensitive(sd->button_start, TRUE);
	gtk_widget_set_sensitive(sd->button_stop, FALSE);
	search_progress_update(sd, TRUE, -1.0);
	search_status_update(sd);
}

static void search_file_load_process(SearchData *sd, CacheData *cd)
{
	GdkPixbuf *pixbuf;

	pixbuf = image_loader_get_pixbuf(sd->img_loader);

	if (cd && pixbuf)
		{
		if (!cd->dimensions)
			{
			cache_sim_data_set_dimensions(cd, gdk_pixbuf_get_width(pixbuf),
							  gdk_pixbuf_get_height(pixbuf));
			}

		if (sd->match_similarity_enable && !cd->similarity)
			{
			ImageSimilarityData *sim;

			sim = image_sim_new_from_pixbuf(pixbuf);
			cache_sim_data_set_similarity(cd, sim);
			image_sim_free(sim);
			}

		if (enable_thumb_caching &&
		    sd->img_loader && sd->img_loader->path)
			{
			gchar *base;
			const gchar *path;
			mode_t mode = 0755;

			path = sd->img_loader->path;
			base = cache_get_location(CACHE_TYPE_SIM, path, FALSE, &mode);
			if (cache_ensure_dir_exists(base, mode))
				{
				g_free(cd->path);
				cd->path = cache_get_location(CACHE_TYPE_SIM, path, TRUE, NULL);
				if (cache_sim_data_save(cd))
					{
					filetime_set(cd->path, filetime(sd->img_loader->path));
					}
				}
			g_free(base);
			}
		}

	image_loader_free(sd->img_loader);
	sd->img_loader = NULL;

	sd->search_idle_id = g_idle_add(search_step_cb, sd);
}

static void search_file_load_done_cb(ImageLoader *il, gpointer data)
{
        SearchData *sd = data;
	search_file_load_process(sd, sd->img_cd);
}

static gint search_file_do_extra(SearchData *sd, FileData *fd, gint *match,
				 gint *width, gint *height, gint *simval)
{
	gint new_data = FALSE;
	gint tmatch = TRUE;
	gint tested = FALSE;

	if (!sd->img_cd)
		{
		gchar *cd_path;

		new_data = TRUE;

		cd_path = cache_find_location(CACHE_TYPE_SIM, fd->path);
		if (cd_path && filetime(fd->path) == filetime(cd_path))
			{
			sd->img_cd = cache_sim_data_load(cd_path);
			}
		g_free(cd_path);
		}

	if (!sd->img_cd)
		{
		sd->img_cd = cache_sim_data_new();
		}

	if (new_data)
		{
		if ((sd->match_dimensions_enable && !sd->img_cd->dimensions) ||
		    (sd->match_similarity_enable && !sd->img_cd->similarity))
			{
			sd->img_loader = image_loader_new(fd->path);
			image_loader_set_error_func(sd->img_loader, search_file_load_done_cb, sd);
			if (image_loader_start(sd->img_loader, search_file_load_done_cb, sd))
				{
				return TRUE;
				}
			else
				{
				image_loader_free(sd->img_loader);
				sd->img_loader = NULL;
				}
			}
		}

	if (tmatch && sd->match_dimensions_enable && sd->img_cd->dimensions)
		{
		CacheData *cd = sd->img_cd;

		tmatch = FALSE;
		tested = TRUE;

		if (sd->match_dimensions == SEARCH_MATCH_EQUAL)
			{
			tmatch = (cd->width == sd->search_width && cd->height == sd->search_height);
			}
		else if (sd->match_dimensions == SEARCH_MATCH_UNDER)
			{
			tmatch = (cd->width < sd->search_width && cd->height < sd->search_height);
			}
		else if (sd->match_dimensions == SEARCH_MATCH_OVER)
			{
			tmatch = (cd->width > sd->search_width && cd->height > sd->search_height);
			}
		else if (sd->match_dimensions == SEARCH_MATCH_BETWEEN)
			{
			tmatch = (MATCH_IS_BETWEEN(cd->width, sd->search_width, sd->search_width_end) &&
				  MATCH_IS_BETWEEN(cd->height, sd->search_height, sd->search_height_end));
			}
		}

	if (tmatch && sd->match_similarity_enable && sd->img_cd->similarity)
		{
		gdouble value = 0.0;

		tmatch = FALSE;
		tested = TRUE;

		/* fixme: implement similarity checking */
		if (sd->search_similarity_cd && sd->search_similarity_cd->similarity)
			{
			gdouble result;

			result = image_sim_compare_fast(sd->search_similarity_cd->sim, sd->img_cd->sim,
							(gdouble)sd->search_similarity / 100.0);
			result *= 100.0;
			if (result >= (gdouble)sd->search_similarity)
				{
				tmatch = TRUE;
				value = (gint)result;
				}
			}
		    
		if (simval) *simval = value;
		}

	if (sd->img_cd->dimensions)
		{
		if (width) *width = sd->img_cd->width;
		if (height) *height = sd->img_cd->height;
		}

	cache_sim_data_free(sd->img_cd);
	sd->img_cd = NULL;

	*match = (tmatch && tested);

	return FALSE;
}

static gint search_file_next(SearchData *sd)
{
	FileData *fd;
	gint match = TRUE;
	gint tested = FALSE;
	gint extra_only = FALSE;
	gint width = 0;
	gint height = 0;
	gint sim = 0;

	if (!sd->search_file_list) return FALSE;

	if (sd->img_cd)
		{
		/* on end of a CacheData load, skip recomparing non-extra match types */
		extra_only = TRUE;
		match = FALSE;
		}
	else
		{
		sd->search_total++;
		}

	fd = sd->search_file_list->data;

	if (match && sd->match_name_enable && sd->search_name)
		{
		tested = TRUE;
		match = FALSE;

		if (sd->match_name == SEARCH_MATCH_EQUAL)
			{
			if (sd->search_name_match_case)
				{
				match = (strcmp(fd->name, sd->search_name) == 0);
				}
			else
				{
				match = (strcasecmp(fd->name, sd->search_name) == 0);
				}
			}
		else if (sd->match_name == SEARCH_MATCH_CONTAINS)
			{
			if (sd->search_name_match_case)
				{
				match = (strstr(fd->name, sd->search_name) != NULL);
				}
			else
				{
				/* sd->search_name is converted in search_start() */
				gchar *haystack = g_utf8_strdown(fd->name, -1);
				match = (strstr(haystack, sd->search_name) != NULL);
				g_free(haystack);
				}
			}
		}

	if (match && sd->match_size_enable)
		{
		tested = TRUE;
		match = FALSE;

		if (sd->match_size == SEARCH_MATCH_EQUAL)
			{
			match = (fd->size == sd->search_size);
			}
		else if (sd->match_size == SEARCH_MATCH_UNDER)
			{
			match = (fd->size < sd->search_size);
			}
		else if (sd->match_size == SEARCH_MATCH_OVER)
			{
			match = (fd->size > sd->search_size);
			}
		else if (sd->match_size == SEARCH_MATCH_BETWEEN)
			{
			match = MATCH_IS_BETWEEN(fd->size, sd->search_size, sd->search_size_end);
			}
		}

	if (match && sd->match_date_enable)
		{
		tested = TRUE;
		match = FALSE;

		if (sd->match_date == SEARCH_MATCH_EQUAL)
			{
			struct tm *lt;

			lt = localtime(&fd->date);
			match = (lt &&
				 lt->tm_year == sd->search_date_y - 1900 &&
				 lt->tm_mon == sd->search_date_m - 1 &&
				 lt->tm_mday == sd->search_date_d);
			}
		else if (sd->match_date == SEARCH_MATCH_UNDER)
			{
			match = (fd->date < convert_dmy_to_time(sd->search_date_d, sd->search_date_m, sd->search_date_y));
			}
		else if (sd->match_date == SEARCH_MATCH_OVER)
			{
			match = (fd->date > convert_dmy_to_time(sd->search_date_d, sd->search_date_m, sd->search_date_y) + 60 * 60 * 24 - 1);
			}
		else if (sd->match_date == SEARCH_MATCH_BETWEEN)
			{
			time_t a = convert_dmy_to_time(sd->search_date_d, sd->search_date_m, sd->search_date_y);
			time_t b = convert_dmy_to_time(sd->search_date_end_d, sd->search_date_end_m, sd->search_date_end_y);

			if (b >= a)
				{
				b += 60 * 60 * 24 - 1;
				}
			else
				{
				a += 60 * 60 * 24 - 1;
				}
			match = MATCH_IS_BETWEEN(fd->date, a, b);
			}
		}

	if (match && sd->match_keywords_enable && sd->search_keyword_list)
		{
		GList *list;

		tested = TRUE;
		match = FALSE;

		if (comment_cache_read(fd->path, &list, NULL))
			{
			GList *needle;
			GList *haystack;

			if (sd->match_keywords == SEARCH_MATCH_ALL)
				{
				gint found = TRUE;

				needle = sd->search_keyword_list;
				while (needle && found)
					{
					found = FALSE;
					haystack = list;
					while (haystack && !found)
						{
						found = (strcasecmp((gchar *)needle->data,
								    (gchar *)haystack->data) == 0);
						haystack = haystack->next;
						}
					needle = needle->next;
					}

				match = found;
				}
			else if (sd->match_keywords == SEARCH_MATCH_ANY)
				{
				gint found = FALSE;

				needle = sd->search_keyword_list;
				while (needle && !found)
					{
					haystack = list;
					while (haystack && !found)
						{
						found = (strcasecmp((gchar *)needle->data,
								    (gchar *)haystack->data) == 0);
						haystack = haystack->next;
						}
					needle = needle->next;
					}

				match = found;
				}
			else if (sd->match_keywords == SEARCH_MATCH_NONE)
				{
				gint found = FALSE;

				needle = sd->search_keyword_list;
				while (needle && !found)
					{
					haystack = list;
					while (haystack && !found)
						{
						found = (strcasecmp((gchar *)needle->data,
								    (gchar *)haystack->data) == 0);
						haystack = haystack->next;
						}
					needle = needle->next;
					}

				match = !found;
				}
			path_list_free(list);
			}
		else
			{
			match = (sd->match_keywords == SEARCH_MATCH_NONE);
			}
		}

	if ((match || extra_only) &&
	    (sd->match_dimensions_enable || sd->match_similarity_enable))
		{
		tested = TRUE;

		if (search_file_do_extra(sd, fd, &match, &width, &height, &sim))
			{
			sd->search_buffer_count += SEARCH_BUFFER_MATCH_LOAD;
			return TRUE;
			}
		}

	sd->search_file_list = g_list_remove(sd->search_file_list, fd);

	if (tested && match)
		{
		MatchFileData *mfd;

		mfd = g_new(MatchFileData, 1);
		memcpy(mfd, fd, sizeof(FileData));
		g_free(fd);

		mfd->width = width;
		mfd->height = height;
		mfd->rank = sim;

		sd->search_buffer_list = g_list_prepend(sd->search_buffer_list, mfd);
		sd->search_buffer_count += SEARCH_BUFFER_MATCH_HIT;
		sd->search_count++;
		search_progress_update(sd, TRUE, -1.0);
		}
	else
		{
		file_data_free(fd);
		sd->search_buffer_count += SEARCH_BUFFER_MATCH_MISS;
		}

	return FALSE;
}

static gint search_step_cb(gpointer data)
{
	SearchData *sd = data;
	FileData *fd;

	if (sd->search_buffer_count > SEARCH_BUFFER_FLUSH_SIZE)
		{
		search_buffer_flush(sd);
		search_progress_update(sd, TRUE, -1.0);
		}

	if (sd->search_file_list)
		{
		if (search_file_next(sd))
			{
			sd->search_idle_id = -1;
			return FALSE;
			}
		return TRUE;
		}

	if (!sd->search_file_list && !sd->search_folder_list)
		{
		sd->search_idle_id = -1;

		search_stop(sd);
		search_result_thumb_step(sd);

		return FALSE;
		}

	fd = sd->search_folder_list->data;

	if (g_list_find(sd->search_done_list, fd) == NULL)
		{
		GList *list = NULL;
		GList *dlist = NULL;
		gint success = FALSE;

		sd->search_done_list = g_list_prepend(sd->search_done_list, fd);

		if (sd->search_type == SEARCH_MATCH_NONE)
			{
			success = filelist_read(fd->path, &list, &dlist);
			}
		else if (sd->search_type == SEARCH_MATCH_ALL &&
			 sd->search_path &&
			 strlen(fd->path) >= strlen(sd->search_path))
			{
			const gchar *path;

			path = fd->path + strlen(sd->search_path);
			if (path != fd->path) success = filelist_read(path, &list, NULL);
			success |= filelist_read(fd->path, NULL, &dlist);
			if (success)
				{
				GList *work;

				work = list;
				while (work)
					{
					FileData *fdp;
					GList *link;
					gchar *meta_path;

					fdp = work->data;
					link = work;
					work = work->next;

					meta_path = cache_find_location(CACHE_TYPE_METADATA, fdp->path);
					if (!meta_path)
						{
						list = g_list_delete_link(list, link);
						file_data_free(fdp);
						}
					g_free(meta_path);
					}
				}
			}

		if (success)
			{
			list = filelist_sort(list, SORT_NAME, TRUE);
			sd->search_file_list = list;

			if (sd->search_path_recurse)
				{
				dlist = filelist_sort(dlist, SORT_NAME, TRUE);
				sd->search_folder_list = g_list_concat(dlist, sd->search_folder_list);
				}
			else
				{
				filelist_free(dlist);
				}
			}
		}
	else
		{
		sd->search_folder_list = g_list_remove(sd->search_folder_list, fd);
		sd->search_done_list = g_list_remove(sd->search_done_list, fd);
		file_data_free(fd);
		}

	return TRUE;
}

static void search_similarity_load_done_cb(ImageLoader *il, gpointer data)
{
	SearchData *sd = data;
	search_file_load_process(sd, sd->search_similarity_cd);
}

static void search_start(SearchData *sd)
{
	search_stop(sd);
	search_result_clear(sd);

	if (sd->search_path)
		{
		sd->search_folder_list = g_list_prepend(sd->search_folder_list,
							file_data_new_simple(sd->search_path));
		}

	if (!sd->search_name_match_case)
		{
		/* convert to lowercase here, so that this is only done once per search */
		gchar *tmp = g_utf8_strdown(sd->search_name, -1);
		g_free(sd->search_name);
		sd->search_name = tmp;
		}

	sd->search_count = 0;
	sd->search_total = 0;

	gtk_widget_set_sensitive(sd->box_search, FALSE);
	spinner_set_interval(sd->spinner, SPINNER_SPEED);
	gtk_widget_set_sensitive(sd->button_start, FALSE);
	gtk_widget_set_sensitive(sd->button_stop, TRUE);
	search_progress_update(sd, TRUE, -1.0);

	if (sd->match_similarity_enable &&
	    !sd->search_similarity_cd &&
	    isfile(sd->search_similarity_path))
		{
		gchar *cd_path;

		cd_path = cache_find_location(CACHE_TYPE_SIM, sd->search_similarity_path);
		if (cd_path && filetime(sd->search_similarity_path) == filetime(cd_path))
			{
			sd->search_similarity_cd = cache_sim_data_load(cd_path);
			}
		g_free(cd_path);

		if (!sd->search_similarity_cd || !sd->search_similarity_cd->similarity)
			{
			if (!sd->search_similarity_cd)
				{
				sd->search_similarity_cd = cache_sim_data_new();
				}

			sd->img_loader = image_loader_new(sd->search_similarity_path);
			image_loader_set_error_func(sd->img_loader, search_similarity_load_done_cb, sd);
			if (image_loader_start(sd->img_loader, search_similarity_load_done_cb, sd))
				{
				return;
				}
			image_loader_free(sd->img_loader);
			sd->img_loader = NULL;
			}
			
		}

	sd->search_idle_id = g_idle_add(search_step_cb, sd);
}

static void search_start_cb(GtkWidget *widget, gpointer data)
{
	SearchData *sd = data;
	GtkTreeViewColumn *column;
	gchar *path;

	if (sd->search_folder_list)
		{
		search_stop(sd);
		search_result_thumb_step(sd);
		return;
		}

	if (sd->match_name_enable) history_combo_append_history(sd->entry_name, NULL);
	g_free(sd->search_name);
	sd->search_name = g_strdup(gtk_entry_get_text(GTK_ENTRY(sd->entry_name)));

	g_free(sd->search_similarity_path);
	sd->search_similarity_path = g_strdup(gtk_entry_get_text(GTK_ENTRY(sd->entry_similarity)));
	if (sd->match_similarity_enable)
		{
		if (!isfile(sd->search_similarity_path))
			{
			file_util_warning_dialog(_("File not found"),
						 _("Please enter an existing file for image content."),
						 GTK_STOCK_DIALOG_WARNING, sd->window);
			return;
			}
		tab_completion_append_to_history(sd->entry_similarity, sd->search_similarity_path);
		}

	path_list_free(sd->search_keyword_list);
	sd->search_keyword_list = keyword_list_pull(sd->entry_keywords);

	date_selection_get(sd->date_sel, &sd->search_date_d, &sd->search_date_m, &sd->search_date_y);
	date_selection_get(sd->date_sel_end, &sd->search_date_end_d, &sd->search_date_end_m, &sd->search_date_end_y);

	column = gtk_tree_view_get_column(GTK_TREE_VIEW(sd->result_view), SEARCH_COLUMN_RANK - 1);
	gtk_tree_view_column_set_visible(column, sd->match_similarity_enable);
	if (!sd->match_similarity_enable)
		{
		GtkTreeSortable *sortable;
		gint id;
		GtkSortType order;

		sortable = GTK_TREE_SORTABLE(gtk_tree_view_get_model(GTK_TREE_VIEW(sd->result_view)));
		if (gtk_tree_sortable_get_sort_column_id(sortable, &id, &order) &&
		    id == SEARCH_COLUMN_RANK)
			{
			gtk_tree_sortable_set_sort_column_id(sortable, SEARCH_COLUMN_PATH, GTK_SORT_ASCENDING);
			}
		}

	if (sd->search_type == SEARCH_MATCH_NONE)
		{
		/* search path */

		path = remove_trailing_slash(gtk_entry_get_text(GTK_ENTRY(sd->path_entry)));
		if (isdir(path))
			{
			g_free(sd->search_path);
			sd->search_path = path;
			path = NULL;

			tab_completion_append_to_history(sd->path_entry, sd->search_path);

			search_start(sd);
			}
		else
			{
			file_util_warning_dialog(_("Folder not found"),
						 _("Please enter an existing folder to search."),
						 GTK_STOCK_DIALOG_WARNING, sd->window);
			}

		g_free(path);
		}
	else if (sd->search_type == SEARCH_MATCH_ALL)
		{
		/* search metadata */

		g_free(sd->search_path);
		sd->search_path = g_strconcat(homedir(), "/", GQVIEW_CACHE_RC_METADATA, NULL);

		search_start(sd);
		}
	else if (sd->search_type == SEARCH_MATCH_CONTAINS)
		{
		/* search current result list */
		GList *list;

		list = search_result_refine_list(sd);

		g_free(sd->search_path);
		sd->search_path = NULL;

		search_start(sd);

		sd->search_file_list = g_list_concat(sd->search_file_list, list);
		}
}

/*
 *-------------------------------------------------------------------
 * window construct
 *-------------------------------------------------------------------
 */

enum {
	MENU_CHOICE_COLUMN_NAME = 0,
	MENU_CHOICE_COLUMN_VALUE
};

static void search_thumb_toggle_cb(GtkWidget *button, gpointer data)
{
	SearchData *sd = data;

	search_result_thumb_enable(sd, gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(button)));
}

static gint sort_matchdata_dimensions(MatchFileData *a, MatchFileData *b)
{
	gint sa;
	gint sb;

	sa = a->width * a->height;
	sb = b->width * b->height;

	if (sa > sb) return 1;
	if (sa < sb) return -1;
	return 0;
}

static gint search_result_sort_cb(GtkTreeModel *model, GtkTreeIter *a, GtkTreeIter *b, gpointer data)
{
	gint n = GPOINTER_TO_INT(data);
	FileData *fda;
	FileData *fdb;

	gtk_tree_model_get(model, a, SEARCH_COLUMN_POINTER, &fda, -1);
	gtk_tree_model_get(model, b, SEARCH_COLUMN_POINTER, &fdb, -1);

	if (!fda || !fdb) return 0;

	switch (n)
		{
		case SEARCH_COLUMN_RANK:
			if (((MatchFileData *)fda)->rank > ((MatchFileData *)fdb)->rank) return 1;
			if (((MatchFileData *)fda)->rank < ((MatchFileData *)fdb)->rank) return -1;
			return 0;
			break;
		case SEARCH_COLUMN_NAME:
			return CASE_SORT(fda->name, fdb->name);
			break;
		case SEARCH_COLUMN_SIZE:
			if (fda->size > fdb->size) return 1;
			if (fda->size < fdb->size) return -1;
			return 0;
			break;
		case SEARCH_COLUMN_DATE:
			if (fda->date > fdb->date) return 1;
			if (fda->date < fdb->date) return -1;
			return 0;
			break;
		case SEARCH_COLUMN_DIMENSIONS:
			return sort_matchdata_dimensions((MatchFileData *)fda, (MatchFileData *)fdb);
			break;
		case SEARCH_COLUMN_PATH:
			return CASE_SORT(fda->path, fdb->path);
			break;
		default:
			break;
		}

	return 0;
}

static void search_result_add_column(SearchData * sd, gint n, const gchar *title, gint image, gint right_justify)
{
	GtkTreeViewColumn *column;
	GtkCellRenderer *renderer;

	column = gtk_tree_view_column_new();
	gtk_tree_view_column_set_title(column, title);
	gtk_tree_view_column_set_min_width(column, 4);

	if (n != SEARCH_COLUMN_THUMB) gtk_tree_view_column_set_resizable(column, TRUE);

	if (!image)
		{
		gtk_tree_view_column_set_sizing(column, GTK_TREE_VIEW_COLUMN_GROW_ONLY);
		renderer = gtk_cell_renderer_text_new();
		if (right_justify) g_object_set(G_OBJECT(renderer), "xalign", 1.0, NULL);
		gtk_tree_view_column_pack_start(column, renderer, TRUE);
		gtk_tree_view_column_add_attribute(column, renderer, "text", n);

		gtk_tree_view_column_set_sort_column_id(column, n);
		}
	else
		{
		gtk_tree_view_column_set_sizing(column, GTK_TREE_VIEW_COLUMN_FIXED);
		renderer = gtk_cell_renderer_pixbuf_new();
		cell_renderer_height_override(renderer);
		gtk_tree_view_column_pack_start(column, renderer, TRUE);
		gtk_tree_view_column_add_attribute(column, renderer, "pixbuf", n);
		}

	gtk_tree_view_append_column(GTK_TREE_VIEW(sd->result_view), column);
}

static void menu_choice_set_visible(GtkWidget *widget, gint visible)
{
	if (visible)
		{
		if (!GTK_WIDGET_VISIBLE(widget)) gtk_widget_show(widget);
		}
	else
		{
		if (GTK_WIDGET_VISIBLE(widget)) gtk_widget_hide(widget);
		}
}

static void menu_choice_path_cb(GtkWidget *combo, gpointer data)
{
	SearchData *sd = data;
	GtkTreeModel *store;
	GtkTreeIter iter;

	store = gtk_combo_box_get_model(GTK_COMBO_BOX(combo));
	if (!gtk_combo_box_get_active_iter(GTK_COMBO_BOX(combo), &iter)) return;
	gtk_tree_model_get(store, &iter, MENU_CHOICE_COLUMN_VALUE, &sd->search_type, -1);

	menu_choice_set_visible(gtk_widget_get_parent(sd->check_recurse),
				(sd->search_type == SEARCH_MATCH_NONE));
}

static void menu_choice_name_cb(GtkWidget *combo, gpointer data)
{
	SearchData *sd = data;
	GtkTreeModel *store;
	GtkTreeIter iter;

	store = gtk_combo_box_get_model(GTK_COMBO_BOX(combo));
	if (!gtk_combo_box_get_active_iter(GTK_COMBO_BOX(combo), &iter)) return;
	gtk_tree_model_get(store, &iter, MENU_CHOICE_COLUMN_VALUE, &sd->match_name, -1);
}

static void menu_choice_size_cb(GtkWidget *combo, gpointer data)
{
	SearchData *sd = data;
	GtkTreeModel *store;
	GtkTreeIter iter;

	store = gtk_combo_box_get_model(GTK_COMBO_BOX(combo));
	if (!gtk_combo_box_get_active_iter(GTK_COMBO_BOX(combo), &iter)) return;
	gtk_tree_model_get(store, &iter, MENU_CHOICE_COLUMN_VALUE, &sd->match_size, -1);

	menu_choice_set_visible(gtk_widget_get_parent(sd->spin_size_end),
				(sd->match_size == SEARCH_MATCH_BETWEEN));
}

static void menu_choice_date_cb(GtkWidget *combo, gpointer data)
{
	SearchData *sd = data;
	GtkTreeModel *store;
	GtkTreeIter iter;

	store = gtk_combo_box_get_model(GTK_COMBO_BOX(combo));
	if (!gtk_combo_box_get_active_iter(GTK_COMBO_BOX(combo), &iter)) return;
	gtk_tree_model_get(store, &iter, MENU_CHOICE_COLUMN_VALUE, &sd->match_date, -1);

	menu_choice_set_visible(gtk_widget_get_parent(sd->date_sel_end),
				(sd->match_date == SEARCH_MATCH_BETWEEN));
}

static void menu_choice_dimensions_cb(GtkWidget *combo, gpointer data)
{
	SearchData *sd = data;
	GtkTreeModel *store;
	GtkTreeIter iter;

	store = gtk_combo_box_get_model(GTK_COMBO_BOX(combo));
	if (!gtk_combo_box_get_active_iter(GTK_COMBO_BOX(combo), &iter)) return;
	gtk_tree_model_get(store, &iter, MENU_CHOICE_COLUMN_VALUE, &sd->match_dimensions, -1);

	menu_choice_set_visible(gtk_widget_get_parent(sd->spin_width_end),
				(sd->match_dimensions == SEARCH_MATCH_BETWEEN));
}

static void menu_choice_keyword_cb(GtkWidget *combo, gpointer data)
{
	SearchData *sd = data;
	GtkTreeModel *store;
	GtkTreeIter iter;

	store = gtk_combo_box_get_model(GTK_COMBO_BOX(combo));
	if (!gtk_combo_box_get_active_iter(GTK_COMBO_BOX(combo), &iter)) return;
	gtk_tree_model_get(store, &iter, MENU_CHOICE_COLUMN_VALUE, &sd->match_keywords, -1);
}

static void menu_choice_spin_cb(GtkAdjustment *adjustment, gpointer data)
{
	gint *value = data;

	*value = (gint)gtk_adjustment_get_value(adjustment);
}

static GtkWidget *menu_spin(GtkWidget *box, gdouble min, gdouble max, gint value,
			    GCallback func, gpointer data)
{
	GtkWidget *spin;
	GtkAdjustment *adj;

	spin = gtk_spin_button_new_with_range(min, max, 1);
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin), (gdouble)value);
	adj = gtk_spin_button_get_adjustment(GTK_SPIN_BUTTON(spin));
	if (func) g_signal_connect(G_OBJECT(adj), "value_changed",
				   G_CALLBACK(func), data);
	gtk_box_pack_start(GTK_BOX(box), spin, FALSE, FALSE, 0);
	gtk_widget_show(spin);

	return spin;
}

static void menu_choice_check_cb(GtkWidget *button, gpointer data)
{
	GtkWidget *widget = data;
	gboolean active;
	gboolean *value;

	active = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(button));
	gtk_widget_set_sensitive(widget, active);

	value = g_object_get_data(G_OBJECT(button), "check_var");
	if (value) *value = active;
}

static GtkWidget *menu_choice_menu(const MatchList *items, gint item_count,
				   GCallback func, gpointer data)
{
	GtkWidget *combo;
	GtkCellRenderer *renderer;
	GtkListStore *store;
	gint i;

	store = gtk_list_store_new(2, G_TYPE_STRING, G_TYPE_INT);
	combo = gtk_combo_box_new_with_model(GTK_TREE_MODEL(store));
	g_object_unref(store);

	renderer = gtk_cell_renderer_text_new();
	gtk_cell_layout_pack_start(GTK_CELL_LAYOUT(combo), renderer, TRUE);
	gtk_cell_layout_set_attributes(GTK_CELL_LAYOUT(combo), renderer,
				       "text", MENU_CHOICE_COLUMN_NAME, NULL);

	for (i = 0; i < item_count; i++)
		{
		GtkTreeIter iter;

		gtk_list_store_append(store, &iter);
		gtk_list_store_set(store, &iter, MENU_CHOICE_COLUMN_NAME, _(items[i].text),
						 MENU_CHOICE_COLUMN_VALUE, items[i].type, -1);
		}

	gtk_combo_box_set_active(GTK_COMBO_BOX(combo), 0);

	if (func) g_signal_connect(G_OBJECT(combo), "changed",
				   G_CALLBACK(func), data);

	return combo;
}

static GtkWidget *menu_choice(GtkWidget *box, GtkWidget **check, GtkWidget **menu,
			      const gchar *text, gboolean *value,
			      const MatchList *items, gint item_count,
			      GCallback func, gpointer data)
{
	GtkWidget *base_box;
	GtkWidget *hbox;
	GtkWidget *button;
	GtkWidget *option;

	base_box = gtk_hbox_new(FALSE, PREF_PAD_GAP);
	gtk_box_pack_start(GTK_BOX(box), base_box, FALSE, FALSE, 0);
	gtk_widget_show(base_box);

	button = gtk_check_button_new();
	if (value) gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(button), *value);
	gtk_box_pack_start(GTK_BOX(base_box), button, FALSE, FALSE, 0);
	gtk_widget_show(button);
	if (check) *check = button;
	if (value) g_object_set_data(G_OBJECT(button), "check_var", value);

	hbox = gtk_hbox_new(FALSE, PREF_PAD_SPACE);
	gtk_box_pack_start(GTK_BOX(base_box), hbox, TRUE, TRUE, 0);
	gtk_widget_show(hbox);

	g_signal_connect(G_OBJECT(button), "toggled",
			 G_CALLBACK(menu_choice_check_cb), hbox);
	gtk_widget_set_sensitive(hbox, (value) ? *value : FALSE);

	pref_label_new(hbox, text);

	if (!items && !menu) return hbox;

	option = menu_choice_menu(items, item_count, func, data);
	gtk_box_pack_start(GTK_BOX(hbox), option, FALSE, FALSE, 0);
	gtk_widget_show(option);
	if (menu) *menu = option;

	return hbox;
}

static void search_window_close(SearchData *sd)
{
	gtk_widget_destroy(sd->window);
}

static gint search_window_delete_cb(GtkWidget *widget, GdkEventAny *event, gpointer data)
{
	SearchData *sd = data;

	search_window_close(sd);
	return TRUE;
}

static void search_window_destroy_cb(GtkWidget *widget, gpointer data)
{
	SearchData *sd = data;

	search_window_list = g_list_remove(search_window_list, sd);

	search_result_update_idle_cancel(sd);

	filelist_free(sd->search_buffer_list);
	sd->search_buffer_list = NULL;

	search_stop(sd);
	search_result_clear(sd);

	g_free(sd->search_path);
	g_free(sd->search_name);
	g_free(sd->search_similarity_path);
	path_list_free(sd->search_keyword_list);

	g_free(sd);
}

void search_new(const gchar *path, const gchar *example_file)
{
	SearchData *sd;
	GtkWidget *vbox;
	GtkWidget *hbox;
	GtkWidget *hbox2;
	GtkWidget *pad_box;
	GtkWidget *frame;
	GtkWidget *scrolled;
	GtkListStore *store;
	GtkTreeSortable *sortable;
	GtkTreeSelection *selection;
	GtkWidget *combo;
	GdkGeometry geometry;

	sd = g_new0(SearchData, 1);

	sd->search_path = g_strdup(path);
	sd->search_path_recurse = TRUE;
	sd->search_size = 0;
	sd->search_width = 640;
	sd->search_height = 480;
	sd->search_width_end = 1024;
	sd->search_height_end = 768;
	sd->search_name = NULL;
	sd->search_name_match_case = FALSE;

	sd->search_type = SEARCH_MATCH_NONE;

	sd->match_name = SEARCH_MATCH_CONTAINS;
	sd->match_size = SEARCH_MATCH_EQUAL;
	sd->match_date = SEARCH_MATCH_EQUAL;
	sd->match_dimensions = SEARCH_MATCH_EQUAL;
	sd->match_keywords = SEARCH_MATCH_ALL;

	sd->match_name_enable = TRUE;
	sd->match_size_enable = FALSE;
	sd->match_date_enable = FALSE;
	sd->match_dimensions_enable = FALSE;
	sd->match_similarity_enable = FALSE;
	sd->match_keywords_enable = FALSE;

	sd->search_similarity = 95;
	sd->search_similarity_path = g_strdup(example_file);
	sd->search_similarity_cd = NULL;

	sd->search_idle_id = -1;
	sd->update_idle_id = -1;

	sd->window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	window_set_icon(sd->window, NULL, NULL);

	gtk_window_set_resizable(GTK_WINDOW(sd->window), TRUE);
	gtk_window_set_title(GTK_WINDOW(sd->window), _("Image search - GQview"));
	gtk_window_set_wmclass(GTK_WINDOW(sd->window), "search", "GQview");

	geometry.min_width = 32;
	geometry.min_height = 32;
	geometry.base_width = DEF_SEARCH_WIDTH;
	geometry.base_height = DEF_SEARCH_HEIGHT;
	gtk_window_set_geometry_hints(GTK_WINDOW(sd->window), NULL, &geometry,
				      GDK_HINT_MIN_SIZE | GDK_HINT_BASE_SIZE);

	gtk_window_set_default_size(GTK_WINDOW(sd->window), DEF_SEARCH_WIDTH, DEF_SEARCH_HEIGHT);

	g_signal_connect(G_OBJECT(sd->window), "delete_event",
			 G_CALLBACK(search_window_delete_cb), sd);
	g_signal_connect(G_OBJECT(sd->window), "destroy",
			 G_CALLBACK(search_window_destroy_cb), sd);

	g_signal_connect(G_OBJECT(sd->window), "key_press_event",
			 G_CALLBACK(search_window_keypress_cb), sd);

	vbox = gtk_vbox_new(FALSE, PREF_PAD_GAP);
	gtk_container_set_border_width(GTK_CONTAINER(vbox), PREF_PAD_GAP);
	gtk_container_add(GTK_CONTAINER(sd->window), vbox);
	gtk_widget_show(vbox);

	sd->box_search = pref_box_new(vbox, FALSE, GTK_ORIENTATION_VERTICAL, PREF_PAD_GAP);

	hbox = pref_box_new(sd->box_search, FALSE, GTK_ORIENTATION_HORIZONTAL, PREF_PAD_SPACE);

	pref_label_new(hbox, _("Search:"));

	sd->menu_path = menu_choice_menu(text_search_menu_path, sizeof(text_search_menu_path) / sizeof(MatchList),
					 G_CALLBACK(menu_choice_path_cb), sd);
	gtk_box_pack_start(GTK_BOX(hbox), sd->menu_path, FALSE, FALSE, 0);
	gtk_widget_show(sd->menu_path);

	hbox2 = pref_box_new(hbox, TRUE, GTK_ORIENTATION_HORIZONTAL, PREF_PAD_SPACE);
	combo = tab_completion_new_with_history(&sd->path_entry, sd->search_path,
						"search_path", -1,
						NULL, NULL);
	tab_completion_add_select_button(sd->path_entry, NULL, TRUE);
	gtk_box_pack_start(GTK_BOX(hbox2), combo, TRUE, TRUE, 0);
	gtk_widget_show(combo);
	sd->check_recurse = pref_checkbox_new_int(hbox2, _("Recurse"),
						  sd->search_path_recurse, &sd->search_path_recurse);

	hbox = menu_choice(sd->box_search, &sd->check_name, &sd->menu_name,
			   _("File name"), &sd->match_name_enable,
			   text_search_menu_name, sizeof(text_search_menu_name) / sizeof(MatchList),
			   G_CALLBACK(menu_choice_name_cb), sd);
	combo = history_combo_new(&sd->entry_name, "", "search_name", -1);
	gtk_box_pack_start(GTK_BOX(hbox), combo, TRUE, TRUE, 0);
	gtk_widget_show(combo);
	pref_checkbox_new_int(hbox, _("Match case"),
			      sd->search_name_match_case, &sd->search_name_match_case);

	hbox = menu_choice(sd->box_search, &sd->check_size, &sd->menu_size,
			   _("File size is"), &sd->match_size_enable,
			   text_search_menu_size, sizeof(text_search_menu_size) / sizeof(MatchList),
			   G_CALLBACK(menu_choice_size_cb), sd);
	sd->spin_size = menu_spin(hbox, 0, 1024*1024*1024, sd->search_size,
				  G_CALLBACK(menu_choice_spin_cb), &sd->search_size);
	hbox2 = gtk_hbox_new(FALSE, PREF_PAD_SPACE);
	gtk_box_pack_start(GTK_BOX(hbox), hbox2, FALSE, FALSE, 0);
	pref_label_new(hbox2, _("and"));
	sd->spin_size_end = menu_spin(hbox2, 0, 1024*1024*1024, sd->search_size_end,
				      G_CALLBACK(menu_choice_spin_cb), &sd->search_size_end);

	hbox = menu_choice(sd->box_search, &sd->check_date, &sd->menu_date,
			   _("File date is"), &sd->match_date_enable,
			   text_search_menu_date, sizeof(text_search_menu_date) / sizeof(MatchList),
			   G_CALLBACK(menu_choice_date_cb), sd);
	sd->date_sel = date_selection_new();
	date_selection_time_set(sd->date_sel, time(NULL));
	gtk_box_pack_start(GTK_BOX(hbox), sd->date_sel, FALSE, FALSE, 0);
	gtk_widget_show(sd->date_sel);

	hbox2 = gtk_hbox_new(FALSE, PREF_PAD_SPACE);
	gtk_box_pack_start(GTK_BOX(hbox), hbox2, FALSE, FALSE, 0);
	pref_label_new(hbox2, _("and"));
	sd->date_sel_end = date_selection_new();
	date_selection_time_set(sd->date_sel_end, time(NULL));
	gtk_box_pack_start(GTK_BOX(hbox2), sd->date_sel_end, FALSE, FALSE, 0);
	gtk_widget_show(sd->date_sel_end);

	hbox = menu_choice(sd->box_search, &sd->check_dimensions, &sd->menu_dimensions,
			   _("Image dimensions are"), &sd->match_dimensions_enable,
			   text_search_menu_size, sizeof(text_search_menu_size) / sizeof(MatchList),
			   G_CALLBACK(menu_choice_dimensions_cb), sd);
	pad_box = pref_box_new(hbox, FALSE, GTK_ORIENTATION_HORIZONTAL, 2);
	sd->spin_width = menu_spin(pad_box, 0, 1000000, sd->search_width,
				   G_CALLBACK(menu_choice_spin_cb), &sd->search_width);
	pref_label_new(pad_box, "x");
	sd->spin_height = menu_spin(pad_box, 0, 1000000, sd->search_height,
				    G_CALLBACK(menu_choice_spin_cb), &sd->search_height);
	hbox2 = gtk_hbox_new(FALSE, 2);
	gtk_box_pack_start(GTK_BOX(hbox), hbox2, FALSE, FALSE, 0);
	pref_label_new(hbox2, _("and"));
	pref_spacer(hbox2, PREF_PAD_SPACE - 2*2);
	sd->spin_width_end = menu_spin(hbox2, 0, 1000000, sd->search_width_end,
				       G_CALLBACK(menu_choice_spin_cb), &sd->search_width_end);
	pref_label_new(hbox2, "x");
	sd->spin_height_end = menu_spin(hbox2, 0, 1000000, sd->search_height_end,
					G_CALLBACK(menu_choice_spin_cb), &sd->search_height_end);

	hbox = menu_choice(sd->box_search, &sd->check_similarity, NULL,
			   _("Image content is"), &sd->match_similarity_enable,
			   NULL, 0, NULL, sd);
	sd->spin_similarity = menu_spin(hbox, 80, 100, sd->search_similarity,
					G_CALLBACK(menu_choice_spin_cb), &sd->search_similarity);

	/* xgettext:no-c-format */
	pref_label_new(hbox, _("% similar to"));

	combo = tab_completion_new_with_history(&sd->entry_similarity,
						(sd->search_similarity_path) ? sd->search_similarity_path : "",
						"search_similarity_path", -1, NULL, NULL);
	tab_completion_add_select_button(sd->entry_similarity, NULL, FALSE);
	gtk_box_pack_start(GTK_BOX(hbox), combo, TRUE, TRUE, 0);
	gtk_widget_show(combo);

	hbox = menu_choice(sd->box_search, &sd->check_keywords, &sd->menu_keywords,
			   _("Keywords"), &sd->match_keywords_enable,
			   text_search_menu_keyword, sizeof(text_search_menu_keyword) / sizeof(MatchList),
			   G_CALLBACK(menu_choice_keyword_cb), sd);
	sd->entry_keywords = gtk_entry_new();
	gtk_box_pack_start(GTK_BOX(hbox), sd->entry_keywords, TRUE, TRUE, 0);
	gtk_widget_set_sensitive(sd->entry_keywords, sd->match_keywords_enable);
	g_signal_connect(G_OBJECT(sd->check_keywords), "toggled",
			 G_CALLBACK(menu_choice_check_cb), sd->entry_keywords);
	gtk_widget_show(sd->entry_keywords);

	scrolled = gtk_scrolled_window_new(NULL, NULL);
	gtk_scrolled_window_set_shadow_type(GTK_SCROLLED_WINDOW(scrolled), GTK_SHADOW_IN);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled),
				       GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
	gtk_box_pack_start(GTK_BOX(vbox), scrolled, TRUE, TRUE, 0);
	gtk_widget_show(scrolled);

	store = gtk_list_store_new(8, G_TYPE_POINTER, G_TYPE_INT, GDK_TYPE_PIXBUF,
				   G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING,
				   G_TYPE_STRING, G_TYPE_STRING);

	/* set up sorting */
	sortable = GTK_TREE_SORTABLE(store);
	gtk_tree_sortable_set_sort_func(sortable, SEARCH_COLUMN_RANK, search_result_sort_cb,
				  GINT_TO_POINTER(SEARCH_COLUMN_RANK), NULL);
	gtk_tree_sortable_set_sort_func(sortable, SEARCH_COLUMN_NAME, search_result_sort_cb,
				  GINT_TO_POINTER(SEARCH_COLUMN_NAME), NULL);
	gtk_tree_sortable_set_sort_func(sortable, SEARCH_COLUMN_SIZE, search_result_sort_cb,
				  GINT_TO_POINTER(SEARCH_COLUMN_SIZE), NULL);
	gtk_tree_sortable_set_sort_func(sortable, SEARCH_COLUMN_DATE, search_result_sort_cb,
				  GINT_TO_POINTER(SEARCH_COLUMN_DATE), NULL);
	gtk_tree_sortable_set_sort_func(sortable, SEARCH_COLUMN_DIMENSIONS, search_result_sort_cb,
				  GINT_TO_POINTER(SEARCH_COLUMN_DIMENSIONS), NULL);
	gtk_tree_sortable_set_sort_func(sortable, SEARCH_COLUMN_PATH, search_result_sort_cb,
				  GINT_TO_POINTER(SEARCH_COLUMN_PATH), NULL);

#if 0
	/* by default, search results are unsorted until user selects a sort column - for speed,
	 * using sort slows search speed by an order of magnitude with 1000's of results :-/
	 */
	gtk_tree_sortable_set_sort_column_id(sortable, SEARCH_COLUMN_PATH, GTK_SORT_ASCENDING);
#endif

	sd->result_view = gtk_tree_view_new_with_model(GTK_TREE_MODEL(store));
	g_object_unref(store);
	gtk_container_add(GTK_CONTAINER(scrolled), sd->result_view);
	gtk_widget_show(sd->result_view);

	selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(sd->result_view));
	gtk_tree_selection_set_mode(GTK_TREE_SELECTION(selection), GTK_SELECTION_MULTIPLE);
	gtk_tree_selection_set_select_function(selection, search_result_select_cb, sd, NULL);

	gtk_tree_view_set_headers_visible(GTK_TREE_VIEW(sd->result_view), TRUE);
	gtk_tree_view_set_enable_search(GTK_TREE_VIEW(sd->result_view), FALSE);

#if 0
	gtk_tree_view_set_search_column(GTK_TREE_VIEW(sd->result_view), SEARCH_COLUMN_NAME);
#endif

	search_result_add_column(sd, SEARCH_COLUMN_RANK, _("Rank"), FALSE, FALSE);
	search_result_add_column(sd, SEARCH_COLUMN_THUMB, "", TRUE, FALSE);
	search_result_add_column(sd, SEARCH_COLUMN_NAME, _("Name"), FALSE, FALSE);
	search_result_add_column(sd, SEARCH_COLUMN_SIZE, _("Size"), FALSE, TRUE);
	search_result_add_column(sd, SEARCH_COLUMN_DATE, _("Date"), FALSE, TRUE);
	search_result_add_column(sd, SEARCH_COLUMN_DIMENSIONS, _("Dimensions"), FALSE, FALSE);
	search_result_add_column(sd, SEARCH_COLUMN_PATH, _("Path"), FALSE, FALSE);

	search_dnd_init(sd);

	g_signal_connect(G_OBJECT(sd->result_view), "button_press_event",
			 G_CALLBACK(search_result_press_cb), sd);
	g_signal_connect(G_OBJECT(sd->result_view), "button_release_event",
			 G_CALLBACK(search_result_release_cb), sd);
	g_signal_connect(G_OBJECT(sd->result_view), "key_press_event",
			 G_CALLBACK(search_result_keypress_cb), sd);

	hbox = pref_box_new(vbox, FALSE, GTK_ORIENTATION_HORIZONTAL, 0);

	sd->button_thumbs = pref_checkbox_new(hbox, _("Thumbnails"), FALSE,
					      G_CALLBACK(search_thumb_toggle_cb), sd);

	frame = gtk_frame_new(NULL);
	gtk_frame_set_shadow_type(GTK_FRAME(frame), GTK_SHADOW_IN);
	gtk_box_pack_start(GTK_BOX(hbox), frame, TRUE, TRUE, PREF_PAD_SPACE);
	gtk_widget_show(frame);

	sd->label_status = gtk_label_new("");
	gtk_widget_set_size_request(sd->label_status, 50, -1);
	gtk_container_add(GTK_CONTAINER(frame), sd->label_status);
	gtk_widget_show(sd->label_status);

	sd->label_progress = gtk_progress_bar_new();
	gtk_widget_set_size_request(sd->label_progress, 50, -1);
	gtk_box_pack_start(GTK_BOX(hbox), sd->label_progress, TRUE, TRUE, 0);
	gtk_widget_show(sd->label_progress);

	sd->spinner = spinner_new(NULL, -1);
	gtk_box_pack_start(GTK_BOX(hbox), sd->spinner, FALSE, FALSE, 0);
	gtk_widget_show(sd->spinner);

	sd->button_start = pref_button_new(hbox, GTK_STOCK_FIND, NULL, FALSE,
					   G_CALLBACK(search_start_cb), sd);
	pref_spacer(hbox, PREF_PAD_BUTTON_GAP);
	sd->button_stop = pref_button_new(hbox, GTK_STOCK_STOP, NULL, FALSE,
					  G_CALLBACK(search_start_cb), sd);
	gtk_widget_set_sensitive(sd->button_stop, FALSE);

	search_status_update(sd);
	search_progress_update(sd, FALSE, -1.0);

	search_window_list = g_list_append(search_window_list, sd);

	gtk_widget_show(sd->window);
}

/*
 *-------------------------------------------------------------------
 * maintenance (move, delete, etc.)
 *-------------------------------------------------------------------
 */

static void search_result_change_path(SearchData *sd, const gchar *path, const gchar *newpath)
{
	GtkTreeModel *store;
	GtkTreeIter iter;
	gint valid;

	store = gtk_tree_view_get_model(GTK_TREE_VIEW(sd->result_view));
	valid = gtk_tree_model_get_iter_first(store, &iter);
	while (valid)
		{
		GtkTreeIter current;
		FileData *fd;

		current = iter;
		valid = gtk_tree_model_iter_next(store, &iter);

		gtk_tree_model_get(store, &current, SEARCH_COLUMN_POINTER, &fd, -1);
		if (strcmp(fd->path, path) == 0)
			{
			if (newpath)
				{
				g_free(fd->path);
				fd->path = g_strdup(newpath);
				fd->name = filename_from_path(fd->path);

				gtk_list_store_set(GTK_LIST_STORE(store), &current,
						   SEARCH_COLUMN_NAME, fd->name,
						   SEARCH_COLUMN_PATH, fd->path, -1);
				}
			else
				{
				search_result_remove_item(sd, fd, &current);
				}
			}
		}
}

void search_maint_renamed(const gchar *source, const gchar *dest)
{
	GList *work;

	work = search_window_list;
	while (work)
		{
		SearchData *sd = work->data;
		work = work->next;

		search_result_change_path(sd, source, dest);
		}
}

void search_maint_removed(const gchar *path)
{
	search_maint_renamed(path, NULL);
}

