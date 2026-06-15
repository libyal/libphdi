#!/bin/sh
# Script to run tests
#
# Version: 20260609

if test -f ${PWD}/libphdi/.libs/libphdi.1.dylib && test -f ./pyphdi/.libs/pyphdi.so
then
	install_name_tool -change /usr/local/lib/libphdi.1.dylib ${PWD}/libphdi/.libs/libphdi.1.dylib ./pyphdi/.libs/pyphdi.so
fi

make check-build > /dev/null

make check $@
RESULT=$?

if test ${RESULT} -ne 0
then
	find . -name \*.log -path \*.dir/\*/\*.log -print -exec cat {} \;
fi
exit ${RESULT}

