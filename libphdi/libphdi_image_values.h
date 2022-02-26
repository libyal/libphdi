/*
 * Image values functions
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

#if !defined( _LIBPHDI_IMAGE_VALUES_H )
#define _LIBPHDI_IMAGE_VALUES_H

#include <common.h>
#include <types.h>

#include "libphdi_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libphdi_image_values libphdi_image_values_t;

struct libphdi_image_values
{
	/* The identifier
	 */
	uint8_t identifier[ 16 ];

	/* The type
	 */
	int type;

	/* The filename
	 */
	uint8_t *filename;

	/* The filename size
	 */
	size_t filename_size;

	/* The file IO pool entry
	 */
	int file_io_pool_entry;
};

int libphdi_image_values_initialize(
     libphdi_image_values_t **image_values,
     libcerror_error_t **error );

int libphdi_image_values_free(
     libphdi_image_values_t **image_values,
     libcerror_error_t **error );

int libphdi_image_values_set_identifier(
     libphdi_image_values_t *image_values,
     const uint8_t *utf8_string,
     size_t utf8_string_length,
     libcerror_error_t **error );

int libphdi_image_values_set_filename(
     libphdi_image_values_t *image_values,
     const uint8_t *utf8_string,
     size_t utf8_string_length,
     libcerror_error_t **error );

int libphdi_image_values_get_identifier(
     libphdi_image_values_t *image_values,
     uint8_t *guid_data,
     size_t guid_data_size,
     libcerror_error_t **error );

int libphdi_image_values_get_type(
     libphdi_image_values_t *image_values,
     int *type,
     libcerror_error_t **error );

int libphdi_image_values_get_utf8_filename_size(
     libphdi_image_values_t *image_values,
     size_t *utf8_string_size,
     libcerror_error_t **error );

int libphdi_image_values_get_utf8_filename(
     libphdi_image_values_t *image_values,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error );

int libphdi_image_values_get_utf16_filename_size(
     libphdi_image_values_t *image_values,
     size_t *utf16_string_size,
     libcerror_error_t **error );

int libphdi_image_values_get_utf16_filename(
     libphdi_image_values_t *image_values,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBPHDI_IMAGE_VALUES_H ) */

