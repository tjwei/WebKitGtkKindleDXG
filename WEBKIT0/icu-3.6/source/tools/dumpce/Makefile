## Makefile.in for ICU - tools/dumpce
## Copyright (c) 2001, International Business Machines Corporation and
## others. All Rights Reserved.

## Source directory information
srcdir = .
top_srcdir = ../..

top_builddir = ../..

include $(top_builddir)/icudefs.mk

## Build directory information
subdir = tools/dumpce

## Extra files to remove for 'make clean'
CLEANFILES = *~ $(DEPS)

## Target information
TARGET = dumpce

CPPFLAGS += -I$(top_srcdir)/common -I$(top_srcdir)/i18n -I$(top_srcdir)/tools/toolutil
LIBS = $(LIBICUI18N) $(LIBICUUC) $(LIBICUTOOLUTIL) $(DEFAULT_LIBS) $(LIB_M)

OBJECTS = dumpce.o

DEPS = $(OBJECTS:.o=.d)

## List of phony targets
.PHONY : all all-local install install-local clean clean-local	\
distclean distclean-local dist dist-local check check-local

## Clear suffix list
.SUFFIXES :

## List of standard targets
all: all-local
install: install-local
clean: clean-local
distclean : distclean-local
dist: dist-local
check: all check-local

all-local: $(TARGET)

install-local:

dist-local:

clean-local:
	test -z "$(CLEANFILES)" || $(RMV) $(CLEANFILES)
	$(RMV) $(OBJECTS) $(TARGET)

distclean-local: clean-local
	$(RMV) Makefile

check-local: all-local

Makefile: $(srcdir)/Makefile.in  $(top_builddir)/config.status
	cd $(top_builddir) \
	 && CONFIG_FILES=$(subdir)/$@ CONFIG_HEADERS= $(SHELL) ./config.status

$(TARGET) : $(OBJECTS)
	$(LINK.cc) -o $@ $^ $(LIBS)

invoke:
	ICU_DATA=$${ICU_DATA:-$(top_builddir)/data/} TZ=PST8PDT $(INVOKE) $(INVOCATION)

ifeq (,$(MAKECMDGOALS))
-include $(DEPS)
else
ifneq ($(patsubst %clean,,$(MAKECMDGOALS)),)
-include $(DEPS)
endif
endif
