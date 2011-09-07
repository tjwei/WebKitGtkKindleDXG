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
#include "cache.h"

#include "md5-util.h"
#include "ui_fileops.h"

#include <utime.h>
#include <errno.h>


/*
 *-------------------------------------------------------------------
 * Cache data file format:
 *-------------------------------------------------------------------
 * 
 * SIMcache
 * #coment
 * Dimensions=[<width> x <height>]
 * Date=[<value in time_t format, or -1 if no embedded date>]
 * Checksum=[<value>]
 * MD5sum=[<32 character ascii text digest>]
 * SimilarityGrid[32 x 32]=<3072 bytes of data (1024 pixels in RGB format, 1 pixel is 24bits)>
 * 
 * 
 * The first line (9 bytes) indicates it is a SIMcache format file. (new line char must exist)
 * Comment lines starting with a # are ignored up to a new line.
 * All data lines should end with a new line char.
 * Format is very strict, data must begin with the char immediately following '='.
 * Currently SimilarityGrid is always assumed to be 32 x 32 RGB.
 */


/*
 *-------------------------------------------------------------------
 * sim cache data
 *-------------------------------------------------------------------
 */

CacheData *cache_sim_data_new(void)
{
	CacheData *cd;

	cd = g_new0(CacheData, 1);
	cd->date = -1;

	return cd;
}

void cache_sim_data_free(CacheData *cd)
{
	if (!cd) return;

	g_free(cd->path);
	image_sim_free(cd->sim);
	g_free(cd);
}

/*
 *-------------------------------------------------------------------
 * sim cache write
 *-------------------------------------------------------------------
 */

static gint cache_sim_write_dimensions(FILE *f, CacheData *cd)
{
	if (!f || !cd || !cd->dimensions) return FALSE;

	fprintf(f, "Dimensions=[%d x %d]\n", cd->width, cd->height);

	return TRUE;
}

static gint cache_sim_write_date(FILE *f, CacheData *cd)
{
	if (!f || !cd || !cd->have_date) return FALSE;

	fprintf(f, "Date=[%ld]\n", cd->date);

	return TRUE;
}

static gint cache_sim_write_checksum(FILE *f, CacheData *cd)
{
	if (!f || !cd || !cd->have_checksum) return FALSE;

	fprintf(f, "Checksum=[%ld]\n", cd->checksum);

	return TRUE;
}

static gint cache_sim_write_md5sum(FILE *f, CacheData *cd)
{
	gchar *text;

	if (!f || !cd || !cd->have_md5sum) return FALSE;

	text = md5_digest_to_text(cd->md5sum);
	fprintf(f, "MD5sum=[%s]\n", text);
	g_free(text);

	return TRUE;
}

static gint cache_sim_write_similarity(FILE *f, CacheData *cd)
{
	gint success = FALSE;

	if (!f || !cd || !cd->similarity) return FALSE;

	if (cd->sim && cd->sim->filled)
		{
		gint x, y;
		guint8 buf[96];

		fprintf(f, "SimilarityGrid[32 x 32]=");
		for (y = 0; y < 32; y++)
			{
			gint s;
			guint8 *p;

			s = y * 32;
			p = buf;
			for(x = 0; x < 32; x++)
				{
				*p = cd->sim->avg_r[s + x]; p++;
				*p = cd->sim->avg_g[s + x]; p++;
				*p = cd->sim->avg_b[s + x]; p++;
				}
			fwrite(buf, sizeof(buf), 1, f);
			}

		fprintf(f, "\n");
		success = TRUE;
		}

	return success;
}

gint cache_sim_data_save(CacheData *cd)
{
	FILE *f;
	gchar *pathl;

	if (!cd || !cd->path) return FALSE;

	pathl = path_from_utf8(cd->path);
	f = fopen(pathl, "w");
	g_free(pathl);

	if (!f)
		{
		printf("Unable to save sim cache data: %s\n", cd->path);
		return FALSE;
		}

	fprintf(f, "SIMcache\n#%s %s\n", PACKAGE, VERSION);
	cache_sim_write_dimensions(f, cd);
	cache_sim_write_date(f, cd);
	cache_sim_write_checksum(f, cd);
	cache_sim_write_md5sum(f, cd);
	cache_sim_write_similarity(f, cd);

	fclose (f);

	return TRUE;
}

/*
 *-------------------------------------------------------------------
 * sim cache read
 *-------------------------------------------------------------------
 */

static gint cache_sim_read_skipline(FILE *f, int s)
{
	if (!f) return FALSE;

	if (fseek(f, 0 - s, SEEK_CUR) == 0)
		{
		char b;
		while (fread(&b, sizeof(b), 1, f) == 1)
			{
			if (b == '\n') return TRUE;
			}
		return TRUE;
		}

	return FALSE;
}

static gint cache_sim_read_comment(FILE *f, char *buf, int s, CacheData *cd)
{
	if (!f || !buf || !cd) return FALSE;

	if (s < 1 || buf[0] != '#') return FALSE;

	return cache_sim_read_skipline(f, s - 1);
}

static gint cache_sim_read_dimensions(FILE *f, char *buf, int s, CacheData *cd)
{
	if (!f || !buf || !cd) return FALSE;

	if (s < 10 || strncmp("Dimensions", buf, 10) != 0) return FALSE;

	if (fseek(f, - s, SEEK_CUR) == 0)
		{
		char b;
		char buf[1024];
		gint p = 0;
		gint w, h;

		b = 'X';
		while (b != '[')
			{
			if (fread(&b, sizeof(b), 1, f) != 1) return FALSE;
			}
		while (b != ']' && p < 1023)
			{
			if (fread(&b, sizeof(b), 1, f) != 1) return FALSE;
			buf[p] = b;
			p++;
			}

		while (b != '\n')
			{
			if (fread(&b, sizeof(b), 1, f) != 1) break;
			}

		buf[p] = '\0';
		if (sscanf(buf, "%d x %d", &w, &h) != 2) return FALSE;

		cd->width = w;
		cd->height = h;
		cd->dimensions = TRUE;

		return TRUE;
		}

	return FALSE;
}

static gint cache_sim_read_date(FILE *f, char *buf, int s, CacheData *cd)
{
	if (!f || !buf || !cd) return FALSE;

	if (s < 4 || strncmp("Date", buf, 4) != 0) return FALSE;

	if (fseek(f, - s, SEEK_CUR) == 0)
		{
		char b;
		char buf[1024];
		gint p = 0;

		b = 'X';
		while (b != '[')
			{
			if (fread(&b, sizeof(b), 1, f) != 1) return FALSE;
			}
		while (b != ']' && p < 1023)
			{
			if (fread(&b, sizeof(b), 1, f) != 1) return FALSE;
			buf[p] = b;
			p++;
			}

		while (b != '\n')
			{
			if (fread(&b, sizeof(b), 1, f) != 1) break;
			}

		buf[p] = '\0';
		cd->date = strtol(buf, NULL, 10);

		cd->have_date = TRUE;

		return TRUE;
		}

	return FALSE;
}

static gint cache_sim_read_checksum(FILE *f, char *buf, int s, CacheData *cd)
{
	if (!f || !buf || !cd) return FALSE;

	if (s < 8 || strncmp("Checksum", buf, 8) != 0) return FALSE;

	if (fseek(f, - s, SEEK_CUR) == 0)
		{
		char b;
		char buf[1024];
		gint p = 0;

		b = 'X';
		while (b != '[')
			{
			if (fread(&b, sizeof(b), 1, f) != 1) return FALSE;
			}
		while (b != ']' && p < 1023)
			{
			if (fread(&b, sizeof(b), 1, f) != 1) return FALSE;
			buf[p] = b;
			p++;
			}

		while (b != '\n')
			{
			if (fread(&b, sizeof(b), 1, f) != 1) break;
			}

		buf[p] = '\0';
		cd->checksum = strtol(buf, NULL, 10);

		cd->have_checksum = TRUE;

		return TRUE;
		}

	return FALSE;
}

static gint cache_sim_read_md5sum(FILE *f, char *buf, int s, CacheData *cd)
{
	if (!f || !buf || !cd) return FALSE;

	if (s < 8 || strncmp("MD5sum", buf, 6) != 0) return FALSE;

	if (fseek(f, - s, SEEK_CUR) == 0)
		{
		char b;
		char buf[64];
		gint p = 0;

		b = 'X';
		while (b != '[')
			{
			if (fread(&b, sizeof(b), 1, f) != 1) return FALSE;
			}
		while (b != ']' && p < 63)
			{
			if (fread(&b, sizeof(b), 1, f) != 1) return FALSE;
			buf[p] = b;
			p++;
			}
		while (b != '\n')
			{
			if (fread(&b, sizeof(b), 1, f) != 1) break;
			}

		buf[p] = '\0';
		cd->have_md5sum = md5_digest_from_text(buf, cd->md5sum);

		return TRUE;
		}

	return FALSE;
}

static gint cache_sim_read_similarity(FILE *f, char *buf, int s, CacheData *cd)
{
	if (!f || !buf || !cd) return FALSE;

	if (s < 11 || strncmp("Similarity", buf, 10) != 0) return FALSE;

	if (strncmp("Grid[32 x 32]", buf + 10, 13) != 0) return FALSE;

	if (fseek(f, - s, SEEK_CUR) == 0)
		{
		char b;
		guint8 pixel_buf[3];
		ImageSimilarityData *sd;
		gint x, y;

		b = 'X';
		while (b != '=')
			{
			if (fread(&b, sizeof(b), 1, f) != 1) return FALSE;
			}

		if (cd->sim)
			{
			/* use current sim that may already contain data we will not touch here */
			sd = cd->sim;
			cd->sim = NULL;
			cd->similarity = FALSE;
			}
		else
			{
			sd = image_sim_new();
			}

		for (y = 0; y < 32; y++)
			{
			gint s = y * 32;
			for (x = 0; x < 32; x++)
				{
				if (fread(&pixel_buf, sizeof(pixel_buf), 1, f) != 1)
					{
					image_sim_free(sd);
					return FALSE;
					}
				sd->avg_r[s + x] = pixel_buf[0];
				sd->avg_g[s + x] = pixel_buf[1];
				sd->avg_b[s + x] = pixel_buf[2];
				}
			}

		if (fread(&b, sizeof(b), 1, f) == 1)
			{
			if (b != '\n') fseek(f, -1, SEEK_CUR);
			}

		cd->sim = sd;
		cd->sim->filled = TRUE;
		cd->similarity = TRUE;

		return TRUE;
		}

	return FALSE;
}

#define CACHE_LOAD_LINE_NOISE 8

CacheData *cache_sim_data_load(const gchar *path)
{
	FILE *f;
	CacheData *cd = NULL;
	char buf[32];
	gint success = CACHE_LOAD_LINE_NOISE;
	gchar *pathl;

	if (!path) return NULL;

	pathl = path_from_utf8(path);
	f = fopen(pathl, "r");
	g_free(pathl);

	if (!f) return NULL;

	cd = cache_sim_data_new();
	cd->path = g_strdup(path);

	if (fread(&buf, sizeof(char), 9, f) != 9 ||
	    strncmp(buf, "SIMcache", 8) != 0)
		{
		if (debug) printf("%s is not a cache file\n", cd->path);
		success = 0;
		}

	while (success > 0)
		{
		int s;
		s = fread(&buf, sizeof(char), sizeof(buf), f);

		if (s < 1)
			{
			success = 0;
			}
		else
			{
			if (!cache_sim_read_comment(f, buf, s, cd) &&
			    !cache_sim_read_dimensions(f, buf, s, cd) &&
			    !cache_sim_read_date(f, buf, s, cd) &&
			    !cache_sim_read_checksum(f, buf, s, cd) &&
			    !cache_sim_read_md5sum(f, buf, s, cd) &&
			    !cache_sim_read_similarity(f, buf, s, cd))
				{
				if (!cache_sim_read_skipline(f, s))
					{
					success = 0;
					}
				else
					{
					success--;
					}
				}
			else
				{
				success = CACHE_LOAD_LINE_NOISE;
				}
			}
		}

	fclose(f);

	if (!cd->dimensions &&
	    !cd->have_date &&
	    !cd->have_checksum &&
	    !cd->have_md5sum &&
	    !cd->similarity)
		{
		cache_sim_data_free(cd);
		cd = NULL;
		}

	return cd;
}

/*
 *-------------------------------------------------------------------
 * sim cache setting
 *-------------------------------------------------------------------
 */

void cache_sim_data_set_dimensions(CacheData *cd, gint w, gint h)
{
	if (!cd) return;

	cd->width = w;
	cd->height = h;
	cd->dimensions = TRUE;
}

void cache_sim_data_set_date(CacheData *cd, time_t date)
{
	if (!cd) return;

	cd->date = date;
	cd->have_date = TRUE;
}

void cache_sim_data_set_checksum(CacheData *cd, long checksum)
{
	if (!cd) return;

	cd->checksum = checksum;
	cd->have_checksum = TRUE;
}

void cache_sim_data_set_md5sum(CacheData *cd, guchar digest[16])
{
	gint i;

	if (!cd) return;

	for (i = 0; i < 16; i++)
		{
		cd->md5sum[i] = digest[i];
		}
	cd->have_md5sum = TRUE;
}

void cache_sim_data_set_similarity(CacheData *cd, ImageSimilarityData *sd)
{
	if (!cd || !sd || !sd->filled) return;

	if (!cd->sim) cd->sim = image_sim_new();

	memcpy(cd->sim->avg_r, sd->avg_r, 1024);
	memcpy(cd->sim->avg_g, sd->avg_g, 1024);
	memcpy(cd->sim->avg_b, sd->avg_b, 1024);
	cd->sim->filled = TRUE;

	cd->similarity = TRUE;
}

gint cache_sim_data_filled(ImageSimilarityData *sd)
{
	if (!sd) return FALSE;
	return sd->filled;
}

/*
 *-------------------------------------------------------------------
 * cache path location utils
 *-------------------------------------------------------------------
 */

/* warning: this func modifies path string contents!, on fail it is set to fail point */
gint cache_ensure_dir_exists(gchar *path, mode_t mode)
{
	if (!path) return FALSE;

	if (!isdir(path))
		{
		gchar *p = path;
		while (p[0] != '\0')
			{
			p++;
			if (p[0] == '/' || p[0] == '\0')
				{
				gint end = TRUE;
				if (p[0] != '\0')
					{
					p[0] = '\0';
					end = FALSE;
					}
				if (!isdir(path))
					{
					if (debug) printf("creating sub dir:%s\n", path);
					if (!mkdir_utf8(path, mode))
						{
						printf("create dir failed: %s\n", path);
						return FALSE;
						}
					}
				if (!end) p[0] = '/';
				}
			}
		}
	return TRUE;
}

static void cache_path_parts(CacheType type,
			     const gchar **cache_rc, const gchar **cache_local, const gchar **cache_ext)
{
	switch (type)
		{
		case CACHE_TYPE_THUMB:
			*cache_rc = GQVIEW_CACHE_RC_THUMB;
			*cache_local = GQVIEW_CACHE_LOCAL_THUMB;
			*cache_ext = GQVIEW_CACHE_EXT_THUMB;
			break;
		case CACHE_TYPE_SIM:
			*cache_rc = GQVIEW_CACHE_RC_THUMB;
			*cache_local = GQVIEW_CACHE_LOCAL_THUMB;
			*cache_ext = GQVIEW_CACHE_EXT_SIM;
			break;
		case CACHE_TYPE_METADATA:
			*cache_rc = GQVIEW_CACHE_RC_METADATA;
			*cache_local = GQVIEW_CACHE_LOCAL_METADATA;
			*cache_ext = GQVIEW_CACHE_EXT_METADATA;
			break;
		}
}

gchar *cache_get_location(CacheType type, const gchar *source, gint include_name, mode_t *mode)
{
	gchar *path = NULL;
	gchar *base;
	gchar *name = NULL;
	const gchar *cache_rc;
	const gchar *cache_local;
	const gchar *cache_ext;

	if (!source) return NULL;

	cache_path_parts(type, &cache_rc, &cache_local, &cache_ext);

	base = remove_level_from_path(source);
	if (include_name)
		{
		name = g_strconcat("/", filename_from_path(source), NULL);
		}
	else
		{
		cache_ext = NULL;
		}

	if (((type != CACHE_TYPE_METADATA && enable_thumb_dirs) ||
	     (type == CACHE_TYPE_METADATA && enable_metadata_dirs)) &&
	    access_file(base, W_OK))
		{
		path = g_strconcat(base, "/", cache_local, name, cache_ext, NULL);
		if (mode) *mode = 0775;
		}

	if (!path)
		{
		path = g_strconcat(homedir(), "/", cache_rc, base, name, cache_ext, NULL);
		if (mode) *mode = 0755;
		}

	g_free(base);
	if (name) g_free(name);

	return path;
}

gchar *cache_find_location(CacheType type, const gchar *source)
{
	gchar *path;
	const gchar *name;
	gchar *base;
	const gchar *cache_rc;
	const gchar *cache_local;
	const gchar *cache_ext;
	gint prefer_local;

	if (!source) return NULL;

	cache_path_parts(type, &cache_rc, &cache_local, &cache_ext);

	name = filename_from_path(source);
	base = remove_level_from_path(source);

	if (type == CACHE_TYPE_METADATA)
		{
		prefer_local = enable_metadata_dirs;
		}
	else
		{
		prefer_local = enable_thumb_dirs;
		}

	if (prefer_local)
		{
		path = g_strconcat(base, "/", cache_local, "/", name, cache_ext, NULL);
		}
	else
		{
		path = g_strconcat(homedir(), "/", cache_rc, source, cache_ext, NULL);
		}

	if (!isfile(path))
		{
		g_free(path);

		/* try the opposite method if not found */
		if (!prefer_local)
			{
			path = g_strconcat(base, "/", cache_local, "/", name, cache_ext, NULL);
			}
		else
			{
			path = g_strconcat(homedir(), "/", cache_rc, source, cache_ext, NULL);
			}

		if (!isfile(path))
			{
			g_free(path);
			path = NULL;
			}
		}

	g_free(base);

	return path;
}

gint cache_time_valid(const gchar *cache, const gchar *path)
{
	struct stat cache_st;
	struct stat path_st;
	gchar *cachel;
	gchar *pathl;
	gint ret = FALSE;

	if (!cache || !path) return FALSE;

	cachel = path_from_utf8(cache);
	pathl = path_from_utf8(path);

	if (stat(cachel, &cache_st) == 0 &&
	    stat(pathl, &path_st) == 0)
		{
		if (cache_st.st_mtime == path_st.st_mtime)
			{
			ret = TRUE;
			}
		else if (cache_st.st_mtime > path_st.st_mtime)
			{
			struct utimbuf ut;

			ut.actime = ut.modtime = cache_st.st_mtime;
			if (utime(cachel, &ut) < 0 &&
			    errno == EPERM)
				{
				if (debug) printf("cache permission workaround: %s\n", cachel);
				ret = TRUE;
				}
			}
		}

	g_free(pathl);
	g_free(cachel);

	return ret;
}

