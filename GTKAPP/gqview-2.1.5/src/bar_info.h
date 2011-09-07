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


#ifndef BAR_INFO_H
#define BAR_INFO_H


GtkWidget *bar_info_new(const gchar *path, gint metadata_only, GtkWidget *bounding_widget);
void bar_info_close(GtkWidget *bar);

void bar_info_set(GtkWidget *bar, const gchar *path);
gint bar_info_event(GtkWidget *bar, GdkEvent *event);

void bar_info_set_selection_func(GtkWidget *bar, GList *(*list_func)(gpointer data), gpointer data);
void bar_info_selection(GtkWidget *bar, gint count);

void bar_info_size_request(GtkWidget *bar, gint width);

void bar_info_maint_renamed(GtkWidget *bar, const gchar *path);

gint comment_write(const gchar *path, GList *keywords, const gchar *comment);
gint comment_cache_write(const gchar *path, GList *keywords, const gchar *comment);

gint comment_read(const gchar *path, GList **keywords, gchar **comment);
gint comment_cache_read(const gchar *path, GList **keywords, gchar **comment);

GList *keyword_list_pull(GtkWidget *text_widget);
void keyword_list_push(GtkWidget *textview, GList *list);


#endif
