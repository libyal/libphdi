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

#if !defined( _LIBPHDI_SPARSE_IMAGE_HEADER_H )
#define _LIBPHDI_SPARSE_IMAGE_HEADER_H

#include <common.h>
#include <types.h>

#include "libphdi_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libphdi_sparse_image_header libphdi_sparse_image_header_t;

struct libphdi_sparse_image_header
{
	/* The block size
	 */
	uint32_t block_size;

	/* The number of allocation table entries
	 */
	uint32_t number_of_allocation_table_entries;

	/* The number of sectors
	 */
	uint64_t number_of_sectors;

	/* The data start sector
	 */
	uint32_t data_start_sector;
};

int libphdi_sparse_image_header_initialize(
     libphdi_sparse_image_header_t **sparse_image_header,
     libcerror_error_t **error );

int libphdi_sparse_image_header_free(
     libphdi_sparse_image_header_t **sparse_image_header,
     libcerror_error_t **error );

int libphdi_sparse_image_header_read_data(
     libphdi_sparse_image_header_t *sparse_image_header,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error );

int libphdi_sparse_image_header_read_file_io_handle(
     libphdi_sparse_image_header_t *sparse_image_header,
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error );

int libphdi_sparse_image_header_get_block_size(
     libphdi_sparse_image_header_t *sparse_image_header,
     size64_t *block_size,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBPHDI_SPARSE_IMAGE_HEADER_H ) */

