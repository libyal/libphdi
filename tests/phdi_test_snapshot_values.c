/*
 * Library snapshot_values type test program
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
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include "phdi_test_libcerror.h"
#include "phdi_test_libphdi.h"
#include "phdi_test_macros.h"
#include "phdi_test_memory.h"
#include "phdi_test_unused.h"

#include "../libphdi/libphdi_snapshot_values.h"

#if defined( __GNUC__ ) && !defined( LIBPHDI_DLL_IMPORT )

/* Tests the libphdi_snapshot_values_initialize function
 * Returns 1 if successful or 0 if not
 */
int phdi_test_snapshot_values_initialize(
     void )
{
	libcerror_error_t *error                   = NULL;
	libphdi_snapshot_values_t *snapshot_values = NULL;
	int result                                 = 0;

#if defined( HAVE_PHDI_TEST_MEMORY )
	int number_of_malloc_fail_tests            = 1;
	int number_of_memset_fail_tests            = 1;
	int test_number                            = 0;
#endif

	/* Test regular cases
	 */
	result = libphdi_snapshot_values_initialize(
	          &snapshot_values,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	PHDI_TEST_ASSERT_IS_NOT_NULL(
	 "snapshot_values",
	 snapshot_values );

	PHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libphdi_snapshot_values_free(
	          &snapshot_values,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	PHDI_TEST_ASSERT_IS_NULL(
	 "snapshot_values",
	 snapshot_values );

	PHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libphdi_snapshot_values_initialize(
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

	snapshot_values = (libphdi_snapshot_values_t *) 0x12345678UL;

	result = libphdi_snapshot_values_initialize(
	          &snapshot_values,
	          &error );

	snapshot_values = NULL;

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
		/* Test libphdi_snapshot_values_initialize with malloc failing
		 */
		phdi_test_malloc_attempts_before_fail = test_number;

		result = libphdi_snapshot_values_initialize(
		          &snapshot_values,
		          &error );

		if( phdi_test_malloc_attempts_before_fail != -1 )
		{
			phdi_test_malloc_attempts_before_fail = -1;

			if( snapshot_values != NULL )
			{
				libphdi_snapshot_values_free(
				 &snapshot_values,
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
			 "snapshot_values",
			 snapshot_values );

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
		/* Test libphdi_snapshot_values_initialize with memset failing
		 */
		phdi_test_memset_attempts_before_fail = test_number;

		result = libphdi_snapshot_values_initialize(
		          &snapshot_values,
		          &error );

		if( phdi_test_memset_attempts_before_fail != -1 )
		{
			phdi_test_memset_attempts_before_fail = -1;

			if( snapshot_values != NULL )
			{
				libphdi_snapshot_values_free(
				 &snapshot_values,
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
			 "snapshot_values",
			 snapshot_values );

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
	if( snapshot_values != NULL )
	{
		libphdi_snapshot_values_free(
		 &snapshot_values,
		 NULL );
	}
	return( 0 );
}

/* Tests the libphdi_snapshot_values_free function
 * Returns 1 if successful or 0 if not
 */
int phdi_test_snapshot_values_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libphdi_snapshot_values_free(
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

/* Tests the libphdi_snapshot_values_get_identifier function
 * Returns 1 if successful or 0 if not
 */
int phdi_test_snapshot_values_get_identifier(
     libphdi_snapshot_values_t *snapshot_values )
{
	uint8_t identifier[ 16 ];

	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test regular cases
	 */
	result = libphdi_snapshot_values_get_identifier(
	          snapshot_values,
	          identifier,
	          16,
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
	result = libphdi_snapshot_values_get_identifier(
	          NULL,
	          identifier,
	          16,
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

	result = libphdi_snapshot_values_get_identifier(
	          snapshot_values,
	          NULL,
	          16,
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

	result = libphdi_snapshot_values_get_identifier(
	          snapshot_values,
	          identifier,
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

	result = libphdi_snapshot_values_get_identifier(
	          snapshot_values,
	          identifier,
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

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
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
#if defined( __GNUC__ ) && !defined( LIBPHDI_DLL_IMPORT )

	libcerror_error_t *error                   = NULL;
	libphdi_snapshot_values_t *snapshot_values = NULL;
	int result                                 = 0;

#endif /* defined( __GNUC__ ) && !defined( LIBPHDI_DLL_IMPORT ) */

	PHDI_TEST_UNREFERENCED_PARAMETER( argc )
	PHDI_TEST_UNREFERENCED_PARAMETER( argv )

#if defined( __GNUC__ ) && !defined( LIBPHDI_DLL_IMPORT )

	PHDI_TEST_RUN(
	 "libphdi_snapshot_values_initialize",
	 phdi_test_snapshot_values_initialize );

	PHDI_TEST_RUN(
	 "libphdi_snapshot_values_free",
	 phdi_test_snapshot_values_free );

	/* TODO add tests for libphdi_snapshot_values_set_identifier */

	/* TODO add tests for libphdi_snapshot_values_set_parent_identifier */

#if !defined( __BORLANDC__ ) || ( __BORLANDC__ >= 0x0560 )

	/* Initialize snapshot_values for tests
	 */
	result = libphdi_snapshot_values_initialize(
	          &snapshot_values,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	PHDI_TEST_ASSERT_IS_NOT_NULL(
	 "snapshot_values",
	 snapshot_values );

	PHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libphdi_snapshot_values_set_identifier(
	          snapshot_values,
	          (uint8_t *) "{5fbaabe3-6958-40ff-92a7-860e329aab41}",
	          38,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	PHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	PHDI_TEST_RUN_WITH_ARGS(
	 "libphdi_snapshot_values_get_identifier",
	 phdi_test_snapshot_values_get_identifier,
	 snapshot_values );

	/* Clean up
	 */
	result = libphdi_snapshot_values_free(
	          &snapshot_values,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	PHDI_TEST_ASSERT_IS_NULL(
	 "snapshot_values",
	 snapshot_values );

	PHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

#endif /* !defined( __BORLANDC__ ) || ( __BORLANDC__ >= 0x0560 ) */
#endif /* defined( __GNUC__ ) && !defined( LIBPHDI_DLL_IMPORT ) */

	return( EXIT_SUCCESS );

#if defined( __GNUC__ ) && !defined( LIBPHDI_DLL_IMPORT )

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( snapshot_values != NULL )
	{
		libphdi_snapshot_values_free(
		 &snapshot_values,
		 NULL );
	}
	return( EXIT_FAILURE );

#endif /* defined( __GNUC__ ) && !defined( LIBPHDI_DLL_IMPORT ) */
}

