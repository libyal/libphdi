/*
 * Extent values functions
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
#include <narrow_string.h>
#include <types.h>

#include "libphdi_definitions.h"
#include "libphdi_extent_values.h"
#include "libphdi_image_values.h"
#include "libphdi_libcerror.h"
#include "libphdi_libuna.h"

/* Creates extent values
 * Make sure the value extent_values is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libphdi_extent_values_initialize(
     libphdi_extent_values_t **extent_values,
     libcerror_error_t **error )
{
	static char *function = "libphdi_extent_values_initialize";

	if( extent_values == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid extent values.",
		 function );

		return( -1 );
	}
	if( *extent_values != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid extent values value already set.",
		 function );

		return( -1 );
	}
	*extent_values = memory_allocate_structure(
	                  libphdi_extent_values_t );

	if( *extent_values == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create extent values.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *extent_values,
	     0,
	     sizeof( libphdi_extent_values_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear extent values.",
		 function );

		memory_free(
		 *extent_values );

		*extent_values = NULL;

		return( -1 );
	}
	if( libcdata_array_initialize(
	     &( ( *extent_values )->image_values_array ),
	     0,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create image values array.",
		 function );

		goto on_error;
	}
	( *extent_values )->offset = -1;

	return( 1 );

on_error:
	if( *extent_values != NULL )
	{
		memory_free(
		 *extent_values );

		*extent_values = NULL;
	}
	return( -1 );
}

/* Frees extent values
 * Returns 1 if successful or -1 on error
 */
int libphdi_extent_values_free(
     libphdi_extent_values_t **extent_values,
     libcerror_error_t **error )
{
	static char *function = "libphdi_extent_values_free";
	int result            = 1;

	if( extent_values == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid extent values.",
		 function );

		return( -1 );
	}
	if( *extent_values != NULL )
	{
		if( libcdata_array_free(
		     &( ( *extent_values )->image_values_array ),
		     (int (*)(intptr_t **, libcerror_error_t **)) &libphdi_image_values_free,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free image values array.",
			 function );

			result = -1;
		}
		memory_free(
		 *extent_values );

		*extent_values = NULL;
	}
	return( result );
}

/* Sets the extent range (offset and size)
 * Returns 1 if successful or -1 on error
 */
int libphdi_extent_values_set_range(
     libphdi_extent_values_t *extent_values,
     off64_t start_offset,
     off64_t end_offset,
     libcerror_error_t **error )
{
	static char *function = "libphdi_extent_values_set_range";

	if( extent_values == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid extent values.",
		 function );

		return( -1 );
	}
	if( start_offset < 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid start offset value out of bounds.",
		 function );

		return( -1 );
	}
	if( end_offset <= start_offset )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid end offset value out of bounds.",
		 function );

		return( -1 );
	}
	extent_values->offset = start_offset;
	extent_values->size   = end_offset - start_offset;

	return( 1 );
}

/* Retrieves the extent type
 * Returns 1 if successful or -1 on error
 */
int libphdi_extent_values_get_type(
     libphdi_extent_values_t *extent_values,
     int *type,
     libcerror_error_t **error )
{
	libphdi_image_values_t *image_values = NULL;
	static char *function                = "libphdi_extent_values_get_type";

	if( extent_values == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid extent values.",
		 function );

		return( -1 );
	}
	if( libcdata_array_get_entry_by_index(
	     extent_values->image_values_array,
	     0,
	     (intptr_t **) &image_values,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve image values: 0 from array.",
		 function );

		return( -1 );
	}
	if( libphdi_image_values_get_type(
	     image_values,
	     type,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve type from image values: 0.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the extent range (offset and size)
 * Returns 1 if successful or -1 on error
 */
int libphdi_extent_values_get_range(
     libphdi_extent_values_t *extent_values,
     off64_t *offset,
     size64_t *size,
     libcerror_error_t **error )
{
	static char *function = "libphdi_extent_values_get_range";

	if( extent_values == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid extent values.",
		 function );

		return( -1 );
	}
	if( offset == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid offset.",
		 function );

		return( -1 );
	}
	if( size == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid size.",
		 function );

		return( -1 );
	}
	*offset = extent_values->offset;
	*size   = extent_values->size;

	return( 1 );
}

/* Retrieves the size of the UTF-8 encoded filename
 * The returned size includes the end of string character
 * Returns 1 if successful, 0 if not available or -1 on error
 */
int libphdi_extent_values_get_utf8_filename_size(
     libphdi_extent_values_t *extent_values,
     size_t *utf8_string_size,
     libcerror_error_t **error )
{
	libphdi_image_values_t *image_values = NULL;
	static char *function                = "libphdi_extent_values_get_utf8_filename_size";
	int result                           = 0;

	if( extent_values == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid extent values.",
		 function );

		return( -1 );
	}
	if( libcdata_array_get_entry_by_index(
	     extent_values->image_values_array,
	     0,
	     (intptr_t **) &image_values,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve image values: 0 from array.",
		 function );

		return( -1 );
	}
	result = libphdi_image_values_get_utf8_filename_size(
	          image_values,
	          utf8_string_size,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve UTF-8 filename size from image values: 0.",
		 function );

		return( -1 );
	}
	return( result );
}

/* Retrieves the UTF-8 encoded filename
 * The size should include the end of string character
 * Returns 1 if successful, 0 if not available or -1 on error
 */
int libphdi_extent_values_get_utf8_filename(
     libphdi_extent_values_t *extent_values,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error )
{
	libphdi_image_values_t *image_values = NULL;
	static char *function                = "libphdi_extent_values_get_utf8_filename";
	int result                           = 0;

	if( extent_values == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid extent values.",
		 function );

		return( -1 );
	}
	if( libcdata_array_get_entry_by_index(
	     extent_values->image_values_array,
	     0,
	     (intptr_t **) &image_values,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve image values: 0 from array.",
		 function );

		return( -1 );
	}
	result = libphdi_image_values_get_utf8_filename(
	          image_values,
	          utf8_string,
	          utf8_string_size,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve UTF-8 filename from image values: 0.",
		 function );

		return( -1 );
	}
	return( result );
}

/* Retrieves the size of the UTF-16 encoded filename
 * The returned size includes the end of string character
 * Returns 1 if successful, 0 if not available or -1 on error
 */
int libphdi_extent_values_get_utf16_filename_size(
     libphdi_extent_values_t *extent_values,
     size_t *utf16_string_size,
     libcerror_error_t **error )
{
	libphdi_image_values_t *image_values = NULL;
	static char *function                = "libphdi_extent_values_get_utf16_filename_size";
	int result                           = 0;

	if( extent_values == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid extent values.",
		 function );

		return( -1 );
	}
	if( libcdata_array_get_entry_by_index(
	     extent_values->image_values_array,
	     0,
	     (intptr_t **) &image_values,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve image values: 0 from array.",
		 function );

		return( -1 );
	}
	result = libphdi_image_values_get_utf16_filename_size(
	          image_values,
	          utf16_string_size,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve UTF-16 filename size from image values: 0.",
		 function );

		return( -1 );
	}
	return( result );
}

/* Retrieves the UTF-16 encoded filename
 * The size should include the end of string character
 * Returns 1 if successful, 0 if not available or -1 on error
 */
int libphdi_extent_values_get_utf16_filename(
     libphdi_extent_values_t *extent_values,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error )
{
	libphdi_image_values_t *image_values = NULL;
	static char *function                = "libphdi_extent_values_get_utf16_filename";
	int result                           = 0;

	if( extent_values == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid extent values.",
		 function );

		return( -1 );
	}
	if( libcdata_array_get_entry_by_index(
	     extent_values->image_values_array,
	     0,
	     (intptr_t **) &image_values,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve image values: 0 from array.",
		 function );

		return( -1 );
	}
	result = libphdi_image_values_get_utf16_filename(
	          image_values,
	          utf16_string,
	          utf16_string_size,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve UTF-16 filename from image values: 0.",
		 function );

		return( -1 );
	}
	return( result );
}

/* Retrieves the number of images
 * Returns 1 if successful or -1 on error
 */
int libphdi_extent_values_get_number_of_images(
     libphdi_extent_values_t *extent_values,
     int *number_of_images,
     libcerror_error_t **error )
{
	static char *function = "libphdi_extent_values_get_number_of_images";

	if( extent_values == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid extent values.",
		 function );

		return( -1 );
	}
	if( libcdata_array_get_number_of_entries(
	     extent_values->image_values_array,
	     number_of_images,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of images from array.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves a specific image values
 * Returns 1 if successful or -1 on error
 */
int libphdi_extent_values_get_image_values_by_index(
     libphdi_extent_values_t *extent_values,
     int image_index,
     libphdi_image_values_t **image_values,
     libcerror_error_t **error )
{
	static char *function = "libphdi_extent_values_get_image_values_by_index";

	if( extent_values == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid extent values.",
		 function );

		return( -1 );
	}
	if( libcdata_array_get_entry_by_index(
	     extent_values->image_values_array,
	     image_index,
	     (intptr_t **) image_values,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve image: %d values from array.",
		 function,
		 image_index );

		return( -1 );
	}
	return( 1 );
}

