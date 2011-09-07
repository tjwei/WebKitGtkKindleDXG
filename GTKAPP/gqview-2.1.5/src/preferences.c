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
#include "preferences.h"

#include "cache_maint.h"
#include "editors.h"
#include "filelist.h"
#include "fullscreen.h"
#include "image.h"
#include "img-view.h"
#include "layout_config.h"
#include "layout_util.h"
#include "pixbuf_util.h"
#include "slideshow.h"
#include "utilops.h"
#include "ui_fileops.h"
#include "ui_misc.h"
#include "ui_tabcomp.h"
#include "ui_utildlg.h"

#include <math.h>


#define EDITOR_NAME_MAX_LENGTH 32
#define EDITOR_COMMAND_MAX_LENGTH 1024


typedef struct _ThumbSize ThumbSize;
struct _ThumbSize
{
	gint w;
	gint h;
};

static ThumbSize thumb_size_list[] =
{
	{ 24, 24 },
	{ 32, 32 },
	{ 48, 48 },
	{ 64, 64 },
	{ 96, 72 },
	{ 96, 96 },
	{ 128, 96 },
	{ 128, 128 },
	{ 160, 120 },
	{ 160, 160 },
	{ 192, 144 },
	{ 192, 192 },
	{ 256, 192 },
	{ 256, 256 }
};

enum {
	FE_ENABLE,
	FE_EXTENSION,
	FE_DESCRIPTION
};

/* config memory values */
static gint startup_path_enable_c;
static gint confirm_delete_c;
static gint enable_delete_key_c;
static gint safe_delete_enable_c;
static gint safe_delete_size_c;
static gint restore_tool_c;
static gint save_window_positions_c;
static gint zoom_mode_c;
static gint two_pass_zoom_c;
static gint fit_window_c;
static gint limit_window_size_c;
static gint zoom_to_fit_expands_c;
static gint max_window_size_c;
static gint progressive_key_scrolling_c;
static gint thumb_max_width_c;
static gint thumb_max_height_c;
static gint enable_thumb_caching_c;
static gint enable_thumb_dirs_c;
static gint thumbnail_fast_c;
#if 0
static gint use_xvpics_thumbnails_c;
#endif
static gint thumbnail_spec_standard_c;
static gint enable_metadata_dirs_c;
static gint show_dot_files_c;
static gint file_filter_disable_c;
static gint file_sort_case_sensitive_c;
static gint slideshow_delay_c;
static gint slideshow_random_c;
static gint slideshow_repeat_c;

static gint mousewheel_scrolls_c;

static gint enable_in_place_rename_c;

static gint collection_rectangular_selection_c;

static gint tile_cache_max_c;

static gint thumbnail_quality_c;
static gint zoom_quality_c;

static gint zoom_increment_c;

static gint enable_read_ahead_c;

static gint black_window_background_c;

static gint fullscreen_screen_c;
static gint fullscreen_clean_flip_c;
static gint fullscreen_disable_saver_c;
static gint fullscreen_above_c;

static gint dupe_custom_threshold_c;

static GtkWidget *configwindow = NULL;
static GtkWidget *startup_path_entry;
static GtkListStore *filter_store = NULL;
static GtkWidget *editor_name_entry[GQVIEW_EDITOR_SLOTS];
static GtkWidget *editor_command_entry[GQVIEW_EDITOR_SLOTS];

static GtkWidget *layout_widget;

static GtkWidget *safe_delete_path_entry;

static gint tree_descend_subdirs_c;

static gint update_on_time_change_c;
static gint exif_rotate_enable_c;

static GtkWidget *color_profile_input_file_entry[COLOR_PROFILE_INPUTS];
static GtkWidget *color_profile_input_name_entry[COLOR_PROFILE_INPUTS];
static GtkWidget *color_profile_screen_file_entry;


/*
 *-----------------------------------------------------------------------------
 * option widget callbacks (private)
 *-----------------------------------------------------------------------------
 */ 

static void startup_path_set_current(GtkWidget *widget, gpointer data)
{
	gtk_entry_set_text(GTK_ENTRY(startup_path_entry), layout_get_path(NULL));
}

static void zoom_mode_original_cb(GtkWidget *widget, gpointer data)
{
	if (GTK_TOGGLE_BUTTON (widget)->active)
		zoom_mode_c = ZOOM_RESET_ORIGINAL;
}

static void zoom_mode_fit_cb(GtkWidget *widget, gpointer data)
{
	if (GTK_TOGGLE_BUTTON (widget)->active)
		zoom_mode_c = ZOOM_RESET_FIT_WINDOW;
}

static void zoom_mode_none_cb(GtkWidget *widget, gpointer data)
{
	if (GTK_TOGGLE_BUTTON (widget)->active)
		zoom_mode_c = ZOOM_RESET_NONE;
}

static void zoom_increment_cb(GtkWidget *spin, gpointer data)
{
	zoom_increment_c = (gint)(gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin)) * 10.0 + 0.01);
}

static void slideshow_delay_cb(GtkWidget *spin, gpointer data)
{
	slideshow_delay_c = (gint)(gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin)) *
				   (double)SLIDESHOW_SUBSECOND_PRECISION + 0.01);
}

/*
 *-----------------------------------------------------------------------------
 * sync progam to config window routine (private)
 *-----------------------------------------------------------------------------
 */ 

static void config_window_apply(void)
{
	const gchar *buf;
	gchar *l_conf;
	gint new_style;
	gint i;
	gint refresh = FALSE;

	for(i = 0; i < GQVIEW_EDITOR_SLOTS; i++)
		{
		g_free(editor_name[i]);
		editor_name[i] = NULL;
		buf = gtk_entry_get_text(GTK_ENTRY(editor_name_entry[i]));
		if (buf && strlen(buf) > 0) editor_name[i] = g_strdup(buf);

		g_free(editor_command[i]);
		editor_command[i] = NULL;
		buf = gtk_entry_get_text(GTK_ENTRY(editor_command_entry[i]));
		if (buf && strlen(buf) > 0) editor_command[i] = g_strdup(buf);
		}
	layout_edit_update_all();

	g_free(startup_path);
	startup_path = NULL;
	buf = gtk_entry_get_text(GTK_ENTRY(startup_path_entry));
	if (buf && strlen(buf) > 0) startup_path = remove_trailing_slash(buf);

	g_free(safe_delete_path);
	safe_delete_path = NULL;
	buf = gtk_entry_get_text(GTK_ENTRY(safe_delete_path_entry));
	if (buf && strlen(buf) > 0) safe_delete_path = remove_trailing_slash(buf);

	if (show_dot_files != show_dot_files_c) refresh = TRUE;
	if (file_sort_case_sensitive != file_sort_case_sensitive_c) refresh = TRUE;
	if (file_filter_disable != file_filter_disable_c) refresh = TRUE;

	startup_path_enable = startup_path_enable_c;
	confirm_delete = confirm_delete_c;
	enable_delete_key = enable_delete_key_c;
	safe_delete_enable = safe_delete_enable_c;
	safe_delete_size = safe_delete_size_c;
	restore_tool = restore_tool_c;
	save_window_positions = save_window_positions_c;
	zoom_mode = zoom_mode_c;
	two_pass_zoom = two_pass_zoom_c;
	fit_window = fit_window_c;
	limit_window_size = limit_window_size_c;
	zoom_to_fit_expands = zoom_to_fit_expands_c;
	max_window_size = max_window_size_c;
	progressive_key_scrolling = progressive_key_scrolling_c;
	thumb_max_width = thumb_max_width_c;
	thumb_max_height = thumb_max_height_c;
	enable_thumb_caching = enable_thumb_caching_c;
	enable_thumb_dirs = enable_thumb_dirs_c;
	thumbnail_fast = thumbnail_fast_c;
#if 0
	use_xvpics_thumbnails = use_xvpics_thumbnails_c;
#endif
	thumbnail_spec_standard = thumbnail_spec_standard_c;
	enable_metadata_dirs = enable_metadata_dirs_c;
	show_dot_files = show_dot_files_c;
	file_sort_case_sensitive = file_sort_case_sensitive_c;
	file_filter_disable = file_filter_disable_c;

	slideshow_random = slideshow_random_c;
	slideshow_repeat = slideshow_repeat_c;
	slideshow_delay = slideshow_delay_c;

	mousewheel_scrolls = mousewheel_scrolls_c;

	enable_in_place_rename = enable_in_place_rename_c;

	collection_rectangular_selection = collection_rectangular_selection_c;

	tile_cache_max = tile_cache_max_c;

	thumbnail_quality = thumbnail_quality_c;
	zoom_quality = zoom_quality_c;

	zoom_increment = zoom_increment_c;

	enable_read_ahead = enable_read_ahead_c;

	if (black_window_background != black_window_background_c)
		{
		black_window_background = black_window_background_c;

		layout_colors_update();
		view_window_colors_update();
		}

	fullscreen_screen = fullscreen_screen_c;
	fullscreen_clean_flip = fullscreen_clean_flip_c;
	fullscreen_disable_saver = fullscreen_disable_saver_c;
	fullscreen_above = fullscreen_above_c;

	update_on_time_change = update_on_time_change_c;
	exif_rotate_enable = exif_rotate_enable_c;

	dupe_custom_threshold = dupe_custom_threshold_c;

	tree_descend_subdirs = tree_descend_subdirs_c;

#ifdef HAVE_LCMS
	for (i = 0; i < COLOR_PROFILE_INPUTS; i++)
		{
		g_free(color_profile_input_name[i]);
		color_profile_input_name[i] = NULL;
		buf = gtk_entry_get_text(GTK_ENTRY(color_profile_input_name_entry[i]));
		if (buf && strlen(buf) > 0) color_profile_input_name[i] = g_strdup(buf);

		g_free(color_profile_input_file[i]);
		color_profile_input_file[i] = NULL;
		buf = gtk_entry_get_text(GTK_ENTRY(color_profile_input_file_entry[i]));
		if (buf && strlen(buf) > 0) color_profile_input_file[i] = g_strdup(buf);
		}
	g_free(color_profile_screen_file);
	color_profile_screen_file = NULL;
	buf = gtk_entry_get_text(GTK_ENTRY(color_profile_screen_file_entry));
	if (buf && strlen(buf) > 0) color_profile_screen_file = g_strdup(buf);
#endif

	l_conf = layout_config_get(layout_widget, &new_style);

	if (new_style != layout_style ||
	    (l_conf == NULL) != (layout_order == NULL) ||
	    !layout_order ||
	    strcmp(buf, layout_order) != 0)
		{
		if (refresh) filter_rebuild();
		refresh = FALSE;

		g_free(layout_order);
		layout_order = l_conf;
		l_conf = NULL;

		layout_style = new_style;

		layout_styles_update();
		}

	g_free(l_conf);

	image_options_sync();

	if (refresh)
		{
		filter_rebuild();
		layout_refresh(NULL);
		}
}

/*
 *-----------------------------------------------------------------------------
 * config window main button callbacks (private)
 *-----------------------------------------------------------------------------
 */ 

static void config_window_close_cb(GtkWidget *widget, gpointer data)
{
	gtk_widget_destroy(configwindow);
	configwindow = NULL;
	filter_store = NULL;
}

static gint config_window_delete(GtkWidget *w, GdkEventAny *event, gpointer data)
{
	config_window_close_cb(NULL, NULL);
	return TRUE;
}

static void config_window_ok_cb(GtkWidget *widget, gpointer data)
{
	config_window_apply();
	config_window_close_cb(NULL, NULL);
}

static void config_window_apply_cb(GtkWidget *widget, gpointer data)
{
	config_window_apply();
}

/*
 *-----------------------------------------------------------------------------
 * config window setup (private)
 *-----------------------------------------------------------------------------
 */ 

static void quality_menu_cb(GtkWidget *combo, gpointer data)
{
	gint *option = data;

	switch (gtk_combo_box_get_active(GTK_COMBO_BOX(combo)))
		{
		case 0:
		default:
			*option = GDK_INTERP_NEAREST;
			break;
		case 1:
			*option = GDK_INTERP_TILES;
			break;
		case 2:
			*option = GDK_INTERP_BILINEAR;
			break;
		case 3:
			*option = GDK_INTERP_HYPER;
			break;
		}
}

static void add_quality_menu(GtkWidget *table, gint column, gint row, const gchar *text,
			     gint option, gint *option_c)
{
	GtkWidget *combo;
	gint current = 0;

	*option_c = option;

	pref_table_label(table, column, row, text, 0.0);

	combo = gtk_combo_box_new_text();

	gtk_combo_box_append_text(GTK_COMBO_BOX(combo), _("Nearest (worst, but fastest)"));
	if (option == GDK_INTERP_NEAREST) current = 0;
	gtk_combo_box_append_text(GTK_COMBO_BOX(combo), _("Tiles"));
	if (option == GDK_INTERP_TILES) current = 1;
	gtk_combo_box_append_text(GTK_COMBO_BOX(combo), _("Bilinear"));
	if (option == GDK_INTERP_BILINEAR) current = 2;
	gtk_combo_box_append_text(GTK_COMBO_BOX(combo), _("Hyper (best, but slowest)"));
	if (option == GDK_INTERP_HYPER) current = 3;

	gtk_combo_box_set_active(GTK_COMBO_BOX(combo), current);

	g_signal_connect(G_OBJECT(combo), "changed",
			 G_CALLBACK(quality_menu_cb), option_c);

	gtk_table_attach(GTK_TABLE(table), combo, column + 1, column + 2, row, row + 1,
			 GTK_EXPAND | GTK_FILL, 0, 0, 0);
	gtk_widget_show(combo);
}

#if 0
static void add_dither_menu(gint option, gint *option_c, gchar *text, GtkWidget *box)
{
	GtkWidget *hbox;
	GtkWidget *omenu;
	GtkWidget *menu;

	*option_c = option;

	hbox = pref_box_new(box, FALSE, GTK_ORIENTATION_HORIZONTAL, PREF_PAD_SPACE);
	pref_label_new(hbox, text);

	omenu = gtk_option_menu_new();
	menu = gtk_menu_new();

	add_menu_item(menu, _("None"), option_c, (gint)GDK_RGB_DITHER_NONE);
	add_menu_item(menu, _("Normal"), option_c, (gint)GDK_RGB_DITHER_NORMAL);
	add_menu_item(menu, _("Best"), option_c, (gint)GDK_RGB_DITHER_MAX);

	gtk_option_menu_set_menu(GTK_OPTION_MENU(omenu), menu);
	gtk_option_menu_set_history(GTK_OPTION_MENU(omenu), *option_c);

	gtk_box_pack_start(GTK_BOX(hbox), omenu, FALSE, FALSE, 0);
	gtk_widget_show(omenu);
}
#endif

static void thumb_size_menu_cb(GtkWidget *combo, gpointer data)
{
	gint n;

	n = gtk_combo_box_get_active(GTK_COMBO_BOX(combo));

	if (n >= 0 && n < sizeof(thumb_size_list) / sizeof(ThumbSize))
		{
		thumb_max_width_c = thumb_size_list[n].w;
		thumb_max_height_c = thumb_size_list[n].h;
		}
	else if (n > 0)
		{
		thumb_max_width_c = thumb_max_width;
		thumb_max_height_c = thumb_max_height;
		}
}

static void add_thumb_size_menu(GtkWidget *table, gint column, gint row, gchar *text)
{
	GtkWidget *combo;
	gint current;
	gint last_w, last_h;
	gint i;
	gint c;

	thumb_max_width_c = thumb_max_width;
	thumb_max_height_c = thumb_max_height;

	pref_table_label(table, column, row, text, 0.0);

	combo = gtk_combo_box_new_text();

	last_w = last_h = 0;
	current = -1;
	i = 0;
	c = TRUE;
	while (c)
		{
		gint w, h;

		w = thumb_size_list[i].w;
		h = thumb_size_list[i].h;

		if ( w > 0 && h > 0)
			{
			gchar *buf;

			buf = g_strdup_printf("%d x %d", w, h);
			gtk_combo_box_append_text(GTK_COMBO_BOX(combo), buf);
			g_free(buf);

			if (w == thumb_max_width && h == thumb_max_height) current = i;

			last_w = w;
			last_h = h;
			}
		else
			{
			c = FALSE;
			}
		i++;
		}

	if (current == -1)
		{
		gchar *buf;

		buf = g_strdup_printf("%s %d x %d", _("Custom"), thumb_max_width, thumb_max_height);
		gtk_combo_box_append_text(GTK_COMBO_BOX(combo), buf);
		g_free(buf);

		current = i - 1;
		}

	gtk_combo_box_set_active(GTK_COMBO_BOX(combo), current);
	g_signal_connect(G_OBJECT(combo), "changed",
			 G_CALLBACK(thumb_size_menu_cb), NULL);

	gtk_table_attach(GTK_TABLE(table), combo, column + 1, column + 2, row, row + 1,
			 GTK_EXPAND | GTK_FILL, 0, 0, 0);
	gtk_widget_show(combo);
}

static void filter_store_populate(void)
{
	GList *work;

	if (!filter_store) return;

	gtk_list_store_clear(filter_store);

	work = filter_get_list();
	while (work)
		{
		FilterEntry *fe;
		GtkTreeIter iter;

		fe = work->data;
		work = work->next;

		gtk_list_store_append(filter_store, &iter);
		gtk_list_store_set(filter_store, &iter, 0, fe, -1);
		}
}

static void filter_store_ext_edit_cb(GtkCellRendererText *cell, gchar *path_str,
				     gchar *new_text, gpointer data)
{
	GtkWidget *model = data;
	FilterEntry *fe = data;
	GtkTreePath *tpath;
	GtkTreeIter iter;

	if (!new_text || strlen(new_text) < 1) return;

	tpath = gtk_tree_path_new_from_string(path_str);
	gtk_tree_model_get_iter(GTK_TREE_MODEL(model), &iter, tpath);
	gtk_tree_model_get(GTK_TREE_MODEL(model), &iter, 0, &fe, -1);

	g_free(fe->extensions);
	fe->extensions = g_strdup(new_text);

	gtk_tree_path_free(tpath);
	filter_rebuild();
}

static void filter_store_desc_edit_cb(GtkCellRendererText *cell, gchar *path_str,
				      gchar *new_text, gpointer data)
{
	GtkWidget *model = data;
	FilterEntry *fe;
	GtkTreePath *tpath;
	GtkTreeIter iter;

	if (!new_text || strlen(new_text) < 1) return;

	tpath = gtk_tree_path_new_from_string(path_str);
	gtk_tree_model_get_iter(GTK_TREE_MODEL(model), &iter, tpath);
	gtk_tree_model_get(GTK_TREE_MODEL(model), &iter, 0, &fe, -1);

	g_free(fe->description);
	fe->description = g_strdup(new_text);

	gtk_tree_path_free(tpath);
}

static void filter_store_enable_cb(GtkCellRendererToggle *renderer,
				   gchar *path_str, gpointer data)
{
	GtkWidget *model = data;
	FilterEntry *fe;
	GtkTreePath *tpath;
	GtkTreeIter iter;

	tpath = gtk_tree_path_new_from_string(path_str);
	gtk_tree_model_get_iter(GTK_TREE_MODEL(model), &iter, tpath);
	gtk_tree_model_get(GTK_TREE_MODEL(model), &iter, 0, &fe, -1);

	fe->enabled = !fe->enabled;

	gtk_tree_path_free(tpath);
	filter_rebuild();
}

static void filter_set_func(GtkTreeViewColumn *tree_column, GtkCellRenderer *cell,
			    GtkTreeModel *tree_model, GtkTreeIter *iter, gpointer data)
{
	FilterEntry *fe;

	gtk_tree_model_get(tree_model, iter, 0, &fe, -1);

	switch(GPOINTER_TO_INT(data))
		{
		case FE_ENABLE:
			g_object_set(GTK_CELL_RENDERER(cell),
				     "active", fe->enabled, NULL);
			break;
		case FE_EXTENSION:
			g_object_set(GTK_CELL_RENDERER(cell),
				     "text", fe->extensions, NULL);
			break;
		case FE_DESCRIPTION:
			g_object_set(GTK_CELL_RENDERER(cell),
				     "text", fe->description, NULL);
			break;
		}
}

static void filter_add_cb(GtkWidget *widget, gpointer data)
{
	filter_add_unique("description", ".new", TRUE);
	filter_store_populate();

	/* FIXME: implement the scroll to/select row stuff for tree view */
}

static void filter_remove_cb(GtkWidget *widget, gpointer data)
{
	GtkWidget *filter_view = data;
	GtkTreeSelection *selection;
	GtkTreeIter iter;
	FilterEntry *fe;

	if (!filter_store) return;
       	selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(filter_view));
	if (!gtk_tree_selection_get_selected(selection, NULL, &iter)) return;
	gtk_tree_model_get(GTK_TREE_MODEL(filter_store), &iter, 0, &fe, -1);
	if (!fe) return;

	filter_remove_entry(fe);
	filter_rebuild();
	filter_store_populate();
}

static void filter_default_ok_cb(GenericDialog *gd, gpointer data)
{
	filter_reset();
	filter_add_defaults();
	filter_rebuild();
	filter_store_populate();
}

static void dummy_cancel_cb(GenericDialog *gd, gpointer data)
{
	/* no op, only so cancel button appears */
}

static void filter_default_cb(GtkWidget *widget, gpointer data)
{
	GenericDialog *gd;

	gd = generic_dialog_new(_("Reset filters"),
				"GQview", "reset_filter", widget, TRUE,
				dummy_cancel_cb, NULL);
	generic_dialog_add_message(gd, GTK_STOCK_DIALOG_QUESTION, _("Reset filters"),
				   _("This will reset the file filters to the defaults.\nContinue?"));
	generic_dialog_add_button(gd, GTK_STOCK_OK, NULL, filter_default_ok_cb, TRUE);
	gtk_widget_show(gd->dialog);
}

static void filter_disable_cb(GtkWidget* widget, gpointer data)
{
	GtkWidget *frame = data;

	gtk_widget_set_sensitive(frame,
				 !gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget)));
}

static void editor_default_ok_cb(GenericDialog *gd, gpointer data)
{
	gint i;

	editor_reset_defaults();
	if (!configwindow) return;

	for (i = 0; i < GQVIEW_EDITOR_SLOTS; i++)
		{
		gtk_entry_set_text(GTK_ENTRY(editor_name_entry[i]),
				   (editor_name[i]) ? editor_name[i] : "");
		gtk_entry_set_text(GTK_ENTRY(editor_command_entry[i]),
				   (editor_command[i]) ? editor_command[i] : "");
		}
}

static void editor_default_cb(GtkWidget *widget, gpointer data)
{
	GenericDialog *gd;

	gd = generic_dialog_new(_("Reset editors"),
				"GQview", "reset_filter", widget, TRUE,
				dummy_cancel_cb, NULL);
	generic_dialog_add_message(gd, GTK_STOCK_DIALOG_QUESTION, _("Reset editors"),
				   _("This will reset the edit commands to the defaults.\nContinue?"));
	generic_dialog_add_button(gd, GTK_STOCK_OK, NULL, editor_default_ok_cb, TRUE);
	gtk_widget_show(gd->dialog);
}

static void editor_help_cb(GtkWidget *widget, gpointer data)
{
	help_window_show("editors");
}

static void safe_delete_view_cb(GtkWidget* widget, gpointer data)
{
	layout_set_path(NULL, gtk_entry_get_text(GTK_ENTRY(safe_delete_path_entry)));
}

static void safe_delete_clear_ok_cb(GenericDialog *gd, gpointer data)
{
	file_util_trash_clear();
}

static void safe_delete_clear_cb(GtkWidget* widget, gpointer data)
{
	GenericDialog *gd;
	GtkWidget *entry;
	gd = generic_dialog_new(_("Clear trash"),
				"GQview", "clear_trash", widget, TRUE,
				dummy_cancel_cb, NULL);
	generic_dialog_add_message(gd, GTK_STOCK_DIALOG_QUESTION, _("Clear trash"),
				    _("This will remove the trash contents."));
	generic_dialog_add_button(gd, GTK_STOCK_OK, NULL, safe_delete_clear_ok_cb, TRUE);
	entry = gtk_entry_new();
	GTK_WIDGET_UNSET_FLAGS(entry, GTK_CAN_FOCUS);
	gtk_editable_set_editable(GTK_EDITABLE(entry), FALSE);
	if (safe_delete_path) gtk_entry_set_text(GTK_ENTRY(entry), safe_delete_path);
	gtk_box_pack_start(GTK_BOX(gd->vbox), entry, FALSE, FALSE, 0);
	gtk_widget_show(entry);
	gtk_widget_show(gd->dialog);
}

static void config_window_create(void)
{
	GtkWidget *win_vbox;
	GtkWidget *hbox;
	GtkWidget *notebook;
	GtkWidget *frame;
	GtkWidget *label;
	GtkWidget *vbox;
	GtkWidget *group;
	GtkWidget *subgroup;
	GtkWidget *button;
	GtkWidget *tabcomp;
	GtkWidget *ct_button;
	GtkWidget *table;
	GtkWidget *spin;
	GtkWidget *scrolled;
	GtkWidget *viewport;
	GtkWidget *filter_view;
	GtkCellRenderer *renderer;
	GtkTreeSelection *selection;
	GtkTreeViewColumn *column;
	gint i;

	configwindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_type_hint(GTK_WINDOW(configwindow), GDK_WINDOW_TYPE_HINT_DIALOG);
	g_signal_connect(G_OBJECT (configwindow), "delete_event",
			 G_CALLBACK(config_window_delete), NULL);
	gtk_window_set_resizable(GTK_WINDOW(configwindow), FALSE);
	gtk_window_set_title(GTK_WINDOW(configwindow), _("GQview Preferences"));
	gtk_window_set_wmclass(GTK_WINDOW(configwindow), "config", "GQview");
	gtk_container_set_border_width(GTK_CONTAINER(configwindow), PREF_PAD_BORDER);

	window_set_icon(configwindow, PIXBUF_INLINE_ICON_CONFIG, NULL);

	win_vbox = gtk_vbox_new(FALSE, PREF_PAD_SPACE);
	gtk_container_add(GTK_CONTAINER(configwindow), win_vbox);
	gtk_widget_show(win_vbox);

	hbox = gtk_hbutton_box_new();
	gtk_button_box_set_layout(GTK_BUTTON_BOX(hbox), GTK_BUTTONBOX_END);
	gtk_box_set_spacing(GTK_BOX(hbox), PREF_PAD_BUTTON_GAP);
	gtk_box_pack_end(GTK_BOX(win_vbox), hbox, FALSE, FALSE, 0);
	gtk_widget_show(hbox);

	button = pref_button_new(NULL, GTK_STOCK_OK, NULL, FALSE,
				 G_CALLBACK(config_window_ok_cb), NULL);
	gtk_container_add(GTK_CONTAINER(hbox), button);
	GTK_WIDGET_SET_FLAGS(button, GTK_CAN_DEFAULT);
	gtk_widget_grab_default(button);
	gtk_widget_show(button);

	ct_button = button;

	button = pref_button_new(NULL, GTK_STOCK_APPLY, NULL, FALSE,
				 G_CALLBACK(config_window_apply_cb), NULL);
	gtk_container_add(GTK_CONTAINER(hbox), button);
	GTK_WIDGET_SET_FLAGS(button, GTK_CAN_DEFAULT);
	gtk_widget_show(button);

	button = pref_button_new(NULL, GTK_STOCK_CANCEL, NULL, FALSE,
				 G_CALLBACK(config_window_close_cb), NULL);
	gtk_container_add(GTK_CONTAINER(hbox), button);
	GTK_WIDGET_SET_FLAGS(button, GTK_CAN_DEFAULT);
	gtk_widget_show(button);

	if (!generic_dialog_get_alternative_button_order(configwindow))
		{
		gtk_box_reorder_child(GTK_BOX(hbox), ct_button, -1);
		}

	notebook = gtk_notebook_new();
	gtk_notebook_set_tab_pos (GTK_NOTEBOOK(notebook), GTK_POS_TOP);
	gtk_box_pack_start(GTK_BOX(win_vbox), notebook, TRUE, TRUE, 0);

	/* general options tab */

	vbox = gtk_vbox_new(FALSE, 0);
	gtk_container_set_border_width(GTK_CONTAINER(vbox), PREF_PAD_BORDER);
	gtk_widget_show(vbox);
	label = gtk_label_new(_("General"));
	gtk_notebook_append_page (GTK_NOTEBOOK(notebook), vbox, label);

	group = pref_group_new(vbox, FALSE, _("Startup"), GTK_ORIENTATION_VERTICAL);

	button = pref_checkbox_new_int(group, _("Change to folder:"),
				       startup_path_enable, &startup_path_enable_c);

	hbox = pref_box_new(group, FALSE, GTK_ORIENTATION_HORIZONTAL, PREF_PAD_SPACE);
	pref_checkbox_link_sensitivity(button, hbox);

	tabcomp = tab_completion_new(&startup_path_entry, startup_path, NULL, NULL);
	tab_completion_add_select_button(startup_path_entry, NULL, TRUE);
	gtk_box_pack_start(GTK_BOX(hbox), tabcomp, TRUE, TRUE, 0);
	gtk_widget_show(tabcomp);

	button = pref_button_new(hbox, NULL, _("Use current"), FALSE,
				 G_CALLBACK(startup_path_set_current), NULL);

	group = pref_group_new(vbox, FALSE, _("Thumbnails"), GTK_ORIENTATION_VERTICAL);

	table = pref_table_new(group, 2, 2, FALSE, FALSE);
	add_thumb_size_menu(table, 0, 0, _("Size:"));
	add_quality_menu(table, 0, 1, _("Quality:"), thumbnail_quality, &thumbnail_quality_c);

	ct_button = pref_checkbox_new_int(group, _("Cache thumbnails"),
					  enable_thumb_caching, &enable_thumb_caching_c);

	subgroup = pref_box_new(group, FALSE, GTK_ORIENTATION_VERTICAL, PREF_PAD_GAP);
	pref_checkbox_link_sensitivity(ct_button, subgroup);

	button = pref_checkbox_new_int(subgroup, _("Use shared thumbnail cache"),
				       thumbnail_spec_standard, &thumbnail_spec_standard_c);

	subgroup = pref_box_new(subgroup, FALSE, GTK_ORIENTATION_VERTICAL, PREF_PAD_GAP);
	pref_checkbox_link_sensitivity_swap(button, subgroup);

	pref_checkbox_new_int(subgroup, _("Cache thumbnails into .thumbnails"),
			      enable_thumb_dirs, &enable_thumb_dirs_c);

#if 0
	pref_checkbox_new_int(subgroup, _("Use xvpics thumbnails when found (read only)"),
			      use_xvpics_thumbnails, &use_xvpics_thumbnails_c);
#endif

	pref_checkbox_new_int(group, _("Faster jpeg thumbnailing (may reduce quality)"),
			      thumbnail_fast, &thumbnail_fast_c);

	group = pref_group_new(vbox, FALSE, _("Slide show"), GTK_ORIENTATION_VERTICAL);

	slideshow_delay_c = slideshow_delay;
	spin = pref_spin_new(group, _("Delay between image change:"), _("seconds"),
			     SLIDESHOW_MIN_SECONDS, SLIDESHOW_MAX_SECONDS, 1.0, 1,
			     slideshow_delay ? (double)slideshow_delay / SLIDESHOW_SUBSECOND_PRECISION : 10.0,
			     G_CALLBACK(slideshow_delay_cb), NULL);
	gtk_spin_button_set_update_policy(GTK_SPIN_BUTTON(spin), GTK_UPDATE_ALWAYS);

	pref_checkbox_new_int(group, _("Random"), slideshow_random, &slideshow_random_c);
	pref_checkbox_new_int(group, _("Repeat"), slideshow_repeat, &slideshow_repeat_c);

	/* image tab */

	vbox = gtk_vbox_new(FALSE, 0);
	gtk_container_set_border_width(GTK_CONTAINER(vbox), PREF_PAD_BORDER);
	gtk_widget_show(vbox);
	label = gtk_label_new(_("Image"));
	gtk_notebook_append_page (GTK_NOTEBOOK (notebook), vbox, label);

	group = pref_group_new(vbox, FALSE, _("Zoom"), GTK_ORIENTATION_VERTICAL);

#if 0
	add_dither_menu(dither_quality, &dither_quality_c, _("Dithering method:"), group);
#endif
	table = pref_table_new(group, 2, 1, FALSE, FALSE);
	add_quality_menu(table, 0, 0, _("Quality:"), zoom_quality, &zoom_quality_c);

	pref_checkbox_new_int(group, _("Two pass zooming"),
			      two_pass_zoom, &two_pass_zoom_c);

	pref_checkbox_new_int(group, _("Allow enlargement of image for zoom to fit"),
			      zoom_to_fit_expands, &zoom_to_fit_expands_c);

	zoom_increment_c = zoom_increment;
	spin = pref_spin_new(group, _("Zoom increment:"), NULL,
			     0.1, 4.0, 1.0, 1, (double)zoom_increment / 10.0,
			     G_CALLBACK(zoom_increment_cb), NULL);
	gtk_spin_button_set_update_policy(GTK_SPIN_BUTTON(spin), GTK_UPDATE_ALWAYS);

	group = pref_group_new(vbox, FALSE, _("When new image is selected:"), GTK_ORIENTATION_VERTICAL);

	zoom_mode_c = zoom_mode;
	button = pref_radiobutton_new(group, NULL, _("Zoom to original size"),
				      (zoom_mode == ZOOM_RESET_ORIGINAL),
				      G_CALLBACK(zoom_mode_original_cb), NULL);
	button = pref_radiobutton_new(group, button, _("Fit image to window"),
				      (zoom_mode == ZOOM_RESET_FIT_WINDOW),
				      G_CALLBACK(zoom_mode_fit_cb), NULL);
	button = pref_radiobutton_new(group, button, _("Leave Zoom at previous setting"),
				      (zoom_mode == ZOOM_RESET_NONE),
				      G_CALLBACK(zoom_mode_none_cb), NULL);

	group = pref_group_new(vbox, FALSE, _("Appearance"), GTK_ORIENTATION_VERTICAL);

	pref_checkbox_new_int(group, _("Black background"),
			      black_window_background, &black_window_background_c);

	group = pref_group_new(vbox, FALSE, _("Convenience"), GTK_ORIENTATION_VERTICAL);

	pref_checkbox_new_int(group, _("Refresh on file change"),
			      update_on_time_change, &update_on_time_change_c);
	pref_checkbox_new_int(group, _("Preload next image"),
			      enable_read_ahead, &enable_read_ahead_c);
	pref_checkbox_new_int(group, _("Auto rotate image using Exif information"),
			      exif_rotate_enable, &exif_rotate_enable_c);


	/* window tab */

	vbox = gtk_vbox_new(FALSE, 0);
	gtk_container_set_border_width(GTK_CONTAINER(vbox), PREF_PAD_BORDER);
	gtk_widget_show(vbox);
	label = gtk_label_new(_("Windows"));
	gtk_notebook_append_page(GTK_NOTEBOOK(notebook), vbox, label);

	group = pref_group_new(vbox, FALSE, _("State"), GTK_ORIENTATION_VERTICAL);

	pref_checkbox_new_int(group, _("Remember window positions"),
			      save_window_positions, &save_window_positions_c);
	pref_checkbox_new_int(group, _("Remember tool state (float/hidden)"),
			      restore_tool, &restore_tool_c);

	group = pref_group_new(vbox, FALSE, _("Size"), GTK_ORIENTATION_VERTICAL);

	pref_checkbox_new_int(group, _("Fit window to image when tools are hidden/floating"),
			      fit_window, &fit_window_c);

	hbox = pref_box_new(group, FALSE, GTK_ORIENTATION_HORIZONTAL, PREF_PAD_SPACE);
	ct_button = pref_checkbox_new_int(hbox, _("Limit size when auto-sizing window (%):"),
					  limit_window_size, &limit_window_size_c);
	spin = pref_spin_new_int(hbox, NULL, NULL,
				 10, 150, 1,
				 max_window_size, &max_window_size_c);
	pref_checkbox_link_sensitivity(ct_button, spin);

	group = pref_group_new(vbox, FALSE, _("Layout"), GTK_ORIENTATION_VERTICAL);

	layout_widget = layout_config_new();
	layout_config_set(layout_widget, layout_style, layout_order);
	gtk_box_pack_start(GTK_BOX(group), layout_widget, FALSE, FALSE, 0);
	gtk_widget_show(layout_widget);


	/* filtering tab */

	vbox = gtk_vbox_new(FALSE, 0);
	gtk_container_set_border_width(GTK_CONTAINER (vbox), PREF_PAD_BORDER);
	gtk_widget_show(vbox);
	label = gtk_label_new(_("Filtering"));
	gtk_notebook_append_page(GTK_NOTEBOOK(notebook), vbox, label);

	group = pref_box_new(vbox, FALSE, GTK_ORIENTATION_VERTICAL, PREF_PAD_GAP);

	pref_checkbox_new_int(group, _("Show entries that begin with a dot"),
			      show_dot_files, &show_dot_files_c);
	pref_checkbox_new_int(group, _("Case sensitive sort"),
			      file_sort_case_sensitive, &file_sort_case_sensitive_c);

	ct_button = pref_checkbox_new_int(group, _("Disable File Filtering"),
					  file_filter_disable, &file_filter_disable_c);

	group = pref_group_new(vbox, TRUE, _("File types"), GTK_ORIENTATION_VERTICAL);

	frame = pref_group_parent(group);
	g_signal_connect(G_OBJECT(ct_button), "toggled",
			 G_CALLBACK(filter_disable_cb), frame);
	gtk_widget_set_sensitive(frame, !file_filter_disable);

	scrolled = gtk_scrolled_window_new(NULL, NULL);
	gtk_scrolled_window_set_shadow_type(GTK_SCROLLED_WINDOW(scrolled), GTK_SHADOW_IN);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW (scrolled), GTK_POLICY_AUTOMATIC, GTK_POLICY_ALWAYS);
	gtk_box_pack_start(GTK_BOX(group), scrolled, TRUE, TRUE, 0);
	gtk_widget_show(scrolled);

	filter_store = gtk_list_store_new(1, G_TYPE_POINTER);
	filter_view = gtk_tree_view_new_with_model(GTK_TREE_MODEL(filter_store));
	g_object_unref(filter_store);
	selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(filter_view));
	gtk_tree_selection_set_mode(GTK_TREE_SELECTION(selection), GTK_SELECTION_SINGLE);

	gtk_tree_view_set_enable_search(GTK_TREE_VIEW(filter_view), FALSE);

	column = gtk_tree_view_column_new();
	gtk_tree_view_column_set_title(column, _("Filter"));
	gtk_tree_view_column_set_resizable(column, TRUE);

	renderer = gtk_cell_renderer_toggle_new();
	g_signal_connect(G_OBJECT(renderer), "toggled",
			 G_CALLBACK(filter_store_enable_cb), filter_store);
	gtk_tree_view_column_pack_start(column, renderer, FALSE);
	gtk_tree_view_column_set_cell_data_func(column, renderer, filter_set_func,
						GINT_TO_POINTER(FE_ENABLE), NULL);
	
	renderer = gtk_cell_renderer_text_new();
	g_signal_connect(G_OBJECT(renderer), "edited",
			 G_CALLBACK(filter_store_ext_edit_cb), filter_store);
	gtk_tree_view_column_pack_start(column, renderer, TRUE);
	g_object_set(G_OBJECT(renderer), "editable", (gboolean)TRUE, NULL);
	gtk_tree_view_column_set_cell_data_func(column, renderer, filter_set_func,
						GINT_TO_POINTER(FE_EXTENSION), NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(filter_view), column);

	column = gtk_tree_view_column_new();
	gtk_tree_view_column_set_title(column, _("Description"));
	gtk_tree_view_column_set_resizable(column, TRUE);
	renderer = gtk_cell_renderer_text_new();
	g_signal_connect(G_OBJECT(renderer), "edited",
			 G_CALLBACK(filter_store_desc_edit_cb), filter_store);
	g_object_set(G_OBJECT(renderer), "editable", (gboolean)TRUE, NULL);
	gtk_tree_view_column_pack_start(column, renderer, FALSE);
	gtk_tree_view_column_set_cell_data_func(column, renderer, filter_set_func,
						GINT_TO_POINTER(FE_DESCRIPTION), NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(filter_view), column);

	filter_store_populate();
	gtk_container_add(GTK_CONTAINER(scrolled), filter_view);
	gtk_widget_show(filter_view);

	hbox = pref_box_new(group, FALSE, GTK_ORIENTATION_HORIZONTAL, PREF_PAD_BUTTON_GAP);

	button = pref_button_new(NULL, NULL, _("Defaults"), FALSE,
				 G_CALLBACK(filter_default_cb), NULL);
	gtk_box_pack_end(GTK_BOX(hbox), button, FALSE, FALSE, 0);
	gtk_widget_show(button);

	button = pref_button_new(NULL, GTK_STOCK_REMOVE, NULL, FALSE,
				 G_CALLBACK(filter_remove_cb), filter_view);
	gtk_box_pack_end(GTK_BOX(hbox), button, FALSE, FALSE, 0);
	gtk_widget_show(button);

	button = pref_button_new(NULL, GTK_STOCK_ADD, NULL, FALSE,
				 G_CALLBACK(filter_add_cb), NULL);
	gtk_box_pack_end(GTK_BOX(hbox), button, FALSE, FALSE, 0);
	gtk_widget_show(button);


	/* editor entry tab */

	vbox = gtk_vbox_new(FALSE, PREF_PAD_GAP);
	gtk_container_set_border_width(GTK_CONTAINER(vbox), PREF_PAD_BORDER);
	gtk_widget_show(vbox);
	label = gtk_label_new(_("Editors"));
	gtk_notebook_append_page(GTK_NOTEBOOK(notebook), vbox, label);

	table = pref_table_new(vbox, 3, 9, FALSE, FALSE);
	gtk_table_set_col_spacings(GTK_TABLE(table), PREF_PAD_GAP);

	label = pref_table_label(table, 0, 0, _("#"), 1.0);
	pref_label_bold(label, TRUE, FALSE);

	label = pref_table_label(table, 1, 0, _("Menu name"), 0.0);
	pref_label_bold(label, TRUE, FALSE);

	label = pref_table_label(table, 2, 0, _("Command Line"), 0.0);
	pref_label_bold(label, TRUE, FALSE);

	for (i = 0; i < GQVIEW_EDITOR_SLOTS; i++)
		{
		gchar *buf;

		buf = g_strdup_printf("%d", i+1);
		pref_table_label(table, 0, i+1, buf, 1.0);
		g_free(buf);

		editor_name_entry[i] = gtk_entry_new();
		gtk_entry_set_max_length(GTK_ENTRY(editor_name_entry[i]), EDITOR_NAME_MAX_LENGTH);
		gtk_widget_set_size_request(editor_name_entry[i],80,-1);
		if (editor_name[i]) gtk_entry_set_text(GTK_ENTRY(editor_name_entry[i]),editor_name[i]);
		gtk_table_attach(GTK_TABLE (table),editor_name_entry[i],1,2,i+1,i+2,
				 GTK_FILL | GTK_EXPAND, 0, 0, 0);
		gtk_widget_show(editor_name_entry[i]);

		editor_command_entry[i] = gtk_entry_new();
		gtk_entry_set_max_length(GTK_ENTRY(editor_command_entry[i]), EDITOR_COMMAND_MAX_LENGTH);
		gtk_widget_set_size_request(editor_command_entry[i],160,-1);
		tab_completion_add_to_entry(editor_command_entry[i], NULL, NULL);
		if (editor_command[i]) gtk_entry_set_text(GTK_ENTRY(editor_command_entry[i]), editor_command[i]);
		gtk_table_attach(GTK_TABLE (table),editor_command_entry[i],2,3,i+1,i+2,
				 GTK_FILL | GTK_EXPAND, 0, 0, 0);
		gtk_widget_show(editor_command_entry[i]);
		}

	hbox = pref_box_new(vbox, FALSE, GTK_ORIENTATION_HORIZONTAL, PREF_PAD_BUTTON_GAP);

	button = pref_button_new(NULL, NULL, _("Defaults"), FALSE,
				 G_CALLBACK(editor_default_cb), NULL);
	gtk_box_pack_end(GTK_BOX(hbox), button, FALSE, FALSE, 0);
	gtk_widget_show(button);

	button = pref_button_new(NULL, GTK_STOCK_HELP, NULL, FALSE,
				 G_CALLBACK(editor_help_cb), NULL);
	gtk_box_pack_end(GTK_BOX(hbox), button, FALSE, FALSE, 0);
	gtk_widget_show(button);

	/* advanced entry tab */

	scrolled = gtk_scrolled_window_new(NULL, NULL);
	gtk_container_set_border_width(GTK_CONTAINER(scrolled), PREF_PAD_BORDER);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled),
				       GTK_POLICY_NEVER, GTK_POLICY_AUTOMATIC);
	label = gtk_label_new(_("Advanced"));
	gtk_notebook_append_page(GTK_NOTEBOOK(notebook), scrolled, label);
	gtk_widget_show(scrolled);

	viewport = gtk_viewport_new(NULL, NULL);
	gtk_viewport_set_shadow_type(GTK_VIEWPORT(viewport), GTK_SHADOW_NONE);
	gtk_container_add(GTK_CONTAINER(scrolled), viewport);
	gtk_widget_show(viewport);

	vbox = gtk_vbox_new(FALSE, 0);
	gtk_container_add(GTK_CONTAINER(viewport), vbox);
	gtk_widget_show(vbox);

	group = pref_group_new(vbox, FALSE, _("Full screen"), GTK_ORIENTATION_VERTICAL);

	fullscreen_screen_c = fullscreen_screen;
	fullscreen_above_c = fullscreen_above;
	hbox = fullscreen_prefs_selection_new(_("Location:"), &fullscreen_screen_c, &fullscreen_above_c);
	gtk_box_pack_start(GTK_BOX(group), hbox, FALSE, FALSE, 0);
	gtk_widget_show(hbox);

	pref_checkbox_new_int(group, _("Smooth image flip"),
			      fullscreen_clean_flip, &fullscreen_clean_flip_c);
	pref_checkbox_new_int(group, _("Disable screen saver"),
			      fullscreen_disable_saver, &fullscreen_disable_saver_c);

	group = pref_group_new(vbox, FALSE, _("Delete"), GTK_ORIENTATION_VERTICAL);

	pref_checkbox_new_int(group, _("Confirm file delete"),
			      confirm_delete, &confirm_delete_c);
	pref_checkbox_new_int(group, _("Enable Delete key"),
			      enable_delete_key, &enable_delete_key_c);

	ct_button = pref_checkbox_new_int(group, _("Safe delete"),
					  safe_delete_enable, &safe_delete_enable_c);

	hbox = pref_box_new(group, FALSE, GTK_ORIENTATION_HORIZONTAL, PREF_PAD_SPACE);
	pref_checkbox_link_sensitivity(ct_button, hbox);

	pref_spacer(hbox, PREF_PAD_INDENT - PREF_PAD_SPACE);
	pref_label_new(hbox, _("Folder:"));

	tabcomp = tab_completion_new(&safe_delete_path_entry, safe_delete_path, NULL, NULL);
	tab_completion_add_select_button(safe_delete_path_entry, NULL, TRUE);
	gtk_box_pack_start(GTK_BOX(hbox), tabcomp, TRUE, TRUE, 0);
	gtk_widget_show(tabcomp);

	hbox = pref_box_new(group, FALSE, GTK_ORIENTATION_HORIZONTAL, PREF_PAD_BUTTON_GAP);
	pref_checkbox_link_sensitivity(ct_button, hbox);

	pref_spacer(hbox, PREF_PAD_INDENT - PREF_PAD_GAP);
	pref_spin_new_int(hbox, _("Maximum size:"), _("MB"),
			  1, 500, 1, safe_delete_size, &safe_delete_size_c);

	button = pref_button_new(NULL, NULL, _("View"), FALSE,
				 G_CALLBACK(safe_delete_view_cb), NULL);
	gtk_box_pack_end(GTK_BOX(hbox), button, FALSE, FALSE, 0);
	gtk_widget_show(button);

	button = pref_button_new(NULL, GTK_STOCK_CLEAR, NULL, FALSE,
				 G_CALLBACK(safe_delete_clear_cb), NULL);
	gtk_box_pack_end(GTK_BOX(hbox), button, FALSE, FALSE, 0);
	gtk_widget_show(button);

	group = pref_group_new(vbox, FALSE, _("Behavior"), GTK_ORIENTATION_VERTICAL);

	pref_checkbox_new_int(group, _("Rectangular selection in icon view"),
			      collection_rectangular_selection, &collection_rectangular_selection_c);

	pref_checkbox_new_int(group, _("Descend folders in tree view"),
			      tree_descend_subdirs, &tree_descend_subdirs_c);

	pref_checkbox_new_int(group, _("In place renaming"),
			      enable_in_place_rename, &enable_in_place_rename_c);

	group = pref_group_new(vbox, FALSE, _("Navigation"), GTK_ORIENTATION_VERTICAL);

	pref_checkbox_new_int(group, _("Progressive keyboard scrolling"),
			      progressive_key_scrolling, &progressive_key_scrolling_c);
	pref_checkbox_new_int(group, _("Mouse wheel scrolls image"),
			      mousewheel_scrolls, &mousewheel_scrolls_c);

	group = pref_group_new(vbox, FALSE, _("Miscellaneous"), GTK_ORIENTATION_VERTICAL);

	pref_checkbox_new_int(group, _("Store keywords and comments local to source images"),
			      enable_metadata_dirs, &enable_metadata_dirs_c);

	pref_spin_new_int(group, _("Custom similarity threshold:"), NULL,
			  0, 100, 1, dupe_custom_threshold, &dupe_custom_threshold_c);

	pref_spin_new_int(group, _("Offscreen cache size (Mb per image):"), NULL,
			  0, 128, 1, tile_cache_max, &tile_cache_max_c);

	group =  pref_group_new(vbox, FALSE, _("Color profiles"), GTK_ORIENTATION_VERTICAL);
#ifndef HAVE_LCMS
	gtk_widget_set_sensitive(pref_group_parent(group), FALSE);
#endif

	table = pref_table_new(group, 3, COLOR_PROFILE_INPUTS + 2, FALSE, FALSE);
	gtk_table_set_col_spacings(GTK_TABLE(table), PREF_PAD_GAP);

	label = pref_table_label(table, 0, 0, _("Type"), 0.0);
	pref_label_bold(label, TRUE, FALSE);

	label = pref_table_label(table, 1, 0, _("Menu name"), 0.0);
	pref_label_bold(label, TRUE, FALSE);

	label = pref_table_label(table, 2, 0, _("File"), 0.0);
	pref_label_bold(label, TRUE, FALSE);

	for (i = 0; i < COLOR_PROFILE_INPUTS; i++)
		{
		GtkWidget *entry;
		gchar *buf;

		buf = g_strdup_printf("Input %d:", i + 1);
		pref_table_label(table, 0, i + 1, buf, 1.0);
		g_free(buf);

		entry = gtk_entry_new();
		gtk_entry_set_max_length(GTK_ENTRY(entry), EDITOR_NAME_MAX_LENGTH);
		gtk_widget_set_size_request(editor_name_entry[i], 30, -1);
		if (color_profile_input_name[i]) gtk_entry_set_text(GTK_ENTRY(entry), color_profile_input_name[i]);
		gtk_table_attach(GTK_TABLE(table), entry, 1, 2, i + 1, i + 2,
				 GTK_FILL | GTK_EXPAND, 0, 0, 0);
		gtk_widget_show(entry);
		color_profile_input_name_entry[i] = entry;

		tabcomp = tab_completion_new(&entry, color_profile_input_file[i], NULL, NULL);
		tab_completion_add_select_button(entry, _("Select color profile"), FALSE);
		gtk_widget_set_size_request(entry, 160, -1);
		gtk_table_attach(GTK_TABLE(table), tabcomp, 2, 3, i + 1, i + 2,
				 GTK_FILL | GTK_EXPAND, 0, 0, 0);
		gtk_widget_show(tabcomp);
		color_profile_input_file_entry[i] = entry;
		}

	pref_table_label(table, 0, COLOR_PROFILE_INPUTS + 1, _("Screen:"), 1.0);
	tabcomp = tab_completion_new(&color_profile_screen_file_entry,
				     color_profile_screen_file, NULL, NULL);
	tab_completion_add_select_button(color_profile_screen_file_entry, _("Select color profile"), FALSE);
	gtk_widget_set_size_request(color_profile_screen_file_entry, 160, -1);
	gtk_table_attach(GTK_TABLE(table), tabcomp, 2, 3,
			 COLOR_PROFILE_INPUTS + 1, COLOR_PROFILE_INPUTS + 2,
			 GTK_FILL | GTK_EXPAND, 0, 0, 0);
	gtk_widget_show(tabcomp);

	gtk_widget_show(notebook);

	gtk_widget_show(configwindow);
}

/*
 *-----------------------------------------------------------------------------
 * config window show (public)
 *-----------------------------------------------------------------------------
 */ 

void show_config_window(void)
{
	if (configwindow)
		{
		gtk_window_present(GTK_WINDOW(configwindow));
		return;
		}

	config_window_create();
}

/*
 *-----------------
 * about window
 *-----------------
 */

static GtkWidget *about = NULL;

static gint about_delete_cb(GtkWidget *widget, GdkEventAny *event, gpointer data)
{
	gtk_widget_destroy(about);
	about = NULL;

	return TRUE;
}

static void about_window_close(GtkWidget *widget, gpointer data)
{
	if (!about) return;

	gtk_widget_destroy(about);
	about = NULL;
}

static void about_credits_cb(GtkWidget *widget, gpointer data)
{
	help_window_show("credits");
}

void show_about_window(void)
{
	GtkWidget *vbox;
	GtkWidget *hbox;
	GtkWidget *label;
	GtkWidget *button;
	GdkPixbuf *pixbuf;

	gchar *buf;

	if (about)
		{
		gtk_window_present(GTK_WINDOW(about));
		return;
		}

	about = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_type_hint(GTK_WINDOW(about), GDK_WINDOW_TYPE_HINT_DIALOG);
	gtk_window_set_wmclass(GTK_WINDOW(about), "about", "GQview");
	g_signal_connect(G_OBJECT(about), "delete_event",
			 G_CALLBACK(about_delete_cb), NULL);

	gtk_window_set_title(GTK_WINDOW(about), _("About - GQview"));
	gtk_container_set_border_width(GTK_CONTAINER(about), PREF_PAD_BORDER);

	vbox = gtk_vbox_new(FALSE, PREF_PAD_SPACE);
	gtk_container_add(GTK_CONTAINER(about), vbox);
	gtk_widget_show(vbox);

	pixbuf = pixbuf_inline(PIXBUF_INLINE_LOGO);
	button = gtk_image_new_from_pixbuf(pixbuf);
	g_object_unref(pixbuf);
	gtk_box_pack_start(GTK_BOX(vbox), button, TRUE, TRUE, 0);
	gtk_widget_show(button);

	buf = g_strdup_printf(_("GQview %s\n\nCopyright (c) %s John Ellis\nwebsite: %s\nemail: %s\n\nReleased under the GNU General Public License"),
			      VERSION,
			      "2006",
			      "gqview.sourceforge.net",
			      "gqview@users.sourceforge.net");
	label = gtk_label_new(buf);
	g_free(buf);

	gtk_label_set_justify(GTK_LABEL(label), GTK_JUSTIFY_CENTER);
	gtk_box_pack_start(GTK_BOX(vbox), label, TRUE, TRUE, 0);
	gtk_widget_show(label);

	hbox = gtk_hbutton_box_new();
	gtk_button_box_set_layout(GTK_BUTTON_BOX(hbox), GTK_BUTTONBOX_END);
	gtk_box_set_spacing(GTK_BOX(hbox), PREF_PAD_BUTTON_GAP);
	gtk_box_pack_end(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);
	gtk_widget_show(hbox);

	button = pref_button_new(NULL, NULL, _("Credits..."), FALSE,
				 G_CALLBACK(about_credits_cb), NULL);
	gtk_container_add(GTK_CONTAINER(hbox), button);
	GTK_WIDGET_SET_FLAGS(button, GTK_CAN_DEFAULT);
	gtk_widget_show(button);

	button = pref_button_new(NULL, GTK_STOCK_CLOSE, NULL, FALSE,
				 G_CALLBACK(about_window_close), NULL);
	gtk_container_add(GTK_CONTAINER(hbox), button);
	GTK_WIDGET_SET_FLAGS(button, GTK_CAN_DEFAULT);
	gtk_widget_grab_default(button);
	gtk_widget_show(button);

	window_set_icon(about, NULL, NULL);
	gtk_widget_show(about);
}

