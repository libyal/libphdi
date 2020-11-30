#!/bin/sh
# Script to run tests
#
# Version: 20201121

if test -f ${PWD}/libphdi/.libs/libphdi.1.dylib && test -f ./pyphdi/.libs/pyphdi.so;
then
	install_name_tool -change /usr/local/lib/libphdi.1.dylib ${PWD}/libphdi/.libs/libphdi.1.dylib ./pyphdi/.libs/pyphdi.so;
fi

make check CHECK_WITH_STDERR=1;
RESULT=$?;

if test ${RESULT} -ne 0 && test -f tests/test-suite.log;
then
	cat tests/test-suite.log;
fi
exit ${RESULT};

