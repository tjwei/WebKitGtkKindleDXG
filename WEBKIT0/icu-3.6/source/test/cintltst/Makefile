#******************************************************************************
#
#   Copyright (C) 1999-2006, International Business Machines
#   Corporation and others.  All Rights Reserved.
#
#******************************************************************************
## Makefile.in for ICU - test/cintltst

## Source directory information
srcdir = .
top_srcdir = ../..

top_builddir = ../..

## All the flags and other definitions are included here.
include $(top_builddir)/icudefs.mk

## Build directory information
subdir = test/cintltst

## Extra files to remove for 'make clean'
CLEANFILES = *~ $(DEPS)

## Target information
TARGET = cintltst$(EXEEXT)

# Oh, this hurts my sensibility. This is supposedly a C test and we need to
# link using a C++ compiler?! This must be done so that library vtables
# work correctly on all platforms.

ifneq ($(ENABLE_STATIC),)
LINK = $(LINK.cc)
else
LINK = $(LINK.c)
endif

BUILDDIR := $(CURR_SRCCODE_FULL_DIR)/../../
# Simplify the path for Unix
BUILDDIR := $(BUILDDIR:test/cintltst/../../=)
# Simplify the path for Windows
BUILDDIR := $(BUILDDIR:test\\cintltst/../../=)
# Simplify the path for Windows 98
BUILDDIR := $(BUILDDIR:TEST\\CINTLTST/../../=)

ifneq ($(top_builddir),$(top_srcdir))
CPPFLAGS += -I$(top_builddir)/common
endif
# we define ICU_UNICODE_VERSION so we can test it
CPPFLAGS += -I$(top_srcdir)/common -I$(top_srcdir)/i18n -I$(top_srcdir)/tools/ctestfw -I$(top_srcdir)/tools/toolutil
DEFS += -D'ICU_UNICODE_VERSION="$(UNICODE_VERSION)"' -D'ICU_VERSION="3.6"' -D'ICUDATA_NAME="$(ICUDATA_PLATFORM_NAME)"' -D'U_TOPSRCDIR="$(top_srcdir)/"' -D'U_TOPBUILDDIR="$(BUILDDIR)"'
LIBS = $(LIBCTESTFW) $(LIBICUI18N) $(LIBICUUC) $(LIBICUTOOLUTIL) $(DEFAULT_LIBS) $(LIB_M)

OBJECTS = callcoll.o calltest.o colutil.o capitst.o cbiapts.o cbkittst.o \
ccaltst.o cctest.o ccapitst.o ccolltst.o encoll.o cconvtst.o ccurrtst.o \
cdattst.o cdetst.o cdtdptst.o cdtrgtst.o cestst.o cfintst.o cformtst.o \
cfrtst.o cg7coll.o chashtst.o cintltst.o citertst.o cjaptst.o cloctst.o \
cmsccoll.o cmsgtst.o cposxtst.o cldrtest.o \
cnmdptst.o cnormtst.o cnumtst.o crestst.o creststn.o cturtst.o \
cucdapi.o cucdtst.o custrtst.o cstrcase.o cutiltst.o nucnvtst.o nccbtst.o bocu1tst.o \
cbiditst.o cbididat.o eurocreg.o udatatst.o utf16tst.o utransts.o \
ncnvfbts.o ncnvtst.o putiltst.o cstrtest.o utf8tst.o \
stdnmtst.o ctstdep.o usrchtst.o custrtrn.o sorttest.o trietest.o usettest.o \
uenumtst.o utmstest.o currtest.o \
idnatest.o nfsprep.o spreptst.o sprpdata.o \
hpmufn.o tracetst.o reapits.o utexttst.o ucsdetst.o

DEPS = $(OBJECTS:.o=.d)

-include Makefile.local

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
	$(INVOKE) ./$(TARGET) $(CINTLTST_OPTS)

Makefile: $(srcdir)/Makefile.in  $(top_builddir)/config.status
	cd $(top_builddir) \
	 && CONFIG_FILES=$(subdir)/$@ CONFIG_HEADERS= $(SHELL) ./config.status

$(TARGET) : $(OBJECTS)
	$(LINK) $(OUTOPT)$@ $^ $(LIBS)

ifeq (,$(MAKECMDGOALS))
-include $(DEPS)
else
ifneq ($(patsubst %clean,,$(MAKECMDGOALS)),)
ifneq ($(patsubst %install,,$(MAKECMDGOALS)),)
-include $(DEPS)
endif
endif
endif

