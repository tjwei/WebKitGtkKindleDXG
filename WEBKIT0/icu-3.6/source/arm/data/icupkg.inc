#******************************************************************************
#
#   Copyright (C) 2000-2004, International Business Machines
#   Corporation and others.  All Rights Reserved.
#
#******************************************************************************
# This Makefile is used to build the ICU's data.
# It is included with the -O option to pkgdata.

top_srcdir=..
srcdir=.
top_builddir=..

include $(top_builddir)/icudefs.mk

CPPFLAGS+= -I$(top_builddir)/common -I$(top_srcdir)/common
LDFLAGS= $(PKGDATA_LDFLAGS)
exec_prefix=${prefix}
prefix=/usr/local
bindir=${exec_prefix}/bin
sbindir=${exec_prefix}/sbin
libexecdir=${exec_prefix}/libexec
datadir=${prefix}/share
sysconfdir=${prefix}/etc
sharedstatedir=${prefix}/com
localstatedir=${prefix}/var
libdir=${exec_prefix}/lib
includedir=${prefix}/include
oldincludedir=/usr/include
infodir=${prefix}/info
mandir=${prefix}/man

INSTALL = /usr/bin/install -c
INSTALL_PROGRAM = ${INSTALL}
INSTALL_DATA = ${INSTALL} -m 644

INSTALL_PROGRAM=${INSTALL}
INSTALL_SCRIPT=${INSTALL}
INSTALL_DATA=${INSTALL} -m 644
MKINSTALLDIRS = $(SHELL) $(top_srcdir)/mkinstalldirs
host=arm-none-linux-gnueabi
host_alias=arm-none-linux-gnueabi
host_cpu=arm
host_vendor=none
host_os=linux-gnueabi
CPP=arm-none-linux-gnueabi-gcc -E
U_HAVE_INTTYPES_H=1
U_IS_BIG_ENDIAN=0

ld_rpath_suf= 

##### Add the following to source/config/Makefile.in

GENCCODE=$(BINDIR)/genccode
GENCMN=$(BINDIR)/gencmn


