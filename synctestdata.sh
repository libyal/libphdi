#!/bin/sh
# Script that synchronizes the local test data
#
# Version: 20251217

REPOSITORY="log2timeline/dfvfs";
TEST_DATA_PATH="test_data/hfsplus.hdd";
TEST_SET="public";
TEST_INPUT_DIRECTORY="tests/input";
TEST_FILES="DiskDescriptor.xml hfsplus.hdd hfsplus.hdd.0.{5fbaabe3-6958-40ff-92a7-860e329aab41}.hds";

mkdir -p "${TEST_INPUT_DIRECTORY}/${TEST_SET}";

for TEST_FILE in ${TEST_FILES};
do
	mkdir -p "${TEST_INPUT_DIRECTORY}/${TEST_SET}/hfsplus.hdd";

	URL="https://raw.githubusercontent.com/${REPOSITORY}/refs/heads/main/${TEST_DATA_PATH}/${TEST_FILE}";

	# URL escape the { and } characters in the name of a test file.
	URL=`echo ${URL} | sed 's/{/%7B/g;s/}/%7D/g'`;

	curl -L -o "${TEST_INPUT_DIRECTORY}/${TEST_SET}/hfsplus.hdd/${TEST_FILE}" ${URL};
done

mkdir -p "${TEST_INPUT_DIRECTORY}/.libphdi/${TEST_SET}";
echo "hfsplus.hdd/DiskDescriptor.xml" > "${TEST_INPUT_DIRECTORY}/.libphdi/${TEST_SET}/files";

mkdir -p "${TEST_INPUT_DIRECTORY}/.pyphdi/${TEST_SET}";
echo "hfsplus.hdd/DiskDescriptor.xml" > "${TEST_INPUT_DIRECTORY}/.pyphdi/${TEST_SET}/files";

mkdir -p "${TEST_INPUT_DIRECTORY}/.phditools/${TEST_SET}";
echo "hfsplus.hdd/DiskDescriptor.xml" > "${TEST_INPUT_DIRECTORY}/.pyphdi/${TEST_SET}/files";

