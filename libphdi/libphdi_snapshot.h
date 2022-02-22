/*
 * Snapshot functions
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

#if !defined( _LIBPHDI_SNAPSHOT_H )
#define _LIBPHDI_SNAPSHOT_H

#include <common.h>
#include <types.h>

#include "libphdi_extern.h"
#include "libphdi_libcerror.h"
#include "libphdi_libcthreads.h"
#include "libphdi_snapshot_values.h"
#include "libphdi_types.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libphdi_internal_snapshot libphdi_internal_snapshot_t;

struct libphdi_internal_snapshot
{
	/* The snapshot values
	 */
	libphdi_snapshot_values_t *snapshot_values;

#if defined( HAVE_LIBPHDI_MULTI_THREAD_SUPPORT )
	/* The read/write lock
	 */
	libcthreads_read_write_lock_t *read_write_lock;
#endif
};

int libphdi_snapshot_initialize(
     libphdi_snapshot_t **snapshot,
     libphdi_snapshot_values_t *snapshot_values,
     libcerror_error_t **error );

LIBPHDI_EXTERN \
int libphdi_snapshot_free(
     libphdi_snapshot_t **snapshot,
     libcerror_error_t **error );

LIBPHDI_EXTERN \
int libphdi_snapshot_get_identifier(
     libphdi_snapshot_t *snapshot,
     uint8_t *guid_data,
     size_t guid_data_size,
     libcerror_error_t **error );

LIBPHDI_EXTERN \
int libphdi_snapshot_get_parent_identifier(
     libphdi_snapshot_t *snapshot,
     uint8_t *guid_data,
     size_t guid_data_size,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBPHDI_SNAPSHOT_H ) */

