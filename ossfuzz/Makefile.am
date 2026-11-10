if HAVE_LIB_FUZZING_ENGINE
AM_CPPFLAGS = \
	-I../include -I$(top_srcdir)/include \
	-I../common -I$(top_srcdir)/common \
	@LIBCERROR_CPPFLAGS@ \
	@LIBCDATA_CPPFLAGS@ \
	@LIBCLOCALE_CPPFLAGS@ \
	@LIBCNOTIFY_CPPFLAGS@ \
	@LIBUNA_CPPFLAGS@ \
	@LIBCFILE_CPPFLAGS@ \
	@LIBCPATH_CPPFLAGS@ \
	@LIBBFIO_CPPFLAGS@

bin_PROGRAMS = \
	extent_fuzzer \
	handle_fuzzer \
	snapshot_fuzzer

extent_fuzzer_SOURCES = \
	extent_fuzzer.cc \
	ossfuzz_libbfio.h \
	ossfuzz_libphdi.h

extent_fuzzer_LDADD = \
	@LIB_FUZZING_ENGINE@ \
	@LIBBFIO_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	../libphdi/libphdi.la \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCERROR_LIBADD@ \
	@LIBINTL@

handle_fuzzer_SOURCES = \
	handle_fuzzer.cc \
	ossfuzz_libbfio.h \
	ossfuzz_libphdi.h

handle_fuzzer_LDADD = \
	@LIB_FUZZING_ENGINE@ \
	@LIBBFIO_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	../libphdi/libphdi.la \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCERROR_LIBADD@ \
	@LIBINTL@

snapshot_fuzzer_SOURCES = \
	snapshot_fuzzer.cc \
	ossfuzz_libbfio.h \
	ossfuzz_libphdi.h

snapshot_fuzzer_LDADD = \
	@LIB_FUZZING_ENGINE@ \
	@LIBBFIO_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	../libphdi/libphdi.la \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCERROR_LIBADD@ \
	@LIBINTL@
endif

DISTCLEANFILES = \
	Makefile \
	Makefile.in

splint-local:
	@echo "Running splint on extent_fuzzer ..."
	-splint -preproc -redef $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(extent_fuzzer_SOURCES)
	@echo "Running splint on handle_fuzzer ..."
	-splint -preproc -redef $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(handle_fuzzer_SOURCES)
	@echo "Running splint on snapshot_fuzzer ..."
	-splint -preproc -redef $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(snapshot_fuzzer_SOURCES)
