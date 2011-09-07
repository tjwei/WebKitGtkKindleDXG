## Process this file with automake to produce Makefile.in.

SUBDIRS = src po doc
DIST_SUBDIRS = src po doc

man_MANS = gqview.1

readmedir = $(datadir)/doc/gqview-$(VERSION)
readme_DATA = README COPYING ChangeLog TODO

desktopdir = $(datadir)/applications
desktop_DATA = gqview.desktop

icondir = $(datadir)/pixmaps
icon_DATA = gqview.png

EXTRA_DIST = \
	$(readme_DATA)	\
	$(desktop_DATA)	\
	$(icon_DATA)	\
	gqview.spec.in	\
	gqview.1

dist-hook: gqview.spec
	cp $(top_builddir)/gqview.spec $(distdir)


