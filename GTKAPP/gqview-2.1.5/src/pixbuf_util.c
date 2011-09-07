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


#include "gqview.h"
#include "pixbuf_util.h"

#include "icons/icons_inline.h"

#include <math.h>


/*
 *-----------------------------------------------------------------------------
 * png save
 *-----------------------------------------------------------------------------
 */

gboolean pixbuf_to_file_as_png (GdkPixbuf *pixbuf, const char *filename)
{
	GError *error = NULL;
	gint ret;

	if (!pixbuf || !filename) return FALSE;

	ret = gdk_pixbuf_save(pixbuf, filename, "png", &error,
			      "tEXt::Software", "GQview "VERSION, NULL);

	if (error)
		{
		printf("Error saving png file: %s\n", error->message);
		g_error_free(error);
		}

	return ret;
}

/*
 *-----------------------------------------------------------------------------
 * jpeg save
 *-----------------------------------------------------------------------------
 */

gboolean pixbuf_to_file_as_jpg(GdkPixbuf *pixbuf, const gchar *filename, gint quality)
{
	GError *error = NULL;
	gchar *qbuf;
	gboolean ret;

	if (!pixbuf || !filename) return FALSE;

	if (quality == -1) quality = 75;
	if (quality < 1 || quality > 100)
		{
		printf("Jpeg not saved, invalid quality %d\n", quality);
		return FALSE;
		}

	qbuf = g_strdup_printf("%d", quality);
	ret = gdk_pixbuf_save(pixbuf, filename, "jpeg", &error, "quality", qbuf, NULL);
	g_free(qbuf);

	if (error)
		{
		printf("Error saving jpeg to %s\n%s\n", filename, error->message);
		g_error_free(error);
		}

	return ret;
}

/*
 *-----------------------------------------------------------------------------
 * pixbuf from inline
 *-----------------------------------------------------------------------------
 */

typedef struct _PixbufInline PixbufInline;
struct _PixbufInline
{
	const gchar *key;
	const guint8 *data;
};

static PixbufInline inline_pixbuf_data[] = {
	{ PIXBUF_INLINE_FOLDER_CLOSED,	folder_closed },
	{ PIXBUF_INLINE_FOLDER_LOCKED,	folder_locked },
	{ PIXBUF_INLINE_FOLDER_OPEN,	folder_open },
	{ PIXBUF_INLINE_FOLDER_UP,	folder_up },
	{ PIXBUF_INLINE_SCROLLER,	icon_scroller },
	{ PIXBUF_INLINE_BROKEN,		icon_broken },
	{ PIXBUF_INLINE_ICON,		gqview_icon },
	{ PIXBUF_INLINE_LOGO,		gqview_logo },
	{ PIXBUF_INLINE_ICON_FLOAT,	icon_float },
	{ PIXBUF_INLINE_ICON_THUMB,	icon_thumb },
	{ PIXBUF_INLINE_ICON_BOOK,	icon_book },
	{ PIXBUF_INLINE_ICON_CONFIG,	icon_config },
	{ PIXBUF_INLINE_ICON_TOOLS,	icon_tools },
	{ PIXBUF_INLINE_ICON_VIEW,	icon_view },
	{ NULL, NULL }
};

GdkPixbuf *pixbuf_inline(const gchar *key)
{
	gint i;

	if (!key) return NULL;

	i = 0;
	while (inline_pixbuf_data[i].key)
		{
		if (strcmp(inline_pixbuf_data[i].key, key) == 0)
			{
			return gdk_pixbuf_new_from_inline(-1, inline_pixbuf_data[i].data, FALSE, NULL);
			}
		i++;
		}

	printf("warning: inline pixbuf key \"%s\" not found.\n", key);

	return NULL;
}

/*
 *-----------------------------------------------------------------------------
 * misc utils
 *-----------------------------------------------------------------------------
 */

gint util_clip_region(gint x, gint y, gint w, gint h,
		      gint clip_x, gint clip_y, gint clip_w, gint clip_h,
		      gint *rx, gint *ry, gint *rw, gint *rh)
{
	if (clip_x + clip_w <= x ||
	    clip_x >= x + w ||
	    clip_y + clip_h <= y ||
	    clip_y >= y + h)
		{
		return FALSE;
		}

	*rx = MAX(x, clip_x);
	*rw = MIN((x + w), (clip_x + clip_w)) - *rx;

	*ry = MAX(y, clip_y);
	*rh = MIN((y + h), (clip_y + clip_h)) - *ry;

	return TRUE;
}

/*
 *-----------------------------------------------------------------------------
 * pixbuf rotation
 *-----------------------------------------------------------------------------
 */

static void pixbuf_copy_block_rotate(guchar *src, gint src_row_stride, gint x, gint y,
				     guchar *dest, gint dest_row_stride, gint w, gint h,
				     gint bytes_per_pixel, gint counter_clockwise)
{
	gint i, j;
	guchar *sp;
	guchar *dp;

	for (i = 0; i < h; i++)
		{
		sp = src + ((i + y) * src_row_stride) + (x * bytes_per_pixel);
		for (j = 0; j < w; j++)
			{
			if (counter_clockwise)
				{
				dp = dest + ((w - j - 1) * dest_row_stride) + (i * bytes_per_pixel);
				}
			else
				{
				dp = dest + (j * dest_row_stride) + ((h - i - 1) * bytes_per_pixel);
				}
			*(dp++) = *(sp++);	/* r */
			*(dp++) = *(sp++);	/* g */
			*(dp++) = *(sp++);	/* b */
			if (bytes_per_pixel == 4) *(dp) = *(sp++);	/* a */
			}
		}
	
}

static void pixbuf_copy_block(guchar *src, gint src_row_stride, gint w, gint h,
			      guchar *dest, gint dest_row_stride, gint x, gint y, gint bytes_per_pixel)
{
	gint i;
	guchar *sp;
	guchar *dp;

	for (i = 0; i < h; i++)
		{
		sp = src + (i * src_row_stride);
		dp = dest + ((y + i) * dest_row_stride) + (x * bytes_per_pixel);
		memcpy(dp, sp, w * bytes_per_pixel);
		}
}

#define ROTATE_BUFFER_WIDTH 48
#define ROTATE_BUFFER_HEIGHT 48

/*
 * Returns a copy of pixbuf src rotated 90 degrees clockwise or 90 counterclockwise
 *
 */
GdkPixbuf *pixbuf_copy_rotate_90(GdkPixbuf *src, gint counter_clockwise)
{
	GdkPixbuf *dest;
	gint has_alpha;
	gint sw, sh, srs;
	gint dw, dh, drs;
	guchar *s_pix;
        guchar *d_pix;
#if 0
	guchar *sp;
        guchar *dp;
#endif
	gint i, j;
	gint a;
	GdkPixbuf *buffer;
        guchar *b_pix;
	gint brs;
	gint w, h;

	if (!src) return NULL;

	sw = gdk_pixbuf_get_width(src);
	sh = gdk_pixbuf_get_height(src);
	has_alpha = gdk_pixbuf_get_has_alpha(src);
	srs = gdk_pixbuf_get_rowstride(src);
	s_pix = gdk_pixbuf_get_pixels(src);

	dw = sh;
	dh = sw;
	dest = gdk_pixbuf_new(GDK_COLORSPACE_RGB, has_alpha, 8, dw, dh);
	drs = gdk_pixbuf_get_rowstride(dest);
	d_pix = gdk_pixbuf_get_pixels(dest);

	a = (has_alpha ? 4 : 3);

	buffer = gdk_pixbuf_new(GDK_COLORSPACE_RGB, has_alpha, 8,
				ROTATE_BUFFER_WIDTH, ROTATE_BUFFER_HEIGHT);
	b_pix = gdk_pixbuf_get_pixels(buffer);
	brs = gdk_pixbuf_get_rowstride(buffer);

	for (i = 0; i < sh; i+= ROTATE_BUFFER_WIDTH)
		{
		w = MIN(ROTATE_BUFFER_WIDTH, (sh - i));
		for (j = 0; j < sw; j += ROTATE_BUFFER_HEIGHT)
			{
			gint x, y;

			h = MIN(ROTATE_BUFFER_HEIGHT, (sw - j));
			pixbuf_copy_block_rotate(s_pix, srs, j, i,
						 b_pix, brs, h, w,
						 a, counter_clockwise);

			if (counter_clockwise)
				{
				x = i;
				y = sw - h - j;
				}
			else
				{
				x = sh - w - i;
				y = j;
				}
			pixbuf_copy_block(b_pix, brs, w, h,
					  d_pix, drs, x, y, a);
			}
		}

	gdk_pixbuf_unref(buffer);

#if 0
	/* this is the simple version of rotation (roughly 2-4x slower) */

	for (i = 0; i < sh; i++)
		{
		sp = s_pix + (i * srs);
		for (j = 0; j < sw; j++)
			{
			if (counter_clockwise)
				{
				dp = d_pix + ((dh - j - 1) * drs) + (i * a);
				}
			else
				{
				dp = d_pix + (j * drs) + ((dw - i - 1) * a);
				}

			*(dp++) = *(sp++);	/* r */
			*(dp++) = *(sp++);	/* g */
			*(dp++) = *(sp++);	/* b */
			if (has_alpha) *(dp) = *(sp++);	/* a */
			}
		}
#endif

	return dest;
}

/*
 * Returns a copy of pixbuf mirrored and or flipped.
 * TO do a 180 degree rotations set both mirror and flipped TRUE
 * if mirror and flip are FALSE, result is a simple copy.
 */
GdkPixbuf *pixbuf_copy_mirror(GdkPixbuf *src, gint mirror, gint flip)
{
	GdkPixbuf *dest;
	gint has_alpha;
	gint w, h, srs;
	gint drs;
	guchar *s_pix;
        guchar *d_pix;
	guchar *sp;
        guchar *dp;
	gint i, j;
	gint a;

	if (!src) return NULL;

	w = gdk_pixbuf_get_width(src);
	h = gdk_pixbuf_get_height(src);
	has_alpha = gdk_pixbuf_get_has_alpha(src);
	srs = gdk_pixbuf_get_rowstride(src);
	s_pix = gdk_pixbuf_get_pixels(src);

	dest = gdk_pixbuf_new(GDK_COLORSPACE_RGB, has_alpha, 8, w, h);
	drs = gdk_pixbuf_get_rowstride(dest);
	d_pix = gdk_pixbuf_get_pixels(dest);

	a = has_alpha ? 4 : 3;

	for (i = 0; i < h; i++)
		{
		sp = s_pix + (i * srs);
		if (flip)
			{
			dp = d_pix + ((h - i - 1) * drs);
			}
		else
			{
			dp = d_pix + (i * drs);
			}
		if (mirror)
			{
			dp += (w - 1) * a;
			for (j = 0; j < w; j++)
				{
				*(dp++) = *(sp++);	/* r */
				*(dp++) = *(sp++);	/* g */
				*(dp++) = *(sp++);	/* b */
				if (has_alpha) *(dp) = *(sp++);	/* a */
				dp -= (a + 3);
				}
			}
		else
			{
			for (j = 0; j < w; j++)
				{
				*(dp++) = *(sp++);	/* r */
				*(dp++) = *(sp++);	/* g */
				*(dp++) = *(sp++);	/* b */
				if (has_alpha) *(dp++) = *(sp++);	/* a */
				}
			}
		}

	return dest;
}


/*
 *-----------------------------------------------------------------------------
 * pixbuf drawing (rectangles)
 *-----------------------------------------------------------------------------
 */

/*
 * Fills region of pixbuf at x,y over w,h
 * with colors red (r), green (g), blue (b)
 * applying alpha (a), use a=255 for solid.
 */
void pixbuf_draw_rect_fill(GdkPixbuf *pb,
			   gint x, gint y, gint w, gint h,
			   gint r, gint g, gint b, gint a)
{
	gint p_alpha;
	gint pw, ph, prs;
	guchar *p_pix;
	guchar *pp;
	gint i, j;

	if (!pb) return;

	pw = gdk_pixbuf_get_width(pb);
	ph = gdk_pixbuf_get_height(pb);

	if (x < 0 || x + w > pw) return;
	if (y < 0 || y + h > ph) return;

	p_alpha = gdk_pixbuf_get_has_alpha(pb);
	prs = gdk_pixbuf_get_rowstride(pb);
	p_pix = gdk_pixbuf_get_pixels(pb);

        for (i = 0; i < h; i++)
		{
		pp = p_pix + (y + i) * prs + (x * (p_alpha ? 4 : 3));
		for (j = 0; j < w; j++)
			{
			*pp = (r * a + *pp * (256-a)) >> 8;
			pp++;
			*pp = (g * a + *pp * (256-a)) >> 8;
			pp++;
			*pp = (b * a + *pp * (256-a)) >> 8;
			pp++;
			if (p_alpha) pp++;
			}
		}
}

void pixbuf_draw_rect(GdkPixbuf *pb,
		      gint x, gint y, gint w, gint h,
		      gint r, gint g, gint b, gint a,
		      gint left, gint right, gint top, gint bottom)
{
	pixbuf_draw_rect_fill(pb, x + left, y, w - left - right, top,
			      r, g, b ,a);
	pixbuf_draw_rect_fill(pb, x + w - right, y, right, h,
			      r, g, b ,a);
	pixbuf_draw_rect_fill(pb, x + left, y + h - bottom, w - left - right, bottom,
			      r, g, b ,a);
	pixbuf_draw_rect_fill(pb, x, y, left, h,
			      r, g, b ,a);
}

void pixbuf_set_rect_fill(GdkPixbuf *pb,
			  gint x, gint y, gint w, gint h,
			  gint r, gint g, gint b, gint a)
{
	gint p_alpha;
	gint pw, ph, prs;
	guchar *p_pix;
	guchar *pp;
	gint i, j;

	if (!pb) return;

	pw = gdk_pixbuf_get_width(pb);
	ph = gdk_pixbuf_get_height(pb);

	if (x < 0 || x + w > pw) return;
	if (y < 0 || y + h > ph) return;

	p_alpha = gdk_pixbuf_get_has_alpha(pb);
	prs = gdk_pixbuf_get_rowstride(pb);
	p_pix = gdk_pixbuf_get_pixels(pb);

        for (i = 0; i < h; i++)
		{
		pp = p_pix + (y + i) * prs + (x * (p_alpha ? 4 : 3));
		for (j = 0; j < w; j++)
			{
			*pp = r; pp++;
			*pp = g; pp++;
			*pp = b; pp++;
			if (p_alpha) { *pp = a; pp++; }
			}
		}
}

void pixbuf_set_rect(GdkPixbuf *pb,
		     gint x, gint y, gint w, gint h,
		     gint r, gint g, gint b, gint a,
		     gint left, gint right, gint top, gint bottom)
{
	pixbuf_set_rect_fill(pb, x + left, y, w - left - right, top,
			     r, g, b ,a);
	pixbuf_set_rect_fill(pb, x + w - right, y, right, h,
			     r, g, b ,a);
	pixbuf_set_rect_fill(pb, x + left, y + h - bottom, w - left - right, bottom,
			     r, g, b ,a);
	pixbuf_set_rect_fill(pb, x, y, left, h,
			     r, g, b ,a);
}

void pixbuf_pixel_set(GdkPixbuf *pb, gint x, gint y, gint r, gint g, gint b, gint a)
{
	guchar *buf;
	gint has_alpha;
	gint rowstride;
	guchar *p;

	if (x < 0 || x >= gdk_pixbuf_get_width(pb) ||
            y < 0 || y >= gdk_pixbuf_get_height(pb)) return;

	buf = gdk_pixbuf_get_pixels(pb);
	has_alpha = gdk_pixbuf_get_has_alpha(pb);
	rowstride = gdk_pixbuf_get_rowstride(pb);

        p = buf + (y * rowstride) + (x * (has_alpha ? 4 : 3));
	*p = r; p++;
	*p = g; p++;
	*p = b; p++;
	if (has_alpha) *p = a;
}


/*
 *-----------------------------------------------------------------------------
 * pixbuf text rendering
 *-----------------------------------------------------------------------------
 */

static void pixbuf_copy_font(GdkPixbuf *src, gint sx, gint sy,
			     GdkPixbuf *dest, gint dx, gint dy,
			     gint w, gint h,
			     guint8 r, guint8 g, guint8 b, guint8 a)
{
	gint sw, sh, srs;
	gint s_alpha;
	gint s_step;
	guchar *s_pix;
	gint dw, dh, drs;
	gint d_alpha;
	gint d_step;
	guchar *d_pix;

	guchar *sp;
	guchar *dp;
	gint i, j;

	if (!src || !dest) return;

	sw = gdk_pixbuf_get_width(src);
	sh = gdk_pixbuf_get_height(src);

	if (sx < 0 || sx + w > sw) return;
	if (sy < 0 || sy + h > sh) return;

	dw = gdk_pixbuf_get_width(dest);
	dh = gdk_pixbuf_get_height(dest);

	if (dx < 0 || dx + w > dw) return;
	if (dy < 0 || dy + h > dh) return;

	s_alpha = gdk_pixbuf_get_has_alpha(src);
	d_alpha = gdk_pixbuf_get_has_alpha(dest);
	srs = gdk_pixbuf_get_rowstride(src);
	drs = gdk_pixbuf_get_rowstride(dest);
	s_pix = gdk_pixbuf_get_pixels(src);
	d_pix = gdk_pixbuf_get_pixels(dest);

	s_step = (s_alpha) ? 4 : 3;
	d_step = (d_alpha) ? 4 : 3;

	for (i = 0; i < h; i++)
		{
		sp = s_pix + (sy + i) * srs + sx * s_step;
		dp = d_pix + (dy + i) * drs + dx * d_step;
		for (j = 0; j < w; j++)
			{
			if (*sp)
				{
				guint8 asub;

				asub = a * sp[0] / 255;
				*dp = (r * asub + *dp * (256-asub)) >> 8;
				dp++;
				asub = a * sp[1] / 255;
				*dp = (g * asub + *dp * (256-asub)) >> 8;
				dp++;
				asub = a * sp[2] / 255;
				*dp = (b * asub + *dp * (256-asub)) >> 8;
				dp++;

				if (d_alpha)
					{
					*dp = MAX(*dp, a * ((sp[0] + sp[1] + sp[2]) / 3) / 255);
					dp++;
					}
				}
			else
				{
				dp += d_step;
				}

			sp += s_step;
			}
		}
}

void pixbuf_draw_layout(GdkPixbuf *pixbuf, PangoLayout *layout, GtkWidget *widget,
			gint x, gint y,
			guint8 r, guint8 g, guint8 b, guint8 a)
{
	GdkPixmap *pixmap;
	GdkPixbuf *buffer;
	gint w, h;
	GdkGC *gc;
	gint sx, sy;
	gint dw, dh;

	if (!widget || !widget->window) return;

	pango_layout_get_pixel_size(layout, &w, &h);
	if (w < 1 || h < 1) return;

	pixmap = gdk_pixmap_new(widget->window, w, h, -1);

	gc = gdk_gc_new(widget->window);
	gdk_gc_copy(gc, widget->style->black_gc);
	gdk_draw_rectangle(pixmap, gc, TRUE, 0, 0, w, h);
	gdk_gc_copy(gc, widget->style->white_gc);
	gdk_draw_layout(pixmap, gc, 0, 0, layout);
	g_object_unref(gc);

	buffer = gdk_pixbuf_new(GDK_COLORSPACE_RGB, FALSE, 8, w, h);
	gdk_pixbuf_get_from_drawable(buffer, pixmap,
				     gdk_drawable_get_colormap(widget->window),
				     0, 0, 0, 0, w, h);
	g_object_unref(pixmap);

	sx = 0;
	sy = 0;
	dw = gdk_pixbuf_get_width(pixbuf);
	dh = gdk_pixbuf_get_height(pixbuf);

	if (x < 0)
		{
		w += x;
		sx = -x;
		x = 0;
		}

	if (y < 0)
		{
		h += y;
		sy = -y;
		y = 0;
		}

	if (x + w > dw)	w = dw - x;
	if (y + h > dh) h = dh - y;

	pixbuf_copy_font(buffer, sx, sy,
			 pixbuf, x, y, w, h,
			 r, g, b, a);

	g_object_unref(buffer);
}

/*
 *-----------------------------------------------------------------------------
 * pixbuf drawing (triangle)
 *-----------------------------------------------------------------------------
 */

void util_clip_triangle(gint x1, gint y1, gint x2, gint y2, gint x3, gint y3,
			gint *rx, gint *ry, gint *rw, gint *rh)
{
	gint tx, ty, tw, th;

	tx = MIN(x1, x2);
	tx = MIN(tx, x3);
	ty = MIN(y1, y2);
	ty = MIN(ty, y3);
	tw = MAX(abs(x1 - x2), abs(x2 - x3));
	tw = MAX(tw, abs(x3 - x1));
	th = MAX(abs(y1 - y2), abs(y2 - y3));
	th = MAX(th, abs(y3 - y1));

	*rx = tx;
	*ry = ty;
	*rw = tw;
	*rh = th;
}

void pixbuf_draw_triangle(GdkPixbuf *pb,
			  gint clip_x, gint clip_y, gint clip_w, gint clip_h,
			  gint x1, gint y1, gint x2, gint y2, gint x3, gint y3,
			  guint8 r, guint8 g, guint8 b, guint8 a)
{
	gint p_alpha;
	gint pw, ph, prs;
	gint rx, ry, rw, rh;
	gint tx, ty, tw, th;
	gint fx1, fy1;
	gint fx2, fy2;
	gint fw, fh;
	guchar *p_pix;
	guchar *pp;
	gint p_step;
	gdouble slope1, slope2;
	gint slope1_x, slope1_y;
	gint y;
	gint t;
	gint middle = FALSE;

	if (!pb) return;

	pw = gdk_pixbuf_get_width(pb);
	ph = gdk_pixbuf_get_height(pb);

	if (!util_clip_region(0, 0, pw, ph,
			      clip_x, clip_y, clip_w, clip_h,
			      &rx, &ry, &rw, &rh)) return;

	util_clip_triangle(x1, y1, x2, y2, x3, y3,
			   &tx, &ty, &tw, &th);

	if (!util_clip_region(rx, ry, rw, rh,
			      tx, ty, tw, th,
			      &fx1, &fy1, &fw, &fh)) return;
	fx2 = fx1 + fw;
	fy2 = fy1 + fh;

	p_alpha = gdk_pixbuf_get_has_alpha(pb);
	prs = gdk_pixbuf_get_rowstride(pb);
	p_pix = gdk_pixbuf_get_pixels(pb);

	p_step = (p_alpha) ? 4 : 3;

	if (y1 > y2)
		{
		t = x1; x1 = x2; x2 = t;
		t = y1; y1 = y2; y2 = t;
		}
	if (y2 > y3)
		{
		t = x2; x2 = x3; x3 = t;
		t = y2; y2 = y3; y3 = t;
		}
	if (y1 > y2)
		{
		t = x1; x1 = x2; x2 = t;
		t = y1; y1 = y2; y2 = t;
		}

	slope1 = (gdouble)(y2 - y1);
	if (slope1) slope1 = (gdouble)(x2 - x1) / slope1;
	slope1_x = x1;
	slope1_y = y1;
	slope2 = (gdouble)(y3 - y1);
	if (slope2) slope2 = (gdouble)(x3 - x1) / slope2;

	for (y = fy1; y < fy2; y++)
		{
		gint xa, xb;

		if (!middle && y > y2)
			{
			slope1 = (gdouble)(y3 - y2);
			if (slope1) slope1 = (gdouble)(x3 - x2) / slope1;
			slope1_x = x2;
			slope1_y = y2;

			middle = TRUE;
			}

		xa = slope1_x + ((gdouble)slope1 * (y - slope1_y) + 0.5);
		xb = x1 + ((gdouble)slope2 * (y - y1) + 0.5);

		if (xa > xb)
			{
			t = xa; xa = xb; xb = t;
			}

		xa = CLAMP(xa, fx1, fx2);
		xb = CLAMP(xb, fx1, fx2);

		pp = p_pix + y * prs + xa * p_step;

		while (xa < xb)
			{
			*pp = (r * a + *pp * (256-a)) >> 8;
			pp++;
			*pp = (g * a + *pp * (256-a)) >> 8;
			pp++;
			*pp = (b * a + *pp * (256-a)) >> 8;
			pp++;
			if (p_alpha) pp++;

			xa++;
			}
		}
}

/*
 *-----------------------------------------------------------------------------
 * pixbuf drawing (line)
 *-----------------------------------------------------------------------------
 */

static gint util_clip_line(gdouble clip_x, gdouble clip_y, gdouble clip_w, gdouble clip_h,
			   gdouble x1, gdouble y1, gdouble x2, gdouble y2,
			   gdouble *rx1, gdouble *ry1, gdouble *rx2, gdouble *ry2)
{
	gint flip = FALSE;
	gdouble d;

	if (x1 > x2)
		{
		gdouble t;

		t = x1; x1 = x2; x2 = t;
		t = y1; y1 = y2; y2 = t;
		flip = TRUE;
		}

	if (x2 < clip_x || x1 > clip_x + clip_w) return FALSE;

	if (y1 < y2)
		{
		if (y2 < clip_y || y1 > clip_y + clip_h) return FALSE;
		}
	else
		{
		if (y1 < clip_y || y2 > clip_y + clip_h) return FALSE;
		}

#if 0
	if (x1 >= clip_x && x2 <= clip_x + clip_w)
		{
		if (y1 < y2)
			{
			if (y1 >= clip_y && y2 <= clip_y + clip_h) return TRUE;
			}
		else
			{
			if (y2 >= clip_y && y1 <= clip_y + clip_h) return TRUE;
			}
		}
#endif

	d = x2 - x1;
	if (d > 0.0)
		{
		gdouble slope;

		slope = (y2 - y1) / d;
		if (x1 < clip_x)
			{
			y1 = y1 + slope * (clip_x - x1);
			x1 = clip_x;
			}
		if (x2 > clip_x + clip_w)
			{
			y2 = y2 + slope * (clip_x + clip_w - x2);
			x2 = clip_x + clip_w;
			}
		}

	if (y1 < y2)
		{
		if (y2 < clip_y || y1 > clip_y + clip_h) return FALSE;
		}
	else
		{
		gdouble t;

		if (y1 < clip_y || y2 > clip_y + clip_h) return FALSE;

		t = x1; x1 = x2; x2 = t;
		t = y1; y1 = y2; y2 = t;
		flip = !flip;
		}

	d = y2 - y1;
	if (d > 0.0)
		{
		gdouble slope;

		slope = (x2 - x1) / d;
		if (y1 < clip_y)
			{
			x1 = x1 + slope * (clip_y - y1);
			y1 = clip_y;
			}
		if (y2 > clip_y + clip_h)
			{
			x2 = x2 + slope * (clip_y + clip_h - y2);
			y2 = clip_y + clip_h;
			}
		}

	if (flip)
		{
		*rx1 = x2;
		*ry1 = y2;
		*rx2 = x1;
		*ry2 = y1;
		}
	else
		{
		*rx1 = x1;
		*ry1 = y1;
		*rx2 = x2;
		*ry2 = y2;
		}

	return TRUE;
}

void pixbuf_draw_line(GdkPixbuf *pb,
		      gint clip_x, gint clip_y, gint clip_w, gint clip_h,
		      gint x1, gint y1, gint x2, gint y2,
		      guint8 r, guint8 g, guint8 b, guint8 a)
{
	gint p_alpha;
	gint pw, ph, prs;
	gint rx, ry, rw, rh;
	gdouble rx1, ry1, rx2, ry2;
	guchar *p_pix;
	guchar *pp;
	gint p_step;
	gdouble slope;
	gdouble x, y;
	gint px, py;
	gint cx1, cy1, cx2, cy2;

	if (!pb) return;

	pw = gdk_pixbuf_get_width(pb);
	ph = gdk_pixbuf_get_height(pb);

	if (!util_clip_region(0, 0, pw, ph,
			      clip_x, clip_y, clip_w, clip_h,
			      &rx, &ry, &rw, &rh)) return;
	if (!util_clip_line((gdouble)rx, (gdouble)ry, (gdouble)rw, (gdouble)rh,
			    (gdouble)x1, (gdouble)y1, (gdouble)x2, (gdouble)y2,
			    &rx1, &ry1, &rx2, &ry2)) return;

	cx1 = rx;
	cy1 = ry;
	cx2 = rx + rw;
	cy2 = ry + rh;

	p_alpha = gdk_pixbuf_get_has_alpha(pb);
	prs = gdk_pixbuf_get_rowstride(pb);
	p_pix = gdk_pixbuf_get_pixels(pb);

	p_step = (p_alpha) ? 4 : 3;

	if (fabs(rx2 - rx1) > fabs(ry2 - ry1))
		{
		if (rx1 > rx2)
			{
			gdouble t;
			t = rx1; rx1 = rx2; rx2 = t;
			t = ry1; ry1 = ry2; ry2 = t;
			}

		slope = rx2 - rx1;
		if (slope != 0.0) slope = (ry2 - ry1) / slope;
		for (x = rx1; x < rx2; x += 1.0)
			{
			px = (gint)(x + 0.5);
			py = (gint)(ry1 + (x - rx1) * slope + 0.5);

			if (px >=  cx1 && px < cx2 && py >= cy1 && py < cy2)
				{
				pp = p_pix + py * prs + px * p_step;
				*pp = (r * a + *pp * (256-a)) >> 8;
				pp++;
				*pp = (g * a + *pp * (256-a)) >> 8;
				pp++;
				*pp = (b * a + *pp * (256-a)) >> 8;
				}
			}
		}
	else
		{
		if (ry1 > ry2)
			{
			gdouble t;
			t = rx1; rx1 = rx2; rx2 = t;
			t = ry1; ry1 = ry2; ry2 = t;
			}

		slope = ry2 - ry1;
		if (slope != 0.0) slope = (rx2 - rx1) / slope;
		for (y = ry1; y < ry2; y += 1.0)
			{
			px = (gint)(rx1 + (y - ry1) * slope + 0.5);
			py = (gint)(y + 0.5);

			if (px >=  cx1 && px < cx2 && py >= cy1 && py < cy2)
				{
				pp = p_pix + py * prs + px * p_step;
				*pp = (r * a + *pp * (256-a)) >> 8;
				pp++;
				*pp = (g * a + *pp * (256-a)) >> 8;
				pp++;
				*pp = (b * a + *pp * (256-a)) >> 8;
				}
			}
		}
}

/*
 *-----------------------------------------------------------------------------
 * pixbuf drawing (fades and shadows)
 *-----------------------------------------------------------------------------
 */

static void pixbuf_draw_fade_linear(guchar *p_pix, gint prs, gint p_alpha,
				    gint s, gint vertical, gint border,
			 	    gint x1, gint y1, gint x2, gint y2,
				    guint8 r, guint8 g, guint8 b, guint8 a)
{
	guchar *pp;
	gint p_step;
	guint8 n = a;
	gint i, j;

	p_step = (p_alpha) ? 4 : 3;
	for (j = y1; j < y2; j++)
		{
		pp = p_pix + j * prs + x1 * p_step;
		if (!vertical) n = a - a * abs(j - s) / border;
		for (i = x1; i < x2; i++)
			{
			if (vertical) n = a - a * abs(i - s) / border;
			*pp = (r * n + *pp * (256-n)) >> 8;
			pp++;
			*pp = (g * n + *pp * (256-n)) >> 8;
			pp++;
			*pp = (b * n + *pp * (256-n)) >> 8;
			pp++;
			if (p_alpha) pp++;
			}
		}
}

static void pixbuf_draw_fade_radius(guchar *p_pix, gint prs, gint p_alpha,
				    gint sx, gint sy, gint border,
			 	    gint x1, gint y1, gint x2, gint y2,
				    guint8 r, guint8 g, guint8 b, guint8 a)
{
	guchar *pp;
	gint p_step;
	gint i, j;

	p_step = (p_alpha) ? 4 : 3;
	for (j = y1; j < y2; j++)
		{
		pp = p_pix + j * prs + x1 * p_step;
		for (i = x1; i < x2; i++)
			{
			guint8 n;
			gint r;

			r = MIN(border, (gint)sqrt((i-sx)*(i-sx) + (j-sy)*(j-sy)));
			n = a - a * r / border;
			*pp = (r * n + *pp * (256-n)) >> 8;
			pp++;
			*pp = (g * n + *pp * (256-n)) >> 8;
			pp++;
			*pp = (b * n + *pp * (256-n)) >> 8;
			pp++;
			if (p_alpha) pp++;
			}
		}
}

void pixbuf_draw_shadow(GdkPixbuf *pb,
			gint clip_x, gint clip_y, gint clip_w, gint clip_h,
			gint x, gint y, gint w, gint h, gint border,
			guint8 r, guint8 g, guint8 b, guint8 a)
{
	gint p_alpha;
	gint pw, ph, prs;
	gint rx, ry, rw, rh;
	gint fx, fy, fw, fh;
	guchar *p_pix;

	if (!pb) return;

	pw = gdk_pixbuf_get_width(pb);
	ph = gdk_pixbuf_get_height(pb);

	if (!util_clip_region(0, 0, pw, ph,
			      clip_x, clip_y, clip_w, clip_h,
			      &rx, &ry, &rw, &rh)) return;

	p_alpha = gdk_pixbuf_get_has_alpha(pb);
	prs = gdk_pixbuf_get_rowstride(pb);
	p_pix = gdk_pixbuf_get_pixels(pb);

	if (util_clip_region(x + border, y + border, w - border * 2, h - border * 2,
			     rx, ry, rw, rh,
			     &fx, &fy, &fw, &fh))
		{
		pixbuf_draw_rect_fill(pb, fx, fy, fw, fh, r, g, b, a);
		}

	if (border < 1) return;

	if (util_clip_region(x, y + border, border, h - border * 2,
			     rx, ry, rw, rh,
			     &fx, &fy, &fw, &fh))
		{
		pixbuf_draw_fade_linear(p_pix, prs, p_alpha,
					x + border, TRUE, border,
					fx, fy, fx + fw, fy + fh,
					r, g, b, a);
		}
	if (util_clip_region(x + w - border, y + border, border, h - border * 2,
			     rx, ry, rw, rh,
			     &fx, &fy, &fw, &fh))
		{
		pixbuf_draw_fade_linear(p_pix, prs, p_alpha,
					x + w - border, TRUE, border,
					fx, fy, fx + fw, fy + fh,
					r, g, b, a);
		}
	if (util_clip_region(x + border, y, w - border * 2, border,
			     rx, ry, rw, rh,
			     &fx, &fy, &fw, &fh))
		{
		pixbuf_draw_fade_linear(p_pix, prs, p_alpha,
					y + border, FALSE, border,
					fx, fy, fx + fw, fy + fh,
					r, g, b, a);
		}
	if (util_clip_region(x + border, y + h - border, w - border * 2, border,
			     rx, ry, rw, rh,
			     &fx, &fy, &fw, &fh))
		{
		pixbuf_draw_fade_linear(p_pix, prs, p_alpha,
					y + h - border, FALSE, border,
					fx, fy, fx + fw, fy + fh,
					r, g, b, a);
		}
	if (util_clip_region(x, y, border, border,
			     rx, ry, rw, rh,
			     &fx, &fy, &fw, &fh))
		{
		pixbuf_draw_fade_radius(p_pix, prs, p_alpha,
					x + border, y + border, border,
					fx, fy, fx + fw, fy + fh,
					r, g, b, a);
		}
	if (util_clip_region(x + w - border, y, border, border,
			     rx, ry, rw, rh,
			     &fx, &fy, &fw, &fh))
		{
		pixbuf_draw_fade_radius(p_pix, prs, p_alpha,
					x + w - border, y + border, border,
					fx, fy, fx + fw, fy + fh,
					r, g, b, a);
		}
	if (util_clip_region(x, y + h - border, border, border,
			     rx, ry, rw, rh,
			     &fx, &fy, &fw, &fh))
		{
		pixbuf_draw_fade_radius(p_pix, prs, p_alpha,
					x + border, y + h - border, border,
					fx, fy, fx + fw, fy + fh,
					r, g, b, a);
		}
	if (util_clip_region(x + w - border, y + h - border, border, border,
			     rx, ry, rw, rh,
			     &fx, &fy, &fw, &fh))
		{
		pixbuf_draw_fade_radius(p_pix, prs, p_alpha,
					x + w - border, y + h - border, border,
					fx, fy, fx + fw, fy + fh,
					r, g, b, a);
		}
}


/*
 *-----------------------------------------------------------------------------
 * pixbuf color alterations
 *-----------------------------------------------------------------------------
 */

void pixbuf_desaturate_rect(GdkPixbuf *pb,
			    gint x, gint y, gint w, gint h)
{
	gint p_alpha;
	gint pw, ph, prs;
	guchar *p_pix;
	guchar *pp;
	gint i, j;

	if (!pb) return;

	pw = gdk_pixbuf_get_width(pb);
	ph = gdk_pixbuf_get_height(pb);

	if (x < 0 || x + w > pw) return;
	if (y < 0 || y + h > ph) return;

	p_alpha = gdk_pixbuf_get_has_alpha(pb);
	prs = gdk_pixbuf_get_rowstride(pb);
	p_pix = gdk_pixbuf_get_pixels(pb);

        for (i = 0; i < h; i++)
		{
		pp = p_pix + (y + i) * prs + (x * (p_alpha ? 4 : 3));
		for (j = 0; j < w; j++)
			{
			guint8 grey;

			grey = (pp[0] + pp[1] + pp[2]) / 3;
			*pp = grey;
			pp++;
			*pp = grey;
			pp++;
			*pp = grey;
			pp++;
			if (p_alpha) pp++;
			}
		}
}


