/*
 * OSS-Fuzz target for libphdi file type
 *
 * Copyright (C) 2015-2026, Joachim Metz <joachim.metz@gmail.com>
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

#include <stddef.h>
#include <stdint.h>

/* Note that some of the OSS-Fuzz engines use C++
 */
extern "C" {

#include "ossfuzz_libbfio.h"
#include "ossfuzz_libphdi.h"

#if !defined( LIBPHDI_HAVE_BFIO )

/* Opens a handle using a Basic File IO (bfio) handle
 * Returns 1 if successful or -1 on error
 */
LIBPHDI_EXTERN \
int libphdi_handle_open_file_io_handle(
     libphdi_handle_t *handle,
     libbfio_handle_t *file_io_handle,
     int access_flags,
     libphdi_error_t **error );

#endif /* !defined( LIBPHDI_HAVE_BFIO ) */

int LLVMFuzzerTestOneInput(
     const uint8_t *data,
     size_t size )
{
	uint8_t buffer[ 512 ];
	uint8_t utf8_string[ 64 ];
	uint16_t utf16_string[ 64 ];

	libbfio_handle_t *file_io_handle = NULL;
	libphdi_handle_t *handle         = NULL;
	off64_t media_offset             = 0;
	size64_t media_size              = 0;
	size_t string_size               = 0;
	int number_of_extents            = 0;
	int number_of_snapshots          = 0;
	int read_iterator                = 0;

	if( libbfio_memory_range_initialize(
	     &file_io_handle,
	     NULL ) != 1 )
	{
		return( 0 );
	}
	if( libbfio_memory_range_set(
	     file_io_handle,
	     (uint8_t *) data,
	     size,
	     NULL ) != 1 )
	{
		goto on_error_libbfio;
	}
	if( libphdi_handle_initialize(
	     &handle,
	     NULL ) != 1 )
	{
		goto on_error_libbfio;
	}
	if( libphdi_handle_open_file_io_handle(
	     handle,
	     file_io_handle,
	     LIBPHDI_OPEN_READ,
	     NULL ) != 1 )
	{
		goto on_error_libphdi;
	}
	if( libphdi_handle_get_utf8_name_size(
	     handle,
	     &string_size,
	     NULL ) == -1 )
	{
		goto on_error_libphdi;
	}
	if( libphdi_handle_get_utf8_name(
	     handle,
	     utf8_string,
	     64,
	     NULL ) == -1 )
	{
		goto on_error_libphdi;
	}
	if( libphdi_handle_get_utf16_name_size(
	     handle,
	     &string_size,
	     NULL ) == -1 )
	{
		goto on_error_libphdi;
	}
	if( libphdi_handle_get_utf16_name(
	     handle,
	     utf16_string,
	     64,
	     NULL ) == -1 )
	{
		goto on_error_libphdi;
	}
	if( libphdi_handle_get_number_of_extents(
	     handle,
	     &number_of_extents,
	     NULL ) != 1 )
	{
		goto on_error_libphdi;
	}
	if( libphdi_handle_get_number_of_snapshots(
	     handle,
	     &number_of_snapshots,
	     NULL ) != 1 )
	{
		goto on_error_libphdi;
	}
	if( libphdi_handle_get_media_size(
	     handle,
	     &media_size,
	     NULL ) != 1 )
	{
		goto on_error_libphdi;
	}
	for( read_iterator = 0;
	     read_iterator < 128;
	     read_iterator++ )
	{
		if( media_offset >= media_size )
		{
			break;
		}
		if( libphdi_handle_read_buffer_at_offset(
		     handle,
		     buffer,
		     497,
		     media_offset,
		     NULL ) == -1 )
		{
			goto on_error_libphdi;
		}
		media_offset += 497;
	}
	libphdi_handle_close(
	 handle,
	 NULL );

on_error_libphdi:
	libphdi_handle_free(
	 &handle,
	 NULL );

on_error_libbfio:
	libbfio_handle_free(
	 &file_io_handle,
	 NULL );

	return( 0 );
}

} /* extern "C" */

