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

#ifndef VIEW_DIR_LIST_H
#define VIEW_DIR_LIST_H


ViewDirList *vdlist_new(const gchar *path);

void vdlist_set_select_func(ViewDirList *vdl,
			    void (*func)(ViewDirList *vdl, const gchar *path, gpointer data), gpointer data);

void vdlist_set_layout(ViewDirList *vdl, LayoutWindow *layout);

gint vdlist_set_path(ViewDirList *vdl, const gchar *path);
void vdlist_refresh(ViewDirList *vdl);

const gchar *vdlist_row_get_path(ViewDirList *vdl, gint row);


#endif


