## Process this file with automake to produce Makefile.in

## Created by Anjuta - will be overwritten
## If you don't want it to overwrite it,
## 	Please disable it in the Anjuta project configuration

INCLUDES = \
	$(GTK_CFLAGS)

AM_CFLAGS =\
	$(vte_CFLAGS)\
	 -Wall\
	 -g

bin_PROGRAMS = gtkterm2

gtkterm2_SOURCES = \
	support.h\
	support.c\
	main.c\
	interface.h\
	interface.c\
	callbacks.h\
	callbacks.c\
	prefs.c\
	prefs.h

gtkterm2_LDFLAGS = \
	$(vte_LIBS)

gtkterm2_LDADD =  \
	$(GTK_LIBS)

