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


#ifndef CACHE_H
#define CACHE_H


#include "similar.h"


#define GQVIEW_CACHE_RC_THUMB       GQVIEW_RC_DIR"/thumbnails"
#define GQVIEW_CACHE_RC_METADATA    GQVIEW_RC_DIR"/metadata"

#define GQVIEW_CACHE_LOCAL_THUMB    ".thumbnails"
#define GQVIEW_CACHE_LOCAL_METADATA ".metadata"

#define GQVIEW_CACHE_EXT_THUMB      ".png"
#define GQVIEW_CACHE_EXT_SIM        ".sim"
#define GQVIEW_CACHE_EXT_METADATA   ".meta"


typedef enum {
	CACHE_TYPE_THUMB,
	CACHE_TYPE_SIM,
	CACHE_TYPE_METADATA
} CacheType;

typedef struct _CacheData CacheData;
struct _CacheData
{
	gchar *path;
	gint width;
	gint height;
	time_t date;
	long checksum;
	guchar md5sum[16];
	ImageSimilarityData *sim;

	gint dimensions;
	gint have_date;
	gint have_checksum;
	gint have_md5sum;
	gint similarity;
};

gint cache_time_valid(const gchar *cache, const gchar *path);


CacheData *cache_sim_data_new(void);
void cache_sim_data_free(CacheData *cd);

gint cache_sim_data_save(CacheData *cd);
CacheData *cache_sim_data_load(const gchar *path);

void cache_sim_data_set_dimensions(CacheData *cd, gint w, gint h);
void cache_sim_data_set_date(CacheData *cd, time_t date);
void cache_sim_data_set_checksum(CacheData *cd, long checksum);
void cache_sim_data_set_md5sum(CacheData *cd, guchar digest[16]);
void cache_sim_data_set_similarity(CacheData *cd, ImageSimilarityData *sd);
gint cache_sim_data_filled(ImageSimilarityData *sd);


gint cache_ensure_dir_exists(gchar *path, mode_t mode);
gchar *cache_get_location(CacheType type, const gchar *source, gint include_name, mode_t *mode);
gchar *cache_find_location(CacheType type, const gchar *source);


#endif


