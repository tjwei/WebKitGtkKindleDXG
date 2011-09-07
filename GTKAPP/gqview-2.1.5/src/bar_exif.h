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


#ifndef BAR_EXIF_H
#define BAR_EXIF_H


GtkWidget *bar_exif_new(gint show_title, const gchar *path, gint advanced, GtkWidget *bounding_widget);
void bar_exif_close(GtkWidget *bar);

void bar_exif_set(GtkWidget *bar, const gchar *path);

gint bar_exif_is_advanced(GtkWidget *bar);


/* these are exposed for when duplication of the exif bar's text is needed */

const gchar **bar_exif_key_list;
const gint bar_exif_key_count;

gchar *bar_exif_validate_text(gchar *text);


#endif

