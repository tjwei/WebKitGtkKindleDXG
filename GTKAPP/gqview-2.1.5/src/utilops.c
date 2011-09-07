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
#include "utilops.h"


#include "cache.h"
#include "cache_maint.h"
#include "collect.h"
#include "dupe.h"
#include "filelist.h"
#include "image.h"
#include "img-view.h"
#include "layout.h"
#include "search.h"
#include "thumb_standard.h"
#include "ui_bookmark.h"
#include "ui_fileops.h"
#include "ui_misc.h"
#include "ui_tabcomp.h"


/*
 *--------------------------------------------------------------------------
 * call these when names change, files move, deleted, etc.
 * so that any open windows are also updated
 *--------------------------------------------------------------------------
 */

void file_maint_renamed(const gchar *source, const gchar *dest)
{
	cache_maint_moved(source, dest);
	collection_maint_renamed(source, dest);

	layout_maint_renamed(source, dest);
	view_window_maint_moved(source, dest);
	dupe_maint_renamed(source, dest);
	search_maint_renamed(source, dest);
}

/* under most cases ignore_list should be NULL */
void file_maint_removed(const gchar *path, GList *ignore_list)
{
	layout_maint_removed(path, ignore_list);
	view_window_maint_removed(path, ignore_list);
	dupe_maint_removed(path);
	search_maint_removed(path);

	collection_maint_removed(path);
	cache_maint_removed(path);
}

/* special case for correct main window behavior */
void file_maint_moved(const gchar *source, const gchar *dest, GList *ignore_list)
{
	cache_maint_moved(source, dest);
	collection_maint_renamed(source, dest);

	layout_maint_moved(source, dest, ignore_list);
	view_window_maint_moved(source, dest);
	dupe_maint_renamed(source, dest);
	search_maint_renamed(source, dest);
}

void file_maint_copied(const gchar *source, const gchar *dest)
{
	cache_maint_copied(source, dest);
}

/*
 *--------------------------------------------------------------------------
 * The file manipulation dialogs
 *--------------------------------------------------------------------------
 */


enum {
	DIALOG_NEW_DIR,
	DIALOG_COPY,
	DIALOG_MOVE,
	DIALOG_DELETE,
	DIALOG_RENAME
};

typedef struct _FileDataMult FileDataMult;
struct _FileDataMult
{
	gint confirm_all;
	gint confirmed;
	gint skip;
	GList *source_list;
	GList *source_next;
	gchar *dest_base;
	gchar *source;
	gchar *dest;
	gint copy;

	gint rename;
	gint rename_auto;
	gint rename_all;

	GtkWidget *rename_box;
	GtkWidget *rename_entry;
	GtkWidget *rename_auto_box;

	GtkWidget *yes_all_button;
};

typedef struct _FileDataSingle FileDataSingle;
struct _FileDataSingle
{
	gint confirmed;
	gchar *source;
	gchar *dest;
	gint copy;

	gint rename;
	gint rename_auto;

	GtkWidget *rename_box;
	GtkWidget *rename_entry;
	GtkWidget *rename_auto_box;
};

/*
 *--------------------------------------------------------------------------
 * Adds 1 or 2 images (if 2, side by side) to a GenericDialog
 *--------------------------------------------------------------------------
 */

#define DIALOG_DEF_IMAGE_DIM_X 200
#define DIALOG_DEF_IMAGE_DIM_Y 150

static void generic_dialog_add_image(GenericDialog *gd, GtkWidget *box,
				     const gchar *path1, const gchar *header1,
				     const gchar *path2, const gchar *header2,
				     gint show_filename)
{
	ImageWindow *imd;
	GtkWidget *hbox = NULL;
	GtkWidget *vbox;
	GtkWidget *label = NULL;

	if (!box) box = gd->vbox;

	if (path2)
		{
		hbox = pref_box_new(box, TRUE, GTK_ORIENTATION_HORIZONTAL, PREF_PAD_SPACE);
		}

	/* image 1 */

	vbox = gtk_vbox_new(FALSE, PREF_PAD_GAP);
	if (hbox)
		{
		GtkWidget *sep;

		gtk_box_pack_start(GTK_BOX(hbox), vbox, TRUE, TRUE, 0);

		sep = gtk_vseparator_new();
		gtk_box_pack_start(GTK_BOX(hbox), sep, FALSE, FALSE, 0);
		gtk_widget_show(sep);
		}
	else
		{
		gtk_box_pack_start(GTK_BOX(box), vbox, TRUE, TRUE, PREF_PAD_GAP);
		}
	gtk_widget_show(vbox);

	if (header1)
		{
		GtkWidget *head;

		head = pref_label_new(vbox, header1);
		pref_label_bold(head, TRUE, FALSE);
		gtk_misc_set_alignment(GTK_MISC(head), 0.0, 0.5);
		}

	imd = image_new(FALSE);
	g_object_set(G_OBJECT(imd->pr), "zoom_expand", FALSE, NULL);
	gtk_widget_set_size_request(imd->widget, DIALOG_DEF_IMAGE_DIM_X, DIALOG_DEF_IMAGE_DIM_Y);
	gtk_box_pack_start(GTK_BOX(vbox), imd->widget, TRUE, TRUE, 0);
	image_change_path(imd, path1, 0.0);
	gtk_widget_show(imd->widget);

	if (show_filename)
		{
		label = pref_label_new(vbox, (path1 == NULL) ? "" : filename_from_path(path1));
		}

	/* only the first image is stored (for use in gd_image_set) */
	g_object_set_data(G_OBJECT(gd->dialog), "img_image", imd);
	g_object_set_data(G_OBJECT(gd->dialog), "img_label", label);
		

	/* image 2 */

	if (hbox && path2)
		{
		vbox = pref_box_new(hbox, TRUE, GTK_ORIENTATION_VERTICAL, PREF_PAD_GAP);

		if (header2)
			{
			GtkWidget *head;

			head = pref_label_new(vbox, header2);
			pref_label_bold(head, TRUE, FALSE);
			gtk_misc_set_alignment(GTK_MISC(head), 0.0, 0.5);
			}

		imd = image_new(FALSE);
		g_object_set(G_OBJECT(imd->pr), "zoom_expand", FALSE, NULL);
		gtk_widget_set_size_request(imd->widget, DIALOG_DEF_IMAGE_DIM_X, DIALOG_DEF_IMAGE_DIM_Y);
		gtk_box_pack_start(GTK_BOX(vbox), imd->widget, TRUE, TRUE, 0);
		image_change_path(imd, path2, 0.0);
		gtk_widget_show(imd->widget);

		pref_label_new(vbox, filename_from_path(path2));
		}
}

static void generic_dialog_image_set(GenericDialog *gd, const gchar *path)
{
	ImageWindow *imd;
	GtkWidget *label;
	
	imd = g_object_get_data(G_OBJECT(gd->dialog), "img_image");
	label = g_object_get_data(G_OBJECT(gd->dialog), "img_label");

	if (!imd) return;

	image_change_path(imd, path, 0.0);
	if (label) gtk_label_set_text(GTK_LABEL(label), filename_from_path(path));
}

/*
 *--------------------------------------------------------------------------
 * Wrappers to aid in setting additional dialog properties (unde mouse, etc.)
 *--------------------------------------------------------------------------
 */

GenericDialog *file_util_gen_dlg(const gchar *title,
				 const gchar *wmclass, const gchar *wmsubclass,
				 GtkWidget *parent, gint auto_close,
				 void (*cancel_cb)(GenericDialog *, gpointer), gpointer data)
{
	GenericDialog *gd;

	gd = generic_dialog_new(title, wmclass, wmsubclass, parent, auto_close, cancel_cb, data);
	if (place_dialogs_under_mouse)
		{
		gtk_window_set_position(GTK_WINDOW(gd->dialog), GTK_WIN_POS_MOUSE);
		}

	return gd;
}

FileDialog *file_util_file_dlg(const gchar *title,
			       const gchar *wmclass, const gchar *wmsubclass,
			       GtkWidget *parent,
			       void (*cancel_cb)(FileDialog *, gpointer), gpointer data)
{
	FileDialog *fd;

	fd = file_dialog_new(title, wmclass, wmsubclass, parent, cancel_cb, data);
	if (place_dialogs_under_mouse)
		{
		gtk_window_set_position(GTK_WINDOW(GENERIC_DIALOG(fd)->dialog), GTK_WIN_POS_MOUSE);
		}

	return fd;
}

/* this warning dialog is copied from SLIK's ui_utildg.c,
 * because it does not have a mouse center option,
 * and we must center it before show, implement it here.
 */
static void file_util_warning_dialog_ok_cb(GenericDialog *gd, gpointer data)
{
	/* no op */
}

GenericDialog *file_util_warning_dialog(const gchar *heading, const gchar *message,
					const gchar *icon_stock_id, GtkWidget *parent)
{
	GenericDialog *gd;

	gd = file_util_gen_dlg(heading, "GQview", "warning", parent, TRUE, NULL, NULL);
	generic_dialog_add_message(gd, icon_stock_id, heading, message);
	generic_dialog_add_button(gd, GTK_STOCK_OK, NULL, file_util_warning_dialog_ok_cb, TRUE);
	if (place_dialogs_under_mouse)
		{
		gtk_window_set_position(GTK_WINDOW(gd->dialog), GTK_WIN_POS_MOUSE);
		}
	gtk_widget_show(gd->dialog);

	return gd;
}

static gint filename_base_length(const gchar *name)
{
	gint n;

	if (!name) return 0;

	n = strlen(name);

	if (filter_name_exists(name))
		{
		const gchar *ext;

		ext = extension_from_path(name);
		if (ext) n -= strlen(ext);
		}

	return n;
}


/*
 *--------------------------------------------------------------------------
 * Move and Copy routines
 *--------------------------------------------------------------------------
 */

/*
 * Multi file move
 */

static FileDataMult *file_data_multiple_new(GList *source_list, const gchar *dest, gint copy)
{
	FileDataMult *fdm = g_new0(FileDataMult, 1);
	fdm->confirm_all = FALSE;
	fdm->confirmed = FALSE;
	fdm->skip = FALSE;
	fdm->source_list = source_list;
	fdm->source_next = fdm->source_list;
	fdm->dest_base = g_strdup(dest);
	fdm->source = NULL;
	fdm->dest = NULL;
	fdm->copy = copy;
	return fdm;
}

static void file_data_multiple_free(FileDataMult *fdm)
{
	path_list_free(fdm->source_list);
	g_free(fdm->dest_base);
	g_free(fdm->dest);
	g_free(fdm);
}

static void file_util_move_multiple(FileDataMult *fdm);

static void file_util_move_multiple_ok_cb(GenericDialog *gd, gpointer data)
{
	FileDataMult *fdm = data;

	fdm->confirmed = TRUE;

	if (fdm->rename_auto)
		{
		gchar *buf;

		buf = unique_filename_simple(fdm->dest);
		if (buf)
			{
			g_free(fdm->dest);
			fdm->dest = buf;
			}
		else
			{
			/* unique failed? well, return to the overwrite prompt :( */
			fdm->confirmed = FALSE;
			}
		}
	else if (fdm->rename)
		{
		const gchar *name;

		name = gtk_entry_get_text(GTK_ENTRY(fdm->rename_entry));
		if (strlen(name) == 0 ||
		    strcmp(name, filename_from_path(fdm->source)) == 0)
			{
			fdm->confirmed = FALSE;
			}
		else
			{
			g_free(fdm->dest);
			fdm->dest = concat_dir_and_file(fdm->dest_base, name);
			fdm->confirmed = !isname(fdm->dest);
			}
		}

	file_util_move_multiple(fdm);
}

static void file_util_move_multiple_all_cb(GenericDialog *gd, gpointer data)
{
	FileDataMult *fdm = data;

	fdm->confirm_all = TRUE;

	if (fdm->rename_auto) fdm->rename_all = TRUE;

	file_util_move_multiple(fdm);
}

static void file_util_move_multiple_skip_cb(GenericDialog *gd, gpointer data)
{
	FileDataMult *fdm = data;

	fdm->skip = TRUE;
	fdm->confirmed = TRUE;

	file_util_move_multiple(fdm);
}

static void file_util_move_multiple_skip_all_cb(GenericDialog *gd, gpointer data)
{
	FileDataMult *fdm = data;

	fdm->skip = TRUE;
	fdm->confirm_all = TRUE;
	file_util_move_multiple(fdm);
}

static void file_util_move_multiple_continue_cb(GenericDialog *gd, gpointer data)
{
	FileDataMult *fdm = data;

	fdm->confirmed = TRUE;
	file_util_move_multiple(fdm);
}

static void file_util_move_multiple_cancel_cb(GenericDialog *gd, gpointer data)
{
	FileDataMult *fdm = data;

	file_data_multiple_free(fdm);
}

/* rename option */

static void file_util_move_multiple_rename_auto_cb(GtkWidget *widget, gpointer data)
{
	GenericDialog *gd = data;
	FileDataMult *fdm;

	fdm = gd->data;

	fdm->rename_auto = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget));
	gtk_widget_set_sensitive(fdm->rename_box, !fdm->rename_auto);
	gtk_widget_set_sensitive(fdm->rename_entry, (!fdm->rename_auto && fdm->rename));

	if (fdm->rename_auto)
		{
		gchar *preview;

		preview = unique_filename_simple(fdm->dest);
		if (preview) gtk_entry_set_text(GTK_ENTRY(fdm->rename_entry), filename_from_path(preview));
		g_free(preview);
		}

	gtk_widget_set_sensitive(fdm->yes_all_button, (fdm->rename_auto || !fdm->rename));
}

static void file_util_move_multiple_rename_cb(GtkWidget *widget, gpointer data)
{
	GenericDialog *gd = data;
	FileDataMult *fdm;

	fdm = gd->data;

	fdm->rename = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget));
	gtk_widget_set_sensitive(fdm->rename_entry, fdm->rename);
	gtk_widget_set_sensitive(fdm->yes_all_button, !fdm->rename);

	if (fdm->rename)
		{
		const gchar *name;

		gtk_widget_grab_focus(fdm->rename_entry);

		name = gtk_entry_get_text(GTK_ENTRY(fdm->rename_entry));
		gtk_editable_select_region(GTK_EDITABLE(fdm->rename_entry), 0, filename_base_length(name));
		}
}

static GenericDialog *file_util_move_multiple_confirm_dialog(FileDataMult *fdm)
{
	GenericDialog *gd;
	GtkWidget *hbox;

	gd = file_util_gen_dlg(_("Overwrite file"), "GQview", "dlg_confirm",
				NULL, TRUE,
				file_util_move_multiple_cancel_cb, fdm);

	generic_dialog_add_message(gd, GTK_STOCK_DIALOG_QUESTION,
				   _("Overwrite file?"),
				   _("Replace existing file with new file."));
	pref_spacer(gd->vbox, 0);

	generic_dialog_add_button(gd, GTK_STOCK_YES, _("_Overwrite"), file_util_move_multiple_ok_cb, TRUE);
	fdm->yes_all_button = generic_dialog_add_button(gd, NULL, _("Overwrite _all"),
							file_util_move_multiple_all_cb, FALSE);
	generic_dialog_add_button(gd, GTK_STOCK_GOTO_LAST, _("S_kip all"), file_util_move_multiple_skip_all_cb, FALSE);
	generic_dialog_add_button(gd, GTK_STOCK_GO_FORWARD, _("_Skip"), file_util_move_multiple_skip_cb, FALSE);
	generic_dialog_add_image(gd, NULL, fdm->dest, _("Existing file"), fdm->source, _("New file"), TRUE);

	/* rename option */

	fdm->rename = FALSE;
	fdm->rename_all = FALSE;
	fdm->rename_auto = FALSE;

	hbox = pref_box_new(gd->vbox, FALSE, GTK_ORIENTATION_HORIZONTAL, PREF_PAD_GAP);

	fdm->rename_auto_box = gtk_check_button_new_with_label(_("Auto rename"));
	g_signal_connect(G_OBJECT(fdm->rename_auto_box), "clicked",
			 G_CALLBACK(file_util_move_multiple_rename_auto_cb), gd);
	gtk_box_pack_start(GTK_BOX(hbox), fdm->rename_auto_box, FALSE, FALSE, 0);
	gtk_widget_show(fdm->rename_auto_box);

	hbox = pref_box_new(gd->vbox, FALSE, GTK_ORIENTATION_HORIZONTAL, PREF_PAD_GAP);

	fdm->rename_box = gtk_check_button_new_with_label(_("Rename"));
	g_signal_connect(G_OBJECT(fdm->rename_box), "clicked",
			 G_CALLBACK(file_util_move_multiple_rename_cb), gd);
	gtk_box_pack_start(GTK_BOX(hbox), fdm->rename_box, FALSE, FALSE, 0);
	gtk_widget_show(fdm->rename_box);

	fdm->rename_entry = gtk_entry_new();
	gtk_entry_set_text(GTK_ENTRY(fdm->rename_entry), filename_from_path(fdm->dest));
	gtk_widget_set_sensitive(fdm->rename_entry, FALSE);
	gtk_box_pack_start(GTK_BOX(hbox), fdm->rename_entry, TRUE, TRUE, 0);
	gtk_widget_show(fdm->rename_entry);

	return gd;
}

static void file_util_move_multiple(FileDataMult *fdm)
{
	while (fdm->dest || fdm->source_next)
		{
		gint success = FALSE;
		gint skip_file = FALSE;

		if (!fdm->dest)
			{
			GList *work = fdm->source_next;
			fdm->source = work->data;
			fdm->dest = concat_dir_and_file(fdm->dest_base, filename_from_path(fdm->source));
			fdm->source_next = work->next;
			fdm->confirmed = FALSE;
			}

		if (fdm->dest && fdm->source && strcmp(fdm->dest, fdm->source) == 0)
			{
			if (!fdm->confirmed)
				{
				GenericDialog *gd;
				const gchar *title;
				gchar *text;

				if (fdm->copy)
					{
					title = _("Source to copy matches destination");
					text = g_strdup_printf(_("Unable to copy file:\n%s\nto itself."), fdm->dest);
					}
				else
					{
					title = _("Source to move matches destination");
					text = g_strdup_printf(_("Unable to move file:\n%s\nto itself."), fdm->dest);
					}

				gd = file_util_gen_dlg(title, "GQview", "dlg_confirm",
							NULL, TRUE,
							file_util_move_multiple_cancel_cb, fdm);
				generic_dialog_add_message(gd, GTK_STOCK_DIALOG_WARNING, title, text);
				g_free(text);
				generic_dialog_add_button(gd, GTK_STOCK_GO_FORWARD, _("Co_ntinue"),
							 file_util_move_multiple_continue_cb, TRUE);

				gtk_widget_show(gd->dialog);
				return;
				}
			skip_file = TRUE;
			}
		else if (isfile(fdm->dest))
			{
			if (!fdm->confirmed && !fdm->confirm_all)
				{
				GenericDialog *gd;

				gd = file_util_move_multiple_confirm_dialog(fdm);
				gtk_widget_show(gd->dialog);
				return;
				}
			if (fdm->skip) skip_file = TRUE;
			}

		if (skip_file)
			{
			success = TRUE;
			if (!fdm->confirm_all) fdm->skip = FALSE;
			}
		else
			{
			gint try = TRUE;

			if (fdm->confirm_all && fdm->rename_all && isfile(fdm->dest))
				{
				gchar *buf;
				buf = unique_filename_simple(fdm->dest);
				if (buf)
					{
					g_free(fdm->dest);
					fdm->dest = buf;
					}
				else
					{
					try = FALSE;
					}
				}
			if (try)
				{
				if (fdm->copy)
					{
					if (copy_file(fdm->source, fdm->dest))
						{
						success = TRUE;
						file_maint_copied(fdm->source, fdm->dest);
						}
					}
				else
					{
					if (move_file(fdm->source, fdm->dest))
						{
						success = TRUE;
						file_maint_moved(fdm->source, fdm->dest, fdm->source_list);
						}
					}
				}
			}

		if (!success)
			{
			GenericDialog *gd;
			const gchar *title;
			gchar *text;

			if (fdm->copy)
				{
				title = _("Error copying file");
				text = g_strdup_printf(_("Unable to copy file:\n%s\nto:\n%s\nduring multiple file copy."), fdm->source, fdm->dest);
				}
			else
				{
				title = _("Error moving file");
				text = g_strdup_printf(_("Unable to move file:\n%s\nto:\n%s\nduring multiple file move."), fdm->source, fdm->dest);
				}
			gd = file_util_gen_dlg(title, "GQview", "dlg_confirm",
						NULL, TRUE,
						file_util_move_multiple_cancel_cb, fdm);
			generic_dialog_add_message(gd, GTK_STOCK_DIALOG_WARNING, title, text);
			g_free(text);

			generic_dialog_add_button(gd, GTK_STOCK_GO_FORWARD, _("Co_ntinue"),
						  file_util_move_multiple_continue_cb, TRUE);
			gtk_widget_show(gd->dialog);
			}

		g_free(fdm->dest);
		fdm->dest = NULL;

		if (!success) return;
		}

	file_data_multiple_free(fdm);
}

/*
 * Single file move
 */

static FileDataSingle *file_data_single_new(const gchar *source, const gchar *dest, gint copy)
{
	FileDataSingle *fds = g_new0(FileDataSingle, 1);
	fds->confirmed = FALSE;
	fds->source = g_strdup(source);
	fds->dest = g_strdup(dest);
	fds->copy = copy;
	return fds;
}

static void file_data_single_free(FileDataSingle *fds)
{
	g_free(fds->source);
	g_free(fds->dest);
	g_free(fds);
}

static void file_util_move_single(FileDataSingle *fds);

static void file_util_move_single_ok_cb(GenericDialog *gd, gpointer data)
{
	FileDataSingle *fds = data;

	fds->confirmed = TRUE;

	if (fds->rename_auto)
		{
		gchar *buf;

		buf = unique_filename_simple(fds->dest);
		if (buf)
			{
			g_free(fds->dest);
			fds->dest = buf;
			}
		else
			{
			/* unique failed? well, return to the overwrite prompt :( */
			fds->confirmed = FALSE;
			}
		}
	else if (fds->rename)
		{
		const gchar *name;

		name = gtk_entry_get_text(GTK_ENTRY(fds->rename_entry));
		if (strlen(name) == 0 ||
		    strcmp(name, filename_from_path(fds->source)) == 0)
			{
			fds->confirmed = FALSE;
			}
		else
			{
			gchar *base;

			base = remove_level_from_path(fds->dest);
			g_free(fds->dest);
			fds->dest = concat_dir_and_file(base, name);
			fds->confirmed = !isname(fds->dest);

			g_free(base);
			}
		}

	file_util_move_single(fds);
}

static void file_util_move_single_cancel_cb(GenericDialog *gd, gpointer data)
{
	FileDataSingle *fds = data;

	file_data_single_free(fds);
}

static void file_util_move_single_rename_auto_cb(GtkWidget *widget, gpointer data)
{
	GenericDialog *gd = data;
	FileDataSingle *fds;

	fds = gd->data;

	fds->rename_auto = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget));
	gtk_widget_set_sensitive(fds->rename_box, !fds->rename_auto);
	gtk_widget_set_sensitive(fds->rename_entry, (!fds->rename_auto && fds->rename));

	if (fds->rename_auto)
		{
		gchar *preview;

		preview = unique_filename_simple(fds->dest);
		if (preview) gtk_entry_set_text(GTK_ENTRY(fds->rename_entry), filename_from_path(preview));
		g_free(preview);
		}
}

static void file_util_move_single_rename_cb(GtkWidget *widget, gpointer data)
{
	GenericDialog *gd = data;
	FileDataSingle *fds;

	fds = gd->data;

	fds->rename = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget));
	gtk_widget_set_sensitive(fds->rename_entry, fds->rename);

	if (fds->rename)
		{
		const gchar *name;

		gtk_widget_grab_focus(fds->rename_entry);

		name = gtk_entry_get_text(GTK_ENTRY(fds->rename_entry));
		gtk_editable_select_region(GTK_EDITABLE(fds->rename_entry), 0, filename_base_length(name));
		}
}

static void file_util_move_single(FileDataSingle *fds)
{
	if (fds->dest && fds->source && strcmp(fds->dest, fds->source) == 0)
		{
		file_util_warning_dialog(_("Source matches destination"),
					 _("Source and destination are the same, operation cancelled."),
					 GTK_STOCK_DIALOG_INFO, NULL);
		}
	else if (isfile(fds->dest) && !fds->confirmed)
		{
		GenericDialog *gd;
		GtkWidget *hbox;

		gd = file_util_gen_dlg(_("Overwrite file"), "GQview", "dlg_confirm",
					NULL, TRUE,
					file_util_move_single_cancel_cb, fds);

		generic_dialog_add_message(gd, GTK_STOCK_DIALOG_QUESTION,
					   _("Overwrite file?"),
					   _("Replace existing file with new file."));
		pref_spacer(gd->vbox, 0);

		generic_dialog_add_button(gd, GTK_STOCK_OK, _("_Overwrite"), file_util_move_single_ok_cb, TRUE);
		generic_dialog_add_image(gd, NULL, fds->dest, _("Existing file"), fds->source, _("New file"), TRUE);

		/* rename option */

		fds->rename = FALSE;
		fds->rename_auto = FALSE;

		hbox = pref_box_new(gd->vbox, FALSE, GTK_ORIENTATION_HORIZONTAL, PREF_PAD_GAP);

		fds->rename_auto_box = gtk_check_button_new_with_label(_("Auto rename"));
		g_signal_connect(G_OBJECT(fds->rename_auto_box), "clicked",
				 G_CALLBACK(file_util_move_single_rename_auto_cb), gd);
		gtk_box_pack_start(GTK_BOX(hbox), fds->rename_auto_box, FALSE, FALSE, 0);
		gtk_widget_show(fds->rename_auto_box);

		hbox = pref_box_new(gd->vbox, FALSE, GTK_ORIENTATION_HORIZONTAL, PREF_PAD_GAP);

		fds->rename_box = gtk_check_button_new_with_label(_("Rename"));
		g_signal_connect(G_OBJECT(fds->rename_box), "clicked",
				 G_CALLBACK(file_util_move_single_rename_cb), gd);
		gtk_box_pack_start(GTK_BOX(hbox), fds->rename_box, FALSE, FALSE, 0);
		gtk_widget_show(fds->rename_box);

		fds->rename_entry = gtk_entry_new();
		gtk_entry_set_text(GTK_ENTRY(fds->rename_entry), filename_from_path(fds->dest));
		gtk_widget_set_sensitive(fds->rename_entry, FALSE);
		gtk_box_pack_start(GTK_BOX(hbox), fds->rename_entry, TRUE, TRUE, 0);
		gtk_widget_show(fds->rename_entry);

		gtk_widget_show(gd->dialog);
		return;
		}
	else
		{
		gint success = FALSE;
		if (fds->copy)
			{
			if (copy_file(fds->source, fds->dest))
				{
				success = TRUE;
				file_maint_copied(fds->source, fds->dest);
				}
			}
		else
			{
			if (move_file(fds->source, fds->dest))
				{
				success = TRUE;
				file_maint_moved(fds->source, fds->dest, NULL);
				}
			}
		if (!success)
			{
			gchar *title;
			gchar *text;
			if (fds->copy)
				{
				title = _("Error copying file");
				text = g_strdup_printf(_("Unable to copy file:\n%s\nto:\n%s"), fds->source, fds->dest);
				}
			else
				{
				title = _("Error moving file");
				text = g_strdup_printf(_("Unable to move file:\n%s\nto:\n%s"), fds->source, fds->dest);
				}
			file_util_warning_dialog(title, text, GTK_STOCK_DIALOG_ERROR, NULL);
			g_free(text);
			}
		}

	file_data_single_free(fds);
}

/*
 * file move dialog
 */

static void file_util_move_do(FileDialog *fd)
{
	file_dialog_sync_history(fd, TRUE);

	if (fd->multiple_files)
		{
		file_util_move_multiple(file_data_multiple_new(fd->source_list, fd->dest_path, fd->type));
		fd->source_list = NULL;
		}
	else
		{
		if (isdir(fd->dest_path))
			{
			gchar *buf = concat_dir_and_file(fd->dest_path, filename_from_path(fd->source_path));
			gtk_entry_set_text(GTK_ENTRY(fd->entry), buf);
			g_free(buf);
			}
		file_util_move_single(file_data_single_new(fd->source_path, fd->dest_path, fd->type));
		}

	file_dialog_close(fd);
}

static void file_util_move_check(FileDialog *fd)
{
	if (fd->dest_path && strcmp(fd->dest_path, "~") == 0)
		{
		gtk_entry_set_text(GTK_ENTRY(fd->entry), homedir());
		}

	if (fd->multiple_files && !isdir(fd->dest_path))
		{
		if (isfile(fd->dest_path))
			{
			file_util_warning_dialog(_("Invalid destination"),
						 _("When operating with multiple files, please select\na folder, not a file."),
						 GTK_STOCK_DIALOG_INFO, NULL);
			}
		else
			file_util_warning_dialog(_("Invalid folder"),
						 _("Please select an existing folder."),
						 GTK_STOCK_DIALOG_INFO, NULL);
		return;
		}

	if (!fd->dest_path || fd->dest_path[0] != '/')
		{
		if (fd->source_path)
			{
			gchar *base;
			gchar *path;

			base = remove_level_from_path(fd->source_path);
			path = concat_dir_and_file(base, fd->dest_path);

			gtk_entry_set_text(GTK_ENTRY(fd->entry), path);

			g_free(path);
			g_free(base);
			}
		return;
		}

	file_util_move_do(fd);
}

static void file_util_move_cb(FileDialog *fd, gpointer data)
{
	file_util_move_check(fd);
}

static void file_util_move_cancel_cb(FileDialog *fd, gpointer data)
{
	file_dialog_close(fd);
}

static void real_file_util_move(const gchar *source_path, GList *source_list,
				const gchar *dest_path, gint copy, GtkWidget *parent)
{
	FileDialog *fd;
	GtkWidget *label;
	gchar *path = NULL;
	gint multiple;
	const gchar *text;
	const gchar *title;
	const gchar *op_text;
	const gchar *stock_id;

	if (!source_path && !source_list) return;

	if (source_path)
		{
		path = g_strdup(source_path);
		multiple = FALSE;
		}
	else if (source_list->next)
		{
		multiple = TRUE;
		}
	else
		{
		path = g_strdup(source_list->data);
		path_list_free(source_list);
		source_list = NULL;
		multiple = FALSE;
		}

	if (copy)
		{
		title = _("Copy - GQview");
		op_text = _("_Copy");
		if (path)
			{
			text = _("Copy file");
			}
		else
			{
			text = _("Copy multiple files");
			}
		stock_id = GTK_STOCK_COPY;
		}
	else
		{
		title = _("Move - GQview");
		op_text = _("_Move");
		if (path)
			{
			text = _("Move file");
			}
		else
			{
			text = _("Move multiple files");
			}
		stock_id = GTK_STOCK_OK;
		}

	fd = file_util_file_dlg(title, "GQview", "dlg_copymove", parent,
				file_util_move_cancel_cb, NULL);
	generic_dialog_add_message(GENERIC_DIALOG(fd), NULL, text, NULL);

	if (path)
		{
		GtkWidget *box;

		box = pref_box_new(GENERIC_DIALOG(fd)->vbox, FALSE, GTK_ORIENTATION_HORIZONTAL, PREF_PAD_SPACE);
		pref_label_new(box, _("File name:"));
		pref_label_new(box, filename_from_path(path));
		}

	label = pref_label_new(GENERIC_DIALOG(fd)->vbox, _("Choose the destination folder."));
	gtk_misc_set_alignment(GTK_MISC(label), 0.0, 0.5);
	pref_spacer(GENERIC_DIALOG(fd)->vbox, 0);

	file_dialog_add_button(fd, stock_id, op_text, file_util_move_cb, TRUE);

	file_dialog_add_path_widgets(fd, NULL, dest_path, "move_copy", NULL, NULL);

	fd->type = copy;
	fd->source_path = path;
	fd->source_list = source_list;
	fd->multiple_files = multiple;

	gtk_widget_show(GENERIC_DIALOG(fd)->dialog);
}

void file_util_move(const gchar *source_path, GList *source_list, const gchar *dest_path, GtkWidget *parent)
{
	real_file_util_move(source_path, source_list, dest_path, FALSE, parent);
}

void file_util_copy(const gchar *source_path, GList *source_list, const gchar *dest_path, GtkWidget *parent)
{
	real_file_util_move(source_path, source_list, dest_path, TRUE, parent);
}

void file_util_move_simple(GList *list, const gchar *dest_path)
{
	if (!list) return;
	if (!dest_path)
		{
		path_list_free(list);
		return;
		}

	if (!list->next)
		{
		const gchar *source;
		gchar *dest;

		source = list->data;
		dest = concat_dir_and_file(dest_path, filename_from_path(source));

		file_util_move_single(file_data_single_new(source, dest, FALSE));
		g_free(dest);
		path_list_free(list);
		return;
		}

	file_util_move_multiple(file_data_multiple_new(list, dest_path, FALSE));
}

void file_util_copy_simple(GList *list, const gchar *dest_path)
{
	if (!list) return;
	if (!dest_path)
		{
		path_list_free(list);
		return;
		}

	if (!list->next)
		{
		const gchar *source;
		gchar *dest;

		source = list->data;
		dest = concat_dir_and_file(dest_path, filename_from_path(source));

		file_util_move_single(file_data_single_new(source, dest, TRUE));
		g_free(dest);
		path_list_free(list);
		return;
		}

	file_util_move_multiple(file_data_multiple_new(list, dest_path, TRUE));
}

/*
 *--------------------------------------------------------------------------
 * Safe Delete
 *--------------------------------------------------------------------------
 */

static gint file_util_safe_number(gint64 free_space)
{
	gint n = 0;
	gint64 total = 0;
	GList *list;
	GList *work;
	gint sorted = FALSE;
	gint warned = FALSE;

	if (!filelist_read(safe_delete_path, &list, NULL)) return 0;

	work = list;
	while (work)
		{
		FileData *fd;
		gint v;
	       
		fd = work->data;
		work = work->next;

		v = (gint)strtol(fd->name, NULL, 10);
		if (v >= n) n = v + 1;

		total += fd->size;
		}

	while (list &&
	       (free_space < 0 || total + free_space > (gint64)safe_delete_size * 1048576) )
		{
		FileData *fd;

		if (!sorted)
			{
			list = filelist_sort(list, SORT_NAME, TRUE);
			sorted = TRUE;
			}

		fd = list->data;
		list = g_list_remove(list, fd);

		if (debug) printf("expunging from trash for space: %s\n", fd->name);
		if (!unlink_file(fd->path) && !warned)
			{
			file_util_warning_dialog(_("Delete failed"),
						 _("Unable to remove old file from trash folder"),
						 GTK_STOCK_DIALOG_WARNING, NULL);
			warned = TRUE;
			}
		total -= fd->size;
		file_data_free(fd);
		}

	filelist_free(list);

	return n;
}

void file_util_trash_clear(void)
{
	file_util_safe_number(-1);
}

static gchar *file_util_safe_dest(const gchar *path)
{
	gint n;

	n = file_util_safe_number(filesize(path));
	return g_strdup_printf("%s/%06d_%s", safe_delete_path, n, filename_from_path(path));
}

static void file_util_safe_del_toggle_cb(GtkWidget *button, gpointer data)
{
	safe_delete_enable = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(button));
}

static void file_util_safe_del_close_cb(GtkWidget *dialog, gpointer data)
{
	GenericDialog **gd = data;

	*gd = NULL;
}

static gint file_util_unlink(const gchar *path)
{
	static GenericDialog *gd = NULL;
	gchar *result = NULL;
	gint success = TRUE;

	if (!isfile(path)) return FALSE;

	if (!safe_delete_enable)
		{
		return unlink_file(path);
		}

	if (!isdir(safe_delete_path))
		{
		if (debug) printf("creating trash: %s\n", safe_delete_path);
		if (!safe_delete_path || !mkdir_utf8(safe_delete_path, 0755))
			{
			result = _("Could not create folder");
			success = FALSE;
			}
		}

	if (success)
		{
		gchar *dest;

		dest = file_util_safe_dest(path);
		if (dest)
			{
			if (debug) printf("safe deleting %s to %s\n", path, dest);
			success = move_file(path, dest);
			}
		else
			{
			success = FALSE;
			}

		if (!success && !access_file(path, W_OK))
			{
			result = _("Permission denied");
			}
		g_free(dest);
		}

	if (result && !gd)
		{
		GtkWidget *button;
		gchar *buf;

		buf = g_strdup_printf(_("Unable to access or create the trash folder.\n\"%s\""), safe_delete_path);
		gd = file_util_warning_dialog(result, buf, GTK_STOCK_DIALOG_WARNING, NULL);
		g_free(buf);

		button = gtk_check_button_new_with_label(_("Turn off safe delete"));
		g_signal_connect(G_OBJECT(button), "toggled",
				 G_CALLBACK(file_util_safe_del_toggle_cb), NULL);
		gtk_box_pack_start(GTK_BOX(gd->vbox), button, FALSE, FALSE, 0);
		gtk_widget_show(button);

		g_signal_connect(G_OBJECT(gd->dialog), "destroy",
				 G_CALLBACK(file_util_safe_del_close_cb), &gd);
		}

	return success;
}

static void box_append_safe_delete_status(GenericDialog *gd)
{
	GtkWidget *label;
	gchar *buf;

	buf = g_strdup_printf(_("Safe delete: %s"), (safe_delete_enable) ? _("on") : _("off"));
	label = pref_label_new(gd->vbox, buf);
	g_free(buf);

	gtk_misc_set_alignment(GTK_MISC(label), 1.0, 0.5);
	gtk_widget_set_sensitive(label, FALSE);
}

/*
 *--------------------------------------------------------------------------
 * Delete routines
 *--------------------------------------------------------------------------
 */

/*
 * delete multiple files
 */

static void file_util_delete_multiple_ok_cb(GenericDialog *gd, gpointer data);
static void file_util_delete_multiple_cancel_cb(GenericDialog *gd, gpointer data);

static void file_util_delete_multiple_ok_cb(GenericDialog *gd, gpointer data)
{
	GList *source_list = data;

	while (source_list)
		{
		gchar *path = source_list->data;

		source_list = g_list_remove(source_list, path);

		if (!file_util_unlink(path))
			{
			if (source_list)
				{
				GenericDialog *d;
				gchar *text;

				d = file_util_gen_dlg(_("Delete failed"), "GQview", "dlg_confirm",
						      NULL, TRUE,
						      file_util_delete_multiple_cancel_cb, source_list);

				text = g_strdup_printf(_("Unable to delete file:\n %s\n Continue multiple delete operation?"), path);
				generic_dialog_add_message(d, GTK_STOCK_DIALOG_WARNING, NULL, text);
				g_free(text);

				generic_dialog_add_button(d, GTK_STOCK_GO_FORWARD, _("Co_ntinue"),
							  file_util_delete_multiple_ok_cb, TRUE);
				gtk_widget_show(d->dialog);
				}
			else
				{
				gchar *text;
				
				text = g_strdup_printf(_("Unable to delete file:\n%s"), path);
				file_util_warning_dialog(_("Delete failed"), text, GTK_STOCK_DIALOG_ERROR, NULL);
				g_free(text);
				}
			g_free(path);
			return;
			}
		else
			{
			file_maint_removed(path, source_list);
			}
		g_free(path);
		}
}

static void file_util_delete_multiple_cancel_cb(GenericDialog *gd, gpointer data)
{
	GList *source_list = data;

	path_list_free(source_list);
}

static void file_util_delete_multiple_review_skip(GenericDialog *gd, gint next)
{
	GtkWidget *button_back;
	GtkWidget *button_next;
	GtkWidget *button_label;
	GList *list;
	GList *list_point;
	const gchar *path;
	gchar *buf;

	list = gd->data;
	button_back = g_object_get_data(G_OBJECT(gd->dialog), "button_back");
	button_next = g_object_get_data(G_OBJECT(gd->dialog), "button_next");
	button_label = g_object_get_data(G_OBJECT(gd->dialog), "button_label");
	list_point = g_object_get_data(G_OBJECT(gd->dialog), "list_point");

	if (!list || !button_label) return;

	if (list_point)
		{
		if (next)
			{
			if (list_point->next) list_point = list_point->next;
			}
		else
			{
			if (list_point->prev) list_point = list_point->prev;
			}
		}
	else
		{
		list_point = list;
		}

	if (!list_point) return;

	path = list_point->data;
	buf = g_strdup_printf(_("File %d of %d"),
			      g_list_index(list, (gpointer)path) + 1,
			      g_list_length(list));
	gtk_label_set_text(GTK_LABEL(button_label), buf);
	g_free(buf);

	gtk_widget_set_sensitive(button_back, (list_point->prev != NULL) );
	gtk_widget_set_sensitive(button_next, (list_point->next != NULL) );

	generic_dialog_image_set(gd, path);

	g_object_set_data(G_OBJECT(gd->dialog), "list_point", list_point);
}

static void file_util_delete_multiple_review_back(GtkWidget *button, gpointer data)
{
	GenericDialog *gd = data;

	file_util_delete_multiple_review_skip(gd, FALSE);
}

static void file_util_delete_multiple_review_next(GtkWidget *button, gpointer data)
{
	GenericDialog *gd = data;

	file_util_delete_multiple_review_skip(gd, TRUE);
}

static void file_util_delete_multiple_review_button_cb(ImageWindow *imd, gint button, guint32 time,
						       gdouble x, gdouble y, guint state, gpointer data)
{
	if (button == 1)
		{
		file_util_delete_multiple_review_next(NULL, data);
		}
	else if (button == 2 || button == 3)
		{
		file_util_delete_multiple_review_back(NULL, data);
		}
}

static void file_util_delete_multiple_review_scroll_cb(ImageWindow *imd, GdkScrollDirection direction, guint32 time,
						       gdouble x, gdouble y, guint state, gpointer data)
{
	if (direction == GDK_SCROLL_UP)
		{
		file_util_delete_multiple_review_back(NULL, data);
		}
	else if (direction == GDK_SCROLL_DOWN)
		{
		file_util_delete_multiple_review_next(NULL, data);
		}
}

static void file_util_delete_multiple(GList *source_list, GtkWidget *parent)
{
	if (!confirm_delete)
		{
		file_util_delete_multiple_ok_cb(NULL, source_list);
		}
	else
		{
		GenericDialog *gd;
		GtkWidget *hbox;
		GtkWidget *button;
		GtkWidget *label;
		ImageWindow *imd;
		gchar *buf;

		gd = file_util_gen_dlg(_("Delete files - GQview"),
					"GQview", "dlg_confirm", parent, TRUE,
					file_util_delete_multiple_cancel_cb, source_list);

		generic_dialog_add_message(gd, NULL, _("Delete multiple files"), NULL);

		generic_dialog_add_image(gd, NULL, NULL, NULL, NULL, NULL, TRUE);
		imd = g_object_get_data(G_OBJECT(gd->dialog), "img_image");
		image_set_button_func(imd, file_util_delete_multiple_review_button_cb, gd);
		image_set_scroll_func(imd, file_util_delete_multiple_review_scroll_cb, gd);

		hbox = pref_box_new(gd->vbox, FALSE, GTK_ORIENTATION_HORIZONTAL, PREF_PAD_BUTTON_GAP);

		button = pref_button_new(hbox, GTK_STOCK_GO_BACK, NULL, TRUE,
					 G_CALLBACK(file_util_delete_multiple_review_back), gd);
		gtk_widget_set_sensitive(button, FALSE);
		g_object_set_data(G_OBJECT(gd->dialog), "button_back", button);

		button = pref_button_new(hbox, GTK_STOCK_GO_FORWARD, NULL, TRUE,
					 G_CALLBACK(file_util_delete_multiple_review_next), gd);
		g_object_set_data(G_OBJECT(gd->dialog), "button_next", button);

		buf = g_strdup_printf(_("Review %d files"), g_list_length(source_list) );
		label = pref_label_new(hbox, buf);
		g_free(buf);
		g_object_set_data(G_OBJECT(gd->dialog), "button_label", label);

		box_append_safe_delete_status(gd);

		generic_dialog_add_button(gd, GTK_STOCK_DELETE, NULL, file_util_delete_multiple_ok_cb, TRUE);

		gtk_widget_show(gd->dialog);
		}
}

/*
 * delete single file
 */

static void file_util_delete_ok_cb(GenericDialog *gd, gpointer data)
{
	gchar *path = data;

	if (!file_util_unlink(path))
		{
		gchar *text = g_strdup_printf(_("Unable to delete file:\n%s"), path);
		file_util_warning_dialog(_("File deletion failed"), text, GTK_STOCK_DIALOG_ERROR, NULL);
		g_free(text);
		}
	else
		{
		file_maint_removed(path, NULL);
		}

	g_free(path);
}

static void file_util_delete_cancel_cb(GenericDialog *gd, gpointer data)
{
	gchar *path = data;

	g_free(path);
}

static void file_util_delete_single(const gchar *path, GtkWidget *parent)
{
	gchar *buf = g_strdup(path);

	if (!confirm_delete)
		{
		file_util_delete_ok_cb(NULL, buf);
		}
	else
		{
		GenericDialog *gd;
		GtkWidget *table;
		gchar *base;

		gd = file_util_gen_dlg(_("Delete file - GQview"), "GQview", "dlg_confirm",
					parent, TRUE,
					file_util_delete_cancel_cb, buf);

		generic_dialog_add_message(gd, NULL, _("Delete file?"), NULL);

		table = pref_table_new(gd->vbox, 2, 2, FALSE, FALSE);

		pref_table_label(table, 0, 0, _("File name:"), 1.0);
		pref_table_label(table, 1, 0, filename_from_path(path), 0.0);

		pref_table_label(table, 0, 1, _("Location:"), 1.0);

		base = remove_level_from_path(path);
		pref_table_label(table, 1, 1, base, 0.0);
		g_free(base);

		generic_dialog_add_image(gd, NULL, path, NULL, NULL, NULL, FALSE);

		box_append_safe_delete_status(gd);

		generic_dialog_add_button(gd, GTK_STOCK_DELETE, NULL, file_util_delete_ok_cb, TRUE);

		gtk_widget_show(gd->dialog);
		}
}

void file_util_delete(const gchar *source_path, GList *source_list, GtkWidget *parent)
{
	if (!source_path && !source_list) return;

	if (source_path)
		{
		file_util_delete_single(source_path, parent);
		}
	else if (!source_list->next)
		{
		file_util_delete_single(source_list->data, parent);
		path_list_free(source_list);
		}
	else
		{
		file_util_delete_multiple(source_list, parent);
		}
}

/*
 *--------------------------------------------------------------------------
 * Rename routines
 *--------------------------------------------------------------------------
 */

/*
 * rename multiple files
 */

enum {
	RENAME_COLUMN_PATH = 0,
	RENAME_COLUMN_NAME,
	RENAME_COLUMN_PREVIEW,
	RENAME_COLUMN_COUNT
};

typedef enum {
	RENAME_TYPE_MANUAL = 0,
	RENAME_TYPE_FORMATTED,
	RENAME_TYPE_AUTO
} RenameType;

typedef struct _RenameDataMult RenameDataMult;
struct _RenameDataMult
{
	FileDialog *fd;

	RenameType rename_type;

	GtkWidget *listview;
	GtkWidget *combo_type;

	GtkWidget *rename_box;
	GtkWidget *rename_label;
	GtkWidget *rename_entry;

	GtkWidget *auto_box;
	GtkWidget *auto_entry_front;
	GtkWidget *auto_spin_start;
	GtkWidget *auto_spin_pad;
	GtkWidget *auto_entry_end;

	GtkWidget *format_box;
	GtkWidget *format_entry;
	GtkWidget *format_spin;

	ImageWindow *imd;

	gint update_idle_id;
};

static void file_util_rename_multiple(RenameDataMult *rd);

static void file_util_rename_multiple_ok_cb(GenericDialog *gd, gpointer data)
{
	RenameDataMult *rd = data;
	GtkWidget *dialog;

	dialog = GENERIC_DIALOG(rd->fd)->dialog;
	if (!GTK_WIDGET_VISIBLE(dialog)) gtk_widget_show(dialog);

	rd->fd->type = TRUE;
	file_util_rename_multiple(rd);
}

static void file_util_rename_multiple_cancel_cb(GenericDialog *gd, gpointer data)
{
	RenameDataMult *rd = data;
	GtkWidget *dialog;

	dialog = GENERIC_DIALOG(rd->fd)->dialog;
	if (!GTK_WIDGET_VISIBLE(dialog)) gtk_widget_show(dialog);
}

static gint file_util_rename_multiple_find_row(RenameDataMult *rd, const gchar *path, GtkTreeIter *iter)
{
	GtkTreeModel *store;
	gint valid;
	gint row = 0;

	store = gtk_tree_view_get_model(GTK_TREE_VIEW(rd->listview));
	valid = gtk_tree_model_get_iter_first(store, iter);
	while (valid)
		{
		gchar *path_n;
		gint ret;

		gtk_tree_model_get(GTK_TREE_MODEL(store), iter, RENAME_COLUMN_PATH, &path_n, -1);
		ret = (strcmp(path_n, path) == 0);
		g_free(path_n);
		if (ret) return row;

		valid = gtk_tree_model_iter_next(GTK_TREE_MODEL(store), iter);
		row++;
		}

	return -1;
}

static void file_util_rename_multiple(RenameDataMult *rd)
{
	FileDialog *fd;

	fd = rd->fd;

	if (isfile(fd->dest_path) && !fd->type)
		{
		GenericDialog *gd;

		gd = file_util_gen_dlg(_("Overwrite file"), "GQview", "dlg_confirm",
					NULL, TRUE,
					file_util_rename_multiple_cancel_cb, rd);

		generic_dialog_add_message(gd, GTK_STOCK_DIALOG_QUESTION,
					   _("Overwrite file?"),
					   _("Replace existing file by renaming new file."));
		pref_spacer(gd->vbox, 0);

		generic_dialog_add_button(gd, GTK_STOCK_OK, _("_Overwrite"), file_util_rename_multiple_ok_cb, TRUE);
		generic_dialog_add_image(gd, NULL,
					 fd->dest_path, _("Existing file"),
					 fd->source_path, _("New file"), TRUE);

		gtk_widget_hide(GENERIC_DIALOG(fd)->dialog);

		gtk_widget_show(gd->dialog);
		return;
		}
	else
		{
		if (!rename_file(fd->source_path, fd->dest_path))
			{
			gchar *text = g_strdup_printf(_("Unable to rename file:\n%s\n to:\n%s"),
						      filename_from_path(fd->source_path),
						      filename_from_path(fd->dest_path));
			file_util_warning_dialog(_("Error renaming file"), text, GTK_STOCK_DIALOG_ERROR, NULL);
			g_free(text);
			}
		else
			{
			GtkTreeModel *store;
			GtkTreeIter iter;
			GtkTreeIter next;
			gint row;

			file_maint_renamed(fd->source_path, fd->dest_path);

			store = gtk_tree_view_get_model(GTK_TREE_VIEW(rd->listview));
			row = file_util_rename_multiple_find_row(rd, rd->fd->source_path, &iter);

			if (row >= 0 &&
			    (gtk_tree_model_iter_nth_child(store, &next, NULL, row + 1) ||
			    (row > 0 && gtk_tree_model_iter_nth_child(store, &next, NULL, row - 1)) ) )
				{
				GtkTreeSelection *selection;

				selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(rd->listview));
				gtk_tree_selection_select_iter(selection, &next);
				gtk_list_store_remove(GTK_LIST_STORE(store), &iter);
				}
			else
				{
				if (debug) printf("closed by #%d\n", row);

				file_dialog_close(rd->fd);
				}
			}
		}
}

/* format: * = filename without extension, ## = number position, extension is kept */
static gchar *file_util_rename_multiple_auto_format_name(const gchar *format, const gchar *name, gint n)
{
	gchar *new_name;
	gchar *parsed;
	const gchar *ext;
	gchar *middle;
	gchar *tmp;
	gchar *pad_start;
	gchar *pad_end;
	gint padding;

	if (!format || !name) return NULL;

	tmp = g_strdup(format);
	pad_start = strchr(tmp, '#');
	if (pad_start)
		{
		pad_end = pad_start;
		padding = 0;
		while (*pad_end == '#')
			{
			pad_end++;
			padding++;
			}
		*pad_start = '\0';

		parsed = g_strdup_printf("%s%0*d%s", tmp, padding, n, pad_end);
		g_free(tmp);
		}
	else
		{
		parsed = tmp;
		}

	ext = extension_from_path(name);

	middle = strchr(parsed, '*');
	if (middle)
		{
		gchar *base;

		*middle = '\0';
		middle++;

		base = remove_extension_from_path(name);
		new_name = g_strconcat(parsed, base, middle, ext, NULL);
		g_free(base);
		}
	else
		{
		new_name = g_strconcat(parsed, ext, NULL);
		}

	g_free(parsed);

	return new_name;
}

static void file_util_rename_multiple_auto(RenameDataMult *rd)
{
	const gchar *front;
	const gchar *end;
	const gchar *format;
	gint start_n;
	gint padding;
	gint n;
	GtkTreeModel *store;
	GtkTreeIter iter;
	gint valid;
	gint success;

	front = gtk_entry_get_text(GTK_ENTRY(rd->auto_entry_front));
	end = gtk_entry_get_text(GTK_ENTRY(rd->auto_entry_end));
	padding = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(rd->auto_spin_pad));

	format = gtk_entry_get_text(GTK_ENTRY(rd->format_entry));

	if (rd->rename_type == RENAME_TYPE_FORMATTED)
		{
		start_n = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(rd->format_spin));

		if (!format ||
		    (strchr(format, '*') == NULL && strchr(format, '#') == NULL))
			{
			file_util_warning_dialog(_("Auto rename"),
			       _("Format must include at least one of the symbol characters '*' or '#'.\n"),
			       GTK_STOCK_DIALOG_WARNING, NULL);
			return;
			}

		history_combo_append_history(rd->format_entry, NULL);
		}
	else
		{
		start_n = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(rd->auto_spin_start));

		history_combo_append_history(rd->auto_entry_front, NULL);
		history_combo_append_history(rd->auto_entry_end, NULL);
		}

	store = gtk_tree_view_get_model(GTK_TREE_VIEW(rd->listview));

	/* first check for name conflicts */
	success = TRUE;
	n = start_n;
	valid = gtk_tree_model_get_iter_first(store, &iter);
	while (valid && success)
		{
		gchar *dest;
		gchar *base;
		gchar *path;

		gtk_tree_model_get(store, &iter, RENAME_COLUMN_PATH, &path, -1);
		base = remove_level_from_path(path);

		if (rd->rename_type == RENAME_TYPE_FORMATTED)
			{
			gchar *new_name;

			new_name = file_util_rename_multiple_auto_format_name(format, filename_from_path(path), n);
			dest = g_strconcat(base, "/", new_name, NULL);
			g_free(new_name);
			}
		else
			{
			dest = g_strdup_printf("%s/%s%0*d%s", base, front, padding, n, end);
			}

		if (isname(dest)) success = FALSE;

		g_free(dest);
		g_free(base);
		g_free(path);

		n++;
		valid = gtk_tree_model_iter_next(store, &iter);
		}

	if (!success)
		{
		file_util_warning_dialog(_("Auto rename"),
			       _("Can not auto rename with the selected\nnumber set, one or more files exist that\nmatch the resulting name list.\n"),
			       GTK_STOCK_DIALOG_WARNING, NULL);
		return;
		}

	/* select the first iter, so that on fail the correct info is given to user */
	if (gtk_tree_model_get_iter_first(store, &iter))
		{
		GtkTreeSelection *selection;

		selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(rd->listview));
		gtk_tree_selection_select_iter(selection, &iter);
		}

	/* now do it for real */
	success = TRUE;
	n = start_n;
	while (success && gtk_tree_model_get_iter_first(store, &iter))
		{
		gchar *dest;
		gchar *base;
		gchar *path;

		gtk_tree_model_get(store, &iter, RENAME_COLUMN_PATH, &path, -1);
		base = remove_level_from_path(path);

		if (rd->rename_type == RENAME_TYPE_FORMATTED)
			{
			gchar *new_name;

			new_name = file_util_rename_multiple_auto_format_name(format, filename_from_path(path), n);
			dest = g_strconcat(base, "/", new_name, NULL);
			g_free(new_name);
			}
		else
			{
			dest = g_strdup_printf("%s/%s%0*d%s", base, front, padding, n, end);
			}

		if (!rename_file(path, dest))
			{
			success = FALSE;
			}
		else
			{
			file_maint_renamed(path, dest);
			}

		g_free(dest);
		g_free(base);
		g_free(path);

		if (success)
			{
			gtk_list_store_remove(GTK_LIST_STORE(store), &iter);
			if (gtk_tree_model_get_iter_first(store, &iter))
				{
				GtkTreeSelection *selection;

				selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(rd->listview));
				gtk_tree_selection_select_iter(selection, &iter);
				}
			}

		n++;
		}

	if (!success)
		{
		gchar *buf;

		n--;
		gtk_spin_button_set_value(GTK_SPIN_BUTTON(rd->auto_spin_start), (gdouble)n);

		buf = g_strdup_printf(_("Failed to rename\n%s\nThe number was %d."), filename_from_path(rd->fd->source_path), n);
		file_util_warning_dialog(_("Auto rename"), buf, GTK_STOCK_DIALOG_ERROR, NULL);
		g_free(buf);

		return;
		}

	file_dialog_close(rd->fd);
}

static void file_util_rename_multiple_cb(FileDialog *fd, gpointer data)
{
	RenameDataMult *rd = data;
	gchar *base;
	const gchar *name;

	if (rd->rename_type != RENAME_TYPE_MANUAL)
		{
		file_util_rename_multiple_auto(rd);
		return;
		}

	name = gtk_entry_get_text(GTK_ENTRY(rd->rename_entry));
	base = remove_level_from_path(fd->source_path);

	g_free(fd->dest_path);
	fd->dest_path = concat_dir_and_file(base, name);
	g_free(base);

	if (strlen(name) == 0 || strcmp(fd->source_path, fd->dest_path) == 0)
		{
		return;
		}

	fd->type = FALSE;
	file_util_rename_multiple(rd);
}

static void file_util_rename_multiple_close_cb(FileDialog *fd, gpointer data)
{
	RenameDataMult *rd = data;

	file_dialog_close(rd->fd);
}

static gboolean file_util_rename_multiple_select_cb(GtkTreeSelection *selection, GtkTreeModel *store, GtkTreePath *tpath,
						    gboolean path_currently_selected, gpointer data)
{
	RenameDataMult *rd = data;
	GtkTreeIter iter;
	const gchar *name;
	gchar *path = NULL;

	if (path_currently_selected ||
	    !gtk_tree_model_get_iter(store, &iter, tpath)) return TRUE;
	gtk_tree_model_get(store, &iter, RENAME_COLUMN_PATH, &path, -1);

	g_free(rd->fd->source_path);
	rd->fd->source_path = path;

	name = filename_from_path(rd->fd->source_path);
	gtk_label_set_text(GTK_LABEL(rd->rename_label), name);
	gtk_entry_set_text(GTK_ENTRY(rd->rename_entry), name);

	image_change_path(rd->imd, rd->fd->source_path, 0.0);

	if (GTK_WIDGET_VISIBLE(rd->rename_box))
		{
		gtk_widget_grab_focus(rd->rename_entry);
		gtk_editable_select_region(GTK_EDITABLE(rd->rename_entry), 0, filename_base_length(name));
		}

	return TRUE;
}

static void file_util_rename_multiple_preview_update(RenameDataMult *rd)
{
	GtkTreeModel *store;
	GtkTreeIter iter;
	const gchar *front;
	const gchar *end;
	const gchar *format;
	gint valid;
	gint start_n;
	gint padding;
	gint n;

	front = gtk_entry_get_text(GTK_ENTRY(rd->auto_entry_front));
	end = gtk_entry_get_text(GTK_ENTRY(rd->auto_entry_end));
	padding = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(rd->auto_spin_pad));

	format = gtk_entry_get_text(GTK_ENTRY(rd->format_entry));

	if (rd->rename_type == RENAME_TYPE_FORMATTED)
		{
		start_n = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(rd->format_spin));
		}
	else
		{
		start_n = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(rd->auto_spin_start));
		}

	store = gtk_tree_view_get_model(GTK_TREE_VIEW(rd->listview));
	n = start_n;
	valid = gtk_tree_model_get_iter_first(store, &iter);
	while (valid)
		{
		gchar *dest;

		if (rd->rename_type == RENAME_TYPE_FORMATTED)
			{
			gchar *path;
	
			gtk_tree_model_get(store, &iter, RENAME_COLUMN_PATH, &path, -1);
			dest = file_util_rename_multiple_auto_format_name(format, filename_from_path(path), n);
			g_free(path);
			}
		else
			{
			dest = g_strdup_printf("%s%0*d%s", front, padding, n, end);
			}
		gtk_list_store_set(GTK_LIST_STORE(store), &iter, RENAME_COLUMN_PREVIEW, dest, -1);
		g_free(dest);

		n++;
		valid = gtk_tree_model_iter_next(store, &iter);
		}

}

static gboolean file_util_rename_multiple_idle_cb(gpointer data)
{
	RenameDataMult *rd = data;

	file_util_rename_multiple_preview_update(rd);

	rd->update_idle_id = -1;
	return FALSE;
}

static void file_util_rename_multiple_preview_order_cb(GtkTreeModel *treemodel, GtkTreePath *tpath,
						       GtkTreeIter *iter, gpointer data)
{
	RenameDataMult *rd = data;

	if (rd->rename_type != RENAME_TYPE_MANUAL && rd->update_idle_id == -1)
		{
		rd->update_idle_id = g_idle_add(file_util_rename_multiple_idle_cb, rd);
		}
}

static void file_util_rename_multiple_preview_entry_cb(GtkWidget *entry, gpointer data)
{
	RenameDataMult *rd = data;
	file_util_rename_multiple_preview_update(rd);
}

static void file_util_rename_multiple_preview_adj_cb(GtkWidget *spin, gpointer data)
{
	RenameDataMult *rd = data;
	file_util_rename_multiple_preview_update(rd);
}

static void file_util_rename_multiple_auto_change(GtkWidget *widget, gpointer data)
{
	RenameDataMult *rd = data;
	GtkTreeViewColumn *column;

	rd->rename_type = gtk_combo_box_get_active(GTK_COMBO_BOX(rd->combo_type));

	switch (rd->rename_type)
		{
		case RENAME_TYPE_FORMATTED:
			if (GTK_WIDGET_VISIBLE(rd->rename_box)) gtk_widget_hide(rd->rename_box);
			if (GTK_WIDGET_VISIBLE(rd->auto_box)) gtk_widget_hide(rd->auto_box);
			if (!GTK_WIDGET_VISIBLE(rd->format_box)) gtk_widget_show(rd->format_box);
			file_util_rename_multiple_preview_update(rd);
			break;
		case RENAME_TYPE_AUTO:
			if (GTK_WIDGET_VISIBLE(rd->format_box)) gtk_widget_hide(rd->format_box);
			if (GTK_WIDGET_VISIBLE(rd->rename_box)) gtk_widget_hide(rd->rename_box);
			if (!GTK_WIDGET_VISIBLE(rd->auto_box)) gtk_widget_show(rd->auto_box);
			file_util_rename_multiple_preview_update(rd);
			break;
		case RENAME_TYPE_MANUAL:
		default:
			if (GTK_WIDGET_VISIBLE(rd->format_box)) gtk_widget_hide(rd->format_box);
			if (GTK_WIDGET_VISIBLE(rd->auto_box)) gtk_widget_hide(rd->auto_box);
			if (!GTK_WIDGET_VISIBLE(rd->rename_box)) gtk_widget_show(rd->rename_box);
			break;
		}

	column = gtk_tree_view_get_column(GTK_TREE_VIEW(rd->listview), RENAME_COLUMN_PREVIEW - 1);
	gtk_tree_view_column_set_visible(column, (rd->rename_type != RENAME_TYPE_MANUAL));
}

static GtkWidget *furm_simple_vlabel(GtkWidget *box, const gchar *text, gint expand)
{
	GtkWidget *vbox;
	GtkWidget *label;

	vbox = gtk_vbox_new(FALSE, 0);
	gtk_box_pack_start(GTK_BOX(box), vbox, expand, expand, 0);
	gtk_widget_show(vbox);

	label = gtk_label_new(text);
	gtk_box_pack_start(GTK_BOX(vbox), label, FALSE, FALSE, 0);
	gtk_widget_show(label);

	return vbox;
}

static GtkTreeViewColumn *file_util_rename_multiple_add_column(RenameDataMult *rd, const gchar *text, gint n)
{
	GtkTreeViewColumn *column;
	GtkCellRenderer *renderer;

	column = gtk_tree_view_column_new();
        gtk_tree_view_column_set_title(column, text);
        gtk_tree_view_column_set_min_width(column, 4);
        gtk_tree_view_column_set_sizing(column, GTK_TREE_VIEW_COLUMN_GROW_ONLY);
        renderer = gtk_cell_renderer_text_new();
        gtk_tree_view_column_pack_start(column, renderer, TRUE);
        gtk_tree_view_column_add_attribute(column, renderer, "text", n);
        gtk_tree_view_append_column(GTK_TREE_VIEW(rd->listview), column);

	return column;
}

static void file_util_rename_multiple_destroy_cb(GtkWidget *widget, gpointer data)
{
	RenameDataMult *rd = data;

	if (rd->update_idle_id != -1) g_source_remove(rd->update_idle_id);

	g_free(rd);
}

static void file_util_rename_multiple_do(GList *source_list, GtkWidget *parent)
{
	RenameDataMult *rd;
	GtkWidget *pane;
	GtkWidget *scrolled;
	GtkListStore *store;
	GtkTreeSelection *selection;
	GtkTreeViewColumn *column;
	GtkWidget *hbox;
	GtkWidget *vbox;
	GtkWidget *box2;
	GtkWidget *table;
	GtkWidget *combo;
	GList *work;
	const gchar *name;

	rd = g_new0(RenameDataMult, 1);

	rd->fd = file_util_file_dlg(_("Rename - GQview"),
				    "GQview", "dlg_rename", parent,
				    file_util_rename_multiple_close_cb, rd);
	generic_dialog_add_message(GENERIC_DIALOG(rd->fd), NULL, _("Rename multiple files"), NULL);
	file_dialog_add_button(rd->fd, GTK_STOCK_OK, _("_Rename"), file_util_rename_multiple_cb, TRUE);

	rd->fd->source_path = g_strdup(source_list->data);
	rd->fd->dest_path = NULL;

	rd->rename_type = RENAME_TYPE_MANUAL;

	rd->update_idle_id = -1;

	vbox = GENERIC_DIALOG(rd->fd)->vbox;

	pane = gtk_hpaned_new();
	gtk_box_pack_start(GTK_BOX(vbox), pane, TRUE, TRUE, 0);
	gtk_widget_show(pane);
	
	scrolled = gtk_scrolled_window_new(NULL, NULL);
	gtk_scrolled_window_set_shadow_type(GTK_SCROLLED_WINDOW(scrolled), GTK_SHADOW_IN);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW (scrolled),
				       GTK_POLICY_AUTOMATIC, GTK_POLICY_ALWAYS);
	gtk_paned_pack1(GTK_PANED(pane), scrolled, TRUE, TRUE);
	gtk_widget_show(scrolled);

	store = gtk_list_store_new(3, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
	rd->listview = gtk_tree_view_new_with_model(GTK_TREE_MODEL(store));
	g_object_unref(store);

	gtk_tree_view_set_headers_visible(GTK_TREE_VIEW(rd->listview), TRUE);
	gtk_tree_view_set_enable_search(GTK_TREE_VIEW(rd->listview), FALSE);

	selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(rd->listview));
	gtk_tree_selection_set_mode(GTK_TREE_SELECTION(selection), GTK_SELECTION_SINGLE);
	gtk_tree_selection_set_select_function(selection, file_util_rename_multiple_select_cb, rd, NULL);

	file_util_rename_multiple_add_column(rd, _("Original Name"), RENAME_COLUMN_NAME);
	column = file_util_rename_multiple_add_column(rd, _("Preview"), RENAME_COLUMN_PREVIEW);
	gtk_tree_view_column_set_visible(column, FALSE);
	
	gtk_tree_view_set_reorderable(GTK_TREE_VIEW(rd->listview), TRUE);
	g_signal_connect(G_OBJECT(store), "row_changed",
			 G_CALLBACK(file_util_rename_multiple_preview_order_cb), rd);
	gtk_widget_set_size_request(rd->listview, 250, 150);

	gtk_container_add(GTK_CONTAINER(scrolled), rd->listview);
	gtk_widget_show(rd->listview);

	work = source_list;
	while (work)
		{
		gchar *path = work->data;
		GtkTreeIter iter;

		gtk_list_store_append(store, &iter);
		gtk_list_store_set(store, &iter, RENAME_COLUMN_PATH, path, RENAME_COLUMN_NAME, filename_from_path(path), -1);

		work = work->next;
		}

	path_list_free(source_list);

	rd->imd = image_new(TRUE);
	g_object_set(G_OBJECT(rd->imd->pr), "zoom_expand", FALSE, NULL);
	gtk_widget_set_size_request(rd->imd->widget, DIALOG_DEF_IMAGE_DIM_X, DIALOG_DEF_IMAGE_DIM_Y);
	gtk_paned_pack2(GTK_PANED(pane), rd->imd->widget, FALSE, TRUE);
	gtk_widget_show(rd->imd->widget);

	hbox = gtk_hbox_new(FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);
	gtk_widget_show(hbox);

	rd->combo_type = gtk_combo_box_new_text();

	gtk_combo_box_append_text(GTK_COMBO_BOX(rd->combo_type), _("Manual rename"));
	gtk_combo_box_append_text(GTK_COMBO_BOX(rd->combo_type), _("Formatted rename"));
	gtk_combo_box_append_text(GTK_COMBO_BOX(rd->combo_type), _("Auto rename"));

	gtk_combo_box_set_active(GTK_COMBO_BOX(rd->combo_type), rd->rename_type);

	g_signal_connect(G_OBJECT(rd->combo_type), "changed",
			 G_CALLBACK(file_util_rename_multiple_auto_change), rd);
	gtk_box_pack_end(GTK_BOX(hbox), rd->combo_type, FALSE, FALSE, 0);
	gtk_widget_show(rd->combo_type);

	rd->rename_box = pref_box_new(vbox, FALSE, GTK_ORIENTATION_VERTICAL, 0);
	table = pref_table_new(rd->rename_box, 2, 2, FALSE, FALSE);

	pref_table_label(table, 0, 0, _("Original name:"), 1.0);
	rd->rename_label = pref_table_label(table, 1, 0, filename_from_path(rd->fd->source_path), 0.0);

	pref_table_label(table, 0, 1, _("New name:"), 1.0);

	rd->rename_entry = gtk_entry_new();
	gtk_table_attach(GTK_TABLE(table), rd->rename_entry, 1, 2, 1, 2, GTK_EXPAND | GTK_FILL, 0, 0, 0);
	generic_dialog_attach_default(GENERIC_DIALOG(rd->fd), rd->rename_entry);
	gtk_widget_grab_focus(rd->rename_entry);

	name = filename_from_path(rd->fd->source_path);
	gtk_entry_set_text(GTK_ENTRY(rd->rename_entry), name);
	gtk_editable_select_region(GTK_EDITABLE(rd->rename_entry), 0, filename_base_length(name));
	gtk_widget_show(rd->rename_entry);

	rd->auto_box = gtk_vbox_new(FALSE, PREF_PAD_GAP);
	gtk_box_pack_start(GTK_BOX(vbox), rd->auto_box, FALSE, FALSE, 0);
	/* do not show it here */

	hbox = pref_box_new(rd->auto_box, FALSE, GTK_ORIENTATION_HORIZONTAL, PREF_PAD_GAP);

	box2 = furm_simple_vlabel(hbox, _("Begin text"), TRUE);

	combo = history_combo_new(&rd->auto_entry_front, "", "numerical_rename_prefix", -1);
	g_signal_connect(G_OBJECT(rd->auto_entry_front), "changed",
			 G_CALLBACK(file_util_rename_multiple_preview_entry_cb), rd);
	gtk_box_pack_start(GTK_BOX(box2), combo, TRUE, TRUE, 0);
	gtk_widget_show(combo);
	
	box2 = furm_simple_vlabel(hbox, _("Start #"), FALSE);

	rd->auto_spin_start = pref_spin_new(box2, NULL, NULL,
					    0.0, 1000000.0, 1.0, 0, 1.0,
					    G_CALLBACK(file_util_rename_multiple_preview_adj_cb), rd);

	box2 = furm_simple_vlabel(hbox, _("End text"), TRUE);

	combo = history_combo_new(&rd->auto_entry_end, "", "numerical_rename_suffix", -1);
	g_signal_connect(G_OBJECT(rd->auto_entry_end), "changed",
			 G_CALLBACK(file_util_rename_multiple_preview_entry_cb), rd);
	gtk_box_pack_start(GTK_BOX(box2), combo, TRUE, TRUE, 0);
	gtk_widget_show(combo);

	rd->auto_spin_pad = pref_spin_new(rd->auto_box, _("Padding:"), NULL,
					  1.0, 8.0, 1.0, 0, 1.0,
					  G_CALLBACK(file_util_rename_multiple_preview_adj_cb), rd);

	rd->format_box = gtk_vbox_new(FALSE, PREF_PAD_GAP);
	gtk_box_pack_start(GTK_BOX(vbox), rd->format_box, FALSE, FALSE, 0);
	/* do not show it here */

	hbox = pref_box_new(rd->format_box, FALSE, GTK_ORIENTATION_HORIZONTAL, PREF_PAD_GAP);

	box2 = furm_simple_vlabel(hbox, _("Format (* = original name, ## = numbers)"), TRUE);

	combo = history_combo_new(&rd->format_entry, "", "auto_rename_format", -1);
	g_signal_connect(G_OBJECT(rd->format_entry), "changed",
			 G_CALLBACK(file_util_rename_multiple_preview_entry_cb), rd);
	gtk_box_pack_start(GTK_BOX(box2), combo, TRUE, TRUE, 0);
	gtk_widget_show(combo);
	
	box2 = furm_simple_vlabel(hbox, _("Start #"), FALSE);

	rd->format_spin = pref_spin_new(box2, NULL, NULL,
					0.0, 1000000.0, 1.0, 0, 1.0,
					G_CALLBACK(file_util_rename_multiple_preview_adj_cb), rd);

	image_change_path(rd->imd, rd->fd->source_path, 0.0);

	g_signal_connect(G_OBJECT(GENERIC_DIALOG(rd->fd)->dialog), "destroy",
			 G_CALLBACK(file_util_rename_multiple_destroy_cb), rd);

	gtk_widget_show(GENERIC_DIALOG(rd->fd)->dialog);
}

/*
 * rename single file
 */

static void file_util_rename_single(FileDataSingle *fds);

static void file_util_rename_single_ok_cb(GenericDialog *gd, gpointer data)
{
	FileDataSingle *fds = data;
	fds->confirmed = TRUE;
	file_util_rename_single(fds);
}

static void file_util_rename_single_cancel_cb(GenericDialog *gd, gpointer data)
{
	FileDataSingle *fds = data;
	file_data_single_free(fds);
}

static void file_util_rename_single(FileDataSingle *fds)
{
	if (isfile(fds->dest) && !fds->confirmed)
		{
		GenericDialog *gd;

		gd = file_util_gen_dlg(_("Overwrite file"), "GQview", "dlg_confirm",
					NULL, TRUE,
					file_util_rename_single_cancel_cb, fds);

		generic_dialog_add_message(gd, GTK_STOCK_DIALOG_QUESTION,
					   _("Overwrite file?"),
					   _("Replace existing file by renaming new file."));
		pref_spacer(gd->vbox, 0);

		generic_dialog_add_button(gd, GTK_STOCK_OK, _("_Overwrite"), file_util_rename_single_ok_cb, TRUE);
		generic_dialog_add_image(gd, NULL,
					 fds->dest, _("Existing file"),
					 fds->source, _("New file"), TRUE);

		gtk_widget_show(gd->dialog);

		return;
		}
	else
		{
		if (!rename_file(fds->source, fds->dest))
			{
			gchar *text = g_strdup_printf(_("Unable to rename file:\n%s\nto:\n%s"), filename_from_path(fds->source), filename_from_path(fds->dest));
			file_util_warning_dialog(_("Error renaming file"), text, GTK_STOCK_DIALOG_ERROR, NULL);
			g_free(text);
			}
		else
			{
			file_maint_renamed(fds->source, fds->dest);
			}
		}
	file_data_single_free(fds);
}

static void file_util_rename_single_cb(FileDialog *fd, gpointer data)
{
	const gchar *name;
	gchar *path;

	name = gtk_entry_get_text(GTK_ENTRY(fd->entry));
	path = concat_dir_and_file(fd->dest_path, name);

	if (strlen(name) == 0 || strcmp(fd->source_path, path) == 0)
		{
		g_free(path);
		return;
		}

	file_util_rename_single(file_data_single_new(fd->source_path, path, fd->type));

	g_free(path);
	file_dialog_close(fd);
}

static void file_util_rename_single_close_cb(FileDialog *fd, gpointer data)
{
	file_dialog_close(fd);
}

static void file_util_rename_single_do(const gchar *source_path, GtkWidget *parent)
{
	FileDialog *fd;
	GtkWidget *table;
	const gchar *name;

	fd = file_util_file_dlg(_("Rename - GQview"), "GQview", "dlg_rename", parent,
			     file_util_rename_single_close_cb, NULL);

	generic_dialog_add_message(GENERIC_DIALOG(fd), NULL, _("Rename file"), NULL);
	generic_dialog_add_image(GENERIC_DIALOG(fd), NULL, source_path, NULL, NULL, NULL, FALSE);

	file_dialog_add_button(fd, GTK_STOCK_OK, _("_Rename"), file_util_rename_single_cb, TRUE);

	fd->source_path = g_strdup(source_path);
	fd->dest_path = remove_level_from_path(source_path);

	table = pref_table_new(GENERIC_DIALOG(fd)->vbox, 2, 2, FALSE, FALSE);

	pref_table_label(table, 0, 0, _("Original name:"), 1.0);
	pref_table_label(table, 1, 0, filename_from_path(fd->source_path), 0.0);

	pref_table_label(table, 0, 1, _("New name:"), 1.0);

	fd->entry = gtk_entry_new();
	gtk_table_attach(GTK_TABLE(table), fd->entry, 1, 2, 1, 2, GTK_EXPAND | GTK_FILL, 0, 0, 0);
	generic_dialog_attach_default(GENERIC_DIALOG(fd), fd->entry);
	gtk_widget_grab_focus(fd->entry);

	name = filename_from_path(fd->source_path);
	gtk_entry_set_text(GTK_ENTRY(fd->entry), name);
	gtk_editable_select_region(GTK_EDITABLE(fd->entry), 0, filename_base_length(name));
	gtk_widget_show(fd->entry);

	gtk_widget_show(GENERIC_DIALOG(fd)->dialog);
}

void file_util_rename(const gchar *source_path, GList *source_list, GtkWidget *parent)
{
	if (!source_path && !source_list) return;

	if (source_path)
		{
		file_util_rename_single_do(source_path, parent);
		}
	else if (!source_list->next)
		{
		file_util_rename_single_do(source_list->data, parent);
		path_list_free(source_list);
		}
	else
		{
		file_util_rename_multiple_do(source_list, parent);
		}
}

/*
 *--------------------------------------------------------------------------
 * Create directory routines
 *--------------------------------------------------------------------------
 */

static void file_util_create_dir_do(const gchar *base, const gchar *name)
{
	gchar *path;

	path = concat_dir_and_file(base, name);

	if (isdir(path))
		{
		gchar *text = g_strdup_printf(_("The folder:\n%s\nalready exists."), name);
		file_util_warning_dialog(_("Folder exists"), text, GTK_STOCK_DIALOG_INFO, NULL);
		g_free(text);
		}
	else if (isname(path))
		{
		gchar *text = g_strdup_printf(_("The path:\n%s\nalready exists as a file."), name);
		file_util_warning_dialog(_("Could not create folder"), text, GTK_STOCK_DIALOG_INFO, NULL);
		g_free(text);
		}
	else
		{
		if (!mkdir_utf8(path, 0755))
			{
			gchar *text = g_strdup_printf(_("Unable to create folder:\n%s"), name);
			file_util_warning_dialog(_("Error creating folder"), text, GTK_STOCK_DIALOG_ERROR, NULL);
			g_free(text);
			}
		}

	g_free(path);
}

static void file_util_create_dir_cb(FileDialog *fd, gpointer data)
{
	const gchar *name;

	name = gtk_entry_get_text(GTK_ENTRY(fd->entry));

	if (strlen(name) == 0) return;

	if (name[0] == '/')
		{
		gchar *buf;
		buf  = remove_level_from_path(name);
		file_util_create_dir_do(buf, filename_from_path(name));
		g_free(buf);
		}
	else
		{
		file_util_create_dir_do(fd->dest_path, name);
		}

	file_dialog_close(fd);
}

static void file_util_create_dir_close_cb(FileDialog *fd, gpointer data)
{
	file_dialog_close(fd);
}

void file_util_create_dir(const gchar *path, GtkWidget *parent)
{
	FileDialog *fd;
	gchar *text;

	if (!isdir(path)) return;

	fd = file_util_file_dlg(_("New folder - GQview"), "GQview", "dlg_newdir", parent,
			     file_util_create_dir_close_cb, NULL);

	text = g_strdup_printf(_("Create folder in:\n%s\nnamed:"), path);
	generic_dialog_add_message(GENERIC_DIALOG(fd), NULL, NULL, text);
	g_free(text);

	file_dialog_add_button(fd, GTK_STOCK_OK, NULL, file_util_create_dir_cb, TRUE);

	fd->dest_path = g_strdup(path);

	fd->entry = gtk_entry_new();
	gtk_box_pack_start(GTK_BOX(GENERIC_DIALOG(fd)->vbox), fd->entry, FALSE, FALSE, 0);
	generic_dialog_attach_default(GENERIC_DIALOG(fd), fd->entry);
	gtk_widget_grab_focus(fd->entry);
	gtk_widget_show(fd->entry);

	gtk_widget_show(GENERIC_DIALOG(fd)->dialog);
}

gint file_util_rename_dir(const gchar *old_path, const gchar *new_path, GtkWidget *parent)
{
	const gchar *old_name;
	const gchar *new_name;

	if (!old_path || !new_path || !isdir(old_path)) return FALSE;

	old_name = filename_from_path(old_path);
	new_name = filename_from_path(new_path);

	if (isdir(new_path))
		{
		gchar *text = g_strdup_printf(_("The folder:\n%s\nalready exists."), new_name);
		file_util_warning_dialog(_("Folder exists"), text, GTK_STOCK_DIALOG_INFO, parent);
		g_free(text);

		return FALSE;
		}

	if (isname(new_path))
		{
		gchar *text = g_strdup_printf(_("The path:\n%s\nalready exists as a file."), new_name);
		file_util_warning_dialog(_("Rename failed"), text, GTK_STOCK_DIALOG_INFO,parent);
		g_free(text);

		return FALSE;
		}

	if (!rename_file(old_path, new_path))
		{
		gchar *text = g_strdup_printf(_("Failed to rename %s to %s."), old_name, new_name);
		file_util_warning_dialog(_("Rename failed"), text, GTK_STOCK_DIALOG_ERROR, parent);
		g_free(text);

		return FALSE;
		}

	return TRUE;
}

/*
 *--------------------------------------------------------------------------
 * Delete directory routines
 *--------------------------------------------------------------------------
 */

/* The plan is to eventually make all of utilops.c
 * use UtilityData and UtilityType.
 * And clean up the above mess someday.
 */

typedef enum {
	UTILITY_TYPE_NONE = 0,
	UTILITY_TYPE_COPY,
	UTILITY_TYPE_MOVE,
	UTILITY_TYPE_RENAME,
	UTILITY_TYPE_DELETE,
	UTILITY_TYPE_DELETE_LINK,
	UTILITY_TYPE_DELETE_FOLDER
} UtilityType;

typedef struct _UtilityData UtilityData;
struct _UtilityData {
	UtilityType type;
	gchar *source_path;
	GList *dlist;
	GList *flist;

	GenericDialog *gd;
};

#define UTILITY_LIST_MIN_WIDTH  250
#define UTILITY_LIST_MIN_HEIGHT 150

/* thumbnail spec has a max depth of 4 (.thumb??/fail/appname/??.png) */
#define UTILITY_DELETE_MAX_DEPTH 5


static void file_util_data_free(UtilityData *ud)
{
	if (!ud) return;

	g_free(ud->source_path);
	path_list_free(ud->dlist);
	path_list_free(ud->flist);

	if (ud->gd) generic_dialog_close(ud->gd);

	g_free(ud);
}

static GtkTreeViewColumn *file_util_dialog_add_list_column(GtkWidget *view, const gchar *text, gint n)
{
	GtkTreeViewColumn *column;
	GtkCellRenderer *renderer;

	column = gtk_tree_view_column_new();
	gtk_tree_view_column_set_title(column, text);
	gtk_tree_view_column_set_min_width(column, 4);
	gtk_tree_view_column_set_sizing(column, GTK_TREE_VIEW_COLUMN_GROW_ONLY);
	renderer = gtk_cell_renderer_text_new();
	gtk_tree_view_column_pack_start(column, renderer, TRUE);
	gtk_tree_view_column_add_attribute(column, renderer, "text", n);
	gtk_tree_view_append_column(GTK_TREE_VIEW(view), column);

	return column;
}

static GtkWidget *file_util_dialog_add_list(GtkWidget *box, GList *list, gint full_paths)
{
	GtkWidget *scrolled;
	GtkWidget *view;
	GtkListStore *store;

	scrolled = gtk_scrolled_window_new(NULL, NULL);
	gtk_scrolled_window_set_shadow_type(GTK_SCROLLED_WINDOW(scrolled), GTK_SHADOW_IN);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW (scrolled),
				       GTK_POLICY_AUTOMATIC, GTK_POLICY_ALWAYS);
	gtk_box_pack_start(GTK_BOX(box), scrolled, TRUE, TRUE, 0);
	gtk_widget_show(scrolled);

	store = gtk_list_store_new(2, G_TYPE_STRING, G_TYPE_STRING);
	view = gtk_tree_view_new_with_model(GTK_TREE_MODEL(store));
	g_object_unref(store);

	gtk_tree_view_set_headers_visible(GTK_TREE_VIEW(view), TRUE);
	gtk_tree_view_set_enable_search(GTK_TREE_VIEW(view), FALSE);

	if (full_paths)
		{
		file_util_dialog_add_list_column(view, _("Location"), 0);
		}
	else
		{
		file_util_dialog_add_list_column(view, _("Name"), 1);
		}

	gtk_widget_set_size_request(view, UTILITY_LIST_MIN_WIDTH, UTILITY_LIST_MIN_HEIGHT);
	gtk_container_add(GTK_CONTAINER(scrolled), view);
	gtk_widget_show(view);

	while (list)
		{
		gchar *path = list->data;
		GtkTreeIter iter;

		gtk_list_store_append(store, &iter);
		gtk_list_store_set(store, &iter, 0, path,
						 1, filename_from_path(path), -1);

		list = list->next;
		}

	return view;
}

static gboolean file_util_delete_dir_preview_cb(GtkTreeSelection *selection, GtkTreeModel *store,
						GtkTreePath *tpath, gboolean path_currently_selected,
						gpointer data)
{
	UtilityData *ud = data;
	GtkTreeIter iter;
	gchar *path = NULL;

	if (path_currently_selected ||
	    !gtk_tree_model_get_iter(store, &iter, tpath)) return TRUE;

	gtk_tree_model_get(store, &iter, 0, &path, -1);
	generic_dialog_image_set(ud->gd, path);
	g_free(path);

	return TRUE;
}

static void file_util_delete_dir_cancel_cb(GenericDialog *gd, gpointer data)
{
	UtilityData *ud = data;

	ud->gd = NULL;
	file_util_data_free(ud);
}

static gchar *file_util_delete_dir_empty_path(const gchar *path, gint real_content, gint level)
{
	GList *dlist = NULL;
	GList *flist = NULL;
	GList *work;
	gchar *fail = NULL;

	if (debug) printf("deltree into: %s\n", path);

	level++;
	if (level > UTILITY_DELETE_MAX_DEPTH)
		{
		printf("folder recursion depth past %d, giving up\n", UTILITY_DELETE_MAX_DEPTH);
		return g_strdup(path);
		}

	if (!path_list_lstat(path, &flist, &dlist)) return g_strdup(path);

	work = dlist;
	while (work && !fail)
		{
		gchar *name;

		name = work->data;
		work = work->next;

		fail = file_util_delete_dir_empty_path(name, real_content, level);
		}

	work = flist;
	while (work && !fail)
		{
		gchar *name;

		name = work->data;
		work = work->next;

		if (debug) printf("deltree child: %s\n", name);

		if (real_content && !islink(name))
			{
			if (!file_util_unlink(name)) fail = g_strdup(name);
			}
		else
			{
			if (!unlink_file(name)) fail = g_strdup(name);
			}
		}

	path_list_free(dlist);
	path_list_free(flist);

	if (!fail && !rmdir_utf8(path))
		{
		fail = g_strdup(path);
		}

	if (debug) printf("deltree done: %s\n", path);

	return fail;
}

static void file_util_delete_dir_ok_cb(GenericDialog *gd, gpointer data)
{
	UtilityData *ud = data;

	ud->gd = NULL;

	if (ud->type == UTILITY_TYPE_DELETE_LINK)
		{
		if (!unlink_file(ud->source_path))
			{
			gchar *text;

			text = g_strdup_printf("Unable to remove symbolic link:\n %s", ud->source_path);
			file_util_warning_dialog(_("Delete failed"), text,
						 GTK_STOCK_DIALOG_ERROR, NULL);
			g_free(text);
			}
		}
	else
		{
		gchar *fail = NULL;
		GList *work;

		work = ud->dlist;
		while (work && !fail)
			{
			gchar *path;

			path = work->data;
			work = work->next;

			fail = file_util_delete_dir_empty_path(path, FALSE, 0);
			}

		work = ud->flist;
		while (work && !fail)
			{
			gchar *path;

			path = work->data;
			work = work->next;

			if (debug) printf("deltree unlink: %s\n", path);

			if (islink(path))
				{
				if (!unlink_file(path)) fail = g_strdup(path);
				}
			else
				{
				if (!file_util_unlink(path)) fail = g_strdup(path);
				}
			}

		if (!fail)
			{
			if (!rmdir_utf8(ud->source_path)) fail = g_strdup(ud->source_path);
			}

		if (fail)
			{
			gchar *text;

			text = g_strdup_printf(_("Unable to delete folder:\n\n%s"), ud->source_path);
			gd = file_util_warning_dialog(_("Delete failed"), text, GTK_STOCK_DIALOG_ERROR, NULL);
			g_free(text);

			if (strcmp(fail, ud->source_path) != 0)
				{
				pref_spacer(gd->vbox, PREF_PAD_GROUP);
				text = g_strdup_printf(_("Removal of folder contents failed at this file:\n\n%s"),
							fail);
				pref_label_new(gd->vbox, text);
				g_free(text);
				}

			g_free(fail);
			}
		}

	file_util_data_free(ud);
}

static GList *file_util_delete_dir_remaining_folders(GList *dlist)
{
	GList *rlist = NULL;

	while (dlist)
		{
		gchar *path;
		const gchar *name;

		path = dlist->data;
		dlist = dlist->next;

		name = filename_from_path(path);
		if (!name ||
		    (strcmp(name, THUMB_FOLDER_GLOBAL) != 0 &&
		     strcmp(name, THUMB_FOLDER_LOCAL) != 0 &&
		     strcmp(name, GQVIEW_CACHE_LOCAL_METADATA) != 0) )
			{
			rlist = g_list_prepend(rlist, path);
			}
		}

	return g_list_reverse(rlist);
}

void file_util_delete_dir(const gchar *path, GtkWidget *parent)
{
	GList *dlist = NULL;
	GList *flist = NULL;
	GList *rlist;

	if (!isdir(path)) return;

	if (islink(path))
		{
		UtilityData *ud;
		gchar *text;

		ud = g_new0(UtilityData, 1);
		ud->type = UTILITY_TYPE_DELETE_LINK;
		ud->source_path = g_strdup(path);
		ud->dlist = NULL;
		ud->flist = NULL;

		ud->gd = file_util_gen_dlg(_("Delete folder"), "GQview", "dlg_confirm",
					   parent, TRUE,
					   file_util_delete_dir_cancel_cb, ud);

		text = g_strdup_printf(_("This will delete the symbolic link:\n\n%s\n\n"
					 "The folder this link points to will not be deleted."),
					path);
		generic_dialog_add_message(ud->gd, GTK_STOCK_DIALOG_QUESTION,
					   _("Delete symbolic link to folder?"),
					   text);
		g_free(text);

		generic_dialog_add_button(ud->gd, GTK_STOCK_DELETE, NULL, file_util_delete_dir_ok_cb, TRUE);

		gtk_widget_show(ud->gd->dialog);

		return;
		}

	if (!access_file(path, W_OK | X_OK))
		{
		gchar *text;

		text = g_strdup_printf(_("Unable to remove folder %s\n"
					 "Permissions do not allow writing to the folder."), path);
		file_util_warning_dialog(_("Delete failed"), text, GTK_STOCK_DIALOG_ERROR, parent);
		g_free(text);

		return;
		}

	if (!path_list_lstat(path, &flist, &dlist))
		{
		gchar *text;

		text = g_strdup_printf(_("Unable to list contents of folder %s"), path);
		file_util_warning_dialog(_("Delete failed"), text, GTK_STOCK_DIALOG_ERROR, parent);
		g_free(text);

		return;
		}

	rlist = file_util_delete_dir_remaining_folders(dlist);
	if (rlist)
		{
		GenericDialog *gd;
		GtkWidget *box;
		gchar *text;

		gd = file_util_gen_dlg(_("Folder contains subfolders"), "GQview", "dlg_warning",
					parent, TRUE, NULL, NULL);
		generic_dialog_add_button(gd, GTK_STOCK_CLOSE, NULL, NULL, TRUE);

		text = g_strdup_printf(_("Unable to delete the folder:\n\n%s\n\n"
					 "This folder contains subfolders which must be moved before it can be deleted."),
					path);
		box = generic_dialog_add_message(gd, GTK_STOCK_DIALOG_WARNING,
						 _("Folder contains subfolders"),
						 text);
		g_free(text);

		box = pref_group_new(box, TRUE, _("Subfolders:"), GTK_ORIENTATION_VERTICAL);

		rlist = path_list_sort(rlist);
		file_util_dialog_add_list(box, rlist, FALSE);

		gtk_widget_show(gd->dialog);
		}
	else
		{
		UtilityData *ud;
		GtkWidget *box;
		GtkWidget *view;
		GtkTreeSelection *selection;
		gchar *text;

		ud = g_new0(UtilityData, 1);
		ud->type = UTILITY_TYPE_DELETE_FOLDER;
		ud->source_path = g_strdup(path);
		ud->dlist = dlist;
		dlist = NULL;
		ud->flist = path_list_sort(flist);
		flist = NULL;

		ud->gd = file_util_gen_dlg(_("Delete folder"), "GQview", "dlg_confirm",
					   parent, TRUE, file_util_delete_dir_cancel_cb, ud);
		generic_dialog_add_button(ud->gd, GTK_STOCK_DELETE, NULL, file_util_delete_dir_ok_cb, TRUE);

		text = g_strdup_printf(_("This will delete the folder:\n\n%s\n\n"
					 "The contents of this folder will also be deleted."),
					path);
		box = generic_dialog_add_message(ud->gd, GTK_STOCK_DIALOG_QUESTION,
						 _("Delete folder?"),
						 text);
		g_free(text);

		box = pref_group_new(box, TRUE, _("Contents:"), GTK_ORIENTATION_HORIZONTAL);

		view = file_util_dialog_add_list(box, ud->flist, FALSE);
		selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(view));
		gtk_tree_selection_set_mode(selection, GTK_SELECTION_SINGLE);
		gtk_tree_selection_set_select_function(selection, file_util_delete_dir_preview_cb, ud, NULL);

		generic_dialog_add_image(ud->gd, box, NULL, NULL, NULL, NULL, FALSE);

		box_append_safe_delete_status(ud->gd);

		gtk_widget_show(ud->gd->dialog);
		}

	g_list_free(rlist);
	path_list_free(dlist);
	path_list_free(flist);
}

