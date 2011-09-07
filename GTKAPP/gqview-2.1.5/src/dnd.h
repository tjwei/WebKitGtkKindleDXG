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


#ifndef DND_H
#define DND_H


enum {
	TARGET_APP_COLLECTION_MEMBER,
	TARGET_URI_LIST,
	TARGET_TEXT_PLAIN
};


extern GtkTargetEntry dnd_file_drag_types[];
extern gint dnd_file_drag_types_count;

extern GtkTargetEntry dnd_file_drop_types[];
extern gint dnd_file_drop_types_count;


/* sets a drag icon to pixbuf, if items is > 1, text is drawn onto icon to indicate value */
void dnd_set_drag_icon(GtkWidget *widget, GdkDragContext *context, GdkPixbuf *pixbuf, gint items);


#endif

