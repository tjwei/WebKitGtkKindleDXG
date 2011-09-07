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

#ifndef PIXBUF_RENDERER_H
#define PIXBUF_RENDERER_H

#include <gtk/gtkeventbox.h>
#include <gtk/gtkwindow.h>


#define TYPE_PIXBUF_RENDERER		(pixbuf_renderer_get_type())
#define PIXBUF_RENDERER(obj)		(G_TYPE_CHECK_INSTANCE_CAST((obj), TYPE_PIXBUF_RENDERER, PixbufRenderer))
#define PIXBUF_RENDERER_CLASS(klass)	(G_TYPE_CHECK_CLASS_CAST((klass), TYPE_PIXBUF_RENDERER, PixbufRendererClass))
#define IS_PIXBUF_RENDERER(obj)		(G_TYPE_CHECK_INSTANCE_TYPE((obj), TYPE_PIXBUF_RENDERER))
#define IS_PIXBUF_RENDERER_CLASS(klass)	(G_TYPE_CHECK_CLASS_TYPE((klass), TYPE_PIXBUF_RENDERER))
#define PIXBUF_RENDERER_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS((obj), TYPE_PIXBUF_RENDERER, PixbufRendererClass))


typedef struct _PixbufRenderer PixbufRenderer;
typedef struct _PixbufRendererClass PixbufRendererClass;


typedef gint (* PixbufRendererTileRequestFunc)(PixbufRenderer *pr, gint x, gint y,
					       gint width, gint height, GdkPixbuf *pixbuf, gpointer user_data);
typedef void (* PixbufRendererTileDisposeFunc)(PixbufRenderer *pr, gint x, gint y,
					       gint width, gint height, GdkPixbuf *pixbuf, gpointer user_data);
typedef enum {
	PR_SCROLL_RESET_TOPLEFT = 0,
	PR_SCROLL_RESET_CENTER,
	PR_SCROLL_RESET_NOCHANGE
} PixbufRendererScrollResetType;

struct _PixbufRenderer
{
	GtkEventBox eventbox;

	gint image_width;	/* image actual dimensions (pixels) */
	gint image_height;

	GdkPixbuf *pixbuf;

	gint window_width;	/* allocated size of window (drawing area) */
	gint window_height;

	gint x_offset;		/* offset of image start (non-zero when image < window) */
	gint y_offset;

	gint vis_width;		/* dimensions of visible part of image */
	gint vis_height;

	gint width;		/* size of scaled image (result) */
	gint height;

	gint x_scroll;		/* scroll offset of image (into width, height to start drawing) */
	gint y_scroll;

	gdouble zoom_min;
	gdouble zoom_max;
	gdouble zoom;		/* zoom we want (0 is auto) */
	gdouble scale;		/* zoom we got (should never be 0) */

	GdkInterpType zoom_quality;
	gboolean zoom_2pass;
	gboolean zoom_expand;

	GdkRgbDither dither_quality;

	PixbufRendererScrollResetType scroll_reset;

	gboolean has_frame;

	GtkWidget *parent_window;	/* resize parent_window when image dimensions change */

	gboolean window_fit;
	gboolean window_limit;
	gint window_limit_size;

	gint tile_cache_max;		/* max mb to use for offscreen buffer */

	/*< private >*/

	gint tile_width;
	gint tile_height;
	gint tile_cols;		/* count of tile columns */
	GList *tiles;		/* list of buffer tiles */
	gint tile_cache_size;	/* allocated size of pixmaps/pixbufs */
	GList *draw_queue;	/* list of areas to redraw */
	GList *draw_queue_2pass;/* list when 2 pass is enabled */

	gint draw_idle_id;
	gint draw_idle_high;	/* current idle_id has high priority */

	gboolean in_drag;
	gint drag_last_x;
	gint drag_last_y;
	gint drag_moved;

	gboolean source_tiles_enabled;
	gint source_tiles_cache_size;

	GList *source_tiles;	/* list of active source tiles */
	gint source_tile_width;
	gint source_tile_height;

	PixbufRendererTileRequestFunc func_tile_request;
	PixbufRendererTileDisposeFunc func_tile_dispose;

	gpointer func_tile_data;

	gboolean delay_flip;
	gboolean loading;
	gboolean complete;

	gint scroller_id;
	gint scroller_overlay;
	gint scroller_x;
	gint scroller_y;
	gint scroller_xpos;
	gint scroller_ypos;
	gint scroller_xinc;
	gint scroller_yinc;

	GList *overlay_list;
	GdkPixmap *overlay_buffer;
};

struct _PixbufRendererClass
{
	GtkEventBoxClass parent_class;

	void (* zoom)		(PixbufRenderer *pr, gdouble zoom);
	void (* clicked)	(PixbufRenderer *pr, GdkEventButton *event);
	void (* scroll_notify)	(PixbufRenderer *pr);

	void (* render_complete)(PixbufRenderer *pr);
};


GType pixbuf_renderer_get_type (void);

PixbufRenderer *pixbuf_renderer_new(void);

void pixbuf_renderer_set_parent(PixbufRenderer *pr, GtkWindow *window);
GtkWindow *pixbuf_renderer_get_parent(PixbufRenderer *pr);

/* display a pixbuf */

void pixbuf_renderer_set_pixbuf(PixbufRenderer *pr, GdkPixbuf *pixbuf, gdouble zoom);
GdkPixbuf *pixbuf_renderer_get_pixbuf(PixbufRenderer *pr);

/* display an on-request array of pixbuf tiles */

void pixbuf_renderer_set_tiles(PixbufRenderer *pr, gint width, gint height,
			       gint tile_width, gint tile_height, gint cache_size,
			       PixbufRendererTileRequestFunc func_request,
			       PixbufRendererTileDisposeFunc func_dispose,
			       gpointer user_data,
			       gdouble zoom);
void pixbuf_renderer_set_tiles_size(PixbufRenderer *pr, gint width, gint height);
gint pixbuf_renderer_get_tiles(PixbufRenderer *pr);

/* move image data from source to pr, source is then set to NULL image */

void pixbuf_renderer_move(PixbufRenderer *pr, PixbufRenderer *source);

/* update region of existing image */

void pixbuf_renderer_area_changed(PixbufRenderer *pr, gint x, gint y, gint width, gint height);

/* scrolling */

void pixbuf_renderer_scroll(PixbufRenderer *pr, gint x, gint y);
void pixbuf_renderer_scroll_to_point(PixbufRenderer *pr, gint x, gint y,
				     gdouble x_align, gdouble y_align);

/* zoom */

void pixbuf_renderer_zoom_adjust(PixbufRenderer *pr, gdouble increment);
void pixbuf_renderer_zoom_adjust_at_point(PixbufRenderer *pr, gdouble increment, gint x, gint y);

void pixbuf_renderer_zoom_set(PixbufRenderer *pr, gdouble zoom);
gdouble pixbuf_renderer_zoom_get(PixbufRenderer *pr);
gdouble pixbuf_renderer_zoom_get_scale(PixbufRenderer *pr);

void pixbuf_renderer_zoom_set_limits(PixbufRenderer *pr, gdouble min, gdouble max);

/* sizes */

gint pixbuf_renderer_get_image_size(PixbufRenderer *pr, gint *width, gint *height);
gint pixbuf_renderer_get_scaled_size(PixbufRenderer *pr, gint *width, gint *height);

/* region of image in pixel coordinates */
gint pixbuf_renderer_get_visible_rect(PixbufRenderer *pr, GdkRectangle *rect);

/* actual size of the PixbufRenderer window minus borders,
 * x and y are the scroll offset and include zoom factor.
 */
gint pixbuf_renderer_get_virtual_rect(PixbufRenderer *pr, GdkRectangle *rect);

/* background color */

void pixbuf_renderer_set_color(PixbufRenderer *pr, GdkColor *color);
void pixbuf_renderer_set_black(PixbufRenderer *pr, gint black);

/* overlay */

gint pixbuf_renderer_overlay_add(PixbufRenderer *pr, GdkPixbuf *pixbuf, gint x, gint y,
				 gint relative, gint always);
void pixbuf_renderer_overlay_set(PixbufRenderer *pr, gint id, GdkPixbuf *pixbuf, gint x, gint y);
gint pixbuf_renderer_overlay_get(PixbufRenderer *pr, gint id, GdkPixbuf **pixbuf, gint *x, gint *y);
void pixbuf_renderer_overlay_remove(PixbufRenderer *pr, gint id);


#endif

