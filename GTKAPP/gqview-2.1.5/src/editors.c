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
#include "editors.h"

#include "utilops.h"
#include "ui_fileops.h"
#include "ui_spinner.h"
#include "ui_utildlg.h"

#include <errno.h>


#define EDITOR_WINDOW_WIDTH 500
#define EDITOR_WINDOW_HEIGHT 300

#define COMMAND_SHELL "sh"
#define COMMAND_OPT  "-c"


typedef struct _EditorVerboseData EditorVerboseData;
struct _EditorVerboseData {
	int fd;

	GenericDialog *gd;
	GtkWidget *button_close;
	GtkWidget *button_stop;
	GtkWidget *text;
	GtkWidget *progress;
	GtkWidget *spinner;
	gint count;
	gint total;

	gchar *command_template;
	GList *list;
};


static gchar *editor_slot_defaults[] = {
	N_("The Gimp"), "gimp-remote -n %f",
	N_("XV"), "xv %f",
	N_("Xpaint"), "xpaint %f",
	NULL, NULL,
	NULL, NULL,
	NULL, NULL,
	NULL, NULL,
	NULL, NULL,
	N_("Rotate jpeg clockwise"), "%vif jpegtran -rotate 90 -copy all -outfile %p_tmp %p; then mv %p_tmp %p;else rm %p_tmp;fi",
	N_("Rotate jpeg counterclockwise"), "%vif jpegtran -rotate 270 -copy all -outfile %p_tmp %p; then mv %p_tmp %p;else rm %p_tmp;fi",
	NULL, NULL
};


static void editor_verbose_window_progress(EditorVerboseData *vd, const gchar *text);
static gint editor_command_next(EditorVerboseData *vd);


/*
 *-----------------------------------------------------------------------------
 * external editor routines
 *-----------------------------------------------------------------------------
 */

void editor_reset_defaults(void)
{
	gint i;

	for (i = 0; i < GQVIEW_EDITOR_SLOTS; i++)
		{
		g_free(editor_name[i]);
		editor_name[i] = g_strdup(_(editor_slot_defaults[i * 2]));
		g_free(editor_command[i]);
		editor_command[i] = g_strdup(editor_slot_defaults[i * 2 + 1]);
		}
}

static void editor_verbose_window_close(GenericDialog *gd, gpointer data)
{
	EditorVerboseData *vd = data;

	generic_dialog_close(gd);
	g_free(vd->command_template);
	g_free(vd);
}

static void editor_verbose_window_stop(GenericDialog *gd, gpointer data)
{
	EditorVerboseData *vd = data;

	path_list_free(vd->list);
	vd->list = NULL;

	vd->count = 0;
	editor_verbose_window_progress(vd, _("stopping..."));
}

static void editor_verbose_window_enable_close(EditorVerboseData *vd)
{
	vd->gd->cancel_cb = editor_verbose_window_close;

	spinner_set_interval(vd->spinner, -1);
	gtk_widget_set_sensitive(vd->button_stop, FALSE);
	gtk_widget_set_sensitive(vd->button_close, TRUE);
}

static EditorVerboseData *editor_verbose_window(const gchar *template, const gchar *text)
{
	EditorVerboseData *vd;
	GtkWidget *scrolled;
	GtkWidget *hbox;
	gchar *buf;

	vd = g_new0(EditorVerboseData, 1);

	vd->list = NULL;
	vd->command_template = g_strdup(template);
	vd->total = 0;
	vd->count = 0;
	vd->fd = -1;

	vd->gd = file_util_gen_dlg(_("Edit command results"), "GQview", "editor_results",
				   NULL, FALSE,
				   NULL, vd);
	buf = g_strdup_printf(_("Output of %s"), text);
	generic_dialog_add_message(vd->gd, NULL, buf, NULL);
	g_free(buf);
	vd->button_stop = generic_dialog_add_button(vd->gd, GTK_STOCK_STOP, NULL,
						   editor_verbose_window_stop, FALSE);
	gtk_widget_set_sensitive(vd->button_stop, FALSE);
	vd->button_close = generic_dialog_add_button(vd->gd, GTK_STOCK_CLOSE, NULL,
						    editor_verbose_window_close, TRUE);
	gtk_widget_set_sensitive(vd->button_close, FALSE);

	scrolled = gtk_scrolled_window_new(NULL, NULL);
	gtk_scrolled_window_set_shadow_type(GTK_SCROLLED_WINDOW(scrolled), GTK_SHADOW_IN);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled),
				       GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
	gtk_box_pack_start(GTK_BOX(vd->gd->vbox), scrolled, TRUE, TRUE, 5);
	gtk_widget_show(scrolled);

	vd->text = gtk_text_view_new();
	gtk_text_view_set_editable(GTK_TEXT_VIEW(vd->text), FALSE);
	gtk_widget_set_size_request(vd->text, EDITOR_WINDOW_WIDTH, EDITOR_WINDOW_HEIGHT);
	gtk_container_add(GTK_CONTAINER(scrolled), vd->text);
	gtk_widget_show(vd->text);

	hbox = gtk_hbox_new(FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vd->gd->vbox), hbox, FALSE, FALSE, 0);
	gtk_widget_show(hbox);

	vd->progress = gtk_progress_bar_new();
	gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(vd->progress), 0.0);
	gtk_box_pack_start(GTK_BOX(hbox), vd->progress, TRUE, TRUE, 0);
	gtk_widget_show(vd->progress);

	vd->spinner = spinner_new(NULL, SPINNER_SPEED);
	gtk_box_pack_start(GTK_BOX(hbox), vd->spinner, FALSE, FALSE, 0);
	gtk_widget_show(vd->spinner);
	
	gtk_widget_show(vd->gd->dialog);

	return vd;
}

static void editor_verbose_window_fill(EditorVerboseData *vd, gchar *text, gint len)
{
	GtkTextBuffer *buffer;
	GtkTextIter iter;

	buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(vd->text));
	gtk_text_buffer_get_iter_at_offset(buffer, &iter, -1);
	gtk_text_buffer_insert(buffer, &iter, text, len);
}

static void editor_verbose_window_progress(EditorVerboseData *vd, const gchar *text)
{
	if (vd->total)
		{
		gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(vd->progress), (double)vd->count / vd->total);
		}

	gtk_progress_bar_set_text(GTK_PROGRESS_BAR(vd->progress), (text) ? text : "");
}

static gboolean editor_verbose_io_cb(GIOChannel *source, GIOCondition condition, gpointer data)
{
	EditorVerboseData *vd = data;
	gchar buf[512];
	gsize count;

	switch (condition)
		{
		case G_IO_IN:
			while (g_io_channel_read_chars(source, buf, sizeof(buf), &count, NULL) == G_IO_STATUS_NORMAL)
				{
				if (!g_utf8_validate(buf, count, NULL))
					{
					gchar *utf8;
					utf8 = g_locale_to_utf8(buf, count, NULL, NULL, NULL);
					if (utf8)
						{
						editor_verbose_window_fill(vd, utf8, -1);
						g_free(utf8);
						}
					else
						{
						editor_verbose_window_fill(vd, "GQview: Error converting text to valid utf8\n", -1);
						}
					}
				else
					{
					editor_verbose_window_fill(vd, buf, count);
					}
				}
			break;
		case G_IO_ERR:
			printf("Error reading from command\n");
		case G_IO_HUP:
			if (debug) printf("Editor command HUP\n");
		default:
			while (g_source_remove_by_user_data(vd));
			close(vd->fd);
			vd->fd = -1;
			editor_command_next(vd);
			return FALSE;
			break;
		}

	return TRUE;
}

static int command_pipe(char *command)
{
	char *args[4];
	int fpipe[2];
	pid_t fpid;

	args[0] = COMMAND_SHELL;
	args[1] = COMMAND_OPT;
	args[2] = command;
	args[3] = NULL;

	if (pipe(fpipe) < 0)
		{
		printf("pipe setup failed: %s\n", strerror(errno));
		return -1;
		}

	fpid = fork();
	if (fpid < 0)
		{
		/* fork failed */
		printf("fork failed: %s\n", strerror(errno));
		}
	else if (fpid == 0)
		{
		/* child */
		gchar *msg;

		dup2(fpipe[1], 1);
		dup2(fpipe[1], 2);
		close(fpipe[0]);

		execvp(args[0], args);

		msg = g_strdup_printf("Unable to exec command:\n%s\n\n%s\n", command, strerror(errno));
		write(1, msg, strlen(msg));

		_exit(1);
		}
	else
		{
		/* parent */
		fcntl(fpipe[0], F_SETFL, O_NONBLOCK);
		close(fpipe[1]);

		return fpipe[0];
		}

	return -1;
}

static gint editor_verbose_start(EditorVerboseData *vd, gchar *command)
	{
	GIOChannel *channel;
	int fd;

	fd = command_pipe(command);
	if (fd < 0)
		{
		gchar *buf;

		buf = g_strdup_printf(_("Failed to run command:\n%s\n"), command);
		editor_verbose_window_fill(vd, buf, strlen(buf));
		g_free(buf);

		return FALSE;
		}

	vd->fd = fd;
	channel = g_io_channel_unix_new(fd);

	g_io_add_watch_full(channel, G_PRIORITY_DEFAULT, G_IO_IN,
			    editor_verbose_io_cb, vd, NULL);
	g_io_add_watch_full(channel, G_PRIORITY_DEFAULT, G_IO_ERR,
			    editor_verbose_io_cb, vd, NULL);
	g_io_add_watch_full(channel, G_PRIORITY_DEFAULT, G_IO_HUP,
			    editor_verbose_io_cb, vd, NULL);
	g_io_channel_unref(channel);

	return TRUE;
}

static gchar *editor_command_path_parse(const gchar *path)
{
	GString *string;
	gchar *pathl;
	const gchar *p;

	string = g_string_new("");
	p = path;
	while (*p != '\0')
		{
		/* must escape \, ", `, and $ to avoid problems,
		 * we assume system shell supports bash-like escaping
		 */
		if (strchr("\\\"`$", *p) != NULL)
			{
			string = g_string_append_c(string, '\\');
			}
		string = g_string_append_c(string, *p);
		p++;
		}

	pathl = path_from_utf8(string->str);
	g_string_free(string, TRUE);

	return pathl;
}

static gint editor_command_one(const gchar *template, const gchar *path, EditorVerboseData *vd)
{
	GString *result = NULL;
	gchar *pathl;
	gchar *found;
	const gchar *ptr;
	gchar path_buffer[512];
	gchar *current_path;
	gint path_change = FALSE;
	gint ret;

	current_path = getcwd(path_buffer, sizeof(path_buffer));

	result = g_string_new("");
	pathl = editor_command_path_parse(path);

	ptr = template;
	while ( (found = strstr(ptr, "%p")) )
		{
		result = g_string_append_len(result, ptr, found - ptr);
		ptr = found + 2;
		result = g_string_append_c(result, '"');
		result = g_string_append(result, pathl);
		result = g_string_append_c(result, '"');
		}
	result = g_string_append(result, ptr);

	if (debug) printf("system command: %s\n", result->str);

	if (current_path)
		{
		gchar *base;
		base = remove_level_from_path(path);
		if (chdir(base) == 0) path_change = TRUE;
		g_free(base);
		}

	if (vd)
		{
		result = g_string_append(result, " 2>&1");
		ret = editor_verbose_start(vd, result->str);
		}
	else
		{
		ret = system(result->str);
		}

	if (path_change) chdir(current_path);

	g_string_free(result, TRUE);
	g_free(pathl);

	return ret;
}

static gint editor_command_next(EditorVerboseData *vd)
{
	const gchar *text;

	editor_verbose_window_fill(vd, "\n", 1);

	while (vd->list)
		{
		gchar *path;
		gint success;

		path = vd->list->data;
		vd->list = g_list_remove(vd->list, path);

		editor_verbose_window_progress(vd, path);

		vd->count++;
		success = editor_command_one(vd->command_template, path, vd);
		if (success)
			{
			gtk_widget_set_sensitive(vd->button_stop, (vd->list != NULL) );
			editor_verbose_window_fill(vd, path, strlen(path));
			editor_verbose_window_fill(vd, "\n", 1);
			}

		g_free(path);
		if (success) return TRUE;
		}

	if (vd->count == vd->total)
		{
		text = _("done");
		}
	else
		{
		text = _("stopped by user");
		}
	vd->count = 0;
	editor_verbose_window_progress(vd, text);
	editor_verbose_window_enable_close(vd);
	return FALSE;
}

static void editor_command_start(const gchar *template, const gchar *text, GList *list)
{
	EditorVerboseData *vd;

	vd = editor_verbose_window(template, text);
	vd->list = path_list_copy(list);
	vd->total = g_list_length(list);

	editor_command_next(vd);
}

static gint editor_line_break(const gchar *template, gchar **front, const gchar **end)
{
	gchar *found;

	*front = g_strdup(template);
	found = strstr(*front, "%f");

	if (found)
		{
		*found = '\0';
		*end = found + 2;
		return TRUE;
		}

	*end = "";
	return FALSE;
}

/*
 * The supported macros for editor commands:
 *
 *   %f   first occurence replaced by quoted sequence of filenames, command is run once.
 *        only one occurence of this macro is supported.
 *        ([ls %f] results in [ls "file1" "file2" ... "lastfile"])
 *   %p   command is run for each filename in turn, each instance replaced with single filename.
 *        multiple occurences of this macro is supported for complex shell commands.
 *        This macro will BLOCK THE APPLICATION until it completes, since command is run once
 *        for every file in syncronous order. To avoid blocking add the %v macro, below.
 *        ([ls %p] results in [ls "file1"], [ls "file2"] ... [ls "lastfile"])
 *   none if no macro is supplied, the result is equivalent to "command %f"
 *        ([ls] results in [ls "file1" "file2" ... "lastfile"])
 *
 *  Only one of the macros %f or %p may be used in a given commmand.
 *
 *   %v   must be the first two characters[1] in a command, causes a window to display
 *        showing the output of the command(s).
 *   %V   same as %v except in the case of %p only displays a window for multiple files,
 *        operating on a single file is suppresses the output dialog.
 *
 *   %w   must be first two characters in a command, presence will disable full screen
 *        from exiting upon invocation.
 *
 *
 * [1] Note: %v,%V may also be preceded by "%w".
 */
static void editor_command_run(const gchar *template, const gchar *text, GList *list)
{
	gint verbose = FALSE;
	gint for_each = FALSE;

	if (!template || template[0] == '\0') return;

	for_each = (strstr(template, "%p") != NULL);

	/* no window state change flag, skip */
	if (strncmp(template, "%w", 2) == 0) template += 2;

	if (strncmp(template, "%v", 2) == 0)
		{
		template += 2;
		verbose = TRUE;
		}
	else if (strncmp(template, "%V", 2) == 0)
		{
		template += 2;
		if (!for_each || list->next) verbose = TRUE;
		}

	if (for_each)
		{
		if (verbose)
			{
			editor_command_start(template, text, list);
			}
		else
			{
			GList *work;

			work = list;
			while (work)
				{
				gchar *path = work->data;
				editor_command_one(template, path, NULL);
				work = work->next;
				}
			}
		}
	else
		{
		gchar *front;
		const gchar *end;
		GList *work;
		GString *result = NULL;
		gint parser_match;

		parser_match = editor_line_break(template, &front, &end);
		result = g_string_new((parser_match) ? "" : " ");

		work = list;
		while (work)
			{
			gchar *path = work->data;
			gchar *pathl;

			if (work != list) g_string_append_c(result, ' ');
			result = g_string_append_c(result, '"');
			pathl = editor_command_path_parse(path);
			result = g_string_append(result, pathl);
			g_free(pathl);
			result = g_string_append_c(result, '"');
			work = work->next;
			}

		result = g_string_prepend(result, front);
		result = g_string_append(result, end);
		if (verbose) result = g_string_append(result, " 2>&1 ");
		result = g_string_append(result, "&");

		if (debug) printf("system command: %s\n", result->str);

		if (verbose)
			{
			EditorVerboseData *vd;

			vd = editor_verbose_window(template, text);
			editor_verbose_window_progress(vd, _("running..."));
			editor_verbose_start(vd, result->str);
			}
		else
			{
			system(result->str);
			}

		g_free(front);
		g_string_free(result, TRUE);
		}
}

void start_editor_from_path_list(gint n, GList *list)
{
	gchar *command;

	if (n < 0 || n >= GQVIEW_EDITOR_SLOTS || !list ||
	    !editor_command[n] ||
	    strlen(editor_command[n]) == 0) return;

	command = g_locale_from_utf8(editor_command[n], -1, NULL, NULL, NULL);
	editor_command_run(command, editor_name[n], list);
	g_free(command);
}

void start_editor_from_file(gint n, const gchar *path)
{
	GList *list;

	if (!path) return;

	list = g_list_append(NULL, (gchar *)path);
	start_editor_from_path_list(n, list);
	g_list_free(list);
}

gint editor_window_flag_set(gint n)
{
	if (n < 0 || n >= GQVIEW_EDITOR_SLOTS ||
	    !editor_command[n] ||
	    strlen(editor_command[n]) == 0) return TRUE;

	return (strncmp(editor_command[n], "%w", 2) == 0);
}


