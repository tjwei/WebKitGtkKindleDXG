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
#include "bar_exif.h"

#include "exif.h"
#include "ui_bookmark.h"
#include "ui_misc.h"

#include <math.h>

#define EXIF_BAR_SIZE_INCREMENT 48
#define EXIF_BAR_ARROW_SIZE 7

#define EXIF_BAR_CUSTOM_COUNT 20

#define BAR_EXIF_DATA_COLUMN_WIDTH 250

static const gchar *bar_exif_key_list_real[] = {
	"fCamera",
	"fDateTime",
	"fShutterSpeed",
	"fAperture",
	"ExposureProgram",
	"fExposureBias",
	"fISOSpeedRating",
	"fFocalLength",
	"fSubjectDistance",
	"MeteringMode",
	"fFlash",
	"LightSource",
	"fResolution",
	"Orientation",
	"ImageDescription",
	"Copyright"
};

const gchar **bar_exif_key_list = bar_exif_key_list_real;
const gint bar_exif_key_count = (sizeof(bar_exif_key_list_real) / sizeof(gchar *));


/*
 *-------------------------------------------------------------------
 * table util
 *-------------------------------------------------------------------
 */

static void table_add_line_custom(GtkWidget *table, gint x, gint y,
                                  const gchar *text1, const gchar *text2,
                                  GtkWidget **label1, GtkWidget **label2)
{
	GtkWidget *label;
	gchar *buf;

	buf = g_strconcat((text1) ? text1 : "fixme", ":", NULL);
	if (!text2) text2 = "";

	label = gtk_label_new(buf);
	gtk_misc_set_alignment(GTK_MISC(label), 1.0, 0.0);
	pref_label_bold(label, TRUE, FALSE);
	gtk_table_attach(GTK_TABLE(table), label,
			 x, x + 1, y, y + 1,
			 GTK_FILL, GTK_FILL,
			 2, 2);
	*label1 = label;

	label = gtk_label_new(text2);
	gtk_misc_set_alignment(GTK_MISC(label), 0.0, 0.0);
	gtk_table_attach(GTK_TABLE(table), label,
			 x + 1, x + 2, y, y + 1,
			 GTK_FILL, GTK_FILL,
			 2, 2);
	*label2 = label;

	g_free(buf);
}

static GtkWidget *table_add_line(GtkWidget *table, gint x, gint y,
				 const gchar *description, const gchar *text)
{
	GtkWidget *key;
	GtkWidget *label;

	table_add_line_custom(table, x, y, description, text, &key, &label);
	gtk_widget_show(key);
	gtk_widget_show(label);

	return label;
}


/*
 *-------------------------------------------------------------------
 * EXIF bar
 *-------------------------------------------------------------------
 */

typedef struct _ExifBar ExifBar;
struct _ExifBar
{
	GtkWidget *vbox;
	GtkWidget *scrolled;
	GtkWidget *table;
	GtkWidget *advanced_scrolled;
	GtkWidget *listview;
	GtkWidget **labels;

	GtkWidget *custom_sep;
	GtkWidget *custom_name[EXIF_BAR_CUSTOM_COUNT];
	GtkWidget *custom_value[EXIF_BAR_CUSTOM_COUNT];

	gchar *path;

	gint allow_search;
};

enum {
	EXIF_ADVCOL_ENABLED = 0,
	EXIF_ADVCOL_TAG,
	EXIF_ADVCOL_NAME,
	EXIF_ADVCOL_VALUE,
	EXIF_ADVCOL_FORMAT,
	EXIF_ADVCOL_ELEMENTS,
	EXIF_ADVCOL_DESCRIPTION,
	EXIF_ADVCOL_COUNT
};

gchar *bar_exif_validate_text(gchar *text)
{
	if (text && !g_utf8_validate(text, strlen(text), NULL))
		{
		gchar *tmp = text;
		text = g_convert(tmp, strlen(tmp), "UTF-8", "ISO-8859-1", NULL, NULL, NULL);
		g_free(tmp);
		}
	return text;
}

static void bar_exif_sensitive(ExifBar *eb, gint enable)
{
	gtk_widget_set_sensitive(eb->table, enable);
	if (eb->advanced_scrolled) gtk_widget_set_sensitive(eb->advanced_scrolled, enable);
}

static gint bar_exif_row_enabled(const gchar *name)
{
	GList *list;

	list = history_list_get_by_key("exif_extras");
	while (list)
		{
		if (name && strcmp(name, (gchar *)(list->data)) == 0) return TRUE;
		list = list->next;
	}

	return FALSE;
}

static void bar_exif_update(ExifBar *eb)
{
	ExifData *exif;
	gint len, i;

	exif = exif_read(eb->path, FALSE);

	if (!exif)
		{
		bar_exif_sensitive(eb, FALSE);
		return;
		}

	bar_exif_sensitive(eb, TRUE);

	if (GTK_WIDGET_VISIBLE(eb->scrolled))
		{
		GList *list;
		len = bar_exif_key_count;
		for (i = 0; i < len; i++)
			{
			gchar *text;
			text = exif_get_data_as_text(exif, bar_exif_key_list[i]);
			text = bar_exif_validate_text(text);
			gtk_label_set_text(GTK_LABEL(eb->labels[i]), text);
			g_free(text);
			}

		list = g_list_last(history_list_get_by_key("exif_extras"));
		if (list)
			{
			gtk_widget_show(eb->custom_sep);
			}
		else
			{
			gtk_widget_hide(eb->custom_sep);
			}
		i = 0;
		while (list && i < EXIF_BAR_CUSTOM_COUNT)
			{
			gchar *text;
			gchar *name;
			gchar *buf;

			name = list->data;
			list = list->prev;

			text = exif_get_data_as_text(exif, name);
			text = bar_exif_validate_text(text);

			buf = g_strconcat(name, ":", NULL);
			gtk_label_set_text(GTK_LABEL(eb->custom_name[i]), buf);
			g_free(buf);
			gtk_label_set_text(GTK_LABEL(eb->custom_value[i]), text);
			g_free(text);

			gtk_widget_show(eb->custom_name[i]);
			gtk_widget_show(eb->custom_value[i]);

			i++;
			}
		while (i < EXIF_BAR_CUSTOM_COUNT)
			{
			gtk_widget_hide(eb->custom_name[i]);
			gtk_widget_hide(eb->custom_value[i]);
			i++;
			}
		}

	if (eb->advanced_scrolled && GTK_WIDGET_VISIBLE(eb->advanced_scrolled))
		{
		GtkListStore *store;
		GtkTreeIter iter;
		GList *work;
		
		store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(eb->listview)));
		gtk_list_store_clear(store);

		work = exif->items;
		while (work)
			{
			ExifItem *item;
			gchar *tag;
			const gchar *tag_name;
			gchar *text;
			const gchar *format;
			gchar *elements;
			const gchar *description;

			item = work->data;
			work = work->next;

			tag = g_strdup_printf("0x%04x", item->tag);
			tag_name = exif_item_get_tag_name(item);
			format = exif_item_get_format_name(item, TRUE);
			text = exif_item_get_data_as_text(item);
			text = bar_exif_validate_text(text);
			elements = g_strdup_printf("%d", item->elements);
			description = exif_item_get_description(item);
			if (!description) description = "";
			gtk_list_store_append(store, &iter);
			gtk_list_store_set(store, &iter,
					EXIF_ADVCOL_ENABLED, bar_exif_row_enabled(tag_name),
					EXIF_ADVCOL_TAG, tag,
					EXIF_ADVCOL_NAME, tag_name,
					EXIF_ADVCOL_VALUE, text,
					EXIF_ADVCOL_FORMAT, format,
					EXIF_ADVCOL_ELEMENTS, elements,
					EXIF_ADVCOL_DESCRIPTION, description, -1);
			g_free(tag);
			g_free(text);
			g_free(elements);
			}
		}

	exif_free(exif);
}

static void bar_exif_clear(ExifBar *eb)
{
	gint len;
	gint i;

	if (!GTK_WIDGET_SENSITIVE(eb->labels[0])) return;

	len = bar_exif_key_count;
	for (i = 0; i < len; i++)
		{
		gtk_label_set_text(GTK_LABEL(eb->labels[i]), "");
		}
	for (i = 0; i < EXIF_BAR_CUSTOM_COUNT; i++)
		{
		gtk_label_set_text(GTK_LABEL(eb->custom_value[i]), "");
		}

	if (eb->listview)
		{
		GtkListStore *store;

		store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(eb->listview)));
		gtk_list_store_clear(store);
		}
}

void bar_exif_set(GtkWidget *bar, const gchar *path)
{
	ExifBar *eb;

	eb = g_object_get_data(G_OBJECT(bar), "bar_exif_data");
	if (!eb) return;

	/* store this, advanced view toggle needs to reload data */
	g_free(eb->path);
	eb->path = g_strdup(path);

	bar_exif_clear(eb);
	bar_exif_update(eb);
}

static void bar_exif_row_toggled_cb(GtkCellRendererToggle *toggle, const gchar *path, gpointer data)
{
	GtkWidget *listview = data;
	GtkTreeModel *store;
	GtkTreeIter iter;
	GtkTreePath *tpath;
	gchar *name = NULL;
	gboolean active;

	store = gtk_tree_view_get_model(GTK_TREE_VIEW(listview));

	tpath = gtk_tree_path_new_from_string(path);
	gtk_tree_model_get_iter(store, &iter, tpath);
	gtk_tree_path_free(tpath);

	gtk_tree_model_get(store, &iter, EXIF_ADVCOL_ENABLED, &active,
					 EXIF_ADVCOL_NAME, &name, -1);
	active = (!active);

	if (active &&
	    g_list_length(history_list_get_by_key("exif_extras")) >= EXIF_BAR_CUSTOM_COUNT)
		{
		active = FALSE;
		}

	gtk_list_store_set(GTK_LIST_STORE(store), &iter, EXIF_ADVCOL_ENABLED, active, -1);

	if (active)
		{
		history_list_add_to_key("exif_extras", name, EXIF_BAR_CUSTOM_COUNT);
		}
	else
		{
		history_list_item_change("exif_extras", name, NULL);
		}

	g_free(name);
}

static void bar_exif_add_column_check(GtkWidget *listview, const gchar *title, gint n)
{
	GtkTreeViewColumn *column;
	GtkCellRenderer *renderer;

	column = gtk_tree_view_column_new();
	gtk_tree_view_column_set_title(column, title);
	gtk_tree_view_column_set_sizing(column, GTK_TREE_VIEW_COLUMN_AUTOSIZE);

	renderer = gtk_cell_renderer_toggle_new();
	gtk_tree_view_column_pack_start(column, renderer, TRUE);
	gtk_tree_view_column_add_attribute(column, renderer, "active", n);
	gtk_tree_view_append_column(GTK_TREE_VIEW(listview), column);

	g_signal_connect(G_OBJECT(renderer), "toggled",
			 G_CALLBACK(bar_exif_row_toggled_cb), listview);
}

static void bar_exif_add_column(GtkWidget *listview, const gchar *title, gint n, gint sizable)
{
	GtkTreeViewColumn *column;
	GtkCellRenderer *renderer;

	column = gtk_tree_view_column_new();
	gtk_tree_view_column_set_title(column, title);

	if (sizable)
		{
		gtk_tree_view_column_set_sizing(column, GTK_TREE_VIEW_COLUMN_FIXED);
		gtk_tree_view_column_set_fixed_width(column, BAR_EXIF_DATA_COLUMN_WIDTH);
		gtk_tree_view_column_set_resizable(column, TRUE);
		}
	else
		{
		gtk_tree_view_column_set_sizing(column, GTK_TREE_VIEW_COLUMN_AUTOSIZE);
		}

	renderer = gtk_cell_renderer_text_new();
	gtk_tree_view_column_pack_start(column, renderer, TRUE);
	gtk_tree_view_column_add_attribute(column, renderer, "text", n);
	gtk_tree_view_append_column(GTK_TREE_VIEW(listview), column);
}

static void bar_exif_advanced_build_view(ExifBar *eb)
{
	GtkListStore *store;

	if (eb->listview) return;

	store = gtk_list_store_new(7, G_TYPE_BOOLEAN,
				      G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING,
				      G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
	eb->listview = gtk_tree_view_new_with_model(GTK_TREE_MODEL(store));
	g_object_unref(store);

	gtk_tree_view_set_rules_hint(GTK_TREE_VIEW(eb->listview), TRUE);
	gtk_tree_view_set_headers_visible(GTK_TREE_VIEW(eb->listview), TRUE);

	if (eb->allow_search)
		{
		gtk_tree_view_set_search_column(GTK_TREE_VIEW(eb->listview), EXIF_ADVCOL_NAME);
		}
	else
		{
		gtk_tree_view_set_enable_search(GTK_TREE_VIEW(eb->listview), FALSE);
		}

	bar_exif_add_column_check(eb->listview, "", EXIF_ADVCOL_ENABLED);

	bar_exif_add_column(eb->listview, _("Tag"), EXIF_ADVCOL_TAG, FALSE);
	bar_exif_add_column(eb->listview, _("Name"), EXIF_ADVCOL_NAME, FALSE);
	bar_exif_add_column(eb->listview, _("Value"), EXIF_ADVCOL_VALUE, TRUE);
	bar_exif_add_column(eb->listview, _("Format"), EXIF_ADVCOL_FORMAT, FALSE);
	bar_exif_add_column(eb->listview, _("Elements"), EXIF_ADVCOL_ELEMENTS, FALSE);
	bar_exif_add_column(eb->listview, _("Description"), EXIF_ADVCOL_DESCRIPTION, FALSE);

	eb->advanced_scrolled = gtk_scrolled_window_new(NULL, NULL);
	gtk_scrolled_window_set_shadow_type(GTK_SCROLLED_WINDOW(eb->advanced_scrolled), GTK_SHADOW_IN);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(eb->advanced_scrolled),
				       GTK_POLICY_AUTOMATIC, GTK_POLICY_ALWAYS);
	gtk_box_pack_start(GTK_BOX(eb->vbox), eb->advanced_scrolled, TRUE, TRUE, 0);
	gtk_container_add(GTK_CONTAINER(eb->advanced_scrolled), eb->listview);
	gtk_widget_show(eb->listview);
}

static void bar_exif_advanced_cb(GtkWidget *widget, gpointer data)
{
	ExifBar *eb = data;
	gint advanced;

	advanced = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget));

	if (advanced)
		{
		gtk_widget_hide(eb->scrolled);
		bar_exif_advanced_build_view(eb);
		gtk_widget_show(eb->advanced_scrolled);
		}
	else
		{
		gtk_widget_hide(eb->advanced_scrolled);
		gtk_widget_show(eb->scrolled);
		}

	bar_exif_update(eb);
}

gint bar_exif_is_advanced(GtkWidget *bar)
{
	ExifBar *eb;

	eb = g_object_get_data(G_OBJECT(bar), "bar_exif_data");
	if (!eb) return FALSE;

	return (eb->advanced_scrolled && GTK_WIDGET_VISIBLE(eb->advanced_scrolled));
}

void bar_exif_close(GtkWidget *bar)
{
	ExifBar *eb;

	eb = g_object_get_data(G_OBJECT(bar), "bar_exif_data");
	if (!eb) return;

	gtk_widget_destroy(eb->vbox);
}

static void bar_exif_size(ExifBar *eb, gint val)
{
	gint size;

	size = eb->vbox->allocation.width;
	size = CLAMP(size + val, EXIF_BAR_SIZE_INCREMENT * 2, EXIF_BAR_SIZE_INCREMENT * 16);

	gtk_widget_set_size_request(eb->vbox, size, -1);
}

static void bar_exif_larger(GtkWidget *widget, gpointer data)
{
	ExifBar *eb = data;

	bar_exif_size(eb, EXIF_BAR_SIZE_INCREMENT);
}

static void bar_exif_smaller(GtkWidget *widget, gpointer data)
{
	ExifBar *eb = data;

	bar_exif_size(eb, -EXIF_BAR_SIZE_INCREMENT);
}

static void bar_exif_destroy(GtkWidget *widget, gpointer data)
{
	ExifBar *eb = data;

	g_free(eb->labels);
	g_free(eb->path);
	g_free(eb);
}

GtkWidget *bar_exif_new(gint show_title, const gchar *path, gint advanced, GtkWidget *bounding_widget)
{
	ExifBar *eb;
	GtkWidget *table;
	GtkWidget *viewport;
	GtkWidget *hbox;
	GtkWidget *button;
	gint len;
	gint i;

	eb = g_new0(ExifBar, 1);

	eb->labels = g_new0(GtkWidget *, bar_exif_key_count);

	eb->vbox = gtk_vbox_new(FALSE, PREF_PAD_GAP);
	g_object_set_data(G_OBJECT(eb->vbox), "bar_exif_data", eb);
	g_signal_connect_after(G_OBJECT(eb->vbox), "destroy",
			       G_CALLBACK(bar_exif_destroy), eb);

	eb->allow_search = !show_title;

	if (show_title)
		{
		GtkWidget *box;
		GtkWidget *label;
		GtkWidget *button;
		GtkWidget *arrow;

		box = gtk_hbox_new(FALSE, 0);

		label = sizer_new(eb->vbox, bounding_widget, SIZER_POS_LEFT);
		sizer_set_limits(label, EXIF_BAR_SIZE_INCREMENT * 2, -1, -1 , -1);
		gtk_box_pack_start(GTK_BOX(box), label, FALSE, FALSE, 0);
		gtk_widget_show(label);

		label = gtk_label_new(_("Exif"));
		pref_label_bold(label, TRUE, FALSE);
		gtk_box_pack_start(GTK_BOX(box), label, TRUE, TRUE, 0);
		gtk_widget_show(label);

		button = gtk_button_new();
		gtk_button_set_relief(GTK_BUTTON(button), GTK_RELIEF_NONE);
		g_signal_connect(G_OBJECT(button), "clicked",
				 G_CALLBACK(bar_exif_smaller), eb);
		gtk_box_pack_end(GTK_BOX(box), button, FALSE, FALSE, 0);
		arrow = gtk_arrow_new(GTK_ARROW_RIGHT, GTK_SHADOW_NONE);
		gtk_widget_set_size_request(arrow, EXIF_BAR_ARROW_SIZE, EXIF_BAR_ARROW_SIZE);
		gtk_container_add(GTK_CONTAINER(button), arrow);
		gtk_widget_show(arrow);
		gtk_widget_show(button);

		button = gtk_button_new();
		gtk_button_set_relief(GTK_BUTTON(button), GTK_RELIEF_NONE);
		g_signal_connect(G_OBJECT(button), "clicked",
				 G_CALLBACK(bar_exif_larger), eb);
		gtk_box_pack_end(GTK_BOX(box), button, FALSE, FALSE, 0);
		arrow = gtk_arrow_new(GTK_ARROW_LEFT, GTK_SHADOW_NONE);
		gtk_widget_set_size_request(arrow, EXIF_BAR_ARROW_SIZE, EXIF_BAR_ARROW_SIZE);
		gtk_container_add(GTK_CONTAINER(button), arrow);
		gtk_widget_show(arrow);
		gtk_widget_show(button);

		gtk_box_pack_start(GTK_BOX(eb->vbox), box, FALSE, FALSE, 0);
		gtk_widget_show(box);
		}

	table = gtk_table_new(2, bar_exif_key_count + 1 + EXIF_BAR_CUSTOM_COUNT, FALSE);

	eb->table = table;

	len = bar_exif_key_count;
	for (i = 0; i < len; i++)
		{
		const gchar *text;

		text = exif_get_description_by_key(bar_exif_key_list[i]);
		eb->labels[i] = table_add_line(table, 0, i, text, NULL);
		}

	eb->custom_sep = gtk_hseparator_new();
	gtk_table_attach(GTK_TABLE(table), eb->custom_sep, 0, 1,
					   bar_exif_key_count, bar_exif_key_count + 1,
					   GTK_FILL, GTK_FILL, 2, 2);

	for (i = 0; i < EXIF_BAR_CUSTOM_COUNT; i++)
		{
		table_add_line_custom(table, 0, bar_exif_key_count + 1 + i,
				      "", "",  &eb->custom_name[i], &eb->custom_value[i]);
		}

	eb->scrolled = gtk_scrolled_window_new(NULL, NULL);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(eb->scrolled),
				       GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);

	viewport = gtk_viewport_new(NULL, NULL);
	gtk_viewport_set_shadow_type(GTK_VIEWPORT(viewport), GTK_SHADOW_NONE);
	gtk_container_add(GTK_CONTAINER(eb->scrolled), viewport);
	gtk_widget_show(viewport);

	gtk_container_add(GTK_CONTAINER(viewport), table);
	gtk_widget_show(table);

	gtk_box_pack_start(GTK_BOX(eb->vbox), eb->scrolled, TRUE, TRUE, 0);

	hbox = gtk_hbox_new(FALSE, PREF_PAD_SPACE);
	gtk_box_pack_end(GTK_BOX(eb->vbox), hbox, FALSE, FALSE, 0);
	gtk_widget_show(hbox);

	button = gtk_check_button_new_with_label(_("Advanced view"));
	if (advanced) gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(button), TRUE);
	g_signal_connect(G_OBJECT(button), "toggled",
			 G_CALLBACK(bar_exif_advanced_cb), eb);
	gtk_box_pack_end(GTK_BOX(hbox), button, FALSE, FALSE, 0);
	gtk_widget_show(button);

	eb->advanced_scrolled = NULL;
	eb->listview = NULL;

	if (advanced)
		{
		bar_exif_advanced_build_view(eb);
		gtk_widget_show(eb->advanced_scrolled);
		}
	else
		{
		gtk_widget_show(eb->scrolled);
		}

	eb->path = g_strdup(path);
	bar_exif_update(eb);

	return eb->vbox;
}

