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

#ifndef VIEW_FILE_LIST_H
#define VIEW_FILE_LIST_H


#include "filelist.h"


ViewFileList *vflist_new(const gchar *path, gint thumbs);

void vflist_set_status_func(ViewFileList *vfl,
			    void (*func)(ViewFileList *vfl, gpointer data), gpointer data);
void vflist_set_thumb_status_func(ViewFileList *vfl,
				  void (*func)(ViewFileList *vfl, gdouble val, const gchar *text, gpointer data),
				  gpointer data);

void vflist_set_layout(ViewFileList *vfl, LayoutWindow *layout);

gint vflist_set_path(ViewFileList *vfl, const gchar *path);
gint vflist_refresh(ViewFileList *vfl);

void vflist_thumb_set(ViewFileList *vfl, gint enable);
void vflist_sort_set(ViewFileList *vfl, SortType type, gint ascend);

FileData *vflist_index_get_data(ViewFileList *vfl, gint row);
gchar *vflist_index_get_path(ViewFileList *vfl, gint row);
gint vflist_index_by_path(ViewFileList *vfl, const gchar *path);
gint vflist_count(ViewFileList *vfl, gint64 *bytes);
GList *vflist_get_list(ViewFileList *vfl);

gint vflist_index_is_selected(ViewFileList *vfl, gint row);
gint vflist_selection_count(ViewFileList *vfl, gint64 *bytes);
GList *vflist_selection_get_list(ViewFileList *vfl);
GList *vflist_selection_get_list_by_index(ViewFileList *vfl);

void vflist_select_all(ViewFileList *vfl);
void vflist_select_none(ViewFileList *vfl);
void vflist_select_by_path(ViewFileList *vfl, const gchar *path);


gint vflist_maint_renamed(ViewFileList *vfl, const gchar *source, const gchar *dest);
gint vflist_maint_removed(ViewFileList *vfl, const gchar *path, GList *ignore_list);
gint vflist_maint_moved(ViewFileList *vfl, const gchar *source, const gchar *dest, GList *ignore_list);


#endif
