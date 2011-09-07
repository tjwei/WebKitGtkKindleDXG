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


#ifndef COLLECT_IO_H
#define COLLECT_IO_H


gint collection_load(CollectionData *cd, const gchar *path, gint append);

gint collection_load_begin(CollectionData *cd, const gchar *path, gint append);
void collection_load_stop(CollectionData *cd);

void collection_load_thumb_idle(CollectionData *cd);

gint collection_save(CollectionData *cd, const gchar *path);

gint collection_load_only_geometry(CollectionData *cd, const gchar *path);


/* these are used to update collections contained in user's collection
 * folder when moving or renaming files.
 * also handles:
 *   deletes file when newpath == NULL
 *   adds file when oldpath == NULL
 */
void collect_manager_moved(const gchar *oldpath, const gchar *newpath);

/* add or removing from a specific collection */
void collect_manager_add(const gchar *path, const gchar *collection);
void collect_manager_remove(const gchar *path, const gchar *collection);

/* commit pending operations to disk */
void collect_manager_flush(void);



#endif

