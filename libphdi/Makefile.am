AM_LFLAGS = -Cf
AM_YFLAGS = -d -v -l -p xml_scanner_

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
	@LIBFGUID_CPPFLAGS@ \
	@LIBFVALUE_CPPFLAGS@ \
	@PTHREAD_CPPFLAGS@ \
	@LIBPHDI_DLL_EXPORT@

BUILT_SOURCES = libphdi_xml_parser.h

lib_LTLIBRARIES = libphdi.la

libphdi_la_SOURCES = \
	libphdi.c \
	libphdi_block_descriptor.c libphdi_block_descriptor.h \
	libphdi_block_tree.c libphdi_block_tree.h \
	libphdi_block_tree_node.c libphdi_block_tree_node.h \
	libphdi_codepage.h \
	libphdi_data_files.c libphdi_data_files.h \
	libphdi_debug.c libphdi_debug.h \
	libphdi_definitions.h \
	libphdi_disk_descriptor_xml_file.c libphdi_disk_descriptor_xml_file.h \
	libphdi_disk_parameters.c libphdi_disk_parameters.h \
	libphdi_error.c libphdi_error.h \
	libphdi_extent_descriptor.c libphdi_extent_descriptor.h \
	libphdi_extent_table.c libphdi_extent_table.h \
	libphdi_extent_values.c libphdi_extent_values.h \
	libphdi_extern.h \
	libphdi_handle.c libphdi_handle.h \
	libphdi_i18n.c libphdi_i18n.h \
	libphdi_image_descriptor.c libphdi_image_descriptor.h \
	libphdi_image_values.c libphdi_image_values.h \
	libphdi_io_handle.c libphdi_io_handle.h \
	libphdi_libbfio.h \
	libphdi_libcdata.h \
	libphdi_libcdirectory.h \
	libphdi_libcerror.h \
	libphdi_libclocale.h \
	libphdi_libcnotify.h \
	libphdi_libcpath.h \
	libphdi_libcthreads.h \
	libphdi_libfcache.h \
	libphdi_libfdata.h \
	libphdi_libfguid.h \
	libphdi_libfvalue.h \
	libphdi_libuna.h \
	libphdi_notify.c libphdi_notify.h \
	libphdi_snapshot.c libphdi_snapshot.h \
	libphdi_snapshot_values.c libphdi_snapshot_values.h \
	libphdi_sparse_image_header.c libphdi_sparse_image_header.h \
	libphdi_storage_image.c libphdi_storage_image.h \
	libphdi_support.c libphdi_support.h \
	libphdi_system_string.c libphdi_system_string.h \
	libphdi_types.h \
	libphdi_uuid_string.c libphdi_uuid_string.h \
	libphdi_unused.h \
	libphdi_xml_attribute.c libphdi_xml_attribute.h \
	libphdi_xml_parser.y \
	libphdi_xml_scanner.l \
	libphdi_xml_tag.c libphdi_xml_tag.h \
	phdi_sparse_image_header.h

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
	@LIBFGUID_LIBADD@ \
	@LIBFVALUE_LIBADD@ \
	@PTHREAD_LIBADD@

libphdi_la_LDFLAGS = -no-undefined -version-info 1:0:0

EXTRA_DIST = \
	libphdi_definitions.h.in \
	libphdi_xml_parser.c libphdi_xml_parser.h \
	libphdi_xml_scanner.c \
	libphdi.rc \
	libphdi.rc.in

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f libphdi_definitions.h
	/bin/rm -f libphdi.rc
	/bin/rm -f libphdi_xml_parser.c
	/bin/rm -f libphdi_xml_parser.h
	/bin/rm -f libphdi_xml_parser.output
	/bin/rm -f libphdi_xml_scanner.c
	/bin/rm -f Makefile

splint:
	@echo "Running splint on libphdi ..."
	-splint -preproc -redef $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(libphdi_la_SOURCES)

