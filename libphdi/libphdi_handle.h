/*
 * Handle functions
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

#if !defined( _LIBPHDI_HANDLE_H )
#define _LIBPHDI_HANDLE_H

#include <common.h>
#include <types.h>

#include "libphdi_extern.h"
#include "libphdi_io_handle.h"
#include "libphdi_libbfio.h"
#include "libphdi_libcerror.h"
#include "libphdi_libcthreads.h"
#include "libphdi_libfcache.h"
#include "libphdi_libfdata.h"

#if defined( _MSC_VER ) || defined( __BORLANDC__ ) || defined( __MINGW32_VERSION ) || defined( __MINGW64_VERSION_MAJOR )

/* This inclusion is needed otherwise some linkers
 * mess up exporting the metadata functions
 */
#include "libphdi_metadata.h"
#endif

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libphdi_internal_handle libphdi_internal_handle_t;

struct libphdi_internal_handle
{
	/* The current (storage media) offset
	 */
	off64_t current_offset;

	/* The IO handle
	 */
	libphdi_io_handle_t *io_handle;

	/* The file IO handle
	 */
	libbfio_handle_t *file_io_handle;

	/* Value to indicate if the file IO handle was created inside the library
	 */
	uint8_t file_io_handle_created_in_library;

	/* Value to indicate if the file IO handle was opened inside the library
	 */
	uint8_t file_io_handle_opened_in_library;

	/* The data block vector
	 */
	libfdata_vector_t *data_block_vector;

	/* The data block cache
	 */
	libfcache_cache_t *data_block_cache;

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
int libphdi_handle_close(
     libphdi_handle_t *handle,
     libcerror_error_t **error );

int libphdi_handle_open_read(
     libphdi_internal_handle_t *internal_handle,
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error );

ssize_t libphdi_internal_handle_read_buffer_from_file_io_handle(
         libphdi_internal_handle_t *internal_handle,
         libbfio_handle_t *file_io_handle,
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

#ifdef TODO_WRITE_SUPPORT

ssize_t libphdi_internal_handle_write_buffer_to_file_io_handle(
         libphdi_internal_handle_t *internal_handle,
         libbfio_handle_t *file_io_handle,
         void *buffer,
         size_t buffer_size,
         libcerror_error_t **error );

LIBPHDI_EXTERN \
ssize_t libphdi_handle_write_buffer(
         libphdi_handle_t *handle,
         const void *buffer,
         size_t buffer_size,
         libcerror_error_t **error );

LIBPHDI_EXTERN \
ssize_t libphdi_handle_write_buffer_at_offset(
         libphdi_handle_t *handle,
         void *buffer,
         size_t buffer_size,
         off64_t offset,
         libcerror_error_t **error );

#endif /* TODO_WRITE_SUPPORT */

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

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBPHDI_HANDLE_H ) */

