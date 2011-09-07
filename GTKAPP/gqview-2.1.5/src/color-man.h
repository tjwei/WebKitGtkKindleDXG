/*
 * GQview
 * (C) 2006 John Ellis
 *
 * Author: John Ellis
 *
 * This software is released under the GNU General Public License (GNU GPL).
 * Please read the included file COPYING for more information.
 * This software comes with no warranty of any kind, use at your own risk!
 */


#ifndef COLOR_MAN_H
#define COLOR_MAN_H

typedef enum {
	COLOR_PROFILE_NONE = 0,
	COLOR_PROFILE_FILE,
	COLOR_PROFILE_SRGB,
	COLOR_PROFILE_MEM
} ColorManProfileType;

typedef enum {
	COLOR_RETURN_SUCCESS = 0,
	COLOR_RETURN_ERROR,
	COLOR_RETURN_IMAGE_CHANGED
} ColorManReturnType;

typedef struct _ColorMan ColorMan;
typedef void (* ColorManDoneFunc)(ColorMan *cm, ColorManReturnType success, gpointer data);


struct _ColorMan {
	ImageWindow *imd;
	GdkPixbuf *pixbuf;
	gint incremental_sync;
	gint row;

	gpointer profile;

	gint idle_id;

	ColorManDoneFunc func_done;
	gpointer func_done_data;
};


ColorMan *color_man_new(ImageWindow *imd, GdkPixbuf *pixbuf,
			ColorManProfileType input_type, const gchar *input_file,
			ColorManProfileType screen_type, const gchar *screen_file,
			ColorManDoneFunc done_func, gpointer done_data);
ColorMan *color_man_new_embedded(ImageWindow *imd, GdkPixbuf *pixbuf,
				 unsigned char *input_data, guint input_data_len,
				 ColorManProfileType screen_type, const gchar *screen_file,
				 ColorManDoneFunc done_func, gpointer done_data);
void color_man_free(ColorMan *cm);

void color_man_update(void);


#endif

