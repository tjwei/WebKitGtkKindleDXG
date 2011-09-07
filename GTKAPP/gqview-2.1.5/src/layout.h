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

#ifndef LAYOUT_H
#define LAYOUT_H


extern GList *layout_window_list;


LayoutWindow *layout_new(const gchar *path, gint popped, gint hidden);
LayoutWindow *layout_new_with_geometry(const gchar *path, gint popped, gint hidden,
				       const gchar *geometry);

void layout_close(LayoutWindow *lw);
void layout_free(LayoutWindow *lw);

gint layout_valid(LayoutWindow **lw);

LayoutWindow *layout_find_by_image(ImageWindow *imd);

const gchar *layout_get_path(LayoutWindow *lw);
gint layout_set_path(LayoutWindow *lw, const gchar *path);

void layout_status_update_progress(LayoutWindow *lw, gdouble val, const gchar *text);
void layout_status_update_info(LayoutWindow *lw, const gchar *text);
void layout_status_update_image(LayoutWindow *lw);
void layout_status_update_all(LayoutWindow *lw);

GList *layout_list(LayoutWindow *lw);
gint layout_list_count(LayoutWindow *lw, gint64 *bytes);
const gchar *layout_list_get_path(LayoutWindow *lw, gint index);
gint layout_list_get_index(LayoutWindow *lw, const gchar *path);
void layout_list_sync_path(LayoutWindow *lw, const gchar *path);

GList *layout_selection_list(LayoutWindow *lw);
/* return list of pointers to int for selection */
GList *layout_selection_list_by_index(LayoutWindow *lw);
gint layout_selection_count(LayoutWindow *lw, gint64 *bytes);
void layout_select_all(LayoutWindow *lw);
void layout_select_none(LayoutWindow *lw);

void layout_refresh(LayoutWindow *lw);

void layout_thumb_set(LayoutWindow *lw, gint enable);
gint layout_thumb_get(LayoutWindow *lw);

void layout_sort_set(LayoutWindow *lw, SortType type, gint ascend);
gint layout_sort_get(LayoutWindow *lw, SortType *type, gint *ascend);

gint layout_geometry_get(LayoutWindow *lw, gint *x, gint *y, gint *w, gint *h);
gint layout_geometry_get_dividers(LayoutWindow *lw, gint *h, gint *v);

void layout_views_set(LayoutWindow *lw, gint tree, gint icons);
gint layout_views_get(LayoutWindow *lw, gint *tree, gint *icons);

void layout_status_update(LayoutWindow *lw, const gchar *text);

void layout_style_set(LayoutWindow *lw, gint style, const gchar *order);

void layout_menu_update_edit(void);
void layout_styles_update(void);
void layout_colors_update(void);


gint layout_geometry_get_tools(LayoutWindow *lw, gint *x, gint *y, gint *w, gint *h, gint *divider_pos);
void layout_tools_float_set(LayoutWindow *lw, gint popped, gint hidden);
gint layout_tools_float_get(LayoutWindow *lw, gint *popped, gint *hidden);

void layout_tools_float_toggle(LayoutWindow *lw);
void layout_tools_hide_toggle(LayoutWindow *lw);


void layout_toolbar_toggle(LayoutWindow *lw);
gint layout_toolbar_hidden(LayoutWindow *lw);


void layout_maint_renamed(const gchar *source, const gchar *dest);
void layout_maint_removed(const gchar *path, GList *ignore_list);
void layout_maint_moved(const gchar *source, const gchar *dest, GList *ignore_list);


#endif



