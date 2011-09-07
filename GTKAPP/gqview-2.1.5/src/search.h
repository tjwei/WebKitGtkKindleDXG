/*
 * GQview
 * (C) 2005 John Ellis
 *
 * Author: John Ellis
 *
 * This software is released under the GNU General Public License (GNU GPL).
 * Please read the included file COPYING for more information.
 * This software comes with no warranty of any kind, use at your own risk!
 */


#ifndef SEARCH_H
#define SEARCH_H


void search_new(const gchar *path, const gchar *example_file);


void search_maint_renamed(const gchar *source, const gchar *dest);
void search_maint_removed(const gchar *path);


#endif


