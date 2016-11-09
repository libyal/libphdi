AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	@LIBCERROR_CPPFLAGS@ \
	@LIBCDATA_CPPFLAGS@ \
	@LIBCLOCALE_CPPFLAGS@ \
	@LIBCNOTIFY_CPPFLAGS@ \
	@LIBCSPLIT_CPPFLAGS@ \
	@LIBUNA_CPPFLAGS@ \
	@LIBCFILE_CPPFLAGS@ \
	@LIBCPATH_CPPFLAGS@ \
	@LIBBFIO_CPPFLAGS@ \
	@LIBFCACHE_CPPFLAGS@ \
	@LIBFDATA_CPPFLAGS@ \
	@LIBCSYSTEM_CPPFLAGS@ \
	@LIBFUSE_CPPFLAGS@ \
	@LIBPHDI_DLL_IMPORT@

AM_LDFLAGS = @STATIC_LDFLAGS@

bin_PROGRAMS = \
	phdiinfo \
	phdimount

phdiinfo_SOURCES = \
	info_handle.c info_handle.h \
	phdiinfo.c \
	phdioutput.c phdioutput.h \
	phditools_libbfio.h \
	phditools_libcdata.h \
	phditools_libcerror.h \
	phditools_libclocale.h \
	phditools_libcnotify.h \
	phditools_libcsystem.h \
	phditools_libphdi.h \
	phditools_libuna.h

phdiinfo_LDADD = \
	@LIBCSYSTEM_LIBADD@ \
	../libphdi/libphdi.la \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCERROR_LIBADD@ \
	@LIBINTL@

phdimount_SOURCES = \
	mount_handle.c mount_handle.h \
	phdimount.c \
	phdioutput.c phdioutput.h \
	phditools_libbfio.h \
	phditools_libcdata.h \
	phditools_libcerror.h \
	phditools_libclocale.h \
	phditools_libcnotify.h \
	phditools_libcpath.h \
	phditools_libcsystem.h \
	phditools_libphdi.h \
	phditools_libuna.h

phdimount_LDADD = \
	@LIBFUSE_LIBADD@ \
	@LIBCSYSTEM_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	../libphdi/libphdi.la \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	@LIBCERROR_LIBADD@ \
	@LIBINTL@

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f Makefile

splint:
	@echo "Running splint on phdiinfo ..."
	-splint -preproc -redef $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(phdiinfo_SOURCES)
	@echo "Running splint on phdimount ..."
	-splint -preproc -redef $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(phdimount_SOURCES)

