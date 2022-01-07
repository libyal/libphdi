/*
 * Disk parameters functions
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

#include "libphdi_disk_parameters.h"
#include "libphdi_libcerror.h"
#include "libphdi_libuna.h"

/* Creates disk parameters
 * Make sure the value disk_parameters is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libphdi_disk_parameters_initialize(
     libphdi_disk_parameters_t **disk_parameters,
     libcerror_error_t **error )
{
	static char *function = "libphdi_disk_parameters_initialize";

	if( disk_parameters == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid disk parameters.",
		 function );

		return( -1 );
	}
	if( *disk_parameters != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid disk parameters value already set.",
		 function );

		return( -1 );
	}
	*disk_parameters = memory_allocate_structure(
	                    libphdi_disk_parameters_t );

	if( *disk_parameters == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create disk parameters.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *disk_parameters,
	     0,
	     sizeof( libphdi_disk_parameters_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear disk parameters.",
		 function );

		memory_free(
		 *disk_parameters );

		*disk_parameters = NULL;

		return( -1 );
	}
	return( 1 );

on_error:
	if( *disk_parameters != NULL )
	{
		memory_free(
		 *disk_parameters );

		*disk_parameters = NULL;
	}
	return( -1 );
}

/* Frees a disk parameters
 * Returns 1 if successful or -1 on error
 */
int libphdi_disk_parameters_free(
     libphdi_disk_parameters_t **disk_parameters,
     libcerror_error_t **error )
{
	static char *function = "libphdi_disk_parameters_free";

	if( disk_parameters == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid disk parameters.",
		 function );

		return( -1 );
	}
	if( *disk_parameters != NULL )
	{
		if( ( *disk_parameters )->name != NULL )
		{
			memory_free(
			 ( *disk_parameters )->name );
		}
		memory_free(
		 *disk_parameters );

		*disk_parameters = NULL;
	}
	return( 1 );
}

/* Retrieves the media size
 * Returns 1 if successful or -1 on error
 */
int libphdi_disk_parameters_get_media_size(
     libphdi_disk_parameters_t *disk_parameters,
     size64_t *media_size,
     libcerror_error_t **error )
{
	static char *function = "libphdi_disk_parameters_get_media_size";

	if( disk_parameters == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file name values.",
		 function );

		return( -1 );
	}
	if( media_size == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid media size.",
		 function );

		return( -1 );
	}
	*media_size = disk_parameters->media_size;

	return( 1 );
}

/* Retrieves the size of the UTF-8 encoded name
 * The returned size includes the end of string character
 * Returns 1 if successful, 0 if not available or -1 on error
 */
int libphdi_disk_parameters_get_utf8_name_size(
     libphdi_disk_parameters_t *disk_parameters,
     size_t *utf8_string_size,
     libcerror_error_t **error )
{
	static char *function = "libphdi_disk_parameters_get_utf8_name_size";

	if( disk_parameters == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file name values.",
		 function );

		return( -1 );
	}
	if( ( disk_parameters->name == NULL )
	 || ( disk_parameters->name_size == 0 ) )
	{
		return( 0 );
	}
	if( libuna_utf8_string_size_from_utf8_stream(
	     disk_parameters->name,
	     disk_parameters->name_size,
	     utf8_string_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve UTF-8 string size.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the UTF-8 encoded name
 * The size should include the end of string character
 * Returns 1 if successful, 0 if not available or -1 on error
 */
int libphdi_disk_parameters_get_utf8_name(
     libphdi_disk_parameters_t *disk_parameters,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error )
{
	static char *function = "libphdi_disk_parameters_get_utf8_name";

	if( disk_parameters == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file name values.",
		 function );

		return( -1 );
	}
	if( ( disk_parameters->name == NULL )
	 || ( disk_parameters->name_size == 0 ) )
	{
		return( 0 );
	}
	if( libuna_utf8_string_copy_from_utf8_stream(
	     utf8_string,
	     utf8_string_size,
	     disk_parameters->name,
	     disk_parameters->name_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve UTF-8 string.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the size of the UTF-16 encoded name
 * The returned size includes the end of string character
 * Returns 1 if successful, 0 if not available or -1 on error
 */
int libphdi_disk_parameters_get_utf16_name_size(
     libphdi_disk_parameters_t *disk_parameters,
     size_t *utf16_string_size,
     libcerror_error_t **error )
{
	static char *function = "libphdi_disk_parameters_get_utf16_name_size";

	if( disk_parameters == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file name values.",
		 function );

		return( -1 );
	}
	if( ( disk_parameters->name == NULL )
	 || ( disk_parameters->name_size == 0 ) )
	{
		return( 0 );
	}
	if( libuna_utf16_string_size_from_utf8_stream(
	     disk_parameters->name,
	     disk_parameters->name_size,
	     utf16_string_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve UTF-16 string size.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the UTF-16 encoded name
 * The size should include the end of string character
 * Returns 1 if successful, 0 if not available or -1 on error
 */
int libphdi_disk_parameters_get_utf16_name(
     libphdi_disk_parameters_t *disk_parameters,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error )
{
	static char *function = "libphdi_disk_parameters_get_utf16_name";

	if( disk_parameters == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file name values.",
		 function );

		return( -1 );
	}
	if( ( disk_parameters->name == NULL )
	 || ( disk_parameters->name_size == 0 ) )
	{
		return( 0 );
	}
	if( libuna_utf16_string_copy_from_utf8_stream(
	     utf16_string,
	     utf16_string_size,
	     disk_parameters->name,
	     disk_parameters->name_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve UTF-16 string.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Sets the name
 * Returns 1 if successful or -1 on error
 */
int libphdi_disk_parameters_set_name(
     libphdi_disk_parameters_t *disk_parameters,
     const uint8_t *name,
     size_t name_size,
     libcerror_error_t **error )
{
	static char *function = "libphdi_disk_parameters_set_name";

	if( disk_parameters == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file name values.",
		 function );

		return( -1 );
	}
	if( disk_parameters->name != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid disk parameters - name value already set.",
		 function );

		return( -1 );
	}
	if( name == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid name.",
		 function );

		return( -1 );
	}
	if( ( name_size == 0 )
	 || ( name_size > (size_t) MEMORY_MAXIMUM_ALLOCATION_SIZE ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid name size value out of bounds.",
		 function );

		return( -1 );
	}
	disk_parameters->name = (uint8_t *) memory_allocate(
	                                     sizeof( uint8_t ) * name_size );

	if( disk_parameters->name == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create name.",
		 function );

		goto on_error;
	}
	disk_parameters->name_size = name_size;

	if( memory_copy(
	     disk_parameters->name,
	     name,
	     name_size ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to copy name.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( disk_parameters->name != NULL )
	{
		memory_free(
		 disk_parameters->name );

		disk_parameters->name = NULL;
	}
	disk_parameters->name_size = 0;

	return( -1 );
}

