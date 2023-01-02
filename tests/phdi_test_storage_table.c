/*
 * Library storage_table type test program
 *
 * Copyright (C) 2015-2023, Joachim Metz <joachim.metz@gmail.com>
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

#include "phdi_test_libcerror.h"
#include "phdi_test_libphdi.h"
#include "phdi_test_macros.h"
#include "phdi_test_memory.h"
#include "phdi_test_unused.h"

#include "../libphdi/libphdi_storage_table.h"

#if defined( __GNUC__ ) && !defined( LIBPHDI_DLL_IMPORT )

/* Tests the libphdi_storage_table_initialize function
 * Returns 1 if successful or 0 if not
 */
int phdi_test_storage_table_initialize(
     void )
{
	libcerror_error_t *error               = NULL;
	libphdi_storage_table_t *storage_table = NULL;
	int result                             = 0;

#if defined( HAVE_PHDI_TEST_MEMORY )
	int number_of_malloc_fail_tests        = 1;
	int number_of_memset_fail_tests        = 1;
	int test_number                        = 0;
#endif

	/* Test regular cases
	 */
	result = libphdi_storage_table_initialize(
	          &storage_table,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	PHDI_TEST_ASSERT_IS_NOT_NULL(
	 "storage_table",
	 storage_table );

	PHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libphdi_storage_table_free(
	          &storage_table,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	PHDI_TEST_ASSERT_IS_NULL(
	 "storage_table",
	 storage_table );

	PHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libphdi_storage_table_initialize(
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

	storage_table = (libphdi_storage_table_t *) 0x12345678UL;

	result = libphdi_storage_table_initialize(
	          &storage_table,
	          &error );

	storage_table = NULL;

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
		/* Test libphdi_storage_table_initialize with malloc failing
		 */
		phdi_test_malloc_attempts_before_fail = test_number;

		result = libphdi_storage_table_initialize(
		          &storage_table,
		          &error );

		if( phdi_test_malloc_attempts_before_fail != -1 )
		{
			phdi_test_malloc_attempts_before_fail = -1;

			if( storage_table != NULL )
			{
				libphdi_storage_table_free(
				 &storage_table,
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
			 "storage_table",
			 storage_table );

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
		/* Test libphdi_storage_table_initialize with memset failing
		 */
		phdi_test_memset_attempts_before_fail = test_number;

		result = libphdi_storage_table_initialize(
		          &storage_table,
		          &error );

		if( phdi_test_memset_attempts_before_fail != -1 )
		{
			phdi_test_memset_attempts_before_fail = -1;

			if( storage_table != NULL )
			{
				libphdi_storage_table_free(
				 &storage_table,
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
			 "storage_table",
			 storage_table );

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
	if( storage_table != NULL )
	{
		libphdi_storage_table_free(
		 &storage_table,
		 NULL );
	}
	return( 0 );
}

/* Tests the libphdi_storage_table_free function
 * Returns 1 if successful or 0 if not
 */
int phdi_test_storage_table_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libphdi_storage_table_free(
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

/* Tests the libphdi_storage_table_clear function
 * Returns 1 if successful or 0 if not
 */
int phdi_test_storage_table_clear(
     void )
{
	libcerror_error_t *error               = NULL;
	libphdi_storage_table_t *storage_table = NULL;
	int result                             = 0;

	/* Initialize test
	 */
	result = libphdi_storage_table_initialize(
	          &storage_table,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	PHDI_TEST_ASSERT_IS_NOT_NULL(
	 "storage_table",
	 storage_table );

	PHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libphdi_storage_table_clear(
	          storage_table,
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
	result = libphdi_storage_table_clear(
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

	/* Test libphdi_storage_table_clear with memset failing
	 */
	phdi_test_memset_attempts_before_fail = 0;

	result = libphdi_storage_table_clear(
	          storage_table,
	          &error );

	if( phdi_test_memset_attempts_before_fail != -1 )
	{
		phdi_test_memset_attempts_before_fail = -1;
	}
	else
	{
		PHDI_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		PHDI_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
#endif /* defined( HAVE_PHDI_TEST_MEMORY ) */

	/* Clean up
	 */
	result = libphdi_storage_table_free(
	          &storage_table,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	PHDI_TEST_ASSERT_IS_NULL(
	 "storage_table",
	 storage_table );

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
	if( storage_table != NULL )
	{
		libphdi_storage_table_free(
		 &storage_table,
		 NULL );
	}
	return( 0 );
}

/* Tests the libphdi_storage_table_get_basename_size function
 * Returns 1 if successful or 0 if not
 */
int phdi_test_storage_table_get_basename_size(
     void )
{
	libcerror_error_t *error               = NULL;
	libphdi_storage_table_t *storage_table = NULL;
	size_t basename_size                   = 0;
	int basename_size_is_set               = 0;
	int result                             = 0;

	/* Initialize test
	 */
	result = libphdi_storage_table_initialize(
	          &storage_table,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	PHDI_TEST_ASSERT_IS_NOT_NULL(
	 "storage_table",
	 storage_table );

	PHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libphdi_storage_table_get_basename_size(
	          storage_table,
	          &basename_size,
	          &error );

	PHDI_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	PHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	basename_size_is_set = result;

	/* Test error cases
	 */
	result = libphdi_storage_table_get_basename_size(
	          NULL,
	          &basename_size,
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

	if( basename_size_is_set != 0 )
	{
		result = libphdi_storage_table_get_basename_size(
		          storage_table,
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
	}
	/* Clean up
	 */
	result = libphdi_storage_table_free(
	          &storage_table,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	PHDI_TEST_ASSERT_IS_NULL(
	 "storage_table",
	 storage_table );

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
	if( storage_table != NULL )
	{
		libphdi_storage_table_free(
		 &storage_table,
		 NULL );
	}
	return( 0 );
}

/* Tests the libphdi_storage_table_get_basename_size_wide function
 * Returns 1 if successful or 0 if not
 */
int phdi_test_storage_table_get_basename_size_wide(
     void )
{
	libcerror_error_t *error               = NULL;
	libphdi_storage_table_t *storage_table = NULL;
	size_t basename_size_wide              = 0;
	int basename_size_wide_is_set          = 0;
	int result                             = 0;

	/* Initialize test
	 */
	result = libphdi_storage_table_initialize(
	          &storage_table,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	PHDI_TEST_ASSERT_IS_NOT_NULL(
	 "storage_table",
	 storage_table );

	PHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libphdi_storage_table_get_basename_size_wide(
	          storage_table,
	          &basename_size_wide,
	          &error );

	PHDI_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	PHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	basename_size_wide_is_set = result;

	/* Test error cases
	 */
	result = libphdi_storage_table_get_basename_size_wide(
	          NULL,
	          &basename_size_wide,
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

	if( basename_size_wide_is_set != 0 )
	{
		result = libphdi_storage_table_get_basename_size_wide(
		          storage_table,
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
	}
	/* Clean up
	 */
	result = libphdi_storage_table_free(
	          &storage_table,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	PHDI_TEST_ASSERT_IS_NULL(
	 "storage_table",
	 storage_table );

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
	if( storage_table != NULL )
	{
		libphdi_storage_table_free(
		 &storage_table,
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
	 "libphdi_storage_table_initialize",
	 phdi_test_storage_table_initialize );

	PHDI_TEST_RUN(
	 "libphdi_storage_table_free",
	 phdi_test_storage_table_free );

	PHDI_TEST_RUN(
	 "libphdi_storage_table_clear",
	 phdi_test_storage_table_clear );

	PHDI_TEST_RUN(
	 "libphdi_storage_table_get_basename_size",
	 phdi_test_storage_table_get_basename_size );

	/* TODO: add tests for libphdi_storage_table_get_basename */

	/* TODO: add tests for libphdi_storage_table_set_basename */

#if defined( HAVE_WIDE_CHARACTER_TYPE )

	PHDI_TEST_RUN(
	 "libphdi_storage_table_get_basename_size_wide",
	 phdi_test_storage_table_get_basename_size_wide );

	/* TODO: add tests for libphdi_storage_table_get_basename_wide */

	/* TODO: add tests for libphdi_storage_table_set_basename_wide */

#endif /* defined( __GNUC__ ) && !defined( LIBPHDI_DLL_IMPORT ) */

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}

