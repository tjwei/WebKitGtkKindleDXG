## Makefile.in for ICU - extra/scrptrun
## Copyright (c) 2001, International Business Machines Corporation and
## others. All Rights Reserved.

## Source directory information
srcdir = .
top_srcdir = ../..

top_builddir = ../..

include $(top_builddir)/icudefs.mk

## Platform-specific setup
include $(top_srcdir)/config/mh-linux

## Build directory information
subdir = extra/scrptrun

## Extra files to remove for 'make clean'
CLEANFILES = *~ $(DEPS)

## Target information
TARGET = srtest

DEFS = -DHAVE_CONFIG_H
CPPFLAGS = -O2 -march=armv6j -mtune=arm1136jf-s -pipe -fomit-frame-pointer -fno-stack-protector $(THREADSCPPFLAGS) -I$(top_builddir)/common -I$(top_srcdir)/common -I$(top_srcdir) 
CFLAGS = -g -O2 $(THREADSCFLAGS)
CXXFLAGS = -g -O2 $(THREADSCXXFLAGS)
ENABLE_RPATH = NO
ifeq ($(ENABLE_RPATH),YES)
RPATHLDFLAGS = $(LD_RPATH)$(LD_RPATH_PRE)$(libdir)
endif
LDFLAGS =  $(RPATHLDFLAGS)
LIBS = $(LIBICUUC) -lpthread -lm  

OBJECTS = scrptrun.o srtest.o

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
