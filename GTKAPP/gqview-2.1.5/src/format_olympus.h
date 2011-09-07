/*
 *  GQView
 *  (C) 2005 John Ellis
 *
 * This software is released under the GNU General Public License (GNU GPL).
 * Please read the included file COPYING for more information.
 * This software comes with no warranty of any kind, use at your own risk!
 */

#ifndef __FORMAT_OLYMPUS_H
#define __FORMAT_OLYMPUS_H


#include "exif.h"


gint format_olympus_raw(unsigned char *data, const guint len,
			guint *image_offset, guint *exif_offset);


#define FORMAT_RAW_OLYMPUS { "orf", \
			     FORMAT_RAW_MATCH_MAGIC, 0, "IIR", 3, \
			     FORMAT_RAW_EXIF_IFD_II, NULL, \
			     "Olympus raw", format_olympus_raw }


gint format_olympus_makernote(ExifData *exif, unsigned char *tiff, guint offset,
			      guint size, ExifByteOrder bo);

#define FORMAT_EXIF_OLYMPUS { FORMAT_EXIF_MATCH_MAKERNOTE, "OLYMP\x00\x01", 7, \
			      "Olympus", format_olympus_makernote }, \
			    { FORMAT_EXIF_MATCH_MAKERNOTE, "OLYMP\x00\x02", 7, \
			      "Olympus", format_olympus_makernote }


#endif

