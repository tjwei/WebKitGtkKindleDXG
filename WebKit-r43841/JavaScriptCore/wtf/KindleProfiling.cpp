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
#include "KindleProfiling.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <time.h>
#include <stdarg.h>

int kindle_debug_flags = 0;
kindle_stats_t kindle_stats;

static struct timespec kindle_start_load_time;
//static clock_t kindle_cpu_start_load_time;
static FILE *outputFile = 0;
static char *outputFileName = 0;

static struct rusage kindle_cpu_start_load_time;


void kindle_start_time()
{
    clock_gettime(CLOCK_MONOTONIC, &kindle_start_load_time);
    getrusage(RUSAGE_SELF, &kindle_cpu_start_load_time);

//	kindle_cpu_start_load_time = clock();
}

void kindle_set_ouput_file(const char *fileName)
{
	if (!fileName || !*fileName) {
		if (outputFile) {
			fclose(outputFile);
		}
		if (outputFileName) {
			free(outputFileName);
			outputFileName = 0;
		}
		return;
	}
	if (!outputFileName || strcmp(fileName, outputFileName)) {
		if (outputFile) {
			fclose(outputFile);
		}
		outputFileName = (char *) realloc(outputFileName, strlen(fileName)+1);
		strcpy(outputFileName, fileName);
		if (!(outputFile = fopen(outputFileName, "w"))) {
			free(outputFileName);
			outputFileName = 0;
			fprintf(stderr, "kindle_set_ouput_file: Could not open %s for writing\n", fileName);
		}
	}
}

/* Extract from the KINDLE_DEBUG environment variable the modules that should be logged */
int kindle_set_debug_flags(const char *debugStr)
{
	kindle_debug_flags = 0;

	if (!debugStr) {
		return 0;
	}

	struct _mapping {
		const char *name;
		int length;
		int flag;
	};
	const struct _mapping mappings[] = {
		{"all", 		3,  Kindle_Debug_All},
		{"keys", 		4,  Kindle_Debug_Keys},
		{"perf", 		4,  Kindle_Debug_Perf},
		{"perfDetails", 11, Kindle_Debug_Perf | Kindle_Debug_Perf_Details},
		{"regions", 	7,  Kindle_Debug_Regions},
		{"resources", 	9,  Kindle_Debug_Resources},
		{"memory", 		6,  Kindle_Debug_Memory},
		{"memoryDetails", 13, Kindle_Debug_Memory | Kindle_Debug_Memory_Details},
        {"network", 	7,  Kindle_Debug_Network},

		{"showLocation", 12, Kindle_Show_Location}
	};

	// This is a comma separated list of flags
	const char *current = debugStr;
	while (*current) {

		// Skip spaces
		while (*current && *current <= ' ') {
			current++;
		}

		// Find the end of the current flag
		const char *end = current;
		while (*end && *end > ' ' && *end != ',' && *end != '\n' && *end != '#' && *end != '=') {
			end++;
		}

		// Find a match
		int count = sizeof(mappings)/sizeof(struct _mapping);
		const struct _mapping *mapping = mappings;
		while (count--) {
			if (end-current == mapping->length && !strncmp(current, mapping->name, mapping->length)) {
				kindle_debug_flags |= mapping->flag;
				break;
			}
			mapping++;
		}


		// Find the ',' separator or the end of the string
		current = end;
		while (*current && *current != ',') {
			current++;
		}
		if (*current == ',') {
			current++;
		}
	}

	return kindle_debug_flags;
}

void kindle_reset_stats()
{
	memset(&kindle_stats, 0, sizeof(kindle_stats_t));
}

kindle_stats_t *kindle_get_stats()
{
	return &kindle_stats;
}

float kindle_time_from_start()
{
	struct timespec endTime;
	clock_gettime(CLOCK_MONOTONIC, &endTime);
	return kindle_time_diff(kindle_start_load_time, endTime);
}

float kindle_time_diff(struct timespec start, struct timespec end)
{
	return end.tv_sec-start.tv_sec + (end.tv_nsec-start.tv_nsec)/1000000000.0;
}

float kindle_cpu_time_from_start()
{
	struct rusage endTime;
	getrusage(RUSAGE_SELF, &endTime);
	return kindle_cpu_time_diff(kindle_cpu_start_load_time, endTime);
}

float kindle_cpu_time_diff(struct rusage start, struct rusage end)
{
	time_t sec = start.ru_utime.tv_sec+start.ru_stime.tv_sec;
	time_t usec = start.ru_utime.tv_usec+start.ru_stime.tv_usec;
	time_t endsec = end.ru_utime.tv_sec+end.ru_stime.tv_sec;
	time_t endusec = end.ru_utime.tv_usec+end.ru_stime.tv_usec;
	return endsec-sec + (endusec - usec)*1e-6;
}

void kindle_print(const char* file, int line, const char *function, int prefixedByTime, const char *format, ...)
{
	FILE *output = (outputFile) ? outputFile : stderr;
	if (kindle_debug_flags & Kindle_Show_Location) {
		fprintf(output, "%s (%d): %s\n", file, line, function);
	}
	if (prefixedByTime) {
		fprintf(output, "%.3fs - ", kindle_time_from_start());
	}

	va_list args;
    va_start(args, format);
    vfprintf(output, format, args);
    va_end(args);
	fflush(output);
}

// </lab126>
