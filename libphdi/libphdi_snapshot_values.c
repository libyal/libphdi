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
#include <types.h>

#include "libphdi_extent_table.h"
#include "libphdi_libcerror.h"
#include "libphdi_libcnotify.h"
#include "libphdi_snapshot_values.h"
#include "libphdi_storage_image.h"
#include "libphdi_uuid_string.h"

const uint8_t libphdi_snapshot_values_empty_identifier[ 16 ] = {
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

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
	if( libphdi_extent_table_initialize(
	     &( ( *snapshot_values )->extent_table ),
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create extent table.",
		 function );

		goto on_error;
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
	int result            = 1;

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
		if( libphdi_extent_table_free(
		     &( ( *snapshot_values )->extent_table ),
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free extent table.",
			 function );

			result = -1;
		}
		memory_free(
		 *snapshot_values );

		*snapshot_values = NULL;
	}
	return( result );
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

/* Retrieves the identifier
 * The identifier is a big-endian GUID and is 16 bytes of size
 * Returns 1 if successful or -1 on error
 */
int libphdi_snapshot_values_get_identifier(
     libphdi_snapshot_values_t *snapshot_values,
     uint8_t *guid_data,
     size_t guid_data_size,
     libcerror_error_t **error )
{
	static char *function = "libphdi_snapshot_values_get_identifier";

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
	if( guid_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid GUID data.",
		 function );

		return( -1 );
	}
	if( ( guid_data_size < 16 )
	 || ( guid_data_size > SSIZE_MAX ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid GUID data size value out of bounds.",
		 function );

		return( -1 );
	}
	if( memory_copy(
	     guid_data,
	     snapshot_values->identifier,
	     16 ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to copy identifier.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the parent identifier
 * The identifier is a big-endian GUID and is 16 bytes of size
 * Returns 1 if successful, 0 if not available or -1 on error
 */
int libphdi_snapshot_values_get_parent_identifier(
     libphdi_snapshot_values_t *snapshot_values,
     uint8_t *guid_data,
     size_t guid_data_size,
     libcerror_error_t **error )
{
	static char *function = "libphdi_snapshot_values_get_parent_identifier";

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
	if( guid_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid GUID data.",
		 function );

		return( -1 );
	}
	if( ( guid_data_size < 16 )
	 || ( guid_data_size > SSIZE_MAX ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid GUID data size value out of bounds.",
		 function );

		return( -1 );
	}
	if( memory_compare(
	     snapshot_values->parent_identifier,
	     libphdi_snapshot_values_empty_identifier,
	     16 ) == 0 )
	{
		return( 0 );
	}
	if( memory_copy(
	     guid_data,
	     snapshot_values->parent_identifier,
	     16 ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to copy parent identifier.",
		 function );

		return( -1 );
	}
	return( 1 );
}

