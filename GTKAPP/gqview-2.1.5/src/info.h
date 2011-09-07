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


#ifndef INFO_H
#define INFO_H


typedef struct _InfoData InfoData;
struct _InfoData
{
	GtkWidget *window;
	ImageWindow *image;

	GList *list;

	const gchar *path;

	GtkWidget *notebook;
	GtkWidget *name_entry;

	GtkWidget *button_next;
	GtkWidget *button_back;
	GtkWidget *label_count;

	GList *tab_list;

	gint updated;
};


void info_window_new(const gchar *path, GList *list);

GtkWidget *table_add_line(GtkWidget *table, gint x, gint y,
			  const gchar *description, const gchar *text);


#endif


