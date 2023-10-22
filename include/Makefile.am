include_HEADERS = \
	libphdi.h

pkginclude_HEADERS = \
	libphdi/codepage.h \
	libphdi/definitions.h \
	libphdi/error.h \
	libphdi/extern.h \
	libphdi/features.h \
	libphdi/types.h

EXTRA_DIST = \
	libphdi.h.in \
	libphdi/definitions.h.in \
	libphdi/features.h.in \
	libphdi/types.h.in

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	-rm -f libphdi.h
	-rm -f libphdi/definitions.h
	-rm -f libphdi/features.h
	-rm -f libphdi/types.h
	-rm -f Makefile

