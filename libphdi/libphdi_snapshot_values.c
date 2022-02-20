/*
 * Snapshot values functions
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

#include "libphdi_libcerror.h"
#include "libphdi_libuna.h"
#include "libphdi_snapshot_values.h"
#include "libphdi_uuid_string.h"

/* Creates snapshot values
 * Make sure the value snapshot_values is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libphdi_snapshot_values_initialize(
     libphdi_snapshot_values_t **snapshot_values,
     libcerror_error_t **error )
{
	static char *function = "libphdi_snapshot_values_initialize";

	if( snapshot_values == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid snapshot values.",
		 function );

		return( -1 );
	}
	if( *snapshot_values != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid snapshot values value already set.",
		 function );

		return( -1 );
	}
	*snapshot_values = memory_allocate_structure(
	                    libphdi_snapshot_values_t );

	if( *snapshot_values == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create snapshot values.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *snapshot_values,
	     0,
	     sizeof( libphdi_snapshot_values_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear snapshot values.",
		 function );

		memory_free(
		 *snapshot_values );

		*snapshot_values = NULL;

		return( -1 );
	}
	return( 1 );

on_error:
	if( *snapshot_values != NULL )
	{
		memory_free(
		 *snapshot_values );

		*snapshot_values = NULL;
	}
	return( -1 );
}

/* Frees snapshot values
 * Returns 1 if successful or -1 on error
 */
int libphdi_snapshot_values_free(
     libphdi_snapshot_values_t **snapshot_values,
     libcerror_error_t **error )
{
	static char *function = "libphdi_snapshot_values_free";

	if( snapshot_values == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid snapshot values.",
		 function );

		return( -1 );
	}
	if( *snapshot_values != NULL )
	{
		memory_free(
		 *snapshot_values );

		*snapshot_values = NULL;
	}
	return( 1 );
}

/* Sets the identifier
 * Returns 1 if successful or -1 on error
 */
int libphdi_snapshot_values_set_identifier(
     libphdi_snapshot_values_t *snapshot_values,
     const uint8_t *utf8_string,
     size_t utf8_string_length,
     libcerror_error_t **error )
{
	static char *function = "libphdi_snapshot_values_set_identifier";

	if( snapshot_values == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid snapshot values.",
		 function );

		return( -1 );
	}
	if( libphdi_uuid_string_copy_to_byte_stream(
	     utf8_string,
	     utf8_string_length,
	     snapshot_values->identifier,
	     16,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to copy UUID string to identifier.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Sets the parent identifier
 * Returns 1 if successful or -1 on error
 */
int libphdi_snapshot_values_set_parent_identifier(
     libphdi_snapshot_values_t *snapshot_values,
     const uint8_t *utf8_string,
     size_t utf8_string_length,
     libcerror_error_t **error )
{
	static char *function = "libphdi_snapshot_values_set_parent_identifier";

	if( snapshot_values == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid snapshot values.",
		 function );

		return( -1 );
	}
	if( libphdi_uuid_string_copy_to_byte_stream(
	     utf8_string,
	     utf8_string_length,
	     snapshot_values->parent_identifier,
	     16,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to copy UUID string to parent identifier.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Sets the filename
 * Returns 1 if successful or -1 on error
 */
int libphdi_snapshot_values_set_filename(
     libphdi_snapshot_values_t *snapshot_values,
     const uint8_t *utf8_string,
     size_t utf8_string_length,
     libcerror_error_t **error )
{
	static char *function = "libphdi_snapshot_values_set_filename";

	if( snapshot_values == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid snapshot values.",
		 function );

		return( -1 );
	}
	if( snapshot_values->filename != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid snapshot values - filename value already set.",
		 function );

		return( -1 );
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
	if( ( utf8_string_length == 0 )
	 || ( utf8_string_length > ( (size_t) MEMORY_MAXIMUM_ALLOCATION_SIZE - 1 ) ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid UTF-8 string length value out of bounds.",
		 function );

		return( -1 );
	}
	snapshot_values->filename_size = utf8_string_length + 1;

	snapshot_values->filename = (uint8_t *) memory_allocate(
	                                         sizeof( uint8_t ) * snapshot_values->filename_size );

	if( snapshot_values->filename == NULL )
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
	     snapshot_values->filename,
	     utf8_string,
	     utf8_string_length ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to copy filename.",
		 function );

		goto on_error;
	}
	snapshot_values->filename[ utf8_string_length ] = 0;

	return( 1 );

on_error:
	if( snapshot_values->filename != NULL )
	{
		memory_free(
		 snapshot_values->filename );

		snapshot_values->filename = NULL;
	}
	snapshot_values->filename_size = 0;

	return( -1 );
}

/* Retrieves the size of the UTF-8 encoded filename
 * The returned size includes the end of string character
 * Returns 1 if successful, 0 if not available or -1 on error
 */
int libphdi_snapshot_values_get_utf8_filename_size(
     libphdi_snapshot_values_t *snapshot_values,
     size_t *utf8_string_size,
     libcerror_error_t **error )
{
	static char *function = "libphdi_snapshot_values_get_utf8_filename_size";

	if( snapshot_values == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid snapshot values.",
		 function );

		return( -1 );
	}
	if( snapshot_values->filename == NULL )
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
	*utf8_string_size = snapshot_values->filename_size;

	return( 1 );
}

/* Retrieves the UTF-8 encoded filename
 * The size should include the end of string character
 * Returns 1 if successful, 0 if not available or -1 on error
 */
int libphdi_snapshot_values_get_utf8_filename(
     libphdi_snapshot_values_t *snapshot_values,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error )
{
	static char *function = "libphdi_snapshot_values_get_utf8_filename";

	if( snapshot_values == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid snapshot values.",
		 function );

		return( -1 );
	}
	if( snapshot_values->filename == NULL )
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
	if( utf8_string_size < snapshot_values->filename_size )
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
	     snapshot_values->filename,
	     snapshot_values->filename_size ) == NULL )
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
int libphdi_snapshot_values_get_utf16_filename_size(
     libphdi_snapshot_values_t *snapshot_values,
     size_t *utf16_string_size,
     libcerror_error_t **error )
{
	static char *function = "libphdi_snapshot_values_get_utf16_filename_size";

	if( snapshot_values == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid snapshot values.",
		 function );

		return( -1 );
	}
	if( snapshot_values->filename == NULL )
	{
		return( 0 );
	}
	if( libuna_utf16_string_size_from_utf8(
	     (uint8_t *) snapshot_values->filename,
	     snapshot_values->filename_size,
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
int libphdi_snapshot_values_get_utf16_filename(
     libphdi_snapshot_values_t *snapshot_values,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error )
{
	static char *function = "libphdi_snapshot_values_get_utf16_filename";

	if( snapshot_values == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid snapshot values.",
		 function );

		return( -1 );
	}
	if( snapshot_values->filename == NULL )
	{
		return( 0 );
	}
	if( libuna_utf16_string_copy_from_utf8(
	     utf16_string,
	     utf16_string_size,
	     (uint8_t *) snapshot_values->filename,
	     snapshot_values->filename_size,
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

