/*
 * Extent table functions
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
#include "libphdi_extent_table.h"
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

/* Creates an extent table
 * Make sure the value extent_table is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libphdi_extent_table_initialize(
     libphdi_extent_table_t **extent_table,
     libcerror_error_t **error )
{
	static char *function = "libphdi_extent_table_initialize";

	if( extent_table == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid extent table.",
		 function );

		return( -1 );
	}
	if( *extent_table != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid extent table value already set.",
		 function );

		return( -1 );
	}
	*extent_table = memory_allocate_structure(
	                 libphdi_extent_table_t );

	if( *extent_table == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create extent table.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *extent_table,
	     0,
	     sizeof( libphdi_extent_table_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear extent table.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *extent_table != NULL )
	{
		memory_free(
		 *extent_table );

		*extent_table = NULL;
	}
	return( -1 );
}

/* Frees an extent table
 * Returns 1 if successful or -1 on error
 */
int libphdi_extent_table_free(
     libphdi_extent_table_t **extent_table,
     libcerror_error_t **error )
{
	static char *function = "libphdi_extent_table_free";
	int result            = 1;

	if( extent_table == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid extent table.",
		 function );

		return( -1 );
	}
	if( *extent_table != NULL )
	{
		if( libphdi_extent_table_clear(
		     *extent_table,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to clear extent table.",
			 function );

			result = -1;
		}
		memory_free(
		 *extent_table );

		*extent_table = NULL;
	}
	return( result );
}

/* Clears the extent table
 * Returns 1 if successful or -1 on error
 */
int libphdi_extent_table_clear(
     libphdi_extent_table_t *extent_table,
     libcerror_error_t **error )
{
	static char *function = "libphdi_extent_table_clear";
	int result            = 1;

	if( extent_table == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid extent table.",
		 function );

		return( -1 );
	}
	if( extent_table->extent_files_list != NULL )
	{
		if( libfdata_list_free(
		     &( extent_table->extent_files_list ),
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free extent files list.",
			 function );

			result = -1;
		}
	}
	if( extent_table->extent_files_cache != NULL )
	{
		if( libfcache_cache_free(
		     &( extent_table->extent_files_cache ),
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free extent files cache.",
			 function );

			result = -1;
		}
	}
	if( memory_set(
	     extent_table,
	     0,
	     sizeof( libphdi_extent_table_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to extent table.",
		 function );

		result = -1;
	}
	return( result );
}

/* Initializes the extents
 * Returns 1 if successful or -1 on error
 */
int libphdi_extent_table_initialize_extents(
     libphdi_extent_table_t *extent_table,
     libphdi_io_handle_t *io_handle,
     int disk_type,
     libcerror_error_t **error )
{
	static char *function = "libphdi_extent_table_initialize_extents";
	int result            = 0;

	if( extent_table == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid extent table.",
		 function );

		return( -1 );
	}
	if( ( disk_type != LIBPHDI_DISK_TYPE_EXPANDING )
	 && ( disk_type != LIBPHDI_DISK_TYPE_FIXED ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported disk type.",
		 function );

		return( -1 );
	}
	if( disk_type == LIBPHDI_DISK_TYPE_FIXED )
	{
		result = libfdata_stream_initialize(
		          &( extent_table->extent_files_stream ),
		          (intptr_t *) io_handle,
		          NULL,
		          NULL,
		          NULL,
		          (ssize_t (*)(intptr_t *, intptr_t *, int, int, uint8_t *, size_t, uint32_t, uint8_t, libcerror_error_t **)) &libphdi_storage_image_read_segment_data,
		          NULL,
		          (off64_t (*)(intptr_t *, intptr_t *, int, int, off64_t, libcerror_error_t **)) &libphdi_storage_image_seek_segment_offset,
		          LIBFDATA_DATA_HANDLE_FLAG_NON_MANAGED,
		          error );

		if( result != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create extent files stream.",
			 function );

			goto on_error;
		}
	}
	else if( disk_type == LIBPHDI_DISK_TYPE_EXPANDING )
	{
		result = libfdata_list_initialize(
		          &( extent_table->extent_files_list ),
		          (intptr_t *) io_handle,
		          NULL,
		          NULL,
		          (int (*)(intptr_t *, intptr_t *, libfdata_list_element_t *, libfdata_cache_t *, int, off64_t, size64_t, uint32_t, uint8_t, libcerror_error_t **)) &libphdi_storage_image_read_element_data,
		          NULL,
		          LIBFDATA_DATA_HANDLE_FLAG_NON_MANAGED,
		          error );

		if( result != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create extent files list.",
			 function );

			goto on_error;
		}
		result = libfcache_cache_initialize(
			  &( extent_table->extent_files_cache ),
			  LIBPHDI_MAXIMUM_CACHE_ENTRIES_EXTENT_FILES,
			  error );

		if( result != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create extent files cache.",
			 function );

			goto on_error;
		}
	}
	extent_table->disk_type = disk_type;

	return( 1 );

on_error:
	if( extent_table->extent_files_list != NULL )
	{
		libfdata_list_free(
		 &( extent_table->extent_files_list ),
		 NULL );
	}
	if( extent_table->extent_files_stream != NULL )
	{
		libfdata_stream_free(
		 &( extent_table->extent_files_stream ),
		 NULL );
	}
	return( -1 );
}

/* Retrieves an extent file at a specific offset from the extent table
 * Returns 1 if successful or -1 on error
 */
int libphdi_extent_table_get_extent_file_at_offset(
     libphdi_extent_table_t *extent_table,
     off64_t offset,
     libbfio_pool_t *file_io_pool,
     int *extent_index,
     off64_t *extent_file_data_offset,
     libphdi_storage_image_t **extent_file,
     libcerror_error_t **error )
{
	static char *function = "libphdi_extent_table_get_extent_file_at_offset";

	if( extent_table == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid extent table.",
		 function );

		return( -1 );
	}
	if( libfdata_list_get_element_value_at_offset(
	     extent_table->extent_files_list,
	     (intptr_t *) file_io_pool,
	     (libfdata_cache_t *) extent_table->extent_files_cache,
	     offset,
	     extent_index,
	     extent_file_data_offset,
	     (intptr_t **) extent_file,
	     0,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve element at offset: %" PRIi64 " (0x%08" PRIx64 ") from extent files list.",
		 function,
		 offset,
		 offset );

		return( -1 );
	}
	return( 1 );
}

/* Appends an extent to the extent table based on the image values
 * Returns 1 if successful or -1 on error
 */
int libphdi_extent_table_append_extent(
     libphdi_extent_table_t *extent_table,
     int image_type,
     int file_io_pool_entry,
     size64_t extent_file_size,
     off64_t extent_offset,
     size64_t extent_size,
     libcerror_error_t **error )
{
	static char *function = "libphdi_extent_table_append_extent";
	int element_index     = 0;
	int segment_index     = 0;

	if( extent_table == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid extent table.",
		 function );

		return( -1 );
	}
	if( extent_table->image_type == 0 )
	{
		if( image_type == LIBPHDI_IMAGE_TYPE_COMPRESSED )
		{
			if( extent_table->disk_type != LIBPHDI_DISK_TYPE_EXPANDING )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
				 "%s: image type not supported for disk type.",
				 function );

				return( -1 );
			}
		}
		else if( image_type == LIBPHDI_IMAGE_TYPE_PLAIN )
		{
			if( extent_table->disk_type != LIBPHDI_DISK_TYPE_FIXED )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
				 "%s: image type not supported for disk type.",
				 function );

				return( -1 );
			}
		}
		else
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
			 "%s: unsupported image type.",
			 function );

			return( -1 );
		}
		extent_table->image_type = image_type;
	}
	else if( extent_table->image_type != image_type )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: mixed image types not supported.",
		 function );

		return( -1 );
	}
	if( image_type == LIBPHDI_IMAGE_TYPE_PLAIN )
	{
		if( ( extent_offset < 0 )
		 || ( (size64_t) extent_offset >= extent_file_size ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: invalid extent offset value out of bounds.",
			 function );

			return( -1 );
		}
		if( extent_size > ( extent_file_size - (size64_t) extent_offset ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: invalid extent size value out of bounds.",
			 function );

			return( -1 );
		}
		if( libfdata_stream_append_segment(
		     extent_table->extent_files_stream,
		     &segment_index,
		     file_io_pool_entry,
		     extent_offset,
		     extent_size,
		     0,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
			 "%s: unable to append segment to extent files stream.",
			 function );

			return( -1 );
		}
	}
	else if( image_type == LIBPHDI_IMAGE_TYPE_COMPRESSED )
	{
		if( extent_offset != 0 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: invalid extent offset value out of bounds.",
			 function );

			return( -1 );
		}
		if( libfdata_list_append_element_with_mapped_size(
		     extent_table->extent_files_list,
		     &element_index,
		     file_io_pool_entry,
		     0,
		     extent_file_size,
		     0,
		     extent_size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
			 "%s: unable to append element to extent files list.",
			 function );

			return( -1 );
		}
	}
	return( 1 );
}

