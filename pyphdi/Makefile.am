if HAVE_PYTHON
AM_CFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	@LIBCERROR_CPPFLAGS@ \
	@LIBCDATA_CPPFLAGS@ \
	@LIBCLOCALE_CPPFLAGS@ \
	@LIBCSPLIT_CPPFLAGS@ \
	@LIBUNA_CPPFLAGS@ \
	@LIBCFILE_CPPFLAGS@ \
	@LIBCPATH_CPPFLAGS@ \
	@LIBBFIO_CPPFLAGS@

pyexec_LTLIBRARIES = pyphdi.la

pyphdi_la_SOURCES = \
	pyphdi.c pyphdi.h \
	pyphdi_disk_types.c pyphdi_disk_types.h \
	pyphdi_error.c pyphdi_error.h \
	pyphdi_file.c pyphdi_file.h \
	pyphdi_file_object_io_handle.c pyphdi_file_object_io_handle.h \
	pyphdi_integer.c pyphdi_integer.h \
	pyphdi_libbfio.h \
	pyphdi_libcerror.h \
	pyphdi_libclocale.h \
	pyphdi_libphdi.h \
	pyphdi_python.h \
	pyphdi_unused.h

pyphdi_la_LIBADD = \
	@LIBCERROR_LIBADD@ \
	../libphdi/libphdi.la \
	@LIBCDATA_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBBFIO_LIBADD@

pyphdi_la_CPPFLAGS = $(PYTHON_CPPFLAGS)
pyphdi_la_LDFLAGS  = -module -avoid-version $(PYTHON_LDFLAGS)

endif

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f Makefile

