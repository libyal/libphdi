/*
 * Data files functions
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

#if !defined( _LIBPHDI_DATA_FILES_H )
#define _LIBPHDI_DATA_FILES_H

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

typedef struct libphdi_data_files libphdi_data_files_t;

struct libphdi_data_files
{
	/* The path
	 */
	system_character_t *path;

	/* The path size
	 */
	size_t path_size;
};

int libphdi_data_files_initialize(
     libphdi_data_files_t **data_files,
     libcerror_error_t **error );

int libphdi_data_files_free(
     libphdi_data_files_t **data_files,
     libcerror_error_t **error );

int libphdi_data_files_clear(
     libphdi_data_files_t *data_files,
     libcerror_error_t **error );

int libphdi_data_files_get_path_size(
     libphdi_data_files_t *data_files,
     size_t *path,
     libcerror_error_t **error );

int libphdi_data_files_get_path(
     libphdi_data_files_t *data_files,
     char *path,
     size_t path_size,
     libcerror_error_t **error );

int libphdi_data_files_set_path(
     libphdi_data_files_t *data_files,
     const char *path,
     size_t path_length,
     libcerror_error_t **error );

#if defined( HAVE_WIDE_CHARACTER_TYPE )

int libphdi_data_files_get_path_size_wide(
     libphdi_data_files_t *data_files,
     size_t *path_size,
     libcerror_error_t **error );

int libphdi_data_files_get_path_wide(
     libphdi_data_files_t *data_files,
     wchar_t *path,
     size_t path_size,
     libcerror_error_t **error );

int libphdi_data_files_set_path_wide(
     libphdi_data_files_t *data_files,
     const wchar_t *path,
     size_t path_length,
     libcerror_error_t **error );

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

int libphdi_data_files_get_extent_data_file_path(
     libphdi_data_files_t *data_files,
     libphdi_image_values_t *image_values,
     char **path,
     size_t *path_size,
     libcerror_error_t **error );

int libphdi_data_files_join_extent_data_file_path(
     libphdi_data_files_t *data_files,
     const char *extent_data_filename,
     size_t extent_data_filename_size,
     char **path,
     size_t *path_size,
     libcerror_error_t **error );

#if defined( HAVE_WIDE_CHARACTER_TYPE )

int libphdi_data_files_get_extent_data_file_path_wide(
     libphdi_data_files_t *data_files,
     libphdi_image_values_t *image_values,
     wchar_t **path,
     size_t *path_size,
     libcerror_error_t **error );

int libphdi_data_files_join_extent_data_file_path_wide(
     libphdi_data_files_t *data_files,
     const wchar_t *extent_data_filename,
     size_t extent_data_filename_size,
     wchar_t **path,
     size_t *path_size,
     libcerror_error_t **error );

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBPHDI_DATA_FILES_H ) */

