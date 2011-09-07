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
#include "bar_sort.h"

#include "collect.h"
#include "collect-io.h"
#include "filelist.h"
#include "layout.h"
#include "layout_image.h"
#include "utilops.h"
#include "ui_bookmark.h"
#include "ui_fileops.h"
#include "ui_menu.h"
#include "ui_misc.h"


/*
  *-------------------------------------------------------------------
  * sort bar
  *-------------------------------------------------------------------
  */

typedef enum {
	BAR_SORT_MODE_FOLDER = 0,
	BAR_SORT_MODE_COLLECTION
} SortModeType;

typedef enum {
	BAR_SORT_COPY,
	BAR_SORT_MOVE,
	BAR_SORT_LINK
} SortActionType;

typedef enum {
	BAR_SORT_SELECTION_IMAGE,
	BAR_SORT_SELECTION_SELECTED
} SortSelectionType;

typedef struct _SortData SortData;
struct _SortData
{
	GtkWidget *vbox;
	GtkWidget *bookmarks;
	LayoutWindow *lw;

	FileDialog *dialog;
	GtkWidget *dialog_name_entry;

	SortModeType mode;
	SortActionType action;
	SortSelectionType selection;

	GtkWidget *folder_group;
	GtkWidget *collection_group;

	GtkWidget *add_button;
	GtkWidget *undo_button;
	SortActionType undo_action;
	GList *undo_src_list;
	gchar *undo_src;
	gchar *undo_dest;
};


#define SORT_KEY_FOLDERS     "sort_manager"
#define SORT_KEY_COLLECTIONS "sort_manager_collections"


static gint bar_sort_mode_state = BAR_SORT_MODE_FOLDER;
static gint bar_sort_action_state = BAR_SORT_COPY;
static gint bar_sort_selection_state = BAR_SORT_SELECTION_IMAGE;


static void bar_sort_undo_set(SortData *sd, GList *src_list, const gchar *src, const gchar *dest);
static void bar_sort_add_close(SortData *sd);


static void bar_sort_collection_list_build(GtkWidget *bookmarks)
{
	gchar *collect_path;
	GList *list = NULL;
	GList *work;

	history_list_free_key(SORT_KEY_COLLECTIONS);
	bookmark_list_set_key(bookmarks, SORT_KEY_COLLECTIONS);

	collect_path = g_strconcat(homedir(), "/", GQVIEW_RC_DIR_COLLECTIONS, NULL);
	path_list(collect_path, &list, NULL);
	g_free(collect_path);

	list = path_list_sort(list);

	work = list;
	while (work)
		{
		const gchar *path;
		gchar *name;

		path = work->data;
		work = work->next;

		if (file_extension_match(path, ".gqv"))
			{
			name = remove_extension_from_path(filename_from_path(path));
			}
		else
			{
			name = g_strdup(filename_from_path(path));
			}
		bookmark_list_add(bookmarks, name, path);
		g_free(name);
		}

	path_list_free(list);
}

static void bar_sort_mode_sync(SortData *sd, SortModeType mode)
{
	gint folder_mode;

	if (sd->mode == mode) return;
	sd->mode = mode;

	folder_mode = (sd->mode == BAR_SORT_MODE_FOLDER);

	bookmark_list_set_no_defaults(sd->bookmarks, !folder_mode);
	bookmark_list_set_editable(sd->bookmarks, folder_mode);

	if (folder_mode)
		{
		gtk_widget_hide(sd->collection_group);
		gtk_widget_show(sd->folder_group);
		bookmark_list_set_key(sd->bookmarks, SORT_KEY_FOLDERS );
		}
	else
		{
		gtk_widget_hide(sd->folder_group);
		gtk_widget_show(sd->collection_group);
		bar_sort_collection_list_build(sd->bookmarks);
		}

	bar_sort_add_close(sd);

	bar_sort_undo_set(sd, NULL, NULL, NULL);
}

static void bar_sort_mode_cb(GtkWidget *combo, gpointer data)
{
	SortData *sd = data;

	if (gtk_combo_box_get_active(GTK_COMBO_BOX(combo)) == BAR_SORT_MODE_FOLDER)
		{
		bar_sort_mode_sync(sd, BAR_SORT_MODE_FOLDER);
		}
	else
		{
		bar_sort_mode_sync(sd, BAR_SORT_MODE_COLLECTION);
		}
}

/* this takes control of src_list */
static void bar_sort_undo_set(SortData *sd, GList *src_list, const gchar *src, const gchar *dest)
{
	path_list_free(sd->undo_src_list);
	sd->undo_src_list = src_list;

	g_free(sd->undo_src);
	sd->undo_src = g_strdup(src);
	g_free(sd->undo_dest);
	sd->undo_dest = g_strdup(dest);

	sd->undo_action = sd->action;

	if (sd->undo_button)
		{
		gtk_widget_set_sensitive(sd->undo_button,
					 ((sd->undo_src_list || sd->undo_src) && sd->undo_dest) );
		}
}

static void bar_sort_undo_folder(SortData *sd, GtkWidget *button)
{
	if (!sd->undo_src || !sd->undo_dest) return;

	switch (sd->undo_action)
		{
		case BAR_SORT_MOVE:
			{
			GList *list;
			gchar *src_dir;

			list = g_list_append(NULL, g_strdup(sd->undo_dest));
			src_dir = remove_level_from_path(sd->undo_src);
			file_util_move_simple(list, src_dir);
			g_free(src_dir);
			}
			break;
		case BAR_SORT_COPY:
			file_util_delete(sd->undo_dest, NULL, button);
			break;
		case BAR_SORT_LINK:
			if (!unlink_file(sd->undo_dest))
				{
				gchar *buf;

				buf = g_strdup_printf(_("Unable to remove symbolic link:\n%s"), sd->undo_dest);
				file_util_warning_dialog(_("Unlink failed"), buf, GTK_STOCK_DIALOG_ERROR, button);
				g_free(buf);
				}
			break;
		}

	layout_refresh(sd->lw);

	if (isfile(sd->undo_src))
		{
		layout_image_set_path(sd->lw, sd->undo_src);
		}

	bar_sort_undo_set(sd, NULL, NULL, NULL);
}

static void bar_sort_undo_collection(SortData *sd)
{
	GList *work;

	work = sd->undo_src_list;
	while (work)
		{
		gchar *source;

		source = work->data;
		work = work->next;
		collect_manager_remove(source, sd->undo_dest);
		}

	bar_sort_undo_set(sd, NULL, NULL, NULL);
}

static void bar_sort_undo_cb(GtkWidget *button, gpointer data)
{
	SortData *sd = data;

	if (sd->mode == BAR_SORT_MODE_FOLDER)
		{
		bar_sort_undo_folder(sd, button);
		}
	else
		{
		bar_sort_undo_collection(sd);
		}
}

static void bar_sort_bookmark_select_folder(SortData *sd, const gchar *source, const gchar *path)
{
	GList *list;
	gchar *dest_path;

	if (!isdir(path)) return;

	dest_path = concat_dir_and_file(path, filename_from_path(source));
	bar_sort_undo_set(sd, NULL, source, dest_path);

	list = g_list_append(NULL, g_strdup(source));

	switch (sd->action)
		{
		case BAR_SORT_COPY:
			file_util_copy_simple(list, path);
			list = NULL;
			layout_image_next(sd->lw);
			break;
		case BAR_SORT_MOVE:
			file_util_move_simple(list, path);
			list = NULL;
			break;
		case BAR_SORT_LINK:
			if (symlink_utf8(source, dest_path))
				{
				layout_image_next(sd->lw);
				}
			else
				{
				gchar *buf;

				buf = g_strdup_printf(_("Unable to create symbolic link:\n%s"), dest_path);
				file_util_warning_dialog(_("Link failed"), buf, GTK_STOCK_DIALOG_ERROR, sd->bookmarks);

				g_free(buf);
				}
			break;
		}

	g_list_free(list);
	g_free(dest_path);
}

static void bar_sort_bookmark_select_collection(SortData *sd, const gchar *source, const gchar *path)
{
	GList *list = NULL;

	switch (sd->selection)
		{
		case BAR_SORT_SELECTION_IMAGE:
			list = g_list_append(NULL, g_strdup(source));
			break;
		case BAR_SORT_SELECTION_SELECTED:
			list = layout_selection_list(sd->lw);
			break;
		}

	if (!list)
		{
		bar_sort_undo_set(sd, NULL, NULL, NULL);
		return;
		}

	bar_sort_undo_set(sd, list, NULL, path);

	while (list)
		{
		gchar *image_path;

		image_path = list->data;
		list = list->next;
		collect_manager_add(image_path, path);
		}
}

static void bar_sort_bookmark_select(const gchar *path, gpointer data)
{
	SortData *sd = data;
	const gchar *source;

	source = layout_image_get_path(sd->lw);
	if (!path || !source) return;

	if (sd->mode == BAR_SORT_MODE_FOLDER)
		{
		bar_sort_bookmark_select_folder(sd, source, path);
		}
	else
		{
		bar_sort_bookmark_select_collection(sd, source, path);
		}
}

static void bar_sort_set_copy_cb(GtkWidget *button, gpointer data)
{
	SortData *sd = data;
	if (!gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(button))) return;
	sd->action = BAR_SORT_COPY;
}

static void bar_sort_set_move_cb(GtkWidget *button, gpointer data)
{
	SortData *sd = data;
	if (!gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(button))) return;
	sd->action = BAR_SORT_MOVE;
}

static void bar_sort_set_link_cb(GtkWidget *button, gpointer data)
{
	SortData *sd = data;
	if (!gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(button))) return;
	sd->action = BAR_SORT_LINK;
}

static void bar_sort_set_selection_image_cb(GtkWidget *button, gpointer data)
{
	SortData *sd = data;
	if (!gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(button))) return;
	sd->selection = BAR_SORT_SELECTION_IMAGE;
}

static void bar_sort_set_selection_selected_cb(GtkWidget *button, gpointer data)
{
	SortData *sd = data;
	if (!gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(button))) return;
	sd->selection = BAR_SORT_SELECTION_SELECTED;
}

static void bar_sort_add_close(SortData *sd)
{
	if (sd->dialog) file_dialog_close(sd->dialog);
	sd->dialog_name_entry = NULL;
	sd->dialog = NULL;
}

static void bar_sort_add_ok_cb(FileDialog *fd, gpointer data)
{
	SortData *sd = data;
	const gchar *name;

	name = gtk_entry_get_text(GTK_ENTRY(sd->dialog_name_entry));
	if (sd->mode == BAR_SORT_MODE_FOLDER)
		{
		if (strlen(name) == 0)
			{
			name = filename_from_path(fd->dest_path);
			}

		bookmark_list_add(sd->bookmarks, name, fd->dest_path);
		}
	else
		{
		gchar *path;
		gchar *ext;

		if (strlen(name) == 0) return;

		if (file_extension_match(name, ".gqv"))
			{
			ext = NULL;
			}
		else
			{
			ext = ".gqv";
			}

		path = g_strconcat(homedir(), "/", GQVIEW_RC_DIR_COLLECTIONS, "/", name, ext, NULL);
		if (isfile(path))
			{
			gchar *text = g_strdup_printf(_("The collection:\n%s\nalready exists."), name);
			file_util_warning_dialog(_("Collection exists"), text, GTK_STOCK_DIALOG_INFO, NULL);
			g_free(text);
			}
		else
			{
			CollectionData *cd;

			cd = collection_new(path);
			if (collection_save(cd, path))
				{
				bar_sort_collection_list_build(sd->bookmarks);
				}
			else
				{
				gchar *text = g_strdup_printf(_("Failed to save the collection:\n%s"), path);
				file_util_warning_dialog(_("Save Failed"), text,
							 GTK_STOCK_DIALOG_ERROR, GENERIC_DIALOG(fd)->dialog);
				g_free(text);
				}
			collection_unref(cd);
			}

		g_free(path);
		}

	bar_sort_add_close(sd);
}

static void bar_sort_add_cancel_cb(FileDialog *fd, gpointer data)
{
	SortData *sd = data;

	bar_sort_add_close(sd);
}

static void bar_sort_add_cb(GtkWidget *button, gpointer data)
{
	SortData *sd = data;
	GtkWidget *hbox;
	const gchar *title;

	if (sd->dialog)
		{
		gtk_window_present(GTK_WINDOW(GENERIC_DIALOG(sd->dialog)->dialog));
		return;
		}

	if (sd->mode == BAR_SORT_MODE_FOLDER)
		{
		title = _("Add Bookmark");
		}
	else
		{
		title = _("Add Collection");
		}

	sd->dialog = file_util_file_dlg(title,
				       "gqview", "add_bookmark", button,
				       bar_sort_add_cancel_cb, sd);
	file_dialog_add_button(sd->dialog, GTK_STOCK_OK, NULL, bar_sort_add_ok_cb, TRUE);

	generic_dialog_add_message(GENERIC_DIALOG(sd->dialog), NULL, title, NULL);

	if (sd->mode == BAR_SORT_MODE_FOLDER)
		{
		file_dialog_add_path_widgets(sd->dialog, NULL, NULL, "add_bookmark", NULL, NULL);
		}

	hbox = pref_box_new(GENERIC_DIALOG(sd->dialog)->vbox, FALSE, GTK_ORIENTATION_HORIZONTAL, PREF_PAD_GAP);

	pref_label_new(hbox, _("Name:"));

	sd->dialog_name_entry = gtk_entry_new();
	gtk_box_pack_start(GTK_BOX(hbox), sd->dialog_name_entry, TRUE, TRUE, 0);
	generic_dialog_attach_default(GENERIC_DIALOG(sd->dialog), sd->dialog_name_entry);
	gtk_widget_show(sd->dialog_name_entry);

	if (sd->mode == BAR_SORT_MODE_COLLECTION)
		{
		gtk_widget_grab_focus(sd->dialog_name_entry);
		}

	gtk_widget_show(GENERIC_DIALOG(sd->dialog)->dialog);
}

void bar_sort_close(GtkWidget *bar)
{
	SortData *sd;

	sd = g_object_get_data(G_OBJECT(bar), "bar_sort_data");
	if (!sd) return;

	gtk_widget_destroy(sd->vbox);
}

static void bar_sort_destroy(GtkWidget *widget, gpointer data)
{
	SortData *sd = data;

	bar_sort_add_close(sd);
	bar_sort_mode_state = sd->mode;
	bar_sort_action_state = sd->action;
	bar_sort_selection_state = sd->selection;

	g_free(sd->undo_src);
	g_free(sd->undo_dest);
	g_free(sd);
}

GtkWidget *bar_sort_new(LayoutWindow *lw)
{
	SortData *sd;
	GtkWidget *buttongrp;
	GtkWidget *label;
	GtkWidget *tbar;
	GtkWidget *combo;

	if (!lw) return NULL;

	sd = g_new0(SortData, 1);

	sd->lw = lw;
	sd->action = bar_sort_action_state;
	sd->selection = bar_sort_selection_state;
	sd->undo_src = NULL;
	sd->undo_dest = NULL;

	sd->vbox = gtk_vbox_new(FALSE, PREF_PAD_GAP);
	g_object_set_data(G_OBJECT(sd->vbox), "bar_sort_data", sd);
	g_signal_connect(G_OBJECT(sd->vbox), "destroy",
			 G_CALLBACK(bar_sort_destroy), sd);

	label = gtk_label_new(_("Sort Manager"));
	pref_label_bold(label, TRUE, FALSE);
	gtk_box_pack_start(GTK_BOX(sd->vbox), label, FALSE, FALSE, 0);
	gtk_widget_show(label);

	combo = gtk_combo_box_new_text();
	gtk_box_pack_start(GTK_BOX(sd->vbox), combo, FALSE, FALSE, 0);
	gtk_widget_show(combo);

	gtk_combo_box_append_text(GTK_COMBO_BOX(combo), _("Folders"));
	gtk_combo_box_append_text(GTK_COMBO_BOX(combo), _("Collections"));

	g_signal_connect(G_OBJECT(combo), "changed",
			 G_CALLBACK(bar_sort_mode_cb), sd);

	sd->folder_group = pref_box_new(sd->vbox, FALSE, GTK_ORIENTATION_VERTICAL, 0);

	buttongrp = pref_radiobutton_new(sd->folder_group, NULL,
					 _("Copy"), (sd->action == BAR_SORT_COPY),
					 G_CALLBACK(bar_sort_set_copy_cb), sd);
	pref_radiobutton_new(sd->folder_group, buttongrp,
			     _("Move"), (sd->action == BAR_SORT_MOVE),
			     G_CALLBACK(bar_sort_set_move_cb), sd);
	pref_radiobutton_new(sd->folder_group, buttongrp,
			     _("Link"), (sd->action == BAR_SORT_LINK),
			     G_CALLBACK(bar_sort_set_link_cb), sd);

	sd->collection_group = pref_box_new(sd->vbox, FALSE, GTK_ORIENTATION_VERTICAL, 0);

	buttongrp = pref_radiobutton_new(sd->collection_group, NULL,
					 _("Add image"), (sd->selection == BAR_SORT_SELECTION_IMAGE),
					 G_CALLBACK(bar_sort_set_selection_image_cb), sd);
	pref_radiobutton_new(sd->collection_group, buttongrp,
			     _("Add selection"), (sd->selection == BAR_SORT_SELECTION_SELECTED),
			     G_CALLBACK(bar_sort_set_selection_selected_cb), sd);

	sd->bookmarks = bookmark_list_new(SORT_KEY_FOLDERS, bar_sort_bookmark_select, sd);
	gtk_box_pack_start(GTK_BOX(sd->vbox), sd->bookmarks, TRUE, TRUE, 0);
	gtk_widget_show(sd->bookmarks);

	tbar = pref_toolbar_new(sd->vbox, GTK_TOOLBAR_ICONS);

	sd->add_button = pref_toolbar_button(tbar, GTK_STOCK_ADD, NULL, FALSE,
					     _("Add Bookmark"),
					     G_CALLBACK(bar_sort_add_cb), sd);
	sd->undo_button = pref_toolbar_button(tbar, GTK_STOCK_UNDO, NULL, FALSE,
					      _("Undo last image"),
					      G_CALLBACK(bar_sort_undo_cb), sd);

	sd->mode = -1;
	bar_sort_mode_sync(sd, bar_sort_mode_state);
	gtk_combo_box_set_active(GTK_COMBO_BOX(combo), sd->mode);
	
	return sd->vbox;
}

