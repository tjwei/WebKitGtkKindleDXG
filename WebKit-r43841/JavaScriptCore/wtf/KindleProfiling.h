/*
 *  Copyright (c) 2009 Amazon Technologies Inc. All rights reserved.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Library General Public
 *  License as published by the Free Software Foundation; either
 *  version 2 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Library General Public License for more details.
 *
 *  You should have received a copy of the GNU Library General Public License
 *  along with this library; see the file COPYING.LIB.  If not, write to
 *  the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 *  Boston, MA 02110-1301, USA.
 *
 */

// <lab126>
#ifndef WTF_PerfMeasure_h
#define WTF_PerfMeasure_h

#include <sys/time.h>
#include <sys/resource.h>
#include "Platform.h"


#ifdef KINDLE_DISABLE_PERFORMANCE
#define KINDLE_BEGIN(group) if (0) {
#else
#define KINDLE_BEGIN(group) if (kindle_debug_flags & (group)) {
#endif
#define KINDLE_PRINT(fmt, a...) kindle_print(__FILE__, __LINE__, __FUNCTION__, TRUE, fmt, a)
#define KINDLE_PRINT_NO_ARGS(fmt) kindle_print(__FILE__, __LINE__, __FUNCTION__, TRUE, fmt)
#define KINDLE_PRINT_NO_TIME(fmt, a...) kindle_print(__FILE__, __LINE__, __FUNCTION__, FALSE, fmt, a)
#define KINDLE_PRINT_NO_TIME_NO_ARGS(fmt) kindle_print(__FILE__, __LINE__, __FUNCTION__, FALSE, fmt)
#define KINDLE_END()		}

#define KINDLE_PRINT_MODULE(g, n, a...) do {if (kindle_debug_flags & (g)) {kindle_print(__FILE__, __LINE__, __FUNCTION__, TRUE, n, ##a);} } while (0)

/* This flags are set in the KINDLE_DEBUG file added to the user space. Strings are listed in gdkkindle.c in the Mappings structure. */
/* CAUTION: When adding a new enumeration, the mappings array in gdkkindle.c needs to be updated */
enum {
	Kindle_Debug_All 			= 0x00FFFFFF,	/* all */

	Kindle_Debug_Keys 			= 0x00000001,	/* keys */
	Kindle_Debug_Perf 			= 0x00000002,	/* perf */
	Kindle_Debug_Perf_Details 	= 0x00000004,	/* perfDetails */
	Kindle_Debug_Regions 		= 0x00000008,	/* regions */
	Kindle_Debug_Resources		= 0x00000010,   /* resources */
	Kindle_Debug_Memory			= 0x00000020,   /* memory */
	Kindle_Debug_Memory_Details	= 0x00000040,   /* memoryDetails */
    Kindle_Debug_Network		= 0x00000080,   /* network */


	/* Misc other controls */
	Kindle_Show_Location		= 0x10000000	/* showLocation: For each print out provide the line, file and function name */
};

typedef struct _kindle_stats {
	int updateCount;
	int fullUpdateCount;
	float totalUpdateTime;
	float totalRenderingTime;
	float totalBlitTime;
	float totalJSEvaluation;
	int   totalJSRequested;
	int   totalCSSRequested;
	int   totalImagesRequested;

	/* Text rendering */
	float totalSimpleTextRenderingTime;
	float totalComplexTextRenderingTime;
	int   totalSimpleTextRenderingCount;
	int   totalComplexTextRenderingCount;

	/* Image rendering */
	float totalImageRenderingTime;
	int   totalImageRenderingCount;

	/* Memory usage */
	int   totalImageMemoryUsage; /* in bytes */
	int   totalImageMemoryUsageCount;

} kindle_stats_t;
WEBCORE_EXPORT extern kindle_stats_t kindle_stats;
WEBCORE_EXPORT extern int kindle_debug_flags;

/* These 2 methods are used so that webkit can access the global variables */
WEBCORE_EXPORT void kindle_start_time();
WEBCORE_EXPORT int kindle_set_debug_flags(const char *debugStr);
WEBCORE_EXPORT void kindle_set_ouput_file(const char *fileName);
WEBCORE_EXPORT void kindle_reset_stats();
WEBCORE_EXPORT kindle_stats_t *kindle_get_stats();

WEBCORE_EXPORT void kindle_print(const char* file, int line, const char *function, int prefixedByTime, const char *format, ...);

/* Times obtained by clock_gettime */
WEBCORE_EXPORT float kindle_time_from_start();
WEBCORE_EXPORT float kindle_time_diff(struct timespec start, struct timespec end);

/* Times obtained by getrusage */
WEBCORE_EXPORT float kindle_cpu_time_from_start();
WEBCORE_EXPORT float kindle_cpu_time_diff(struct rusage start, struct rusage end);

#endif // WTF_PerfMeasure_h
// </lab126>

