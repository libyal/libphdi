/*
 * Disk parameters functions
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

#if !defined( _LIBPHDI_DISK_PARAMETERS_H )
#define _LIBPHDI_DISK_PARAMETERS_H

#include <common.h>
#include <types.h>

#include "libphdi_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libphdi_disk_parameters libphdi_disk_parameters_t;

struct libphdi_disk_parameters
{
	/* The media size
	 */
	size64_t media_size;

	/* The number of cylinders
	 */
	uint32_t number_of_cylinders;

	/* The number of heads
	 */
	uint32_t number_of_heads;

	/* The number of sectors
	 */
	uint64_t number_of_sectors;

	/* The name
	 */
	uint8_t *name;

	/* The name size
	 */
	size_t name_size;

/* TODO add identifier */
};

int libphdi_disk_parameters_initialize(
     libphdi_disk_parameters_t **disk_parameters,
     libcerror_error_t **error );

int libphdi_disk_parameters_free(
     libphdi_disk_parameters_t **disk_parameters,
     libcerror_error_t **error );

int libphdi_disk_parameters_get_media_size(
     libphdi_disk_parameters_t *disk_parameters,
     size64_t *media_size,
     libcerror_error_t **error );

int libphdi_disk_parameters_get_utf8_name_size(
     libphdi_disk_parameters_t *disk_parameters,
     size_t *utf8_string_size,
     libcerror_error_t **error );

int libphdi_disk_parameters_get_utf8_name(
     libphdi_disk_parameters_t *disk_parameters,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error );

int libphdi_disk_parameters_get_utf16_name_size(
     libphdi_disk_parameters_t *disk_parameters,
     size_t *utf16_string_size,
     libcerror_error_t **error );

int libphdi_disk_parameters_get_utf16_name(
     libphdi_disk_parameters_t *disk_parameters,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error );

int libphdi_disk_parameters_set_name(
     libphdi_disk_parameters_t *disk_parameters,
     const uint8_t *name,
     size_t name_size,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBPHDI_DISK_PARAMETERS_H ) */

