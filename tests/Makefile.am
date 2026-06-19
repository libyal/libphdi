AUTOMAKE_OPTIONS = subdir-objects

AM_CPPFLAGS = \
	-I../include -I$(top_srcdir)/include \
	-I../common -I$(top_srcdir)/common \
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

BUILT_SOURCES = package.m4

check_AUTOTESTS = \
	test_library \
	test_manpages \
	test_tools

if HAVE_PYTHON_TESTS
check_AUTOTESTS += test_python_module
endif

check_SCRIPTS = \
	pyphdi_test_handle.py \
	pyphdi_test_support.py

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
	@LIBCDATA_LIBADD@ \
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

AUTOM4TE = autom4te
AUTOTEST = $(AUTOM4TE) --language=autotest

SUFFIXES = .at

.at:
	$(AM_V_GEN)rm -f $@ $@.tmp; \
	$(AUTOTEST) -I '$(srcdir)' -o $@.tmp $< && \
	mv $@.tmp $@

atconfig: $(top_builddir)/config.status
	cd $(top_builddir) && $(SHELL) ./config.status tests/$@

check-build: $(check_PROGRAMS)

check-local: $(check_AUTOTESTS)
	@fail=0; \
	for test_suite in $(check_AUTOTESTS); do \
		$(AM_TESTS_ENVIRONMENT) $(SHELL) "./$$test_suite" $(TESTSUITEFLAGS) || fail=1; \
		echo ""; \
	done; \
	exit $$fail

clean-local:
	for test_suite in $(check_AUTOTESTS); do \
		test ! -f "$$test_suite" || $(SHELL) "./$$test_suite" --clean; \
	done

package.m4: $(top_srcdir)/configure.ac
	$(AM_V_GEN):; \
	{ \
	  echo 'm4_define([AT_PACKAGE_NAME], [$(PACKAGE_NAME)])' ; \
	  echo 'm4_define([AT_PACKAGE_TARNAME], [$(PACKAGE_TARNAME)])' ; \
	  echo 'm4_define([AT_PACKAGE_VERSION], [$(PACKAGE_VERSION)])' ; \
	  echo 'm4_define([AT_PACKAGE_STRING], [$(PACKAGE_STRING)])' ; \
	  echo 'm4_define([AT_PACKAGE_BUGREPORT], [$(PACKAGE_BUGREPORT)])' ; \
	} > $@

test_inputs_libphdi.at: generate_test_inputs.sh
	$(SHELL) $(srcdir)/generate_test_inputs.sh $(PACKAGE_NAME) libphdi

test_inputs_pyphdi.at: generate_test_inputs.sh
	$(SHELL) $(srcdir)/generate_test_inputs.sh $(PACKAGE_NAME) pyphdi

test_inputs_phdiinfo.at: generate_test_inputs.sh
	$(SHELL) $(srcdir)/generate_test_inputs.sh $(PACKAGE_NAME) phdiinfo

test_library: \
	package.m4 \
	test_inputs_libphdi.at \
	test_library.at \
	test_macros.at

test_manpages: \
	package.m4 \
	test_manpages.at

test_python_module: \
	package.m4 \
	test_inputs_pyphdi.at \
	test_python_module.at

test_tools: \
	package.m4 \
	test_inputs_phdiinfo.at \
	test_macros.at \
	test_tools.at

EXTRA_DIST = \
	$(check_AUTOTESTS:=.at) \
	$(check_SCRIPTS) \
	generate_test_inputs.sh \
	package.m4 \
	test_macros.at

CLEANFILES = \
	$(check_AUTOTESTS) \
	*.exe \
	*.tmp \
	notify_stream.log \
	test_inputs_*.at

DISTCLEANFILES = \
	*.log \
	atconfig \
	Makefile \
	Makefile.in

