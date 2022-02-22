/*
 * Image descriptor functions
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

#if !defined( _LIBPHDI_IMAGE_DESCRIPTOR_H )
#define _LIBPHDI_IMAGE_DESCRIPTOR_H

#include <common.h>
#include <types.h>

#include "libphdi_extern.h"
#include "libphdi_image_values.h"
#include "libphdi_libcerror.h"
#include "libphdi_libcthreads.h"
#include "libphdi_types.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libphdi_internal_image_descriptor libphdi_internal_image_descriptor_t;

struct libphdi_internal_image_descriptor
{
	/* The image values
	 */
	libphdi_image_values_t *image_values;

#if defined( HAVE_LIBPHDI_MULTI_THREAD_SUPPORT )
	/* The read/write lock
	 */
	libcthreads_read_write_lock_t *read_write_lock;
#endif
};

int libphdi_image_descriptor_initialize(
     libphdi_image_descriptor_t **image_descriptor,
     libphdi_image_values_t *image_values,
     libcerror_error_t **error );

LIBPHDI_EXTERN \
int libphdi_image_descriptor_free(
     libphdi_image_descriptor_t **image_descriptor,
     libcerror_error_t **error );

LIBPHDI_EXTERN \
int libphdi_image_descriptor_get_type(
     libphdi_image_descriptor_t *image_descriptor,
     int *type,
     libcerror_error_t **error );

LIBPHDI_EXTERN \
int libphdi_image_descriptor_get_utf8_filename_size(
     libphdi_image_descriptor_t *image_descriptor,
     size_t *utf8_string_size,
     libcerror_error_t **error );

LIBPHDI_EXTERN \
int libphdi_image_descriptor_get_utf8_filename(
     libphdi_image_descriptor_t *image_descriptor,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error );

LIBPHDI_EXTERN \
int libphdi_image_descriptor_get_utf16_filename_size(
     libphdi_image_descriptor_t *image_descriptor,
     size_t *utf16_string_size,
     libcerror_error_t **error );

LIBPHDI_EXTERN \
int libphdi_image_descriptor_get_utf16_filename(
     libphdi_image_descriptor_t *image_descriptor,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBPHDI_IMAGE_DESCRIPTOR_H ) */

