/*
 * Library disk_descriptor_xml_file type test program
 *
 * Copyright (C) 2015-2021, Joachim Metz <joachim.metz@gmail.com>
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <common.h>
#include <file_stream.h>
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include "phdi_test_functions.h"
#include "phdi_test_libbfio.h"
#include "phdi_test_libcerror.h"
#include "phdi_test_libphdi.h"
#include "phdi_test_macros.h"
#include "phdi_test_memory.h"
#include "phdi_test_unused.h"

#include "../libphdi/libphdi_disk_descriptor_xml_file.h"

#if defined( __GNUC__ ) && !defined( LIBPHDI_DLL_IMPORT )

/* Tests the libphdi_disk_descriptor_xml_file_initialize function
 * Returns 1 if successful or 0 if not
 */
int phdi_test_disk_descriptor_xml_file_initialize(
     void )
{
	libcerror_error_t *error                                     = NULL;
	libphdi_disk_descriptor_xml_file_t *disk_descriptor_xml_file = NULL;
	int result                                                   = 0;

#if defined( HAVE_PHDI_TEST_MEMORY )
	int number_of_malloc_fail_tests                              = 1;
	int number_of_memset_fail_tests                              = 1;
	int test_number                                              = 0;
#endif

	/* Test regular cases
	 */
	result = libphdi_disk_descriptor_xml_file_initialize(
	          &disk_descriptor_xml_file,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	PHDI_TEST_ASSERT_IS_NOT_NULL(
	 "disk_descriptor_xml_file",
	 disk_descriptor_xml_file );

	PHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libphdi_disk_descriptor_xml_file_free(
	          &disk_descriptor_xml_file,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	PHDI_TEST_ASSERT_IS_NULL(
	 "disk_descriptor_xml_file",
	 disk_descriptor_xml_file );

	PHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libphdi_disk_descriptor_xml_file_initialize(
	          NULL,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	PHDI_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	disk_descriptor_xml_file = (libphdi_disk_descriptor_xml_file_t *) 0x12345678UL;

	result = libphdi_disk_descriptor_xml_file_initialize(
	          &disk_descriptor_xml_file,
	          &error );

	disk_descriptor_xml_file = NULL;

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	PHDI_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

#if defined( HAVE_PHDI_TEST_MEMORY )

	for( test_number = 0;
	     test_number < number_of_malloc_fail_tests;
	     test_number++ )
	{
		/* Test libphdi_disk_descriptor_xml_file_initialize with malloc failing
		 */
		phdi_test_malloc_attempts_before_fail = test_number;

		result = libphdi_disk_descriptor_xml_file_initialize(
		          &disk_descriptor_xml_file,
		          &error );

		if( phdi_test_malloc_attempts_before_fail != -1 )
		{
			phdi_test_malloc_attempts_before_fail = -1;

			if( disk_descriptor_xml_file != NULL )
			{
				libphdi_disk_descriptor_xml_file_free(
				 &disk_descriptor_xml_file,
				 NULL );
			}
		}
		else
		{
			PHDI_TEST_ASSERT_EQUAL_INT(
			 "result",
			 result,
			 -1 );

			PHDI_TEST_ASSERT_IS_NULL(
			 "disk_descriptor_xml_file",
			 disk_descriptor_xml_file );

			PHDI_TEST_ASSERT_IS_NOT_NULL(
			 "error",
			 error );

			libcerror_error_free(
			 &error );
		}
	}
	for( test_number = 0;
	     test_number < number_of_memset_fail_tests;
	     test_number++ )
	{
		/* Test libphdi_disk_descriptor_xml_file_initialize with memset failing
		 */
		phdi_test_memset_attempts_before_fail = test_number;

		result = libphdi_disk_descriptor_xml_file_initialize(
		          &disk_descriptor_xml_file,
		          &error );

		if( phdi_test_memset_attempts_before_fail != -1 )
		{
			phdi_test_memset_attempts_before_fail = -1;

			if( disk_descriptor_xml_file != NULL )
			{
				libphdi_disk_descriptor_xml_file_free(
				 &disk_descriptor_xml_file,
				 NULL );
			}
		}
		else
		{
			PHDI_TEST_ASSERT_EQUAL_INT(
			 "result",
			 result,
			 -1 );

			PHDI_TEST_ASSERT_IS_NULL(
			 "disk_descriptor_xml_file",
			 disk_descriptor_xml_file );

			PHDI_TEST_ASSERT_IS_NOT_NULL(
			 "error",
			 error );

			libcerror_error_free(
			 &error );
		}
	}
#endif /* defined( HAVE_PHDI_TEST_MEMORY ) */

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( disk_descriptor_xml_file != NULL )
	{
		libphdi_disk_descriptor_xml_file_free(
		 &disk_descriptor_xml_file,
		 NULL );
	}
	return( 0 );
}

/* Tests the libphdi_disk_descriptor_xml_file_free function
 * Returns 1 if successful or 0 if not
 */
int phdi_test_disk_descriptor_xml_file_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libphdi_disk_descriptor_xml_file_free(
	          NULL,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	PHDI_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libphdi_disk_descriptor_xml_file_get_disk_parameters function
 * Returns 1 if successful or 0 if not
 */
int phdi_test_disk_descriptor_xml_file_get_disk_parameters(
     void )
{
	libcerror_error_t *error                                     = NULL;
	libphdi_disk_descriptor_xml_file_t *disk_descriptor_xml_file = NULL;
	libphdi_disk_parameters_t *disk_parameters                   = NULL;
	int result                                                   = 0;

	/* Initialize test
	 */
	result = libphdi_disk_descriptor_xml_file_initialize(
	          &disk_descriptor_xml_file,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	PHDI_TEST_ASSERT_IS_NOT_NULL(
	 "disk_descriptor_xml_file",
	 disk_descriptor_xml_file );

	PHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libphdi_disk_descriptor_xml_file_get_disk_parameters(
	          disk_descriptor_xml_file,
	          &disk_parameters,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	PHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	PHDI_TEST_ASSERT_IS_NOT_NULL(
	 "disk_parameters",
	 disk_parameters );

	result = libphdi_disk_parameters_free(
	          &disk_parameters,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	PHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libphdi_disk_descriptor_xml_file_get_disk_parameters(
	          NULL,
	          &disk_parameters,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	PHDI_TEST_ASSERT_IS_NULL(
	 "disk_parameters",
	 disk_parameters );

	PHDI_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libphdi_disk_descriptor_xml_file_get_disk_parameters(
	          disk_descriptor_xml_file,
	          NULL,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	PHDI_TEST_ASSERT_IS_NULL(
	 "disk_parameters",
	 disk_parameters );

	PHDI_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Clean up
	 */
	result = libphdi_disk_descriptor_xml_file_free(
	          &disk_descriptor_xml_file,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	PHDI_TEST_ASSERT_IS_NULL(
	 "disk_descriptor_xml_file",
	 disk_descriptor_xml_file );

	PHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( disk_descriptor_xml_file != NULL )
	{
		libphdi_disk_descriptor_xml_file_free(
		 &disk_descriptor_xml_file,
		 NULL );
	}
	return( 0 );
}

/* Tests the libphdi_disk_descriptor_xml_file_get_storage_data function
 * Returns 1 if successful or 0 if not
 */
int phdi_test_disk_descriptor_xml_file_get_storage_data(
     void )
{
	libcerror_error_t *error                                     = NULL;
	libphdi_disk_descriptor_xml_file_t *disk_descriptor_xml_file = NULL;
	libphdi_storage_table_t *storage_data                        = NULL;
	int result                                                   = 0;

	/* Initialize test
	 */
	result = libphdi_disk_descriptor_xml_file_initialize(
	          &disk_descriptor_xml_file,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	PHDI_TEST_ASSERT_IS_NOT_NULL(
	 "disk_descriptor_xml_file",
	 disk_descriptor_xml_file );

	PHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libphdi_disk_descriptor_xml_file_get_storage_data(
	          disk_descriptor_xml_file,
	          &storage_data,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	PHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	PHDI_TEST_ASSERT_IS_NOT_NULL(
	 "storage_data",
	 storage_data );

	result = libphdi_storage_table_free(
	          &storage_data,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	PHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libphdi_disk_descriptor_xml_file_get_storage_data(
	          NULL,
	          &storage_data,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	PHDI_TEST_ASSERT_IS_NULL(
	 "storage_data",
	 storage_data );

	PHDI_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libphdi_disk_descriptor_xml_file_get_storage_data(
	          disk_descriptor_xml_file,
	          NULL,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	PHDI_TEST_ASSERT_IS_NULL(
	 "storage_data",
	 storage_data );

	PHDI_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Clean up
	 */
	result = libphdi_disk_descriptor_xml_file_free(
	          &disk_descriptor_xml_file,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	PHDI_TEST_ASSERT_IS_NULL(
	 "disk_descriptor_xml_file",
	 disk_descriptor_xml_file );

	PHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( disk_descriptor_xml_file != NULL )
	{
		libphdi_disk_descriptor_xml_file_free(
		 &disk_descriptor_xml_file,
		 NULL );
	}
	return( 0 );
}

#endif /* defined( __GNUC__ ) && !defined( LIBPHDI_DLL_IMPORT ) */

/* The main program
 */
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
int wmain(
     int argc PHDI_TEST_ATTRIBUTE_UNUSED,
     wchar_t * const argv[] PHDI_TEST_ATTRIBUTE_UNUSED )
#else
int main(
     int argc PHDI_TEST_ATTRIBUTE_UNUSED,
     char * const argv[] PHDI_TEST_ATTRIBUTE_UNUSED )
#endif
{
	PHDI_TEST_UNREFERENCED_PARAMETER( argc )
	PHDI_TEST_UNREFERENCED_PARAMETER( argv )

#if defined( __GNUC__ ) && !defined( LIBPHDI_DLL_IMPORT )

	PHDI_TEST_RUN(
	 "libphdi_disk_descriptor_xml_file_initialize",
	 phdi_test_disk_descriptor_xml_file_initialize );

	PHDI_TEST_RUN(
	 "libphdi_disk_descriptor_xml_file_free",
	 phdi_test_disk_descriptor_xml_file_free );

	/* TODO: add tests for libphdi_disk_descriptor_xml_file_read_data */

	/* TODO: add tests for libphdi_disk_descriptor_xml_file_read_file_io_handle */

	PHDI_TEST_RUN(
	 "libphdi_disk_descriptor_xml_file_get_disk_parameters",
	 phdi_test_disk_descriptor_xml_file_get_disk_parameters );

	PHDI_TEST_RUN(
	 "libphdi_disk_descriptor_xml_file_get_storage_data",
	 phdi_test_disk_descriptor_xml_file_get_storage_data );

	/* TODO: add tests for libphdi_disk_descriptor_xml_file_get_snapshots */

	/* TODO: add tests for libphdi_disk_descriptor_xml_file_set_root_tag */

#endif /* defined( __GNUC__ ) && !defined( LIBPHDI_DLL_IMPORT ) */

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}

