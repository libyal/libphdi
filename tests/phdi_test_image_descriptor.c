/*
 * Library image_descriptor type test program
 *
 * Copyright (C) 2009-2022, Joachim Metz <joachim.metz@gmail.com>
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

#include "../libphdi/libphdi_definitions.h"
#include "../libphdi/libphdi_image_descriptor.h"
#include "../libphdi/libphdi_image_values.h"

#if defined( __GNUC__ ) && !defined( LIBPHDI_DLL_IMPORT )

/* Tests the libphdi_image_descriptor_initialize function
 * Returns 1 if successful or 0 if not
 */
int phdi_test_image_descriptor_initialize(
     void )
{
	libcerror_error_t *error                     = NULL;
	libphdi_image_descriptor_t *image_descriptor = NULL;
	libphdi_image_values_t *image_values         = NULL;
	int result                                   = 0;

#if defined( HAVE_PHDI_TEST_MEMORY )
	int number_of_malloc_fail_tests              = 1;
	int number_of_memset_fail_tests              = 1;
	int test_number                              = 0;
#endif

	/* Initialize test
	 */
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

	/* Test regular cases
	 */
	result = libphdi_image_descriptor_initialize(
	          &image_descriptor,
	          image_values,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	PHDI_TEST_ASSERT_IS_NOT_NULL(
	 "image_descriptor",
	 image_descriptor );

	PHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libphdi_image_descriptor_free(
	          &image_descriptor,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	PHDI_TEST_ASSERT_IS_NULL(
	 "image_descriptor",
	 image_descriptor );

	PHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libphdi_image_descriptor_initialize(
	          NULL,
	          image_values,
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

	image_descriptor = (libphdi_image_descriptor_t *) 0x12345678UL;

	result = libphdi_image_descriptor_initialize(
	          &image_descriptor,
	          image_values,
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

	image_descriptor = NULL;

	result = libphdi_image_descriptor_initialize(
	          &image_descriptor,
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
		/* Test libphdi_image_descriptor_initialize with malloc failing
		 */
		phdi_test_malloc_attempts_before_fail = test_number;

		result = libphdi_image_descriptor_initialize(
		          &image_descriptor,
		          image_values,
		          &error );

		if( phdi_test_malloc_attempts_before_fail != -1 )
		{
			phdi_test_malloc_attempts_before_fail = -1;

			if( image_descriptor != NULL )
			{
				libphdi_image_descriptor_free(
				 &image_descriptor,
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
			 "image_descriptor",
			 image_descriptor );

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
		/* Test libphdi_image_descriptor_initialize with memset failing
		 */
		phdi_test_memset_attempts_before_fail = test_number;

		result = libphdi_image_descriptor_initialize(
		          &image_descriptor,
		          image_values,
		          &error );

		if( phdi_test_memset_attempts_before_fail != -1 )
		{
			phdi_test_memset_attempts_before_fail = -1;

			if( image_descriptor != NULL )
			{
				libphdi_image_descriptor_free(
				 &image_descriptor,
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
			 "image_descriptor",
			 image_descriptor );

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
	if( image_descriptor != NULL )
	{
		libphdi_image_descriptor_free(
		 &image_descriptor,
		 NULL );
	}
	return( 0 );
}

#endif /* defined( __GNUC__ ) && !defined( LIBPHDI_DLL_IMPORT ) */

/* Tests the libphdi_image_descriptor_free function
 * Returns 1 if successful or 0 if not
 */
int phdi_test_image_descriptor_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libphdi_image_descriptor_free(
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

/* Tests the libphdi_image_descriptor_get_type function
 * Returns 1 if successful or 0 if not
 */
int phdi_test_image_descriptor_get_type(
     libphdi_image_descriptor_t *image_descriptor )
{
	libcerror_error_t *error = NULL;
	int result               = 0;
	int type                 = 0;

	/* Test regular cases
	 */
	result = libphdi_image_descriptor_get_type(
	          image_descriptor,
	          &type,
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
	result = libphdi_image_descriptor_get_type(
	          NULL,
	          &type,
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

	result = libphdi_image_descriptor_get_type(
	          image_descriptor,
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

/* Tests the libphdi_image_descriptor_get_utf8_filename_size function
 * Returns 1 if successful or 0 if not
 */
int phdi_test_image_descriptor_get_utf8_filename_size(
     libphdi_image_descriptor_t *image_descriptor )
{
	libcerror_error_t *error  = NULL;
	size_t utf8_filename_size = 0;
	int result                = 0;

	/* Test regular cases
	 */
	result = libphdi_image_descriptor_get_utf8_filename_size(
	          image_descriptor,
	          &utf8_filename_size,
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
	result = libphdi_image_descriptor_get_utf8_filename_size(
	          NULL,
	          &utf8_filename_size,
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

	result = libphdi_image_descriptor_get_utf8_filename_size(
	          image_descriptor,
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

/* Tests the libphdi_image_descriptor_get_utf8_filename function
 * Returns 1 if successful or 0 if not
 */
int phdi_test_image_descriptor_get_utf8_filename(
     libphdi_image_descriptor_t *image_descriptor )
{
	uint8_t utf8_filename[ 32 ];

	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test regular cases
	 */
	result = libphdi_image_descriptor_get_utf8_filename(
	          image_descriptor,
	          utf8_filename,
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
	result = libphdi_image_descriptor_get_utf8_filename(
	          NULL,
	          utf8_filename,
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

	result = libphdi_image_descriptor_get_utf8_filename(
	          image_descriptor,
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

	result = libphdi_image_descriptor_get_utf8_filename(
	          image_descriptor,
	          utf8_filename,
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

	result = libphdi_image_descriptor_get_utf8_filename(
	          image_descriptor,
	          utf8_filename,
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

/* Tests the libphdi_image_descriptor_get_utf16_filename_size function
 * Returns 1 if successful or 0 if not
 */
int phdi_test_image_descriptor_get_utf16_filename_size(
     libphdi_image_descriptor_t *image_descriptor )
{
	libcerror_error_t *error   = NULL;
	size_t utf16_filename_size = 0;
	int result                 = 0;

	/* Test regular cases
	 */
	result = libphdi_image_descriptor_get_utf16_filename_size(
	          image_descriptor,
	          &utf16_filename_size,
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
	result = libphdi_image_descriptor_get_utf16_filename_size(
	          NULL,
	          &utf16_filename_size,
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

	result = libphdi_image_descriptor_get_utf16_filename_size(
	          image_descriptor,
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

/* Tests the libphdi_image_descriptor_get_utf16_filename function
 * Returns 1 if successful or 0 if not
 */
int phdi_test_image_descriptor_get_utf16_filename(
     libphdi_image_descriptor_t *image_descriptor )
{
	uint16_t utf16_filename[ 32 ];

	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test regular cases
	 */
	result = libphdi_image_descriptor_get_utf16_filename(
	          image_descriptor,
	          utf16_filename,
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
	result = libphdi_image_descriptor_get_utf16_filename(
	          NULL,
	          utf16_filename,
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

	result = libphdi_image_descriptor_get_utf16_filename(
	          image_descriptor,
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

	result = libphdi_image_descriptor_get_utf16_filename(
	          image_descriptor,
	          utf16_filename,
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

	result = libphdi_image_descriptor_get_utf16_filename(
	          image_descriptor,
	          utf16_filename,
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

	libcerror_error_t *error                     = NULL;
	libphdi_image_descriptor_t *image_descriptor = NULL;
	libphdi_image_values_t *image_values         = NULL;
	int result                                   = 0;

#endif /* defined( __GNUC__ ) && !defined( LIBPHDI_DLL_IMPORT ) */

	PHDI_TEST_UNREFERENCED_PARAMETER( argc )
	PHDI_TEST_UNREFERENCED_PARAMETER( argv )

#if defined( __GNUC__ ) && !defined( LIBPHDI_DLL_IMPORT )

	PHDI_TEST_RUN(
	 "libphdi_image_descriptor_initialize",
	 phdi_test_image_descriptor_initialize );

#endif /* defined( __GNUC__ ) && !defined( LIBPHDI_DLL_IMPORT ) */

	PHDI_TEST_RUN(
	 "libphdi_image_descriptor_free",
	 phdi_test_image_descriptor_free );

#if defined( __GNUC__ ) && !defined( LIBPHDI_DLL_IMPORT )
#if !defined( __BORLANDC__ ) || ( __BORLANDC__ >= 0x0560 )

	/* Initialize image_descriptor for tests
	 */
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

	image_values->type = LIBPHDI_IMAGE_TYPE_COMPRESSED;

	result = libphdi_image_values_set_filename(
	          image_values,
	          (uint8_t *) "test.hdd",
	          9,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	PHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libphdi_image_descriptor_initialize(
	          &image_descriptor,
	          image_values,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	PHDI_TEST_ASSERT_IS_NOT_NULL(
	 "image_descriptor",
	 image_descriptor );

	PHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	PHDI_TEST_RUN_WITH_ARGS(
	 "libphdi_image_descriptor_get_type",
	 phdi_test_image_descriptor_get_type,
	 image_descriptor );

	PHDI_TEST_RUN_WITH_ARGS(
	 "libphdi_image_descriptor_get_utf8_filename_size",
	 phdi_test_image_descriptor_get_utf8_filename_size,
	 image_descriptor );

	PHDI_TEST_RUN_WITH_ARGS(
	 "libphdi_image_descriptor_get_utf8_filename",
	 phdi_test_image_descriptor_get_utf8_filename,
	 image_descriptor );

	PHDI_TEST_RUN_WITH_ARGS(
	 "libphdi_image_descriptor_get_utf16_filename_size",
	 phdi_test_image_descriptor_get_utf16_filename_size,
	 image_descriptor );

	PHDI_TEST_RUN_WITH_ARGS(
	 "libphdi_image_descriptor_get_utf16_filename",
	 phdi_test_image_descriptor_get_utf16_filename,
	 image_descriptor );

	/* Clean up
	 */
	result = libphdi_image_descriptor_free(
	          &image_descriptor,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	PHDI_TEST_ASSERT_IS_NULL(
	 "image_descriptor",
	 image_descriptor );

	PHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

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

#endif /* !defined( __BORLANDC__ ) || ( __BORLANDC__ >= 0x0560 ) */
#endif /* defined( __GNUC__ ) && !defined( LIBPHDI_DLL_IMPORT ) */

	return( EXIT_SUCCESS );

on_error:
#if defined( __GNUC__ ) && !defined( LIBPHDI_DLL_IMPORT )
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( image_descriptor != NULL )
	{
		libphdi_image_descriptor_free(
		 &image_descriptor,
		 NULL );
	}
	if( image_values != NULL )
	{
		libphdi_image_values_free(
		 &image_values,
		 NULL );
	}
#endif /* defined( __GNUC__ ) && !defined( LIBPHDI_DLL_IMPORT ) */

	return( EXIT_FAILURE );
}

