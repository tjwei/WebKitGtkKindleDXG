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
#include "collect-io.h"

#include "collect.h"
#include "layout_util.h"
#include "rcfile.h"
#include "thumb.h"
#include "ui_fileops.h"


#define GQVIEW_COLLECTION_MARKER "#GQview"

#define GQVIEW_COLLECTION_FAIL_MIN     300
#define GQVIEW_COLLECTION_FAIL_PERCENT 98


static void collection_load_thumb_step(CollectionData *cd);


static gint scan_geometry(gchar *buffer, gint *x, gint *y, gint *w, gint *h)
{
	gint nx, ny, nw, nh;

	if(sscanf(buffer, "%d %d %d %d", &nx, &ny, &nw, &nh) != 4) return FALSE;

	*x = nx;
	*y = ny;
	*w = nw;
	*h = nh;

	return TRUE;
}

static gint collection_load_private(CollectionData *cd, const gchar *path, gint append, gint flush)
{
	gchar s_buf[2048];
	FILE *f;
	gchar *pathl;
	gint official = FALSE;
	gint success = TRUE;
	guint total = 0;
	guint fail = 0;

	collection_load_stop(cd);

	if (flush) collect_manager_flush();

	if (!append)
		{
		collection_list_free(cd->list);
		cd->list = NULL;
		}

	if (!path && !cd->path) return FALSE;

	if (!path) path = cd->path;

	/* load it */
	pathl = path_from_utf8(path);
	f = fopen(pathl, "r");
	g_free(pathl);
	if (!f)
		{
		printf("Failed to open collection file: \"%s\"\n", path);
		return FALSE;
		}

	while (fgets(s_buf, sizeof(s_buf), f))
		{
		gchar *buf;
		if (s_buf[0]=='#')
			{
			if (strncasecmp(s_buf, GQVIEW_COLLECTION_MARKER, strlen(GQVIEW_COLLECTION_MARKER)) == 0)
				{
				/* Looks like an official collection, allow unchecked input.
				 * All this does is allow adding files that may not exist,
				 * which is needed for the collection manager to work.
				 * Also unofficial files abort after too many invalid entries.
				 */
				official = TRUE;
				}
			else if (strncmp(s_buf, "#geometry:", 10 ) == 0 &&
			    scan_geometry(s_buf + 10, &cd->window_x, &cd->window_y, &cd->window_w, &cd->window_h) )
				{
				cd->window_read = TRUE;
				}
			continue;
			}
		if (s_buf[0]=='\n') continue;

		buf = quoted_value(s_buf);
		if (buf)
			{
			gint valid;

			valid = (buf[0] == '/' && collection_add_check(cd, buf, FALSE, flush));
			g_free(buf);

			total++;
			if (!valid && !official)
				{
				fail++;
				if (fail > GQVIEW_COLLECTION_FAIL_MIN &&
				    fail * 100 / total > GQVIEW_COLLECTION_FAIL_PERCENT)
					{
					printf("Too many invalid filenames in unoffical collection file, closing: %s\n", path);
					success = FALSE;
					break;
					}
				}
			}
		}

	fclose(f);

	cd->list = collection_list_sort(cd->list, cd->sort_method);
	if (!append) cd->changed = FALSE;

	return success;
}

gint collection_load(CollectionData *cd, const gchar *path, gint append)
{
	if (collection_load_private(cd, path, append, TRUE))
		{
		layout_recent_add_path(cd->path);
		return TRUE;
		}

	return FALSE;
}

static void collection_load_thumb_do(CollectionData *cd)
{
	GdkPixbuf *pixbuf;

	if (!cd->thumb_loader || !g_list_find(cd->list, cd->thumb_info)) return;

	pixbuf = thumb_loader_get_pixbuf(cd->thumb_loader, TRUE);
	collection_info_set_thumb(cd->thumb_info, pixbuf);
	g_object_unref(pixbuf);

	if (cd->info_updated_func) cd->info_updated_func(cd, cd->thumb_info, cd->info_updated_data);
}

static void collection_load_thumb_error_cb(ThumbLoader *tl, gpointer data)
{
	CollectionData *cd = data;

	collection_load_thumb_do(cd);
	collection_load_thumb_step(cd);
}

static void collection_load_thumb_done_cb(ThumbLoader *tl, gpointer data)
{
	CollectionData *cd = data;

	collection_load_thumb_do(cd);
	collection_load_thumb_step(cd);
}

static void collection_load_thumb_step(CollectionData *cd)
{
	GList *work;
	CollectInfo *ci;

	if (!cd->list)
		{
		collection_load_stop(cd);
		return;
		}

	work = cd->list;
	ci = work->data;
	work = work->next;
	/* find first unloaded thumb */
	while (work && ci->pixbuf)
		{
		ci = work->data;
		work = work->next;
		}

	if (!ci || ci->pixbuf)
		{
		/* done */
		collection_load_stop(cd);

		/* send a NULL CollectInfo to notify end */
		if (cd->info_updated_func) cd->info_updated_func(cd, NULL, cd->info_updated_data);

		return;
		}

	/* setup loader and call it */
	cd->thumb_info = ci;
	thumb_loader_free(cd->thumb_loader);
	cd->thumb_loader = thumb_loader_new(thumb_max_width, thumb_max_height);
	thumb_loader_set_callbacks(cd->thumb_loader,
				   collection_load_thumb_done_cb,
				   collection_load_thumb_error_cb,
				   NULL,
				   cd);

	/* start it */
	if (!thumb_loader_start(cd->thumb_loader, ci->path))
		{
		/* error, handle it, do next */
		if (debug) printf("error loading thumb for %s\n", ci->path);
		collection_load_thumb_do(cd);
		collection_load_thumb_step(cd);
		}
}

void collection_load_thumb_idle(CollectionData *cd)
{
	if (!cd->thumb_loader) collection_load_thumb_step(cd);
}

gint collection_load_begin(CollectionData *cd, const gchar *path, gint append)
{
	if (!collection_load(cd, path, append)) return FALSE;

	collection_load_thumb_idle(cd);

	return TRUE;
}

void collection_load_stop(CollectionData *cd)
{
	if (!cd->thumb_loader) return;

	thumb_loader_free(cd->thumb_loader);
	cd->thumb_loader = NULL;
}

static gint collection_save_private(CollectionData *cd, const gchar *path)
{
	FILE *f;
	GList *work;
	gchar *tmp_path;
	gchar *pathl;
	mode_t save_mask;

	if (!path && !cd->path) return FALSE;

	if (!path)
		{
		path = cd->path;
		}

	tmp_path = unique_filename(path, ".tmp", "_", 3);
	if (!tmp_path) return FALSE;

	pathl = path_from_utf8(tmp_path);
	save_mask = umask(0077);
	f = fopen(pathl, "w");
	umask(save_mask);
	g_free(pathl);

	if (!f)
		{
		/* file open failed */
		printf("failed to open collection (write) \"%s\"\n", tmp_path);
		g_free(tmp_path);
		return FALSE;
		}

	fprintf(f, "%s collection\n", GQVIEW_COLLECTION_MARKER);
	fprintf(f, "#created with GQview version %s\n", VERSION);

	collection_update_geometry(cd);
	if (cd->window_read)
		{
		fprintf(f, "#geometry: %d %d %d %d\n", cd->window_x, cd->window_y, cd->window_w, cd->window_h);
		}

	work = cd->list;
	while (work)
		{
		CollectInfo *ci = work->data;
		if (fprintf(f, "\"%s\"\n", ci->path) < 0)
			{
			fclose(f);
			printf("Error writing to %s\n", tmp_path);
			unlink_file(tmp_path);
			g_free(tmp_path);
			return FALSE;
			}
		work = work->next;
		}

	fprintf(f, "#end\n");

	fclose(f);

	copy_file_attributes(path, tmp_path, TRUE, FALSE);
	if (!rename_file(tmp_path, path))
		{
		printf("collection save unable to rename %s to %s\n", tmp_path, path);
		unlink_file(tmp_path);
		g_free(tmp_path);
		return FALSE;
		}

	g_free(tmp_path);

	if (!cd->path || strcmp(path, cd->path) != 0)
		{
		gchar *buf = cd->path;
		cd->path = g_strdup(path);
		path = cd->path;
		g_free(buf);

		g_free(cd->name);
		cd->name = g_strdup(filename_from_path(cd->path));

		collection_path_changed(cd);
		}

	cd->changed = FALSE;

	return TRUE;
}

gint collection_save(CollectionData *cd, const gchar *path)
{
	if (collection_save_private(cd, path))
		{
		layout_recent_add_path(cd->path);
		return TRUE;
		}

	return FALSE;
}

gint collection_load_only_geometry(CollectionData *cd, const gchar *path)
{
	gchar s_buf[2048];
	FILE *f;
	gchar *pathl;

	if (!path && !cd->path) return FALSE;

	if (!path) path = cd->path;

	/* load it */
	pathl = path_from_utf8(path);
	f = fopen(pathl, "r");
	g_free(pathl);
	if (!f) return FALSE;

	while (fgets(s_buf, sizeof(s_buf), f))
		{
		if (s_buf[0]=='#' &&
		    strncmp(s_buf, "#geometry:", 10 ) == 0 &&
		    scan_geometry(s_buf + 10, &cd->window_x, &cd->window_y, &cd->window_w, &cd->window_h) )
			{
			cd->window_read = TRUE;
			fclose(f);
			return TRUE;
			}
		}
	fclose(f);
	return FALSE;
}


/*
 *-------------------------------------------------------------------
 * collection manager
 *-------------------------------------------------------------------
 */

#define COLLECT_MANAGER_ACTIONS_PER_IDLE 1000
#define COLLECT_MANAGER_FLUSH_DELAY      10000

typedef struct _CollectManagerEntry CollectManagerEntry;
struct _CollectManagerEntry
{
	gchar *path;
	GList *action_list;
};

typedef enum {
	COLLECTION_MANAGER_UPDATE,
	COLLECTION_MANAGER_ADD,
	COLLECTION_MANAGER_REMOVE
} CollectManagerType;

typedef struct _CollectManagerAction CollectManagerAction;
struct _CollectManagerAction
{
	gchar *oldpath;
	gchar *newpath;

	CollectManagerType type;

	gint ref;
};


static GList *collection_manager_entry_list = NULL;
static GList *collection_manager_action_list = NULL;
static GList *collection_manager_action_tail = NULL;
static gint collection_manager_timer_id = -1;


static CollectManagerAction *collect_manager_action_new(const gchar *oldpath, const gchar *newpath,
							CollectManagerType type)
{
	CollectManagerAction *action;

	action = g_new0(CollectManagerAction, 1);
	action->ref = 1;

	action->oldpath = g_strdup(oldpath);
	action->newpath = g_strdup(newpath);

	action->type = type;

	return action;
}

static void collect_manager_action_ref(CollectManagerAction *action)
{
	action->ref++;
}

static void collect_manager_action_unref(CollectManagerAction *action)
{
	action->ref--;

	if (action->ref > 0) return;

	g_free(action->oldpath);
	g_free(action->newpath);
	g_free(action);
}

static CollectManagerEntry *collect_manager_entry_new(const gchar *path)
{
	CollectManagerEntry *entry;

	entry = g_new0(CollectManagerEntry, 1);
	entry->path = g_strdup(path);
	entry->action_list = NULL;

	collection_manager_entry_list = g_list_append(collection_manager_entry_list, entry);

	return entry;
}

static void collect_manager_entry_free(CollectManagerEntry *entry)
{
	GList *work;

	collection_manager_entry_list = g_list_remove(collection_manager_entry_list, entry);

	work = entry->action_list;
	while (work)
		{
		CollectManagerAction *action;

		action = work->data;
		work = work->next;

		collect_manager_action_unref(action);
		}
	g_list_free(entry->action_list);

	g_free(entry->path);
	g_free(entry);
}

static void collect_manager_refresh(void)
{
	GList *list = NULL;
	GList *work;
	gchar *base;

	base = g_strconcat(homedir(), "/", GQVIEW_RC_DIR_COLLECTIONS, NULL);
	path_list(base, &list, NULL);
	g_free(base);

	work = collection_manager_entry_list;
	while (work && list)
		{
		CollectManagerEntry *entry;
		GList *list_step;

		entry = work->data;
		work = work->next;

		list_step = list;
		while (list_step && entry)
			{
			gchar *path;

			path = list_step->data;
			list_step = list_step->next;

			if (strcmp(path, entry->path) == 0)
				{
				list = g_list_remove(list, path);
				g_free(path);

				entry = NULL;
				}
			else
				{
				collect_manager_entry_free(entry);
				}
			}
		}

	work = list;
	while (work)
		{
		gchar *path;

		path = work->data;
		work = work->next;

		collect_manager_entry_new(path);
		g_free(path);
		}

	g_list_free(list);
}

static void collect_manager_process_actions(gint max)
{
	if (debug && collection_manager_action_list)
		{
		printf("collection manager processing actions\n");
		}

	while (collection_manager_action_list != NULL && max > 0)
		{
		CollectManagerAction *action;
		GList *work;

		action = collection_manager_action_list->data;
		work = collection_manager_entry_list;
		while (work)
			{
			CollectManagerEntry *entry;

			entry = work->data;
			work = work->next;

			if (action->type == COLLECTION_MANAGER_UPDATE)
				{
				entry->action_list = g_list_prepend(entry->action_list, action);
				collect_manager_action_ref(action);
				}
			else if (action->oldpath && action->newpath &&
				 strcmp(action->newpath, entry->path) == 0)
				{
				/* convert action to standard add format */
				g_free(action->newpath);
				if (action->type == COLLECTION_MANAGER_ADD)
					{
					action->newpath = action->oldpath;
					action->oldpath = NULL;
					}
				else if (action->type == COLLECTION_MANAGER_REMOVE)
					{
					action->newpath = NULL;
					}

				entry->action_list = g_list_prepend(entry->action_list, action);
				collect_manager_action_ref(action);
				}

			max--;
			}

		if (action->type != COLLECTION_MANAGER_UPDATE &&
		    action->oldpath && action->newpath)
			{
			printf("collection manager failed to %s %s for collection %s\n",
				(action->type == COLLECTION_MANAGER_ADD) ? "add" : "remove",
				action->oldpath, action->newpath);
			}

		if (collection_manager_action_tail == collection_manager_action_list)
			{
			collection_manager_action_tail = NULL;
			}
		collection_manager_action_list = g_list_remove(collection_manager_action_list, action);
		collect_manager_action_unref(action);
		}
}

static gint collect_manager_process_entry(CollectManagerEntry *entry)
{
	CollectionData *cd;
	gint success;
	GList *work;

	if (!entry->action_list) return FALSE;

	cd = collection_new(entry->path);
	success = collection_load_private(cd, entry->path, FALSE, FALSE);

	work = g_list_last(entry->action_list);
	while (work)
		{
		CollectManagerAction *action;

		action = work->data;
		work = work->prev;

		if (!action->oldpath)
			{
			/* add image */
			if (collection_list_find(cd->list, action->newpath) == NULL)
				{
				collection_add_check(cd, action->newpath, FALSE, FALSE);
				}
			}
		else if (action->newpath)
			{
			/* rename image */
			while (collection_rename(cd, action->oldpath, action->newpath));
			}
		else
			{
			/* remove image */
			while (collection_remove(cd, action->oldpath));
			}
		collect_manager_action_unref(action);
		}

	if (success && cd->changed)
		{
		collection_save_private(cd, entry->path);
		if (debug) printf("collection manager updated: %s\n", entry->path);
		}
	collection_unref(cd);

	g_list_free(entry->action_list);
	entry->action_list = NULL;

	return TRUE;
}

static gint collect_manager_process_entry_list(void)
{
	GList *work;

	work = collection_manager_entry_list;
	while (work)
		{
		CollectManagerEntry *entry;

		entry = work->data;
		work = work->next;
		if (collect_manager_process_entry(entry)) return TRUE;
		}

	return FALSE;
}

static gint collect_manager_process_cb(gpointer data)
{
	if (collection_manager_action_list) collect_manager_refresh();
	collect_manager_process_actions(COLLECT_MANAGER_ACTIONS_PER_IDLE);
	if (collection_manager_action_list) return TRUE;

	if (collect_manager_process_entry_list()) return TRUE;

	if (debug) printf("collection manager is up to date\n");
	return FALSE;
}

static gint collect_manager_timer_cb(gpointer data)
{
	if (debug) printf("collection manager timer expired\n");

	g_idle_add_full(G_PRIORITY_LOW, collect_manager_process_cb, NULL, NULL);

	collection_manager_timer_id = -1;
	return FALSE;
}

static void collect_manager_timer_push(gint stop)
{
	if (collection_manager_timer_id != -1)
		{
		if (!stop) return;

		g_source_remove(collection_manager_timer_id);
		collection_manager_timer_id = -1;
		}

	if (!stop)
		{
		collection_manager_timer_id = g_timeout_add(COLLECT_MANAGER_FLUSH_DELAY,
							    collect_manager_timer_cb, NULL);
		if (debug) printf("collection manager timer started\n");
		}
}

static void collect_manager_add_action(CollectManagerAction *action)
{
	if (!action) return;

	/* we keep track of the list's tail to keep this a n(1) operation */

	if (collection_manager_action_tail)
		{
		collection_manager_action_tail = g_list_append(collection_manager_action_tail, action);
		collection_manager_action_tail = collection_manager_action_tail->next;
		}
	else
		{
		collection_manager_action_list = g_list_append(collection_manager_action_list, action);
		collection_manager_action_tail = collection_manager_action_list;
		}

	collect_manager_timer_push(FALSE);
}

void collect_manager_moved(const gchar *oldpath, const gchar *newpath)
{
	CollectManagerAction *action;

	action = collect_manager_action_new(oldpath, newpath, COLLECTION_MANAGER_UPDATE);
	collect_manager_add_action(action);
}

void collect_manager_add(const gchar *path, const gchar *collection)
{
	CollectManagerAction *action;
	CollectWindow *cw;

	if (!path || !collection) return;

	cw = collection_window_find_by_path(collection);
	if (cw)
		{
		if (collection_list_find(cw->cd->list, path) == NULL)
			{
			collection_add(cw->cd, path, FALSE);
			}
		return;
		}

	action = collect_manager_action_new(path, collection, COLLECTION_MANAGER_ADD);
	collect_manager_add_action(action);
}

void collect_manager_remove(const gchar *path, const gchar *collection)
{
	CollectManagerAction *action;
	CollectWindow *cw;

	if (!path || !collection) return;

	cw = collection_window_find_by_path(collection);
	if (cw)
		{
		while (collection_remove(cw->cd, path));
		return;
		}

	action = collect_manager_action_new(path, collection, COLLECTION_MANAGER_REMOVE);
	collect_manager_add_action(action);
}

void collect_manager_flush(void)
{
	collect_manager_timer_push(TRUE);

	if (debug) printf("collection manager flushing\n");
	while (collect_manager_process_cb(NULL));
}

