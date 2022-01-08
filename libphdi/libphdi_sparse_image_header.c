/*
 * Sparse image header functions
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

#include "libphdi_libbfio.h"
#include "libphdi_libcerror.h"
#include "libphdi_libcnotify.h"
#include "libphdi_sparse_image_header.h"

#include "phdi_sparse_image_header.h"

const uint8_t phdi_sparse_image_signature[ 16 ] = {
	'W', 'i', 't', 'h', 'o', 'u', 't', 'F', 'r', 'e', 'e', 'S', 'p', 'a', 'c', 'e' };

/* Creates sparse image header
 * Make sure the value sparse_image_header is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libphdi_sparse_image_header_initialize(
     libphdi_sparse_image_header_t **sparse_image_header,
     libcerror_error_t **error )
{
	static char *function = "libphdi_sparse_image_header_initialize";

	if( sparse_image_header == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid sparse image header.",
		 function );

		return( -1 );
	}
	if( *sparse_image_header != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid sparse image header value already set.",
		 function );

		return( -1 );
	}
	*sparse_image_header = memory_allocate_structure(
	                        libphdi_sparse_image_header_t );

	if( *sparse_image_header == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create sparse image header.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *sparse_image_header,
	     0,
	     sizeof( libphdi_sparse_image_header_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear sparse image header.",
		 function );

		memory_free(
		 *sparse_image_header );

		*sparse_image_header = NULL;

		return( -1 );
	}
	return( 1 );

on_error:
	if( *sparse_image_header != NULL )
	{
		memory_free(
		 *sparse_image_header );

		*sparse_image_header = NULL;
	}
	return( -1 );
}

/* Frees a sparse image header
 * Returns 1 if successful or -1 on error
 */
int libphdi_sparse_image_header_free(
     libphdi_sparse_image_header_t **sparse_image_header,
     libcerror_error_t **error )
{
	static char *function = "libphdi_sparse_image_header_free";

	if( sparse_image_header == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid sparse image header.",
		 function );

		return( -1 );
	}
	if( *sparse_image_header != NULL )
	{
		memory_free(
		 *sparse_image_header );

		*sparse_image_header = NULL;
	}
	return( 1 );
}

/* Reads the sparse image header data
 * Returns 1 if successful, 0 if the signature does not match or -1 on error
 */
int libphdi_sparse_image_header_read_data(
     libphdi_sparse_image_header_t *sparse_image_header,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error )
{
	static char *function   = "libphdi_sparse_image_header_read_data";
	uint32_t format_version = 0;

#if defined( HAVE_DEBUG_OUTPUT )
	uint32_t value_32bit   = 0;
#endif

	if( sparse_image_header == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid sparse image header.",
		 function );

		return( -1 );
	}
	if( data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid data.",
		 function );

		return( -1 );
	}
	if( ( data_size < sizeof( phdi_sparse_image_header_t ) )
	 || ( data_size > (size_t) SSIZE_MAX ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid data size value out of bounds.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: sparse image header data:\n",
		 function );
		libcnotify_print_data(
		 data,
		 sizeof( phdi_sparse_image_header_t ),
		 0 );
	}
#endif
/* TODO add support for "WithouFreSpacExt" */

	if( memory_compare(
	     ( (phdi_sparse_image_header_t *) data )->signature,
	     phdi_sparse_image_signature,
	     16 ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported signature.",
		 function );

		return( -1 );
	}
	byte_stream_copy_to_uint32_little_endian(
	 ( (phdi_sparse_image_header_t *) data )->format_version,
	 format_version );

	byte_stream_copy_to_uint32_little_endian(
	 ( (phdi_sparse_image_header_t *) data )->block_size,
	 sparse_image_header->block_size );

	byte_stream_copy_to_uint32_little_endian(
	 ( (phdi_sparse_image_header_t *) data )->number_of_allocation_table_entries,
	 sparse_image_header->number_of_allocation_table_entries );

	byte_stream_copy_to_uint64_little_endian(
	 ( (phdi_sparse_image_header_t *) data )->number_of_sectors,
	 sparse_image_header->number_of_sectors );

	byte_stream_copy_to_uint32_little_endian(
	 ( (phdi_sparse_image_header_t *) data )->data_start_sector,
	 sparse_image_header->data_start_sector );

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: signature\t\t\t\t: %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",
		 function,
		 ( (phdi_sparse_image_header_t *) data )->signature[ 0 ],
		 ( (phdi_sparse_image_header_t *) data )->signature[ 1 ],
		 ( (phdi_sparse_image_header_t *) data )->signature[ 2 ],
		 ( (phdi_sparse_image_header_t *) data )->signature[ 3 ],
		 ( (phdi_sparse_image_header_t *) data )->signature[ 4 ],
		 ( (phdi_sparse_image_header_t *) data )->signature[ 5 ],
		 ( (phdi_sparse_image_header_t *) data )->signature[ 6 ],
		 ( (phdi_sparse_image_header_t *) data )->signature[ 7 ],
		 ( (phdi_sparse_image_header_t *) data )->signature[ 8 ],
		 ( (phdi_sparse_image_header_t *) data )->signature[ 9 ],
		 ( (phdi_sparse_image_header_t *) data )->signature[ 10 ],
		 ( (phdi_sparse_image_header_t *) data )->signature[ 11 ],
		 ( (phdi_sparse_image_header_t *) data )->signature[ 12 ],
		 ( (phdi_sparse_image_header_t *) data )->signature[ 13 ],
		 ( (phdi_sparse_image_header_t *) data )->signature[ 14 ],
		 ( (phdi_sparse_image_header_t *) data )->signature[ 15 ] );

		libcnotify_printf(
		 "%s: format version\t\t\t\t: %" PRIu32 "\n",
		 function,
		 format_version );

		byte_stream_copy_to_uint32_little_endian(
		 ( (phdi_sparse_image_header_t *) data )->number_of_heads,
		 value_32bit );
		libcnotify_printf(
		 "%s: number of heads\t\t\t\t: %" PRIu32 "\n",
		 function,
		 value_32bit );

		byte_stream_copy_to_uint32_little_endian(
		 ( (phdi_sparse_image_header_t *) data )->number_of_cylinders,
		 value_32bit );
		libcnotify_printf(
		 "%s: number of cylinders\t\t\t: %" PRIu32 "\n",
		 function,
		 value_32bit );

		libcnotify_printf(
		 "%s: block size\t\t\t\t: %" PRIu32 "\n",
		 function,
		 sparse_image_header->block_size );

		libcnotify_printf(
		 "%s: number of allocation table entries\t: %" PRIu32 "\n",
		 function,
		 sparse_image_header->number_of_allocation_table_entries );

		libcnotify_printf(
		 "%s: number of sectors\t\t\t: %" PRIu64 "\n",
		 function,
		 sparse_image_header->number_of_sectors );

		byte_stream_copy_to_uint32_little_endian(
		 ( (phdi_sparse_image_header_t *) data )->unknown1,
		 value_32bit );
		libcnotify_printf(
		 "%s: unknown1\t\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		libcnotify_printf(
		 "%s: data start sector\t\t\t: %" PRIu32 "\n",
		 function,
		 sparse_image_header->data_start_sector );

		libcnotify_printf(
		 "%s: unknown2:\n",
		 function );
		libcnotify_print_data(
		 (uint8_t *) ( (phdi_sparse_image_header_t *) data )->unknown2,
		 12,
		 0 );
	}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

	if( format_version != 2 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported format version: %" PRIu32 ".",
		 function,
		 format_version );

		return( -1 );
	}
	if( sparse_image_header->block_size == 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid block size value out of bounds.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Reads the sparse image header
 * Returns 1 if successful, 0 if the signature does not match or -1 on error
 */
int libphdi_sparse_image_header_read_file_io_handle(
     libphdi_sparse_image_header_t *sparse_image_header,
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error )
{
	uint8_t sparse_image_header_data[ sizeof( phdi_sparse_image_header_t ) ];

	static char *function = "libphdi_sparse_image_header_read_file_io_handle";
	ssize_t read_count    = 0;

	if( sparse_image_header == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid sparse image header.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: reading sparse image header at offset: 0 (0x00000000)\n",
		 function );
	}
#endif
	read_count = libbfio_handle_read_buffer_at_offset(
	              file_io_handle,
	              sparse_image_header_data,
	              sizeof( phdi_sparse_image_header_t ),
	              0,
	              error );

	if( read_count != (ssize_t) sizeof( phdi_sparse_image_header_t ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read sparse image header data at offset: 0 (0x00000000).",
		 function );

		return( -1 );
	}
	if( libphdi_sparse_image_header_read_data(
	     sparse_image_header,
	     sparse_image_header_data,
	     sizeof( phdi_sparse_image_header_t ),
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read sparse image header.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the block size
 * Returns 1 if successful or -1 on error
 */
int libphdi_sparse_image_header_get_block_size(
     libphdi_sparse_image_header_t *sparse_image_header,
     size64_t *block_size,
     libcerror_error_t **error )
{
	static char *function = "libphdi_sparse_image_header_get_block_size";

	if( sparse_image_header == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid sparse image header.",
		 function );

		return( -1 );
	}
	if( block_size == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid block size.",
		 function );

		return( -1 );
	}
	*block_size = (size64_t) sparse_image_header->block_size * 512;

	return( 1 );
}

