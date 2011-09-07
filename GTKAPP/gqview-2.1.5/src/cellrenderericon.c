/* cellrenderericon.c, based on:
 *
 * gtkcellrendererpixbuf.c
 * Copyright (C) 2000  Red Hat, Inc.,  Jonathan Blandford <jrb@redhat.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#include <stdlib.h>
#include "cellrenderericon.h"
#include "intl.h"


#define FIXED_ICON_SIZE_MAX 512

static void gqv_cell_renderer_icon_get_property(GObject		*object,
					        guint		param_id,
					        GValue		*value,
					        GParamSpec	*pspec);
static void gqv_cell_renderer_icon_set_property(GObject		*object,
						guint		param_id,
						const GValue	*value,
						GParamSpec	*pspec);
static void gqv_cell_renderer_icon_init(GQvCellRendererIcon *celltext);
static void gqv_cell_renderer_icon_class_init(GQvCellRendererIconClass *class);
static void gqv_cell_renderer_icon_finalize(GObject *object);
static void gqv_cell_renderer_icon_get_size(GtkCellRenderer	*cell,
					    GtkWidget		*widget,
					    GdkRectangle	*rectangle,
					    gint		*x_offset,
					    gint		*y_offset,
					    gint		*width,
					    gint		*height);
static void gqv_cell_renderer_icon_render(GtkCellRenderer	*cell,
					   GdkWindow		*window,
					   GtkWidget		*widget,
					   GdkRectangle		*background_area,
					   GdkRectangle		*cell_area,
					   GdkRectangle		*expose_area,
					   GtkCellRendererState	flags);


enum {
	PROP_ZERO,
	PROP_PIXBUF,
	PROP_TEXT,
	PROP_BACKGROUND_GDK,
	PROP_FOREGROUND_GDK,
	PROP_FOCUSED,
	PROP_FIXED_WIDTH,
	PROP_FIXED_HEIGHT,

	PROP_BACKGROUND_SET,
	PROP_FOREGROUND_SET,
	PROP_SHOW_TEXT
};

static gpointer parent_class;

GType
gqv_cell_renderer_icon_get_type (void)
{
	static GType cell_icon_type = 0;

	if (!cell_icon_type)
		{
		static const GTypeInfo cell_icon_info =
			{
			sizeof (GQvCellRendererIconClass),
			NULL,		/* base_init */
			NULL,		/* base_finalize */
			(GClassInitFunc) gqv_cell_renderer_icon_class_init,
			NULL,		/* class_finalize */
			NULL,		/* class_data */
			sizeof (GQvCellRendererIcon),
			0,		/* n_preallocs */
		(GInstanceInitFunc) gqv_cell_renderer_icon_init,
		};

	cell_icon_type = g_type_register_static(GTK_TYPE_CELL_RENDERER,
					        "GQvCellRendererIcon",
						&cell_icon_info, 0);
	}

	return cell_icon_type;
}

static void
gqv_cell_renderer_icon_init (GQvCellRendererIcon *cellicon)
{
	GTK_CELL_RENDERER(cellicon)->xpad = 2;
	GTK_CELL_RENDERER(cellicon)->ypad = 2;
}

static void
gqv_cell_renderer_icon_class_init (GQvCellRendererIconClass *class)
{
	GObjectClass *object_class = G_OBJECT_CLASS (class);
	GtkCellRendererClass *cell_class = GTK_CELL_RENDERER_CLASS (class);

	parent_class = g_type_class_peek_parent (class);

	object_class->finalize = gqv_cell_renderer_icon_finalize;

	object_class->get_property = gqv_cell_renderer_icon_get_property;
	object_class->set_property = gqv_cell_renderer_icon_set_property;

	cell_class->get_size = gqv_cell_renderer_icon_get_size;
	cell_class->render = gqv_cell_renderer_icon_render;

	g_object_class_install_property(object_class,
					PROP_PIXBUF,
					g_param_spec_object("pixbuf",
							_("Pixbuf Object"),
							_("The pixbuf to render"),
							GDK_TYPE_PIXBUF,
							G_PARAM_READWRITE));

	g_object_class_install_property(object_class,
					PROP_TEXT,
					g_param_spec_string("text",
							_("Text"),
							_("Text to render"),
							NULL,
							G_PARAM_READWRITE));

	g_object_class_install_property(object_class,
					PROP_BACKGROUND_GDK,
					g_param_spec_boxed("background_gdk",
							_("Background color"),
							_("Background color as a GdkColor"),
							GDK_TYPE_COLOR,
							G_PARAM_READWRITE));

	g_object_class_install_property(object_class,
					PROP_FOREGROUND_GDK,
					g_param_spec_boxed("foreground_gdk",
							_("Foreground color"),
							_("Foreground color as a GdkColor"),
							GDK_TYPE_COLOR,
							G_PARAM_READWRITE));

	g_object_class_install_property(object_class,
					PROP_FOCUSED,
					g_param_spec_boolean ("has_focus",
							_("Focus"),
							_("Draw focus indicator"),
							FALSE,
							G_PARAM_READWRITE));

	g_object_class_install_property(object_class,
					PROP_FIXED_WIDTH,
					g_param_spec_int("fixed_width",
							_("Fixed width"),
							_("Width of cell"),
							-1, FIXED_ICON_SIZE_MAX,
							-1,
							G_PARAM_READWRITE));

	g_object_class_install_property(object_class,
					PROP_FIXED_HEIGHT,
					g_param_spec_int("fixed_height",
							_("Fixed height"),
							_("Height of icon excluding text"),
							-1, FIXED_ICON_SIZE_MAX,
							-1,
							G_PARAM_READWRITE));

	g_object_class_install_property(object_class,
					PROP_BACKGROUND_SET,
					g_param_spec_boolean("background_set",
							_("Background set"),
							_("Whether this tag affects the background color"),
							FALSE,
							G_PARAM_READWRITE));

	g_object_class_install_property(object_class,
					PROP_FOREGROUND_SET,
					g_param_spec_boolean ("foreground_set",
							_("Foreground set"),
							_("Whether this tag affects the foreground color"),
							FALSE,
							G_PARAM_READWRITE));

	g_object_class_install_property(object_class,
					PROP_SHOW_TEXT,
					g_param_spec_boolean("show_text",
							_("Show text"),
							_("Whether the text is displayed"),
							TRUE,
							G_PARAM_READWRITE));
}

static void
gqv_cell_renderer_icon_finalize (GObject *object)
{
	GQvCellRendererIcon *cellicon = GQV_CELL_RENDERER_ICON (object);

	if (cellicon->pixbuf) g_object_unref (cellicon->pixbuf);

	g_free(cellicon->text);

	(* G_OBJECT_CLASS (parent_class)->finalize) (object);
}

static void
gqv_cell_renderer_icon_get_property(GObject	*object,
				    guint	param_id,
				    GValue	*value,
				    GParamSpec	*pspec)
{
	GQvCellRendererIcon *cellicon = GQV_CELL_RENDERER_ICON (object);
  
	switch (param_id)
		{
		case PROP_PIXBUF:
		g_value_set_object(value,
      				   cellicon->pixbuf ? G_OBJECT (cellicon->pixbuf) : NULL);
		break;
	case PROP_TEXT:
		g_value_set_string (value, cellicon->text);
		break;
	case PROP_BACKGROUND_GDK:
		{
		GdkColor color;

		color.red = cellicon->background.red;
		color.green = cellicon->background.green;
		color.blue = cellicon->background.blue;

		g_value_set_boxed (value, &color);
		}
		break;
	case PROP_FOREGROUND_GDK:
		{
		GdkColor color;

		color.red = cellicon->foreground.red;
		color.green = cellicon->foreground.green;
		color.blue = cellicon->foreground.blue;

		g_value_set_boxed (value, &color);
		}
		break;
	case PROP_FOCUSED:
		g_value_set_boolean (value, cellicon->focused);
		break;
	case PROP_FIXED_WIDTH:
		g_value_set_int(value, cellicon->fixed_width);
		break;
	case PROP_FIXED_HEIGHT:
		g_value_set_int(value, cellicon->fixed_height);
		break;
	case PROP_BACKGROUND_SET:
		g_value_set_boolean(value, cellicon->background_set);
		break;
	case PROP_FOREGROUND_SET:
		g_value_set_boolean(value, cellicon->foreground_set);
		break;
	case PROP_SHOW_TEXT:
		g_value_set_boolean(value, cellicon->show_text);
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, param_id, pspec);
		break;
	}
}

static void
set_bg_color (GQvCellRendererIcon *cellicon,
	      GdkColor		  *color)
{
	if (color)
		{
		if (!cellicon->background_set)
			{
			cellicon->background_set = TRUE;
			g_object_notify(G_OBJECT(cellicon), "background_set");
			}

		cellicon->background.red = color->red;
		cellicon->background.green = color->green;
		cellicon->background.blue = color->blue;
		}
	else
		{
		if (cellicon->background_set)
			{
			cellicon->background_set = FALSE;
			g_object_notify(G_OBJECT(cellicon), "background_set");
			}
		}
}

static void set_fg_color (GQvCellRendererIcon *cellicon,
			  GdkColor	      *color)
{
	if (color)
		{
		if (!cellicon->foreground_set)
			{
			cellicon->foreground_set = TRUE;
			g_object_notify(G_OBJECT(cellicon), "foreground_set");
			}

		cellicon->foreground.red = color->red;
		cellicon->foreground.green = color->green;
		cellicon->foreground.blue = color->blue;
		}
	else
		{
		if (cellicon->foreground_set)
			{
			cellicon->foreground_set = FALSE;
			g_object_notify(G_OBJECT(cellicon), "foreground_set");
			}
		}
}

static void
gqv_cell_renderer_icon_set_property(GObject		*object,
				    guint		param_id,
				    const GValue	*value,
				    GParamSpec		*pspec)
{
	GQvCellRendererIcon *cellicon = GQV_CELL_RENDERER_ICON (object);
  
	switch (param_id)
		{
		case PROP_PIXBUF:
			{
			GdkPixbuf *pixbuf;

			pixbuf = (GdkPixbuf*) g_value_get_object (value);
			if (pixbuf) g_object_ref (pixbuf);
			if (cellicon->pixbuf) g_object_unref (cellicon->pixbuf);
			cellicon->pixbuf = pixbuf;
			}
		break;
	case PROP_TEXT:
		{
		gchar *text;

		text = cellicon->text;
		cellicon->text = g_strdup(g_value_get_string(value));
		g_free(text);

		g_object_notify(object, "text");
		}
		break;
	case PROP_BACKGROUND_GDK:
		set_bg_color(cellicon, g_value_get_boxed(value));
		break;
	case PROP_FOREGROUND_GDK:
		set_fg_color(cellicon, g_value_get_boxed(value));
		break;
	case PROP_FOCUSED:
		cellicon->focused = g_value_get_boolean(value);
		break;
	case PROP_FIXED_WIDTH:
		cellicon->fixed_width = g_value_get_int(value);
		break;
	case PROP_FIXED_HEIGHT:
		cellicon->fixed_height = g_value_get_int(value);
		break;
	case PROP_BACKGROUND_SET:
		cellicon->background_set = g_value_get_boolean(value);
		break;
	case PROP_FOREGROUND_SET:
		cellicon->foreground_set = g_value_get_boolean(value);
		break;
	case PROP_SHOW_TEXT:
		cellicon->show_text = g_value_get_boolean(value);
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, param_id, pspec);
		break;
    }
}

static PangoLayout *
gqv_cell_renderer_icon_get_layout(GQvCellRendererIcon *cellicon, GtkWidget *widget, gboolean will_render)
{
	PangoLayout *layout;
	gint width;

	width = (cellicon->fixed_width > 0) ? cellicon->fixed_width * PANGO_SCALE : -1;

	layout = gtk_widget_create_pango_layout(widget, cellicon->text);
	pango_layout_set_width(layout, width);
	pango_layout_set_alignment(layout, PANGO_ALIGN_CENTER);
	pango_layout_set_wrap(layout, PANGO_WRAP_WORD_CHAR);

	if (will_render)
		{
		PangoAttrList *attr_list;

		attr_list = pango_attr_list_new();

		if (cellicon->foreground_set)
			{
			PangoColor color;
			PangoAttribute *attr;

			color = cellicon->foreground;

			attr = pango_attr_foreground_new(color.red, color.green, color.blue);

			attr->start_index = 0;
			attr->end_index = G_MAXINT;
			pango_attr_list_insert(attr_list, attr);
			}

		pango_layout_set_attributes(layout, attr_list);
		pango_attr_list_unref(attr_list);
		}

	return layout;
}

/**
 * gqv_cell_renderer_icon_new:
 * 
 * Creates a new #GQvCellRendererIcon. Adjust rendering
 * parameters using object properties. Object properties can be set
 * globally (with g_object_set()). Also, with #GtkTreeViewColumn, you
 * can bind a property to a value in a #GtkTreeModel. For example, you
 * can bind the "pixbuf" property on the cell renderer to a pixbuf value
 * in the model, thus rendering a different image in each row of the
 * #GtkTreeView.
 * 
 * Return value: the new cell renderer
 **/
GtkCellRenderer *
gqv_cell_renderer_icon_new(void)
{
	return g_object_new (GQV_TYPE_CELL_RENDERER_ICON, NULL);
}

static void
gqv_cell_renderer_icon_get_size(GtkCellRenderer *cell,
				GtkWidget	*widget,
				GdkRectangle	*cell_area,
				gint		*x_offset,
				gint		*y_offset,
				gint		*width,
				gint		*height)
{
	GQvCellRendererIcon *cellicon = (GQvCellRendererIcon *) cell;
	gint calc_width;
	gint calc_height;

	if (cellicon->fixed_width > 0)
		{
		calc_width = cellicon->fixed_width;
		}
	else
		{
		calc_width = (cellicon->pixbuf) ? gdk_pixbuf_get_width(cellicon->pixbuf) : 0;
		}

	if (cellicon->fixed_height > 0)
		{
		calc_height = cellicon->fixed_height;
		}
	else
		{
		calc_height = (cellicon->pixbuf) ? gdk_pixbuf_get_height(cellicon->pixbuf) : 0;
		}

	if (cellicon->show_text && cellicon->text)
		{
		PangoLayout *layout;
		PangoRectangle rect;

		layout = gqv_cell_renderer_icon_get_layout(cellicon, widget, FALSE);
		pango_layout_get_pixel_extents(layout, NULL, &rect);
		g_object_unref(layout);

		calc_width = MAX(calc_width, rect.width);
		calc_height += rect.height;
		}

	calc_width += (gint)cell->xpad * 2;
	calc_height += (gint)cell->ypad * 2;

	if (x_offset) *x_offset = 0;
	if (y_offset) *y_offset = 0;

	if (cell_area && calc_width > 0 && calc_height > 0)
		{
		if (x_offset)
			{
			*x_offset = (cell->xalign * (cell_area->width - calc_width - 2 * cell->xpad));
			*x_offset = MAX (*x_offset, 0) + cell->xpad;
			}
		if (y_offset)
			{
			*y_offset = (cell->yalign * (cell_area->height - calc_height - 2 * cell->ypad));
			*y_offset = MAX (*y_offset, 0) + cell->ypad;
			}
		}

	if (width) *width = calc_width;
	if (height) *height = calc_height;
}

static void
gqv_cell_renderer_icon_render(GtkCellRenderer		*cell,
			      GdkWindow			*window,
			      GtkWidget			*widget,
			      GdkRectangle		*background_area,
			      GdkRectangle		*cell_area,
			      GdkRectangle		*expose_area,
			      GtkCellRendererState	flags)

{
	GQvCellRendererIcon *cellicon = (GQvCellRendererIcon *) cell;
	GdkPixbuf *pixbuf;
	const gchar *text;
	GdkRectangle cell_rect;
	GtkStateType state;

	pixbuf = cellicon->pixbuf;
	text = cellicon->text;

	if (!pixbuf && !text) return;

	gqv_cell_renderer_icon_get_size(cell, widget, cell_area,
					&cell_rect.x, &cell_rect.y,
					&cell_rect.width, &cell_rect.height);

	cell_rect.x += cell->xpad;
	cell_rect.y += cell->ypad;
	cell_rect.width -= cell->xpad * 2;
	cell_rect.height -= cell->ypad * 2;

	if ((flags & GTK_CELL_RENDERER_SELECTED) == GTK_CELL_RENDERER_SELECTED)
		{
		if (GTK_WIDGET_HAS_FOCUS(widget))
			state = GTK_STATE_SELECTED;
		else
			state = GTK_STATE_ACTIVE;
		}
	else
		{
		if (GTK_WIDGET_STATE(widget) == GTK_STATE_INSENSITIVE)
			state = GTK_STATE_INSENSITIVE;
		else
			state = GTK_STATE_NORMAL;
		}

	if (pixbuf)
		{
		GdkRectangle pix_rect;
		GdkRectangle draw_rect;

		pix_rect.width = gdk_pixbuf_get_width(pixbuf);
		pix_rect.height = gdk_pixbuf_get_height(pixbuf);

		pix_rect.x = cell_area->x + (cell_area->width - pix_rect.width) / 2;

		if (cellicon->fixed_height > 0)
			{
			pix_rect.y = cell_area->y + cell->ypad + (cellicon->fixed_height - pix_rect.height) / 2;
			}
		else
			{
			pix_rect.y = cell_area->y + cell_rect.y;
			}

		if (gdk_rectangle_intersect(cell_area, &pix_rect, &draw_rect) &&
		    gdk_rectangle_intersect(expose_area, &draw_rect, &draw_rect))
			{
			gdk_draw_pixbuf(window,
					widget->style->black_gc,
					pixbuf,
					/* pixbuf 0, 0 is at pix_rect.x, pix_rect.y */
					draw_rect.x - pix_rect.x,
					draw_rect.y - pix_rect.y,
					draw_rect.x,
					draw_rect.y,
					draw_rect.width,
					draw_rect.height,
					GDK_RGB_DITHER_NORMAL,
					0, 0);
			}
		}

	if (cellicon->show_text && text)
		{
		PangoLayout *layout;
		PangoRectangle text_rect;
		GdkRectangle pix_rect;
                GdkRectangle draw_rect;

		layout = gqv_cell_renderer_icon_get_layout(cellicon, widget, TRUE);
		pango_layout_get_pixel_extents(layout, NULL, &text_rect);

		pix_rect.width = text_rect.width;
		pix_rect.height = text_rect.height;
		pix_rect.x = cell_area->x + cell->xpad + (cell_rect.width - text_rect.width + 1) / 2;
		pix_rect.y = cell_area->y + cell->ypad + (cell_rect.height - text_rect.height);

		if (gdk_rectangle_intersect(cell_area, &pix_rect, &draw_rect) &&
		    gdk_rectangle_intersect(expose_area, &draw_rect, &draw_rect))
			{
			gtk_paint_layout(widget->style, window,
					 state, TRUE,
					 cell_area, widget,
					 "cellrenderertext",
					 pix_rect.x - text_rect.x, pix_rect.y,
					 layout);
			}

		g_object_unref(layout);
		}

	if (cellicon->focused &&
	    GTK_WIDGET_HAS_FOCUS(widget))
		{
		gtk_paint_focus(widget->style, window,
				state,
				cell_area, widget,
				"cellrendererfocus",
				cell_area->x, cell_area->y,
				cell_area->width, cell_area->height);
		}
}

