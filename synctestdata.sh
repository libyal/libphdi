#!/bin/sh
# Script that synchronizes the local test data
#
# Version: 20161009

TEST_SET="public";
TEST_INPUT_DIRECTORY="tests/input";
TEST_FILES="DiskDescriptor.xml hfsplus.hdd hfsplus.hdd.0.{5fbaabe3-6958-40ff-92a7-860e329aab41}.hds";

mkdir -p "${TEST_INPUT_DIRECTORY}/${TEST_SET}";

for TEST_FILE in ${TEST_FILES};
do
	mkdir -p "${TEST_INPUT_DIRECTORY}/${TEST_SET}/hfsplus.hdd";

	URL="https://github.com/log2timeline/dfvfs/blob/main/test_data/hfsplus.hdd/${TEST_FILE}?raw=true";

	# URL escape the { and } characters in the name of a test file.
	URL=`echo ${URL} | sed 's/{/%7B/g;s/}/%7D/g'`;

	curl -L -o "${TEST_INPUT_DIRECTORY}/${TEST_SET}/hfsplus.hdd/${TEST_FILE}" ${URL};
done

mkdir -p "${TEST_INPUT_DIRECTORY}/.libphdi/${TEST_SET}";
echo "hfsplus.hdd/DiskDescriptor.xml" > "${TEST_INPUT_DIRECTORY}/.libphdi/${TEST_SET}/files";

mkdir -p "${TEST_INPUT_DIRECTORY}/.pyphdi/${TEST_SET}";
echo "hfsplus.hdd/DiskDescriptor.xml" > "${TEST_INPUT_DIRECTORY}/.pyphdi/${TEST_SET}/files";

