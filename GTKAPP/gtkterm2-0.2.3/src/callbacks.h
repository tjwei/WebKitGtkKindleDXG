#include <gtk/gtk.h>


void
on_new_window_activate                 (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_new_tab_activate                    (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_close_window_activate               (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_close_tab_activate                  (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_copy_activate                       (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_paste_activate                      (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_full_screen_activate                (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_hide_menu_activate                  (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_info_activate                       (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_window_about_close_button_activate  (GtkButton       *button,
                                        gpointer         user_data);

/*void
window_title_changed				   (GtkWidget *widget,
										gpointer win);*/

void
window_title_changed(GtkWidget *widget, gpointer pref);

void
commit(GtkWidget *widget, gchar *arg1, guint arg2, gpointer user_data);

void
char_size_changed(GtkWidget *widget, guint width, guint height, gpointer data);

void
destroy_and_quit_eof				   (GtkWidget *widget,
										gpointer data);

void
destroy_and_quit_exited				   (GtkWidget *widget,
										gpointer data);

void
status_line_changed					   (GtkWidget *widget,
										gpointer data);

int
button_pressed						   (GtkWidget *widget,
										GdkEventButton *event,
										gpointer data);

void
iconify_window(GtkWidget *widget, gpointer data);

void
deiconify_window(GtkWidget *widget, gpointer data);

void
raise_window(GtkWidget *widget, gpointer data);

void
lower_window(GtkWidget *widget, gpointer data);

void
maximize_window(GtkWidget *widget, gpointer data);

void
restore_window(GtkWidget *widget, gpointer data);

void
refresh_window(GtkWidget *widget, gpointer data);

void
resize_window(GtkWidget *widget, guint width, guint height, gpointer data);

void
move_window(GtkWidget *widget, guint x, guint y, gpointer data);

void
adjust_font_size(GtkWidget *widget, gpointer data, gint howmuch);

void
increase_font_size(GtkWidget *widget, gpointer data);

void
decrease_font_size(GtkWidget *widget, gpointer data);

void
mess_with_fontconfig(void);

gboolean
read_and_feed(GIOChannel *source, GIOCondition condition, gpointer data);

void
disconnect_watch(GtkWidget *widget, gpointer data);

void
clipboard_get(GtkClipboard *clipboard, GtkSelectionData *selection_data,
	      guint info, gpointer owner);

void
take_xconsole_ownership(GtkWidget *widget, gpointer data);

gboolean
nb_handle_key (GtkWidget* fenster, GdkEventKey* event, gpointer user_data);

void on_commit (VteTerminal *vteterminal, gpointer user_data);
