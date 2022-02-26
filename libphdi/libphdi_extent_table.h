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

#if !defined( _LIBPHDI_EXTENT_TABLE_H )
#define _LIBPHDI_EXTENT_TABLE_H

#include <common.h>
#include <types.h>

#include "libphdi_extent_values.h"
#include "libphdi_image_values.h"
#include "libphdi_io_handle.h"
#include "libphdi_libbfio.h"
#include "libphdi_libcerror.h"
#include "libphdi_libfcache.h"
#include "libphdi_libfdata.h"
#include "libphdi_storage_image.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libphdi_extent_table libphdi_extent_table_t;

struct libphdi_extent_table
{
	/* The disk type
	 */
	int disk_type;

	/* The image type
	 */
	int image_type;

	/* The number of extents
	 */
	int number_of_extents;

	/* The extent files list used for compressed storage image files
	 */
	libfdata_list_t *extent_files_list;

	/* The extent files cache used for compressed storage image files
	 */
	libfcache_cache_t *extent_files_cache;

	/* The extent files stream used for plain storage image files
	 */
	libfdata_stream_t *extent_files_stream;
};

int libphdi_extent_table_initialize(
     libphdi_extent_table_t **extent_table,
     libcerror_error_t **error );

int libphdi_extent_table_free(
     libphdi_extent_table_t **extent_table,
     libcerror_error_t **error );

int libphdi_extent_table_clear(
     libphdi_extent_table_t *extent_table,
     libcerror_error_t **error );

int libphdi_extent_table_initialize_extents(
     libphdi_extent_table_t *extent_table,
     libphdi_io_handle_t *io_handle,
     int disk_type,
     libcerror_error_t **error );

int libphdi_extent_table_get_extent_file_at_offset(
     libphdi_extent_table_t *extent_table,
     off64_t offset,
     libbfio_pool_t *file_io_pool,
     int *extent_index,
     off64_t *extent_file_data_offset,
     libphdi_storage_image_t **extent_file,
     libcerror_error_t **error );

int libphdi_extent_table_append_extent(
     libphdi_extent_table_t *extent_table,
     int image_type,
     int file_io_pool_entry,
     size64_t extent_file_size,
     off64_t extent_file_offset,
     size64_t extent_size,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBPHDI_EXTENT_TABLE_H ) */

