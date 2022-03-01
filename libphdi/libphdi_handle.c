/*
 * Handle functions
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
#include <narrow_string.h>
#include <types.h>
#include <system_string.h>
#include <wide_string.h>

#include "libphdi_block_descriptor.h"
#include "libphdi_data_files.h"
#include "libphdi_debug.h"
#include "libphdi_definitions.h"
#include "libphdi_disk_descriptor_xml_file.h"
#include "libphdi_disk_parameters.h"
#include "libphdi_extent_descriptor.h"
#include "libphdi_extent_table.h"
#include "libphdi_extent_values.h"
#include "libphdi_i18n.h"
#include "libphdi_image_values.h"
#include "libphdi_io_handle.h"
#include "libphdi_handle.h"
#include "libphdi_libbfio.h"
#include "libphdi_libcdata.h"
#include "libphdi_libcdirectory.h"
#include "libphdi_libcerror.h"
#include "libphdi_libcnotify.h"
#include "libphdi_libcpath.h"
#include "libphdi_libcthreads.h"
#include "libphdi_libfcache.h"
#include "libphdi_libfdata.h"
#include "libphdi_snapshot.h"
#include "libphdi_snapshot_values.h"
#include "libphdi_storage_image.h"

/* Creates a handle
 * Make sure the value handle is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libphdi_handle_initialize(
     libphdi_handle_t **handle,
     libcerror_error_t **error )
{
	libphdi_internal_handle_t *internal_handle = NULL;
	static char *function                      = "libphdi_handle_initialize";

	if( handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	if( *handle != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid handle value already set.",
		 function );

		return( -1 );
	}
	internal_handle = memory_allocate_structure(
	                   libphdi_internal_handle_t );

	if( internal_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create handle.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     internal_handle,
	     0,
	     sizeof( libphdi_internal_handle_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear handle.",
		 function );

		memory_free(
		 internal_handle );

		return( -1 );
	}
	if( libphdi_io_handle_initialize(
	     &( internal_handle->io_handle ),
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create IO handle.",
		 function );

		goto on_error;
	}
	if( libcdata_array_initialize(
	     &( internal_handle->extent_values_array ),
	     0,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create extent values array.",
		 function );

		goto on_error;
	}
	if( libcdata_array_initialize(
	     &( internal_handle->image_values_array ),
	     0,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create image values array.",
		 function );

		goto on_error;
	}
	if( libcdata_array_initialize(
	     &( internal_handle->snapshot_values_array ),
	     0,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create snapshot values array.",
		 function );

		goto on_error;
	}
	if( libphdi_data_files_initialize(
	     &( internal_handle->data_files ),
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create data files.",
		 function );

		goto on_error;
	}
	if( libphdi_i18n_initialize(
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to initalize internationalization (i18n).",
		 function );

		goto on_error;
	}
#if defined( HAVE_LIBPHDI_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_initialize(
	     &( internal_handle->read_write_lock ),
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
	internal_handle->maximum_number_of_open_handles = LIBBFIO_POOL_UNLIMITED_NUMBER_OF_OPEN_HANDLES;

	*handle = (libphdi_handle_t *) internal_handle;

	return( 1 );

on_error:
	if( internal_handle != NULL )
	{
		if( internal_handle->data_files != NULL )
		{
			libphdi_data_files_free(
			 &( internal_handle->data_files ),
			 NULL );
		}
		if( internal_handle->snapshot_values_array != NULL )
		{
			libcdata_array_free(
			 &( internal_handle->snapshot_values_array ),
			 NULL,
			 NULL );
		}
		if( internal_handle->image_values_array != NULL )
		{
			libcdata_array_free(
			 &( internal_handle->image_values_array ),
			 NULL,
			 NULL );
		}
		if( internal_handle->extent_values_array != NULL )
		{
			libcdata_array_free(
			 &( internal_handle->extent_values_array ),
			 NULL,
			 NULL );
		}
		if( internal_handle->io_handle != NULL )
		{
			libphdi_io_handle_free(
			 &( internal_handle->io_handle ),
			 NULL );
		}
		memory_free(
		 internal_handle );
	}
	return( -1 );
}

/* Frees a handle
 * Returns 1 if successful or -1 on error
 */
int libphdi_handle_free(
     libphdi_handle_t **handle,
     libcerror_error_t **error )
{
	libphdi_internal_handle_t *internal_handle = NULL;
	static char *function                      = "libphdi_handle_free";
	int result                                 = 1;

	if( handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	if( *handle != NULL )
	{
		internal_handle = (libphdi_internal_handle_t *) *handle;

		if( ( internal_handle->extent_data_file_io_pool != NULL )
		 || ( internal_handle->file_io_handle != NULL ) )
		{
			if( libphdi_handle_close(
			     *handle,
			     error ) != 0 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_IO,
				 LIBCERROR_IO_ERROR_CLOSE_FAILED,
				 "%s: unable to close handle.",
				 function );

				result = -1;
			}
		}
		*handle = NULL;

#if defined( HAVE_LIBPHDI_MULTI_THREAD_SUPPORT )
		if( libcthreads_read_write_lock_free(
		     &( internal_handle->read_write_lock ),
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
		if( libphdi_data_files_free(
		     &( internal_handle->data_files ),
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free data files.",
			 function );

			result = -1;
		}
		if( libcdata_array_free(
		     &( internal_handle->snapshot_values_array ),
		     (int (*)(intptr_t **, libcerror_error_t **)) &libphdi_snapshot_values_free,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free snapshot values array.",
			 function );

			result = -1;
		}
		if( libcdata_array_free(
		     &( internal_handle->image_values_array ),
		     NULL,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free extent values array.",
			 function );

			result = -1;
		}
		if( libcdata_array_free(
		     &( internal_handle->extent_values_array ),
		     (int (*)(intptr_t **, libcerror_error_t **)) &libphdi_extent_values_free,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free extent values array.",
			 function );

			result = -1;
		}
		if( libphdi_io_handle_free(
		     &( internal_handle->io_handle ),
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free IO handle.",
			 function );

			result = -1;
		}
		memory_free(
		 internal_handle );
	}
	return( result );
}

/* Signals a handle to abort its current activity
 * Returns 1 if successful or -1 on error
 */
int libphdi_handle_signal_abort(
     libphdi_handle_t *handle,
     libcerror_error_t **error )
{
	libphdi_internal_handle_t *internal_handle = NULL;
	static char *function                      = "libphdi_handle_signal_abort";

	if( handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	internal_handle = (libphdi_internal_handle_t *) handle;

	if( internal_handle->io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid handle - missing IO handle.",
		 function );

		return( -1 );
	}
	internal_handle->io_handle->abort = 1;

	return( 1 );
}

/* Opens a handle
 * Returns 1 if successful or -1 on error
 */
int libphdi_handle_open(
     libphdi_handle_t *handle,
     const char *filename,
     int access_flags,
     libcerror_error_t **error )
{
	libbfio_handle_t *file_io_handle           = NULL;
	libcdirectory_directory_t *directory       = NULL;
	libphdi_internal_handle_t *internal_handle = NULL;
	char *data_files_path_end                  = NULL;
	char *disk_descriptor_xml_path             = NULL;
	static char *function                      = "libphdi_handle_open";
	size_t data_files_path_length              = 0;
	size_t disk_descriptor_xml_path_size       = 0;
	size_t filename_length                     = 0;
	int is_directory                           = 0;
	int result                                 = 1;

	if( handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	internal_handle = (libphdi_internal_handle_t *) handle;

	if( filename == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid filename.",
		 function );

		return( -1 );
	}
	if( ( ( access_flags & LIBPHDI_ACCESS_FLAG_READ ) == 0 )
	 && ( ( access_flags & LIBPHDI_ACCESS_FLAG_WRITE ) == 0 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported access flags.",
		 function );

		return( -1 );
	}
	if( ( access_flags & LIBPHDI_ACCESS_FLAG_WRITE ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: write access currently not supported.",
		 function );

		return( -1 );
	}
	if( libcdirectory_directory_initialize(
	     &directory,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create directory.",
		 function );

		goto on_error;
	}
	is_directory = libcdirectory_directory_open(
	                directory,
	                filename,
	                NULL );

	if( libcdirectory_directory_free(
	     &directory,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to free directory.",
		 function );

		goto on_error;
	}
	if( libbfio_file_initialize(
	     &file_io_handle,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create file IO handle.",
		 function );

		goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libbfio_handle_set_track_offsets_read(
	     file_io_handle,
	     1,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set track offsets read in file IO handle.",
		 function );

		goto on_error;
	}
#endif
	if( is_directory == 1 )
	{
		filename_length = narrow_string_length(
		                   filename );

		if( libcpath_path_join(
		     &disk_descriptor_xml_path,
		     &disk_descriptor_xml_path_size,
		     filename,
		     filename_length,
		     "DiskDescriptor.xml",
		     19,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create DiskDescriptor.xml path.",
			 function );

			goto on_error;
		}
		if( libbfio_file_set_name(
		     file_io_handle,
		     disk_descriptor_xml_path,
		     disk_descriptor_xml_path_size - 1,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
			 "%s: unable to set filename in file IO handle.",
			 function );

			goto on_error;
		}
		filename        = disk_descriptor_xml_path;
		filename_length = disk_descriptor_xml_path_size - 1;
	}
	else
	{
		filename_length = narrow_string_length(
		                   filename );

		if( libbfio_file_set_name(
		     file_io_handle,
		     filename,
		     filename_length,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
			 "%s: unable to set filename in file IO handle.",
			 function );

			goto on_error;
		}
	}
	if( libphdi_handle_open_file_io_handle(
	     handle,
	     file_io_handle,
	     access_flags,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_OPEN_FAILED,
		 "%s: unable to open handle from file: %s.",
		 function,
		 filename );

		goto on_error;
	}
	filename_length = narrow_string_length(
	                   filename );

	data_files_path_end = narrow_string_search_character_reverse(
	                       filename,
	                       (int) LIBCPATH_SEPARATOR,
	                       filename_length + 1 );

	if( data_files_path_end != NULL )
	{
		data_files_path_length = (size_t) ( data_files_path_end - filename );
	}
	if( data_files_path_length > 0 )
	{
#if defined( HAVE_LIBPHDI_MULTI_THREAD_SUPPORT )
		if( libcthreads_read_write_lock_grab_for_write(
		     internal_handle->read_write_lock,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
			 "%s: unable to grab read/write lock for writing.",
			 function );

			return( -1 );
		}
#endif
		if( libphdi_data_files_set_path(
		     internal_handle->data_files,
		     filename,
		     data_files_path_length,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
			 "%s: unable to set data files path.",
			 function );

			result = -1;
		}
#if defined( HAVE_LIBPHDI_MULTI_THREAD_SUPPORT )
		if( libcthreads_read_write_lock_release_for_write(
		     internal_handle->read_write_lock,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
			 "%s: unable to release read/write lock for writing.",
			 function );

			return( -1 );
		}
#endif
	}
	internal_handle->file_io_handle_created_in_library = 1;

	if( disk_descriptor_xml_path != NULL )
	{
		memory_free(
		 disk_descriptor_xml_path );

		disk_descriptor_xml_path = NULL;
	}
	return( result );

on_error:
	if( file_io_handle != NULL )
	{
		libbfio_handle_free(
		 &file_io_handle,
		 NULL );
	}
	if( disk_descriptor_xml_path != NULL )
	{
		memory_free(
		 disk_descriptor_xml_path );
	}
	if( directory != NULL )
	{
		libcdirectory_directory_free(
		 &directory,
		 NULL );
	}
	return( -1 );
}

#if defined( HAVE_WIDE_CHARACTER_TYPE )

/* Opens a handle
 * Returns 1 if successful or -1 on error
 */
int libphdi_handle_open_wide(
     libphdi_handle_t *handle,
     const wchar_t *filename,
     int access_flags,
     libcerror_error_t **error )
{
	libbfio_handle_t *file_io_handle           = NULL;
	libcdirectory_directory_t *directory       = NULL;
	libphdi_internal_handle_t *internal_handle = NULL;
	wchar_t *data_files_path_end               = NULL;
	wchar_t *disk_descriptor_xml_path          = NULL;
	static char *function                      = "libphdi_handle_open_wide";
	size_t data_files_path_length              = 0;
	size_t disk_descriptor_xml_path_size       = 0;
	size_t filename_length                     = 0;
	int is_directory                           = 0;
	int result                                 = 1;

	if( handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	internal_handle = (libphdi_internal_handle_t *) handle;

	if( filename == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid filename.",
		 function );

		return( -1 );
	}
	if( ( ( access_flags & LIBPHDI_ACCESS_FLAG_READ ) == 0 )
	 && ( ( access_flags & LIBPHDI_ACCESS_FLAG_WRITE ) == 0 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported access flags.",
		 function );

		return( -1 );
	}
	if( ( access_flags & LIBPHDI_ACCESS_FLAG_WRITE ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: write access currently not supported.",
		 function );

		return( -1 );
	}
	if( libcdirectory_directory_initialize(
	     &directory,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create directory.",
		 function );

		goto on_error;
	}
	is_directory = libcdirectory_directory_open_wide(
	                directory,
	                filename,
	                NULL );

	if( libcdirectory_directory_free(
	     &directory,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to free directory.",
		 function );

		goto on_error;
	}
	if( libbfio_file_initialize(
	     &file_io_handle,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create file IO handle.",
		 function );

		goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libbfio_handle_set_track_offsets_read(
	     file_io_handle,
	     1,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set track offsets read in file IO handle.",
		 function );

		goto on_error;
	}
#endif
	if( is_directory == 1 )
	{
		filename_length = wide_string_length(
		                   filename );

		if( libcpath_path_join_wide(
		     &disk_descriptor_xml_path,
		     &disk_descriptor_xml_path_size,
		     filename,
		     filename_length,
		     L"DiskDescriptor.xml",
		     19,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create DiskDescriptor.xml path.",
			 function );

			goto on_error;
		}
		if( libbfio_file_set_name_wide(
		     file_io_handle,
		     disk_descriptor_xml_path,
		     disk_descriptor_xml_path_size - 1,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
			 "%s: unable to set filename in file IO handle.",
			 function );

			goto on_error;
		}
	}
	else
	{
		filename_length = wide_string_length(
		                   filename );

		if( libbfio_file_set_name_wide(
		     file_io_handle,
		     filename,
		     filename_length,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
			 "%s: unable to set filename in file IO handle.",
			 function );

			goto on_error;
		}
	}
	if( libphdi_handle_open_file_io_handle(
	     handle,
	     file_io_handle,
	     access_flags,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_OPEN_FAILED,
		 "%s: unable to open handle: %ls.",
		 function,
		 filename );

		goto on_error;
	}
	filename_length = wide_string_length(
	                   filename );

	data_files_path_end = wide_string_search_character_reverse(
	                       filename,
	                       (int) LIBCPATH_SEPARATOR,
	                       filename_length + 1 );

	if( data_files_path_end != NULL )
	{
		data_files_path_length = (size_t) ( data_files_path_end - filename );
	}
	if( data_files_path_length > 0 )
	{
#if defined( HAVE_LIBPHDI_MULTI_THREAD_SUPPORT )
		if( libcthreads_read_write_lock_grab_for_write(
		     internal_handle->read_write_lock,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
			 "%s: unable to grab read/write lock for writing.",
			 function );

			return( -1 );
		}
#endif
		if( libphdi_data_files_set_path_wide(
		     internal_handle->data_files,
		     filename,
		     data_files_path_length,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
			 "%s: unable to set data files path.",
			 function );

			result = -1;
		}
#if defined( HAVE_LIBPHDI_MULTI_THREAD_SUPPORT )
		if( libcthreads_read_write_lock_release_for_write(
		     internal_handle->read_write_lock,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
			 "%s: unable to release read/write lock for writing.",
			 function );

			return( -1 );
		}
#endif
	}
	internal_handle->file_io_handle_created_in_library = 1;

	if( disk_descriptor_xml_path != NULL )
	{
		memory_free(
		 disk_descriptor_xml_path );

		disk_descriptor_xml_path = NULL;
	}
	return( result );

on_error:
	if( file_io_handle != NULL )
	{
		libbfio_handle_free(
		 &file_io_handle,
		 NULL );
	}
	if( disk_descriptor_xml_path != NULL )
	{
		memory_free(
		 disk_descriptor_xml_path );
	}
	if( directory != NULL )
	{
		libcdirectory_directory_free(
		 &directory,
		 NULL );
	}
	return( -1 );
}

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

/* Opens a handle using a Basic File IO (bfio) handle
 * Returns 1 if successful or -1 on error
 */
int libphdi_handle_open_file_io_handle(
     libphdi_handle_t *handle,
     libbfio_handle_t *file_io_handle,
     int access_flags,
     libcerror_error_t **error )
{
	libphdi_internal_handle_t *internal_handle = NULL;
	static char *function                      = "libphdi_handle_open_file_io_handle";
	int bfio_access_flags                      = 0;
	int file_io_handle_is_open                 = 0;
	int file_io_handle_opened_in_library       = 0;
	int result                                 = 1;

	if( handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	internal_handle = (libphdi_internal_handle_t *) handle;

	if( file_io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file IO handle.",
		 function );

		return( -1 );
	}
	if( ( ( access_flags & LIBPHDI_ACCESS_FLAG_READ ) == 0 )
	 && ( ( access_flags & LIBPHDI_ACCESS_FLAG_WRITE ) == 0 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported access flags.",
		 function );

		return( -1 );
	}
	if( ( access_flags & LIBPHDI_ACCESS_FLAG_WRITE ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: write access currently not supported.",
		 function );

		return( -1 );
	}
	if( ( access_flags & LIBPHDI_ACCESS_FLAG_READ ) != 0 )
	{
		bfio_access_flags = LIBBFIO_ACCESS_FLAG_READ;
	}
	file_io_handle_is_open = libbfio_handle_is_open(
	                          file_io_handle,
	                          error );

	if( file_io_handle_is_open == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_OPEN_FAILED,
		 "%s: unable to determine if file IO handle is open.",
		 function );

		goto on_error;
	}
	else if( file_io_handle_is_open == 0 )
	{
		if( libbfio_handle_open(
		     file_io_handle,
		     bfio_access_flags,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_OPEN_FAILED,
			 "%s: unable to open file IO handle.",
			 function );

			goto on_error;
		}
		file_io_handle_opened_in_library = 1;
	}
#if defined( HAVE_LIBPHDI_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_grab_for_write(
	     internal_handle->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to grab read/write lock for writing.",
		 function );

		return( -1 );
	}
#endif
	if( libphdi_internal_handle_open_read(
	     internal_handle,
	     file_io_handle,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read from file IO handle.",
		 function );

		result = -1;
	}
	else
	{
		internal_handle->file_io_handle                   = file_io_handle;
		internal_handle->file_io_handle_opened_in_library = file_io_handle_opened_in_library;
		internal_handle->access_flags                     = access_flags;
	}
#if defined( HAVE_LIBPHDI_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_release_for_write(
	     internal_handle->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to release read/write lock for writing.",
		 function );

		return( -1 );
	}
#endif
	return( result );

on_error:
	if( file_io_handle_opened_in_library != 0 )
	{
		libbfio_handle_close(
		 file_io_handle,
		 error );
	}
	return( -1 );
}

/* Opens the extent data files
 * If the extent data filenames were not set explicitly this function assumes the extent data files
 * are in the same location as the descriptor file
 * Returns 1 if successful or -1 on error
 */
int libphdi_handle_open_extent_data_files(
     libphdi_handle_t *handle,
     libcerror_error_t **error )
{
	libbfio_pool_t *file_io_pool                  = NULL;
	libphdi_image_values_t *image_values          = NULL;
	libphdi_internal_handle_t *internal_handle    = NULL;
	system_character_t *extent_data_file_location = NULL;
	static char *function                         = "libphdi_handle_open_extent_data_files";
	size_t extent_data_file_location_size         = 0;
	int image_index                               = 0;
	int number_of_images                          = 0;
	int result                                    = 0;

	if( handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	internal_handle = (libphdi_internal_handle_t *) handle;

	if( ( ( internal_handle->access_flags & LIBPHDI_ACCESS_FLAG_READ ) == 0 )
	 && ( ( internal_handle->access_flags & LIBPHDI_ACCESS_FLAG_WRITE ) == 0 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported access flags.",
		 function );

		return( -1 );
	}
	if( ( internal_handle->access_flags & LIBPHDI_ACCESS_FLAG_WRITE ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: write access currently not supported.",
		 function );

		return( -1 );
	}
	if( internal_handle->file_io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid handle - missing file IO handle.",
		 function );

		return( -1 );
	}
	if( internal_handle->extent_data_file_io_pool != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid handle - extent data file IO pool already exists.",
		 function );

		return( -1 );
	}
#if defined( HAVE_LIBPHDI_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_grab_for_write(
	     internal_handle->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to grab read/write lock for writing.",
		 function );

		return( -1 );
	}
#endif
	if( libcdata_array_get_number_of_entries(
	     internal_handle->image_values_array,
	     &number_of_images,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of extents.",
		 function );

		goto on_error;
	}
	if( number_of_images == 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid number of images value out of bounds.",
		 function );

		return( -1 );
	}
	if( libbfio_pool_initialize(
	     &file_io_pool,
	     number_of_images,
	     internal_handle->maximum_number_of_open_handles,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create file IO pool.",
		 function );

		goto on_error;
	}
	for( image_index = 0;
	     image_index < number_of_images;
	     image_index++ )
	{
		if( libcdata_array_get_entry_by_index(
		     internal_handle->image_values_array,
		     image_index,
		     (intptr_t **) &image_values,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve image values: %d from array.",
			 function,
			 image_index );

			goto on_error;
		}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
		result = libphdi_data_files_get_extent_data_file_path_wide(
		          internal_handle->data_files,
		          image_values,
		          &extent_data_file_location,
		          &extent_data_file_location_size,
		          error );
#else
		result = libphdi_data_files_get_extent_data_file_path(
		          internal_handle->data_files,
		          image_values,
		          &extent_data_file_location,
		          &extent_data_file_location_size,
		          error );
#endif
		if( result != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create extent data file location.",
			 function );

			goto on_error;
		}
		/* Note that the open extent data file function will initialize extent_data_file_io_pool
		 */
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
		result = libphdi_handle_open_extent_data_file_wide(
			  internal_handle,
			  file_io_pool,
			  image_values->file_io_pool_entry,
			  extent_data_file_location,
			  error );
#else
		result = libphdi_handle_open_extent_data_file(
			  internal_handle,
			  file_io_pool,
			  image_values->file_io_pool_entry,
			  extent_data_file_location,
			  error );
#endif
		if( result != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_OPEN_FAILED,
			 "%s: unable to open extent data file: %" PRIs_SYSTEM ".",
			 function,
			 extent_data_file_location );

			goto on_error;
		}
		memory_free(
		 extent_data_file_location );

		extent_data_file_location = NULL;
	}
	if( libphdi_internal_handle_open_read_extent_data_files(
	     internal_handle,
	     file_io_pool,
	     error ) != 1 )
	{
                libcerror_error_set(
                 error,
                 LIBCERROR_ERROR_DOMAIN_RUNTIME,
                 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
                 "%s: unable to read extent data files.",
                 function );

                goto on_error;
	}
	internal_handle->extent_data_file_io_pool                    = file_io_pool;
	internal_handle->extent_data_file_io_pool_created_in_library = 1;

#if defined( HAVE_LIBPHDI_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_release_for_write(
	     internal_handle->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to release read/write lock for writing.",
		 function );

		return( -1 );
	}
#endif
	return( 1 );

on_error:
	if( file_io_pool != NULL )
	{
		libbfio_pool_close_all(
		 file_io_pool,
		 NULL );
		libbfio_pool_free(
		 &file_io_pool,
		 NULL );
	}
	if( extent_data_file_location != NULL )
	{
		memory_free(
		 extent_data_file_location );
	}
#if defined( HAVE_LIBPHDI_MULTI_THREAD_SUPPORT )
	libcthreads_read_write_lock_release_for_write(
	 internal_handle->read_write_lock,
	 NULL );
#endif
	return( -1 );
}

/* Opens the extent data files using a Basic File IO (bfio) pool
 * This function assumes the extent data files are in same order as defined by the descriptor file
 * Returns 1 if successful or -1 on error
 */
int libphdi_handle_open_extent_data_files_file_io_pool(
     libphdi_handle_t *handle,
     libbfio_pool_t *file_io_pool,
     libcerror_error_t **error )
{
	libphdi_internal_handle_t *internal_handle = NULL;
	static char *function                      = "libphdi_handle_open_extent_data_files_file_io_pool";
	int result                                 = 1;

	if( handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	internal_handle = (libphdi_internal_handle_t *) handle;

	if( ( ( internal_handle->access_flags & LIBPHDI_ACCESS_FLAG_READ ) == 0 )
	 && ( ( internal_handle->access_flags & LIBPHDI_ACCESS_FLAG_WRITE ) == 0 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported access flags.",
		 function );

		return( -1 );
	}
	if( ( internal_handle->access_flags & LIBPHDI_ACCESS_FLAG_WRITE ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: write access currently not supported.",
		 function );

		return( -1 );
	}
	if( internal_handle->file_io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid handle - missing file IO handle.",
		 function );

		return( -1 );
	}
	if( internal_handle->extent_data_file_io_pool != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid handle - extent data file IO pool already exists.",
		 function );

		return( -1 );
	}
#if defined( HAVE_LIBPHDI_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_grab_for_write(
	     internal_handle->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to grab read/write lock for writing.",
		 function );

		return( -1 );
	}
#endif
	if( libphdi_internal_handle_open_read_extent_data_files(
	     internal_handle,
	     file_io_pool,
	     error ) != 1 )
	{
                libcerror_error_set(
                 error,
                 LIBCERROR_ERROR_DOMAIN_RUNTIME,
                 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
                 "%s: unable to read extent data files.",
                 function );

                result = -1;
	}
	else
	{
		internal_handle->extent_data_file_io_pool = file_io_pool;
	}
#if defined( HAVE_LIBPHDI_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_release_for_write(
	     internal_handle->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to release read/write lock for writing.",
		 function );

		return( -1 );
	}
#endif
	return( result );
}

/* Opens a specific extent data file
 * Returns 1 if successful or -1 on error
 */
int libphdi_handle_open_extent_data_file(
     libphdi_internal_handle_t *internal_handle,
     libbfio_pool_t *file_io_pool,
     int extent_index,
     const char *filename,
     libcerror_error_t **error )
{
	libbfio_handle_t *file_io_handle = NULL;
	static char *function            = "libphdi_handle_open_extent_data_file";
	size_t filename_length           = 0;
	int bfio_access_flags            = 0;

	if( internal_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	if( filename == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid filename.",
		 function );

		return( -1 );
	}
	if( ( internal_handle->access_flags & LIBPHDI_ACCESS_FLAG_READ ) != 0 )
	{
		bfio_access_flags = LIBBFIO_ACCESS_FLAG_READ;
	}
	if( libbfio_file_initialize(
	     &file_io_handle,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create file IO handle.",
		 function );

		goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libbfio_handle_set_track_offsets_read(
	     file_io_handle,
	     1,
	     error ) != 1 )
	{
                libcerror_error_set(
                 error,
                 LIBCERROR_ERROR_DOMAIN_RUNTIME,
                 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
                 "%s: unable to set track offsets read in file IO handle.",
                 function );

                goto on_error;
	}
#endif
	filename_length = narrow_string_length(
	                   filename );

	if( libbfio_file_set_name(
	     file_io_handle,
	     filename,
	     filename_length + 1,
	     error ) != 1 )
	{
                libcerror_error_set(
                 error,
                 LIBCERROR_ERROR_DOMAIN_RUNTIME,
                 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
                 "%s: unable to set filename in file IO handle.",
                 function );

                goto on_error;
	}
	if( libbfio_handle_open(
	     file_io_handle,
	     bfio_access_flags,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_OPEN_FAILED,
		 "%s: unable to open file IO handle.",
		 function );

		goto on_error;
	}
	if( libbfio_pool_set_handle(
	     file_io_pool,
	     extent_index,
	     file_io_handle,
	     bfio_access_flags,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set file IO handle: %d in pool.",
		 function,
		 extent_index );

		goto on_error;
	}
	return( 1 );

on_error:
	if( file_io_handle != NULL )
	{
		libbfio_handle_free(
		 &file_io_handle,
		 NULL );
	}
	return( -1 );
}

#if defined( HAVE_WIDE_CHARACTER_TYPE )

/* Opens a specific extent data file
 * Returns 1 if successful or -1 on error
 */
int libphdi_handle_open_extent_data_file_wide(
     libphdi_internal_handle_t *internal_handle,
     libbfio_pool_t *file_io_pool,
     int extent_index,
     const wchar_t *filename,
     libcerror_error_t **error )
{
	libbfio_handle_t *file_io_handle = NULL;
	static char *function            = "libphdi_handle_open_extent_data_file_wide";
	size_t filename_length           = 0;
	int bfio_access_flags            = 0;

	if( internal_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	if( filename == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid filename.",
		 function );

		return( -1 );
	}
	if( ( internal_handle->access_flags & LIBPHDI_ACCESS_FLAG_READ ) != 0 )
	{
		bfio_access_flags = LIBBFIO_ACCESS_FLAG_READ;
	}
	if( libbfio_file_initialize(
	     &file_io_handle,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create file IO handle.",
		 function );

                goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libbfio_handle_set_track_offsets_read(
	     file_io_handle,
	     1,
	     error ) != 1 )
	{
                libcerror_error_set(
                 error,
                 LIBCERROR_ERROR_DOMAIN_RUNTIME,
                 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
                 "%s: unable to set track offsets read in file IO handle.",
                 function );

                goto on_error;
	}
#endif
	filename_length = wide_string_length(
	                   filename );

	if( libbfio_file_set_name_wide(
	     file_io_handle,
	     filename,
	     filename_length + 1,
	     error ) != 1 )
	{
                libcerror_error_set(
                 error,
                 LIBCERROR_ERROR_DOMAIN_RUNTIME,
                 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
                 "%s: unable to set filename in file IO handle.",
                 function );

                goto on_error;
	}
	if( libbfio_handle_open(
	     file_io_handle,
	     bfio_access_flags,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_OPEN_FAILED,
		 "%s: unable to open file IO handle.",
		 function );

		goto on_error;
	}
	if( libbfio_pool_set_handle(
	     file_io_pool,
	     extent_index,
	     file_io_handle,
	     bfio_access_flags,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set file IO handle: %d in pool.",
		 function,
		 extent_index );

		goto on_error;
	}
	return( 1 );

on_error:
	if( file_io_handle != NULL )
	{
		libbfio_handle_free(
		 &file_io_handle,
		 NULL );
	}
	return( -1 );
}

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

/* Closes a handle
 * Returns 0 if successful or -1 on error
 */
int libphdi_handle_close(
     libphdi_handle_t *handle,
     libcerror_error_t **error )
{
	libphdi_internal_handle_t *internal_handle = NULL;
	static char *function                      = "libphdi_handle_close";
	int result                                 = 0;

	if( handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	internal_handle = (libphdi_internal_handle_t *) handle;

	if( internal_handle->file_io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid handle - missing file IO handle.",
		 function );

		return( -1 );
	}
#if defined( HAVE_LIBPHDI_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_grab_for_write(
	     internal_handle->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to grab read/write lock for writing.",
		 function );

		return( -1 );
	}
#endif
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		if( internal_handle->file_io_handle_created_in_library != 0 )
		{
			if( libphdi_debug_print_read_offsets(
			     internal_handle->file_io_handle,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
				 "%s: unable to print the read offsets.",
				 function );

				result = -1;
			}
		}
	}
#endif
	if( internal_handle->file_io_handle_opened_in_library != 0 )
	{
		if( libbfio_handle_close(
		     internal_handle->file_io_handle,
		     error ) != 0 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_CLOSE_FAILED,
			 "%s: unable to close file IO handle.",
			 function );

			result = -1;
		}
		internal_handle->file_io_handle_opened_in_library = 0;
	}
	if( internal_handle->file_io_handle_created_in_library != 0 )
	{
		if( libbfio_handle_free(
		     &( internal_handle->file_io_handle ),
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free file IO handle.",
			 function );

			result = -1;
		}
		internal_handle->file_io_handle_created_in_library = 0;
	}
	internal_handle->file_io_handle = NULL;

	if( internal_handle->extent_data_file_io_pool_created_in_library != 0 )
	{
		if( libbfio_pool_close_all(
		     internal_handle->extent_data_file_io_pool,
		     error ) != 0 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_CLOSE_FAILED,
			 "%s: unable to close all files in extent data file IO pool.",
			 function );

			result = -1;
		}
		if( libbfio_pool_free(
		     &( internal_handle->extent_data_file_io_pool ),
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free extent data file IO pool.",
			 function );

			result = -1;
		}
		internal_handle->extent_data_file_io_pool_created_in_library = 0;
	}
	internal_handle->extent_data_file_io_pool = NULL;
	internal_handle->current_offset           = 0;

	if( libphdi_io_handle_clear(
	     internal_handle->io_handle,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to clear IO handle.",
		 function );

		result = -1;
	}
	if( libphdi_disk_parameters_free(
	     &( internal_handle->disk_parameters ),
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to free disk parameters.",
		 function );

		result = -1;
	}
	if( libphdi_data_files_clear(
	     internal_handle->data_files,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to clear data files.",
		 function );

		result = -1;
	}
	if( libfdata_vector_free(
	     &( internal_handle->data_block_vector ),
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to free data block vector.",
		 function );

		result = -1;
	}
	if( libfcache_cache_free(
	     &( internal_handle->data_block_cache ),
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to free data block cache.",
		 function );

		result = -1;
	}
#if defined( HAVE_LIBPHDI_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_release_for_write(
	     internal_handle->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to release read/write lock for writing.",
		 function );

		return( -1 );
	}
#endif
	return( result );
}

/* Opens a handle for reading
 * Returns 1 if successful or -1 on error
 */
int libphdi_internal_handle_open_read(
     libphdi_internal_handle_t *internal_handle,
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error )
{
	libphdi_disk_descriptor_xml_file_t *disk_descriptor_xml_file = NULL;
	libphdi_extent_values_t *extent_values                       = NULL;
	libphdi_image_values_t *image_values                         = NULL;
	static char *function                                        = "libphdi_internal_handle_open_read";
	int entry_index                                              = 0;
	int extent_index                                             = 0;
	int image_index                                              = 0;
	int number_of_extents                                        = 0;
	int number_of_images                                         = 0;

	if( internal_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	if( internal_handle->disk_parameters != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid handle - disk parameters value already set.",
		 function );

		return( -1 );
	}
	if( internal_handle->data_block_vector != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid handle - data block vector value already set.",
		 function );

		return( -1 );
	}
	if( internal_handle->data_block_cache != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid handle - data block cache value already set.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "Reading Disk descriptor XML file:\n" );
	}
#endif
	if( libphdi_disk_descriptor_xml_file_initialize(
	     &disk_descriptor_xml_file,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create disk descriptor XML file.",
		 function );

		goto on_error;
	}
	if( libphdi_disk_descriptor_xml_file_read_file_io_handle(
	     disk_descriptor_xml_file,
	     file_io_handle,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read disk descriptor XML file.",
		 function );

		goto on_error;
	}
	if( libphdi_disk_parameters_initialize(
	     &( internal_handle->disk_parameters ),
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create disk parameters.",
		 function );

		goto on_error;
	}
	if( libphdi_disk_descriptor_xml_file_get_disk_parameters(
	     disk_descriptor_xml_file,
	     internal_handle->disk_parameters,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve disk parameters from disk descriptor XML file.",
		 function );

		goto on_error;
	}
	if( libphdi_disk_descriptor_xml_file_get_storage_data(
	     disk_descriptor_xml_file,
	     internal_handle->extent_values_array,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve storage data from disk descriptor XML file.",
		 function );

		goto on_error;
	}
	if( libphdi_disk_descriptor_xml_file_get_disk_type(
	     disk_descriptor_xml_file,
	     &( internal_handle->disk_type ),
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve disk type from disk descriptor XML file.",
		 function );

		goto on_error;
	}
	if( libphdi_disk_descriptor_xml_file_get_snapshots(
	     disk_descriptor_xml_file,
	     internal_handle->snapshot_values_array,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve snapshots from disk descriptor XML file.",
		 function );

		goto on_error;
	}
	if( libphdi_disk_descriptor_xml_file_free(
	     &disk_descriptor_xml_file,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to free disk descriptor XML file.",
		 function );

		goto on_error;
	}
	if( libcdata_array_get_number_of_entries(
	     internal_handle->extent_values_array,
	     &number_of_extents,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of extents.",
		 function );

		goto on_error;
	}
	if( number_of_extents == 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid number of extents value out of bounds.",
		 function );

		goto on_error;
	}
	for( extent_index = 0;
	     extent_index < number_of_extents;
	     extent_index++ )
	{
		if( libcdata_array_get_entry_by_index(
		     internal_handle->extent_values_array,
		     extent_index,
		     (intptr_t **) &extent_values,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve extent values: %d from array.",
			 function,
			 extent_index );

			goto on_error;
		}
		if( libphdi_extent_values_get_number_of_images(
		     extent_values,
		     &number_of_images,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve number of extents.",
			 function );

			goto on_error;
		}
		if( number_of_images == 0 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: invalid number of images value out of bounds.",
			 function );

			goto on_error;
		}
		for( image_index = 0;
		     image_index < number_of_images;
		     image_index++ )
		{
			if( libphdi_extent_values_get_image_values_by_index(
			     extent_values,
			     image_index,
			     &image_values,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
				 "%s: unable to retrieve image values: %d from extent values.",
				 function,
				 image_index );

				goto on_error;
			}
			image_values->file_io_pool_entry = image_index;

			if( libcdata_array_append_entry(
			     internal_handle->image_values_array,
			     &entry_index,
			     (intptr_t *) image_values,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
				 "%s: unable to append image values to array.",
				 function );

				goto on_error;
			}
			image_values = NULL;
		}
	}
	return( 1 );

on_error:
	if( disk_descriptor_xml_file != NULL )
	{
		libphdi_disk_descriptor_xml_file_free(
		 &disk_descriptor_xml_file,
		 NULL );
	}
	if( internal_handle->data_block_cache != NULL )
	{
		libfcache_cache_free(
		 &( internal_handle->data_block_cache ),
		 NULL );
	}
	if( internal_handle->data_block_vector != NULL )
	{
		libfdata_vector_free(
		 &( internal_handle->data_block_vector ),
		 NULL );
	}
	if( internal_handle->disk_parameters != NULL )
	{
		libphdi_disk_parameters_free(
		 &( internal_handle->disk_parameters ),
		 NULL );
	}
	return( -1 );
}

/* Reads the extent data files
 * Returns 1 if successful or -1 on error
 */
int libphdi_internal_handle_open_read_extent_data_files(
     libphdi_internal_handle_t *internal_handle,
     libbfio_pool_t *file_io_pool,
     libcerror_error_t **error )
{
	libphdi_extent_values_t *extent_values            = NULL;
	libphdi_image_values_t *image_values              = NULL;
	libphdi_snapshot_values_t *parent_snapshot_values = NULL;
	libphdi_snapshot_values_t *snapshot_values        = NULL;
	libphdi_storage_image_t *storage_image            = NULL;
	static char *function                             = "libphdi_internal_handle_open_read_extent_data_files";
	size64_t image_file_size                          = 0;
	int extent_index                                  = 0;
	int image_index                                   = 0;
	int image_type                                    = 0;
	int number_of_extents                             = 0;
	int number_of_file_io_handles                     = 0;
	int number_of_images                              = 0;
	int number_of_snapshots                           = 0;
	int parent_snapshot_index                         = 0;
	int snapshot_index                                = 0;

	if( internal_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	if( internal_handle->io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid handle - missing IO handle.",
		 function );

		return( -1 );
	}
	if( libbfio_pool_get_number_of_handles(
	     file_io_pool,
	     &number_of_file_io_handles,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve the number of file IO handles.",
		 function );

		return( -1 );
	}
	if( number_of_file_io_handles == 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: missing file IO handles.",
		 function );

		goto on_error;
	}
	if( libcdata_array_get_number_of_entries(
	     internal_handle->image_values_array,
	     &number_of_images,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of images.",
		 function );

		goto on_error;
	}
	if( number_of_file_io_handles != number_of_images )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: mismatch between number of file IO handles in pool and number of images in metadata.",
		 function );

		goto on_error;
	}
	if( libcdata_array_get_number_of_entries(
	     internal_handle->snapshot_values_array,
	     &number_of_snapshots,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of snapshots.",
		 function );

		goto on_error;
	}
	if( libcdata_array_get_number_of_entries(
	     internal_handle->extent_values_array,
	     &number_of_extents,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of extents.",
		 function );

		goto on_error;
	}
	for( snapshot_index = 0;
	     snapshot_index < number_of_snapshots;
	     snapshot_index++ )
	{
		if( libcdata_array_get_entry_by_index(
		     internal_handle->snapshot_values_array,
		     snapshot_index,
		     (intptr_t **) &snapshot_values,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve snapshot values: %d from array.",
			 function,
			 snapshot_index );

			goto on_error;
		}
		for( parent_snapshot_index = 0;
		     parent_snapshot_index < number_of_snapshots;
		     parent_snapshot_index++ )
		{
			if( libcdata_array_get_entry_by_index(
			     internal_handle->snapshot_values_array,
			     parent_snapshot_index,
			     (intptr_t **) &parent_snapshot_values,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
				 "%s: unable to retrieve snapshot values: %d from array.",
				 function,
				 parent_snapshot_index );

				goto on_error;
			}
			if( memory_compare(
			     snapshot_values->parent_identifier,
			     parent_snapshot_values->identifier,
			     16 ) == 0 )
			{
				snapshot_values->parent_snapshot_values = parent_snapshot_values;

				break;
			}
		}
		if( libphdi_extent_table_initialize_extents(
		     snapshot_values->extent_table,
		     internal_handle->io_handle,
		     internal_handle->disk_type,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to initialize extent table extents.",
			 function );

			goto on_error;
		}
		for( extent_index = 0;
		     extent_index < number_of_extents;
		     extent_index++ )
		{
			if( libcdata_array_get_entry_by_index(
			     internal_handle->extent_values_array,
			     extent_index,
			     (intptr_t **) &extent_values,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
				 "%s: unable to retrieve extent values: %d from array.",
				 function,
				 extent_index );

				goto on_error;
			}
			if( libphdi_extent_values_get_number_of_images(
			     extent_values,
			     &number_of_images,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
				 "%s: unable to retrieve number of images.",
				 function );

				goto on_error;
			}
			for( image_index = 0;
			     image_index < number_of_images;
			     image_index++ )
			{
				if( libphdi_extent_values_get_image_values_by_index(
				     extent_values,
				     image_index,
				     &image_values,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
					 "%s: unable to retrieve image values: %d from array.",
					 function,
					 image_index );

					goto on_error;
				}
				if( memory_compare(
				     snapshot_values->identifier,
				     image_values->identifier,
				     16 ) == 0 )
				{
					if( libphdi_image_values_get_type(
					     image_values,
					     &image_type,
					     error ) != 1 )
					{
						libcerror_error_set(
						 error,
						 LIBCERROR_ERROR_DOMAIN_RUNTIME,
						 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
						 "%s: unable to retrieve type from image values: %d of extent values: %d.",
						 function,
						 image_index,
						 extent_index );

						goto on_error;
					}
					if( libbfio_pool_get_size(
					     file_io_pool,
					     image_values->file_io_pool_entry,
					     &image_file_size,
					     error ) != 1 )
					{
						libcerror_error_set(
						 error,
						 LIBCERROR_ERROR_DOMAIN_RUNTIME,
						 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
						 "%s: unable to retrieve size of file IO pool entry: %d.",
						 function,
						 image_values->file_io_pool_entry );

						goto on_error;
					}
					if( libphdi_extent_table_append_extent(
					     snapshot_values->extent_table,
					     image_type,
					     image_values->file_io_pool_entry,
					     image_file_size,
					     extent_values->offset,
					     extent_values->size,
					     error ) != 1 )
					{
						libcerror_error_set(
						 error,
						 LIBCERROR_ERROR_DOMAIN_RUNTIME,
						 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
						 "%s: unable to set extent: %d in table.",
						 function,
						 extent_index );

						goto on_error;
					}
				}
			}
		}
		if( snapshot_index == 0 )
		{
		     internal_handle->current_snapshot_values = snapshot_values;
		}
		if( internal_handle->io_handle->abort == 1 )
		{
			goto on_error;
		}
	}
	return( 1 );

on_error:
	if( storage_image != NULL )
	{
		libphdi_storage_image_free(
		 &storage_image,
		 NULL );
	}
	return( -1 );
}

/* Reads a block of data at a specific offset into a buffer using a Basic File IO (bfio) pool
 * Returns the number of bytes read or -1 on error
 */
ssize_t libphdi_internal_handle_read_block_from_file_io_pool(
         libphdi_snapshot_values_t *snapshot_values,
         libbfio_pool_t *file_io_pool,
         void *buffer,
         size_t buffer_size,
         off64_t file_offset,
         int level,
         libcerror_error_t **error )
{
	libphdi_block_descriptor_t *block_descriptor = NULL;
	libphdi_storage_image_t *storage_image       = NULL;
	static char *function                        = "libphdi_internal_handle_read_block_from_file_io_pool";
	size64_t block_size                          = 0;
	size_t read_size                             = 0;
	ssize_t read_count                           = 0;
	off64_t block_offset                         = 0;
	off64_t storage_image_data_offset            = 0;
	int extent_number                            = 0;
	int result                                   = 0;

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
	if( buffer == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid buffer.",
		 function );

		return( -1 );
	}
	if( buffer_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid element data size value exceeds maximum.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: requested offset: %" PRIi64 " (0x%08" PRIx64 ") at level: %d\n",
		 function,
		 file_offset,
		 file_offset,
		 level );
	}
#endif
	if( libphdi_extent_table_get_extent_file_at_offset(
	     snapshot_values->extent_table,
	     file_offset,
	     file_io_pool,
	     &extent_number,
	     &storage_image_data_offset,
	     &storage_image,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve extent file at offset: %" PRIi64 " (0x%08" PRIx64 ") from extent table.",
		 function,
		 file_offset,
		 file_offset );

		return( -1 );
	}
	if( libphdi_storage_image_get_block_size(
	     storage_image,
	     &block_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve block size from storage image.",
		 function );

		return( -1 );
	}
	result = libphdi_storage_image_get_block_descriptor_at_offset(
	          storage_image,
	          storage_image_data_offset,
	          &block_descriptor,
	          &block_offset,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve block descriptor at offset: %" PRIi64 " (0x%08" PRIx64 ") from storage image.",
		 function,
		 storage_image_data_offset,
		 storage_image_data_offset );

		return( -1 );
	}
	else if( result == 0 )
	{
		block_offset = storage_image_data_offset % block_size;
	}
	read_size = (size_t) block_size - block_offset;

	if( read_size > buffer_size )
	{
		read_size = buffer_size;
	}
	if( result != 0 )
	{
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: reading block descriptor offset: %" PRIi64 " (0x%08" PRIx64 ")\n",
			 function,
			 block_descriptor->file_offset,
			 block_descriptor->file_offset );

			libcnotify_printf(
			 "%s: reading block offset: %" PRIi64 " (0x%08" PRIx64 ")\n",
			 function,
			 block_offset,
			 block_offset );

			libcnotify_printf(
			 "%s: reading from file IO pool entry: %d\n",
			 function,
			 block_descriptor->file_io_pool_entry );

			libcnotify_printf(
			 "%s: reading from offset: %" PRIi64 " (0x%08" PRIx64 ")\n",
			 function,
			 block_descriptor->file_offset + block_offset,
			 block_descriptor->file_offset + block_offset );
		}
#endif
		read_count = libbfio_pool_read_buffer_at_offset(
		              file_io_pool,
		              block_descriptor->file_io_pool_entry,
		              buffer,
		              read_size,
		              block_descriptor->file_offset + block_offset,
		              error );

		if( read_count == -1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read data from file IO pool entry: %d at offset: %" PRIi64 " (0x%08" PRIx64 ").",
			 function,
			 block_descriptor->file_io_pool_entry,
			 block_descriptor->file_offset + block_offset,
			 block_descriptor->file_offset + block_offset );

			return( -1 );
		}
	}
	else if( snapshot_values->parent_snapshot_values != NULL )
	{
		read_count = libphdi_internal_handle_read_block_from_file_io_pool(
			      snapshot_values->parent_snapshot_values,
		              file_io_pool,
			      buffer,
			      read_size,
			      file_offset,
			      level + 1,
			      error );

		if( read_count == -1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read buffer from parent snapshot at offset: %" PRIi64 " (0x%08" PRIx64 ").",
			 function,
			 file_offset,
			 file_offset );

			return( -1 );
		}
	}
	else
	{
		if( memory_set(
		     buffer,
		     0,
		     read_size ) == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_SET_FAILED,
			 "%s: unable to fill buffer with sparse block.",
			 function );

			return( -1 );
		}
		read_count = (ssize_t) read_size;
	}
	return( read_count );
}

/* Reads (media) data at the current offset into a buffer using a Basic File IO (bfio) pool
 * This function is not multi-thread safe acquire write lock before call
 * Returns the number of bytes read or -1 on error
 */
ssize_t libphdi_internal_handle_read_buffer_from_file_io_pool(
         libphdi_internal_handle_t *internal_handle,
         libbfio_pool_t *file_io_pool,
         void *buffer,
         size_t buffer_size,
         libcerror_error_t **error )
{
	static char *function = "libphdi_internal_handle_read_buffer_from_file_io_pool";
	size_t buffer_offset  = 0;
	size_t read_size      = 0;
	ssize_t read_count    = 0;

	if( internal_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	if( internal_handle->disk_parameters == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid handle - missing disk parameters.",
		 function );

		return( -1 );
	}
	if( internal_handle->current_snapshot_values == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid handle - missing current snapshot values.",
		 function );

		return( -1 );
	}
	if( internal_handle->current_offset < 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid handle - invalid IO handle - current offset value out of bounds.",
		 function );

		return( -1 );
	}
	if( buffer == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid buffer.",
		 function );

		return( -1 );
	}
	if( buffer_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid element data size value exceeds maximum.",
		 function );

		return( -1 );
	}
	internal_handle->io_handle->abort = 0;

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: requested offset: %" PRIi64 " (0x%08" PRIx64 ")\n",
		 function,
		 internal_handle->current_offset,
		 internal_handle->current_offset );
	}
#endif
	if( (size64_t) internal_handle->current_offset >= internal_handle->disk_parameters->media_size )
	{
		return( 0 );
	}
	if( internal_handle->current_snapshot_values->extent_table->extent_files_stream != NULL )
	{
		read_size = buffer_size;

		if( ( (size64_t) read_size > internal_handle->disk_parameters->media_size )
		 || ( (size64_t) internal_handle->current_offset > ( internal_handle->disk_parameters->media_size - read_size ) ) )
		{
			read_size = (size_t) ( internal_handle->disk_parameters->media_size - internal_handle->current_offset );
		}
		read_count = libfdata_stream_read_buffer_at_offset(
		              internal_handle->current_snapshot_values->extent_table->extent_files_stream,
			      (intptr_t *) file_io_pool,
			      (uint8_t *) buffer,
			      read_size,
			      internal_handle->current_offset,
			      0,
			      error );

		if( read_count != (ssize_t) read_size )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read buffer from extent files stream at offset: %" PRIi64 " (0x%" PRIx64 ").",
			 function,
			 internal_handle->current_offset,
			 internal_handle->current_offset );

			return( -1 );
		}
		buffer_offset = read_size;

		internal_handle->current_offset += (off64_t) read_size;
	}
	else
	{
		while( buffer_offset < buffer_size )
		{
			read_size = buffer_size - buffer_offset;

			if( ( (size64_t) read_size > internal_handle->disk_parameters->media_size )
			 || ( (size64_t) internal_handle->current_offset > ( internal_handle->disk_parameters->media_size - read_size ) ) )
			{
				read_size = (size_t) ( internal_handle->disk_parameters->media_size - internal_handle->current_offset );
			}
			read_count = libphdi_internal_handle_read_block_from_file_io_pool(
				      internal_handle->current_snapshot_values,
			              file_io_pool,
				      &(( (uint8_t *) buffer )[ buffer_offset ] ),
				      read_size,
				      internal_handle->current_offset,
				      0,
				      error );

			if( read_count == -1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_IO,
				 LIBCERROR_IO_ERROR_READ_FAILED,
				 "%s: unable to read buffer from current snapshot.",
				 function );

				return( -1 );
			}
			buffer_offset += read_count;

			internal_handle->current_offset += (off64_t) read_count;

			if( (size64_t) internal_handle->current_offset >= internal_handle->disk_parameters->media_size )
			{
				break;
			}
			if( internal_handle->io_handle->abort != 0 )
			{
				break;
			}
		}
	}
	return( (ssize_t) buffer_offset );
}

/* Reads (media) data from the current offset into a buffer
 * Returns the number of bytes read or -1 on error
 */
ssize_t libphdi_handle_read_buffer(
         libphdi_handle_t *handle,
         void *buffer,
         size_t buffer_size,
         libcerror_error_t **error )
{
	libphdi_internal_handle_t *internal_handle = NULL;
	static char *function                      = "libphdi_handle_read_buffer";
	ssize_t read_count                         = 0;

	if( handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	internal_handle = (libphdi_internal_handle_t *) handle;

	if( internal_handle->extent_data_file_io_pool == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid handle - missing extent data file IO pool.",
		 function );

		return( -1 );
	}
#if defined( HAVE_LIBPHDI_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_grab_for_write(
	     internal_handle->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to grab read/write lock for writing.",
		 function );

		return( -1 );
	}
#endif
	read_count = libphdi_internal_handle_read_buffer_from_file_io_pool(
		      internal_handle,
	              internal_handle->extent_data_file_io_pool,
		      buffer,
		      buffer_size,
		      error );

	if( read_count == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read buffer.",
		 function );

		read_count = -1;
	}
#if defined( HAVE_LIBPHDI_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_release_for_write(
	     internal_handle->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to release read/write lock for writing.",
		 function );

		return( -1 );
	}
#endif
	return( read_count );
}

/* Reads (media) data at a specific offset
 * Returns the number of bytes read or -1 on error
 */
ssize_t libphdi_handle_read_buffer_at_offset(
         libphdi_handle_t *handle,
         void *buffer,
         size_t buffer_size,
         off64_t offset,
         libcerror_error_t **error )
{
	libphdi_internal_handle_t *internal_handle = NULL;
	static char *function                      = "libphdi_handle_read_buffer_at_offset";
	ssize_t read_count                         = 0;

	if( handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	internal_handle = (libphdi_internal_handle_t *) handle;

	if( internal_handle->extent_data_file_io_pool == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid handle - missing extent data file IO pool.",
		 function );

		return( -1 );
	}
#if defined( HAVE_LIBPHDI_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_grab_for_write(
	     internal_handle->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to grab read/write lock for writing.",
		 function );

		return( -1 );
	}
#endif
	if( libphdi_internal_handle_seek_offset(
	     internal_handle,
	     offset,
	     SEEK_SET,
	     error ) == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_SEEK_FAILED,
		 "%s: unable to seek offset.",
		 function );

		read_count = -1;
	}
	else
	{
		read_count = libphdi_internal_handle_read_buffer_from_file_io_pool(
			      internal_handle,
		              internal_handle->extent_data_file_io_pool,
			      buffer,
			      buffer_size,
			      error );

		if( read_count == -1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read buffer.",
			 function );

			read_count = -1;
		}
	}
#if defined( HAVE_LIBPHDI_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_release_for_write(
	     internal_handle->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to release read/write lock for writing.",
		 function );

		return( -1 );
	}
#endif
	return( read_count );
}

/* Seeks a certain offset of the (media) data
 * This function is not multi-thread safe acquire write lock before call
 * Returns the offset if seek is successful or -1 on error
 */
off64_t libphdi_internal_handle_seek_offset(
         libphdi_internal_handle_t *internal_handle,
         off64_t offset,
         int whence,
         libcerror_error_t **error )
{
	static char *function = "libphdi_handle_seek_offset";

	if( internal_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	if( internal_handle->disk_parameters == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid handle - missing disk parameters.",
		 function );

		return( -1 );
	}
	if( ( whence != SEEK_CUR )
	 && ( whence != SEEK_END )
	 && ( whence != SEEK_SET ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported whence.",
		 function );

		return( -1 );
	}
	if( whence == SEEK_CUR )
	{
		offset += internal_handle->current_offset;
	}
	else if( whence == SEEK_END )
	{
		offset += (off64_t) internal_handle->disk_parameters->media_size;
	}
	if( offset < 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid offset value out of bounds.",
		 function );

		return( -1 );
	}
	internal_handle->current_offset = offset;

	return( offset );
}

/* Seeks a certain offset of the (media) data
 * Returns the offset if seek is successful or -1 on error
 */
off64_t libphdi_handle_seek_offset(
         libphdi_handle_t *handle,
         off64_t offset,
         int whence,
         libcerror_error_t **error )
{
	libphdi_internal_handle_t *internal_handle = NULL;
	static char *function                      = "libphdi_handle_seek_offset";

	if( handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	internal_handle = (libphdi_internal_handle_t *) handle;

	if( internal_handle->extent_data_file_io_pool == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid handle - missing extent data file IO pool.",
		 function );

		return( -1 );
	}
#if defined( HAVE_LIBPHDI_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_grab_for_write(
	     internal_handle->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to grab read/write lock for writing.",
		 function );

		return( -1 );
	}
#endif
	offset = libphdi_internal_handle_seek_offset(
	          internal_handle,
	          offset,
	          whence,
	          error );

	if( offset == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_SEEK_FAILED,
		 "%s: unable to seek offset.",
		 function );

		offset = -1;
	}
#if defined( HAVE_LIBPHDI_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_release_for_write(
	     internal_handle->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to release read/write lock for writing.",
		 function );

		return( -1 );
	}
#endif
	return( offset );
}

/* Retrieves the current offset of the (media) data
 * Returns 1 if successful or -1 on error
 */
int libphdi_handle_get_offset(
     libphdi_handle_t *handle,
     off64_t *offset,
     libcerror_error_t **error )
{
	libphdi_internal_handle_t *internal_handle = NULL;
	static char *function                      = "libphdi_handle_get_offset";

	if( handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	internal_handle = (libphdi_internal_handle_t *) handle;

	if( internal_handle->file_io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid handle - missing file IO handle.",
		 function );

		return( -1 );
	}
	if( offset == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid offset.",
		 function );

		return( -1 );
	}
#if defined( HAVE_LIBPHDI_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_grab_for_read(
	     internal_handle->read_write_lock,
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
	*offset = internal_handle->current_offset;

#if defined( HAVE_LIBPHDI_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_release_for_read(
	     internal_handle->read_write_lock,
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
	return( 1 );
}

/* Sets the maximum number of (concurrent) open file handles
 * Returns 1 if successful or -1 on error
 */
int libphdi_handle_set_maximum_number_of_open_handles(
     libphdi_handle_t *handle,
     int maximum_number_of_open_handles,
     libcerror_error_t **error )
{
	libphdi_internal_handle_t *internal_handle = NULL;
	static char *function                      = "libphdi_handle_set_maximum_number_of_open_handles";
	int result                                 = 1;

	if( handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	internal_handle = (libphdi_internal_handle_t *) handle;

#if defined( HAVE_LIBPHDI_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_grab_for_write(
	     internal_handle->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to grab read/write lock for writing.",
		 function );

		return( -1 );
	}
#endif
	if( internal_handle->extent_data_file_io_pool != NULL )
	{
		if( libbfio_pool_set_maximum_number_of_open_handles(
		     internal_handle->extent_data_file_io_pool,
		     maximum_number_of_open_handles,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
			 "%s: unable to set maximum number of open handles in extent data file IO pool.",
			 function );

			result = -1;
		}
	}
	if( result == 1 )
	{
		internal_handle->maximum_number_of_open_handles = maximum_number_of_open_handles;
	}
#if defined( HAVE_LIBPHDI_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_release_for_write(
	     internal_handle->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to release read/write lock for writing.",
		 function );

		return( -1 );
	}
#endif
	return( result );
}

/* Sets the path to the extent data files
 * Returns 1 if successful or -1 on error
 */
int libphdi_handle_set_extent_data_files_path(
     libphdi_handle_t *handle,
     const char *path,
     size_t path_length,
     libcerror_error_t **error )
{
	libphdi_internal_handle_t *internal_handle = NULL;
	static char *function                      = "libphdi_handle_set_extent_data_files_path";
	int result                                 = 1;

	if( handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	internal_handle = (libphdi_internal_handle_t *) handle;

	if( path == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid path.",
		 function );

		return( -1 );
	}
	if( path_length > (size_t) ( SSIZE_MAX - 1 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid path length value exceeds maximum.",
		 function );

		return( -1 );
	}
#if defined( HAVE_LIBPHDI_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_grab_for_write(
	     internal_handle->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to grab read/write lock for writing.",
		 function );

		return( -1 );
	}
#endif
	if( libphdi_data_files_set_path(
	     internal_handle->data_files,
	     path,
	     path_length,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set data files path.",
		 function );

		result = -1;
	}
#if defined( HAVE_LIBPHDI_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_release_for_write(
	     internal_handle->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to release read/write lock for writing.",
		 function );

		return( -1 );
	}
#endif
	return( result );
}

#if defined( HAVE_WIDE_CHARACTER_TYPE )

/* Sets the path to the extent data files
 * Returns 1 if successful or -1 on error
 */
int libphdi_handle_set_extent_data_files_path_wide(
     libphdi_handle_t *handle,
     const wchar_t *path,
     size_t path_length,
     libcerror_error_t **error )
{
	libphdi_internal_handle_t *internal_handle = NULL;
	static char *function                      = "libphdi_handle_set_extent_data_files_path_wide";
	int result                                 = 1;

	if( handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	internal_handle = (libphdi_internal_handle_t *) handle;

	if( path == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid path.",
		 function );

		return( -1 );
	}
	if( path_length > (size_t) ( SSIZE_MAX - 1 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid path length value exceeds maximum.",
		 function );

		return( -1 );
	}
#if defined( HAVE_LIBPHDI_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_grab_for_write(
	     internal_handle->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to grab read/write lock for writing.",
		 function );

		return( -1 );
	}
#endif
	if( libphdi_data_files_set_path_wide(
	     internal_handle->data_files,
	     path,
	     path_length,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set data files path.",
		 function );

		result = -1;
	}
#if defined( HAVE_LIBPHDI_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_release_for_write(
	     internal_handle->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to release read/write lock for writing.",
		 function );

		return( -1 );
	}
#endif
	return( result );
}

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

/* Retrieves the number of media size
 * Returns 1 if successful or -1 on error
 */
int libphdi_handle_get_media_size(
     libphdi_handle_t *handle,
     size64_t *media_size,
     libcerror_error_t **error )
{
	libphdi_internal_handle_t *internal_handle = NULL;
	static char *function                      = "libphdi_handle_get_media_size";
	int result                                 = 1;

	if( handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	internal_handle = (libphdi_internal_handle_t *) handle;

#if defined( HAVE_LIBPHDI_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_grab_for_read(
	     internal_handle->read_write_lock,
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
	if( libphdi_disk_parameters_get_media_size(
	     internal_handle->disk_parameters,
	     media_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve media size from disk parameters.",
		 function );

		result = -1;
	}
#if defined( HAVE_LIBPHDI_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_release_for_read(
	     internal_handle->read_write_lock,
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

/* Retrieves the size of the UTF-8 encoded name
 * The returned size includes the end of string character
 * Returns 1 if successful, 0 if not available or -1 on error
 */
int libphdi_handle_get_utf8_name_size(
     libphdi_handle_t *handle,
     size_t *utf8_string_size,
     libcerror_error_t **error )
{
	libphdi_internal_handle_t *internal_handle = NULL;
	static char *function                      = "libphdi_handle_get_utf8_name_size";
	int result                                 = 0;

	if( handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	internal_handle = (libphdi_internal_handle_t *) handle;

#if defined( HAVE_LIBPHDI_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_grab_for_write(
	     internal_handle->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to grab read/write lock for writing.",
		 function );

		return( -1 );
	}
#endif
	result = libphdi_disk_parameters_get_utf8_name_size(
	          internal_handle->disk_parameters,
	          utf8_string_size,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve size of UTF-8 name from disk parameters.",
		 function );

		result = -1;
	}
#if defined( HAVE_LIBPHDI_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_release_for_write(
	     internal_handle->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to release read/write lock for writing.",
		 function );

		return( -1 );
	}
#endif
	return( result );
}

/* Retrieves the UTF-8 encoded name
 * The size should include the end of string character
 * Returns 1 if successful, 0 if not available or -1 on error
 */
int libphdi_handle_get_utf8_name(
     libphdi_handle_t *handle,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error )
{
	libphdi_internal_handle_t *internal_handle = NULL;
	static char *function                      = "libphdi_handle_get_utf8_name";
	int result                                 = 0;

	if( handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	internal_handle = (libphdi_internal_handle_t *) handle;

#if defined( HAVE_LIBPHDI_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_grab_for_write(
	     internal_handle->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to grab read/write lock for writing.",
		 function );

		return( -1 );
	}
#endif
	result = libphdi_disk_parameters_get_utf8_name(
	          internal_handle->disk_parameters,
	          utf8_string,
	          utf8_string_size,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve UTF-8 name from disk parameters.",
		 function );

		result = -1;
	}
#if defined( HAVE_LIBPHDI_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_release_for_write(
	     internal_handle->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to release read/write lock for writing.",
		 function );

		return( -1 );
	}
#endif
	return( result );
}

/* Retrieves the size of the UTF-16 encoded name
 * The returned size includes the end of string character
 * Returns 1 if successful, 0 if not available or -1 on error
 */
int libphdi_handle_get_utf16_name_size(
     libphdi_handle_t *handle,
     size_t *utf16_string_size,
     libcerror_error_t **error )
{
	libphdi_internal_handle_t *internal_handle = NULL;
	static char *function                      = "libphdi_handle_get_utf16_name_size";
	int result                                 = 0;

	if( handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	internal_handle = (libphdi_internal_handle_t *) handle;

#if defined( HAVE_LIBPHDI_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_grab_for_write(
	     internal_handle->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to grab read/write lock for writing.",
		 function );

		return( -1 );
	}
#endif
	result = libphdi_disk_parameters_get_utf16_name_size(
	          internal_handle->disk_parameters,
	          utf16_string_size,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve size of UTF-16 name from disk parameters.",
		 function );

		result = -1;
	}
#if defined( HAVE_LIBPHDI_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_release_for_write(
	     internal_handle->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to release read/write lock for writing.",
		 function );

		return( -1 );
	}
#endif
	return( result );
}

/* Retrieves the UTF-16 encoded name
 * The size should include the end of string character
 * Returns 1 if successful, 0 if not available or -1 on error
 */
int libphdi_handle_get_utf16_name(
     libphdi_handle_t *handle,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error )
{
	libphdi_internal_handle_t *internal_handle = NULL;
	static char *function                      = "libphdi_handle_get_utf16_name";
	int result                                 = 0;

	if( handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	internal_handle = (libphdi_internal_handle_t *) handle;

#if defined( HAVE_LIBPHDI_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_grab_for_write(
	     internal_handle->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to grab read/write lock for writing.",
		 function );

		return( -1 );
	}
#endif
	result = libphdi_disk_parameters_get_utf16_name(
	          internal_handle->disk_parameters,
	          utf16_string,
	          utf16_string_size,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve UTF-16 name from disk parameters.",
		 function );

		result = -1;
	}
#if defined( HAVE_LIBPHDI_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_release_for_write(
	     internal_handle->read_write_lock,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to release read/write lock for writing.",
		 function );

		return( -1 );
	}
#endif
	return( result );
}

/* Retrieves the number of extents
 * Returns 1 if successful or -1 on error
 */
int libphdi_handle_get_number_of_extents(
     libphdi_handle_t *handle,
     int *number_of_extents,
     libcerror_error_t **error )
{
	libphdi_internal_handle_t *internal_handle = NULL;
	static char *function                      = "libphdi_handle_get_number_of_extents";
	int result                                 = 1;

	if( handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	internal_handle = (libphdi_internal_handle_t *) handle;

#if defined( HAVE_LIBPHDI_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_grab_for_read(
	     internal_handle->read_write_lock,
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
	if( libcdata_array_get_number_of_entries(
	     internal_handle->extent_values_array,
	     number_of_extents,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of extents.",
		 function );

		result = -1;
	}
#if defined( HAVE_LIBPHDI_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_release_for_read(
	     internal_handle->read_write_lock,
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

/* Retrieves a specific extent descriptor
 * Returns 1 if successful or -1 on error
 */
int libphdi_handle_get_extent_descriptor_by_index(
     libphdi_handle_t *handle,
     int extent_index,
     libphdi_extent_descriptor_t **extent_descriptor,
     libcerror_error_t **error )
{
	libphdi_extent_values_t *extent_values     = NULL;
	libphdi_internal_handle_t *internal_handle = NULL;
	static char *function                      = "libphdi_handle_get_extent_descriptor_by_index";
	int result                                 = 1;

	if( handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	internal_handle = (libphdi_internal_handle_t *) handle;

	if( extent_descriptor == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid extent descriptor.",
		 function );

		return( -1 );
	}
	if( *extent_descriptor != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid extent descriptor value already set.",
		 function );

		return( -1 );
	}
#if defined( HAVE_LIBPHDI_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_grab_for_read(
	     internal_handle->read_write_lock,
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
	if( libcdata_array_get_entry_by_index(
	     internal_handle->extent_values_array,
	     extent_index,
	     (intptr_t **) &extent_values,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve extent: %d from array.",
		 function,
		 extent_index );

		result = -1;
	}
	else if( libphdi_extent_descriptor_initialize(
	          extent_descriptor,
	          extent_values,
	          error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create extent descriptor.",
		 function );

		result = -1;
	}
#if defined( HAVE_LIBPHDI_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_release_for_read(
	     internal_handle->read_write_lock,
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


/* Retrieves the number of snapshots
 * Returns 1 if successful or -1 on error
 */
int libphdi_handle_get_number_of_snapshots(
     libphdi_handle_t *handle,
     int *number_of_snapshots,
     libcerror_error_t **error )
{
	libphdi_internal_handle_t *internal_handle = NULL;
	static char *function                      = "libphdi_handle_get_number_of_snapshots";
	int result                                 = 1;

	if( handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	internal_handle = (libphdi_internal_handle_t *) handle;

#if defined( HAVE_LIBPHDI_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_grab_for_read(
	     internal_handle->read_write_lock,
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
	if( libcdata_array_get_number_of_entries(
	     internal_handle->snapshot_values_array,
	     number_of_snapshots,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of snapshots.",
		 function );

		result = -1;
	}
#if defined( HAVE_LIBPHDI_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_release_for_read(
	     internal_handle->read_write_lock,
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

/* Retrieves a specific snapshot
 * Returns 1 if successful or -1 on error
 */
int libphdi_handle_get_snapshot_by_index(
     libphdi_handle_t *handle,
     int snapshot_index,
     libphdi_snapshot_t **snapshot,
     libcerror_error_t **error )
{
	libphdi_internal_handle_t *internal_handle = NULL;
	libphdi_snapshot_values_t *snapshot_values = NULL;
	static char *function                      = "libphdi_handle_get_snapshot_by_index";
	int result                                 = 1;

	if( handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	internal_handle = (libphdi_internal_handle_t *) handle;

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
#if defined( HAVE_LIBPHDI_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_grab_for_read(
	     internal_handle->read_write_lock,
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
	if( libcdata_array_get_entry_by_index(
	     internal_handle->snapshot_values_array,
	     snapshot_index,
	     (intptr_t **) &snapshot_values,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve snapshot: %d from array.",
		 function,
		 snapshot_index );

		result = -1;
	}
	else if( libphdi_snapshot_initialize(
	          snapshot,
	          snapshot_values,
	          error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create snapshot.",
		 function );

		result = -1;
	}
#if defined( HAVE_LIBPHDI_MULTI_THREAD_SUPPORT )
	if( libcthreads_read_write_lock_release_for_read(
	     internal_handle->read_write_lock,
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

