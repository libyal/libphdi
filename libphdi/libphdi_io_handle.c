/*
 * Input/Output (IO) handle functions
 *
 * Copyright (C) 2015-2017, Joachim Metz <joachim.metz@gmail.com>
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This software is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this software.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <common.h>
#include <byte_stream.h>
#include <memory.h>
#include <types.h>

#include "libphdi_definitions.h"
#include "libphdi_io_handle.h"
#include "libphdi_libbfio.h"
#include "libphdi_libcerror.h"
#include "libphdi_libcnotify.h"
#include "libphdi_libfcache.h"
#include "libphdi_libfdata.h"
#include "libphdi_libuna.h"
#include "libphdi_unused.h"

#include "phdi_file_footer.h"

const uint8_t *phdi_file_signature         = (uint8_t *) "conectix";
const uint8_t *phdi_dynamic_disk_signature = (uint8_t *) "cxsparse";

/* Creates an IO handle
 * Make sure the value io_handle is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libphdi_io_handle_initialize(
     libphdi_io_handle_t **io_handle,
     libcerror_error_t **error )
{
	static char *function = "libphdi_io_handle_initialize";

	if( io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid IO handle.",
		 function );

		return( -1 );
	}
	if( *io_handle != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid IO handle value already set.",
		 function );

		return( -1 );
	}
	*io_handle = memory_allocate_structure(
	              libphdi_io_handle_t );

	if( *io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create IO handle.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *io_handle,
	     0,
	     sizeof( libphdi_io_handle_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear IO handle.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *io_handle != NULL )
	{
		memory_free(
		 *io_handle );

		*io_handle = NULL;
	}
	return( -1 );
}

/* Frees an IO handle
 * Returns 1 if successful or -1 on error
 */
int libphdi_io_handle_free(
     libphdi_io_handle_t **io_handle,
     libcerror_error_t **error )
{
	static char *function = "libphdi_io_handle_free";

	if( io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid IO handle.",
		 function );

		return( -1 );
	}
	if( *io_handle != NULL )
	{
		memory_free(
		 *io_handle );

		*io_handle = NULL;
	}
	return( 1 );
}

/* Clears the IO handle
 * Returns 1 if successful or -1 on error
 */
int libphdi_io_handle_clear(
     libphdi_io_handle_t *io_handle,
     libcerror_error_t **error )
{
	static char *function = "libphdi_io_handle_clear";

	if( io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid IO handle.",
		 function );

		return( -1 );
	}
	if( memory_set(
	     io_handle,
	     0,
	     sizeof( libphdi_io_handle_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear IO handle.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Reads the file footer
 * Returns 1 if successful or -1 on error
 */
int libphdi_io_handle_read_file_footer(
     libphdi_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     off64_t *next_offset,
     libcerror_error_t **error )
{
	uint8_t *file_footer_data = NULL;
	static char *function     = "libphdi_io_handle_read_file_footer";
	ssize_t read_count        = 0;

#if defined( HAVE_DEBUG_OUTPUT )
	uint64_t value_64bit      = 0;
	uint32_t value_32bit      = 0;
	int result                = 0;
#endif

	if( io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid IO handle.",
		 function );

		return( -1 );
	}
	if( next_offset == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid next offset.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: reading file footer at offset: -512 from the end.\n",
		 function );
	}
#endif
	if( libbfio_handle_seek_offset(
	     file_io_handle,
	     -512,
	     SEEK_END,
	     error ) == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_SEEK_FAILED,
		 "%s: unable to seek file footer offset: -512 from the end.",
		 function );

		goto on_error;
	}
	file_footer_data = (uint8_t *) memory_allocate(
	                                sizeof( phdi_file_footer_t ) );

	if( file_footer_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create file footer data.",
		 function );

		goto on_error;
	}
	read_count = libbfio_handle_read_buffer(
	              file_io_handle,
	              file_footer_data,
	              sizeof( phdi_file_footer_t ),
	              error );

	if( read_count != (ssize_t) sizeof( phdi_file_footer_t ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read file footer.",
		 function );

		goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: file footer data:\n",
		 function );
		libcnotify_print_data(
		 file_footer_data,
		 sizeof( phdi_file_footer_t ),
		 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );
	}
#endif
	if( memory_compare(
	     ( (phdi_file_footer_t *) file_footer_data )->signature,
	     phdi_file_signature,
	     8 ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported file signature.",
		 function );

		goto on_error;
	}
	byte_stream_copy_to_uint32_big_endian(
	 ( (phdi_file_footer_t *) file_footer_data )->format_version,
	 io_handle->format_version );

	byte_stream_copy_to_uint64_big_endian(
	 ( (phdi_file_footer_t *) file_footer_data )->next_offset,
	 *next_offset );

	byte_stream_copy_to_uint64_big_endian(
	 ( (phdi_file_footer_t *) file_footer_data )->disk_size,
	 io_handle->media_size );

	byte_stream_copy_to_uint32_big_endian(
	 ( (phdi_file_footer_t *) file_footer_data )->disk_type,
	 io_handle->disk_type );

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: signature\t\t\t\t: %c%c%c%c%c%c%c%c\n",
		 function,
		 ( (phdi_file_footer_t *) file_footer_data )->signature[ 0 ],
		 ( (phdi_file_footer_t *) file_footer_data )->signature[ 1 ],
		 ( (phdi_file_footer_t *) file_footer_data )->signature[ 2 ],
		 ( (phdi_file_footer_t *) file_footer_data )->signature[ 3 ],
		 ( (phdi_file_footer_t *) file_footer_data )->signature[ 4 ],
		 ( (phdi_file_footer_t *) file_footer_data )->signature[ 5 ],
		 ( (phdi_file_footer_t *) file_footer_data )->signature[ 6 ],
		 ( (phdi_file_footer_t *) file_footer_data )->signature[ 7 ] );

		byte_stream_copy_to_uint32_big_endian(
		 ( (phdi_file_footer_t *) file_footer_data )->features,
		 value_32bit );
		libcnotify_printf(
		 "%s: features\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		libcnotify_printf(
		 "%s: format version\t\t\t: %" PRIu16 ".%" PRIu16 "\n",
		 function,
		 io_handle->format_version >> 16,
		 io_handle->format_version & 0x0000ffffUL );

		libcnotify_printf(
		 "%s: next offset\t\t\t\t: 0x%08" PRIx64 "\n",
		 function,
		 *next_offset );

		byte_stream_copy_to_uint32_big_endian(
		 ( (phdi_file_footer_t *) file_footer_data )->modification_time,
		 value_32bit );
		libcnotify_printf(
		 "%s: modification time\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		byte_stream_copy_to_uint32_big_endian(
		 ( (phdi_file_footer_t *) file_footer_data )->creator_application,
		 value_32bit );
		libcnotify_printf(
		 "%s: creators application\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		byte_stream_copy_to_uint32_big_endian(
		 ( (phdi_file_footer_t *) file_footer_data )->creator_version,
		 value_32bit );
		libcnotify_printf(
		 "%s: creators version\t\t\t: %" PRIu16 ".%" PRIu16 "\n",
		 function,
		 value_32bit >> 16,
		 value_32bit & 0x0000ffffUL );

		byte_stream_copy_to_uint32_big_endian(
		 ( (phdi_file_footer_t *) file_footer_data )->creator_operating_system,
		 value_32bit );
		libcnotify_printf(
		 "%s: creators operating system\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		libcnotify_printf(
		 "%s: disk size\t\t\t\t: %" PRIu64 "\n",
		 function,
		 io_handle->media_size );

		byte_stream_copy_to_uint64_big_endian(
		 ( (phdi_file_footer_t *) file_footer_data )->data_size,
		 value_64bit );
		libcnotify_printf(
		 "%s: data size\t\t\t\t: %" PRIu64 "\n",
		 function,
		 value_64bit );

		byte_stream_copy_to_uint32_big_endian(
		 ( (phdi_file_footer_t *) file_footer_data )->disk_geometry,
		 value_32bit );
		libcnotify_printf(
		 "%s: disk geometry\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		libcnotify_printf(
		 "%s: disk type\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 io_handle->disk_type );

		byte_stream_copy_to_uint32_big_endian(
		 ( (phdi_file_footer_t *) file_footer_data )->checksum,
		 value_32bit );
		libcnotify_printf(
		 "%s: checksum\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		libcnotify_printf(
		 "%s: saved state\t\t\t\t: 0x%02" PRIx8 "\n",
		 function,
		 ( (phdi_file_footer_t *) file_footer_data )->saved_state );

		libcnotify_printf(
		 "%s: unknown1:\n",
		 function );
		libcnotify_print_data(
		 ( (phdi_file_footer_t *) file_footer_data )->unknown1,
		 427,
		 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );
	}
#endif
	if( io_handle->format_version != 0x00010000UL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported format version: 0x%08" PRIx32 ".",
		 function,
		 io_handle->format_version );

		goto on_error;
	}
	if( ( io_handle->disk_type != LIBPHDI_DISK_TYPE_FIXED )
	 && ( io_handle->disk_type != LIBPHDI_DISK_TYPE_DYNAMIC )
	 && ( io_handle->disk_type != LIBPHDI_DISK_TYPE_DIFFERENTIAL ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported disk type: 0x%08" PRIx32 ".",
		 function,
		 io_handle->disk_type );

		goto on_error;
	}
	memory_free(
	 file_footer_data );

	file_footer_data = NULL;

	return( 1 );

on_error:
	if( file_footer_data != NULL )
	{
		memory_free(
		 file_footer_data );
	}
	return( -1 );
}

/* Reads a data block
 * Callback function for the data block vector
 * Returns 1 if successful or -1 on error
 */
int libphdi_io_handle_read_data_block(
     libphdi_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     libfdata_vector_t *vector,
     libfcache_cache_t *cache,
     int element_index,
     int element_data_file_index,
     off64_t element_data_offset,
     size64_t element_data_size,
     uint32_t element_data_flags LIBPHDI_ATTRIBUTE_UNUSED,
     uint8_t read_flags LIBPHDI_ATTRIBUTE_UNUSED,
     libcerror_error_t **error )
{
	static char *function = "libphdi_io_handle_read_data_block";

	LIBPHDI_UNREFERENCED_PARAMETER( element_data_flags );
	LIBPHDI_UNREFERENCED_PARAMETER( read_flags );

	if( io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid IO handle.",
		 function );

		return( -1 );
	}
	if( element_data_file_index != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid element data file index value out of bounds.",
		 function );

		return( -1 );
	}
	if( element_data_size > (size64_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid element data size value exceeds maximum.",
		 function );

		return( -1 );
	}
/* TODO */
	if( libfdata_vector_set_element_value_by_index(
	     vector,
	     (intptr_t *) file_io_handle,
	     cache,
	     element_index,
	     (intptr_t *) NULL,
	     (int (*)(intptr_t **, libcerror_error_t **)) NULL,
	     LIBFDATA_LIST_ELEMENT_VALUE_FLAG_MANAGED,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set data block as element value.",
		 function );

		return( -1 );
	}
	return( 1 );
}

