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
		memory_free(
		 *extent_values );

		*extent_values = NULL;
	}
	return( 1 );
}

/* Sets extent values
 * Returns 1 if successful or -1 on error
 */
int libphdi_extent_values_set(
     libphdi_extent_values_t *extent_values,
     const uint8_t *filename,
     size_t filename_length,
     int type,
     off64_t start_offset,
     off64_t end_offset,
     libcerror_error_t **error )
{
	static char *function = "libphdi_extent_values_set";

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
	if( ( type != LIBPHDI_EXTENT_TYPE_COMPRESSED )
	 && ( type != LIBPHDI_EXTENT_TYPE_PLAIN ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported type: %d.",
		 function,
		 type );

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
	if( libphdi_extent_values_set_filename(
	     extent_values,
	     filename,
	     filename_length,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set filename.",
		 function );

		return( -1 );
	}
	extent_values->type   = type;
	extent_values->offset = start_offset;
	extent_values->size   = end_offset - start_offset;

	return( 1 );
}

/* Sets the filename
 * Returns 1 if successful or -1 on error
 */
int libphdi_extent_values_set_filename(
     libphdi_extent_values_t *extent_values,
     const uint8_t *filename,
     size_t filename_length,
     libcerror_error_t **error )
{
	static char *function = "libphdi_extent_values_set_filename";

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
	if( extent_values->filename != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid extent values - filename value already set.",
		 function );

		return( -1 );
	}
	if( filename == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid filename.",
		 function );

		return( -1 );
	}
	if( ( filename_length == 0 )
	 || ( filename_length > ( (size_t) MEMORY_MAXIMUM_ALLOCATION_SIZE - 1 ) ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid filename size value out of bounds.",
		 function );

		return( -1 );
	}
	extent_values->filename_size = filename_length + 1;

	extent_values->filename = (uint8_t *) memory_allocate(
	                                       sizeof( uint8_t ) * extent_values->filename_size );

	if( extent_values->filename == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create filename.",
		 function );

		goto on_error;
	}
	if( memory_copy(
	     extent_values->filename,
	     filename,
	     filename_length ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to copy filename.",
		 function );

		goto on_error;
	}
	extent_values->filename[ filename_length ] = 0;

	return( 1 );

on_error:
	if( extent_values->filename != NULL )
	{
		memory_free(
		 extent_values->filename );

		extent_values->filename = NULL;
	}
	extent_values->filename_size = 0;

	return( -1 );
}

/* Retrieves the extent type
 * Returns 1 if successful or -1 on error
 */
int libphdi_extent_values_get_type(
     libphdi_extent_values_t *extent_values,
     int *type,
     libcerror_error_t **error )
{
	static char *function = "libphdi_extent_values_get_type";

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
	if( type == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid type.",
		 function );

		return( -1 );
	}
	*type = extent_values->type;

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
	static char *function = "libphdi_extent_values_get_utf8_filename_size";

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
	if( extent_values->filename == NULL )
	{
		return( 0 );
	}
	if( utf8_string_size == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-8 string size.",
		 function );

		return( -1 );
	}
	*utf8_string_size = extent_values->filename_size;

	return( 1 );
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
	static char *function = "libphdi_extent_values_get_utf8_filename";

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
	if( extent_values->filename == NULL )
	{
		return( 0 );
	}
	if( utf8_string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-8 string.",
		 function );

		return( -1 );
	}
	if( utf8_string_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-8 string size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( utf8_string_size < extent_values->filename_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: UTF-8 string is too small.",
		 function );

		return( -1 );
	}
	if( narrow_string_copy(
	     utf8_string,
	     extent_values->filename,
	     extent_values->filename_size ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to copy UTF-8 string.",
		 function );

		return( -1 );
	}
	return( 1 );
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
	static char *function = "libphdi_extent_values_get_utf16_filename_size";

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
	if( extent_values->filename == NULL )
	{
		return( 0 );
	}
	if( libuna_utf16_string_size_from_utf8(
	     (uint8_t *) extent_values->filename,
	     extent_values->filename_size,
	     utf16_string_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve UTF-16 size size.",
		 function );

		return( -1 );
	}
	return( 1 );
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
	static char *function = "libphdi_extent_values_get_utf16_filename";

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
	if( extent_values->filename == NULL )
	{
		return( 0 );
	}
	if( libuna_utf16_string_copy_from_utf8(
	     utf16_string,
	     utf16_string_size,
	     (uint8_t *) extent_values->filename,
	     extent_values->filename_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
		 "%s: unable to copy UTF-16 string.",
		 function );

		return( -1 );
	}
	return( 1 );
}

