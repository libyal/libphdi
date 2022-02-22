/*
 * Library extent_descriptor type test program
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

#include "phdi_test_libcdata.h"
#include "phdi_test_libcerror.h"
#include "phdi_test_libphdi.h"
#include "phdi_test_macros.h"
#include "phdi_test_memory.h"
#include "phdi_test_unused.h"

#include "../libphdi/libphdi_definitions.h"
#include "../libphdi/libphdi_extent_descriptor.h"
#include "../libphdi/libphdi_extent_values.h"
#include "../libphdi/libphdi_image_values.h"

#if defined( __GNUC__ ) && !defined( LIBPHDI_DLL_IMPORT )

/* Tests the libphdi_extent_descriptor_initialize function
 * Returns 1 if successful or 0 if not
 */
int phdi_test_extent_descriptor_initialize(
     void )
{
	libcerror_error_t *error                       = NULL;
	libphdi_extent_descriptor_t *extent_descriptor = NULL;
	libphdi_extent_values_t *extent_values         = NULL;
	int result                                     = 0;

#if defined( HAVE_PHDI_TEST_MEMORY )
	int number_of_malloc_fail_tests                = 1;
	int number_of_memset_fail_tests                = 1;
	int test_number                                = 0;
#endif

	/* Initialize test
	 */
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

	/* Test regular cases
	 */
	result = libphdi_extent_descriptor_initialize(
	          &extent_descriptor,
	          extent_values,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	PHDI_TEST_ASSERT_IS_NOT_NULL(
	 "extent_descriptor",
	 extent_descriptor );

	PHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libphdi_extent_descriptor_free(
	          &extent_descriptor,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	PHDI_TEST_ASSERT_IS_NULL(
	 "extent_descriptor",
	 extent_descriptor );

	PHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libphdi_extent_descriptor_initialize(
	          NULL,
	          extent_values,
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

	extent_descriptor = (libphdi_extent_descriptor_t *) 0x12345678UL;

	result = libphdi_extent_descriptor_initialize(
	          &extent_descriptor,
	          extent_values,
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

	extent_descriptor = NULL;

	result = libphdi_extent_descriptor_initialize(
	          &extent_descriptor,
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
		/* Test libphdi_extent_descriptor_initialize with malloc failing
		 */
		phdi_test_malloc_attempts_before_fail = test_number;

		result = libphdi_extent_descriptor_initialize(
		          &extent_descriptor,
		          extent_values,
		          &error );

		if( phdi_test_malloc_attempts_before_fail != -1 )
		{
			phdi_test_malloc_attempts_before_fail = -1;

			if( extent_descriptor != NULL )
			{
				libphdi_extent_descriptor_free(
				 &extent_descriptor,
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
			 "extent_descriptor",
			 extent_descriptor );

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
		/* Test libphdi_extent_descriptor_initialize with memset failing
		 */
		phdi_test_memset_attempts_before_fail = test_number;

		result = libphdi_extent_descriptor_initialize(
		          &extent_descriptor,
		          extent_values,
		          &error );

		if( phdi_test_memset_attempts_before_fail != -1 )
		{
			phdi_test_memset_attempts_before_fail = -1;

			if( extent_descriptor != NULL )
			{
				libphdi_extent_descriptor_free(
				 &extent_descriptor,
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
			 "extent_descriptor",
			 extent_descriptor );

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
	if( extent_descriptor != NULL )
	{
		libphdi_extent_descriptor_free(
		 &extent_descriptor,
		 NULL );
	}
	return( 0 );
}

#endif /* defined( __GNUC__ ) && !defined( LIBPHDI_DLL_IMPORT ) */

/* Tests the libphdi_extent_descriptor_free function
 * Returns 1 if successful or 0 if not
 */
int phdi_test_extent_descriptor_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libphdi_extent_descriptor_free(
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

/* Tests the libphdi_extent_descriptor_get_range function
 * Returns 1 if successful or 0 if not
 */
int phdi_test_extent_descriptor_get_range(
     libphdi_extent_descriptor_t *extent_descriptor )
{
	libcerror_error_t *error = NULL;
	size64_t size            = 0;
	off64_t offset           = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = libphdi_extent_descriptor_get_range(
	          extent_descriptor,
	          &offset,
	          &size,
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
	result = libphdi_extent_descriptor_get_range(
	          NULL,
	          &offset,
	          &size,
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

	result = libphdi_extent_descriptor_get_range(
	          extent_descriptor,
	          NULL,
	          &size,
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

	result = libphdi_extent_descriptor_get_range(
	          extent_descriptor,
	          &offset,
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

	libcerror_error_t *error                       = NULL;
	libphdi_extent_descriptor_t *extent_descriptor = NULL;
	libphdi_extent_values_t *extent_values         = NULL;
	libphdi_image_values_t *image_values           = NULL;
	int entry_index                                = 0;
	int result                                     = 0;

#endif /* defined( __GNUC__ ) && !defined( LIBPHDI_DLL_IMPORT ) */

	PHDI_TEST_UNREFERENCED_PARAMETER( argc )
	PHDI_TEST_UNREFERENCED_PARAMETER( argv )

#if defined( __GNUC__ ) && !defined( LIBPHDI_DLL_IMPORT )

	PHDI_TEST_RUN(
	 "libphdi_extent_descriptor_initialize",
	 phdi_test_extent_descriptor_initialize );

#endif /* defined( __GNUC__ ) && !defined( LIBPHDI_DLL_IMPORT ) */

	PHDI_TEST_RUN(
	 "libphdi_extent_descriptor_free",
	 phdi_test_extent_descriptor_free );

#if defined( __GNUC__ ) && !defined( LIBPHDI_DLL_IMPORT )
#if !defined( __BORLANDC__ ) || ( __BORLANDC__ >= 0x0560 )

	/* Initialize extent_descriptor for tests
	 */
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

	result = libphdi_extent_values_set_range(
	          extent_values,
	          0,
	          1024,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

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

	result = libcdata_array_append_entry(
	          extent_values->image_values_array,
	          &entry_index,
	          (intptr_t *) image_values,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	PHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	image_values = NULL;

	result = libphdi_extent_descriptor_initialize(
	          &extent_descriptor,
	          extent_values,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	PHDI_TEST_ASSERT_IS_NOT_NULL(
	 "extent_descriptor",
	 extent_descriptor );

	PHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	PHDI_TEST_RUN_WITH_ARGS(
	 "libphdi_extent_descriptor_get_range",
	 phdi_test_extent_descriptor_get_range,
	 extent_descriptor );

	/* TODO add tests for libphdi_extent_values_get_number_of_images */

	/* TODO add tests for libphdi_extent_values_get_image_values_by_index */

	/* Clean up
	 */
	result = libphdi_extent_descriptor_free(
	          &extent_descriptor,
	          &error );

	PHDI_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	PHDI_TEST_ASSERT_IS_NULL(
	 "extent_descriptor",
	 extent_descriptor );

	PHDI_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

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
	if( extent_descriptor != NULL )
	{
		libphdi_extent_descriptor_free(
		 &extent_descriptor,
		 NULL );
	}
	if( image_values != NULL )
	{
		libphdi_image_values_free(
		 &image_values,
		 NULL );
	}
	if( extent_values != NULL )
	{
		libphdi_extent_values_free(
		 &extent_values,
		 NULL );
	}
#endif /* defined( __GNUC__ ) && !defined( LIBPHDI_DLL_IMPORT ) */

	return( EXIT_FAILURE );
}

