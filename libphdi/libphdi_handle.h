/*
 * Handle functions
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

#if !defined( _LIBPHDI_HANDLE_H )
#define _LIBPHDI_HANDLE_H

#include <common.h>
#include <types.h>

#include "libphdi_data_files.h"
#include "libphdi_disk_parameters.h"
#include "libphdi_extern.h"
#include "libphdi_io_handle.h"
#include "libphdi_libbfio.h"
#include "libphdi_libcdata.h"
#include "libphdi_libcerror.h"
#include "libphdi_libcthreads.h"
#include "libphdi_libfcache.h"
#include "libphdi_libfdata.h"
#include "libphdi_snapshot_values.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libphdi_internal_handle libphdi_internal_handle_t;

struct libphdi_internal_handle
{
	/* The current (storage media) offset
	 */
	off64_t current_offset;

	/* The disk type
	 */
	int disk_type;

	/* The IO handle
	 */
	libphdi_io_handle_t *io_handle;

	/* The extent values array
	 */
	libcdata_array_t *extent_values_array;

	/* The unique image values array
	 */
	libcdata_array_t *image_values_array;

	/* The snapshot values array
	 */
	libcdata_array_t *snapshot_values_array;

	/* The data files
	 */
	libphdi_data_files_t *data_files;

	/* The current snapshot values
	 */
	libphdi_snapshot_values_t *current_snapshot_values;

	/* The file IO handle
	 */
	libbfio_handle_t *file_io_handle;

	/* Value to indicate if the file IO handle was created inside the library
	 */
	uint8_t file_io_handle_created_in_library;

	/* Value to indicate if the file IO handle was opened inside the library
	 */
	uint8_t file_io_handle_opened_in_library;

	/* The disk parameters
	 */
	libphdi_disk_parameters_t *disk_parameters;

	/* The data block vector
	 */
	libfdata_vector_t *data_block_vector;

	/* The data block cache
	 */
	libfcache_cache_t *data_block_cache;

	/* The extent data file IO pool
	 */
	libbfio_pool_t *extent_data_file_io_pool;

	/* Value to indicate if the file IO pool was created inside the library
	 */
	uint8_t extent_data_file_io_pool_created_in_library;

	/* The access flags
	 */
	int access_flags;

	/* The maximum number of open handles in the file IO pool
	 */
	int maximum_number_of_open_handles;

#if defined( HAVE_LIBPHDI_MULTI_THREAD_SUPPORT )
	/* The read/write lock
	 */
	libcthreads_read_write_lock_t *read_write_lock;
#endif
};

LIBPHDI_EXTERN \
int libphdi_handle_initialize(
     libphdi_handle_t **handle,
     libcerror_error_t **error );

LIBPHDI_EXTERN \
int libphdi_handle_free(
     libphdi_handle_t **handle,
     libcerror_error_t **error );

LIBPHDI_EXTERN \
int libphdi_handle_signal_abort(
     libphdi_handle_t *handle,
     libcerror_error_t **error );

LIBPHDI_EXTERN \
int libphdi_handle_open(
     libphdi_handle_t *handle,
     const char *filename,
     int access_flags,
     libcerror_error_t **error );

#if defined( HAVE_WIDE_CHARACTER_TYPE )

LIBPHDI_EXTERN \
int libphdi_handle_open_wide(
     libphdi_handle_t *handle,
     const wchar_t *filename,
     int access_flags,
     libcerror_error_t **error );

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

LIBPHDI_EXTERN \
int libphdi_handle_open_file_io_handle(
     libphdi_handle_t *handle,
     libbfio_handle_t *file_io_handle,
     int access_flags,
     libcerror_error_t **error );

LIBPHDI_EXTERN \
int libphdi_handle_open_extent_data_files(
     libphdi_handle_t *handle,
     libcerror_error_t **error );

LIBPHDI_EXTERN \
int libphdi_handle_open_extent_data_files_file_io_pool(
     libphdi_handle_t *handle,
     libbfio_pool_t *file_io_pool,
     libcerror_error_t **error );

int libphdi_handle_open_extent_data_file(
     libphdi_internal_handle_t *internal_handle,
     libbfio_pool_t *file_io_pool,
     int extent_index,
     const char *filename,
     libcerror_error_t **error );

#if defined( HAVE_WIDE_CHARACTER_TYPE )

int libphdi_handle_open_extent_data_file_wide(
     libphdi_internal_handle_t *internal_handle,
     libbfio_pool_t *file_io_pool,
     int extent_index,
     const wchar_t *filename,
     libcerror_error_t **error );

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

LIBPHDI_EXTERN \
int libphdi_handle_close(
     libphdi_handle_t *handle,
     libcerror_error_t **error );

int libphdi_internal_handle_open_read(
     libphdi_internal_handle_t *internal_handle,
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error );

int libphdi_internal_handle_open_read_extent_data_files(
     libphdi_internal_handle_t *internal_handle,
     libbfio_pool_t *file_io_pool,
     libcerror_error_t **error );

ssize_t libphdi_internal_handle_read_buffer_from_file_io_pool(
         libphdi_internal_handle_t *internal_handle,
         libbfio_pool_t *file_io_pool,
         void *buffer,
         size_t buffer_size,
         libcerror_error_t **error );

LIBPHDI_EXTERN \
ssize_t libphdi_handle_read_buffer(
         libphdi_handle_t *handle,
         void *buffer,
         size_t buffer_size,
         libcerror_error_t **error );

LIBPHDI_EXTERN \
ssize_t libphdi_handle_read_buffer_at_offset(
         libphdi_handle_t *handle,
         void *buffer,
         size_t buffer_size,
         off64_t offset,
         libcerror_error_t **error );

off64_t libphdi_internal_handle_seek_offset(
         libphdi_internal_handle_t *internal_handle,
         off64_t offset,
         int whence,
         libcerror_error_t **error );

LIBPHDI_EXTERN \
off64_t libphdi_handle_seek_offset(
         libphdi_handle_t *handle,
         off64_t offset,
         int whence,
         libcerror_error_t **error );

LIBPHDI_EXTERN \
int libphdi_handle_get_offset(
     libphdi_handle_t *handle,
     off64_t *offset,
     libcerror_error_t **error );

LIBPHDI_EXTERN \
int libphdi_handle_set_maximum_number_of_open_handles(
     libphdi_handle_t *handle,
     int maximum_number_of_open_handles,
     libcerror_error_t **error );

LIBPHDI_EXTERN \
int libphdi_handle_set_extent_data_files_path(
     libphdi_handle_t *handle,
     const char *path,
     size_t path_length,
     libcerror_error_t **error );

#if defined( HAVE_WIDE_CHARACTER_TYPE )

LIBPHDI_EXTERN \
int libphdi_handle_set_extent_data_files_path_wide(
     libphdi_handle_t *handle,
     const wchar_t *path,
     size_t path_length,
     libcerror_error_t **error );

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

LIBPHDI_EXTERN \
int libphdi_handle_get_media_size(
     libphdi_handle_t *handle,
     size64_t *media_size,
     libcerror_error_t **error );

LIBPHDI_EXTERN \
int libphdi_handle_get_utf8_name_size(
     libphdi_handle_t *handle,
     size_t *utf8_string_size,
     libcerror_error_t **error );

LIBPHDI_EXTERN \
int libphdi_handle_get_utf8_name(
     libphdi_handle_t *handle,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error );

LIBPHDI_EXTERN \
int libphdi_handle_get_utf16_name_size(
     libphdi_handle_t *handle,
     size_t *utf16_string_size,
     libcerror_error_t **error );

LIBPHDI_EXTERN \
int libphdi_handle_get_utf16_name(
     libphdi_handle_t *handle,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error );

LIBPHDI_EXTERN \
int libphdi_handle_get_number_of_extents(
     libphdi_handle_t *handle,
     int *number_of_extents,
     libcerror_error_t **error );

LIBPHDI_EXTERN \
int libphdi_handle_get_extent_descriptor_by_index(
     libphdi_handle_t *handle,
     int extent_index,
     libphdi_extent_descriptor_t **extent_descriptor,
     libcerror_error_t **error );

LIBPHDI_EXTERN \
int libphdi_handle_get_number_of_snapshots(
     libphdi_handle_t *handle,
     int *number_of_snapshots,
     libcerror_error_t **error );

LIBPHDI_EXTERN \
int libphdi_handle_get_snapshot_by_index(
     libphdi_handle_t *handle,
     int snapshot_index,
     libphdi_snapshot_t **snapshot,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBPHDI_HANDLE_H ) */

