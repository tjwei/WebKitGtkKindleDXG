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


#ifndef MENU_H
#define MENU_H


gpointer submenu_item_get_data(GtkWidget *menu);

GtkWidget *submenu_add_edit(GtkWidget *menu, GtkWidget **menu_item, GtkSignalFunc func, gpointer data);

gchar *sort_type_get_text(SortType method);
GtkWidget *submenu_add_sort(GtkWidget *menu, GtkSignalFunc func, gpointer data,
			    gint include_none, gint include_path,
			    gint show_current, SortType type);

gchar *alter_type_get_text(AlterType type);
GtkWidget *submenu_add_alter(GtkWidget *menu, GtkSignalFunc func, gpointer data);


#endif
