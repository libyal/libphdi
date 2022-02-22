# Note that we cannot use: AUTOMAKE_OPTIONS = subdir-objects
# subdir-objects will compile the source files to a single version of Python.
# Since subdir-objects is being deprecated we copy the source files instead.
am__installdirs = "$(DESTDIR)$(pyexecdir2)"
pyexecdir = $(pyexecdir2)

if HAVE_PYTHON2
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
	@LIBBFIO_CPPFLAGS@ \
	@LIBPHDI_DLL_IMPORT@

am_pyphdi_la_rpath = -rpath $(pyexecdir2)

BUILT_SOURCES = \
	pyphdi.c pyphdi.h \
	pyphdi_error.c pyphdi_error.h \
	pyphdi_extent_descriptor.c pyphdi_extent_descriptor.h \
	pyphdi_extent_descriptors.c pyphdi_extent_descriptors.h \
	pyphdi_file_object_io_handle.c pyphdi_file_object_io_handle.h \
	pyphdi_file_objects_io_pool.c pyphdi_file_objects_io_pool.h \
	pyphdi_handle.c pyphdi_handle.h \
	pyphdi_image_descriptor.c pyphdi_image_descriptor.h \
	pyphdi_image_descriptors.c pyphdi_image_descriptors.h \
	pyphdi_integer.c pyphdi_integer.h \
	pyphdi_libbfio.h \
	pyphdi_libcerror.h \
	pyphdi_libclocale.h \
	pyphdi_libphdi.h \
	pyphdi_python.h \
	pyphdi_unused.h

pyexec_LTLIBRARIES = pyphdi.la

nodist_pyphdi_la_SOURCES = $(BUILT_SOURCES)

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

pyphdi_la_CPPFLAGS = $(PYTHON2_CPPFLAGS)
pyphdi_la_LDFLAGS  = -module -avoid-version $(PYTHON2_LDFLAGS)

$(BUILT_SOURCES):
	/bin/cp -f $(top_srcdir)/pyphdi/$@ $@

endif

MAINTAINERCLEANFILES = \
	Makefile.in

clean-local:
	/bin/rm -f pyphdi*.[ch]

distclean: clean
	/bin/rm -f Makefile

