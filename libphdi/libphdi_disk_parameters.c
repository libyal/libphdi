/*
 * Disk parameters functions
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

#include <common.h>
#include <memory.h>
#include <types.h>

#include "libphdi_disk_parameters.h"
#include "libphdi_libcerror.h"

/* Creates disk parameters
 * Make sure the value disk_parameters is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libphdi_disk_parameters_initialize(
     libphdi_disk_parameters_t **disk_parameters,
     libcerror_error_t **error )
{
	static char *function = "libphdi_disk_parameters_initialize";

	if( disk_parameters == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid disk parameters.",
		 function );

		return( -1 );
	}
	if( *disk_parameters != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid disk parameters value already set.",
		 function );

		return( -1 );
	}
	*disk_parameters = memory_allocate_structure(
	                    libphdi_disk_parameters_t );

	if( *disk_parameters == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create disk parameters.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *disk_parameters,
	     0,
	     sizeof( libphdi_disk_parameters_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear disk parameters.",
		 function );

		memory_free(
		 *disk_parameters );

		*disk_parameters = NULL;

		return( -1 );
	}
	return( 1 );

on_error:
	if( *disk_parameters != NULL )
	{
		memory_free(
		 *disk_parameters );

		*disk_parameters = NULL;
	}
	return( -1 );
}

/* Frees a disk parameters
 * Returns 1 if successful or -1 on error
 */
int libphdi_disk_parameters_free(
     libphdi_disk_parameters_t **disk_parameters,
     libcerror_error_t **error )
{
	static char *function = "libphdi_disk_parameters_free";

	if( disk_parameters == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid disk parameters.",
		 function );

		return( -1 );
	}
	if( *disk_parameters != NULL )
	{
		memory_free(
		 *disk_parameters );

		*disk_parameters = NULL;
	}
	return( 1 );
}

