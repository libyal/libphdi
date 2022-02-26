AUTOMAKE_OPTIONS = subdir-objects

AM_CPPFLAGS = \
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
	@PTHREAD_CPPFLAGS@ \
	@LIBPHDI_DLL_IMPORT@

if HAVE_PYTHON_TESTS
TESTS_PYPHDI = \
	test_python_module.sh
endif

TESTS = \
	test_library.sh \
	test_phdiinfo.sh \
	$(TESTS_PYPHDI)

check_SCRIPTS = \
	pyphdi_test_handle.py \
	pyphdi_test_support.py \
	test_library.sh \
	test_manpage.sh \
	test_phdiinfo.sh \
	test_python_module.sh \
	test_runner.sh

EXTRA_DIST = \
	$(check_SCRIPTS)

check_PROGRAMS = \
	phdi_test_block_descriptor \
	phdi_test_block_tree \
	phdi_test_block_tree_node \
	phdi_test_error \
	phdi_test_data_files \
	phdi_test_disk_descriptor_xml_file \
	phdi_test_disk_parameters \
	phdi_test_extent_descriptor \
	phdi_test_extent_table \
	phdi_test_extent_values \
	phdi_test_handle \
	phdi_test_image_descriptor \
	phdi_test_image_values \
	phdi_test_io_handle \
	phdi_test_notify \
	phdi_test_snapshot_values \
	phdi_test_support \
	phdi_test_system_string \
	phdi_test_xml_tag

phdi_test_block_descriptor_SOURCES = \
	phdi_test_block_descriptor.c \
	phdi_test_libcerror.h \
	phdi_test_libphdi.h \
	phdi_test_macros.h \
	phdi_test_memory.c phdi_test_memory.h \
	phdi_test_unused.h

phdi_test_block_descriptor_LDADD = \
	../libphdi/libphdi.la \
	@LIBCERROR_LIBADD@

phdi_test_block_tree_SOURCES = \
	phdi_test_block_tree.c \
	phdi_test_libcerror.h \
	phdi_test_libphdi.h \
	phdi_test_macros.h \
	phdi_test_memory.c phdi_test_memory.h \
	phdi_test_unused.h

phdi_test_block_tree_LDADD = \
	../libphdi/libphdi.la \
	@LIBCERROR_LIBADD@

phdi_test_block_tree_node_SOURCES = \
	phdi_test_block_tree_node.c \
	phdi_test_libcerror.h \
	phdi_test_libphdi.h \
	phdi_test_macros.h \
	phdi_test_memory.c phdi_test_memory.h \
	phdi_test_unused.h

phdi_test_block_tree_node_LDADD = \
	../libphdi/libphdi.la \
	@LIBCERROR_LIBADD@

phdi_test_data_files_SOURCES = \
	phdi_test_data_files.c \
	phdi_test_libcerror.h \
	phdi_test_libcpath.h \
	phdi_test_libphdi.h \
	phdi_test_macros.h \
	phdi_test_memory.c phdi_test_memory.h \
	phdi_test_unused.h

phdi_test_data_files_LDADD = \
	../libphdi/libphdi.la \
	@LIBCERROR_LIBADD@

phdi_test_disk_descriptor_xml_file_SOURCES = \
	phdi_test_disk_descriptor_xml_file.c \
	phdi_test_functions.c phdi_test_functions.h \
	phdi_test_libbfio.h \
	phdi_test_libcdata.h \
	phdi_test_libcerror.h \
	phdi_test_libphdi.h \
	phdi_test_macros.h \
	phdi_test_memory.c phdi_test_memory.h \
	phdi_test_unused.h

phdi_test_disk_descriptor_xml_file_LDADD = \
	@LIBBFIO_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	../libphdi/libphdi.la \
	@LIBCERROR_LIBADD@

phdi_test_disk_parameters_SOURCES = \
	phdi_test_disk_parameters.c \
	phdi_test_libcerror.h \
	phdi_test_libphdi.h \
	phdi_test_macros.h \
	phdi_test_memory.c phdi_test_memory.h \
	phdi_test_unused.h

phdi_test_disk_parameters_LDADD = \
	../libphdi/libphdi.la \
	@LIBCERROR_LIBADD@

phdi_test_error_SOURCES = \
	phdi_test_error.c \
	phdi_test_libphdi.h \
	phdi_test_macros.h \
	phdi_test_unused.h

phdi_test_error_LDADD = \
	../libphdi/libphdi.la

phdi_test_extent_descriptor_SOURCES = \
	phdi_test_extent_descriptor.c \
	phdi_test_libcerror.h \
	phdi_test_libphdi.h \
	phdi_test_macros.h \
	phdi_test_memory.c phdi_test_memory.h \
	phdi_test_unused.h

phdi_test_extent_descriptor_LDADD = \
	../libphdi/libphdi.la \
	@LIBCERROR_LIBADD@

phdi_test_extent_table_SOURCES = \
	phdi_test_extent_table.c \
	phdi_test_libcerror.h \
	phdi_test_libcpath.h \
	phdi_test_libphdi.h \
	phdi_test_macros.h \
	phdi_test_memory.c phdi_test_memory.h \
	phdi_test_unused.h

phdi_test_extent_table_LDADD = \
	../libphdi/libphdi.la \
	@LIBCERROR_LIBADD@

phdi_test_extent_values_SOURCES = \
	phdi_test_extent_values.c \
	phdi_test_libcerror.h \
	phdi_test_libphdi.h \
	phdi_test_macros.h \
	phdi_test_memory.c phdi_test_memory.h \
	phdi_test_unused.h

phdi_test_extent_values_LDADD = \
	../libphdi/libphdi.la \
	@LIBCERROR_LIBADD@

phdi_test_handle_SOURCES = \
	phdi_test_functions.c phdi_test_functions.h \
	phdi_test_getopt.c phdi_test_getopt.h \
	phdi_test_handle.c \
	phdi_test_libbfio.h \
	phdi_test_libcerror.h \
	phdi_test_libclocale.h \
	phdi_test_libcnotify.h \
	phdi_test_libphdi.h \
	phdi_test_libuna.h \
	phdi_test_macros.h \
	phdi_test_memory.c phdi_test_memory.h \
	phdi_test_unused.h

phdi_test_handle_LDADD = \
	@LIBBFIO_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	../libphdi/libphdi.la \
	@LIBCTHREADS_LIBADD@ \
	@LIBCERROR_LIBADD@ \
	@PTHREAD_LIBADD@

phdi_test_image_descriptor_SOURCES = \
	phdi_test_image_descriptor.c \
	phdi_test_libcerror.h \
	phdi_test_libphdi.h \
	phdi_test_macros.h \
	phdi_test_memory.c phdi_test_memory.h \
	phdi_test_unused.h

phdi_test_image_descriptor_LDADD = \
	../libphdi/libphdi.la \
	@LIBCERROR_LIBADD@

phdi_test_image_values_SOURCES = \
	phdi_test_image_values.c \
	phdi_test_libcerror.h \
	phdi_test_libphdi.h \
	phdi_test_macros.h \
	phdi_test_memory.c phdi_test_memory.h \
	phdi_test_unused.h

phdi_test_image_values_LDADD = \
	../libphdi/libphdi.la \
	@LIBCERROR_LIBADD@

phdi_test_io_handle_SOURCES = \
	phdi_test_io_handle.c \
	phdi_test_libcerror.h \
	phdi_test_libphdi.h \
	phdi_test_macros.h \
	phdi_test_memory.c phdi_test_memory.h \
	phdi_test_unused.h

phdi_test_io_handle_LDADD = \
	../libphdi/libphdi.la \
	@LIBCERROR_LIBADD@

phdi_test_notify_SOURCES = \
	phdi_test_libcerror.h \
	phdi_test_libphdi.h \
	phdi_test_macros.h \
	phdi_test_notify.c \
	phdi_test_unused.h

phdi_test_notify_LDADD = \
	../libphdi/libphdi.la \
	@LIBCERROR_LIBADD@

phdi_test_snapshot_values_SOURCES = \
	phdi_test_libcerror.h \
	phdi_test_libphdi.h \
	phdi_test_macros.h \
	phdi_test_memory.c phdi_test_memory.h \
	phdi_test_snapshot_values.c \
	phdi_test_unused.h

phdi_test_snapshot_values_LDADD = \
	../libphdi/libphdi.la \
	@LIBCERROR_LIBADD@

phdi_test_support_SOURCES = \
	phdi_test_functions.c phdi_test_functions.h \
	phdi_test_getopt.c phdi_test_getopt.h \
	phdi_test_libbfio.h \
	phdi_test_libcerror.h \
	phdi_test_libclocale.h \
	phdi_test_libcnotify.h \
	phdi_test_libphdi.h \
	phdi_test_libuna.h \
	phdi_test_macros.h \
	phdi_test_memory.c phdi_test_memory.h \
	phdi_test_support.c \
	phdi_test_unused.h

phdi_test_support_LDADD = \
	@LIBBFIO_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	../libphdi/libphdi.la \
	@LIBCERROR_LIBADD@

phdi_test_system_string_SOURCES = \
	phdi_test_libcerror.h \
	phdi_test_libphdi.h \
	phdi_test_macros.h \
	phdi_test_system_string.c \
	phdi_test_unused.h

phdi_test_system_string_LDADD = \
	../libphdi/libphdi.la \
	@LIBCERROR_LIBADD@

phdi_test_xml_tag_SOURCES = \
	phdi_test_libcerror.h \
	phdi_test_libphdi.h \
	phdi_test_macros.h \
	phdi_test_memory.c phdi_test_memory.h \
	phdi_test_unused.h \
	phdi_test_xml_tag.c

phdi_test_xml_tag_LDADD = \
	../libphdi/libphdi.la \
	@LIBCERROR_LIBADD@

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f Makefile

