/*
 * Snapshot values functions
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

#if !defined( _LIBPHDI_SNAPSHOT_VALUES_H )
#define _LIBPHDI_SNAPSHOT_VALUES_H

#include <common.h>
#include <types.h>

#include "libphdi_extent_table.h"
#include "libphdi_libbfio.h"
#include "libphdi_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libphdi_snapshot_values libphdi_snapshot_values_t;

struct libphdi_snapshot_values
{
	/* The identifier
	 */
	uint8_t identifier[ 16 ];

	/* The parent identifier
	 */
	uint8_t parent_identifier[ 16 ];

	/* The parent snapshot values
	 */
	libphdi_snapshot_values_t *parent_snapshot_values;

	/* The extent table
	 */
	libphdi_extent_table_t *extent_table;
};

int libphdi_snapshot_values_initialize(
     libphdi_snapshot_values_t **snapshot_values,
     libcerror_error_t **error );

int libphdi_snapshot_values_free(
     libphdi_snapshot_values_t **snapshot_values,
     libcerror_error_t **error );

int libphdi_snapshot_values_set_identifier(
     libphdi_snapshot_values_t *snapshot_values,
     const uint8_t *utf8_string,
     size_t utf8_string_length,
     libcerror_error_t **error );

int libphdi_snapshot_values_set_parent_identifier(
     libphdi_snapshot_values_t *snapshot_values,
     const uint8_t *utf8_string,
     size_t utf8_string_length,
     libcerror_error_t **error );

int libphdi_snapshot_values_get_identifier(
     libphdi_snapshot_values_t *snapshot_values,
     uint8_t *guid_data,
     size_t guid_data_size,
     libcerror_error_t **error );

int libphdi_snapshot_values_get_parent_identifier(
     libphdi_snapshot_values_t *snapshot_values,
     uint8_t *guid_data,
     size_t guid_data_size,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBPHDI_SNAPSHOT_VALUES_H ) */

