/*
 * Data files functions
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
#include <system_string.h>
#include <types.h>
#include <wide_string.h>

#include "libphdi_definitions.h"
#include "libphdi_data_files.h"
#include "libphdi_image_values.h"
#include "libphdi_io_handle.h"
#include "libphdi_libbfio.h"
#include "libphdi_libcdata.h"
#include "libphdi_libcerror.h"
#include "libphdi_libclocale.h"
#include "libphdi_libcpath.h"
#include "libphdi_libfcache.h"
#include "libphdi_libfdata.h"
#include "libphdi_libuna.h"
#include "libphdi_storage_image.h"
#include "libphdi_system_string.h"

/* Creates data files
 * Make sure the value data_files is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libphdi_data_files_initialize(
     libphdi_data_files_t **data_files,
     libcerror_error_t **error )
{
	static char *function = "libphdi_data_files_initialize";

	if( data_files == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid data files.",
		 function );

		return( -1 );
	}
	if( *data_files != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid data files value already set.",
		 function );

		return( -1 );
	}
	*data_files = memory_allocate_structure(
	                 libphdi_data_files_t );

	if( *data_files == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create data files.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *data_files,
	     0,
	     sizeof( libphdi_data_files_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear data files.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *data_files != NULL )
	{
		memory_free(
		 *data_files );

		*data_files = NULL;
	}
	return( -1 );
}

/* Frees data files
 * Returns 1 if successful or -1 on error
 */
int libphdi_data_files_free(
     libphdi_data_files_t **data_files,
     libcerror_error_t **error )
{
	static char *function = "libphdi_data_files_free";
	int result            = 1;

	if( data_files == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid data files.",
		 function );

		return( -1 );
	}
	if( *data_files != NULL )
	{
		if( libphdi_data_files_clear(
		     *data_files,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to clear data files.",
			 function );

			result = -1;
		}
		memory_free(
		 *data_files );

		*data_files = NULL;
	}
	return( result );
}

/* Clears the data files
 * Returns 1 if successful or -1 on error
 */
int libphdi_data_files_clear(
     libphdi_data_files_t *data_files,
     libcerror_error_t **error )
{
	static char *function = "libphdi_data_files_clear";

	if( data_files == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid data files.",
		 function );

		return( -1 );
	}
	if( data_files->path != NULL )
	{
		memory_free(
		 data_files->path );

		data_files->path      = NULL;
		data_files->path_size = 0;
	}
	return( 1 );
}

/* Retrieves the size of the path
 * Returns 1 if successful, 0 if value not present or -1 on error
 */
int libphdi_data_files_get_path_size(
     libphdi_data_files_t *data_files,
     size_t *path_size,
     libcerror_error_t **error )
{
	static char *function = "libphdi_data_files_get_path_size";

	if( data_files == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid data files.",
		 function );

		return( -1 );
	}
	if( data_files->path == NULL )
	{
		return( 0 );
	}
	if( libphdi_system_string_size_to_narrow_string(
	     data_files->path,
	     data_files->path_size,
	     path_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_CONVERSION,
		 LIBCERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to determine data files path size.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the data files path
 * Returns 1 if successful, 0 if value not present or -1 on error
 */
int libphdi_data_files_get_path(
     libphdi_data_files_t *data_files,
     char *path,
     size_t path_size,
     libcerror_error_t **error )
{
	static char *function   = "libphdi_data_files_get_path";
	size_t narrow_path_size = 0;

	if( data_files == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid data files.",
		 function );

		return( -1 );
	}
	if( path == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid path.",
		 function );

		return( -1 );
	}
	if( path_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid path size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( data_files->path == NULL )
	{
		return( 0 );
	}
	if( libphdi_system_string_size_to_narrow_string(
	     data_files->path,
	     data_files->path_size,
	     &narrow_path_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_CONVERSION,
		 LIBCERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to determine data files path size.",
		 function );

		return( -1 );
	}
	if( path_size < narrow_path_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: path too small.",
		 function );

		return( -1 );
	}
	if( libphdi_system_string_copy_to_narrow_string(
	     data_files->path,
	     data_files->path_size,
	     path,
	     path_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_CONVERSION,
		 LIBCERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to set data files path.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Sets the data files path
 * Returns 1 if successful or -1 on error
 */
int libphdi_data_files_set_path(
     libphdi_data_files_t *data_files,
     const char *path,
     size_t path_length,
     libcerror_error_t **error )
{
	static char *function = "libphdi_data_files_set_path";

	if( data_files == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid data files.",
		 function );

		return( -1 );
	}
	if( path == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid path.",
		 function );

		return( -1 );
	}
	if( path_length > (size_t) ( SSIZE_MAX - 1 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid path length value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( data_files->path != NULL )
	{
		memory_free(
		 data_files->path );

		data_files->path      = NULL;
		data_files->path_size = 0;
	}
	if( libphdi_system_string_size_from_narrow_string(
	     path,
	     path_length + 1,
	     &( data_files->path_size ),
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_CONVERSION,
		 LIBCERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to determine data files path size.",
		 function );

		goto on_error;
	}
	data_files->path = system_string_allocate(
	                                 data_files->path_size );

	if( data_files->path == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create data files path.",
		 function );

		goto on_error;
	}
	if( libphdi_system_string_copy_from_narrow_string(
	     data_files->path,
	     data_files->path_size,
	     path,
	     path_length + 1,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_CONVERSION,
		 LIBCERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to set data files path.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( data_files->path != NULL )
	{
		memory_free(
		 data_files->path );

		data_files->path = NULL;
	}
	data_files->path_size = 0;

	return( -1 );
}

#if defined( HAVE_WIDE_CHARACTER_TYPE )

/* Retrieves the size of the data files path
 * Returns 1 if successful, 0 if value not present or -1 on error
 */
int libphdi_data_files_get_path_size_wide(
     libphdi_data_files_t *data_files,
     size_t *path_size,
     libcerror_error_t **error )
{
	static char *function = "libphdi_data_files_get_path_size_wide";

	if( data_files == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid data files.",
		 function );

		return( -1 );
	}
	if( path_size == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid path size.",
		 function );

		return( -1 );
	}
	if( data_files->path == NULL )
	{
		return( 0 );
	}
	if( libphdi_system_string_size_to_wide_string(
	     data_files->path,
	     data_files->path_size,
	     path_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_CONVERSION,
		 LIBCERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to determine data files path size.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the data files path
 * Returns 1 if successful, 0 if value not present or -1 on error
 */
int libphdi_data_files_get_path_wide(
     libphdi_data_files_t *data_files,
     wchar_t *path,
     size_t path_size,
     libcerror_error_t **error )
{
	static char *function = "libphdi_data_files_get_path_wide";
	size_t wide_path_size = 0;

	if( data_files == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid data files.",
		 function );

		return( -1 );
	}
	if( path == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid path.",
		 function );

		return( -1 );
	}
	if( path_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid path size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( data_files->path == NULL )
	{
		return( 0 );
	}
	if( libphdi_system_string_size_to_wide_string(
	     data_files->path,
	     data_files->path_size,
	     &wide_path_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_CONVERSION,
		 LIBCERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to determine data files path size.",
		 function );

		return( -1 );
	}
	if( path_size < wide_path_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: path too small.",
		 function );

		return( -1 );
	}
	if( libphdi_system_string_copy_to_wide_string(
	     data_files->path,
	     data_files->path_size,
	     path,
	     path_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_CONVERSION,
		 LIBCERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to set data files path.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Sets the data files path
 * Returns 1 if successful or -1 on error
 */
int libphdi_data_files_set_path_wide(
     libphdi_data_files_t *data_files,
     const wchar_t *path,
     size_t path_length,
     libcerror_error_t **error )
{
	static char *function = "libphdi_data_files_set_path_wide";

	if( data_files == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid data files.",
		 function );

		return( -1 );
	}
	if( path == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid  path.",
		 function );

		return( -1 );
	}
	if( path_length > (size_t) ( SSIZE_MAX - 1 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid path length value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( data_files->path != NULL )
	{
		memory_free(
		 data_files->path );

		data_files->path      = NULL;
		data_files->path_size = 0;
	}
	if( libphdi_system_string_size_from_wide_string(
	     path,
	     path_length + 1,
	     &( data_files->path_size ),
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_CONVERSION,
		 LIBCERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to determine data files path size.",
		 function );

		goto on_error;
	}
	data_files->path = system_string_allocate(
	                    data_files->path_size );

	if( data_files->path == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create data files path.",
		 function );

		goto on_error;
	}
	if( libphdi_system_string_copy_from_wide_string(
	     data_files->path,
	     data_files->path_size,
	     path,
	     path_length + 1,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_CONVERSION,
		 LIBCERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to set data files path.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( data_files->path != NULL )
	{
		memory_free(
		 data_files->path );

		data_files->path = NULL;
	}
	data_files->path_size = 0;

	return( -1 );
}

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

/* Retrieves the path of an extent data file
 * Returns 1 if successful or -1 on error
 */
int libphdi_data_files_get_extent_data_file_path(
     libphdi_data_files_t *data_files,
     libphdi_image_values_t *image_values,
     char **path,
     size_t *path_size,
     libcerror_error_t **error )
{
	uint8_t *utf8_filename           = NULL;
	char *extent_data_filename       = NULL;
	static char *function            = "libphdi_data_files_get_extent_data_file_path";
	char *narrow_filename            = NULL;
	size_t extent_data_filename_size = 0;
	size_t narrow_filename_size      = 0;
	size_t utf8_filename_size        = 0;

	if( data_files == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid data files.",
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
	if( path == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid path.",
		 function );

		return( -1 );
	}
	if( path_size == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid path size.",
		 function );

		return( -1 );
	}
	if( libphdi_image_values_get_utf8_filename_size(
	     image_values,
	     &utf8_filename_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve UTF-8 extent filename size.",
		 function );

		goto on_error;
	}
	if( ( utf8_filename_size == 0 )
	 || ( utf8_filename_size > MEMORY_MAXIMUM_ALLOCATION_SIZE ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid UTF-8 extent filename size value out of bounds.",
		 function );

		goto on_error;
	}
	utf8_filename = (uint8_t *) memory_allocate(
	                             sizeof( uint8_t ) * utf8_filename_size );

	if( utf8_filename == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create UTF-8 extent filename.",
		 function );

		goto on_error;
	}
	if( libphdi_image_values_get_utf8_filename(
	     image_values,
	     utf8_filename,
	     utf8_filename_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve UTF-8 extent filename.",
		 function );

		goto on_error;
	}
	if( libclocale_codepage == 0 )
	{
		narrow_filename      = (char *) utf8_filename;
		narrow_filename_size = utf8_filename_size;
		utf8_filename        = NULL;
	}
	else
	{
		if( libuna_byte_stream_size_from_utf8(
		     utf8_filename,
		     utf8_filename_size,
		     libclocale_codepage,
		     &narrow_filename_size,
		     error ) != 1)
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve narrow extent filename size.",
			 function );

			goto on_error;
		}
		if( ( narrow_filename_size == 0 )
		 || ( narrow_filename_size > ( MEMORY_MAXIMUM_ALLOCATION_SIZE / sizeof( char ) ) ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: invalid narrow extent filename size value out of bounds.",
			 function );

			goto on_error;
		}
		narrow_filename = narrow_string_allocate(
		                   narrow_filename_size );

		if( narrow_filename == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to create narrow extent filename.",
			 function );

			goto on_error;
		}
		if( libuna_byte_stream_copy_from_utf8(
		     (uint8_t *) narrow_filename,
		     narrow_filename_size,
		     libclocale_codepage,
		     utf8_filename,
		     utf8_filename_size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve narrow extent filename.",
			 function );

			goto on_error;
		}
	}
	extent_data_filename = narrow_string_search_character_reverse(
	                        narrow_filename,
	                        (int) LIBCPATH_SEPARATOR,
	                        narrow_filename_size );

	if( extent_data_filename != NULL )
	{
		/* Ignore the path separator itself
		 */
		extent_data_filename++;

		extent_data_filename_size = (size_t) ( extent_data_filename - narrow_filename );
	}
	else
	{
		extent_data_filename      = narrow_filename;
		extent_data_filename_size = narrow_filename_size;
	}
	if( libphdi_data_files_join_extent_data_file_path(
	     data_files,
	     extent_data_filename,
	     extent_data_filename_size,
	     path,
	     path_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to join extent path.",
		 function );

		goto on_error;
	}
	memory_free(
	 narrow_filename );

	return( 1 );

on_error:
	if( narrow_filename != NULL )
	{
		memory_free(
		 narrow_filename );
	}
	if( utf8_filename != NULL )
	{
		memory_free(
		 utf8_filename );
	}
	return( -1 );
}

/* Joins an extent data filename with the data files path
 * Returns 1 if successful or -1 on error
 */
int libphdi_data_files_join_extent_data_file_path(
     libphdi_data_files_t *data_files,
     const char *extent_data_filename,
     size_t extent_data_filename_size,
     char **path,
     size_t *path_size,
     libcerror_error_t **error )
{
	static char *function   = "libphdi_data_files_join_extent_data_file_path";
	char *narrow_path       = NULL;
	char *safe_path         = NULL;
	size_t narrow_path_size = 0;
	size_t safe_path_size   = 0;

	if( data_files == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid data files.",
		 function );

		return( -1 );
	}
	if( extent_data_filename == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid extent data filename.",
		 function );

		return( -1 );
	}
	if( path == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid path.",
		 function );

		return( -1 );
	}
	if( path_size == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid path size.",
		 function );

		return( -1 );
	}
	if( data_files->path == NULL )
	{
		if( ( extent_data_filename_size == 0 )
		 || ( extent_data_filename_size > ( MEMORY_MAXIMUM_ALLOCATION_SIZE / sizeof( char ) ) ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: invalid extent data filename size value out of bounds.",
			 function );

			goto on_error;
		}
		safe_path = narrow_string_allocate(
		             extent_data_filename_size );

		if( safe_path == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to create path.",
			 function );

			goto on_error;
		}
		safe_path_size = extent_data_filename_size;

		if( narrow_string_copy(
		     safe_path,
		     extent_data_filename,
		     extent_data_filename_size ) == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
			 "%s: unable to copy path.",
			 function );

			goto on_error;
		}
		safe_path[ safe_path_size - 1 ] = 0;
	}
	else
	{
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
		if( libphdi_data_files_get_path_size(
		     data_files,
		     &narrow_path_size,
		     error ) != 1)
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve narrow data files path size.",
			 function );

			goto on_error;
		}
		if( ( narrow_path_size == 0 )
		 || ( narrow_path_size > ( MEMORY_MAXIMUM_ALLOCATION_SIZE / sizeof( char ) ) ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: invalid narrow data files path size value out of bounds.",
			 function );

			goto on_error;
		}
		narrow_path = narrow_string_allocate(
		               narrow_path_size );

		if( narrow_path == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to create narrow data files path.",
			 function );

			goto on_error;
		}
		if( libphdi_data_files_get_path(
		     data_files,
		     narrow_path,
		     narrow_path_size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve narrow path.",
			 function );

			goto on_error;
		}
#else
		narrow_path      = (char *) data_files->path;
		narrow_path_size = data_files->path_size;

#endif /* defined( HAVE_WIDE_SYSTEM_CHARACTER ) */

		if( libcpath_path_join(
		     &safe_path,
		     &safe_path_size,
		     narrow_path,
		     narrow_path_size - 1,
		     extent_data_filename,
		     extent_data_filename_size - 1,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create path.",
			 function );

			goto on_error;
		}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
		memory_free(
		 narrow_path );
#endif
	}
	*path      = safe_path;
	*path_size = safe_path_size;

	return( 1 );

on_error:
	if( safe_path != NULL )
	{
		memory_free(
		 safe_path );
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	if( narrow_path != NULL )
	{
		memory_free(
		 narrow_path );
	}
#endif
	return( -1 );
}

#if defined( HAVE_WIDE_CHARACTER_TYPE )

/* Retrieves the path of an extent data file
 * Returns 1 if successful or -1 on error
 */
int libphdi_data_files_get_extent_data_file_path_wide(
     libphdi_data_files_t *data_files,
     libphdi_image_values_t *image_values,
     wchar_t **path,
     size_t *path_size,
     libcerror_error_t **error )
{
	uint8_t *utf8_filename           = NULL;
	wchar_t *extent_data_filename    = NULL;
	wchar_t *wide_filename           = NULL;
	static char *function            = "libphdi_data_files_get_extent_data_file_path_wide";
	size_t extent_data_filename_size = 0;
	size_t utf8_filename_size        = 0;
	size_t wide_filename_size        = 0;
	int result                       = 0;

	if( data_files == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid data files.",
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
	if( path == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid path.",
		 function );

		return( -1 );
	}
	if( path_size == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid path size.",
		 function );

		return( -1 );
	}
	if( libphdi_image_values_get_utf8_filename_size(
	     image_values,
	     &utf8_filename_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve UTF-8 extent filename size.",
		 function );

		goto on_error;
	}
	if( ( utf8_filename_size == 0 )
	 || ( utf8_filename_size > MEMORY_MAXIMUM_ALLOCATION_SIZE ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid UTF-8 extent filename size value out of bounds.",
		 function );

		goto on_error;
	}
	utf8_filename = (uint8_t *) memory_allocate(
	                             sizeof( uint8_t ) * utf8_filename_size );

	if( utf8_filename == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create UTF-8 extent filename.",
		 function );

		goto on_error;
	}
	if( libphdi_image_values_get_utf8_filename(
	     image_values,
	     utf8_filename,
	     utf8_filename_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve UTF-8 extent filename.",
		 function );

		goto on_error;
	}
#if SIZEOF_WCHAR_T == 4
	result = libuna_utf32_string_size_from_utf8(
	          utf8_filename,
	          utf8_filename_size,
	          &wide_filename_size,
	          error );
#elif SIZEOF_WCHAR_T == 2
	result = libuna_utf16_string_size_from_utf8(
	          utf8_filename,
	          utf8_filename_size,
	          &wide_filename_size,
	          error );
#else
#error Unsupported size of wchar_t
#endif /* SIZEOF_WCHAR_T */

	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve wide extent filename size.",
		 function );

		goto on_error;
	}
	if( ( wide_filename_size == 0 )
	 || ( wide_filename_size > ( MEMORY_MAXIMUM_ALLOCATION_SIZE / sizeof( wchar_t ) ) ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid wide extent filename size value out of bounds.",
		 function );

		goto on_error;
	}
	wide_filename = wide_string_allocate(
	                 wide_filename_size );

	if( wide_filename == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create wide extent filename.",
		 function );

		goto on_error;
	}
#if SIZEOF_WCHAR_T == 4
	result = libuna_utf32_string_copy_from_utf8(
	          (libuna_utf32_character_t *) wide_filename,
	          wide_filename_size,
	          utf8_filename,
	          utf8_filename_size,
	          error );
#elif SIZEOF_WCHAR_T == 2
	result = libuna_utf16_string_copy_from_utf8(
	          (libuna_utf16_character_t *) wide_filename,
	          wide_filename_size,
	          utf8_filename,
	          utf8_filename_size,
	          error );
#else
#error Unsupported size of wchar_t
#endif /* SIZEOF_WCHAR_T */

	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve wide extent filename.",
		 function );

		goto on_error;
	}
	memory_free(
	 utf8_filename );

	utf8_filename = NULL;

	extent_data_filename = wide_string_search_character_reverse(
	                        wide_filename,
	                        (wint_t) LIBCPATH_SEPARATOR,
	                        wide_filename_size );

	if( extent_data_filename != NULL )
	{
		/* Ignore the path separator itself
		 */
		extent_data_filename++;

		extent_data_filename_size = (size_t) ( extent_data_filename - wide_filename );
	}
	else
	{
		extent_data_filename      = wide_filename;
		extent_data_filename_size = wide_filename_size;
	}
	if( libphdi_data_files_join_extent_data_file_path_wide(
	     data_files,
	     extent_data_filename,
	     extent_data_filename_size,
	     path,
	     path_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to join extent path.",
		 function );

		goto on_error;
	}
	memory_free(
	 wide_filename );

	return( 1 );

on_error:
	if( wide_filename != NULL )
	{
		memory_free(
		 wide_filename );
	}
	if( utf8_filename != NULL )
	{
		memory_free(
		 utf8_filename );
	}
	return( -1 );
}

/* Joins an extent data filename with the data files path
 * Returns 1 if successful or -1 on error
 */
int libphdi_data_files_join_extent_data_file_path_wide(
     libphdi_data_files_t *data_files,
     const wchar_t *extent_data_filename,
     size_t extent_data_filename_size,
     wchar_t **path,
     size_t *path_size,
     libcerror_error_t **error )
{
	wchar_t *safe_path    = NULL;
	wchar_t *wide_path    = NULL;
	static char *function = "libphdi_data_files_join_extent_data_file_path_wide";
	size_t safe_path_size = 0;
	size_t wide_path_size = 0;

	if( data_files == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid data files.",
		 function );

		return( -1 );
	}
	if( extent_data_filename == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid extent data filename.",
		 function );

		return( -1 );
	}
	if( path == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid path.",
		 function );

		return( -1 );
	}
	if( path_size == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid path size.",
		 function );

		return( -1 );
	}
	if( data_files->path == NULL )
	{
		if( ( extent_data_filename_size == 0 )
		 || ( extent_data_filename_size > ( MEMORY_MAXIMUM_ALLOCATION_SIZE / sizeof( wchar_t ) ) ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: invalid extent data filename size value out of bounds.",
			 function );

			goto on_error;
		}
		safe_path = wide_string_allocate(
		             extent_data_filename_size );

		if( safe_path == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to create path.",
			 function );

			goto on_error;
		}
		safe_path_size = extent_data_filename_size;

		if( wide_string_copy(
		     safe_path,
		     extent_data_filename,
		     extent_data_filename_size ) == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
			 "%s: unable to copy path.",
			 function );

			goto on_error;
		}
		safe_path[ safe_path_size - 1 ] = 0;
	}
	else
	{
#if !defined( HAVE_WIDE_SYSTEM_CHARACTER )
		if( libphdi_data_files_get_path_size_wide(
		     data_files,
		     &wide_path_size,
		     error ) != 1)
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve wide data files path size.",
			 function );

			goto on_error;
		}
		if( ( wide_path_size == 0 )
		 || ( wide_path_size > ( MEMORY_MAXIMUM_ALLOCATION_SIZE / sizeof( wchar_t ) ) ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: invalid wide data files path size value out of bounds.",
			 function );

			goto on_error;
		}
		wide_path = wide_string_allocate(
		             wide_path_size );

		if( wide_path == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to create wide data files path.",
			 function );

			goto on_error;
		}
		if( libphdi_data_files_get_path_wide(
		     data_files,
		     wide_path,
		     wide_path_size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve wide path.",
			 function );

			goto on_error;
		}
#else
		wide_path      = (wchar_t *) data_files->path;
		wide_path_size = data_files->path_size;

#endif /* !defined( HAVE_WIDE_SYSTEM_CHARACTER ) */

		if( libcpath_path_join_wide(
		     &safe_path,
		     &safe_path_size,
		     wide_path,
		     wide_path_size - 1,
		     extent_data_filename,
		     extent_data_filename_size - 1,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create path.",
			 function );

			goto on_error;
		}
#if !defined( HAVE_WIDE_SYSTEM_CHARACTER )
		memory_free(
		 wide_path );
#endif
	}
	*path      = safe_path;
	*path_size = safe_path_size;

	return( 1 );

on_error:
	if( safe_path != NULL )
	{
		memory_free(
		 safe_path );
	}
#if !defined( HAVE_WIDE_SYSTEM_CHARACTER )
	if( wide_path != NULL )
	{
		memory_free(
		 wide_path );
	}
#endif
	return( -1 );
}

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

