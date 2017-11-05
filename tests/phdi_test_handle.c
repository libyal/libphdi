/*
 * Library handle type test program
 *
 * Copyright (C) 2015-2017, Joachim Metz <joachim.metz@gmail.com>
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This software is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this software.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <common.h>
#include <file_stream.h>
#include <narrow_string.h>
#include <system_string.h>
#include <types.h>
#include <wide_string.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include "phdi_test_functions.h"
#include "phdi_test_getopt.h"
#include "phdi_test_libbfio.h"
#include "phdi_test_libcerror.h"
#include "phdi_test_libphdi.h"
#include "phdi_test_macros.h"
#include "phdi_test_memory.h"
#include "phdi_test_unused.h"

#include "../libphdi/libphdi_handle.h"

#if !defined( LIBPHDI_HAVE_BFIO )

LIBPHDI_EXTERN \
int libphdi_check_file_signature_file_io_handle(
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error );

LIBPHDI_EXTERN \
int libphdi_handle_open_file_io_handle(
     libphdi_handle_t *handle,
     libbfio_handle_t *file_io_handle,
     int access_flags,
     libphdi_error_t **error );

#endif /* !defined( LIBPHDI_HAVE_BFIO ) */

#if defined( HAVE_WIDE_SYSTEM_CHARACTER ) && SIZEOF_WCHAR_T != 2 && SIZEOF_WCHAR_T != 4
#error Unsupported size of wchar_t
#endif

/* Define to make phdi_test_handle generate verbose output
#define PHDI_TEST_HANDLE_VERBOSE
 */

/* Creates and opens a source handle
 * Returns 1 if successful or -1 on error
 */
int phdi_test_handle_open_source(
     libphdi_handle_t **handle,
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error )
{
	static char *function = "phdi_test_handle_open_source";
	int result            = 0;

	if( handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	if( file_io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file IO handle.",
		 function );

		return( -1 );
	}
	if( libphdi_handle_initialize(
	     handle,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to initialize handle.",
		 function );

		goto on_error;
	}
	result = libphdi_handle_open_file_io_handle(
	          *handle,
	          file_io_handle,
	          LIBPHDI_OPEN_READ,
	          error );

	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_OPEN_FAILED,
		 "%s: unable to open handle.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *handle != NULL )
	{
		libphdi_handle_free(
		 handle,
		 NULL );
	}
	return( -1 );
}

/* Closes and frees a source handle
 * Returns 1 if successful or -1 on error
 */
int phdi_test_handle_close_source(
     libphdi_handle_t **handle,
     libcerror_error_t **error )
{
	static char *function = "phdi_test_handle_close_source";
	int result            = 0;

	if( handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	if( libphdi_handle_close(
	     *handle,
	     error ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_CLOSE_FAILED,
		 "%s: unable to close handle.",
		 function );

		result = -1;
	}
	if( libphdi_handle_free(
	     handle,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to free handle.",
		 function );

		result = -1;
	}
	return( result );
}

/* Tests the libphdi_handle_initialize function
 * Returns 1 if successful or 0 if not
 */
int phdi_test_handle_initialize(
     void )
{
	libcerror_error_t *error        = NULL;
	libphdi_handle_t *handle        = NULL;
	int result                      = 0;

#if defined( HAVE_PHDI_TEST_MEMORY )
	int number_of_malloc_fail_tests = 1;
	int number_of_memset_fail_tests = 1;
	int test_number                 = 0;
#endif

	/* Test regular cases
	 */
	result = libphdi_handle_initialize(
	          &handle,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	PHDI_TEST_ASSERT_IS_NOT_NULL(
	 "handle",
	 handle );

	PHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libphdi_handle_free(
	          &handle,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	PHDI_TEST_ASSERT_IS_NULL(
	 "handle",
	 handle );

	PHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libphdi_handle_initialize(
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

	handle = (libphdi_handle_t *) 0x12345678UL;

	result = libphdi_handle_initialize(
	          &handle,
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

	handle = NULL;

#if defined( HAVE_PHDI_TEST_MEMORY )

	for( test_number = 0;
	     test_number < number_of_malloc_fail_tests;
	     test_number++ )
	{
		/* Test libphdi_handle_initialize with malloc failing
		 */
		phdi_test_malloc_attempts_before_fail = test_number;

		result = libphdi_handle_initialize(
		          &handle,
		          &error );

		if( phdi_test_malloc_attempts_before_fail != -1 )
		{
			phdi_test_malloc_attempts_before_fail = -1;

			if( handle != NULL )
			{
				libphdi_handle_free(
				 &handle,
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
			 "handle",
			 handle );

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
		/* Test libphdi_handle_initialize with memset failing
		 */
		phdi_test_memset_attempts_before_fail = test_number;

		result = libphdi_handle_initialize(
		          &handle,
		          &error );

		if( phdi_test_memset_attempts_before_fail != -1 )
		{
			phdi_test_memset_attempts_before_fail = -1;

			if( handle != NULL )
			{
				libphdi_handle_free(
				 &handle,
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
			 "handle",
			 handle );

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
	if( handle != NULL )
	{
		libphdi_handle_free(
		 &handle,
		 NULL );
	}
	return( 0 );
}

/* Tests the libphdi_handle_free function
 * Returns 1 if successful or 0 if not
 */
int phdi_test_handle_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libphdi_handle_free(
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

/* Tests the libphdi_handle_open function
 * Returns 1 if successful or 0 if not
 */
int phdi_test_handle_open(
     const system_character_t *source )
{
	char narrow_source[ 256 ];

	libcerror_error_t *error = NULL;
	libphdi_handle_t *handle = NULL;
	int result               = 0;

	/* Initialize test
	 */
	result = phdi_test_get_narrow_source(
	          source,
	          narrow_source,
	          256,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	PHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libphdi_handle_initialize(
	          &handle,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	PHDI_TEST_ASSERT_IS_NOT_NULL(
	 "handle",
	 handle );

	PHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test open
	 */
	result = libphdi_handle_open(
	          handle,
	          narrow_source,
	          LIBPHDI_OPEN_READ,
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
	result = libphdi_handle_open(
	          NULL,
	          narrow_source,
	          LIBPHDI_OPEN_READ,
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

	result = libphdi_handle_open(
	          handle,
	          NULL,
	          LIBPHDI_OPEN_READ,
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

	result = libphdi_handle_open(
	          handle,
	          narrow_source,
	          -1,
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

	/* Test open when already opened
	 */
	result = libphdi_handle_open(
	          handle,
	          narrow_source,
	          LIBPHDI_OPEN_READ,
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
	result = libphdi_handle_free(
	          &handle,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	PHDI_TEST_ASSERT_IS_NULL(
	 "handle",
	 handle );

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
	if( handle != NULL )
	{
		libphdi_handle_free(
		 &handle,
		 NULL );
	}
	return( 0 );
}

#if defined( HAVE_WIDE_CHARACTER_TYPE )

/* Tests the libphdi_handle_open_wide function
 * Returns 1 if successful or 0 if not
 */
int phdi_test_handle_open_wide(
     const system_character_t *source )
{
	wchar_t wide_source[ 256 ];

	libcerror_error_t *error = NULL;
	libphdi_handle_t *handle = NULL;
	int result               = 0;

	/* Initialize test
	 */
	result = phdi_test_get_wide_source(
	          source,
	          wide_source,
	          256,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	PHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libphdi_handle_initialize(
	          &handle,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	PHDI_TEST_ASSERT_IS_NOT_NULL(
	 "handle",
	 handle );

	PHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test open
	 */
	result = libphdi_handle_open_wide(
	          handle,
	          wide_source,
	          LIBPHDI_OPEN_READ,
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
	result = libphdi_handle_open_wide(
	          NULL,
	          wide_source,
	          LIBPHDI_OPEN_READ,
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

	result = libphdi_handle_open_wide(
	          handle,
	          NULL,
	          LIBPHDI_OPEN_READ,
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

	result = libphdi_handle_open_wide(
	          handle,
	          wide_source,
	          -1,
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

	/* Test open when already opened
	 */
	result = libphdi_handle_open_wide(
	          handle,
	          wide_source,
	          LIBPHDI_OPEN_READ,
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
	result = libphdi_handle_free(
	          &handle,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	PHDI_TEST_ASSERT_IS_NULL(
	 "handle",
	 handle );

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
	if( handle != NULL )
	{
		libphdi_handle_free(
		 &handle,
		 NULL );
	}
	return( 0 );
}

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

/* Tests the libphdi_handle_open_file_io_handle function
 * Returns 1 if successful or 0 if not
 */
int phdi_test_handle_open_file_io_handle(
     const system_character_t *source )
{
	libbfio_handle_t *file_io_handle = NULL;
	libcerror_error_t *error         = NULL;
	libphdi_handle_t *handle         = NULL;
	size_t string_length             = 0;
	int result                       = 0;

	/* Initialize test
	 */
	result = libbfio_file_initialize(
	          &file_io_handle,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        PHDI_TEST_ASSERT_IS_NOT_NULL(
         "file_io_handle",
         file_io_handle );

        PHDI_TEST_ASSERT_IS_NULL(
         "error",
         error );

	string_length = system_string_length(
	                 source );

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libbfio_file_set_name_wide(
	          file_io_handle,
	          source,
	          string_length,
	          &error );
#else
	result = libbfio_file_set_name(
	          file_io_handle,
	          source,
	          string_length,
	          &error );
#endif
	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        PHDI_TEST_ASSERT_IS_NULL(
         "error",
         error );

	result = libphdi_handle_initialize(
	          &handle,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	PHDI_TEST_ASSERT_IS_NOT_NULL(
	 "handle",
	 handle );

	PHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test open
	 */
	result = libphdi_handle_open_file_io_handle(
	          handle,
	          file_io_handle,
	          LIBPHDI_OPEN_READ,
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
	result = libphdi_handle_open_file_io_handle(
	          NULL,
	          file_io_handle,
	          LIBPHDI_OPEN_READ,
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

	result = libphdi_handle_open_file_io_handle(
	          handle,
	          NULL,
	          LIBPHDI_OPEN_READ,
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

	result = libphdi_handle_open_file_io_handle(
	          handle,
	          file_io_handle,
	          -1,
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

	/* Test open when already opened
	 */
	result = libphdi_handle_open_file_io_handle(
	          handle,
	          file_io_handle,
	          LIBPHDI_OPEN_READ,
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
	result = libphdi_handle_free(
	          &handle,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	PHDI_TEST_ASSERT_IS_NULL(
	 "handle",
	 handle );

	PHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libbfio_handle_free(
	          &file_io_handle,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	PHDI_TEST_ASSERT_IS_NULL(
         "file_io_handle",
         file_io_handle );

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
	if( handle != NULL )
	{
		libphdi_handle_free(
		 &handle,
		 NULL );
	}
	if( file_io_handle != NULL )
	{
		libbfio_handle_free(
		 &file_io_handle,
		 NULL );
	}
	return( 0 );
}

/* Tests the libphdi_handle_close function
 * Returns 1 if successful or 0 if not
 */
int phdi_test_handle_close(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libphdi_handle_close(
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

/* Tests the libphdi_handle_open and libphdi_handle_close functions
 * Returns 1 if successful or 0 if not
 */
int phdi_test_handle_open_close(
     const system_character_t *source )
{
	libcerror_error_t *error = NULL;
	libphdi_handle_t *handle = NULL;
	int result               = 0;

	/* Initialize test
	 */
	result = libphdi_handle_initialize(
	          &handle,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	PHDI_TEST_ASSERT_IS_NOT_NULL(
	 "handle",
	 handle );

	PHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test open and close
	 */
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libphdi_handle_open_wide(
	          handle,
	          source,
	          LIBPHDI_OPEN_READ,
	          &error );
#else
	result = libphdi_handle_open(
	          handle,
	          source,
	          LIBPHDI_OPEN_READ,
	          &error );
#endif

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	PHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libphdi_handle_close(
	          handle,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	PHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test open and close a second time to validate clean up on close
	 */
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libphdi_handle_open_wide(
	          handle,
	          source,
	          LIBPHDI_OPEN_READ,
	          &error );
#else
	result = libphdi_handle_open(
	          handle,
	          source,
	          LIBPHDI_OPEN_READ,
	          &error );
#endif

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	PHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libphdi_handle_close(
	          handle,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	PHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Clean up
	 */
	result = libphdi_handle_free(
	          &handle,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	PHDI_TEST_ASSERT_IS_NULL(
	 "handle",
	 handle );

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
	if( handle != NULL )
	{
		libphdi_handle_free(
		 &handle,
		 NULL );
	}
	return( 0 );
}

/* Tests the libphdi_handle_signal_abort function
 * Returns 1 if successful or 0 if not
 */
int phdi_test_handle_signal_abort(
     libphdi_handle_t *handle )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test regular cases
	 */
	result = libphdi_handle_signal_abort(
	          handle,
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
	result = libphdi_handle_signal_abort(
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

/* Tests the libphdi_handle_read_buffer function
 * Returns 1 if successful or 0 if not
 */
int phdi_test_handle_read_buffer(
     libphdi_handle_t *handle )
{
	uint8_t buffer[ 16 ];

	libcerror_error_t *error = NULL;
	size64_t media_size      = 0;
	ssize_t read_count       = 0;
	off64_t offset           = 0;
	int result               = 0;

	/* Determine size
	 */
	result = libphdi_handle_get_media_size(
	          handle,
	          &media_size,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	PHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Reset offset to 0
	 */
	offset = libphdi_handle_seek_offset(
	          handle,
	          0,
	          SEEK_SET,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 offset,
	 (int64_t) 0 );

	PHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	if( media_size > 16 )
	{
		read_count = libphdi_handle_read_buffer(
		              handle,
		              buffer,
		              16,
		              &error );

		PHDI_TEST_ASSERT_EQUAL_SSIZE(
		 "read_count",
		 read_count,
		 (ssize_t) 16 );

		PHDI_TEST_ASSERT_IS_NULL(
		 "error",
		 error );

		/* Set offset to media_size - 8
		 */
		offset = libphdi_handle_seek_offset(
		          handle,
		          -8,
		          SEEK_END,
		          &error );

		PHDI_TEST_ASSERT_EQUAL_INT64(
		 "offset",
		 offset,
		 (int64_t) media_size - 8 );

		PHDI_TEST_ASSERT_IS_NULL(
		 "error",
		 error );

		/* Read buffer on media_size boundary
		 */
		read_count = libphdi_handle_read_buffer(
		              handle,
		              buffer,
		              16,
		              &error );

		PHDI_TEST_ASSERT_EQUAL_SSIZE(
		 "read_count",
		 read_count,
		 (ssize_t) 8 );

		PHDI_TEST_ASSERT_IS_NULL(
		 "error",
		 error );

		/* Read buffer beyond media_size boundary
		 */
		read_count = libphdi_handle_read_buffer(
		              handle,
		              buffer,
		              16,
		              &error );

		PHDI_TEST_ASSERT_EQUAL_SSIZE(
		 "read_count",
		 read_count,
		 (ssize_t) 0 );

		PHDI_TEST_ASSERT_IS_NULL(
		 "error",
		 error );

		/* Reset offset to 0
		 */
		offset = libphdi_handle_seek_offset(
		          handle,
		          0,
		          SEEK_SET,
		          &error );

		PHDI_TEST_ASSERT_EQUAL_INT64(
		 "offset",
		 offset,
		 (int64_t) 0 );

		PHDI_TEST_ASSERT_IS_NULL(
		 "error",
		 error );
	}
	/* Test error cases
	 */
	read_count = libphdi_handle_read_buffer(
	              NULL,
	              buffer,
	              16,
	              &error );

	PHDI_TEST_ASSERT_EQUAL_SSIZE(
	 "read_count",
	 read_count,
	 (ssize_t) -1 );

	PHDI_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	read_count = libphdi_handle_read_buffer(
	              handle,
	              NULL,
	              16,
	              &error );

	PHDI_TEST_ASSERT_EQUAL_SSIZE(
	 "read_count",
	 read_count,
	 (ssize_t) -1 );

	PHDI_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	read_count = libphdi_handle_read_buffer(
	              handle,
	              buffer,
	              (size_t) SSIZE_MAX + 1,
	              &error );

	PHDI_TEST_ASSERT_EQUAL_SSIZE(
	 "read_count",
	 read_count,
	 (ssize_t) -1 );

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

/* Tests the libphdi_handle_read_buffer_at_offset function
 * Returns 1 if successful or 0 if not
 */
int phdi_test_handle_read_buffer_at_offset(
     libphdi_handle_t *handle )
{
	uint8_t buffer[ 16 ];

	libcerror_error_t *error = NULL;
	size64_t media_size      = 0;
	ssize_t read_count       = 0;
	int result               = 0;

	/* Determine size
	 */
	result = libphdi_handle_get_media_size(
	          handle,
	          &media_size,
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
	if( media_size > 16 )
	{
		read_count = libphdi_handle_read_buffer_at_offset(
		              handle,
		              buffer,
		              16,
		              0,
		              &error );

		PHDI_TEST_ASSERT_EQUAL_SSIZE(
		 "read_count",
		 read_count,
		 (ssize_t) 16 );

		PHDI_TEST_ASSERT_IS_NULL(
		 "error",
		 error );

		/* Read buffer on media_size boundary
		 */
		read_count = libphdi_handle_read_buffer_at_offset(
		              handle,
		              buffer,
		              16,
		              media_size - 8,
		              &error );

		PHDI_TEST_ASSERT_EQUAL_SSIZE(
		 "read_count",
		 read_count,
		 (ssize_t) 8 );

		PHDI_TEST_ASSERT_IS_NULL(
		 "error",
		 error );

		/* Read buffer beyond media_size boundary
		 */
		read_count = libphdi_handle_read_buffer_at_offset(
		              handle,
		              buffer,
		              16,
		              media_size + 8,
		              &error );

		PHDI_TEST_ASSERT_EQUAL_SSIZE(
		 "read_count",
		 read_count,
		 (ssize_t) 0 );

		PHDI_TEST_ASSERT_IS_NULL(
		 "error",
		 error );
	}
	/* Test error cases
	 */
	read_count = libphdi_handle_read_buffer_at_offset(
	              NULL,
	              buffer,
	              16,
	              0,
	              &error );

	PHDI_TEST_ASSERT_EQUAL_SSIZE(
	 "read_count",
	 read_count,
	 (ssize_t) -1 );

	PHDI_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	read_count = libphdi_handle_read_buffer_at_offset(
	              handle,
	              NULL,
	              16,
	              0,
	              &error );

	PHDI_TEST_ASSERT_EQUAL_SSIZE(
	 "read_count",
	 read_count,
	 (ssize_t) -1 );

	PHDI_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	read_count = libphdi_handle_read_buffer_at_offset(
	              handle,
	              buffer,
	              (size_t) SSIZE_MAX + 1,
	              0,
	              &error );

	PHDI_TEST_ASSERT_EQUAL_SSIZE(
	 "read_count",
	 read_count,
	 (ssize_t) -1 );

	PHDI_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	read_count = libphdi_handle_read_buffer_at_offset(
	              handle,
	              buffer,
	              16,
	              -1,
	              &error );

	PHDI_TEST_ASSERT_EQUAL_SSIZE(
	 "read_count",
	 read_count,
	 (ssize_t) -1 );

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

/* Tests the libphdi_handle_seek_offset function
 * Returns 1 if successful or 0 if not
 */
int phdi_test_handle_seek_offset(
     libphdi_handle_t *handle )
{
	libcerror_error_t *error = NULL;
	size64_t size            = 0;
	off64_t offset           = 0;

	/* Test regular cases
	 */
	offset = libphdi_handle_seek_offset(
	          handle,
	          0,
	          SEEK_END,
	          &error );

	PHDI_TEST_ASSERT_NOT_EQUAL_INT64(
	 "offset",
	 offset,
	 (int64_t) -1 );

	PHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	size = (size64_t) offset;

	offset = libphdi_handle_seek_offset(
	          handle,
	          1024,
	          SEEK_SET,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 offset,
	 (int64_t) 1024 );

	PHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	offset = libphdi_handle_seek_offset(
	          handle,
	          -512,
	          SEEK_CUR,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 offset,
	 (int64_t) 512 );

	PHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	offset = libphdi_handle_seek_offset(
	          handle,
	          (off64_t) ( size + 512 ),
	          SEEK_SET,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 offset,
	 (int64_t) ( size + 512 ) );

	PHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Reset offset to 0
	 */
	offset = libphdi_handle_seek_offset(
	          handle,
	          0,
	          SEEK_SET,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 offset,
	 (int64_t) 0 );

	PHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	offset = libphdi_handle_seek_offset(
	          NULL,
	          0,
	          SEEK_SET,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 offset,
	 (int64_t) -1 );

	PHDI_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	offset = libphdi_handle_seek_offset(
	          handle,
	          -1,
	          SEEK_SET,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 offset,
	 (int64_t) -1 );

	PHDI_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	offset = libphdi_handle_seek_offset(
	          handle,
	          -1,
	          SEEK_CUR,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 offset,
	 (int64_t) -1 );

	PHDI_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	offset = libphdi_handle_seek_offset(
	          handle,
	          (off64_t) ( -1 * ( size + 1 ) ),
	          SEEK_END,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 offset,
	 (int64_t) -1 );

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

/* Tests the libphdi_handle_get_offset function
 * Returns 1 if successful or 0 if not
 */
int phdi_test_handle_get_offset(
     libphdi_handle_t *handle )
{
	libcerror_error_t *error = NULL;
	off64_t offset           = 0;
	int offset_is_set        = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = libphdi_handle_get_offset(
	          handle,
	          &offset,
	          &error );

	PHDI_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	PHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	offset_is_set = result;

	/* Test error cases
	 */
	result = libphdi_handle_get_offset(
	          NULL,
	          &offset,
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

	if( offset_is_set != 0 )
	{
		result = libphdi_handle_get_offset(
		          handle,
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
	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libphdi_handle_get_media_size function
 * Returns 1 if successful or 0 if not
 */
int phdi_test_handle_get_media_size(
     libphdi_handle_t *handle )
{
	libcerror_error_t *error = NULL;
	size64_t media_size      = 0;
	int media_size_is_set    = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = libphdi_handle_get_media_size(
	          handle,
	          &media_size,
	          &error );

	PHDI_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	PHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	media_size_is_set = result;

	/* Test error cases
	 */
	result = libphdi_handle_get_media_size(
	          NULL,
	          &media_size,
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

	if( media_size_is_set != 0 )
	{
		result = libphdi_handle_get_media_size(
		          handle,
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
	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* The main program
 */
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
int wmain(
     int argc,
     wchar_t * const argv[] )
#else
int main(
     int argc,
     char * const argv[] )
#endif
{
	libbfio_handle_t *file_io_handle = NULL;
	libcerror_error_t *error         = NULL;
	libphdi_handle_t *handle         = NULL;
	system_character_t *source       = NULL;
	system_integer_t option          = 0;
	size_t string_length             = 0;
	int result                       = 0;

	while( ( option = phdi_test_getopt(
	                   argc,
	                   argv,
	                   _SYSTEM_STRING( "" ) ) ) != (system_integer_t) -1 )
	{
		switch( option )
		{
			case (system_integer_t) '?':
			default:
				fprintf(
				 stderr,
				 "Invalid argument: %" PRIs_SYSTEM ".\n",
				 argv[ optind - 1 ] );

				return( EXIT_FAILURE );
		}
	}
	if( optind < argc )
	{
		source = argv[ optind ];
	}
#if defined( HAVE_DEBUG_OUTPUT ) && defined( PHDI_TEST_HANDLE_VERBOSE )
	libphdi_notify_set_verbose(
	 1 );
	libphdi_notify_set_stream(
	 stderr,
	 NULL );
#endif

	PHDI_TEST_RUN(
	 "libphdi_handle_initialize",
	 phdi_test_handle_initialize );

	PHDI_TEST_RUN(
	 "libphdi_handle_free",
	 phdi_test_handle_free );

#if !defined( __BORLANDC__ ) || ( __BORLANDC__ >= 0x0560 )
	if( source != NULL )
	{
		result = libbfio_file_initialize(
		          &file_io_handle,
		          &error );

		PHDI_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

	        PHDI_TEST_ASSERT_IS_NOT_NULL(
	         "file_io_handle",
	         file_io_handle );

	        PHDI_TEST_ASSERT_IS_NULL(
	         "error",
	         error );

		string_length = system_string_length(
		                 source );

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
		result = libbfio_file_set_name_wide(
		          file_io_handle,
		          source,
		          string_length,
		          &error );
#else
		result = libbfio_file_set_name(
		          file_io_handle,
		          source,
		          string_length,
		          &error );
#endif
		PHDI_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

	        PHDI_TEST_ASSERT_IS_NULL(
	         "error",
	         error );

		result = libphdi_check_file_signature_file_io_handle(
		          file_io_handle,
		          &error );

		PHDI_TEST_ASSERT_NOT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		PHDI_TEST_ASSERT_IS_NULL(
		 "error",
		 error );
	}
	if( result != 0 )
	{
		PHDI_TEST_RUN_WITH_ARGS(
		 "libphdi_handle_open",
		 phdi_test_handle_open,
		 source );

#if defined( HAVE_WIDE_CHARACTER_TYPE )

		PHDI_TEST_RUN_WITH_ARGS(
		 "libphdi_handle_open_wide",
		 phdi_test_handle_open_wide,
		 source );

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

		PHDI_TEST_RUN_WITH_ARGS(
		 "libphdi_handle_open_file_io_handle",
		 phdi_test_handle_open_file_io_handle,
		 source );

		PHDI_TEST_RUN(
		 "libphdi_handle_close",
		 phdi_test_handle_close );

		PHDI_TEST_RUN_WITH_ARGS(
		 "libphdi_handle_open_close",
		 phdi_test_handle_open_close,
		 source );

		/* Initialize handle for tests
		 */
		result = phdi_test_handle_open_source(
		          &handle,
		          file_io_handle,
		          &error );

		PHDI_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

		PHDI_TEST_ASSERT_IS_NOT_NULL(
		 "handle",
		 handle );

		PHDI_TEST_ASSERT_IS_NULL(
		 "error",
		 error );

		PHDI_TEST_RUN_WITH_ARGS(
		 "libphdi_handle_signal_abort",
		 phdi_test_handle_signal_abort,
		 handle );

#if defined( __GNUC__ ) && !defined( LIBPHDI_DLL_IMPORT )

		/* TODO: add tests for libphdi_handle_open_read */

#endif /* defined( __GNUC__ ) && !defined( LIBPHDI_DLL_IMPORT ) */

		PHDI_TEST_RUN_WITH_ARGS(
		 "libphdi_handle_read_buffer",
		 phdi_test_handle_read_buffer,
		 handle );

		PHDI_TEST_RUN_WITH_ARGS(
		 "libphdi_handle_read_buffer_at_offset",
		 phdi_test_handle_read_buffer_at_offset,
		 handle );

		/* TODO: add tests for libphdi_handle_write_buffer */

		/* TODO: add tests for libphdi_handle_write_buffer_at_offset */

		PHDI_TEST_RUN_WITH_ARGS(
		 "libphdi_handle_seek_offset",
		 phdi_test_handle_seek_offset,
		 handle );

		PHDI_TEST_RUN_WITH_ARGS(
		 "libphdi_handle_get_offset",
		 phdi_test_handle_get_offset,
		 handle );

		PHDI_TEST_RUN_WITH_ARGS(
		 "libphdi_handle_get_media_size",
		 phdi_test_handle_get_media_size,
		 handle );

		/* Clean up
		 */
		result = phdi_test_handle_close_source(
		          &handle,
		          &error );

		PHDI_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 0 );

		PHDI_TEST_ASSERT_IS_NULL(
		 "handle",
		 handle );

		PHDI_TEST_ASSERT_IS_NULL(
		 "error",
		 error );

		result = libbfio_handle_free(
		          &file_io_handle,
		          &error );

		PHDI_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

		PHDI_TEST_ASSERT_IS_NULL(
	         "file_io_handle",
	         file_io_handle );

	        PHDI_TEST_ASSERT_IS_NULL(
	         "error",
	         error );
	}
#endif /* !defined( __BORLANDC__ ) || ( __BORLANDC__ >= 0x0560 ) */

	return( EXIT_SUCCESS );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( handle != NULL )
	{
		libphdi_handle_free(
		 &handle,
		 NULL );
	}
	if( file_io_handle != NULL )
	{
		libbfio_handle_free(
		 &file_io_handle,
		 NULL );
	}
	return( EXIT_FAILURE );
}

