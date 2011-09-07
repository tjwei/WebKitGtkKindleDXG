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


#ifndef EDITORS_H
#define EDITORS_H


void editor_reset_defaults(void);
void start_editor_from_file(gint n, const gchar *path);
void start_editor_from_path_list(gint n, GList *list);

gint editor_window_flag_set(gint n);


#endif



