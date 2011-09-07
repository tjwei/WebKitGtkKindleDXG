/*
 *  GQView
 *  (C) 2006 John Ellis
 *
 *  Authors:
 *    Support for Exif file format, originally written by Eric Swalens.    
 *    Modified by Quy Tonthat
 *    Reimplemented with generic data storage by John Ellis
 *

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*/

#ifndef __EXIF_H
#define __EXIF_H


/*
 *-----------------------------------------------------------------------------
 * Tag formats
 *-----------------------------------------------------------------------------
 */

#define EXIF_FORMAT_COUNT 13

typedef enum {
	EXIF_FORMAT_UNKNOWN		= 0,
	EXIF_FORMAT_BYTE_UNSIGNED	= 1,
	EXIF_FORMAT_STRING		= 2,
	EXIF_FORMAT_SHORT_UNSIGNED	= 3,
	EXIF_FORMAT_LONG_UNSIGNED	= 4,
	EXIF_FORMAT_RATIONAL_UNSIGNED	= 5,
	EXIF_FORMAT_BYTE		= 6,
	EXIF_FORMAT_UNDEFINED		= 7,
	EXIF_FORMAT_SHORT		= 8,
	EXIF_FORMAT_LONG		= 9,
	EXIF_FORMAT_RATIONAL		= 10,
	EXIF_FORMAT_FLOAT		= 11,
	EXIF_FORMAT_DOUBLE		= 12
} ExifFormatType;

typedef enum {
	EXIF_BYTE_ORDER_INTEL,
	EXIF_BYTE_ORDER_MOTOROLA
} ExifByteOrder;

typedef struct _ExifFormatAttrib ExifFormatAttrib;
struct _ExifFormatAttrib
{
	ExifFormatType type;
	guint size;
	const gchar *short_name;
	const gchar *description;
};

/* the list of known tag data formats */
extern ExifFormatAttrib ExifFormatList[];


/*
 *-----------------------------------------------------------------------------
 * Data storage
 *-----------------------------------------------------------------------------
 */

typedef struct _ExifData ExifData;
struct _ExifData
{
	GList *items;	/* list of (ExifItem *) */
};

typedef struct _ExifRational ExifRational;
struct _ExifRational
{
	guint32 num;
	guint32 den;
};


typedef struct _ExifItem ExifItem;
typedef struct _ExifMarker ExifMarker;
typedef struct _ExifTextList ExifTextList;

struct _ExifItem
{
	ExifFormatType format;
	guint tag;
	const ExifMarker *marker;
	guint elements;
	gpointer data;
	guint data_len;
};

struct _ExifMarker
{
	guint		tag;
	ExifFormatType	format;
	gint		components;
	gchar		*key;
	gchar		*description;
	ExifTextList	*list;
};

#define EXIF_MARKER_LIST_END { 0x0000, EXIF_FORMAT_UNKNOWN, 0, NULL, NULL, NULL }

struct _ExifTextList
{
	gint value;
	const gchar* description;
};

#define EXIF_TEXT_LIST_END { -1, NULL }


typedef struct _ExifFormattedText ExifFormattedText;
struct _ExifFormattedText
{
	const gchar *key;
	const gchar *description;
};


/*
 *-----------------------------------------------------------------------------
 * Data
 *-----------------------------------------------------------------------------
 */

/* enums useful for image manipulation */

typedef enum {
	EXIF_ORIENTATION_UNKNOWN	= 0,
	EXIF_ORIENTATION_TOP_LEFT	= 1,
	EXIF_ORIENTATION_TOP_RIGHT	= 2,
	EXIF_ORIENTATION_BOTTOM_RIGHT	= 3,
	EXIF_ORIENTATION_BOTTOM_LEFT	= 4,
	EXIF_ORIENTATION_LEFT_TOP	= 5,
	EXIF_ORIENTATION_RIGHT_TOP	= 6,
	EXIF_ORIENTATION_RIGHT_BOTTOM	= 7,
	EXIF_ORIENTATION_LEFT_BOTTOM	= 8
} ExifOrientationType;

typedef enum {
	EXIF_UNIT_UNKNOWN	= 0,
	EXIF_UNIT_NOUNIT	= 1,
	EXIF_UNIT_INCH		= 2,
	EXIF_UNIT_CENTIMETER	= 3
} ExifUnitType;


/* the known exif tags list */
extern ExifMarker ExifKnownMarkersList[];

/* the unknown tags utilize this generic list */
extern ExifMarker ExifUnknownMarkersList[];

/* the list of specially formatted keys, for human readable output */
extern ExifFormattedText ExifFormattedList[];


/*
 *-----------------------------------------------------------------------------
 * functions
 *-----------------------------------------------------------------------------
 */

ExifData *exif_read(const gchar *path, gint parse_color_profile);
void exif_free(ExifData *exif);

gchar *exif_get_data_as_text(ExifData *exif, const gchar *key);
gint exif_get_integer(ExifData *exif, const gchar *key, gint *value);
ExifRational *exif_get_rational(ExifData *exif, const gchar *key, gint *sign);
double exif_rational_to_double(ExifRational *r, gint sign);

ExifItem *exif_get_item(ExifData *exif, const gchar *key);

const char *exif_item_get_tag_name(ExifItem *item);
const char *exif_item_get_description(ExifItem *item);
const char *exif_item_get_format_name(ExifItem *item, gint brief);
gchar *exif_item_get_data_as_text(ExifItem *item);
gint exif_item_get_integer(ExifItem *item, gint *value);
ExifRational *exif_item_get_rational(ExifItem *item, gint *sign);

const gchar *exif_get_description_by_key(const gchar *key);

/* usually for debugging to stdout */
void exif_write_data_list(ExifData *exif, FILE *f, gint human_readable_list);



/* These funcs for use by makernote/tiff parsers only */

#define EXIF_TIFF_MAX_LEVELS 4

#define EXIF_TIFD_OFFSET_TAG 0
#define EXIF_TIFD_OFFSET_FORMAT 2
#define EXIF_TIFD_OFFSET_COUNT 4
#define EXIF_TIFD_OFFSET_DATA 8
#define EXIF_TIFD_SIZE 12


guint16 exif_byte_get_int16(unsigned char *f, ExifByteOrder bo);
guint32 exif_byte_get_int32(unsigned char *f, ExifByteOrder bo);
void exif_byte_put_int16(unsigned char *f, guint16 n, ExifByteOrder bo);
void exif_byte_put_int32(unsigned char *f, guint32 n, ExifByteOrder bo);

ExifItem *exif_item_new(ExifFormatType format, guint tag,
			guint elements, const ExifMarker *marker);
void exif_item_copy_data(ExifItem *item, void *src, guint len,
			 ExifFormatType src_format, ExifByteOrder bo);

gint exif_parse_IFD_table(ExifData *exif,
			  unsigned char *tiff, guint offset,
			  guint size, ExifByteOrder bo,
			  gint level,
			  const ExifMarker *list);

gint exif_tiff_directory_offset(unsigned char *data, const guint len,
				guint *offset, ExifByteOrder *bo);
gint exif_tiff_parse(ExifData *exif, unsigned char *tiff, guint size, ExifMarker *list);

gchar *exif_text_list_find_value(ExifTextList *list, guint value);


#endif

