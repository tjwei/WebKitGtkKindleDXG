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


#ifndef CACHE_MAINT_H
#define CACHE_MAINT_H


void cache_maintain_home(gint metadata, gint clear, GtkWidget *parent);

gint cache_maintain_home_dir(const gchar *dir, gint recursive, gint clear);
gint cache_maintain_dir(const gchar *dir, gint recursive, gint clear);

void cache_maint_moved(const gchar *src, const gchar *dest);
void cache_maint_removed(const gchar *source);
void cache_maint_copied(const gchar *src, const gchar *dest);


void cache_manager_gqview_clear_confirm(GtkWidget *parent);
void cache_manager_show(void);


#endif


