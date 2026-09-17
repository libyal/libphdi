#!/bin/sh
# Script to run tests
#
# Version: 20260714

if [ -f "${PWD}/libphdi/.libs/libphdi.1.dylib" ] && [ -f ./pyphdi/.libs/pyphdi.so ]
then
    install_name_tool -change /usr/local/lib/libphdi.1.dylib "${PWD}/libphdi/.libs/libphdi.1.dylib" ./pyphdi/.libs/pyphdi.so
fi

make check-build > /dev/null

# shellcheck disable=SC2068
make check $@
RESULT=$?

if [ ${RESULT} -ne 0 ]
then
    find . -name \*.log -path \*.dir/\*/\*.log -print -exec cat {} \;
fi
exit ${RESULT}

