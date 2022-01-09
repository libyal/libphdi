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

#if !defined( _LIBPHDI_STORAGE_IMAGE_H )
#define _LIBPHDI_STORAGE_IMAGE_H

#include <common.h>
#include <types.h>

#include "libphdi_block_descriptor.h"
#include "libphdi_block_tree.h"
#include "libphdi_libcerror.h"
#include "libphdi_sparse_image_header.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libphdi_storage_image libphdi_storage_image_t;

struct libphdi_storage_image
{
	/* The sparse image header
	 */
	libphdi_sparse_image_header_t *sparse_image_header;

	/* The block tree
	 */
	libphdi_block_tree_t *block_tree;
};

int libphdi_storage_image_initialize(
     libphdi_storage_image_t **storage_image,
     libcerror_error_t **error );

int libphdi_storage_image_free(
     libphdi_storage_image_t **storage_image,
     libcerror_error_t **error );

int libphdi_storage_image_read_file_header(
     libphdi_storage_image_t *storage_image,
     libbfio_pool_t *file_io_pool,
     int file_io_pool_entry,
     libcerror_error_t **error );

int libphdi_storage_image_read_block_allocation_table(
     libphdi_storage_image_t *storage_image,
     libbfio_pool_t *file_io_pool,
     int file_io_pool_entry,
     libcerror_error_t **error );

int libphdi_storage_image_get_block_size(
     libphdi_storage_image_t *storage_image,
     size64_t *block_size,
     libcerror_error_t **error );

int libphdi_storage_image_get_block_descriptor_at_offset(
     libphdi_storage_image_t *storage_image,
     off64_t offset,
     libphdi_block_descriptor_t **block_descriptor,
     off64_t *block_offset,
     libcerror_error_t **error );

int libphdi_storage_image_read_element_data(
     intptr_t *data_handle,
     libbfio_pool_t *file_io_pool,
     libfdata_list_element_t *element,
     libfdata_cache_t *storage_image_cache,
     int file_io_pool_entry,
     off64_t element_offset,
     size64_t storage_image_size,
     uint32_t element_flags,
     uint8_t read_flags,
     libcerror_error_t **error );

ssize_t libphdi_storage_image_read_segment_data(
         intptr_t *data_handle,
         libbfio_pool_t *file_io_pool,
         int segment_index,
         int segment_file_index,
         uint8_t *segment_data,
         size_t segment_data_size,
         uint32_t segment_flags,
         uint8_t read_flags,
         libcerror_error_t **error );

off64_t libphdi_storage_image_seek_segment_offset(
         intptr_t *data_handle,
         libbfio_pool_t *file_io_pool,
         int segment_index,
         int segment_file_index,
         off64_t segment_offset,
         libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBPHDI_STORAGE_IMAGE_H ) */

