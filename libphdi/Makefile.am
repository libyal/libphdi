AM_CPPFLAGS = \
	-DLOCALEDIR=\"$(datadir)/locale\" \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	@LIBCERROR_CPPFLAGS@ \
	@LIBCTHREADS_CPPFLAGS@ \
	@LIBCDATA_CPPFLAGS@ \
	@LIBCLOCALE_CPPFLAGS@ \
	@LIBCNOTIFY_CPPFLAGS@ \
	@LIBCSPLIT_CPPFLAGS@ \
	@LIBUNA_CPPFLAGS@ \
	@LIBCDIRECTORY_CPPFLAGS@ \
	@LIBCFILE_CPPFLAGS@ \
	@LIBCPATH_CPPFLAGS@ \
	@LIBBFIO_CPPFLAGS@ \
	@LIBFCACHE_CPPFLAGS@ \
	@LIBFDATA_CPPFLAGS@ \
	@PTHREAD_CPPFLAGS@

lib_LTLIBRARIES = libphdi.la

libphdi_la_SOURCES = \
	libphdi.c \
	libphdi_codepage.h \
	libphdi_debug.c libphdi_debug.h \
	libphdi_definitions.h \
	libphdi_error.c libphdi_error.h \
	libphdi_extern.h \
	libphdi_handle.c libphdi_handle.h \
	libphdi_i18n.c libphdi_i18n.h \
	libphdi_io_handle.c libphdi_io_handle.h \
	libphdi_libbfio.h \
	libphdi_libcdirectory.h \
	libphdi_libcerror.h \
	libphdi_libclocale.h \
	libphdi_libcnotify.h \
	libphdi_libcthreads.h \
	libphdi_libfcache.h \
	libphdi_libfdata.h \
	libphdi_libuna.h \
	libphdi_notify.c libphdi_notify.h \
	libphdi_support.c libphdi_support.h \
	libphdi_types.h \
	libphdi_unused.h \
	phdi_file_footer.h

libphdi_la_LIBADD = \
	@LIBCERROR_LIBADD@ \
	@LIBCTHREADS_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCDIRECTORY_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBBFIO_LIBADD@ \
	@LIBFCACHE_LIBADD@ \
	@LIBFDATA_LIBADD@ \
	@PTHREAD_LIBADD@

libphdi_la_LDFLAGS = -no-undefined -version-info 1:0:0

EXTRA_DIST = \
	libphdi_definitions.h.in \
	libphdi.rc \
	libphdi.rc.in

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f libphdi_definitions.h
	/bin/rm -f libphdi.rc
	/bin/rm -f Makefile

splint:
	@echo "Running splint on libphdi ..."
	-splint -preproc -redef $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(libphdi_la_SOURCES)

