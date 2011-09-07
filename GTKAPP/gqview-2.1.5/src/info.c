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
#include "info.h"

#include "bar_info.h"
#include "bar_exif.h"
#include "dnd.h"
#include "filelist.h"
#include "image.h"
#include "image-load.h"
#include "pixbuf-renderer.h"
#include "ui_bookmark.h"
#include "ui_fileops.h"
#include "ui_misc.h"

#include <pwd.h>
#include <grp.h>


#define IMAGE_SIZE_W 200
#define IMAGE_SIZE_H 200

#define DEF_PROPERTY_WIDTH  600
#define DEF_PROPERTY_HEIGHT 400

typedef struct _TabData TabData;
struct _TabData
{
	void (*func_free)(gpointer data);
	void (*func_sync)(InfoData *id, gpointer data);
	void (*func_image)(InfoData *id, gpointer data);
	gpointer data;
};


/*
 *-------------------------------------------------------------------
 * table utils
 *-------------------------------------------------------------------
 */

GtkWidget *table_add_line(GtkWidget *table, gint x, gint y,
			  const gchar *description, const gchar *text)
{
	GtkWidget *label;

	if (!text) text = "";

	label = pref_table_label(table, x, y, description, 1.0);
	pref_label_bold(label, TRUE, FALSE);

	label = pref_table_label(table, x + 1, y, text, 0.0);
	return label;
}

/*
 *-------------------------------------------------------------------
 * EXIF tab
 *-------------------------------------------------------------------
 */

static void info_tab_exif_image(InfoData *id, gpointer data)
{
	GtkWidget *bar = data;
	const gchar *path;

	if (id->image->unknown)
		{
		path = NULL;
		}
	else
       		{
		path = id->image->image_path;
		}

	bar_exif_set(bar, path);
}

static void info_tab_exif_sync(InfoData *id, gpointer data)
{
	GtkWidget *bar = data;

	bar_exif_set(bar, NULL);
}

static TabData *info_tab_exif_new(InfoData *id)
{
	TabData *td;
	GtkWidget *bar;
	GtkWidget *label;

	bar = bar_exif_new(FALSE, NULL, FALSE, NULL);
	gtk_container_set_border_width(GTK_CONTAINER(bar), PREF_PAD_BORDER);

	label = gtk_label_new(_("Exif"));
	gtk_notebook_append_page(GTK_NOTEBOOK(id->notebook), bar, label);
	gtk_widget_show(bar);

	/* register */
	td = g_new0(TabData, 1);
	td->func_free = NULL;
	td->func_sync = info_tab_exif_sync;
	td->func_image = info_tab_exif_image;
	td->data = bar;

	return td;
}

/*
 *-------------------------------------------------------------------
 * file attributes tab
 *-------------------------------------------------------------------
 */

typedef struct _InfoTabMeta InfoTabMeta;
struct _InfoTabMeta
{
	GtkWidget *bar_info;
};

static void info_tab_meta_free(gpointer data)
{
	InfoTabMeta *tab = data;

	g_free(tab);
}

static void info_tab_meta_sync(InfoData *id, gpointer data)
{
	InfoTabMeta *tab = data;

	bar_info_set(tab->bar_info, id->path);
}

static GList *info_tab_meta_list_cb(gpointer data)
{
	InfoData *id = data;

	return path_list_copy(id->list);
}

static TabData *info_tab_meta_new(InfoData *id)
{
	TabData *td;
	InfoTabMeta *tab;
	GtkWidget *label;

	tab = g_new0(InfoTabMeta, 1);

	tab->bar_info = bar_info_new(NULL, TRUE, NULL);
	bar_info_set_selection_func(tab->bar_info, info_tab_meta_list_cb, id);
	bar_info_selection(tab->bar_info, g_list_length(id->list) - 1);

	gtk_container_set_border_width(GTK_CONTAINER(tab->bar_info), PREF_PAD_BORDER);

	label = gtk_label_new(_("Keywords"));
	gtk_notebook_append_page(GTK_NOTEBOOK(id->notebook), tab->bar_info, label);
	gtk_widget_show(tab->bar_info);

	/* register */
	td = g_new0(TabData, 1);
	td->func_free = info_tab_meta_free;
	td->func_sync = info_tab_meta_sync;
	td->func_image = NULL;
	td->data = tab;

	return td;
}

/*
 *-------------------------------------------------------------------
 * general tab
 *-------------------------------------------------------------------
 */

typedef struct _InfoTabGeneral InfoTabGeneral;
struct _InfoTabGeneral
{
	GtkWidget *label_file_time;
	GtkWidget *label_file_size;
	GtkWidget *label_dimensions;
	GtkWidget *label_transparent;
	GtkWidget *label_image_size;
	GtkWidget *label_compression;
	GtkWidget *label_mime_type;

	GtkWidget *label_user;
	GtkWidget *label_group;
	GtkWidget *label_perms;

	gint compression_done;
	gint64 byte_size;
};

static void info_tab_general_image(InfoData *id, gpointer data)
{
	InfoTabGeneral *tab = data;
	gchar *buf;
	guint mem_size;
	gint has_alpha;
	GdkPixbuf *pixbuf;
	gint width, height;

	if (id->image->unknown) return;

	pixbuf_renderer_get_image_size(PIXBUF_RENDERER(id->image->pr), &width, &height);

	buf = g_strdup_printf("%d x %d", width, height);
	gtk_label_set_text(GTK_LABEL(tab->label_dimensions), buf);
	g_free(buf);

	pixbuf = image_get_pixbuf(id->image);
	if (pixbuf)
		{
		has_alpha = gdk_pixbuf_get_has_alpha(pixbuf);
		}
	else
		{
		has_alpha = FALSE;
		}
	gtk_label_set_text(GTK_LABEL(tab->label_transparent), has_alpha ? _("yes") : _("no"));

	mem_size = width * height * ((has_alpha) ? 4 : 3);
	buf = text_from_size_abrev(mem_size);
	gtk_label_set_text(GTK_LABEL(tab->label_image_size), buf);
	g_free(buf);

	if (!tab->compression_done && mem_size > 0)
		{
		buf = g_strdup_printf("%.1f%%", (double)tab->byte_size / mem_size * 100.0);
		gtk_label_set_text(GTK_LABEL(tab->label_compression), buf);
		g_free(buf);

		tab->compression_done = TRUE;
		}

	buf = image_loader_get_format(id->image->il);
	if (buf)
	gtk_label_set_text(GTK_LABEL(tab->label_mime_type), buf);
	g_free(buf);
}

static gchar *mode_number(mode_t m)
{
	int mb, mu, mg, mo;

	mb = mu = mg = mo = 0;

	if (m & S_ISUID) mb |= 4;
	if (m & S_ISGID) mb |= 2;
	if (m & S_ISVTX) mb |= 1;

	if (m & S_IRUSR) mu |= 4;
	if (m & S_IWUSR) mu |= 2;
	if (m & S_IXUSR) mu |= 1;

	if (m & S_IRGRP) mg |= 4;
	if (m & S_IWGRP) mg |= 2;
	if (m & S_IXGRP) mg |= 1;

	if (m & S_IROTH) mo |= 4;
	if (m & S_IWOTH) mo |= 2;
	if (m & S_IXOTH) mo |= 1;

	return g_strdup_printf("%d%d%d%d", mb, mu, mg, mo);
}

static void info_tab_general_sync_perm(InfoTabGeneral *tab, InfoData *id)
{
	struct stat st;

	if (!stat_utf8(id->path, &st))
		{
		gtk_label_set_text(GTK_LABEL(tab->label_user), "");
		gtk_label_set_text(GTK_LABEL(tab->label_group), "");
		gtk_label_set_text(GTK_LABEL(tab->label_perms), "");
		}
	else
		{
		struct passwd *user;
		struct group *grp;
		gchar pbuf[12];
		gchar *pmod;
		gchar *buf;

		user = getpwuid(st.st_uid);
		gtk_label_set_text(GTK_LABEL(tab->label_user), (user) ? user->pw_name : "");

		grp = getgrgid(st.st_gid);
		gtk_label_set_text(GTK_LABEL(tab->label_group), (grp) ? grp->gr_name : "");

		pbuf[0] = (st.st_mode & S_IRUSR) ? 'r' : '-';
		pbuf[1] = (st.st_mode & S_IWUSR) ? 'w' : '-';
		pbuf[2] = (st.st_mode & S_IXUSR) ? 'x' : '-';
		pbuf[3] = (st.st_mode & S_IRGRP) ? 'r' : '-';
		pbuf[4] = (st.st_mode & S_IWGRP) ? 'w' : '-';
		pbuf[5] = (st.st_mode & S_IXGRP) ? 'x' : '-';
		pbuf[6] = (st.st_mode & S_IROTH) ? 'r' : '-';
		pbuf[7] = (st.st_mode & S_IWOTH) ? 'w' : '-';
		pbuf[8] = (st.st_mode & S_IXOTH) ? 'x' : '-';
		pbuf[9] = '\0';

		pmod = mode_number(st.st_mode);
		buf = g_strdup_printf("%s (%s)", pbuf, pmod);
		gtk_label_set_text(GTK_LABEL(tab->label_perms), buf);
		g_free(buf);
		g_free(pmod);
		}
}

static void info_tab_general_sync(InfoData *id, gpointer data)
{
	InfoTabGeneral *tab = data;
	gchar *buf;

	gtk_label_set_text(GTK_LABEL(tab->label_file_time), text_from_time(filetime(id->path)));

	tab->byte_size = filesize(id->path);

	buf = text_from_size(tab->byte_size);
	gtk_label_set_text(GTK_LABEL(tab->label_file_size), buf);
	g_free(buf);

	gtk_label_set_text(GTK_LABEL(tab->label_dimensions), "");
	gtk_label_set_text(GTK_LABEL(tab->label_transparent), "");
	gtk_label_set_text(GTK_LABEL(tab->label_image_size), "");

	gtk_label_set_text(GTK_LABEL(tab->label_compression), "");
	gtk_label_set_text(GTK_LABEL(tab->label_mime_type), "");

	info_tab_general_sync_perm(tab, id);

	tab->compression_done = FALSE;
}

static void info_tab_general_free(gpointer data)
{
	InfoTabGeneral *tab = data;

	g_free(tab);
}

static TabData *info_tab_general_new(InfoData *id)
{
	TabData *td;
	InfoTabGeneral *tab;
	GtkWidget *table;
	GtkWidget *label;

	tab = g_new0(InfoTabGeneral, 1);

	table = pref_table_new(NULL, 2, 11, FALSE, FALSE);
	gtk_container_set_border_width(GTK_CONTAINER(table), PREF_PAD_BORDER);

	tab->label_file_time = table_add_line(table, 0, 0, _("File date:"), NULL);
	tab->label_file_size = table_add_line(table, 0, 1, _("File size:"), NULL);

	tab->label_dimensions = table_add_line(table, 0, 2, _("Dimensions:"), NULL);
	tab->label_transparent = table_add_line(table, 0, 3, _("Transparent:"), NULL);
	tab->label_image_size = table_add_line(table, 0, 4, _("Image size:"), NULL);

	tab->label_compression = table_add_line(table, 0, 5, _("Compress ratio:"), NULL);
	tab->label_mime_type = table_add_line(table, 0, 6, _("File type:"), NULL);

	tab->label_user = table_add_line(table, 0, 7, _("Owner:"), NULL);
	tab->label_group = table_add_line(table, 0, 8, _("Group:"), NULL);
	tab->label_perms = table_add_line(table, 0, 9, "", NULL);

	label = gtk_label_new(_("General"));
	gtk_notebook_append_page(GTK_NOTEBOOK(id->notebook), table, label);
	gtk_widget_show(table);

	/* register */
	td = g_new0(TabData, 1);
	td->func_free = info_tab_general_free;
	td->func_sync = info_tab_general_sync;
	td->func_image = info_tab_general_image;
	td->data = tab;

	return td;
}

/*
 *-------------------------------------------------------------------
 * tabs
 *-------------------------------------------------------------------
 */

static void info_tabs_sync(InfoData *id, gint image)
{
	GList *work;

	work = id->tab_list;
	while (work)
		{
		TabData *td = work->data;
		work = work->next;

		if (image)
			{
			if (td->func_image) td->func_image(id, td->data);
			}
		else
			{
			if (td->func_sync) td->func_sync(id, td->data);
			}
		}
}

static void info_tabs_free(InfoData *id)
{
	GList *work;

	work = id->tab_list;
	while (work)
		{
		TabData *td = work->data;
		work = work->next;

		if (td->func_free) td->func_free(td->data);
		g_free(td);
		}
	g_list_free(id->tab_list);
	id->tab_list = NULL;
}

static void info_tabs_init(InfoData *id)
{
	id->tab_list = g_list_append(id->tab_list, info_tab_general_new(id));
	id->tab_list = g_list_append(id->tab_list, info_tab_meta_new(id));
	id->tab_list = g_list_append(id->tab_list, info_tab_exif_new(id));
}

/*
 *-------------------------------------------------------------------
 * sync
 *-------------------------------------------------------------------
 */

static void info_window_sync(InfoData *id, const gchar *path)
{

	if (!path) return;

	gtk_entry_set_text(GTK_ENTRY(id->name_entry), filename_from_path(path));

	if (id->label_count)
		{
		gchar *buf;
		buf = g_strdup_printf(_("Image %d of %d"),
				      g_list_index(id->list, (gpointer)path) + 1,
				      g_list_length(id->list));
		gtk_label_set_text(GTK_LABEL(id->label_count), buf);
		g_free(buf);
		}

	info_tabs_sync(id, FALSE);

	id->updated = FALSE;
	image_change_path(id->image, path, 0.0);
}

/*
 *-------------------------------------------------------------------
 * drag n drop (dropping not supported!)
 *-------------------------------------------------------------------
 */

static void info_window_dnd_data_set(GtkWidget *widget, GdkDragContext *context,
				     GtkSelectionData *selection_data, guint info,
				     guint time, gpointer data)
{
	InfoData *id = data;
	const gchar *path;

	path = image_get_path(id->image);
	if (path)
		{
		gchar *text;
		gint len;
		GList *list;
		gint plain_text;

		switch (info)
			{
			case TARGET_URI_LIST:
				plain_text = FALSE;
				break;
			case TARGET_TEXT_PLAIN:
			default:
				plain_text = TRUE;
				break;
			}
		list = g_list_append(NULL, (gchar *)path);
		text = uri_text_from_list(list, &len, plain_text);
		g_list_free(list);

		gtk_selection_data_set(selection_data, selection_data->target,
				       8, (guchar *)text, len);
		g_free(text);
		}
}

static void info_window_dnd_init(InfoData *id)
{
	ImageWindow *imd;

	imd = id->image;

	gtk_drag_source_set(imd->pr, GDK_BUTTON2_MASK,
			    dnd_file_drag_types, dnd_file_drag_types_count,
			    GDK_ACTION_COPY | GDK_ACTION_MOVE | GDK_ACTION_LINK);
	g_signal_connect(G_OBJECT(imd->pr), "drag_data_get",
			 G_CALLBACK(info_window_dnd_data_set), id);

#if 0
	gtk_drag_dest_set(imd->pr,
			  GTK_DEST_DEFAULT_MOTION | GTK_DEST_DEFAULT_DROP,
			  dnd_file_drop_types, dnd_file_drop_types_count,
			  GDK_ACTION_COPY | GDK_ACTION_MOVE | GDK_ACTION_LINK);
	g_signal_connect(G_OBJECT(imd->pr), "drag_data_received",
			 G_CALLBACK(info_window_dnd_data_get), id);
#endif
}

/*
 *-------------------------------------------------------------------
 * base window
 *-------------------------------------------------------------------
 */

static gint info_window_last_width = DEF_PROPERTY_WIDTH;
static gint info_window_last_height = DEF_PROPERTY_HEIGHT;

static void info_window_image_update_cb(ImageWindow *imd, gpointer data)
{
	InfoData *id = data;

	/* only do this once after when loading a new image,
	 * for tabs that depend on image data (exif)
	 * Subsequent updates are ignored, as the image
	 * should not really changed if id->updated is TRUE.
	 */

	if (id->updated) return;
	if (imd->unknown) return;

	info_tabs_sync(id, TRUE);
	id->updated = TRUE;
}

static void info_window_back_cb(GtkWidget *widget, gpointer data)
{
	InfoData *id = data;
	GList *work;

	work = g_list_find(id->list, (gpointer)id->path);
	if (!work || !work->prev) return;

	work = work->prev;
	id->path = work->data;

	info_window_sync(id, id->path);

	gtk_widget_set_sensitive(id->button_back, (work->prev != NULL));
	gtk_widget_set_sensitive(id->button_next, TRUE);
}

static void info_window_next_cb(GtkWidget *widget, gpointer data)
{
	InfoData *id = data;
	GList *work;

	work = g_list_find(id->list, (gpointer)id->path);
	if (!work || !work->next) return;

	work = work->next;
	id->path = work->data;

	info_window_sync(id, id->path);

	gtk_widget_set_sensitive(id->button_next, (work->next != NULL));
	gtk_widget_set_sensitive(id->button_back, TRUE);
}

static void info_window_image_button_cb(ImageWindow *imd, gint button, guint32 time,
					gdouble x, gdouble y, guint state, gpointer data)
{
	if (button == 1)
		{
		info_window_next_cb(NULL, data);
		}
	else if (button == 2 || button == 3)
		{
		info_window_back_cb(NULL, data);
		}
}

static void info_window_image_scroll_cb(ImageWindow *imd, GdkScrollDirection direction, guint32 time,
					gdouble x, gdouble y, guint state, gpointer data)
{
	if (direction == GDK_SCROLL_UP)
		{
		info_window_back_cb(NULL, data);
		}
	else if (direction == GDK_SCROLL_DOWN)
		{
		info_window_next_cb(NULL, data);
		}
}

static void info_window_close(InfoData *id)
{
	gdk_drawable_get_size(id->window->window, &info_window_last_width, &info_window_last_height);
	info_window_last_width = MAX(info_window_last_width, DEF_PROPERTY_WIDTH);
	info_window_last_height = MAX(info_window_last_height, DEF_PROPERTY_HEIGHT);

	gtk_widget_destroy(id->window);
}

static void info_window_close_cb(GtkWidget *widget, gpointer data)
{
	InfoData *id = data;

	info_window_close(id);
}

static gint info_window_delete_cb(GtkWidget *widget, GdkEventAny *event, gpointer data)
{
	InfoData *id = data;

	info_window_close(id);
	return TRUE;
}

static void info_window_destroy_cb(GtkWidget *widget, gpointer data)
{
	InfoData *id = data;

	info_tabs_free(id);
	path_list_free(id->list);
	g_free(id);
}

void info_window_new(const gchar *path, GList *list)
{
	InfoData *id;
	GtkWidget *main_vbox;
	GtkWidget *paned;
	GtkWidget *hbox;
	GtkWidget *button;
	GtkWidget *label;
	GdkGeometry geometry;

	if (!path && !list) return;

	if (!list)
		{
		list = g_list_append(NULL, g_strdup(path));
		}

	id = g_new0(InfoData, 1);

	id->list = list;
	id->path = (gchar *)id->list->data;
	id->updated = FALSE;

	id->window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_type_hint(GTK_WINDOW(id->window), GDK_WINDOW_TYPE_HINT_DIALOG);
	window_set_icon(id->window, NULL, NULL);

	gtk_window_set_resizable(GTK_WINDOW(id->window), TRUE);
	gtk_window_set_title(GTK_WINDOW(id->window), _("Image properties - GQview"));
	gtk_window_set_wmclass(GTK_WINDOW(id->window), "properties", "GQview");

	geometry.min_width = 32;
	geometry.min_height = 32;
	geometry.base_width = DEF_PROPERTY_WIDTH;
	geometry.base_height = DEF_PROPERTY_HEIGHT;
	gtk_window_set_geometry_hints(GTK_WINDOW(id->window), NULL, &geometry,
				      GDK_HINT_MIN_SIZE | GDK_HINT_BASE_SIZE);


	gtk_window_set_default_size(GTK_WINDOW(id->window), info_window_last_width, info_window_last_height);
	gtk_container_set_border_width(GTK_CONTAINER(id->window), PREF_PAD_BORDER);

	g_signal_connect(G_OBJECT(id->window), "delete_event",
			 G_CALLBACK(info_window_delete_cb), id);
	g_signal_connect(G_OBJECT(id->window), "destroy",
			 G_CALLBACK(info_window_destroy_cb), id);

	paned = gtk_hpaned_new();
	gtk_container_add(GTK_CONTAINER(id->window), paned);
	gtk_widget_show(paned);

	id->image = image_new(FALSE);
	image_set_update_func(id->image, info_window_image_update_cb, id);

	image_set_button_func(id->image, info_window_image_button_cb, id);
	image_set_scroll_func(id->image, info_window_image_scroll_cb, id);

	gtk_widget_set_size_request(id->image->widget, IMAGE_SIZE_W, IMAGE_SIZE_H);
	gtk_paned_pack1(GTK_PANED(paned), id->image->widget, FALSE, TRUE);
	gtk_widget_show(id->image->widget);

	main_vbox = gtk_vbox_new(FALSE, 0);
	gtk_paned_pack2(GTK_PANED(paned), main_vbox, TRUE, TRUE);
	gtk_widget_show(main_vbox);

	hbox = pref_box_new(main_vbox, FALSE, GTK_ORIENTATION_HORIZONTAL, PREF_PAD_SPACE);
	label = pref_label_new(hbox, _("Filename:"));
	pref_label_bold(label, TRUE, FALSE);

	id->name_entry = gtk_entry_new();
	gtk_editable_set_editable(GTK_EDITABLE(id->name_entry), FALSE);
	gtk_box_pack_start(GTK_BOX(hbox), id->name_entry, TRUE, TRUE, 0);
	gtk_widget_show(id->name_entry);

	id->notebook = gtk_notebook_new();
	gtk_notebook_set_tab_pos(GTK_NOTEBOOK(id->notebook), GTK_POS_TOP);
	gtk_box_pack_start(GTK_BOX(main_vbox), id->notebook, TRUE, TRUE, 5);
	gtk_widget_show(id->notebook);

	pref_spacer(main_vbox, PREF_PAD_GAP);

	hbox = pref_box_new(main_vbox, FALSE, GTK_ORIENTATION_HORIZONTAL, PREF_PAD_GAP);

	id->button_back = pref_button_new(hbox, GTK_STOCK_GO_BACK, NULL, TRUE,
					  G_CALLBACK(info_window_back_cb), id);
	gtk_widget_set_sensitive(id->button_back, FALSE);

	id->button_next = pref_button_new(hbox, GTK_STOCK_GO_FORWARD, NULL, TRUE,
					  G_CALLBACK(info_window_next_cb), id);
	gtk_widget_set_sensitive(id->button_next, (id->list->next != NULL));

	if (id->list->next)
		{
		id->label_count = pref_label_new(hbox, "");
		}

	button = pref_button_new(NULL, GTK_STOCK_CLOSE, NULL, FALSE,
				 G_CALLBACK(info_window_close_cb), id);
	gtk_box_pack_end(GTK_BOX(hbox), button, FALSE, FALSE, 0);
	gtk_widget_show(button);

	/* set up tabs */

	info_tabs_init(id);

	/* fill it */

	info_window_sync(id, id->path);

	/* finish */

	info_window_dnd_init(id);

	gtk_widget_show(id->window);
}

