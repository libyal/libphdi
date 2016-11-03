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
	/bin/rm -f libphdi.h
	/bin/rm -f libphdi/definitions.h
	/bin/rm -f libphdi/features.h
	/bin/rm -f libphdi/types.h
	/bin/rm -f Makefile

