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


#ifndef IMG_VIEW_H
#define IMG_VIEW_H


void view_window_new(const gchar *path);
void view_window_new_from_list(GList *list);
void view_window_new_from_collection(CollectionData *cd, CollectInfo *info);

void view_window_colors_update(void);

gint view_window_find_image(ImageWindow *imd, gint *index, gint *total);

void view_window_maint_removed(const gchar *path, GList *ignore_list);
void view_window_maint_moved(const gchar *source, const gchar *dest);


#endif
