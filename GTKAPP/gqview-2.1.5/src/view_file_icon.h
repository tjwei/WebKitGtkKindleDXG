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

#ifndef VIEW_FILE_ICON_H
#define VIEW_FILE_ICON_H


ViewFileIcon *vficon_new(const gchar *path);

gint vficon_set_path(ViewFileIcon *vfi, const gchar *path);
void vficon_set_status_func(ViewFileIcon *vfi,
			    void (*func)(ViewFileIcon *vfi, gpointer data), gpointer data);
void vficon_set_thumb_status_func(ViewFileIcon *vfi,
				  void (*func)(ViewFileIcon *vfi, gdouble val, const gchar *text, gpointer data),
				  gpointer data);

void vficon_set_layout(ViewFileIcon *vfi, LayoutWindow *layout);

gint vficon_set_path(ViewFileIcon *vfi, const gchar *path);
gint vficon_refresh(ViewFileIcon *vfi);

void vficon_sort_set(ViewFileIcon *vfi, SortType type, gint ascend);

FileData *vficon_index_get_data(ViewFileIcon *vfi, gint row);
gchar *vficon_index_get_path(ViewFileIcon *vfi, gint row);
gint vficon_index_by_path(ViewFileIcon *vfi, const gchar *path);
gint vficon_count(ViewFileIcon *vfi, gint64 *bytes);
GList *vficon_get_list(ViewFileIcon *vfi);

gint vficon_index_is_selected(ViewFileIcon *vfi, gint row);
gint vficon_selection_count(ViewFileIcon *vfi, gint64 *bytes);
GList *vficon_selection_get_list(ViewFileIcon *vfi);
GList *vficon_selection_get_list_by_index(ViewFileIcon *vfi);

void vficon_select_all(ViewFileIcon *vfi);
void vficon_select_none(ViewFileIcon *vfi);
void vficon_select_by_path(ViewFileIcon *vfi, const gchar *path);


gint vficon_maint_renamed(ViewFileIcon *vfi, const gchar *source, const gchar *dest);
gint vficon_maint_removed(ViewFileIcon *vfi, const gchar *path, GList *ignore_list);
gint vficon_maint_moved(ViewFileIcon *vfi, const gchar *source, const gchar *dest, GList *ignore_list);


#endif


