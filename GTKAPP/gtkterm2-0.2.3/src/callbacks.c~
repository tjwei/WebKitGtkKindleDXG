#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <stdio.h>
#include <gtk/gtk.h>
#include <gdk/gdkx.h>
#include <gdk/gdkkeysyms.h> 
#include <vte/vte.h>
#include <gtk/gtkwindow.h>


#include "prefs.h"
#include "callbacks.h"
#include "interface.h"
#include "support.h"



static void
set_menuitem_text (GtkWidget  *mi,
                   const char *text,
                   gboolean    strip_mnemonic)
{
  GtkWidget *child;

  child = gtk_bin_get_child (GTK_BIN (mi));

  if (child && GTK_IS_LABEL (child))
    {
      const char *label;
      char *no_mnemonic;
      
      label = NULL;
      no_mnemonic = NULL;
      
      if (strip_mnemonic)
        {
          const char *src;
          char *dest;

          no_mnemonic = g_strdup (text);
          dest = no_mnemonic;
          src = text;

          while (*src)
            {
              if (*src != '_')
                {
                  *dest = *src;
                  ++dest;
                }
              
              ++src;
            }
          *dest = '\0';

          label = no_mnemonic;
        }
      else
        {
          label = text;
        }

      if (strip_mnemonic)
        gtk_label_set_text (GTK_LABEL (child), label);
      else
        gtk_label_set_text_with_mnemonic (GTK_LABEL (child), label);
      
      if (no_mnemonic)
        g_free (no_mnemonic);
    }
}


void
on_new_window_activate                 (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{

}


void
on_new_tab_activate                    (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
	gtkTermPref *pref;
	
	pref = (gtkTermPref *) user_data;
	
	create_terminal(pref->notebook, lookup_widget(GTK_WIDGET(menuitem), "window"), pref);

	gtk_notebook_set_current_page (GTK_NOTEBOOK(pref->notebook), pref->nbpage);
	pref->nbpage++;
	
	if(pref->nbpage >1)
	{
		gtk_notebook_set_show_tabs(GTK_NOTEBOOK(pref->notebook), TRUE);
	}
}


void
on_close_window_activate               (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{

}


void
on_close_tab_activate                  (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
	gint pagenr;
	gtkTermPref *pref;
	
	pref = (gtkTermPref *) user_data;

	pagenr = gtk_notebook_get_current_page(GTK_NOTEBOOK(pref->notebook));

	gtk_notebook_remove_page(GTK_NOTEBOOK(pref->notebook), pagenr);

	pref->nbpage--;

	if(pref->nbpage == 1 && pref->showTabsByOneTerminal == 0)
	{
		gtk_notebook_set_show_tabs(GTK_NOTEBOOK(pref->notebook), FALSE);
	}

	if(gtk_notebook_get_current_page(GTK_NOTEBOOK(pref->notebook)) == -1 && pref->quitPRGonExitLastTerminal == TRUE)
	{
		gtk_main_quit();
	}

}


void
on_copy_activate                       (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{

}


void
on_paste_activate                      (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{

}


void
on_full_screen_activate                (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
	gtkTermPref *pref;
	
	pref = (gtkTermPref *) user_data;

	//wmspec_change_state (TRUE, GTK_WIDGET (menuitem)->window,
   //                    gdk_atom_intern ("_NET_WM_STATE_FULLSCREEN",
   //                                     FALSE),
   //                    GDK_NONE);
	//gtk_window_fullscreen (GTK_WINDOW(lookup_widget(GTK_WIDGET(menuitem), "window")));
	
	/*if (setting)
	{
		set_menuitem_text (menuitem, _("_Restore normal size"), FALSE);
	}
	else
	{
		set_menuitem_text (menuitem, _("_Full screen"), FALSE);
	}*/
	
	if(pref->fullscreen == TRUE)
	{
		gtk_window_unfullscreen (GTK_WINDOW(lookup_widget(GTK_WIDGET(menuitem), "window")));
		set_menuitem_text (GTK_WIDGET(menuitem), _("_Full screen"), FALSE);
		pref->fullscreen = FALSE;
	}
	else
	{
		gtk_window_fullscreen (GTK_WINDOW(lookup_widget(GTK_WIDGET(menuitem), "window")));
		set_menuitem_text (GTK_WIDGET(menuitem), _("_Restore normal size"), FALSE);
		pref->fullscreen = TRUE;
	}
}


void
on_hide_menu_activate                  (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{

}


void
on_info_activate                       (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
	gtk_widget_show(lookup_widget(GTK_WIDGET(menuitem), "window_about"));
}


void
on_window_about_close_button_activate  (GtkButton       *button,
                                        gpointer         user_data)
{
	gtk_widget_hide(lookup_widget(GTK_WIDGET(button), "window_about"));
}


void
window_title_changed(GtkWidget *widget, gpointer pref)
{
	GtkWidget *win;
	GtkWindow *window;

	win = lookup_widget(GTK_WIDGET(widget), "window");
	
	g_return_if_fail(VTE_TERMINAL(widget));
	g_return_if_fail(GTK_IS_WINDOW(win));
	g_return_if_fail(VTE_TERMINAL(widget)->window_title != NULL);
	window = GTK_WINDOW(win);

	gtkTermSetMPref(widget, pref, gtkTermFindMPref(VTE_TERMINAL(widget)->window_title, pref));

	gtk_window_set_title(window, VTE_TERMINAL (widget)->window_title);
}

gboolean test (VteTerminal *terminal,glong column,glong row,gpointer data)
{
	//printf("%dx%d", column, row);
	return TRUE;
}

void
commit(GtkWidget *widget, gchar *arg1, guint arg2, gpointer user_data)
{
	char* hehe=NULL;
	GArray *attributes;
	
 	fprintf(stdout, "%c\n", arg1[0]); fflush(stdout);
	
	if(arg1[0] == 'z')
	{
				attributes = g_array_new (FALSE, TRUE, sizeof (VteCharAttributes));
		      hehe = vte_terminal_get_text     ( VTE_TERMINAL (widget),
													//		1,
													//		1,
													//		10,
													//		10,
                                             test,
                                             NULL,
                                             attributes);
															
		fprintf(stdout, "%shehe\n", hehe); fflush(stdout);
		if(hehe!=NULL)	free(hehe);
	}
	//fprintf(stdout, "%s\n", arg1); fflush(stdout);
}

void
char_size_changed(GtkWidget *widget, guint width, guint height, gpointer data)
{
	VteTerminal *terminal;
	GtkWindow *window;
	GdkGeometry geometry;
	int xpad, ypad;

	g_return_if_fail(GTK_IS_WINDOW(data));
	g_return_if_fail(VTE_IS_TERMINAL(widget));

	terminal = VTE_TERMINAL(widget);
	window = GTK_WINDOW(data);

	vte_terminal_get_padding(terminal, &xpad, &ypad);

	geometry.width_inc = terminal->char_width;
	geometry.height_inc = terminal->char_height;
	geometry.base_width = xpad;
	geometry.base_height = ypad;
	geometry.min_width = xpad + terminal->char_width * 2;
	geometry.min_height = ypad + terminal->char_height * 2;

	gtk_window_set_geometry_hints(window, widget, &geometry,
				      GDK_HINT_RESIZE_INC |
				      GDK_HINT_BASE_SIZE |
				      GDK_HINT_MIN_SIZE);
}

void
destroy_and_quit(GtkWidget *widget, gpointer data)
{
	if (GTK_IS_CONTAINER(data)) {
		gtk_container_remove(GTK_CONTAINER(data), widget);
	} else {
		gtk_widget_destroy(widget);
	}
	gtk_main_quit();
}

void
destroy_and_quit_eof(GtkWidget *widget, gpointer data)
{
	//g_print("Detected EOF.\n");
	//destroy_and_quit(widget, data);
	on_close_tab_activate(NULL, data);
}

void
destroy_and_quit_exited(GtkWidget *widget, gpointer data)
{
	//g_print("Detected child exit.\n");
	//destroy_and_quit(widget, data);
	on_close_tab_activate(NULL, data);
}

void
status_line_changed(GtkWidget *widget, gpointer data)
{
	g_print("Status = `%s'.\n",
		vte_terminal_get_status_line(VTE_TERMINAL(widget)));
}

int
button_pressed(GtkWidget *widget, GdkEventButton *event, gpointer data)
{
	VteTerminal *terminal;
	char *match;
	int tag;
	gint xpad, ypad;
	switch (event->button) {
	case 3:
		terminal = VTE_TERMINAL(widget);
		vte_terminal_get_padding(terminal, &xpad, &ypad);
		match = vte_terminal_match_check(terminal,
						 (event->x - ypad) /
						 terminal->char_width,
						 (event->y - ypad) /
						 terminal->char_height,
						 &tag);
		if (match != NULL) {
			g_print("Matched `%s' (%d).\n", match, tag);
			g_free(match);
			if (GPOINTER_TO_INT(data) != 0) {
				vte_terminal_match_remove(terminal, tag);
			}
		}
		break;
	case 1:
	case 2:
	default:
		break;
	}
	return FALSE;
}

void
iconify_window(GtkWidget *widget, gpointer data)
{
	if (GTK_IS_WIDGET(data)) {
		if ((GTK_WIDGET(data))->window) {
			gdk_window_iconify((GTK_WIDGET(data))->window);
		}
	}
}

void
deiconify_window(GtkWidget *widget, gpointer data)
{
	if (GTK_IS_WIDGET(data)) {
		if ((GTK_WIDGET(data))->window) {
			gdk_window_deiconify((GTK_WIDGET(data))->window);
		}
	}
}

void
raise_window(GtkWidget *widget, gpointer data)
{
	if (GTK_IS_WIDGET(data)) {
		if ((GTK_WIDGET(data))->window) {
			gdk_window_raise((GTK_WIDGET(data))->window);
		}
	}
}

void
lower_window(GtkWidget *widget, gpointer data)
{
	if (GTK_IS_WIDGET(data)) {
		if ((GTK_WIDGET(data))->window) {
			gdk_window_lower((GTK_WIDGET(data))->window);
		}
	}
}

void
maximize_window(GtkWidget *widget, gpointer data)
{
	if (GTK_IS_WIDGET(data)) {
		if ((GTK_WIDGET(data))->window) {
			gdk_window_maximize((GTK_WIDGET(data))->window);
		}
	}
}

void
restore_window(GtkWidget *widget, gpointer data)
{
	if (GTK_IS_WIDGET(data)) {
		if ((GTK_WIDGET(data))->window) {
			gdk_window_unmaximize((GTK_WIDGET(data))->window);
		}
	}
}

void
refresh_window(GtkWidget *widget, gpointer data)
{
	GdkRectangle rect;
	if (GTK_IS_WIDGET(data)) {
		if ((GTK_WIDGET(data))->window) {
			rect.x = rect.y = 0;
			rect.width = (GTK_WIDGET(data))->allocation.width;
			rect.height = (GTK_WIDGET(data))->allocation.height;
			gdk_window_invalidate_rect((GTK_WIDGET(data))->window,
						   &rect, TRUE);
		}
	}
}

void
resize_window(GtkWidget *widget, guint width, guint height, gpointer data)
{
	VteTerminal *terminal;
	gint owidth, oheight;
	if ((GTK_IS_WINDOW(data)) && (width >= 2) && (height >= 2)) {
		terminal = VTE_TERMINAL(widget);
		/* Take into account padding and border overhead. */
		gtk_window_get_size(GTK_WINDOW(data), &owidth, &oheight);
		owidth -= terminal->char_width * terminal->column_count;
		oheight -= terminal->char_height * terminal->row_count;
		gtk_window_resize(GTK_WINDOW(data),
				  width + owidth, height + oheight);
	}
}

void
move_window(GtkWidget *widget, guint x, guint y, gpointer data)
{
	if (GTK_IS_WIDGET(data)) {
		if ((GTK_WIDGET(data))->window) {
			gdk_window_move((GTK_WIDGET(data))->window, x, y);
		}
	}
}

void
adjust_font_size(GtkWidget *widget, gpointer data, gint howmuch)
{
	VteTerminal *terminal;
	PangoFontDescription *desired;
	gint newsize;
	gint columns, rows, owidth, oheight;

	/* Read the screen dimensions in cells. */
	terminal = VTE_TERMINAL(widget);
	columns = terminal->column_count;
	rows = terminal->row_count;

	/* Take into account padding and border overhead. */
	gtk_window_get_size(GTK_WINDOW(data), &owidth, &oheight);
	owidth -= terminal->char_width * terminal->column_count;
	oheight -= terminal->char_height * terminal->row_count;

	/* Calculate the new font size. */
	desired = pango_font_description_copy(vte_terminal_get_font(terminal));
	newsize = pango_font_description_get_size(desired) / PANGO_SCALE;
	newsize += howmuch;
	pango_font_description_set_size(desired,
					CLAMP(newsize, 4, 144) * PANGO_SCALE);

	/* Change the font, then resize the window so that we have the same
	 * number of rows and columns. */
	vte_terminal_set_font(terminal, desired);
	gtk_window_resize(GTK_WINDOW(data),
			  columns * terminal->char_width + owidth,
			  rows * terminal->char_height + oheight);

	pango_font_description_free(desired);
}

void
increase_font_size(GtkWidget *widget, gpointer data)
{
	adjust_font_size(widget, data, 1);
}

void
decrease_font_size(GtkWidget *widget, gpointer data)
{
	adjust_font_size(widget, data, -1);
}

void
mess_with_fontconfig(void)
{
#ifdef HAVE_XFT2
	/* Is this even a good idea?  Probably not, since this doesn't expose
	 * these fonts to the gnome-font-properties capplet. */
	FcInit();
	FcConfigAppFontAddDir(NULL, DATADIR "/" PACKAGE "/fonts");
#endif
}

gboolean
read_and_feed(GIOChannel *source, GIOCondition condition, gpointer data)
{
	char buf[2048];
	gsize size;
	GIOStatus status;
	g_return_val_if_fail(VTE_IS_TERMINAL(data), FALSE);
	status = g_io_channel_read_chars(source, buf, sizeof(buf),
					 &size, NULL);
	if ((status == G_IO_STATUS_NORMAL) && (size > 0)) {
		vte_terminal_feed(VTE_TERMINAL(data), buf, size);
		return TRUE;
	}
	return FALSE;
}

void
disconnect_watch(GtkWidget *widget, gpointer data)
{
	g_source_remove(GPOINTER_TO_INT(data));
}

void
clipboard_get(GtkClipboard *clipboard, GtkSelectionData *selection_data,
	      guint info, gpointer owner)
{
	/* No-op. */
	return;
}

#ifdef TIOCCONS

void
take_xconsole_ownership(GtkWidget *widget, gpointer data)
{
	char *name, hostname[255];
	GdkDisplay *display;
	Atom xatom;
	GdkAtom atom;
	GtkClipboard *clipboard;
	GtkTargetEntry targets[] = {
		{"UTF8_STRING", 0, 0},
		{"COMPOUND_TEXT", 0, 0},
		{"TEXT", 0, 0},
		{"STRING", 0, 0},
	};

	memset(hostname, '\0', sizeof(hostname));
	gethostname(hostname, sizeof(hostname) - 1);
	display = gdk_display_get_default();

	name = g_strdup_printf("MIT_CONSOLE_%s", hostname);
	xatom = gdk_x11_get_xatom_by_name_for_display(display, name);
	atom = gdk_x11_xatom_to_atom_for_display(display, xatom);
	clipboard = gtk_clipboard_get(atom);
	g_free(name);

	gtk_clipboard_set_with_owner(clipboard,
				     targets,
				     G_N_ELEMENTS(targets),
				     clipboard_get,
				     (GtkClipboardClearFunc)gtk_main_quit,
				     G_OBJECT(widget));
}

#endif

gboolean
nb_handle_key (GtkWidget* fenster, GdkEventKey* event, gpointer user_data)
{
	gint cur_term;
	gint next_term;
	GtkWidget *notebook;
	gtkTermPref *pref;

	pref = (gtkTermPref *) user_data;
	notebook = pref->notebook;

	if (event->state & GDK_SHIFT_MASK)
	{
		if ((event->keyval == GDK_Right) || (event->keyval == GDK_KP_Right))
		{
			cur_term = gtk_notebook_get_current_page (GTK_NOTEBOOK(notebook));
			gtk_notebook_next_page(GTK_NOTEBOOK(notebook));
			next_term = gtk_notebook_get_current_page (GTK_NOTEBOOK(notebook));
			if (cur_term == next_term)
			{
				gtk_notebook_set_page(GTK_NOTEBOOK(notebook), 0);
			}

			event->state = event->keyval = event->length = 0;
			event->string = NULL;

			return TRUE;
		}

		else if ((event->keyval == GDK_Left) || (event->keyval == GDK_KP_Left))
		{
			cur_term = gtk_notebook_get_current_page (GTK_NOTEBOOK(notebook));
			if (cur_term == 0)
			{
				gtk_notebook_set_page(GTK_NOTEBOOK(notebook), -1);
			}
			else
			{
				gtk_notebook_prev_page (GTK_NOTEBOOK(notebook));
			}

			event->state = event->keyval = event->length = 0;
			event->string = NULL;

			return TRUE;
		}
	}
	if (event->state & GDK_CONTROL_MASK)
	{
		if (event->keyval == GDK_n)
		{
			on_new_tab_activate (GTK_MENU_ITEM(lookup_widget(GTK_WIDGET(fenster), "new_tab")), pref);

			event->state = event->keyval = event->length = 0;
			event->string = NULL;

			return TRUE;
		}
	}

	return FALSE;
}

void on_commit (VteTerminal *vteterminal, gpointer user_data)
{
	printf("Commit; %s\n", vteterminal->icon_title);fflush(stdout);
}
