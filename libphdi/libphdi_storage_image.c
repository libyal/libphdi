/*
 * Storage image functions
 *
 * Copyright (C) 2015-2020, Joachim Metz <joachim.metz@gmail.com>
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

#include "libphdi_libbfio.h"
#include "libphdi_libcerror.h"
#include "libphdi_libfdata.h"
#include "libphdi_storage_image.h"
#include "libphdi_unused.h"

/* Creates storage image
 * Make sure the value storage_image is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libphdi_storage_image_initialize(
     libphdi_storage_image_t **storage_image,
     libcerror_error_t **error )
{
	static char *function = "libphdi_storage_image_initialize";

	if( storage_image == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid storage image.",
		 function );

		return( -1 );
	}
	if( *storage_image != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid storage image value already set.",
		 function );

		return( -1 );
	}
	*storage_image = memory_allocate_structure(
	                  libphdi_storage_image_t );

	if( *storage_image == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create storage image.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *storage_image,
	     0,
	     sizeof( libphdi_storage_image_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear storage image.",
		 function );

		memory_free(
		 *storage_image );

		*storage_image = NULL;

		return( -1 );
	}
	return( 1 );

on_error:
	if( *storage_image != NULL )
	{
		memory_free(
		 *storage_image );

		*storage_image = NULL;
	}
	return( -1 );
}

/* Frees a storage image
 * Returns 1 if successful or -1 on error
 */
int libphdi_storage_image_free(
     libphdi_storage_image_t **storage_image,
     libcerror_error_t **error )
{
	static char *function = "libphdi_storage_image_free";
	int result            = 1;

	if( storage_image == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid storage image.",
		 function );

		return( -1 );
	}
	if( *storage_image != NULL )
	{
		if( ( *storage_image )->sparse_image_header != NULL )
		{
			if( libphdi_sparse_image_header_free(
			     &( ( *storage_image )->sparse_image_header ),
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
				 "%s: unable to free sparse image header.",
				 function );

				result = -1;
			}
		}
		memory_free(
		 *storage_image );

		*storage_image = NULL;
	}
	return( result );
}

/* Opens a storage image for reading
 * Returns 1 if successful or -1 on error
 */
int libphdi_storage_image_open_read(
     libphdi_storage_image_t *storage_image,
     libbfio_pool_t *file_io_pool,
     int file_io_pool_entry,
     libcerror_error_t **error )
{
	libbfio_handle_t *file_io_handle                   = NULL;
	libphdi_sparse_image_header_t *sparse_image_header = NULL;
	static char *function                              = "libphdi_storage_image_open_read";
	int result                                         = 0;

	if( storage_image == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid storage image.",
		 function );

		return( -1 );
	}
	if( storage_image->sparse_image_header != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid storage image - sparse image header value already set.",
		 function );

		return( -1 );
	}
	if( libbfio_pool_get_handle(
	     file_io_pool,
	     file_io_pool_entry,
	     &file_io_handle,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
		 "%s: unable to retrieve file IO handle: %d from pool.",
		 function,
		 file_io_pool_entry );

		goto on_error;
	}
	if( libphdi_sparse_image_header_initialize(
	     &sparse_image_header,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create sparse image header.",
		 function );

		goto on_error;
	}
	result = libphdi_sparse_image_header_read_file_io_handle(
	          sparse_image_header,
	          file_io_handle,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read from file IO handle.",
		 function );

		goto on_error;
	}
	else if( result == 0 )
	{
		if( libphdi_sparse_image_header_free(
		     &sparse_image_header,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free sparse image header.",
			 function );

			goto on_error;
		}
	}
	storage_image->sparse_image_header = sparse_image_header;

	return( 1 );

on_error:
	if( sparse_image_header != NULL )
	{
		libphdi_sparse_image_header_free(
		 &sparse_image_header,
		 NULL );
	}
	return( -1 );
}

/* Reads a storage image
 * Callback function for the storage images list
 * Returns 1 if successful or -1 on error
 */
int libphdi_storage_image_read_element_data(
     intptr_t *data_handle LIBPHDI_ATTRIBUTE_UNUSED,
     libbfio_pool_t *file_io_pool,
     libfdata_list_element_t *element,
     libfdata_cache_t *storage_image_cache,
     int file_io_pool_entry,
     off64_t storage_image_offset,
     size64_t storage_image_size,
     uint32_t element_flags LIBPHDI_ATTRIBUTE_UNUSED,
     uint8_t read_flags LIBPHDI_ATTRIBUTE_UNUSED,
     libcerror_error_t **error )
{
	libphdi_storage_image_t *storage_image = NULL;
	static char *function                  = "libphdi_storage_image_read_element_data";

	LIBPHDI_UNREFERENCED_PARAMETER( data_handle )
	LIBPHDI_UNREFERENCED_PARAMETER( element_flags )
	LIBPHDI_UNREFERENCED_PARAMETER( read_flags )

	if( libphdi_storage_image_initialize(
	     &storage_image,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create storage image.",
		 function );

		goto on_error;
	}
	if( libphdi_storage_image_open_read(
	     storage_image,
	     file_io_pool,
	     file_io_pool_entry,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to open storage image for reading.",
		 function );

		goto on_error;
	}
	if( libfdata_list_element_set_element_value(
	     element,
	     (intptr_t *) file_io_pool,
	     (libfdata_cache_t *) storage_image_cache,
	     (intptr_t *) storage_image,
	     (int (*)(intptr_t **, libcerror_error_t **)) &libphdi_storage_image_free,
	     LIBFDATA_LIST_ELEMENT_VALUE_FLAG_MANAGED,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set storage image as element value.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( storage_image != NULL )
	{
		libphdi_storage_image_free(
		 &storage_image,
		 NULL );
	}
	return( -1 );
}

