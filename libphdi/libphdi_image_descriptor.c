/*
 * Image descriptor functions
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
#include <memory.h>
#include <types.h>

#include "libphdi_image_descriptor.h"
#include "libphdi_image_values.h"
#include "libphdi_libcerror.h"
#include "libphdi_libcthreads.h"
#include "libphdi_types.h"

/* Creates an image descriptor
 * Make sure the value image_descriptor is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libphdi_image_descriptor_initialize(
     libphdi_image_descriptor_t **image_descriptor,
     libphdi_image_values_t *image_values,
     libcerror_error_t **error )
{
	libphdi_internal_image_descriptor_t *internal_image_descriptor = NULL;
	static char *function                                          = "libphdi_image_descriptor_initialize";

	if( image_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid image descriptor.",
		 function );

		return( -1 );
	}
	if( *image_descriptor != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid image descriptor value already set.",
		 function );

		return( -1 );
	}
	if( image_values == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid image values.",
		 function );

		return( -1 );
	}
	internal_image_descriptor = memory_allocate_structure(
	                             libphdi_internal_image_descriptor_t );

	if( internal_image_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create image descriptor.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     internal_image_descriptor,
	     0,
	     sizeof( libphdi_internal_image_descriptor_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear image descriptor.",
		 function );

		memory_free(
		 internal_image_descriptor );

		return( -1 );
	}
#if defined( HAVE_LIBPHDI_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_initialize(
	     &( internal_image_descriptor->read_write_lock ),
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to initialize read/write lock.",
		 function );

		goto on_error;
	}
#endif
	internal_image_descriptor->image_values = image_values;

	*image_descriptor = (libphdi_image_descriptor_t *) internal_image_descriptor;

	return( 1 );

on_error:
	if( internal_image_descriptor != NULL )
	{
		memory_free(
		 internal_image_descriptor );
	}
	return( -1 );
}

/* Frees an image descriptor
 * Returns 1 if successful or -1 on error
 */
int libphdi_image_descriptor_free(
     libphdi_image_descriptor_t **image_descriptor,
     libcerror_error_t **error )
{
	libphdi_internal_image_descriptor_t *internal_image_descriptor = NULL;
	static char *function                                          = "libphdi_image_descriptor_free";
	int result                                                     = 1;

	if( image_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid image descriptor.",
		 function );

		return( -1 );
	}
	if( *image_descriptor != NULL )
	{
		internal_image_descriptor = (libphdi_internal_image_descriptor_t *) *image_descriptor;
		*image_descriptor         = NULL;

#if defined( HAVE_LIBPHDI_MULTI_THREAD_SUPPORT )
		if( libcthreads_read_write_lock_free(
		     &( internal_image_descriptor->read_write_lock ),
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free read/write lock.",
			 function );

			result = -1;
		}
#endif
		/* The image values reference is freed elsewhere
		 */
		memory_free(
		 internal_image_descriptor );
	}
	return( result );
}

/* Retrieves the image type
 * Returns 1 if successful or -1 on error
 */
int libphdi_image_descriptor_get_type(
     libphdi_image_descriptor_t *image_descriptor,
     int *type,
     libcerror_error_t **error )
{
	libphdi_internal_image_descriptor_t *internal_image_descriptor = NULL;
	static char *function                                          = "libphdi_image_descriptor_get_type";
	int result                                                     = 1;

	if( image_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid image descriptor.",
		 function );

		return( -1 );
	}
	internal_image_descriptor = (libphdi_internal_image_descriptor_t *) image_descriptor;

#if defined( HAVE_LIBPHDI_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_grab_for_read(
	     internal_image_descriptor->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to grab read/write lock for reading.",
		 function );

		return( -1 );
	}
#endif
	if( libphdi_image_values_get_type(
	     internal_image_descriptor->image_values,
	     type,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve type.",
		 function );

		result = -1;
	}
#if defined( HAVE_LIBPHDI_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_release_for_read(
	     internal_image_descriptor->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to release read/write lock for reading.",
		 function );

		return( -1 );
	}
#endif
	return( result );
}

/* Retrieves the size of the UTF-8 encoded filename
 * The returned size includes the end of string character
 * Returns 1 if successful, 0 if not available or -1 on error
 */
int libphdi_image_descriptor_get_utf8_filename_size(
     libphdi_image_descriptor_t *image_descriptor,
     size_t *utf8_string_size,
     libcerror_error_t **error )
{
	libphdi_internal_image_descriptor_t *internal_image_descriptor = NULL;
	static char *function                                          = "libphdi_image_descriptor_get_utf8_filename_size";
	int result                                                     = 1;

	if( image_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid image descriptor.",
		 function );

		return( -1 );
	}
	internal_image_descriptor = (libphdi_internal_image_descriptor_t *) image_descriptor;

#if defined( HAVE_LIBPHDI_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_grab_for_read(
	     internal_image_descriptor->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to grab read/write lock for reading.",
		 function );

		return( -1 );
	}
#endif
	if( libphdi_image_values_get_utf8_filename_size(
	     internal_image_descriptor->image_values,
	     utf8_string_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve UTF-8 string size.",
		 function );

		result = -1;
	}
#if defined( HAVE_LIBPHDI_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_release_for_read(
	     internal_image_descriptor->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to release read/write lock for reading.",
		 function );

		return( -1 );
	}
#endif
	return( result );
}

/* Retrieves the UTF-8 encoded filename
 * The size should include the end of string character
 * Returns 1 if successful, 0 if not available or -1 on error
 */
int libphdi_image_descriptor_get_utf8_filename(
     libphdi_image_descriptor_t *image_descriptor,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error )
{
	libphdi_internal_image_descriptor_t *internal_image_descriptor = NULL;
	static char *function                                          = "libphdi_image_descriptor_get_utf8_filename";
	int result                                                     = 1;

	if( image_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid image descriptor.",
		 function );

		return( -1 );
	}
	internal_image_descriptor = (libphdi_internal_image_descriptor_t *) image_descriptor;

#if defined( HAVE_LIBPHDI_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_grab_for_read(
	     internal_image_descriptor->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to grab read/write lock for reading.",
		 function );

		return( -1 );
	}
#endif
	if( libphdi_image_values_get_utf8_filename(
	     internal_image_descriptor->image_values,
	     utf8_string,
	     utf8_string_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve UTF-8 string.",
		 function );

		result = -1;
	}
#if defined( HAVE_LIBPHDI_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_release_for_read(
	     internal_image_descriptor->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to release read/write lock for reading.",
		 function );

		return( -1 );
	}
#endif
	return( result );
}

/* Retrieves the size of the UTF-16 encoded filename
 * The returned size includes the end of string character
 * Returns 1 if successful, 0 if not available or -1 on error
 */
int libphdi_image_descriptor_get_utf16_filename_size(
     libphdi_image_descriptor_t *image_descriptor,
     size_t *utf16_string_size,
     libcerror_error_t **error )
{
	libphdi_internal_image_descriptor_t *internal_image_descriptor = NULL;
	static char *function                                          = "libphdi_image_descriptor_get_utf16_filename_size";
	int result                                                     = 1;

	if( image_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid image descriptor.",
		 function );

		return( -1 );
	}
	internal_image_descriptor = (libphdi_internal_image_descriptor_t *) image_descriptor;

#if defined( HAVE_LIBPHDI_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_grab_for_read(
	     internal_image_descriptor->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to grab read/write lock for reading.",
		 function );

		return( -1 );
	}
#endif
	if( libphdi_image_values_get_utf16_filename_size(
	     internal_image_descriptor->image_values,
	     utf16_string_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve UTF-16 string size.",
		 function );

		result = -1;
	}
#if defined( HAVE_LIBPHDI_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_release_for_read(
	     internal_image_descriptor->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to release read/write lock for reading.",
		 function );

		return( -1 );
	}
#endif
	return( result );
}

/* Retrieves the UTF-16 encoded filename
 * The size should include the end of string character
 * Returns 1 if successful, 0 if not available or -1 on error
 */
int libphdi_image_descriptor_get_utf16_filename(
     libphdi_image_descriptor_t *image_descriptor,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error )
{
	libphdi_internal_image_descriptor_t *internal_image_descriptor = NULL;
	static char *function                                          = "libphdi_image_descriptor_get_utf16_filename";
	int result                                                     = 1;

	if( image_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid image descriptor.",
		 function );

		return( -1 );
	}
	internal_image_descriptor = (libphdi_internal_image_descriptor_t *) image_descriptor;

#if defined( HAVE_LIBPHDI_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_grab_for_read(
	     internal_image_descriptor->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to grab read/write lock for reading.",
		 function );

		return( -1 );
	}
#endif
	if( libphdi_image_values_get_utf16_filename(
	     internal_image_descriptor->image_values,
	     utf16_string,
	     utf16_string_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve UTF-16 string.",
		 function );

		result = -1;
	}
#if defined( HAVE_LIBPHDI_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_release_for_read(
	     internal_image_descriptor->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to release read/write lock for reading.",
		 function );

		return( -1 );
	}
#endif
	return( result );
}

