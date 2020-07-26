/*
 * Segment table functions
 *
 * Copyright (C) 2015-2020, Joachim Metz <joachim.metz@gmail.com>
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

#if !defined( _LIBPHDI_SEGMENT_TABLE_H )
#define _LIBPHDI_SEGMENT_TABLE_H

#include <common.h>
#include <types.h>

#include "libphdi_libbfio.h"
#include "libphdi_libcerror.h"
#include "libphdi_libfcache.h"
#include "libphdi_libfdata.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libphdi_segment_table libphdi_segment_table_t;

struct libphdi_segment_table
{
	/* The basename
	 */
	system_character_t *basename;

	/* The basename size
	 */
	size_t basename_size;

	/* The segment files list
	 */
	libfdata_list_t *segment_files_list;

	/* The segment files cache
	 */
	libfcache_cache_t *segment_files_cache;
};

int libphdi_segment_table_initialize(
     libphdi_segment_table_t **segment_table,
     libcerror_error_t **error );

int libphdi_segment_table_free(
     libphdi_segment_table_t **segment_table,
     libcerror_error_t **error );

int libphdi_segment_table_clear(
     libphdi_segment_table_t *segment_table,
     libcerror_error_t **error );

int libphdi_segment_table_empty(
     libphdi_segment_table_t *segment_table,
     libcerror_error_t **error );

int libphdi_segment_table_get_basename_size(
     libphdi_segment_table_t *segment_table,
     size_t *basename_size,
     libcerror_error_t **error );

int libphdi_segment_table_get_basename(
     libphdi_segment_table_t *segment_table,
     char *basename,
     size_t basename_size,
     libcerror_error_t **error );

int libphdi_segment_table_set_basename(
     libphdi_segment_table_t *segment_table,
     const char *basename,
     size_t basename_length,
     libcerror_error_t **error );

#if defined( HAVE_WIDE_CHARACTER_TYPE )

int libphdi_segment_table_get_basename_size_wide(
     libphdi_segment_table_t *segment_table,
     size_t *basename_size,
     libcerror_error_t **error );

int libphdi_segment_table_get_basename_wide(
     libphdi_segment_table_t *segment_table,
     wchar_t *basename,
     size_t basename_size,
     libcerror_error_t **error );

int libphdi_segment_table_set_basename_wide(
     libphdi_segment_table_t *segment_table,
     const wchar_t *basename,
     size_t basename_length,
     libcerror_error_t **error );

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBPHDI_SEGMENT_TABLE_H ) */

