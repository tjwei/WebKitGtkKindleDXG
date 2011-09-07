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


#ifndef IMAGE_H
#define IMAGE_H


ImageWindow *image_new(gint frame);

/* additional setup */
void image_attach_window(ImageWindow *imd, GtkWidget *window,
			 const gchar *title, const gchar *title_right, gint show_zoom);
void image_set_update_func(ImageWindow *imd,
			   void (*func)(ImageWindow *imd, gpointer data),
			   gpointer data);
void image_set_button_func(ImageWindow *imd,
	void (*func)(ImageWindow *, gint button, guint32 time, gdouble x, gdouble y, guint state, gpointer),
	gpointer data);
void image_set_scroll_func(ImageWindow *imd,
	void (*func)(ImageWindow *, GdkScrollDirection direction, guint32 time, gdouble x, gdouble y, guint state, gpointer),
        gpointer data);
void image_set_scroll_notify_func(ImageWindow *imd,
				  void (*func)(ImageWindow *imd, gint x, gint y, gint width, gint height, gpointer data),
				  gpointer data);
void image_set_complete_func(ImageWindow *imd,
			     void (*func)(ImageWindow *imd, gint preload, gpointer data),
			     gpointer data);
void image_set_state_func(ImageWindow *imd,
			  void (*func)(ImageWindow *imd, ImageState state, gpointer data),
			  gpointer data);

/* path, name */
const gchar *image_get_path(ImageWindow *imd);
const gchar *image_get_name(ImageWindow *imd);

/* merely changes path string, does not change the image! */
void image_set_path(ImageWindow *imd, const gchar *newpath);

/* load a new image */
void image_change_path(ImageWindow *imd, const gchar *path, gdouble zoom);
void image_change_pixbuf(ImageWindow *imd, GdkPixbuf *pixbuf, gdouble zoom);
void image_change_from_collection(ImageWindow *imd, CollectionData *cd, CollectInfo *info, gdouble zoom);
CollectionData *image_get_collection(ImageWindow *imd, CollectInfo **info);
void image_change_from_image(ImageWindow *imd, ImageWindow *source);

GdkPixbuf *image_get_pixbuf(ImageWindow *imd);

/* manipulation */
void image_area_changed(ImageWindow *imd, gint x, gint y, gint width, gint height);
void image_reload(ImageWindow *imd);
void image_scroll(ImageWindow *imd, gint x, gint y);
void image_scroll_to_point(ImageWindow *imd, gint x, gint y,
			   gdouble x_align, gdouble y_align);
void image_alter(ImageWindow *imd, AlterType type);

/* zoom */
void image_zoom_adjust(ImageWindow *imd, gdouble increment);
void image_zoom_adjust_at_point(ImageWindow *imd, gdouble increment, gint x, gint y);
void image_zoom_set_limits(ImageWindow *imd, gdouble min, gdouble max);
void image_zoom_set(ImageWindow *imd, gdouble zoom);
void image_zoom_set_fill_geometry(ImageWindow *imd, gint vertical);
gdouble image_zoom_get(ImageWindow *imd);
gdouble image_zoom_get_real(ImageWindow *imd);
gchar *image_zoom_get_as_text(ImageWindow *imd);
gdouble image_zoom_get_default(ImageWindow *imd, gint mode);

/* read ahead, pass NULL to cancel */
void image_prebuffer_set(ImageWindow *imd, const gchar *path);

/* auto refresh, interval is 1/1000 sec, 0 uses default, -1 disables */
void image_auto_refresh(ImageWindow *imd, gint interval);

/* allow top window to be resized ? */
void image_top_window_set_sync(ImageWindow *imd, gint allow_sync);

/* background of image */
void image_background_set_black(ImageWindow *imd, gint black);
void image_background_set_color(ImageWindow *imd, GdkColor *color);

/* color profiles */
void image_color_profile_set(ImageWindow *imd,
			     gint input_type, gint screen_type,
			     gint use_embedded);
gint image_color_profile_get(ImageWindow *imd,
			     gint *input_type, gint *screen_type,
			     gint *use_image);
void image_color_profile_set_use(ImageWindow *imd, gint enable);
gint image_color_profile_get_use(ImageWindow *imd);

/* set delayed page flipping */
void image_set_delay_flip(ImageWindow *imd, gint delay);

/* wallpaper util */
void image_to_root_window(ImageWindow *imd, gint scaled);

/* overlays */
gint image_overlay_add(ImageWindow *imd, GdkPixbuf *pixbuf, gint x, gint y,
		       gint relative, gint always);
void image_overlay_set(ImageWindow *imd, gint id, GdkPixbuf *pixbuf, gint x, gint y);
gint image_overlay_get(ImageWindow *imd, gint id, GdkPixbuf **pixbuf, gint *x, gint *y);
void image_overlay_remove(ImageWindow *imd, gint id);



void image_set_image_as_tiles(ImageWindow *imd, gint width, gint height,
			      gint tile_width, gint tile_height, gint cache_size,
			      ImageTileRequestFunc func_tile_request,
			      ImageTileDisposeFunc func_tile_dispose,
			      gpointer data,
			      gdouble zoom);

/* reset default options */
void image_options_sync(void);


#endif



