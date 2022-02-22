/*
 * Info handle
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
#include <byte_stream.h>
#include <memory.h>
#include <narrow_string.h>
#include <system_string.h>
#include <types.h>
#include <wide_string.h>

#include "byte_size_string.h"
#include "info_handle.h"
#include "phditools_libcerror.h"
#include "phditools_libcnotify.h"
#include "phditools_libfguid.h"
#include "phditools_libphdi.h"

#define INFO_HANDLE_NOTIFY_STREAM		stdout

/* Creates an info handle
 * Make sure the value info_handle is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int info_handle_initialize(
     info_handle_t **info_handle,
     libcerror_error_t **error )
{
	static char *function = "info_handle_initialize";

	if( info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
	if( *info_handle == NULL )
	{
		*info_handle = memory_allocate_structure(
		                info_handle_t );

		if( *info_handle == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to create info handle.",
			 function );

			goto on_error;
		}
		if( memory_set(
		     *info_handle,
		     0,
		     sizeof( info_handle_t ) ) == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_SET_FAILED,
			 "%s: unable to clear info handle.",
			 function );

			goto on_error;
		}
		if( libphdi_handle_initialize(
		     &( ( *info_handle )->input_handle ),
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to initialize input handle.",
			 function );

			goto on_error;
		}
		( *info_handle )->notify_stream = INFO_HANDLE_NOTIFY_STREAM;
	}
	return( 1 );

on_error:
	if( *info_handle != NULL )
	{
		memory_free(
		 *info_handle );

		*info_handle = NULL;
	}
	return( -1 );
}

/* Frees an info handle
 * Returns 1 if successful or -1 on error
 */
int info_handle_free(
     info_handle_t **info_handle,
     libcerror_error_t **error )
{
	static char *function = "info_handle_free";
	int result            = 1;

	if( info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
	if( *info_handle != NULL )
	{
		if( ( *info_handle )->input_handle != NULL )
		{
			if( libphdi_handle_free(
			     &( ( *info_handle )->input_handle ),
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
				 "%s: unable to free input.",
				 function );

				result = -1;
			}
		}
		memory_free(
		 *info_handle );

		*info_handle = NULL;
	}
	return( result );
}

/* Signals the info handle to abort
 * Returns 1 if successful or -1 on error
 */
int info_handle_signal_abort(
     info_handle_t *info_handle,
     libcerror_error_t **error )
{
	static char *function = "info_handle_signal_abort";

	if( info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
	if( info_handle->input_handle != NULL )
	{
		if( libphdi_handle_signal_abort(
		     info_handle->input_handle,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
			 "%s: unable to signal input handle to abort.",
			 function );

			return( -1 );
		}
	}
	return( 1 );
}

/* Opens the info handle
 * Returns 1 if successful or -1 on error
 */
int info_handle_open_input(
     info_handle_t *info_handle,
     const system_character_t *filename,
     libcerror_error_t **error )
{
	static char *function = "info_handle_open_input";

	if( info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	if( libphdi_handle_open_wide(
	     info_handle->input_handle,
	     filename,
	     LIBPHDI_OPEN_READ,
	     error ) != 1 )
#else
	if( libphdi_handle_open(
	     info_handle->input_handle,
	     filename,
	     LIBPHDI_OPEN_READ,
	     error ) != 1 )
#endif
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_OPEN_FAILED,
		 "%s: unable to open input handle.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Closes the info handle
 * Returns the 0 if succesful or -1 on error
 */
int info_handle_close(
     info_handle_t *info_handle,
     libcerror_error_t **error )
{
	static char *function = "info_handle_close";

	if( info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
	if( info_handle->input_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid info handle - missing input handle.",
		 function );

		return( -1 );
	}
	if( libphdi_handle_close(
	     info_handle->input_handle,
	     error ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_CLOSE_FAILED,
		 "%s: unable to close input handle.",
		 function );

		return( -1 );
	}
	return( 0 );
}

/* Prints the file information to a stream
 * Returns 1 if successful or -1 on error
 */
int info_handle_file_fprint(
     info_handle_t *info_handle,
     libcerror_error_t **error )
{
	system_character_t byte_size_string[ 16 ];
	system_character_t guid_string[ 48 ];
	uint8_t guid_data[ 16 ];

	libfguid_identifier_t *guid                    = NULL;
	libphdi_extent_descriptor_t *extent_descriptor = NULL;
	libphdi_image_descriptor_t *image_descriptor   = NULL;
	libphdi_snapshot_t *snapshot                   = NULL;
	system_character_t *value_string               = NULL;
	static char *function                          = "info_handle_file_fprint";
	size64_t extent_size                           = 0;
	size64_t media_size                            = 0;
	size_t value_string_size                       = 0;
	off64_t extent_offset                          = 0;
	int extent_index                               = 0;
	int image_index                                = 0;
	int image_type                                 = 0;
	int number_of_extents                          = 0;
	int number_of_images                           = 0;
	int number_of_snapshots                        = 0;
	int result                                     = 0;
	int snapshot_index                             = 0;

	if( info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
	fprintf(
	 info_handle->notify_stream,
	 "Parallels Hard Disk image information:\n" );

	if( libphdi_handle_get_media_size(
	     info_handle->input_handle,
	     &media_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve media size.",
		 function );

		goto on_error;
	}
	fprintf(
	 info_handle->notify_stream,
	 "\tMedia size\t\t: %" PRIu64 " bytes\n",
	 media_size );

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libphdi_handle_get_utf16_name_size(
	          info_handle->input_handle,
	          &value_string_size,
	          error );
#else
	result = libphdi_handle_get_utf8_name_size(
	          info_handle->input_handle,
	          &value_string_size,
	          error );
#endif
	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve name string size.",
		 function );

		goto on_error;
	}
	if( ( result != 0 )
	 && ( value_string_size > 0 ) )
	{
		value_string = system_string_allocate(
		                value_string_size );

		if( value_string == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to create name string.",
			 function );

			goto on_error;
		}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
		result = libphdi_handle_get_utf16_name(
		          info_handle->input_handle,
		          (uint16_t *) value_string,
		          value_string_size,
		          error );
#else
		result = libphdi_handle_get_utf8_name(
		          info_handle->input_handle,
		          (uint8_t *) value_string,
		          value_string_size,
		          error );
#endif
		if( result != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve name string.",
			 function );

			goto on_error;
		}
		fprintf(
		 info_handle->notify_stream,
		 "\tName\t\t\t: %" PRIs_SYSTEM "\n",
		 value_string );

		memory_free(
		 value_string );

		value_string = NULL;
	}
	if( libphdi_handle_get_number_of_extents(
	     info_handle->input_handle,
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
	fprintf(
	 info_handle->notify_stream,
	 "\tNumber of extents\t: %d\n",
	 number_of_extents );

	if( libphdi_handle_get_number_of_snapshots(
	     info_handle->input_handle,
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
	fprintf(
	 info_handle->notify_stream,
	 "\tNumber of snapshots\t: %d\n",
	 number_of_snapshots );

	fprintf(
	 info_handle->notify_stream,
	 "\n" );

	for( extent_index = 0;
	     extent_index < number_of_extents;
	     extent_index++ )
	{
		fprintf(
		 info_handle->notify_stream,
		 "Extent: %d\n",
		 extent_index + 1 );

		if( libphdi_handle_get_extent_descriptor_by_index(
		     info_handle->input_handle,
		     extent_index,
		     &extent_descriptor,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve extent: %d descriptor.",
			 function,
			 extent_index );

			goto on_error;
		}
		if( libphdi_extent_descriptor_get_range(
		     extent_descriptor,
		     &extent_offset,
		     &extent_size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve extent: %d descriptor range.",
			 function,
			 extent_index );

			goto on_error;
		}
		fprintf(
		 info_handle->notify_stream,
		 "\tStart offset\t\t: %" PRIi64 "\n",
		 extent_offset );

		result = byte_size_string_create(
		          byte_size_string,
		          16,
		          extent_size,
		          BYTE_SIZE_STRING_UNIT_MEBIBYTE,
		          NULL );

		if( result == 1 )
		{
			fprintf(
			 info_handle->notify_stream,
			 "\tSize\t\t\t: %" PRIs_SYSTEM " (%" PRIu64 " bytes)\n",
			 byte_size_string,
			 extent_size );
		}
		else
		{
			fprintf(
			 info_handle->notify_stream,
			 "\tSize\t\t\t: %" PRIu64 " bytes\n",
			 extent_size );
		}
		if( libphdi_extent_descriptor_get_number_of_images(
		     extent_descriptor,
		     &number_of_images,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve number of images from extent: %d descriptor.",
			 function,
			 extent_index );

			goto on_error;
		}
		fprintf(
		 info_handle->notify_stream,
		 "\tNumber of images\t: %d\n",
		 number_of_images );

		for( image_index = 0;
		     image_index < number_of_images;
		     image_index++ )
		{
			fprintf(
			 info_handle->notify_stream,
			 "\tImage: %d\n",
			 image_index + 1 );

			if( libphdi_extent_descriptor_get_image_descriptor_by_index(
			     extent_descriptor,
			     image_index,
			     &image_descriptor,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
				 "%s: unable to retrieve image: %d descriptor from extent: %d descriptor.",
				 function,
				 image_index,
				 extent_index );

				goto on_error;
			}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
			result = libphdi_image_descriptor_get_utf16_filename_size(
			          image_descriptor,
			          &value_string_size,
			          error );
#else
			result = libphdi_image_descriptor_get_utf8_filename_size(
			          image_descriptor,
			          &value_string_size,
			          error );
#endif
			if( result == -1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
				 "%s: unable to retrieve image: %d descriptor filename size.",
				 function,
				 image_index );

				goto on_error;
			}
			else if( result != 0 )
			{
				if( ( value_string_size == 0 )
				 || ( value_string_size > ( (size_t) MEMORY_MAXIMUM_ALLOCATION_SIZE / sizeof( system_character_t ) ) ) )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
					 "%s: invalid filename size value out of bounds.",
					 function );

					goto on_error;
				}
				value_string = system_string_allocate(
				                value_string_size );

				if( value_string == NULL )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_MEMORY,
					 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
					 "%s: unable to create filename string.",
					 function );

					goto on_error;
				}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
				result = libphdi_image_descriptor_get_utf16_filename(
				          image_descriptor,
					  (uint16_t *) value_string,
					  value_string_size,
					  error );
#else
				result = libphdi_image_descriptor_get_utf8_filename(
				          image_descriptor,
					  (uint8_t *) value_string,
					  value_string_size,
					  error );
#endif
				if( result != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
					 "%s: unable to retrieve image: %d descriptor filename.",
					 function,
					 image_index );

					goto on_error;
				}
				fprintf(
				 info_handle->notify_stream,
				 "\t\tFilename\t: %" PRIs_SYSTEM "\n",
				 value_string );

				memory_free(
				 value_string );

				value_string = NULL;
			}
			if( libphdi_image_descriptor_get_type(
			     image_descriptor,
			     &image_type,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
				 "%s: unable to retrieve image: %d descriptor type.",
				 function,
				 image_index );

				goto on_error;
			}
			fprintf(
			 info_handle->notify_stream,
			 "\t\tType\t\t: " );

			switch( image_type )
			{
				case LIBPHDI_IMAGE_TYPE_COMPRESSED:
					fprintf(
					 info_handle->notify_stream,
					 "Compressed" );
					break;

				case LIBPHDI_IMAGE_TYPE_PLAIN:
					fprintf(
					 info_handle->notify_stream,
					 "Plain" );
					break;

				default:
					fprintf(
					 info_handle->notify_stream,
					 "Unknown" );
					break;
			}
			fprintf(
			 info_handle->notify_stream,
			 "\n" );

			if( libphdi_image_descriptor_free(
			     &image_descriptor,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
				 "%s: unable to free image: %d descriptor.",
				 function,
				 image_index );

				goto on_error;
			}
		}
		if( libphdi_extent_descriptor_free(
		     &extent_descriptor,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free extent: %d descriptor.",
			 function,
			 extent_index );

			goto on_error;
		}
		fprintf(
		 info_handle->notify_stream,
		 "\n" );
	}
	for( snapshot_index = 0;
	     snapshot_index < number_of_snapshots;
	     snapshot_index++ )
	{
		fprintf(
		 info_handle->notify_stream,
		 "Snapshot: %d\n",
		 snapshot_index + 1 );

		if( libphdi_handle_get_snapshot_by_index(
		     info_handle->input_handle,
		     snapshot_index,
		     &snapshot,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve snapshot: %d.",
			 function,
			 extent_index );

			goto on_error;
		}
		if( libfguid_identifier_initialize(
		     &guid,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create GUID.",
			 function );

			goto on_error;
		}
		if( libphdi_snapshot_get_identifier(
		     snapshot,
		     guid_data,
		     16,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve identifier.",
			 function );

			goto on_error;
		}
		if( libfguid_identifier_copy_from_byte_stream(
		     guid,
		     guid_data,
		     16,
		     LIBFGUID_ENDIAN_BIG,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
			 "%s: unable to copy byte stream to GUID.",
			 function );

			goto on_error;
		}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
		result = libfguid_identifier_copy_to_utf16_string(
			  guid,
			  (uint16_t *) guid_string,
			  48,
			  LIBFGUID_STRING_FORMAT_FLAG_USE_LOWER_CASE,
			  error );
#else
		result = libfguid_identifier_copy_to_utf8_string(
			  guid,
			  (uint8_t *) guid_string,
			  48,
			  LIBFGUID_STRING_FORMAT_FLAG_USE_LOWER_CASE,
			  error );
#endif
		if( result != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
			 "%s: unable to copy GUID to string.",
			 function );

			goto on_error;
		}
		fprintf(
		 info_handle->notify_stream,
		 "\tIdentifier\t\t: %" PRIs_SYSTEM "\n",
		 guid_string );

		result = libphdi_snapshot_get_parent_identifier(
		          snapshot,
		          guid_data,
		          16,
		          error );

		if( result == -1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve parent identifier.",
			 function );

			goto on_error;
		}
		else if( result != 0 )
		{
			if( libfguid_identifier_copy_from_byte_stream(
			     guid,
			     guid_data,
			     16,
			     LIBFGUID_ENDIAN_BIG,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
				 "%s: unable to copy byte stream to GUID.",
				 function );

				goto on_error;
			}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
			result = libfguid_identifier_copy_to_utf16_string(
			          guid,
			          (uint16_t *) guid_string,
			          48,
			          LIBFGUID_STRING_FORMAT_FLAG_USE_LOWER_CASE,
			          error );
#else
			result = libfguid_identifier_copy_to_utf8_string(
			          guid,
			          (uint8_t *) guid_string,
			          48,
			          LIBFGUID_STRING_FORMAT_FLAG_USE_LOWER_CASE,
			          error );
#endif
			if( result != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
				 "%s: unable to copy GUID to string.",
				 function );

				goto on_error;
			}
			fprintf(
			 info_handle->notify_stream,
			 "\tParent identifier\t: %" PRIs_SYSTEM "\n",
			 guid_string );
		}
		if( libfguid_identifier_free(
		     &guid,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free GUID.",
			 function );

			goto on_error;
		}
		if( libphdi_snapshot_free(
		     &snapshot,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free snapshot: %d.",
			 function,
			 extent_index );

			goto on_error;
		}
		fprintf(
		 info_handle->notify_stream,
		 "\n" );
	}
	return( 1 );

on_error:
	if( guid != NULL )
	{
		libfguid_identifier_free(
		 &guid,
		 NULL );
	}
	if( snapshot != NULL )
	{
		libphdi_snapshot_free(
		 &snapshot,
		 NULL );
	}
	if( extent_descriptor != NULL )
	{
		libphdi_extent_descriptor_free(
		 &extent_descriptor,
		 NULL );
	}
	if( value_string != NULL )
	{
		memory_free(
		 value_string );
	}
	return( -1 );
}

