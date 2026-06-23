#!/bin/sh
# Script that synchronizes the local test data

TESTS_INPUT_DIRECTORY="tests/input"
TEST_SET="public"
TEST_FILES="DiskDescriptor.xml hfsplus.hdd hfsplus.hdd.0.{5fbaabe3-6958-40ff-92a7-860e329aab41}.hds"

mkdir -p "${TESTS_INPUT_DIRECTORY}/${TEST_SET}"

for TEST_FILE in ${TEST_FILES}
do
	mkdir -p "${TESTS_INPUT_DIRECTORY}/${TEST_SET}/hfsplus.hdd"

	# URL escape the { and } characters in the name of a test file.
	URL_TEST_FILE=`echo ${TEST_FILE} | sed 's/{/%7B/g;s/}/%7D/g'`

	URL="https://raw.githubusercontent.com/log2timeline/dfvfs/refs/heads/main/test_data/hfsplus.hdd/${URL_TEST_FILE}"

	curl -L -o "${TESTS_INPUT_DIRECTORY}/${TEST_SET}/hfsplus.hdd/${TEST_FILE}" ${URL}
done

mkdir -p "${TESTS_INPUT_DIRECTORY}/.libphdi/${TEST_SET}"
echo "hfsplus.hdd/DiskDescriptor.xml" > "${TESTS_INPUT_DIRECTORY}/.libphdi/${TEST_SET}/files"

mkdir -p "${TESTS_INPUT_DIRECTORY}/.pyphdi/${TEST_SET}"
echo "hfsplus.hdd/DiskDescriptor.xml" > "${TESTS_INPUT_DIRECTORY}/.pyphdi/${TEST_SET}/files"

mkdir -p "${TESTS_INPUT_DIRECTORY}/.phdiinfo/${TEST_SET}"
echo "hfsplus.hdd/DiskDescriptor.xml" > "${TESTS_INPUT_DIRECTORY}/.phdiinfo/${TEST_SET}/files"
