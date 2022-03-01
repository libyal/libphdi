/*
 * Storage image functions
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
#include <byte_stream.h>
#include <memory.h>
#include <types.h>

#include "libphdi_block_descriptor.h"
#include "libphdi_block_tree.h"
#include "libphdi_libbfio.h"
#include "libphdi_libcerror.h"
#include "libphdi_libcnotify.h"
#include "libphdi_libfdata.h"
#include "libphdi_storage_image.h"
#include "libphdi_unused.h"

/* Creates a storage image
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
		if( ( *storage_image )->block_tree != NULL )
		{
			if( libphdi_block_tree_free(
			     &( ( *storage_image )->block_tree ),
			     (int (*)(intptr_t **, libcerror_error_t **)) &libphdi_block_descriptor_free,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
				 "%s: unable to free block tree.",
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

/* Reads the file header from the storage image using the file IO pool entry
 * Returns 1 if successful or -1 on error
 */
int libphdi_storage_image_read_file_header(
     libphdi_storage_image_t *storage_image,
     libbfio_pool_t *file_io_pool,
     int file_io_pool_entry,
     libcerror_error_t **error )
{
	libbfio_handle_t *file_io_handle                   = NULL;
	libphdi_sparse_image_header_t *sparse_image_header = NULL;
	static char *function                              = "libphdi_storage_image_read_file_header";
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

/* Reads the block allocation table from the storage image using the file IO pool entry
 * Returns 1 if successful or -1 on error
 */
int libphdi_storage_image_read_block_allocation_table(
     libphdi_storage_image_t *storage_image,
     libbfio_pool_t *file_io_pool,
     int file_io_pool_entry,
     libcerror_error_t **error )
{
	libphdi_block_descriptor_t *existing_block_descriptor = NULL;
	libphdi_block_descriptor_t *new_block_descriptor      = NULL;
	libphdi_block_tree_node_t *leaf_block_tree_node       = NULL;
	uint8_t *block_allocation_table_data                  = NULL;
	static char *function                                 = "libphdi_storage_image_read_block_allocation_table";
	size64_t block_size                                   = 0;
	size_t block_allocation_table_data_size               = 0;
	size_t data_offset                                    = 0;
	ssize_t read_count                                    = 0;
	off64_t file_offset                                   = 0;
	off64_t logical_offset                                = 0;
	uint32_t block_allocation_table_entry                 = 0;
	int leaf_value_index                                  = 0;

#if defined( HAVE_DEBUG_OUTPUT )
	int entry_index                                       = 0;
#endif

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
	if( storage_image->block_tree != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid storage image - block tree value already set.",
		 function );

		return( -1 );
	}
	if( libphdi_sparse_image_header_get_block_size(
	     storage_image->sparse_image_header,
	     &block_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve block size.",
		 function );

		return( -1 );
	}
	if( ( storage_image->sparse_image_header->number_of_allocation_table_entries == 0 )
	 || ( storage_image->sparse_image_header->number_of_allocation_table_entries > ( (size_t) MEMORY_MAXIMUM_ALLOCATION_SIZE / 4 ) ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid storage image - invalid sparse image header value - number of allocation table entries value out of bounds.",
		 function );

		return( -1 );
	}
	block_allocation_table_data_size = (size_t) storage_image->sparse_image_header->number_of_allocation_table_entries * 4;

	block_allocation_table_data = (uint8_t *) memory_allocate(
	                                           sizeof( uint8_t ) * block_allocation_table_data_size );

	if( block_allocation_table_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create block allocation table data.",
		 function );

		goto on_error;
	}
	read_count = libbfio_pool_read_buffer(
	              file_io_pool,
	              file_io_pool_entry,
	              block_allocation_table_data,
	              block_allocation_table_data_size,
	              error );

	if( read_count != (ssize_t) block_allocation_table_data_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read block allocation table data from file IO pool entry: %d.",
		 function,
		 file_io_pool_entry );

		goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: block allocation table data:\n",
		 function );
		libcnotify_print_data(
		 block_allocation_table_data,
		 block_allocation_table_data_size,
		 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );
	}
#endif
	if( libphdi_block_tree_initialize(
	     &( storage_image->block_tree ),
	     (size64_t) storage_image->sparse_image_header->number_of_sectors * 512,
	     block_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create block tree.",
		 function );

		goto on_error;
	}
	while( data_offset < block_allocation_table_data_size )
	{
		byte_stream_copy_to_uint32_little_endian(
		 &( block_allocation_table_data[ data_offset ] ),
		 block_allocation_table_entry );

		data_offset += 4;

		if( block_allocation_table_entry != 0 )
		{
			file_offset = (off64_t) block_allocation_table_entry * 512;

#if defined( HAVE_DEBUG_OUTPUT )
			if( libcnotify_verbose != 0 )
			{
				libcnotify_printf(
				 "%s: entry index\t: %d\n",
				 function,
				 entry_index );

				libcnotify_printf(
				 "%s: entry offset\t: %" PRIi64 " (0x%08" PRIx64 ")\n",
				 function,
				 logical_offset,
				 logical_offset );

				libcnotify_printf(
				 "%s: entry value\t: %" PRIu32 "\n",
				 function,
				 block_allocation_table_entry );

				libcnotify_printf(
				 "%s: file offset\t: %" PRIi64 " (0x%08" PRIx64 ")\n",
				 function,
				 (off64_t) file_offset,
				 (off64_t) file_offset );

				libcnotify_printf(
				 "\n" );
			}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

			if( libphdi_block_descriptor_initialize(
			     &new_block_descriptor,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
				 "%s: unable to create block descriptor.",
				 function );

				goto on_error;
			}
			new_block_descriptor->file_io_pool_entry = file_io_pool_entry;
			new_block_descriptor->file_offset        = file_offset;

			if( libphdi_block_tree_insert_block_descriptor_by_offset(
			     storage_image->block_tree,
			     logical_offset,
			     new_block_descriptor,
			     &leaf_value_index,
			     &leaf_block_tree_node,
			     &existing_block_descriptor,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
				 "%s: unable to insert block descriptor in block tree.",
				 function );

				goto on_error;
			}
			new_block_descriptor = NULL;
		}
		logical_offset += (off64_t) block_size;

#if defined( HAVE_DEBUG_OUTPUT )
		entry_index++;
#endif
	}
	memory_free(
	 block_allocation_table_data );

	return( 1 );

on_error:
	if( new_block_descriptor != NULL )
	{
		libphdi_block_descriptor_free(
		 &new_block_descriptor,
		 NULL );
	}
	if( storage_image->block_tree != NULL )
	{
		libphdi_block_tree_free(
		 &( storage_image->block_tree ),
		 (int (*)(intptr_t **, libcerror_error_t **)) &libphdi_block_descriptor_free,
		 NULL );
	}
	if( block_allocation_table_data != NULL )
	{
		memory_free(
		 block_allocation_table_data );
	}
	return( -1 );
}

/* Retrieves the block size
 * Returns 1 if successful or -1 on error
 */
int libphdi_storage_image_get_block_size(
     libphdi_storage_image_t *storage_image,
     size64_t *block_size,
     libcerror_error_t **error )
{
	static char *function = "libphdi_storage_image_get_block_size";

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
	if( libphdi_sparse_image_header_get_block_size(
	     storage_image->sparse_image_header,
	     block_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve block size.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the block descriptor at a specific offset
 * Returns 1 if successful, 0 if not available or -1 on error
 */
int libphdi_storage_image_get_block_descriptor_at_offset(
     libphdi_storage_image_t *storage_image,
     off64_t offset,
     libphdi_block_descriptor_t **block_descriptor,
     off64_t *block_offset,
     libcerror_error_t **error )
{
	static char *function = "libphdi_storage_image_get_block_descriptor_at_offset";
	int result            = 0;

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
	result = libphdi_block_tree_get_block_descriptor_by_offset(
	          storage_image->block_tree,
	          offset,
	          block_descriptor,
	          block_offset,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve block descriptor for offset: %" PRIi64 " (0x%08" PRIx64 ").",
		 function,
		 offset,
		 offset );

		return( -1 );
	}
	return( result );
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
     off64_t storage_image_offset LIBPHDI_ATTRIBUTE_UNUSED,
     size64_t storage_image_size LIBPHDI_ATTRIBUTE_UNUSED,
     uint32_t element_flags LIBPHDI_ATTRIBUTE_UNUSED,
     uint8_t read_flags LIBPHDI_ATTRIBUTE_UNUSED,
     libcerror_error_t **error )
{
	libphdi_storage_image_t *storage_image = NULL;
	static char *function                  = "libphdi_storage_image_read_element_data";

	LIBPHDI_UNREFERENCED_PARAMETER( data_handle )
	LIBPHDI_UNREFERENCED_PARAMETER( storage_image_offset )
	LIBPHDI_UNREFERENCED_PARAMETER( storage_image_size )
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
	if( libphdi_storage_image_read_file_header(
	     storage_image,
	     file_io_pool,
	     file_io_pool_entry,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read storage image file header.",
		 function );

		goto on_error;
	}
	if( libphdi_storage_image_read_block_allocation_table(
	     storage_image,
	     file_io_pool,
	     file_io_pool_entry,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read storage image block allocation table.",
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

/* Reads segment data into a buffer
 * Callback function for the segments stream
 * Returns the number of bytes read or -1 on error
 */
ssize_t libphdi_storage_image_read_segment_data(
         intptr_t *data_handle LIBPHDI_ATTRIBUTE_UNUSED,
         libbfio_pool_t *file_io_pool,
         int segment_index LIBPHDI_ATTRIBUTE_UNUSED,
         int segment_file_index,
         uint8_t *segment_data,
         size_t segment_data_size,
         uint32_t segment_flags LIBPHDI_ATTRIBUTE_UNUSED,
         uint8_t read_flags LIBPHDI_ATTRIBUTE_UNUSED,
         libcerror_error_t **error )
{
	static char *function = "libphdi_storage_image_read_segment_data";
	ssize_t read_count    = 0;

	LIBPHDI_UNREFERENCED_PARAMETER( data_handle )
	LIBPHDI_UNREFERENCED_PARAMETER( segment_index )
	LIBPHDI_UNREFERENCED_PARAMETER( segment_flags )
	LIBPHDI_UNREFERENCED_PARAMETER( read_flags )

	read_count = libbfio_pool_read_buffer(
	              file_io_pool,
	              segment_file_index,
	              segment_data,
	              segment_data_size,
	              error );

	if( read_count == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read segment data.",
		 function );

		return( -1 );
	}
	return( read_count );
}

/* Seeks a certain segment offset
 * Callback function for the segments stream
 * Returns the offset or -1 on error
 */
off64_t libphdi_storage_image_seek_segment_offset(
         intptr_t *data_handle LIBPHDI_ATTRIBUTE_UNUSED,
         libbfio_pool_t *file_io_pool,
         int segment_index LIBPHDI_ATTRIBUTE_UNUSED,
         int segment_file_index,
         off64_t segment_offset,
         libcerror_error_t **error )
{
	static char *function = "libphdi_storage_image_seek_segment_offset";

	LIBPHDI_UNREFERENCED_PARAMETER( data_handle )
	LIBPHDI_UNREFERENCED_PARAMETER( segment_index )

	segment_offset = libbfio_pool_seek_offset(
	                  file_io_pool,
	                  segment_file_index,
	                  segment_offset,
	                  SEEK_SET,
	                  error );

	if( segment_offset == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to seek segment offset.",
		 function );

		return( -1 );
	}
	return( segment_offset );
}

