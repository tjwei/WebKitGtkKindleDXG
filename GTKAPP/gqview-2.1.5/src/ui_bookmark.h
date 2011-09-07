/*
 * (SLIK) SimpLIstic sKin functions
 * (C) 2004 John Ellis
 *
 * Author: John Ellis
 *
 * This software is released under the GNU General Public License (GNU GPL).
 * Please read the included file COPYING for more information.
 * This software comes with no warranty of any kind, use at your own risk!
 */


#ifndef UI_BOOKMARK_H
#define UI_BOOKMARK_H


/* history lists */

gint history_list_load(const gchar *path);
gint history_list_save(const gchar *path);

void history_list_free_key(const gchar *key);

void history_list_add_to_key(const gchar *key, const gchar *path, gint max);

void history_list_item_change(const gchar *key, const gchar *oldpath, const gchar *newpath);
void history_list_item_move(const gchar *key, const gchar *path, gint direction);
void history_list_item_remove(const gchar *key, const gchar *path);

const gchar *history_list_find_last_path_by_key(const gchar* key);

/* the returned GList is internal, don't free it */
GList *history_list_get_by_key(const gchar *key);


/* bookmarks */

GtkWidget *bookmark_list_new(const gchar *key,
			     void (*select_func)(const gchar *path, gpointer data), gpointer select_data);
void bookmark_list_set_key(GtkWidget *list, const gchar *key);
void bookmark_list_set_no_defaults(GtkWidget *list, gint no_defaults);
void bookmark_list_set_editable(GtkWidget *list, gint editable);
void bookmark_list_add(GtkWidget *list, const gchar *name, const gchar *path);

/* allows apps to set up the defaults */
void bookmark_add_default(const gchar *name, const gchar *path);


/* history combo entry */

GtkWidget *history_combo_new(GtkWidget **entry, const gchar *text,
			     const gchar *history_key, gint max_levels);
void history_combo_append_history(GtkWidget *widget, const gchar *text);


/* dnd data parsers (uris) */

gchar *uri_text_escape(const gchar *text);
void uri_text_decode(gchar *text);

GList *uri_list_from_text(gchar *data, gint files_only);
gchar *uri_text_from_list(GList *list, gint *len, gint plain_text);


#endif

