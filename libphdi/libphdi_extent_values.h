/*
 * Extent values functions
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

#if !defined( _LIBPHDI_EXTENT_VALUES_H )
#define _LIBPHDI_EXTENT_VALUES_H

#include <common.h>
#include <types.h>

#include "libphdi_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libphdi_extent_values libphdi_extent_values_t;

struct libphdi_extent_values
{
	 /* The filename
	 */
	uint8_t *filename;

	 /* The filename size
	 */
	size_t filename_size;

	/* The type
	 */
	int type;

	/* The offset
	 */
	off64_t offset;

	/* The size
	 */
	size64_t size;
};

int libphdi_extent_values_initialize(
     libphdi_extent_values_t **extent_values,
     libcerror_error_t **error );

int libphdi_extent_values_free(
     libphdi_extent_values_t **extent_values,
     libcerror_error_t **error );

int libphdi_extent_values_set(
     libphdi_extent_values_t *extent_values,
     const uint8_t *filename,
     size_t filename_length,
     int type,
     off64_t start_offset,
     off64_t end_offset,
     libcerror_error_t **error );

int libphdi_extent_values_set_filename(
     libphdi_extent_values_t *extent_values,
     const uint8_t *filename,
     size_t filename_length,
     libcerror_error_t **error );

int libphdi_extent_values_get_type(
     libphdi_extent_values_t *extent_values,
     int *type,
     libcerror_error_t **error );

int libphdi_extent_values_get_range(
     libphdi_extent_values_t *extent_values,
     off64_t *offset,
     size64_t *size,
     libcerror_error_t **error );

int libphdi_extent_values_get_utf8_filename_size(
     libphdi_extent_values_t *extent_values,
     size_t *utf8_string_size,
     libcerror_error_t **error );

int libphdi_extent_values_get_utf8_filename(
     libphdi_extent_values_t *extent_values,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error );

int libphdi_extent_values_get_utf16_filename_size(
     libphdi_extent_values_t *extent_values,
     size_t *utf16_string_size,
     libcerror_error_t **error );

int libphdi_extent_values_get_utf16_filename(
     libphdi_extent_values_t *extent_values,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBPHDI_EXTENT_VALUES_H ) */

