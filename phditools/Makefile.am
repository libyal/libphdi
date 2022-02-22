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
	@LIBFGUID_CPPFLAGS@ \
	@LIBFUSE_CPPFLAGS@ \
	@LIBPHDI_DLL_IMPORT@

AM_LDFLAGS = @STATIC_LDFLAGS@

bin_PROGRAMS = \
	phdiinfo \
	phdimount

phdiinfo_SOURCES = \
	byte_size_string.c byte_size_string.h \
	info_handle.c info_handle.h \
	phdiinfo.c \
	phditools_getopt.c phditools_getopt.h \
	phditools_i18n.h \
	phditools_libbfio.h \
	phditools_libcdata.h \
	phditools_libcerror.h \
	phditools_libclocale.h \
	phditools_libcnotify.h \
	phditools_libcpath.h \
	phditools_libfguid.h \
	phditools_libphdi.h \
	phditools_libuna.h \
	phditools_output.c phditools_output.h \
	phditools_signal.c phditools_signal.h \
	phditools_unused.h

phdiinfo_LDADD = \
	@LIBFGUID_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	../libphdi/libphdi.la \
	@LIBCERROR_LIBADD@ \
	@LIBINTL@

phdimount_SOURCES = \
	mount_dokan.c mount_dokan.h \
	mount_file_entry.c mount_file_entry.h \
	mount_file_system.c mount_file_system.h \
	mount_fuse.c mount_fuse.h \
	mount_handle.c mount_handle.h \
	phdimount.c \
	phditools_getopt.c phditools_getopt.h \
	phditools_i18n.h \
	phditools_libbfio.h \
	phditools_libcdata.h \
	phditools_libcerror.h \
	phditools_libclocale.h \
	phditools_libcnotify.h \
	phditools_libcpath.h \
	phditools_libphdi.h \
	phditools_libuna.h \
	phditools_output.c phditools_output.h \
	phditools_signal.c phditools_signal.h \
	phditools_unused.h

phdimount_LDADD = \
	@LIBFUSE_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	../libphdi/libphdi.la \
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

