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

#include "cache.h"
#include "collect.h"
#include "collect-io.h"
#include "dnd.h"
#include "editors.h"
#include "filelist.h"
#include "img-view.h"
#include "layout.h"
#include "layout_image.h"
#include "menu.h"
#include "pixbuf_util.h"
#include "preferences.h"
#include "rcfile.h"
#include "remote.h"
#include "similar.h"
#include "slideshow.h"
#include "utilops.h"
#include "ui_bookmark.h"
#include "ui_help.h"
#include "ui_fileops.h"
#include "ui_tabcomp.h"
#include "ui_utildlg.h"

#include <gdk/gdkkeysyms.h> /* for keyboard values */


#include <math.h>


static RemoteConnection *gqview_remote = NULL;
static CollectionData *gqview_command_collection = NULL;


/*
 *-----------------------------------------------------------------------------
 * misc (public)
 *-----------------------------------------------------------------------------
 */ 

void window_set_icon(GtkWidget *window, const gchar *icon, const gchar *file)
{
	if (!icon && !file) icon = PIXBUF_INLINE_ICON;

	if (icon)
		{
		GdkPixbuf *pixbuf;

		pixbuf = pixbuf_inline(icon);
		if (pixbuf)
			{
			gtk_window_set_icon(GTK_WINDOW(window), pixbuf);
			g_object_unref(pixbuf);
			}
		}
	else
		{
		gtk_window_set_icon_from_file(GTK_WINDOW(window), file, NULL);
		}
}

gint window_maximized(GtkWidget *window)
{
	GdkWindowState state;

	if (!window || !window->window) return FALSE;

	state = gdk_window_get_state(window->window);
	return (state & GDK_WINDOW_STATE_MAXIMIZED);
}

gdouble get_zoom_increment(void)
{
	return ((zoom_increment != 0) ? (gdouble)zoom_increment / 10.0 : 1.0);
}

/*
 *-----------------------------------------------------------------------------
 * Open  browser with the help Documentation
 *-----------------------------------------------------------------------------
 */

static gchar *command_result(const gchar *binary, const gchar *command)
{
	gchar *result = NULL;
	FILE *f;
	char buf[2048];
	int l;

	if (!binary) return NULL;
	if (!file_in_path(binary)) return NULL;

	if (!command) return g_strdup(binary);
	if (command[0] == '!') return g_strdup(command + 1);

	f = popen(command, "r");
	if (!f) return NULL;

	while ((l = fread(buf, sizeof(char), sizeof(buf), f)) > 0)
		{
		if (!result)
			{
			int n = 0;

			while (n < l && buf[n] != '\n' && buf[n] != '\r') n++;
			if (n > 0) result = g_strndup(buf, n);
			}
		}

	pclose(f);

	return result;
}

static void help_browser_command(const gchar *command, const gchar *path)
{
	gchar *result;
	gchar *buf;
	gchar *begin;
	gchar *end;

	if (!command || !path) return;

	if (debug) printf("Help command pre \"%s\", \"%s\"\n", command, path);

	buf = g_strdup(command);
	begin = strstr(buf, "%s");
	if (begin)
		{
		*begin = '\0';
		end = begin + 2;
		begin = buf;

		result = g_strdup_printf("%s%s%s &", begin, path, end);
		}
	else
		{
		result = g_strdup_printf("%s \"%s\" &", command, path);
		}
	g_free(buf);

	if (debug) printf("Help command post [%s]\n", result);

	system(result);

	g_free(result);
}

/*
 * each set of 2 strings is one browser:
 *   the 1st is the binary to look for in the path
 *   the 2nd has 3 capabilities:
 *        NULL     exec binary with html file path as command line
 *        string   exec string and use results for command line
 *        !string  use text following ! as command line, replacing optional %s with html file path
*/
static gchar *html_browsers[] =
{
	/* Redhat has a nifty htmlview script to start the user's preferred browser */
	"htmlview",	NULL,
	/* GNOME 2 */
	"gconftool-2",	"gconftool-2 -g /desktop/gnome/url-handlers/http/command",
	/* KDE */
	"kfmclient",	"!kfmclient exec \"%s\"",
	/* use fallbacks */
	"firefox",	NULL,
	"mozilla",	NULL,
	"konqueror",	NULL,
	"netscape",	NULL,
	NULL,		NULL
};

static void help_browser_run(void)
{
	gchar *result = NULL;
	gint i;

	i = 0;
	while (!result && html_browsers[i])
		{
		result = command_result(html_browsers[i], html_browsers[i+1]);
		i += 2;
		}

	if (!result)
		{
		printf("Unable to detect an installed browser.\n");
		return;
		}

	help_browser_command(result, GQVIEW_HTMLDIR "/index.html");

	g_free(result);
}

/*
 *-----------------------------------------------------------------------------
 * help window
 *-----------------------------------------------------------------------------
 */ 

static GtkWidget *help_window = NULL;

static void help_window_destroy_cb(GtkWidget *window, gpointer data)
{
	help_window = NULL;
}

void help_window_show(const gchar *key)
{
	if (key && strcmp(key, "html_contents") == 0)
		{
		help_browser_run();
		return;
		}

	if (help_window)
		{
		gtk_window_present(GTK_WINDOW(help_window));
		if (key) help_window_set_key(help_window, key);
		return;
		}

	help_window = help_window_new(_("Help - GQview"), "GQview", "help",
                                      GQVIEW_HELPDIR "/README", key);
	g_signal_connect(G_OBJECT(help_window), "destroy",
			 G_CALLBACK(help_window_destroy_cb), NULL);
}


/*
 *-----------------------------------------------------------------------------
 * keyboard functions
 *-----------------------------------------------------------------------------
 */

void keyboard_scroll_calc(gint *x, gint *y, GdkEventKey *event)
{
	static gint delta = 0;
	static guint32 time_old = 0;
	static guint keyval_old = 0;

	if (event->state & GDK_CONTROL_MASK)
		{
		if (*x < 0) *x = G_MININT / 2;
		if (*x > 0) *x = G_MAXINT / 2;
		if (*y < 0) *y = G_MININT / 2;
		if (*y > 0) *y = G_MAXINT / 2;

		return;
		}

	if (progressive_key_scrolling)
		{
		guint32 time_diff;

		time_diff = event->time - time_old;

		/* key pressed within 125ms ? (1/8 second) */
		if (time_diff > 125 || event->keyval != keyval_old) delta = 0;

		time_old = event->time;
		keyval_old = event->keyval;

		delta += 2;
		}
	else
		{
		delta = 8;
		}

	*x = *x * delta;
	*y = *y * delta;
}


/*
 *-----------------------------------------------------------------------------
 * remote functions
 *-----------------------------------------------------------------------------
 */

static void gr_image_next(const gchar *text, gpointer data)
{
	layout_image_next(NULL);
}

static void gr_image_prev(const gchar *text, gpointer data)
{
	layout_image_prev(NULL);
}

static void gr_image_first(const gchar *text, gpointer data)
{
	layout_image_first(NULL);
}

static void gr_image_last(const gchar *text, gpointer data)
{
	layout_image_last(NULL);
}

static void gr_fullscreen_toggle(const gchar *text, gpointer data)
{
	layout_image_full_screen_toggle(NULL);
}

static void gr_fullscreen_start(const gchar *text, gpointer data)
{
	layout_image_full_screen_start(NULL);
}

static void gr_fullscreen_stop(const gchar *text, gpointer data)
{
	layout_image_full_screen_stop(NULL);
}

static void gr_slideshow_start_rec(const gchar *text, gpointer data)
{
	GList *list;

	list = path_list_recursive(text);
	if (!list) return;
printf("length: %d\n", g_list_length(list));
	layout_image_slideshow_stop(NULL);
	layout_image_slideshow_start_from_list(NULL, list);
}

static void gr_slideshow_toggle(const gchar *text, gpointer data)
{
	layout_image_slideshow_toggle(NULL);
}

static void gr_slideshow_start(const gchar *text, gpointer data)
{
	layout_image_slideshow_start(NULL);
}

static void gr_slideshow_stop(const gchar *text, gpointer data)
{
	layout_image_slideshow_stop(NULL);
}

static void gr_slideshow_delay(const gchar *text, gpointer data)
{
	gdouble n;

	n = strtod(text, NULL);
	if (n < SLIDESHOW_MIN_SECONDS || n > SLIDESHOW_MAX_SECONDS)
		{
		gchar *buf;

		buf = g_strdup_printf("Remote slideshow delay out of range (%.1f to %.1f)\n",
				      SLIDESHOW_MIN_SECONDS, SLIDESHOW_MAX_SECONDS);
		print_term(buf);
		g_free(buf);

		return;
		}
	slideshow_delay = (gint)(n * 10.0 + 0.01);
}

static void gr_tools_show(const gchar *text, gpointer data)
{
	gint popped;
	gint hidden;

	if (layout_tools_float_get(NULL, &popped, &hidden) && hidden)
		{
		layout_tools_float_set(NULL, popped, FALSE);
		}
}

static void gr_tools_hide(const gchar *text, gpointer data)
{
	gint popped;
	gint hidden;

	if (layout_tools_float_get(NULL, &popped, &hidden) && !hidden)
		{
		layout_tools_float_set(NULL, popped, TRUE);
		}
}

static gint gr_quit_idle_cb(gpointer data)
{
	exit_gqview();

	return FALSE;
}

static void gr_quit(const gchar *text, gpointer data)
{
	/* schedule exit when idle, if done from within a
	 * remote handler remote_close will crash
	 */
	g_idle_add(gr_quit_idle_cb, NULL);
}

static void gr_file_load(const gchar *text, gpointer data)
{
	if (isfile(text))
		{
		if (file_extension_match(text, ".gqv"))
			{
			collection_window_new(text);
			}
		else
			{
			layout_set_path(NULL, text);
			}
		}
	else if (isdir(text))
		{
		layout_set_path(NULL, text);
		}
	else
		{
		printf("remote sent filename that does not exist:\"%s\"\n", text);
		}
}

static void gr_file_view(const gchar *text, gpointer data)
{
	view_window_new(text);
}

static void gr_list_clear(const gchar *text, gpointer data)
{
	if (gqview_command_collection) collection_unref(gqview_command_collection);
	gqview_command_collection = NULL;
}

static void gr_list_add(const gchar *text, gpointer data)
{
	gint new = TRUE;

	if (!gqview_command_collection)
		{
		CollectionData *cd;

		cd = collection_new("");

		g_free(cd->path);
		cd->path = NULL;
		g_free(cd->name);
		cd->name = g_strdup(_("Command line"));

		gqview_command_collection = cd;
		}
	else
		{
		new = (!collection_get_first(gqview_command_collection));
		}

	if (collection_add(gqview_command_collection, text, FALSE) && new)
		{
		layout_image_set_collection(NULL, gqview_command_collection,
					    collection_get_first(gqview_command_collection));
		}
}

static void gr_raise(const gchar *text, gpointer data)
{
	LayoutWindow *lw = NULL;

	if (layout_valid(&lw))
		{
		gtk_window_present(GTK_WINDOW(lw->window));
		}
}

typedef struct _RemoteCommandEntry RemoteCommandEntry;
struct _RemoteCommandEntry {
	gchar *opt_s;
	gchar *opt_l;
	void (*func)(const gchar *text, gpointer data);
	gint needs_extra;
	gint prefer_command_line;
	gchar *description;
};

static RemoteCommandEntry remote_commands[] = {
	/* short, long                  callback,               extra, prefer,description */
	{ "-n", "--next",               gr_image_next,          FALSE, FALSE, N_("next image") },
	{ "-b", "--back",               gr_image_prev,          FALSE, FALSE, N_("previous image") },
	{ NULL, "--first",              gr_image_first,         FALSE, FALSE, N_("first image") },
        { NULL, "--last",               gr_image_last,          FALSE, FALSE, N_("last image") },
	{ "-f", "--fullscreen",         gr_fullscreen_toggle,   FALSE, TRUE,  N_("toggle full screen") },
	{ "-fs","--fullscreen-start",   gr_fullscreen_start,    FALSE, FALSE, N_("start full screen") },
	{ "-fS","--fullscreen-stop",    gr_fullscreen_stop,     FALSE, FALSE, N_("stop full screen") },
	{ "-s", "--slideshow",          gr_slideshow_toggle,	FALSE, TRUE,  N_("toggle slide show") },
	{ "-ss","--slideshow-start",    gr_slideshow_start,     FALSE, FALSE, N_("start slide show") },
	{ "-sS","--slideshow-stop",     gr_slideshow_stop,      FALSE, FALSE, N_("stop slide show") },
	{ "-sr","--slideshow-recurse",  gr_slideshow_start_rec, TRUE,  FALSE, N_("start recursive slide show") },
	{ "-d", "--delay=",             gr_slideshow_delay,     TRUE,  FALSE, N_("set slide show delay in seconds") },
	{ "+t", "--tools-show",         gr_tools_show,          FALSE, TRUE,  N_("show tools") },
	{ "-t", "--tools-hide",	        gr_tools_hide,          FALSE, TRUE,  N_("hide tools") },
	{ "-q", "--quit",               gr_quit,                FALSE, FALSE, N_("quit") },
	{ NULL, "file:",                gr_file_load,           TRUE,  FALSE, N_("open file") },
	{ NULL, "view:",		gr_file_view,		TRUE,  FALSE, N_("open file in new window") },
	{ NULL, "--list-clear",         gr_list_clear,          FALSE, FALSE, NULL },
	{ NULL, "--list-add:",          gr_list_add,            TRUE,  FALSE, NULL },
	{ NULL, "raise",		gr_raise,		FALSE, FALSE, NULL },
	{ NULL, NULL, NULL, FALSE, FALSE, NULL }
};

static RemoteCommandEntry *gqview_remote_command_find(const gchar *text, const gchar **offset)
{
	gint match = FALSE;
	gint i;

	i = 0;
	while (!match && remote_commands[i].func != NULL)
		{
		if (remote_commands[i].needs_extra)
			{
			if (remote_commands[i].opt_s &&
			    strncmp(remote_commands[i].opt_s, text, strlen(remote_commands[i].opt_s)) == 0)
				{
				if (offset) *offset = text + strlen(remote_commands[i].opt_s);
				return &remote_commands[i];
				}
			else if (remote_commands[i].opt_l &&
				 strncmp(remote_commands[i].opt_l, text, strlen(remote_commands[i].opt_l)) == 0)
				{
				if (offset) *offset = text + strlen(remote_commands[i].opt_l);
				return &remote_commands[i];
				}
			}
		else
			{
			if ((remote_commands[i].opt_s && strcmp(remote_commands[i].opt_s, text) == 0) ||
			    (remote_commands[i].opt_l && strcmp(remote_commands[i].opt_l, text) == 0))
				{
				if (offset) *offset = text;
				return &remote_commands[i];
				}
			}

		i++;
		}

	return NULL;
}

static void gqview_remote_cb(RemoteConnection *rc, const gchar *text, gpointer data)
{
	RemoteCommandEntry *entry;
	const gchar *offset;

	entry = gqview_remote_command_find(text, &offset);
	if (entry && entry->func)
		{
		entry->func(offset, data);
		}
	else
		{
		printf("unknown remote command:%s\n", text);
		}
}

static void gqview_remote_help(void)
{
	gint i;

	print_term(_("Remote command list:\n"));

	i = 0;
	while (remote_commands[i].func != NULL)
		{
		if (remote_commands[i].description)
			{
			gchar *buf;

			buf = g_strdup_printf("  %-3s%s %-20s %s\n",
				(remote_commands[i].opt_s) ? remote_commands[i].opt_s : "",
				(remote_commands[i].opt_s && remote_commands[i].opt_l) ? "," : " ",
				(remote_commands[i].opt_l) ? remote_commands[i].opt_l : "",
				_(remote_commands[i].description));

			print_term(buf);
			g_free(buf);
			}
		i++;
		}
}

static GList *gqview_remote_build_list(GList *list, int argc, char *argv[])
{
	gint i;

	i = 1;
	while (i < argc)
		{
		RemoteCommandEntry *entry;

		entry = gqview_remote_command_find(argv[i], NULL);
		if (entry)
			{
			list = g_list_append(list, argv[i]);
			}
		i++;
		}

	return list;
}

static void gqview_remote_control(const gchar *arg_exec, GList *remote_list, const gchar *path,
				  GList *cmd_list, GList *collection_list)
{
	RemoteConnection *rc;
	gint started = FALSE;
	gchar *buf;

	buf = g_strconcat(homedir(), "/", GQVIEW_RC_DIR, "/.command", NULL);
	rc = remote_client_open(buf);
	if (!rc)
		{
		GString *command;
		GList *work;
		gint retry_count = 12;
		gint blank = FALSE;

		print_term(_("Remote GQview not running, starting..."));
		command = g_string_new(arg_exec);

		work = remote_list;
		while (work)
			{
			gchar *text;
			RemoteCommandEntry *entry;

			text = work->data;
			work = work->next;

			entry = gqview_remote_command_find(text, NULL);
			if (entry)
				{
				if (entry->prefer_command_line)
					{
					remote_list = g_list_remove(remote_list, text);
					g_string_append(command, " ");
					g_string_append(command, text);
					}
				if (entry->opt_l && strcmp(entry->opt_l, "file:") == 0)
					{
					blank = TRUE;
					}
				}
			}

		if (blank || cmd_list || path) g_string_append(command, " --blank");
		if (debug) g_string_append(command, " --debug");

		g_string_append(command, " &");
		system(command->str);
		g_string_free(command, TRUE);

		while (!rc && retry_count > 0)
			{
			usleep((retry_count > 10) ? 500000 : 1000000);
			rc = remote_client_open(buf);
			if (!rc) print_term(".");
			retry_count--;
			}

		print_term("\n");

		started = TRUE;
		}
	g_free(buf);

	if (rc)
		{
		GList *work;
		const gchar *prefix;
		gint use_path = TRUE;
		gint sent = FALSE;

		work = remote_list;
		while (work)
			{
			gchar *text;
			RemoteCommandEntry *entry;

			text = work->data;
			work = work->next;

			entry = gqview_remote_command_find(text, NULL);
			if (entry &&
			    entry->opt_l &&
			    strcmp(entry->opt_l, "file:") == 0) use_path = FALSE;

			remote_client_send(rc, text);

			sent = TRUE;
			}

		if (cmd_list && cmd_list->next)
			{
			prefix = "--list-add:";
			remote_client_send(rc, "--list-clear");
			}
		else
			{
			prefix = "file:";
			}

		work = cmd_list;
		while (work)
			{
			const gchar *name;
			gchar *text;

			name = work->data;
			work = work->next;

			text = g_strconcat(prefix, name, NULL);
			remote_client_send(rc, text);
			g_free(text);

			sent = TRUE;
			}

		if (path && !cmd_list && use_path)
			{
			gchar *text;

			text = g_strdup_printf("file:%s", path);
			remote_client_send(rc, text);
			g_free(text);

			sent = TRUE;
			}

		work = collection_list;
		while (work)
			{
			const gchar *name;
			gchar *text;

			name = work->data;
			work = work->next;

			text = g_strdup_printf("file:%s", name);
			remote_client_send(rc, text);
			g_free(text);

			sent = TRUE;
			}

		if (!started && !sent)
			{
			remote_client_send(rc, "raise");
			}
		}
	else
		{
		print_term(_("Remote not available\n"));
		}

	_exit(0);
}

/*
 *-----------------------------------------------------------------------------
 * command line parser (private) hehe, who needs popt anyway?
 *-----------------------------------------------------------------------------
 */ 

static gint startup_blank = FALSE;
static gint startup_full_screen = FALSE;
static gint startup_in_slideshow = FALSE;
static gint startup_command_line_collection = FALSE;


static void parse_command_line_add_file(const gchar *file_path, gchar **path, gchar **file,
				        GList **list, GList **collection_list)
{
	gchar *path_parsed;

	path_parsed = g_strdup(file_path);
	parse_out_relatives(path_parsed);

	if (file_extension_match(path_parsed, ".gqv"))
		{
		*collection_list = g_list_append(*collection_list, path_parsed);
		}
	else
		{
		if (!*path) *path = remove_level_from_path(path_parsed);
		if (!*file) *file = g_strdup(path_parsed);
		*list = g_list_prepend(*list, path_parsed);
		}
}

static void parse_command_line_add_dir(const gchar *dir, gchar **path, gchar **file,
				       GList **list)
{
	GList *files = NULL;
	gchar *path_parsed;

	path_parsed = g_strdup(dir);
	parse_out_relatives(path_parsed);

	if (path_list(path_parsed, &files, NULL))
		{
		GList *work;

		files = path_list_filter(files, FALSE);
		files = path_list_sort(files);

		work = files;
		while (work)
			{
			gchar *p;

			p = work->data;
			if (!*path) *path = remove_level_from_path(p);
			if (!*file) *file = g_strdup(p);
			*list = g_list_prepend(*list, p);

			work = work->next;
			}

		g_list_free(files);
		}

	g_free(path_parsed);
}

static void parse_command_line_process_dir(const gchar *dir, gchar **path, gchar **file,
					   GList **list, gchar **first_dir)
{
	
	if (!*list && !*first_dir)
		{
		*first_dir = g_strdup(dir);
		}
	else
		{
		if (*first_dir)
			{
			parse_command_line_add_dir(*first_dir, path, file, list);
			g_free(*first_dir);
			*first_dir = NULL;
			}
		parse_command_line_add_dir(dir, path, file, list);
		}
}

static void parse_command_line_process_file(const gchar *file_path, gchar **path, gchar **file,
					    GList **list, GList **collection_list, gchar **first_dir)
{
	
	if (*first_dir)
		{
		parse_command_line_add_dir(*first_dir, path, file, list);
		g_free(*first_dir);
		*first_dir = NULL;
		}
	parse_command_line_add_file(file_path, path, file, list, collection_list);
}

static void parse_command_line(int argc, char *argv[], gchar **path, gchar **file,
			       GList **cmd_list, GList **collection_list,
			       gchar **geometry)
{
	GList *list = NULL;
	GList *remote_list = NULL;
	gint remote_do = FALSE;
	gchar *first_dir = NULL;

	if (argc > 1)
		{
		gint i;
		gchar *base_dir = get_current_dir();
		i = 1;
		while (i < argc)
			{
			const gchar *cmd_line = argv[i];
			gchar *cmd_all = concat_dir_and_file(base_dir, cmd_line);

			if (cmd_line[0] == '/' && isdir(cmd_line))
				{
				parse_command_line_process_dir(cmd_line, path, file, &list, &first_dir);
				}
			else if (isdir(cmd_all))
				{
				parse_command_line_process_dir(cmd_all, path, file, &list, &first_dir);
				}
			else if (cmd_line[0] == '/' && isfile(cmd_line))
				{
				parse_command_line_process_file(cmd_line, path, file,
								&list, collection_list, &first_dir);
				}
			else if (isfile(cmd_all))
				{
				parse_command_line_process_file(cmd_all, path, file,
								&list, collection_list, &first_dir);
				}
			else if (strcmp(cmd_line, "--debug") == 0)
				{
				/* we now increment the debug state for verbosity */
				debug++;
				printf("debugging output enabled (level %d)\n", debug);
				}
			else if (strcmp(cmd_line, "+t") == 0 ||
				 strcmp(cmd_line, "--with-tools") == 0)
				{
				tools_float = FALSE;
				tools_hidden = FALSE;

				remote_list = g_list_append(remote_list, "+t");
				}
			else if (strcmp(cmd_line, "-t") == 0 ||
				 strcmp(cmd_line, "--without-tools") == 0)
				{
				tools_hidden = TRUE;

				remote_list = g_list_append(remote_list, "-t");
				}
			else if (strcmp(cmd_line, "-f") == 0 ||
				 strcmp(cmd_line, "--fullscreen") == 0)
				{
				startup_full_screen = TRUE;
				}
			else if (strcmp(cmd_line, "-s") == 0 ||
				 strcmp(cmd_line, "--slideshow") == 0)
				{
				startup_in_slideshow = TRUE;
				}
			else if (strcmp(cmd_line, "-l") == 0 ||
				 strcmp(cmd_line, "--list") == 0)
				{
				startup_command_line_collection = TRUE;
				}
			else if (strncmp(cmd_line, "--geometry=", 11) == 0)
				{
				if (!*geometry) *geometry = g_strdup(cmd_line + 11);
				}
			else if (strcmp(cmd_line, "-r") == 0 ||
				 strcmp(cmd_line, "--remote") == 0)
				{
				if (!remote_do)
					{
					remote_do = TRUE;
					remote_list = gqview_remote_build_list(remote_list, argc, argv);
					}
				}
			else if (strcmp(cmd_line, "-rh") == 0 ||
				 strcmp(cmd_line, "--remote-help") == 0)
				{
				gqview_remote_help();
				exit (0);
				}
			else if (strcmp(cmd_line, "--blank") == 0)
				{
				startup_blank = TRUE;
				}
			else if (strcmp(cmd_line, "-v") == 0 ||
				 strcmp(cmd_line, "--version") == 0)
				{
				printf("GQview %s\n", VERSION);
				exit (0);
				}
			else if (strcmp(cmd_line, "--alternate") == 0)
				{
				/* enable faster experimental algorithm */
				printf("Alternate similarity algorithm enabled\n");
				image_sim_alternate_set(TRUE);
				}
			else if (strcmp(cmd_line, "-h") == 0 ||
				 strcmp(cmd_line, "--help") == 0)
				{
				printf("GQview %s\n", VERSION);
				print_term(_("Usage: gqview [options] [path]\n\n"));
				print_term(_("valid options are:\n"));
				print_term(_("  +t, --with-tools           force show of tools\n"));
				print_term(_("  -t, --without-tools        force hide of tools\n"));
				print_term(_("  -f, --fullscreen           start in full screen mode\n"));
				print_term(_("  -s, --slideshow            start in slideshow mode\n"));
				print_term(_("  -l, --list                 open collection window for command line\n"));
				print_term(_("      --geometry=GEOMETRY    set main window location\n"));
				print_term(_("  -r, --remote               send following commands to open window\n"));
				print_term(_("  -rh,--remote-help          print remote command list\n"));
				print_term(_("  --debug                    turn on debug output\n"));
				print_term(_("  -v, --version              print version info\n"));
				print_term(_("  -h, --help                 show this message\n\n"));
				
#if 0
				/* these options are not officially supported!
				 * only for testing new features, no need to translate them */
				print_term(  "  --alternate                use alternate similarity algorithm\n");
#endif
				
				exit (0);
				}
			else if (!remote_do)
				{
				gchar *buf;

				buf = g_strdup_printf(_("invalid or ignored: %s\nUse --help for options\n"), cmd_line);
				print_term(buf);
				g_free(buf);
				}

			g_free(cmd_all);
			i++;
			}
		g_free(base_dir);
		parse_out_relatives(*path);
		parse_out_relatives(*file);
		}

	list = g_list_reverse(list);

	if (!*path && first_dir)
		{
		*path = first_dir;
		first_dir = NULL;

		parse_out_relatives(*path);
		}
	g_free(first_dir);

	if (remote_do)
		{
		gqview_remote_control(argv[0], remote_list, *path, list, *collection_list);
		}
	g_list_free(remote_list);

	if (list && list->next)
		{
		*cmd_list = list;
		}
	else
		{
		path_list_free(list);
		*cmd_list = NULL;
		}
}

/*
 *-----------------------------------------------------------------------------
 * startup, init, and exit
 *-----------------------------------------------------------------------------
 */ 

#define RC_HISTORY_NAME "history"

static void keys_load(void)
{
	gchar *path;

	path = g_strconcat(homedir(), "/", GQVIEW_RC_DIR, "/", RC_HISTORY_NAME, NULL);
	history_list_load(path);
	g_free(path);
}

static void keys_save(void)
{
	gchar *path;

	path = g_strconcat(homedir(), "/", GQVIEW_RC_DIR, "/", RC_HISTORY_NAME, NULL);
	history_list_save(path);
	g_free(path);
}

static void check_for_home_path(gchar *path)
{
	gchar *buf;

	buf = g_strconcat(homedir(), "/", path, NULL);
	if (!isdir(buf))
		{
		gchar *tmp;

		tmp = g_strdup_printf(_("Creating GQview dir:%s\n"), buf);
		print_term(tmp);
		g_free(tmp);

		if (!mkdir_utf8(buf, 0755))
			{
			tmp = g_strdup_printf(_("Could not create dir:%s\n"), buf);
			print_term(tmp);
			g_free(tmp);
			}
		}
	g_free(buf);
}

static void setup_default_options(void)
{
	gchar *path;
	gint i;

	for (i = 0; i < GQVIEW_EDITOR_SLOTS; i++)
		{
		editor_name[i] = NULL;
		editor_command[i] = NULL;
		}

	editor_reset_defaults();

	bookmark_add_default(_("Home"), homedir());
	path = concat_dir_and_file(homedir(), "Desktop");
	bookmark_add_default(_("Desktop"), path);
	g_free(path);
	path = concat_dir_and_file(homedir(), GQVIEW_RC_DIR_COLLECTIONS);
	bookmark_add_default(_("Collections"), path);
	g_free(path);

	g_free(safe_delete_path);
	safe_delete_path = concat_dir_and_file(homedir(), GQVIEW_RC_DIR_TRASH);

	for (i = 0; i < COLOR_PROFILE_INPUTS; i++)
		{
		color_profile_input_file[i] = NULL;
		color_profile_input_name[i] = NULL;
		}
}

static void exit_gqview_final(void)
{
	gchar *path;
	gchar *pathl;
	LayoutWindow *lw = NULL;

	remote_close(gqview_remote);

	collect_manager_flush();

	if (layout_valid(&lw))
		{
		main_window_maximized =  window_maximized(lw->window);
		if (!main_window_maximized)
			{
			layout_geometry_get(NULL, &main_window_x, &main_window_y,
					    &main_window_w, &main_window_h);
			}
		}

	layout_geometry_get_dividers(NULL, &window_hdivider_pos, &window_vdivider_pos);

	layout_views_get(NULL, &layout_view_tree, &layout_view_icons);

	thumbnails_enabled = layout_thumb_get(NULL);
	layout_sort_get(NULL, &file_sort_method, &file_sort_ascending);

	layout_geometry_get_tools(NULL, &float_window_x, &float_window_y,
				  &float_window_w, &float_window_h, &float_window_divider);
	layout_tools_float_get(NULL, &tools_float, &tools_hidden);
	toolbar_hidden = layout_toolbar_hidden(NULL);

	color_profile_enabled = layout_image_color_profile_get_use(NULL);
	layout_image_color_profile_get(NULL,
				       &color_profile_input_type, &color_profile_screen_type,
				       &color_profile_use_image);

	save_options();
	keys_save();

	path = g_strconcat(homedir(), "/", GQVIEW_RC_DIR, "/accels", NULL);
	pathl = path_from_utf8(path);
	gtk_accel_map_save(pathl);
	g_free(pathl);
	g_free(path);

	gtk_main_quit();
}

static GenericDialog *exit_dialog = NULL;

static void exit_confirm_cancel_cb(GenericDialog *gd, gpointer data)
{
	exit_dialog = NULL;
	generic_dialog_close(gd);
}

static void exit_confirm_exit_cb(GenericDialog *gd, gpointer data)
{
	exit_dialog = NULL;
	generic_dialog_close(gd);
	exit_gqview_final();
}

static gint exit_confirm_dlg(void)
{
	GtkWidget *parent;
	LayoutWindow *lw;

	if (exit_dialog)
		{
		gtk_window_present(GTK_WINDOW(exit_dialog->dialog));
		return TRUE;
		}

	if (!collection_window_modified_exists()) return FALSE;

	parent = NULL;
	lw = NULL;
	if (layout_valid(&lw))
		{
		parent = lw->window;
		}

	exit_dialog = generic_dialog_new(_("GQview - exit"),
				"GQview", "exit", parent, FALSE,
				exit_confirm_cancel_cb, NULL);
	generic_dialog_add_message(exit_dialog, GTK_STOCK_DIALOG_QUESTION,
				   _("Quit GQview"), _("Collections have been modified. Quit anyway?"));
	generic_dialog_add_button(exit_dialog, GTK_STOCK_QUIT, NULL, exit_confirm_exit_cb, TRUE);

	gtk_widget_show(exit_dialog->dialog);

	return TRUE;
}

void exit_gqview(void)
{
	layout_image_full_screen_stop(NULL);

	if (exit_confirm_dlg()) return;

	exit_gqview_final();
}

int main (int argc, char *argv[])
{
	LayoutWindow *lw;
	gchar *path = NULL;
	gchar *cmd_path = NULL;
	gchar *cmd_file = NULL;
	GList *cmd_list = NULL;
	GList *collection_list = NULL;
	CollectionData *first_collection = NULL;
	gchar *geometry = NULL;
	gchar *buf;
	gchar *bufl;

	/* setup locale, i18n */
	gtk_set_locale();
	bindtextdomain(PACKAGE, GQVIEW_LOCALEDIR);
	bind_textdomain_codeset(PACKAGE, "UTF-8");
	textdomain(PACKAGE);

	/* setup random seed for random slideshow */
        srand(time(NULL));

#if 1
	printf("GQview %s, This is a beta release.\n", VERSION);
#endif

	layout_order = g_strdup("123");
	setup_default_options();
	load_options();

	parse_command_line(argc, argv, &cmd_path, &cmd_file, &cmd_list, &collection_list, &geometry);

	gtk_init (&argc, &argv);

	if (gtk_major_version < GTK_MAJOR_VERSION ||
	    (gtk_major_version == GTK_MAJOR_VERSION && gtk_minor_version < GTK_MINOR_VERSION) )
		{
		gchar *msg;
		print_term("!!! This is a friendly warning.\n");
		print_term("!!! The version of GTK+ in use now is older than when GQview was compiled.\n");
		msg = g_strdup_printf("!!!  compiled with GTK+-%d.%d\n", GTK_MAJOR_VERSION, GTK_MINOR_VERSION);
		print_term(msg);
		g_free(msg);
		msg = g_strdup_printf("!!!   running with GTK+-%d.%d\n", gtk_major_version, gtk_minor_version);
		print_term(msg);
		g_free(msg);
		print_term("!!! GQview may quit unexpectedly with a relocation error.\n");
		}

	check_for_home_path(GQVIEW_RC_DIR);
	check_for_home_path(GQVIEW_RC_DIR_COLLECTIONS);
	check_for_home_path(GQVIEW_CACHE_RC_THUMB);
	check_for_home_path(GQVIEW_CACHE_RC_METADATA);

	keys_load();
	filter_add_defaults();
	filter_rebuild();

	buf = g_strconcat(homedir(), "/", GQVIEW_RC_DIR, "/accels", NULL);
	bufl = path_from_utf8(buf);
	gtk_accel_map_load(bufl);
	g_free(bufl);
	g_free(buf);

	if (startup_blank)
		{
		g_free(cmd_path);
		cmd_path = NULL;
		g_free(cmd_file);
		cmd_file = NULL;
		path_list_free(cmd_list);
		cmd_list = NULL;
		path_list_free(collection_list);
		collection_list = NULL;

		path = NULL;
		}
	else if (cmd_path)
		{
		path = g_strdup(cmd_path);
		}
	else if (startup_path_enable && startup_path && isdir(startup_path))
		{
		path = g_strdup(startup_path);
		}
	else
		{
		path = get_current_dir();
		}

	lw = layout_new_with_geometry(NULL, tools_float, tools_hidden, geometry);
	layout_sort_set(lw, file_sort_method, file_sort_ascending);

	if (collection_list && !startup_command_line_collection)
		{
		GList *work;

		work = collection_list;
		while (work)
			{
			CollectWindow *cw;
			const gchar *path;

			path = work->data;
			work = work->next;

			cw = collection_window_new(path);
			if (!first_collection && cw) first_collection = cw->cd;
			}
		}

	if (cmd_list ||
	    (startup_command_line_collection && collection_list))
		{
		CollectionData *cd;
		GList *work;

		if (startup_command_line_collection)
			{
			CollectWindow *cw;

			cw = collection_window_new("");
			cd = cw->cd;
			}
		else
			{
			cd = collection_new("");	/* if we pass NULL, untitled counter is falsely increm. */
			gqview_command_collection = cd;
			}

		g_free(cd->path);
		cd->path = NULL;
		g_free(cd->name);
		cd->name = g_strdup(_("Command line"));

		collection_path_changed(cd);

		work = cmd_list;
		while (work)
			{
			collection_add(cd, (gchar *)work->data, FALSE);
			work = work->next;
			}

		work = collection_list;
		while (work)
			{
			collection_load(cd, (gchar *)work->data, TRUE);
			work = work->next;
			}

		layout_set_path(lw, path);
		if (cd->list) layout_image_set_collection(lw, cd, cd->list->data);

		/* mem leak, we never unref this collection when !startup_command_line_collection
		 * (the image view of the main window does not hold a ref to the collection)
		 * this is sort of unavoidable, for if it did hold a ref, next/back
		 * may not work as expected when closing collection windows.
		 *
		 * collection_unref(cd);
		 */

		}
	else if (cmd_file)
		{
		layout_set_path(lw, cmd_file);
		}
	else
		{
		layout_set_path(lw, path);
		if (first_collection)
			{
			layout_image_set_collection(lw, first_collection,
						    collection_get_first(first_collection));
			}
		}

	g_free(geometry);
	g_free(cmd_path);
	g_free(cmd_file);
	path_list_free(cmd_list);
	path_list_free(collection_list);
	g_free(path);

	if (startup_full_screen) layout_image_full_screen_start(lw);
	if (startup_in_slideshow) layout_image_slideshow_start(lw);

	buf = g_strconcat(homedir(), "/", GQVIEW_RC_DIR, "/.command", NULL);
	gqview_remote = remote_server_open(buf);
	remote_server_subscribe(gqview_remote, gqview_remote_cb, NULL);
	g_free(buf);

	gtk_main ();
	return 0;
}

