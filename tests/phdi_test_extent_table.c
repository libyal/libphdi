/*
 * Library extent_table type test program
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

#include "../libphdi/libphdi_extent_table.h"
#include "../libphdi/libphdi_extent_values.h"
#include "../libphdi/libphdi_io_handle.h"

#if defined( __GNUC__ ) && !defined( LIBPHDI_DLL_IMPORT )

/* Tests the libphdi_extent_table_initialize function
 * Returns 1 if successful or 0 if not
 */
int phdi_test_extent_table_initialize(
     void )
{
	libcerror_error_t *error             = NULL;
	libphdi_extent_table_t *extent_table = NULL;
	libphdi_io_handle_t *io_handle       = NULL;
	int result                           = 0;

#if defined( HAVE_PHDI_TEST_MEMORY )
	int number_of_malloc_fail_tests      = 1;
	int number_of_memset_fail_tests      = 1;
	int test_number                      = 0;
#endif

	/* Initialize test
	 */
	result = libphdi_io_handle_initialize(
	          &io_handle,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	PHDI_TEST_ASSERT_IS_NOT_NULL(
	 "io_handle",
	 io_handle );

	PHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libphdi_extent_table_initialize(
	          &extent_table,
	          io_handle,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	PHDI_TEST_ASSERT_IS_NOT_NULL(
	 "extent_table",
	 extent_table );

	PHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libphdi_extent_table_free(
	          &extent_table,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	PHDI_TEST_ASSERT_IS_NULL(
	 "extent_table",
	 extent_table );

	PHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libphdi_extent_table_initialize(
	          NULL,
	          io_handle,
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

	extent_table = (libphdi_extent_table_t *) 0x12345678UL;

	result = libphdi_extent_table_initialize(
	          &extent_table,
	          io_handle,
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

	extent_table = NULL;

	result = libphdi_extent_table_initialize(
	          &extent_table,
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

#if defined( HAVE_PHDI_TEST_MEMORY )

	for( test_number = 0;
	     test_number < number_of_malloc_fail_tests;
	     test_number++ )
	{
		/* Test libphdi_extent_table_initialize with malloc failing
		 */
		phdi_test_malloc_attempts_before_fail = test_number;

		result = libphdi_extent_table_initialize(
		          &extent_table,
		          io_handle,
		          &error );

		if( phdi_test_malloc_attempts_before_fail != -1 )
		{
			phdi_test_malloc_attempts_before_fail = -1;

			if( extent_table != NULL )
			{
				libphdi_extent_table_free(
				 &extent_table,
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
			 "extent_table",
			 extent_table );

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
		/* Test libphdi_extent_table_initialize with memset failing
		 */
		phdi_test_memset_attempts_before_fail = test_number;

		result = libphdi_extent_table_initialize(
		          &extent_table,
		          io_handle,
		          &error );

		if( phdi_test_memset_attempts_before_fail != -1 )
		{
			phdi_test_memset_attempts_before_fail = -1;

			if( extent_table != NULL )
			{
				libphdi_extent_table_free(
				 &extent_table,
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
			 "extent_table",
			 extent_table );

			PHDI_TEST_ASSERT_IS_NOT_NULL(
			 "error",
			 error );

			libcerror_error_free(
			 &error );
		}
	}
#endif /* defined( HAVE_PHDI_TEST_MEMORY ) */

	/* Clean up
	 */
	result = libphdi_io_handle_free(
	          &io_handle,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	PHDI_TEST_ASSERT_IS_NULL(
	 "io_handle",
	 io_handle );

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
	if( extent_table != NULL )
	{
		libphdi_extent_table_free(
		 &extent_table,
		 NULL );
	}
	if( io_handle != NULL )
	{
		libphdi_io_handle_free(
		 &io_handle,
		 NULL );
	}
	return( 0 );
}

/* Tests the libphdi_extent_table_free function
 * Returns 1 if successful or 0 if not
 */
int phdi_test_extent_table_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libphdi_extent_table_free(
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

/* Tests the libphdi_extent_table_clear function
 * Returns 1 if successful or 0 if not
 */
int phdi_test_extent_table_clear(
     void )
{
	libcerror_error_t *error             = NULL;
	libphdi_extent_table_t *extent_table = NULL;
	libphdi_io_handle_t *io_handle       = NULL;
	int result                           = 0;

	/* Initialize test
	 */
	result = libphdi_io_handle_initialize(
	          &io_handle,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	PHDI_TEST_ASSERT_IS_NOT_NULL(
	 "io_handle",
	 io_handle );

	PHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libphdi_extent_table_initialize(
	          &extent_table,
	          io_handle,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	PHDI_TEST_ASSERT_IS_NOT_NULL(
	 "extent_table",
	 extent_table );

	PHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libphdi_extent_table_clear(
	          extent_table,
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
	result = libphdi_extent_table_clear(
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
	result = libphdi_extent_table_free(
	          &extent_table,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	PHDI_TEST_ASSERT_IS_NULL(
	 "extent_table",
	 extent_table );

	PHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libphdi_io_handle_free(
	          &io_handle,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	PHDI_TEST_ASSERT_IS_NULL(
	 "io_handle",
	 io_handle );

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
	if( extent_table != NULL )
	{
		libphdi_extent_table_free(
		 &extent_table,
		 NULL );
	}
	if( io_handle != NULL )
	{
		libphdi_io_handle_free(
		 &io_handle,
		 NULL );
	}
	return( 0 );
}

/* Tests the libphdi_extent_table_get_data_files_path_size function
 * Returns 1 if successful or 0 if not
 */
int phdi_test_extent_table_get_data_files_path_size(
     void )
{
	libcerror_error_t *error             = NULL;
	libphdi_extent_table_t *extent_table = NULL;
	libphdi_io_handle_t *io_handle       = NULL;
	size_t path_size                     = 0;
	int result                           = 0;

	/* Initialize test
	 */
	result = libphdi_io_handle_initialize(
	          &io_handle,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	PHDI_TEST_ASSERT_IS_NOT_NULL(
	 "io_handle",
	 io_handle );

	PHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libphdi_extent_table_initialize(
	          &extent_table,
	          io_handle,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	PHDI_TEST_ASSERT_IS_NOT_NULL(
	 "extent_table",
	 extent_table );

	PHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libphdi_extent_table_set_data_files_path(
	          extent_table,
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
	result = libphdi_extent_table_get_data_files_path_size(
	          extent_table,
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

	result = libphdi_extent_table_get_data_files_path_size(
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

	result = libphdi_extent_table_get_data_files_path_size(
	          extent_table,
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
	result = libphdi_extent_table_free(
	          &extent_table,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	PHDI_TEST_ASSERT_IS_NULL(
	 "extent_table",
	 extent_table );

	PHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libphdi_io_handle_free(
	          &io_handle,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	PHDI_TEST_ASSERT_IS_NULL(
	 "io_handle",
	 io_handle );

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
	if( extent_table != NULL )
	{
		libphdi_extent_table_free(
		 &extent_table,
		 NULL );
	}
	if( io_handle != NULL )
	{
		libphdi_io_handle_free(
		 &io_handle,
		 NULL );
	}
	return( 0 );
}

/* Tests the libphdi_extent_table_get_data_files_path function
 * Returns 1 if successful or 0 if not
 */
int phdi_test_extent_table_get_data_files_path(
     void )
{
	char path[ 32 ];

	libcerror_error_t *error             = NULL;
	libphdi_extent_table_t *extent_table = NULL;
	libphdi_io_handle_t *io_handle       = NULL;
	int result                           = 0;

	/* Initialize test
	 */
	result = libphdi_io_handle_initialize(
	          &io_handle,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	PHDI_TEST_ASSERT_IS_NOT_NULL(
	 "io_handle",
	 io_handle );

	PHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libphdi_extent_table_initialize(
	          &extent_table,
	          io_handle,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	PHDI_TEST_ASSERT_IS_NOT_NULL(
	 "extent_table",
	 extent_table );

	PHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libphdi_extent_table_set_data_files_path(
	          extent_table,
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
	result = libphdi_extent_table_get_data_files_path(
	          extent_table,
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
	result = libphdi_extent_table_get_data_files_path(
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

	result = libphdi_extent_table_get_data_files_path(
	          extent_table,
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

	result = libphdi_extent_table_get_data_files_path(
	          extent_table,
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

	result = libphdi_extent_table_get_data_files_path(
	          extent_table,
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
	result = libphdi_extent_table_free(
	          &extent_table,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	PHDI_TEST_ASSERT_IS_NULL(
	 "extent_table",
	 extent_table );

	PHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libphdi_io_handle_free(
	          &io_handle,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	PHDI_TEST_ASSERT_IS_NULL(
	 "io_handle",
	 io_handle );

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
	if( extent_table != NULL )
	{
		libphdi_extent_table_free(
		 &extent_table,
		 NULL );
	}
	if( io_handle != NULL )
	{
		libphdi_io_handle_free(
		 &io_handle,
		 NULL );
	}
	return( 0 );
}

#if defined( HAVE_WIDE_CHARACTER_TYPE )

/* Tests the libphdi_extent_table_get_data_files_path_size_wide function
 * Returns 1 if successful or 0 if not
 */
int phdi_test_extent_table_get_data_files_path_size_wide(
     void )
{
	libcerror_error_t *error             = NULL;
	libphdi_extent_table_t *extent_table = NULL;
	libphdi_io_handle_t *io_handle       = NULL;
	size_t path_size                     = 0;
	int result                           = 0;

	/* Initialize test
	 */
	result = libphdi_io_handle_initialize(
	          &io_handle,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	PHDI_TEST_ASSERT_IS_NOT_NULL(
	 "io_handle",
	 io_handle );

	PHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libphdi_extent_table_initialize(
	          &extent_table,
	          io_handle,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	PHDI_TEST_ASSERT_IS_NOT_NULL(
	 "extent_table",
	 extent_table );

	PHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libphdi_extent_table_set_data_files_path(
	          extent_table,
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
	result = libphdi_extent_table_get_data_files_path_size_wide(
	          extent_table,
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

	result = libphdi_extent_table_get_data_files_path_size_wide(
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

	result = libphdi_extent_table_get_data_files_path_size_wide(
	          extent_table,
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
	result = libphdi_extent_table_free(
	          &extent_table,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	PHDI_TEST_ASSERT_IS_NULL(
	 "extent_table",
	 extent_table );

	PHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libphdi_io_handle_free(
	          &io_handle,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	PHDI_TEST_ASSERT_IS_NULL(
	 "io_handle",
	 io_handle );

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
	if( extent_table != NULL )
	{
		libphdi_extent_table_free(
		 &extent_table,
		 NULL );
	}
	if( io_handle != NULL )
	{
		libphdi_io_handle_free(
		 &io_handle,
		 NULL );
	}
	return( 0 );
}

/* Tests the libphdi_extent_table_get_data_files_path_wide function
 * Returns 1 if successful or 0 if not
 */
int phdi_test_extent_table_get_data_files_path_wide(
     void )
{
	wchar_t path[ 32 ];

	libcerror_error_t *error             = NULL;
	libphdi_extent_table_t *extent_table = NULL;
	libphdi_io_handle_t *io_handle       = NULL;
	int result                           = 0;

	/* Initialize test
	 */
	result = libphdi_io_handle_initialize(
	          &io_handle,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	PHDI_TEST_ASSERT_IS_NOT_NULL(
	 "io_handle",
	 io_handle );

	PHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libphdi_extent_table_initialize(
	          &extent_table,
	          io_handle,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	PHDI_TEST_ASSERT_IS_NOT_NULL(
	 "extent_table",
	 extent_table );

	PHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libphdi_extent_table_set_data_files_path_wide(
	          extent_table,
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
	result = libphdi_extent_table_get_data_files_path_wide(
	          extent_table,
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
	result = libphdi_extent_table_get_data_files_path_wide(
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

	result = libphdi_extent_table_get_data_files_path_wide(
	          extent_table,
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

	result = libphdi_extent_table_get_data_files_path_wide(
	          extent_table,
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

	result = libphdi_extent_table_get_data_files_path_wide(
	          extent_table,
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
	result = libphdi_extent_table_free(
	          &extent_table,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	PHDI_TEST_ASSERT_IS_NULL(
	 "extent_table",
	 extent_table );

	PHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libphdi_io_handle_free(
	          &io_handle,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	PHDI_TEST_ASSERT_IS_NULL(
	 "io_handle",
	 io_handle );

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
	if( extent_table != NULL )
	{
		libphdi_extent_table_free(
		 &extent_table,
		 NULL );
	}
	if( io_handle != NULL )
	{
		libphdi_io_handle_free(
		 &io_handle,
		 NULL );
	}
	return( 0 );
}

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

/* Tests the libphdi_extent_table_get_extent_data_file_path function
 * Returns 1 if successful or 0 if not
 */
int phdi_test_extent_table_get_extent_data_file_path(
     void )
{
	libcerror_error_t *error               = NULL;
	libphdi_extent_table_t *extent_table   = NULL;
	libphdi_extent_values_t *extent_values = NULL;
	libphdi_io_handle_t *io_handle         = NULL;
	const char *expected_path              = NULL;
	char *path                             = NULL;
	size_t path_size                       = 0;
	int result                             = 0;

	/* Initialize test
	 */
	result = libphdi_io_handle_initialize(
	          &io_handle,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	PHDI_TEST_ASSERT_IS_NOT_NULL(
	 "io_handle",
	 io_handle );

	PHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libphdi_extent_table_initialize(
	          &extent_table,
	          io_handle,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	PHDI_TEST_ASSERT_IS_NOT_NULL(
	 "extent_table",
	 extent_table );

	PHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libphdi_extent_values_initialize(
	          &extent_values,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	PHDI_TEST_ASSERT_IS_NOT_NULL(
	 "extent_values",
	 extent_values );

	PHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libphdi_extent_values_set_filename(
	          extent_values,
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
	result = libphdi_extent_table_get_extent_data_file_path(
	          extent_table,
	          extent_values,
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

	result = libphdi_extent_table_set_data_files_path(
	          extent_table,
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

	result = libphdi_extent_table_get_extent_data_file_path(
	          extent_table,
	          extent_values,
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

	result = libphdi_extent_table_get_extent_data_file_path(
	          NULL,
	          extent_values,
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

	result = libphdi_extent_table_get_extent_data_file_path(
	          extent_table,
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

	result = libphdi_extent_table_get_extent_data_file_path(
	          extent_table,
	          extent_values,
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

	result = libphdi_extent_table_get_extent_data_file_path(
	          extent_table,
	          extent_values,
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
	result = libphdi_extent_values_free(
	          &extent_values,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	PHDI_TEST_ASSERT_IS_NULL(
	 "extent_values",
	 extent_values );

	PHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libphdi_extent_table_free(
	          &extent_table,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	PHDI_TEST_ASSERT_IS_NULL(
	 "extent_table",
	 extent_table );

	PHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libphdi_io_handle_free(
	          &io_handle,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	PHDI_TEST_ASSERT_IS_NULL(
	 "io_handle",
	 io_handle );

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
	if( extent_values != NULL )
	{
		libphdi_extent_values_free(
		 &extent_values,
		 NULL );
	}
	if( extent_table != NULL )
	{
		libphdi_extent_table_free(
		 &extent_table,
		 NULL );
	}
	if( io_handle != NULL )
	{
		libphdi_io_handle_free(
		 &io_handle,
		 NULL );
	}
	return( 0 );
}

#if defined( HAVE_WIDE_CHARACTER_TYPE )

/* Tests the libphdi_extent_table_get_extent_data_file_path_wide function
 * Returns 1 if successful or 0 if not
 */
int phdi_test_extent_table_get_extent_data_file_path_wide(
     void )
{
	libcerror_error_t *error               = NULL;
	libphdi_extent_table_t *extent_table   = NULL;
	libphdi_extent_values_t *extent_values = NULL;
	libphdi_io_handle_t *io_handle         = NULL;
	const wchar_t *expected_path           = NULL;
	wchar_t *path                          = NULL;
	size_t path_size                       = 0;
	int result                             = 0;

	/* Initialize test
	 */
	result = libphdi_io_handle_initialize(
	          &io_handle,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	PHDI_TEST_ASSERT_IS_NOT_NULL(
	 "io_handle",
	 io_handle );

	PHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libphdi_extent_table_initialize(
	          &extent_table,
	          io_handle,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	PHDI_TEST_ASSERT_IS_NOT_NULL(
	 "extent_table",
	 extent_table );

	PHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libphdi_extent_values_initialize(
	          &extent_values,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	PHDI_TEST_ASSERT_IS_NOT_NULL(
	 "extent_values",
	 extent_values );

	PHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libphdi_extent_values_set_filename(
	          extent_values,
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
	result = libphdi_extent_table_get_extent_data_file_path_wide(
	          extent_table,
	          extent_values,
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

	result = libphdi_extent_table_set_data_files_path_wide(
	          extent_table,
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
	result = libphdi_extent_table_get_extent_data_file_path_wide(
	          extent_table,
	          extent_values,
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

	result = libphdi_extent_table_get_extent_data_file_path_wide(
	          NULL,
	          extent_values,
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

	result = libphdi_extent_table_get_extent_data_file_path_wide(
	          extent_table,
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

	result = libphdi_extent_table_get_extent_data_file_path_wide(
	          extent_table,
	          extent_values,
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

	result = libphdi_extent_table_get_extent_data_file_path_wide(
	          extent_table,
	          extent_values,
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
	result = libphdi_extent_values_free(
	          &extent_values,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	PHDI_TEST_ASSERT_IS_NULL(
	 "extent_values",
	 extent_values );

	PHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libphdi_extent_table_free(
	          &extent_table,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	PHDI_TEST_ASSERT_IS_NULL(
	 "extent_table",
	 extent_table );

	PHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libphdi_io_handle_free(
	          &io_handle,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	PHDI_TEST_ASSERT_IS_NULL(
	 "io_handle",
	 io_handle );

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
	if( extent_values != NULL )
	{
		libphdi_extent_values_free(
		 &extent_values,
		 NULL );
	}
	if( extent_table != NULL )
	{
		libphdi_extent_table_free(
		 &extent_table,
		 NULL );
	}
	if( io_handle != NULL )
	{
		libphdi_io_handle_free(
		 &io_handle,
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
	 "libphdi_extent_table_initialize",
	 phdi_test_extent_table_initialize );

	PHDI_TEST_RUN(
	 "libphdi_extent_table_free",
	 phdi_test_extent_table_free );

	PHDI_TEST_RUN(
	 "libphdi_extent_table_clear",
	 phdi_test_extent_table_clear );

	PHDI_TEST_RUN(
	 "libphdi_extent_table_get_data_files_path_size",
	 phdi_test_extent_table_get_data_files_path_size );

	PHDI_TEST_RUN(
	 "libphdi_extent_table_get_data_files_path",
	 phdi_test_extent_table_get_data_files_path );

	/* TODO: add tests for libphdi_extent_table_set_data_files_path */

#if defined( HAVE_WIDE_CHARACTER_TYPE )

	PHDI_TEST_RUN(
	 "libphdi_extent_table_get_data_files_path_size_wide",
	 phdi_test_extent_table_get_data_files_path_size_wide );

	PHDI_TEST_RUN(
	 "libphdi_extent_table_get_data_files_path_wide",
	 phdi_test_extent_table_get_data_files_path_wide );

	/* TODO: add tests for libphdi_extent_table_set_data_files_path_wide */

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

	PHDI_TEST_RUN(
	 "libphdi_extent_table_get_extent_data_file_path",
	 phdi_test_extent_table_get_extent_data_file_path );

#if defined( HAVE_WIDE_CHARACTER_TYPE )

	PHDI_TEST_RUN(
	 "libphdi_extent_table_get_extent_data_file_path_wide",
	 phdi_test_extent_table_get_extent_data_file_path_wide );

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

	/* TODO: add tests for libphdi_extent_table_initialize_extents */

	/* TODO: add tests for libphdi_extent_table_set_extent_storage_media_size_by_index */

	/* TODO: add tests for libphdi_extent_table_get_extent_file_at_offset */

	/* TODO: add tests for libphdi_extent_table_set_extent_by_extent_values */

#endif /* defined( __GNUC__ ) && !defined( LIBPHDI_DLL_IMPORT ) */

	return( EXIT_SUCCESS );

#if defined( __GNUC__ ) && !defined( LIBPHDI_DLL_IMPORT )

on_error:
	return( EXIT_FAILURE );

#endif /* defined( __GNUC__ ) && !defined( LIBPHDI_DLL_IMPORT ) */
}
