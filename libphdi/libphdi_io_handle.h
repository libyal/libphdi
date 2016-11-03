/*
 * Input/Output (IO) handle functions
 *
 * Copyright (C) 2015-2016, Joachim Metz <joachim.metz@gmail.com>
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

#if !defined( _LIBPHDI_IO_HANDLE_H )
#define _LIBPHDI_IO_HANDLE_H

#include <common.h>
#include <types.h>

#include "libphdi_libbfio.h"
#include "libphdi_libcerror.h"
#include "libphdi_libfcache.h"
#include "libphdi_libfdata.h"
#include "libphdi_types.h"

#if defined( __cplusplus )
extern "C" {
#endif

extern const uint8_t *phdi_file_signature;

typedef struct libphdi_io_handle libphdi_io_handle_t;

struct libphdi_io_handle
{
	/* The (storage) media size
	 */
	size64_t media_size;

	/* The format version
	 */
	uint32_t format_version;

	/* The disk type
	 */
	uint32_t disk_type;

	/* The block data offset
 	 */
	off64_t block_data_offset;

	/* The block size
	 */
	uint32_t block_size;

	/* The block bitmap size
	 */
	uint32_t block_bitmap_size;

	/* The number of blocks
	 */
	uint32_t number_of_blocks;

	/* Value to indicate if abort was signalled
	 */
	int abort;
};

int libphdi_io_handle_initialize(
     libphdi_io_handle_t **io_handle,
     libcerror_error_t **error );

int libphdi_io_handle_free(
     libphdi_io_handle_t **io_handle,
     libcerror_error_t **error );

int libphdi_io_handle_clear(
     libphdi_io_handle_t *io_handle,
     libcerror_error_t **error );

int libphdi_io_handle_read_file_footer(
     libphdi_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     off64_t *next_offset,
     libcerror_error_t **error );

int libphdi_io_handle_read_data_block(
     libphdi_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     libfdata_vector_t *vector,
     libfcache_cache_t *cache,
     int element_index,
     int element_data_file_index,
     off64_t element_data_offset,
     size64_t element_data_size,
     uint32_t element_data_flags,
     uint8_t read_flags,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBPHDI_IO_HANDLE_H ) */

