/*
 * OSS-Fuzz target for libphdi extent descriptor type
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

/* Opens the extent data files using a Basic File IO (bfio) pool
 * This function assumes the extent data files are in same order as defined by the descriptor file
 * Returns 1 if successful or -1 on error
 */
LIBPHDI_EXTERN \
int libphdi_handle_open_extent_data_files_file_io_pool(
      libphdi_handle_t *handle,
      libbfio_pool_t *file_io_pool,
      libphdi_error_t **error );

#endif /* !defined( LIBPHDI_HAVE_BFIO ) */

int LLVMFuzzerTestOneInput(
      const uint8_t *data,
      size_t size )
{
	uint8_t utf8_string[ 64 ];
	uint16_t utf16_string[ 64 ];

	libbfio_handle_t *file_io_handle               = NULL;
	libbfio_pool_t *file_io_pool                   = NULL;
	libphdi_handle_t *handle                       = NULL;
	libphdi_extent_descriptor_t *extent_descriptor = NULL;
	libphdi_image_descriptor_t *image_descriptor   = NULL;
	off64_t extent_offset                          = 0;
	size64_t extent_size                           = 0;
	size_t string_size                             = 0;
	int entry_index                                = 0;
	int extent_index                               = 0;
	int image_index                                = 0;
	int image_type                                 = 0;
	int number_of_extents                          = 0;
	int number_of_images                           = 0;

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
	if( libbfio_pool_initialize(
	     &file_io_pool,
	     0,
	     0,
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
	if( libbfio_pool_append_handle(
	     file_io_pool,
	     &entry_index,
	     file_io_handle,
	     LIBBFIO_OPEN_READ,
	     NULL ) != 1 )
	{
		goto on_error_libphdi;
	}
	/* The file IO pool takes over management of the file IO handle
	 */
	file_io_handle = NULL;

	/* Note that the extent data files can only be opened if the number
	 * of file IO handles in the pool matches the number of images
	 * defined in the descriptor file.
	 */
	libphdi_handle_open_extent_data_files_file_io_pool(
	 handle,
	 file_io_pool,
	 NULL );

	if( libphdi_handle_get_number_of_extents(
	     handle,
	     &number_of_extents,
	     NULL ) != 1 )
	{
		goto on_error_libphdi;
	}
	for( extent_index = 0;
	     extent_index < number_of_extents;
	     extent_index++ )
	{
		if( libphdi_handle_get_extent_descriptor_by_index(
		     handle,
		     extent_index,
		     &extent_descriptor,
		     NULL ) != 1 )
		{
			goto on_error_libphdi;
		}
		if( libphdi_extent_descriptor_get_range(
		     extent_descriptor,
		     &extent_offset,
		     &extent_size,
		     NULL ) != 1 )
		{
			goto on_error_extent_descriptor;
		}
		if( libphdi_extent_descriptor_get_number_of_images(
		     extent_descriptor,
		     &number_of_images,
		     NULL ) != 1 )
		{
			goto on_error_extent_descriptor;
		}
		for( image_index = 0;
		     image_index < number_of_images;
		     image_index++ )
		{
			if( libphdi_extent_descriptor_get_image_descriptor_by_index(
			     extent_descriptor,
			     image_index,
			     &image_descriptor,
			     NULL ) != 1 )
			{
				goto on_error_extent_descriptor;
			}
			if( libphdi_image_descriptor_get_type(
			     image_descriptor,
			     &image_type,
			     NULL ) != 1 )
			{
				goto on_error_image_descriptor;
			}
			if( libphdi_image_descriptor_get_utf8_filename_size(
			     image_descriptor,
			     &string_size,
			     NULL ) == -1 )
			{
				goto on_error_image_descriptor;
			}
			if( libphdi_image_descriptor_get_utf8_filename(
			     image_descriptor,
			     utf8_string,
			     64,
			     NULL ) == -1 )
			{
				goto on_error_image_descriptor;
			}
			if( libphdi_image_descriptor_get_utf16_filename_size(
			     image_descriptor,
			     &string_size,
			     NULL ) == -1 )
			{
				goto on_error_image_descriptor;
			}
			if( libphdi_image_descriptor_get_utf16_filename(
			     image_descriptor,
			     utf16_string,
			     64,
			     NULL ) == -1 )
			{
				goto on_error_image_descriptor;
			}
on_error_image_descriptor:
			libphdi_image_descriptor_free(
			 &image_descriptor,
			 NULL );
		}
on_error_extent_descriptor:
		libphdi_extent_descriptor_free(
		 &extent_descriptor,
		 NULL );
	}
	libphdi_handle_close(
	 handle,
	 NULL );

on_error_libphdi:
	libphdi_handle_free(
	 &handle,
	 NULL );

on_error_libbfio:
	/* Note that on error the handle still has a reference to file_io_pool
	 * that will be closed. Therefore the file IO pool and handle need to
	 * be freed after closing or freeing the handle.
	 */
	if( file_io_pool != NULL )
	{
		libbfio_pool_free(
		 &file_io_pool,
		 NULL );
	}
	if( file_io_handle != NULL )
	{
		libbfio_handle_free(
		 &file_io_handle,
		 NULL );
	}
	return( 0 );
}

} /* extern "C" */
