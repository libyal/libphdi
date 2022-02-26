/*
 * Library data_files type test program
 *
 * Copyright (C) 2015-2022, Joachim Metz <joachim.metz@gmail.com>
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
#include <memory.h>
#include <narrow_string.h>
#include <types.h>
#include <wide_string.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include "phdi_test_libcerror.h"
#include "phdi_test_libcpath.h"
#include "phdi_test_libphdi.h"
#include "phdi_test_macros.h"
#include "phdi_test_memory.h"
#include "phdi_test_unused.h"

#include "../libphdi/libphdi_data_files.h"
#include "../libphdi/libphdi_image_values.h"

#if defined( __GNUC__ ) && !defined( LIBPHDI_DLL_IMPORT )

/* Tests the libphdi_data_files_initialize function
 * Returns 1 if successful or 0 if not
 */
int phdi_test_data_files_initialize(
     void )
{
	libcerror_error_t *error         = NULL;
	libphdi_data_files_t *data_files = NULL;
	int result                       = 0;

#if defined( HAVE_PHDI_TEST_MEMORY )
	int number_of_malloc_fail_tests  = 1;
	int number_of_memset_fail_tests  = 1;
	int test_number                  = 0;
#endif

	/* Test regular cases
	 */
	result = libphdi_data_files_initialize(
	          &data_files,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	PHDI_TEST_ASSERT_IS_NOT_NULL(
	 "data_files",
	 data_files );

	PHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libphdi_data_files_free(
	          &data_files,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	PHDI_TEST_ASSERT_IS_NULL(
	 "data_files",
	 data_files );

	PHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libphdi_data_files_initialize(
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

	data_files = (libphdi_data_files_t *) 0x12345678UL;

	result = libphdi_data_files_initialize(
	          &data_files,
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

	data_files = NULL;

#if defined( HAVE_PHDI_TEST_MEMORY )

	for( test_number = 0;
	     test_number < number_of_malloc_fail_tests;
	     test_number++ )
	{
		/* Test libphdi_data_files_initialize with malloc failing
		 */
		phdi_test_malloc_attempts_before_fail = test_number;

		result = libphdi_data_files_initialize(
		          &data_files,
		          &error );

		if( phdi_test_malloc_attempts_before_fail != -1 )
		{
			phdi_test_malloc_attempts_before_fail = -1;

			if( data_files != NULL )
			{
				libphdi_data_files_free(
				 &data_files,
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
			 "data_files",
			 data_files );

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
		/* Test libphdi_data_files_initialize with memset failing
		 */
		phdi_test_memset_attempts_before_fail = test_number;

		result = libphdi_data_files_initialize(
		          &data_files,
		          &error );

		if( phdi_test_memset_attempts_before_fail != -1 )
		{
			phdi_test_memset_attempts_before_fail = -1;

			if( data_files != NULL )
			{
				libphdi_data_files_free(
				 &data_files,
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
			 "data_files",
			 data_files );

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
	if( data_files != NULL )
	{
		libphdi_data_files_free(
		 &data_files,
		 NULL );
	}
	return( 0 );
}

/* Tests the libphdi_data_files_free function
 * Returns 1 if successful or 0 if not
 */
int phdi_test_data_files_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libphdi_data_files_free(
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

/* Tests the libphdi_data_files_clear function
 * Returns 1 if successful or 0 if not
 */
int phdi_test_data_files_clear(
     void )
{
	libcerror_error_t *error         = NULL;
	libphdi_data_files_t *data_files = NULL;
	int result                       = 0;

	/* Initialize test
	 */
	result = libphdi_data_files_initialize(
	          &data_files,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	PHDI_TEST_ASSERT_IS_NOT_NULL(
	 "data_files",
	 data_files );

	PHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libphdi_data_files_clear(
	          data_files,
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
	result = libphdi_data_files_clear(
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

	/* Clean up
	 */
	result = libphdi_data_files_free(
	          &data_files,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	PHDI_TEST_ASSERT_IS_NULL(
	 "data_files",
	 data_files );

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
	if( data_files != NULL )
	{
		libphdi_data_files_free(
		 &data_files,
		 NULL );
	}
	return( 0 );
}

/* Tests the libphdi_data_files_get_path_size function
 * Returns 1 if successful or 0 if not
 */
int phdi_test_data_files_get_path_size(
     void )
{
	libcerror_error_t *error         = NULL;
	libphdi_data_files_t *data_files = NULL;
	size_t path_size                 = 0;
	int result                       = 0;

	/* Initialize test
	 */
	result = libphdi_data_files_initialize(
	          &data_files,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	PHDI_TEST_ASSERT_IS_NOT_NULL(
	 "data_files",
	 data_files );

	PHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libphdi_data_files_set_path(
	          data_files,
	          "test",
	          4,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	PHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libphdi_data_files_get_path_size(
	          data_files,
	          &path_size,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	PHDI_TEST_ASSERT_EQUAL_SIZE(
	 "path_size",
	 path_size,
	 (size_t) 5 );

	PHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	path_size = 0;

	result = libphdi_data_files_get_path_size(
	          NULL,
	          &path_size,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	PHDI_TEST_ASSERT_EQUAL_SIZE(
	 "path_size",
	 path_size,
	 (size_t) 0 );

	PHDI_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libphdi_data_files_get_path_size(
	          data_files,
	          NULL,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	PHDI_TEST_ASSERT_EQUAL_SIZE(
	 "path_size",
	 path_size,
	 (size_t) 0 );

	PHDI_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Clean up
	 */
	result = libphdi_data_files_free(
	          &data_files,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	PHDI_TEST_ASSERT_IS_NULL(
	 "data_files",
	 data_files );

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
	if( data_files != NULL )
	{
		libphdi_data_files_free(
		 &data_files,
		 NULL );
	}
	return( 0 );
}

/* Tests the libphdi_data_files_get_path function
 * Returns 1 if successful or 0 if not
 */
int phdi_test_data_files_get_path(
     void )
{
	char path[ 32 ];

	libcerror_error_t *error         = NULL;
	libphdi_data_files_t *data_files = NULL;
	int result                       = 0;

	/* Initialize test
	 */
	result = libphdi_data_files_initialize(
	          &data_files,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	PHDI_TEST_ASSERT_IS_NOT_NULL(
	 "data_files",
	 data_files );

	PHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libphdi_data_files_set_path(
	          data_files,
	          "test",
	          4,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	PHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libphdi_data_files_get_path(
	          data_files,
	          path,
	          32,
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
	result = libphdi_data_files_get_path(
	          NULL,
	          path,
	          32,
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

	result = libphdi_data_files_get_path(
	          data_files,
	          NULL,
	          32,
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

	result = libphdi_data_files_get_path(
	          data_files,
	          path,
	          0,
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

	result = libphdi_data_files_get_path(
	          data_files,
	          path,
	          (size_t) SSIZE_MAX + 1,
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

	/* Clean up
	 */
	result = libphdi_data_files_free(
	          &data_files,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	PHDI_TEST_ASSERT_IS_NULL(
	 "data_files",
	 data_files );

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
	if( data_files != NULL )
	{
		libphdi_data_files_free(
		 &data_files,
		 NULL );
	}
	return( 0 );
}

#if defined( HAVE_WIDE_CHARACTER_TYPE )

/* Tests the libphdi_data_files_get_path_size_wide function
 * Returns 1 if successful or 0 if not
 */
int phdi_test_data_files_get_path_size_wide(
     void )
{
	libcerror_error_t *error         = NULL;
	libphdi_data_files_t *data_files = NULL;
	size_t path_size                 = 0;
	int result                       = 0;

	/* Initialize test
	 */
	result = libphdi_data_files_initialize(
	          &data_files,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	PHDI_TEST_ASSERT_IS_NOT_NULL(
	 "data_files",
	 data_files );

	PHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libphdi_data_files_set_path(
	          data_files,
	          "test",
	          4,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	PHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libphdi_data_files_get_path_size_wide(
	          data_files,
	          &path_size,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	PHDI_TEST_ASSERT_EQUAL_SIZE(
	 "path_size",
	 path_size,
	 (size_t) 5 );

	PHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	path_size = 0;

	result = libphdi_data_files_get_path_size_wide(
	          NULL,
	          &path_size,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	PHDI_TEST_ASSERT_EQUAL_SIZE(
	 "path_size",
	 path_size,
	 (size_t) 0 );

	PHDI_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libphdi_data_files_get_path_size_wide(
	          data_files,
	          NULL,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	PHDI_TEST_ASSERT_EQUAL_SIZE(
	 "path_size",
	 path_size,
	 (size_t) 0 );

	PHDI_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Clean up
	 */
	result = libphdi_data_files_free(
	          &data_files,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	PHDI_TEST_ASSERT_IS_NULL(
	 "data_files",
	 data_files );

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
	if( data_files != NULL )
	{
		libphdi_data_files_free(
		 &data_files,
		 NULL );
	}
	return( 0 );
}

/* Tests the libphdi_data_files_get_path_wide function
 * Returns 1 if successful or 0 if not
 */
int phdi_test_data_files_get_path_wide(
     void )
{
	wchar_t path[ 32 ];

	libcerror_error_t *error         = NULL;
	libphdi_data_files_t *data_files = NULL;
	int result                       = 0;

	/* Initialize test
	 */
	result = libphdi_data_files_initialize(
	          &data_files,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	PHDI_TEST_ASSERT_IS_NOT_NULL(
	 "data_files",
	 data_files );

	PHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libphdi_data_files_set_path_wide(
	          data_files,
	          L"test",
	          4,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	PHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libphdi_data_files_get_path_wide(
	          data_files,
	          path,
	          32,
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
	result = libphdi_data_files_get_path_wide(
	          NULL,
	          path,
	          32,
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

	result = libphdi_data_files_get_path_wide(
	          data_files,
	          NULL,
	          32,
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

	result = libphdi_data_files_get_path_wide(
	          data_files,
	          path,
	          0,
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

	result = libphdi_data_files_get_path_wide(
	          data_files,
	          path,
	          (size_t) SSIZE_MAX + 1,
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

	/* Clean up
	 */
	result = libphdi_data_files_free(
	          &data_files,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	PHDI_TEST_ASSERT_IS_NULL(
	 "data_files",
	 data_files );

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
	if( data_files != NULL )
	{
		libphdi_data_files_free(
		 &data_files,
		 NULL );
	}
	return( 0 );
}

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

/* Tests the libphdi_data_files_get_extent_data_file_path function
 * Returns 1 if successful or 0 if not
 */
int phdi_test_data_files_get_extent_data_file_path(
     void )
{
	libcerror_error_t *error             = NULL;
	libphdi_data_files_t *data_files     = NULL;
	libphdi_image_values_t *image_values = NULL;
	const char *expected_path            = NULL;
	char *path                           = NULL;
	size_t path_size                     = 0;
	int result                           = 0;

	/* Initialize test
	 */
	result = libphdi_data_files_initialize(
	          &data_files,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	PHDI_TEST_ASSERT_IS_NOT_NULL(
	 "data_files",
	 data_files );

	PHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libphdi_image_values_initialize(
	          &image_values,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	PHDI_TEST_ASSERT_IS_NOT_NULL(
	 "image_values",
	 image_values );

	PHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libphdi_image_values_set_filename(
	          image_values,
	          (uint8_t *) "filename.hdd",
	          12,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	PHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases - extent values name without extent table data files path
	 */
	result = libphdi_data_files_get_extent_data_file_path(
	          data_files,
	          image_values,
	          &path,
	          &path_size,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	PHDI_TEST_ASSERT_IS_NOT_NULL(
	 "path",
	 path );

	PHDI_TEST_ASSERT_EQUAL_SIZE(
	 "path_size",
	 path_size,
	 (size_t) 13 );

	PHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = narrow_string_compare(
	          path,
	          "filename.hdd",
	          12 );

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	memory_free(
	 path );

	path = NULL;

	result = libphdi_data_files_set_path(
	          data_files,
	          "test",
	          4,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	PHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases - extent values name with extent table data files path
	 */
	path_size = 0;

	result = libphdi_data_files_get_extent_data_file_path(
	          data_files,
	          image_values,
	          &path,
	          &path_size,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	PHDI_TEST_ASSERT_IS_NOT_NULL(
	 "path",
	 path );

	PHDI_TEST_ASSERT_EQUAL_SIZE(
	 "path_size",
	 path_size,
	 (size_t) 18 );

	PHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

#if defined( WINAPI )
	expected_path = "test\\filename.hdd";
#else
	expected_path = "test/filename.hdd";
#endif
	result = narrow_string_compare(
	          path,
	          expected_path,
	          17 );

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	memory_free(
	 path );

	path = NULL;

	/* Test error cases
	 */
	path_size = 0;

	result = libphdi_data_files_get_extent_data_file_path(
	          NULL,
	          image_values,
	          &path,
	          &path_size,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	PHDI_TEST_ASSERT_IS_NULL(
	 "path",
	 path );

	PHDI_TEST_ASSERT_EQUAL_SIZE(
	 "path_size",
	 path_size,
	 (size_t) 0 );

	PHDI_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libphdi_data_files_get_extent_data_file_path(
	          data_files,
	          NULL,
	          &path,
	          &path_size,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	PHDI_TEST_ASSERT_IS_NULL(
	 "path",
	 path );

	PHDI_TEST_ASSERT_EQUAL_SIZE(
	 "path_size",
	 path_size,
	 (size_t) 0 );

	PHDI_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libphdi_data_files_get_extent_data_file_path(
	          data_files,
	          image_values,
	          NULL,
	          &path_size,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	PHDI_TEST_ASSERT_IS_NULL(
	 "path",
	 path );

	PHDI_TEST_ASSERT_EQUAL_SIZE(
	 "path_size",
	 path_size,
	 (size_t) 0 );

	PHDI_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libphdi_data_files_get_extent_data_file_path(
	          data_files,
	          image_values,
	          &path,
	          NULL,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	PHDI_TEST_ASSERT_IS_NULL(
	 "path",
	 path );

	PHDI_TEST_ASSERT_EQUAL_SIZE(
	 "path_size",
	 path_size,
	 (size_t) 0 );

	PHDI_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Clean up
	 */
	result = libphdi_image_values_free(
	          &image_values,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	PHDI_TEST_ASSERT_IS_NULL(
	 "image_values",
	 image_values );

	PHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libphdi_data_files_free(
	          &data_files,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	PHDI_TEST_ASSERT_IS_NULL(
	 "data_files",
	 data_files );

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
	if( image_values != NULL )
	{
		libphdi_image_values_free(
		 &image_values,
		 NULL );
	}
	if( data_files != NULL )
	{
		libphdi_data_files_free(
		 &data_files,
		 NULL );
	}
	return( 0 );
}

#if defined( HAVE_WIDE_CHARACTER_TYPE )

/* Tests the libphdi_data_files_get_extent_data_file_path_wide function
 * Returns 1 if successful or 0 if not
 */
int phdi_test_data_files_get_extent_data_file_path_wide(
     void )
{
	libcerror_error_t *error             = NULL;
	libphdi_data_files_t *data_files     = NULL;
	libphdi_image_values_t *image_values = NULL;
	const wchar_t *expected_path         = NULL;
	wchar_t *path                        = NULL;
	size_t path_size                     = 0;
	int result                           = 0;

	/* Initialize test
	 */
	result = libphdi_data_files_initialize(
	          &data_files,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	PHDI_TEST_ASSERT_IS_NOT_NULL(
	 "data_files",
	 data_files );

	PHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libphdi_image_values_initialize(
	          &image_values,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	PHDI_TEST_ASSERT_IS_NOT_NULL(
	 "image_values",
	 image_values );

	PHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libphdi_image_values_set_filename(
	          image_values,
	          (uint8_t *) "filename.hdd",
	          12,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	PHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases - extent values name without extent table data files path
	 */
	result = libphdi_data_files_get_extent_data_file_path_wide(
	          data_files,
	          image_values,
	          &path,
	          &path_size,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	PHDI_TEST_ASSERT_IS_NOT_NULL(
	 "path",
	 path );

	PHDI_TEST_ASSERT_EQUAL_SIZE(
	 "path_size",
	 path_size,
	 (size_t) 13 );

	PHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = wide_string_compare(
	          path,
	          L"filename.hdd",
	          12 );

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	memory_free(
	 path );

	path = NULL;

	result = libphdi_data_files_set_path_wide(
	          data_files,
	          L"test",
	          4,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	PHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	path_size = 0;

	/* Test regular cases - extent values name with extent table data files path
	 */
	result = libphdi_data_files_get_extent_data_file_path_wide(
	          data_files,
	          image_values,
	          &path,
	          &path_size,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	PHDI_TEST_ASSERT_IS_NOT_NULL(
	 "path",
	 path );

	PHDI_TEST_ASSERT_EQUAL_SIZE(
	 "path_size",
	 path_size,
	 (size_t) 18 );

	PHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

#if defined( WINAPI )
	expected_path = L"test\\filename.hdd";
#else
	expected_path = L"test/filename.hdd";
#endif

	result = wide_string_compare(
	          path,
	          expected_path,
	          17 );

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	memory_free(
	 path );

	path = NULL;

	/* Test error cases
	 */
	path_size = 0;

	result = libphdi_data_files_get_extent_data_file_path_wide(
	          NULL,
	          image_values,
	          &path,
	          &path_size,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	PHDI_TEST_ASSERT_IS_NULL(
	 "path",
	 path );

	PHDI_TEST_ASSERT_EQUAL_SIZE(
	 "path_size",
	 path_size,
	 (size_t) 0 );

	PHDI_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libphdi_data_files_get_extent_data_file_path_wide(
	          data_files,
	          NULL,
	          &path,
	          &path_size,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	PHDI_TEST_ASSERT_IS_NULL(
	 "path",
	 path );

	PHDI_TEST_ASSERT_EQUAL_SIZE(
	 "path_size",
	 path_size,
	 (size_t) 0 );

	PHDI_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libphdi_data_files_get_extent_data_file_path_wide(
	          data_files,
	          image_values,
	          NULL,
	          &path_size,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	PHDI_TEST_ASSERT_IS_NULL(
	 "path",
	 path );

	PHDI_TEST_ASSERT_EQUAL_SIZE(
	 "path_size",
	 path_size,
	 (size_t) 0 );

	PHDI_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libphdi_data_files_get_extent_data_file_path_wide(
	          data_files,
	          image_values,
	          &path,
	          NULL,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	PHDI_TEST_ASSERT_IS_NULL(
	 "path",
	 path );

	PHDI_TEST_ASSERT_EQUAL_SIZE(
	 "path_size",
	 path_size,
	 (size_t) 0 );

	PHDI_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Clean up
	 */
	result = libphdi_image_values_free(
	          &image_values,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	PHDI_TEST_ASSERT_IS_NULL(
	 "image_values",
	 image_values );

	PHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libphdi_data_files_free(
	          &data_files,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	PHDI_TEST_ASSERT_IS_NULL(
	 "data_files",
	 data_files );

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
	if( image_values != NULL )
	{
		libphdi_image_values_free(
		 &image_values,
		 NULL );
	}
	if( data_files != NULL )
	{
		libphdi_data_files_free(
		 &data_files,
		 NULL );
	}
	return( 0 );
}

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

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
	 "libphdi_data_files_initialize",
	 phdi_test_data_files_initialize );

	PHDI_TEST_RUN(
	 "libphdi_data_files_free",
	 phdi_test_data_files_free );

	PHDI_TEST_RUN(
	 "libphdi_data_files_clear",
	 phdi_test_data_files_clear );

	PHDI_TEST_RUN(
	 "libphdi_data_files_get_path_size",
	 phdi_test_data_files_get_path_size );

	PHDI_TEST_RUN(
	 "libphdi_data_files_get_path",
	 phdi_test_data_files_get_path );

	/* TODO: add tests for libphdi_data_files_set_path */

#if defined( HAVE_WIDE_CHARACTER_TYPE )

	PHDI_TEST_RUN(
	 "libphdi_data_files_get_path_size_wide",
	 phdi_test_data_files_get_path_size_wide );

	PHDI_TEST_RUN(
	 "libphdi_data_files_get_path_wide",
	 phdi_test_data_files_get_path_wide );

	/* TODO: add tests for libphdi_data_files_set_path_wide */

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

	PHDI_TEST_RUN(
	 "libphdi_data_files_get_extent_data_file_path",
	 phdi_test_data_files_get_extent_data_file_path );

#if defined( HAVE_WIDE_CHARACTER_TYPE )

	PHDI_TEST_RUN(
	 "libphdi_data_files_get_extent_data_file_path_wide",
	 phdi_test_data_files_get_extent_data_file_path_wide );

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

#endif /* defined( __GNUC__ ) && !defined( LIBPHDI_DLL_IMPORT ) */

	return( EXIT_SUCCESS );

#if defined( __GNUC__ ) && !defined( LIBPHDI_DLL_IMPORT )

on_error:
	return( EXIT_FAILURE );

#endif /* defined( __GNUC__ ) && !defined( LIBPHDI_DLL_IMPORT ) */
}

