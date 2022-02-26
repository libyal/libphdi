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
#include "../libphdi/libphdi_image_values.h"
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
	int result                           = 0;

#if defined( HAVE_PHDI_TEST_MEMORY )
	int number_of_malloc_fail_tests      = 1;
	int number_of_memset_fail_tests      = 1;
	int test_number                      = 0;
#endif

	/* Test regular cases
	 */
	result = libphdi_extent_table_initialize(
	          &extent_table,
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
	int result                           = 0;

	/* Initialize test
	 */
	result = libphdi_extent_table_initialize(
	          &extent_table,
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
	 "libphdi_extent_table_initialize",
	 phdi_test_extent_table_initialize );

	PHDI_TEST_RUN(
	 "libphdi_extent_table_free",
	 phdi_test_extent_table_free );

	PHDI_TEST_RUN(
	 "libphdi_extent_table_clear",
	 phdi_test_extent_table_clear );

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

