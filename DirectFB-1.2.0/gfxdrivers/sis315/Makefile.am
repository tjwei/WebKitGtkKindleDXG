## Makefile.am for DirectFB/src/core/gfxcards/sis315

INCLUDES = \
	-I$(top_srcdir)/include	\
	-I$(top_builddir)/lib	\
	-I$(top_srcdir)/lib	\
	-I$(top_srcdir)/src	\
	-I$(top_srcdir)/systems

sis315_LTLIBRARIES = libdirectfb_sis315.la

if BUILD_STATIC
sis315_DATA = $(sis315_LTLIBRARIES:.la=.o)
endif

sis315dir = $(MODULEDIR)/gfxdrivers

libdirectfb_sis315_la_SOURCES =	\
	sis315.c		\
	sis315.h		\
	sis315_accel.c		\
	sis315_accel.h		\
	sis315_compat.h		\
	sis315_mmio.c		\
	sis315_mmio.h		\
	sis315_regs.h		\
	sis315_state.c		\
	sis315_state.h

libdirectfb_sis315_la_LDFLAGS = \
	-export-dynamic		\
	-avoid-version		\
	$(DFB_LDFLAGS)

libdirectfb_sis315_la_LIBADD = \
	$(top_builddir)/lib/direct/libdirect.la \
	$(top_builddir)/src/libdirectfb.la


include $(top_srcdir)/rules/libobject.make
	
