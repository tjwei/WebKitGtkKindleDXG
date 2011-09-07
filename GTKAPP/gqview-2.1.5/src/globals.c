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


GList *filename_filter = NULL;

/* -- options -- */
gint main_window_w = 500;
gint main_window_h = 400;
gint main_window_x = 0;
gint main_window_y = 0;
gint main_window_maximized = FALSE;

gint float_window_w = 260;
gint float_window_h = 450;
gint float_window_x = 0;
gint float_window_y = 0;
gint float_window_divider = -1;

gint window_hdivider_pos = -1;
gint window_vdivider_pos = 200;

gint save_window_positions = FALSE;
gint tools_float = FALSE;
gint tools_hidden = FALSE;
gint toolbar_hidden = FALSE;
gint progressive_key_scrolling = FALSE;

gint startup_path_enable = FALSE;
gchar *startup_path = NULL;
gint confirm_delete = TRUE;
gint enable_delete_key = TRUE;
gint safe_delete_enable = FALSE;
gchar *safe_delete_path = NULL;
gint safe_delete_size = 20;
gint restore_tool = FALSE;
gint zoom_mode = ZOOM_RESET_ORIGINAL;
gint two_pass_zoom = TRUE;
gint scroll_reset_method = SCROLL_RESET_TOPLEFT;
gint fit_window = FALSE;
gint limit_window_size = FALSE;
gint zoom_to_fit_expands = TRUE;
gint max_window_size = 100;
gint thumb_max_width = 96;
gint thumb_max_height = 72;
gint enable_thumb_caching = TRUE;
gint enable_thumb_dirs = FALSE;
gint use_xvpics_thumbnails = TRUE;
gint thumbnail_fast = TRUE;
gint thumbnail_spec_standard = TRUE;
gint enable_metadata_dirs = FALSE;
gint show_dot_files = FALSE;
gint file_filter_disable = FALSE;
gchar *editor_name[GQVIEW_EDITOR_SLOTS];
gchar *editor_command[GQVIEW_EDITOR_SLOTS];

gint thumbnails_enabled = FALSE;
SortType file_sort_method = SORT_NAME;
gint file_sort_ascending = TRUE;

gint slideshow_delay = 150;
gint slideshow_random = FALSE;
gint slideshow_repeat = FALSE;

gint mousewheel_scrolls = FALSE;
gint enable_in_place_rename = TRUE;

gint recent_list_max = 10;

gint collection_rectangular_selection = FALSE;

gint tile_cache_max = 10;
gint thumbnail_quality = (gint)GDK_INTERP_TILES;
gint zoom_quality = (gint)GDK_INTERP_BILINEAR;
gint dither_quality = (gint)GDK_RGB_DITHER_NORMAL;

gint zoom_increment = 5;

gint enable_read_ahead = TRUE;

gint place_dialogs_under_mouse = FALSE;

gint black_window_background = FALSE;

gint fullscreen_screen = -1;
gint fullscreen_clean_flip = FALSE;
gint fullscreen_disable_saver = TRUE;
gint fullscreen_above = FALSE;

gint dupe_custom_threshold = 99;

gint debug = FALSE;

/* layout */
gchar *layout_order = NULL;
gint layout_style = 0;

gint layout_view_icons = FALSE;
gint layout_view_tree = FALSE;

gint show_icon_names = TRUE;

gint tree_descend_subdirs = FALSE;

gint lazy_image_sync = FALSE;
gint update_on_time_change = TRUE;
gint exif_rotate_enable = FALSE;

/* color profiles */
gint color_profile_enabled = FALSE;
gint color_profile_input_type = 0;
gchar *color_profile_input_file[COLOR_PROFILE_INPUTS];
gchar *color_profile_input_name[COLOR_PROFILE_INPUTS];
gint color_profile_screen_type = 0;
gchar *color_profile_screen_file = NULL;
gint color_profile_use_image = TRUE;


