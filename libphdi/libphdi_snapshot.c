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

#include <common.h>
#include <memory.h>
#include <types.h>

#include "libphdi_libcerror.h"
#include "libphdi_libcthreads.h"
#include "libphdi_snapshot.h"
#include "libphdi_snapshot_values.h"
#include "libphdi_types.h"

/* Creates a snapshot
 * Make sure the value snapshot is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libphdi_snapshot_initialize(
     libphdi_snapshot_t **snapshot,
     libphdi_snapshot_values_t *snapshot_values,
     libcerror_error_t **error )
{
	libphdi_internal_snapshot_t *internal_snapshot = NULL;
	static char *function                          = "libphdi_snapshot_initialize";

	if( snapshot == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid snapshot.",
		 function );

		return( -1 );
	}
	if( *snapshot != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid snapshot value already set.",
		 function );

		return( -1 );
	}
	if( snapshot_values == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid snapshot values.",
		 function );

		return( -1 );
	}
	internal_snapshot = memory_allocate_structure(
	                     libphdi_internal_snapshot_t );

	if( internal_snapshot == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create snapshot.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     internal_snapshot,
	     0,
	     sizeof( libphdi_internal_snapshot_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear snapshot.",
		 function );

		memory_free(
		 internal_snapshot );

		return( -1 );
	}
#if defined( HAVE_LIBPHDI_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_initialize(
	     &( internal_snapshot->read_write_lock ),
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to initialize read/write lock.",
		 function );

		goto on_error;
	}
#endif
	internal_snapshot->snapshot_values = snapshot_values;

	*snapshot = (libphdi_snapshot_t *) internal_snapshot;

	return( 1 );

on_error:
	if( internal_snapshot != NULL )
	{
		memory_free(
		 internal_snapshot );
	}
	return( -1 );
}

/* Frees a snapshot
 * Returns 1 if successful or -1 on error
 */
int libphdi_snapshot_free(
     libphdi_snapshot_t **snapshot,
     libcerror_error_t **error )
{
	libphdi_internal_snapshot_t *internal_snapshot = NULL;
	static char *function                          = "libphdi_snapshot_free";
	int result                                     = 1;

	if( snapshot == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid snapshot.",
		 function );

		return( -1 );
	}
	if( *snapshot != NULL )
	{
		internal_snapshot = (libphdi_internal_snapshot_t *) *snapshot;
		*snapshot         = NULL;

#if defined( HAVE_LIBPHDI_MULTI_THREAD_SUPPORT )
		if( libcthreads_read_write_lock_free(
		     &( internal_snapshot->read_write_lock ),
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free read/write lock.",
			 function );

			result = -1;
		}
#endif
		/* The snapshot values reference is freed elsewhere
		 */
		memory_free(
		 internal_snapshot );
	}
	return( result );
}

/* Retrieves the identifier
 * The identifier is a big-endian GUID and is 16 bytes of size
 * Returns 1 if successful or -1 on error
 */
int libphdi_snapshot_get_identifier(
     libphdi_snapshot_t *snapshot,
     uint8_t *guid_data,
     size_t guid_data_size,
     libcerror_error_t **error )
{
	libphdi_internal_snapshot_t *internal_snapshot = NULL;
	static char *function                          = "libphdi_snapshot_get_identifier";
	int result                                     = 1;

	if( snapshot == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid snapshot.",
		 function );

		return( -1 );
	}
	internal_snapshot = (libphdi_internal_snapshot_t *) snapshot;

#if defined( HAVE_LIBPHDI_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_grab_for_read(
	     internal_snapshot->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to grab read/write lock for reading.",
		 function );

		return( -1 );
	}
#endif
	if( libphdi_snapshot_values_get_identifier(
	     internal_snapshot->snapshot_values,
	     guid_data,
	     guid_data_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve identifier.",
		 function );

		result = -1;
	}
#if defined( HAVE_LIBPHDI_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_release_for_read(
	     internal_snapshot->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to release read/write lock for reading.",
		 function );

		return( -1 );
	}
#endif
	return( result );
}

/* Retrieves the parent identifier
 * The identifier is a big-endian GUID and is 16 bytes of size
 * Returns 1 if successful, 0 if not available or -1 on error
 */
int libphdi_snapshot_get_parent_identifier(
     libphdi_snapshot_t *snapshot,
     uint8_t *guid_data,
     size_t guid_data_size,
     libcerror_error_t **error )
{
	libphdi_internal_snapshot_t *internal_snapshot = NULL;
	static char *function                          = "libphdi_snapshot_get_parent_identifier";
	int result                                     = 0;

	if( snapshot == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid snapshot.",
		 function );

		return( -1 );
	}
	internal_snapshot = (libphdi_internal_snapshot_t *) snapshot;

#if defined( HAVE_LIBPHDI_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_grab_for_read(
	     internal_snapshot->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to grab read/write lock for reading.",
		 function );

		return( -1 );
	}
#endif
	result = libphdi_snapshot_values_get_parent_identifier(
	          internal_snapshot->snapshot_values,
	          guid_data,
	          guid_data_size,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve parent identifier.",
		 function );

		result = -1;
	}
#if defined( HAVE_LIBPHDI_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_release_for_read(
	     internal_snapshot->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to release read/write lock for reading.",
		 function );

		return( -1 );
	}
#endif
	return( result );
}

