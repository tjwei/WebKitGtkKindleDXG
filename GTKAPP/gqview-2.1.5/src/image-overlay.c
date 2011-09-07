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

#include "gqview.h"
#include "image-overlay.h"

#include "collect.h"
#include "filelist.h"
#include "image.h"
#include "img-view.h"
#include "layout.h"
#include "pixbuf-renderer.h"
#include "pixbuf_util.h"


/*
 *----------------------------------------------------------------------------
 * image overlay
 *----------------------------------------------------------------------------
 */

typedef struct _OverlayStateData OverlayStateData;
struct _OverlayStateData {
	ImageWindow *imd;
	ImageState changed_states;

	gint show_info;
	gint show_status;

	gint ovl_info;

	gint icon_time[IMAGE_OSD_COUNT];
	gint icon_id[IMAGE_OSD_COUNT];

	gint idle_id;
	gint timer_id;
	gulong destroy_id;
};


typedef struct _OSDIcon OSDIcon;
struct _OSDIcon {
	gint reset;	/* reset on new image */
	gint x;		/* x, y offset */
	gint y;
	gchar *key;	/* inline pixbuf */
};

static OSDIcon osd_icons[] = {
	{  TRUE,   0,   0, NULL },			/* none */
	{  TRUE, -10, -10, NULL },			/* auto rotated */
	{  TRUE, -10, -10, NULL },			/* user rotated */
	{  TRUE, -40, -10, NULL },			/* color embedded */
	{  TRUE, -70, -10, NULL },			/* first image */
	{  TRUE, -70, -10, NULL },			/* last image */
	{ FALSE, -70, -10, NULL },			/* osd enabled */
	{ FALSE, 0, 0, NULL }
};

#define OSD_DATA "overlay-data"

#define OSD_INFO_X 10
#define OSD_INFO_Y -10

#define IMAGE_OSD_DEFAULT_DURATION 30


static void image_osd_timer_schedule(OverlayStateData *osd);


static GdkPixbuf *image_osd_info_render(ImageWindow *imd)
{
	GdkPixbuf *pixbuf;
	gint width, height;
	PangoLayout *layout;
	const gchar *name;
	gchar *name_escaped;
	gchar *text;
	gchar *size;
	gint n, t;
	CollectionData *cd;
	CollectInfo *info;
	gchar *ct;

	name = image_get_name(imd);
	if (name)
		{
		name_escaped = g_markup_escape_text(name, -1);
		}
	else
		{
		name_escaped = NULL;
		}

	cd = image_get_collection(imd, &info);
	if (cd)
		{
		gchar *buf;

		t = g_list_length(cd->list);
		n = g_list_index(cd->list, info) + 1;
		buf = g_markup_escape_text((cd->name) ? cd->name : _("Untitled"), -1);
		ct = g_strdup_printf("<i>%s</i>\n", buf);
		g_free(buf);
		}
	else
		{
		LayoutWindow *lw;

		lw = layout_find_by_image(imd);
		if (lw)
			{
			if (lw->slideshow)
				{
				n = g_list_length(lw->slideshow->list_done);
				t = n + g_list_length(lw->slideshow->list);
				if (n == 0) n = t;
				}
			else
				{
				t = layout_list_count(lw, NULL);
				n = layout_list_get_index(lw, image_get_path(lw->image)) + 1;
				}
			}
		else if (view_window_find_image(imd, &n, &t))
			{
			n++;
			}
		else
			{
			t = 1;
			n = 1;
			}

		if (n < 1) n = 1;
		if (t < 1) t = 1;

		ct = g_strdup("");
		}

	size = text_from_size_abrev(imd->size);
	if (!name_escaped)
		{
		text = g_strdup_printf(_("Untitled"));
		}
	else if (imd->unknown)
		{
		text = g_strdup_printf("%s(%d/%d) <b>%s</b>\n%s - %s", ct,
				       n, t, name_escaped,
				       text_from_time(imd->mtime), size);
		}
	else
		{
		gint w, h;

		if (imd->delay_flip &&
		    imd->il && imd->il->pixbuf &&
		    image_get_pixbuf(imd) != imd->il->pixbuf)
			{
			w = gdk_pixbuf_get_width(imd->il->pixbuf);
			h = gdk_pixbuf_get_height(imd->il->pixbuf);
			}
		else
			{
			pixbuf_renderer_get_image_size(PIXBUF_RENDERER(imd->pr), &w, &h);
			}

		text = g_strdup_printf("%s(%d/%d) <b>%s</b>\n%d x %d - %s - %s", ct,
				       n, t, name_escaped,
				       w, h,
				       text_from_time(imd->mtime), size);
		}
	g_free(size);
	g_free(ct);
	g_free(name_escaped);

	layout = gtk_widget_create_pango_layout(imd->pr, NULL);
	pango_layout_set_markup(layout, text, -1);
	g_free(text);

	pango_layout_get_pixel_size(layout, &width, &height);

	width += 10;
	height += 10;

	pixbuf = gdk_pixbuf_new(GDK_COLORSPACE_RGB, TRUE, 8, width, height);
	pixbuf_set_rect_fill(pixbuf, 3, 3, width-6, height-6, 240, 240, 240, 210);
	pixbuf_set_rect(pixbuf, 0, 0, width, height, 240, 240, 240, 80, 1, 1, 1, 1);
	pixbuf_set_rect(pixbuf, 1, 1, width-2, height-2, 240, 240, 240, 130, 1, 1, 1, 1);
	pixbuf_set_rect(pixbuf, 2, 2, width-4, height-4, 240, 240, 240, 180, 1, 1, 1, 1);
	pixbuf_pixel_set(pixbuf, 0, 0, 0, 0, 0, 0);
	pixbuf_pixel_set(pixbuf, width - 1, 0, 0, 0, 0, 0);
	pixbuf_pixel_set(pixbuf, 0, height - 1, 0, 0, 0, 0);
	pixbuf_pixel_set(pixbuf, width - 1, height - 1, 0, 0, 0, 0);

	pixbuf_draw_layout(pixbuf, layout, imd->pr, 5, 5, 0, 0, 0, 255);

	g_object_unref(G_OBJECT(layout));

	return pixbuf;
}

static GdkPixbuf *image_osd_icon_pixbuf(ImageOSDFlag flag)
{
	static GdkPixbuf **icons = NULL;
	GdkPixbuf *icon = NULL;

	if (!icons) icons = g_new0(GdkPixbuf *, IMAGE_OSD_COUNT);
	if (icons[flag]) return icons[flag];

	if (osd_icons[flag].key)
		{
		icon = pixbuf_inline(osd_icons[flag].key);
		}

	if (!icon)
		{
		icon = gdk_pixbuf_new(GDK_COLORSPACE_RGB, TRUE, 8, 24, 24);
		pixbuf_set_rect_fill(icon, 1, 1, 22, 22, 255, 255, 255, 200);
		pixbuf_set_rect(icon, 0, 0, 24, 24, 0, 0, 0, 128, 1, 1, 1, 1);
		switch (flag)
			{
			case IMAGE_OSD_ROTATE_AUTO:
				pixbuf_set_rect(icon, 3, 8, 11, 12,
						0, 0, 0, 255,
						3, 0, 3, 0);
				pixbuf_draw_triangle(icon, 14, 3, 6, 12,
						     20, 9, 14, 15, 14, 3,
						     0, 0, 0, 255);
				break;
			case IMAGE_OSD_ROTATE_USER:
				break;
			case IMAGE_OSD_COLOR:
				pixbuf_set_rect_fill(icon, 3, 3, 18, 6, 200, 0, 0, 255);
				pixbuf_set_rect_fill(icon, 3, 9, 18, 6, 0, 200, 0, 255);
				pixbuf_set_rect_fill(icon, 3, 15, 18, 6, 0, 0, 200, 255);
				break;
			case IMAGE_OSD_FIRST:
				pixbuf_set_rect(icon, 3, 3, 18, 18, 0, 0, 0, 200, 3, 3, 3, 0);
				pixbuf_draw_triangle(icon, 6, 5, 12, 6,
						     12, 5, 18, 11, 6, 11,
						     0, 0, 0, 255);
				break;
			case IMAGE_OSD_LAST:
				pixbuf_set_rect(icon, 3, 3, 18, 18, 0, 0, 0, 200, 3, 3, 0, 3);
				pixbuf_draw_triangle(icon, 6, 12, 12, 6,
						     12, 18, 6, 12, 18, 12,
						     0, 0, 0, 255);
				break;
			case IMAGE_OSD_ICON:
				pixbuf_set_rect_fill(icon, 11, 3, 3, 12, 0, 0, 0, 255);
				pixbuf_set_rect_fill(icon, 11, 17, 3, 3, 0, 0, 0, 255);
				break;
			default:
				break;
			}
		}

	icons[flag] = icon;

	return icon;
}

static void image_osd_icon_show(OverlayStateData *osd, ImageOSDFlag flag)
{
	GdkPixbuf *pixbuf;

	if (osd->icon_id[flag]) return;

	pixbuf = image_osd_icon_pixbuf(flag);
	if (!pixbuf) return;

	osd->icon_id[flag] = image_overlay_add(osd->imd, pixbuf,
					       osd_icons[flag].x, osd_icons[flag].y,
					       TRUE, FALSE);
}

static void image_osd_icon_hide(OverlayStateData *osd, ImageOSDFlag flag)
{
	if (osd->icon_id[flag])
		{
		image_overlay_remove(osd->imd, osd->icon_id[flag]);
		osd->icon_id[flag] = 0;
		}
}

static gint image_osd_update_cb(gpointer data)
{
	OverlayStateData *osd = data;

	if (osd->show_info)
		{
		if (osd->changed_states & IMAGE_STATE_IMAGE)
			{
			GdkPixbuf *pixbuf;

			pixbuf = image_osd_info_render(osd->imd);
			if (osd->ovl_info == 0)
				{
				osd->ovl_info = image_overlay_add(osd->imd, pixbuf,
								  OSD_INFO_X, OSD_INFO_Y, TRUE, FALSE);
				}
			else
				{
				image_overlay_set(osd->imd, osd->ovl_info, pixbuf, OSD_INFO_X, OSD_INFO_Y);
				}
			g_object_unref(pixbuf);
			}
		}
	else
		{
		if (osd->ovl_info)
			{
			image_overlay_remove(osd->imd, osd->ovl_info);
			osd->ovl_info = 0;
			}
		}

	if (osd->show_status)
		{
		gint i;

		if (osd->changed_states & IMAGE_STATE_IMAGE)
			{
			for (i = 0; i < IMAGE_OSD_COUNT; i++)
				{
				if (osd_icons[i].reset)	osd->icon_time[i] = 0;
				}
			}

		if (osd->changed_states & IMAGE_STATE_COLOR_ADJ)
			{
			osd->icon_time[IMAGE_OSD_COLOR] = IMAGE_OSD_DEFAULT_DURATION + 1;
			image_osd_timer_schedule(osd);
			}

		if (osd->changed_states & IMAGE_STATE_ROTATE_AUTO)
			{
			gint n = 0;

			if (osd->imd->state & IMAGE_STATE_ROTATE_AUTO)
				{
				n = 1;
				if (!osd->imd->cm) n += IMAGE_OSD_DEFAULT_DURATION;
				}

			osd->icon_time[IMAGE_OSD_ROTATE_AUTO] = n;
			image_osd_timer_schedule(osd);
			}

		for (i = 0; i < IMAGE_OSD_COUNT; i++)
			{
			if (osd->icon_time[i] > 0)
				{
				image_osd_icon_show(osd, i);
				}
			else
				{
				image_osd_icon_hide(osd, i);
				}
			}
		}
	else
		{
		gint i;

		for (i = 0; i < IMAGE_OSD_COUNT; i++)
			{
			image_osd_icon_hide(osd, i);
			}
		}

	osd->changed_states = IMAGE_STATE_NONE;
	osd->idle_id = -1;
	return FALSE;
}

static void image_osd_update_schedule(OverlayStateData *osd, gint force)
{
	if (force) osd->changed_states |= IMAGE_STATE_IMAGE;

	if (osd->idle_id == -1)
		{
		osd->idle_id = g_idle_add_full(G_PRIORITY_HIGH, image_osd_update_cb, osd, NULL);
		}
}

void image_osd_update(ImageWindow *imd)
{
	OverlayStateData *osd;

	if (!imd) return;

	osd = g_object_get_data(G_OBJECT(imd->pr), "IMAGE_OVERLAY_DATA");
	if (!osd) return;

	image_osd_update_schedule(osd, TRUE);
}

static gint image_osd_timer_cb(gpointer data)
{
	OverlayStateData *osd = data;
	gint done = TRUE;
	gint changed = FALSE;
	gint i;

	for (i = 0; i < IMAGE_OSD_COUNT; i++)
		{
		if (osd->icon_time[i] > 1)
			{
			osd->icon_time[i]--;
			if (osd->icon_time[i] < 2)
				{
				osd->icon_time[i] = 0;
				changed = TRUE;
				}
			else
				{
				done = FALSE;
				}
			}
		}

	if (changed) image_osd_update_schedule(osd, FALSE);

	if (done)
		{
		osd->timer_id = -1;
		return FALSE;
		}

	return TRUE;
}

static void image_osd_timer_schedule(OverlayStateData *osd)
{
	if (osd->timer_id == -1)
		{
		osd->timer_id = g_timeout_add(100, image_osd_timer_cb, osd);
		}
}

static void image_osd_state_cb(ImageWindow *imd, ImageState state, gpointer data)
{
	OverlayStateData *osd = data;

	osd->changed_states |= state;
	image_osd_update_schedule(osd, FALSE);
}

static void image_osd_free(OverlayStateData *osd)
{
	if (!osd) return;

	if (osd->idle_id != -1) g_source_remove(osd->idle_id);
	if (osd->timer_id != -1) g_source_remove(osd->timer_id);

	if (osd->imd)
		{
		gint i;

		g_object_set_data(G_OBJECT(osd->imd->pr), "IMAGE_OVERLAY_DATA", NULL);
		g_signal_handler_disconnect(osd->imd->pr, osd->destroy_id);

		image_set_state_func(osd->imd, NULL, NULL);
		image_overlay_remove(osd->imd, osd->ovl_info);

		for (i = 0; i < IMAGE_OSD_COUNT; i++)
			{
			image_osd_icon_hide(osd, i);
			}
		}

	g_free(osd);
}

static void image_osd_remove(ImageWindow *imd)
{
	OverlayStateData *osd;

	osd = g_object_get_data(G_OBJECT(imd->pr), "IMAGE_OVERLAY_DATA");
	image_osd_free(osd);
}

static void image_osd_destroy_cb(GtkWidget *widget, gpointer data)
{
	OverlayStateData *osd = data;

	osd->imd = NULL;
	image_osd_free(osd);
}

static void image_osd_enable(ImageWindow *imd, gint info, gint status)
{
	OverlayStateData *osd;

	osd = g_object_get_data(G_OBJECT(imd->pr), "IMAGE_OVERLAY_DATA");
	if (!osd)
		{
		osd = g_new0(OverlayStateData, 1);
		osd->imd = imd;
		osd->idle_id = -1;
		osd->timer_id = -1;

		osd->destroy_id = g_signal_connect(G_OBJECT(imd->pr), "destroy",
						   G_CALLBACK(image_osd_destroy_cb), osd);
		g_object_set_data(G_OBJECT(imd->pr), "IMAGE_OVERLAY_DATA", osd);

		image_set_state_func(osd->imd, image_osd_state_cb, osd);
		}

	if (osd->show_info != info ||
	    osd->show_status != status)
		{
		osd->show_info = info;
		osd->show_status = status;

		image_osd_update_schedule(osd, TRUE);
		}
}

void image_osd_set(ImageWindow *imd, gint info, gint status)
{
	if (!imd) return;

	if (!info && !status)
		{
		image_osd_remove(imd);
		return;
		}

	image_osd_enable(imd, info, status);
}

gint image_osd_get(ImageWindow *imd, gint *info, gint *status)
{
	OverlayStateData *osd;

	if (!imd) return FALSE;

	osd = g_object_get_data(G_OBJECT(imd->pr), "IMAGE_OVERLAY_DATA");
	if (!osd) return FALSE;

	if (info) *info = osd->show_info;
	if (status) *status = osd->show_status;

	return TRUE;
}

/* duration:
    0 = hide
    1 = show
   2+ = show for duration tenths of a second
   -1 = use default duration
 */
void image_osd_icon(ImageWindow *imd, ImageOSDFlag flag, gint duration)
{
	OverlayStateData *osd;

	if (!imd) return;

	osd = g_object_get_data(G_OBJECT(imd->pr), "IMAGE_OVERLAY_DATA");
	if (!osd) return;

	if (flag < IMAGE_OSD_NONE || flag >= IMAGE_OSD_COUNT) return;
	if (duration < 0) duration = IMAGE_OSD_DEFAULT_DURATION;
	if (duration > 1) duration += 1;

	osd->icon_time[flag] = duration;

	image_osd_update_schedule(osd, FALSE);
	image_osd_timer_schedule(osd);
}

