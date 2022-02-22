/*
 * Disk descriptor XML file functions
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

#include "libphdi_disk_descriptor_xml_file.h"
#include "libphdi_definitions.h"
#include "libphdi_extent_values.h"
#include "libphdi_image_values.h"
#include "libphdi_libbfio.h"
#include "libphdi_libcdata.h"
#include "libphdi_libcerror.h"
#include "libphdi_libcnotify.h"
#include "libphdi_libfvalue.h"
#include "libphdi_snapshot_values.h"
#include "libphdi_xml_parser.h"

extern \
int xml_parser_parse_buffer(
     libphdi_disk_descriptor_xml_file_t *disk_descriptor_xml_file,
     const uint8_t *buffer,
     size_t buffer_size,
     libcerror_error_t **error );

/* Creates a disk descriptor XML file
 * Make sure the value disk_descriptor_xml_file is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libphdi_disk_descriptor_xml_file_initialize(
    libphdi_disk_descriptor_xml_file_t **disk_descriptor_xml_file,
    libcerror_error_t **error )
{
	static char *function = "libphdi_disk_descriptor_xml_file_initialize";

	if( disk_descriptor_xml_file == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid disk descriptor XML file.",
		 function );

		return( -1 );
	}
	if( *disk_descriptor_xml_file != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid disk descriptor XML file value already set.",
		 function );

		return( -1 );
	}
	*disk_descriptor_xml_file = memory_allocate_structure(
	                             libphdi_disk_descriptor_xml_file_t );

	if( *disk_descriptor_xml_file == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create disk descriptor XML file.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *disk_descriptor_xml_file,
	     0,
	     sizeof( libphdi_disk_descriptor_xml_file_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear disk descriptor XML file.",
		 function );
	
		memory_free(
		 *disk_descriptor_xml_file );

		*disk_descriptor_xml_file = NULL;

		return( -1 );
	}
	return( 1 );

on_error:
	if( *disk_descriptor_xml_file != NULL )
	{
		memory_free(
		 *disk_descriptor_xml_file );

		*disk_descriptor_xml_file = NULL;
	}
	return( -1 );
}

/* Frees a disk descriptor XML file
 * Returns 1 if successful or -1 on error
 */
int libphdi_disk_descriptor_xml_file_free(
    libphdi_disk_descriptor_xml_file_t **disk_descriptor_xml_file,
    libcerror_error_t **error )
{
	static char *function = "libphdi_disk_descriptor_xml_file_free";
	int result            = 1;

	if( disk_descriptor_xml_file == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid disk descriptor XML file.",
		 function );

		return( -1 );
	}
	if( *disk_descriptor_xml_file != NULL )
	{
		/* The root_tag and dict_tag are referenced and freed elsewhere */

		if( libphdi_xml_tag_free(
		     &( ( *disk_descriptor_xml_file )->root_tag ),
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free root XML tag.",
			 function );

			result = -1;
		}
		memory_free(
		 *disk_descriptor_xml_file );

		*disk_descriptor_xml_file = NULL;
	}
	return( result );
}

/* Reads the disk descriptor XML file
 * Returns 1 if successful or -1 on error
 */
int libphdi_disk_descriptor_xml_file_read_data(
     libphdi_disk_descriptor_xml_file_t *disk_descriptor_xml_file,
     uint8_t *data,
     size_t data_size,
     libcerror_error_t **error )
{
	libphdi_xml_tag_t *element_tag = NULL;
	static char *function          = "libphdi_disk_descriptor_xml_file_read_data";
	int element_index              = 0;
	int number_of_elements         = 0;
	int result                     = 0;

	if( disk_descriptor_xml_file == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid disk descriptor XML file.",
		 function );

		return( -1 );
	}
	if( disk_descriptor_xml_file->root_tag != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid disk descriptor XML file - root XML tag already set.",
		 function );

		return( -1 );
	}
	if( data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid data.",
		 function );

		return( -1 );
	}
	if( ( data_size == 0 )
	 || ( data_size > (size_t) SSIZE_MAX ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid data size value out of bounds.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{                
		if( ( data_size >= 6 )
		 && ( data[ 0 ] == '<' )
		 && ( data[ 1 ] == '?' )
		 && ( data[ 2 ] == 'x' )
		 && ( data[ 3 ] == 'm' )
		 && ( data[ 4 ] == 'l' )
		 && ( data[ data_size - 1 ] == 0 ) )
		{
			libcnotify_printf(
			 "%s: XML:\n%s\n",
			 function,
			 data );
		}        
		else     
		{       
			libcnotify_printf(
			 "%s: XML data:\n",
			 function );
			libcnotify_print_data(
			 data,
			 data_size,
			 0 );
		}
	}                
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

	/* Lex wants a buffer it can write to
	 */
	result = xml_parser_parse_buffer(
	          disk_descriptor_xml_file,
	          data,
	          data_size,
	          error );

	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to parse XML.",
		 function );

		goto on_error;
	}
	if( disk_descriptor_xml_file->root_tag == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid disk descriptor XML file - missing root XML tag.",
		 function );

		goto on_error;
	}
	result = libphdi_xml_tag_compare_name(
	          disk_descriptor_xml_file->root_tag,
	          (uint8_t *) "Parallels_disk_image",
	          20,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to compare name of root tag.",
		 function );

		goto on_error;
	}
	else if( result == 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported root tag.",
		 function );

		goto on_error;
	}
	if( libphdi_xml_tag_get_number_of_elements(
	     disk_descriptor_xml_file->root_tag,
	     &number_of_elements,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of elements.",
		 function );

		goto on_error;
	}
	for( element_index = 0;
	     element_index < number_of_elements;
	     element_index++ )
	{
		if( libphdi_xml_tag_get_element(
		     disk_descriptor_xml_file->root_tag,
		     element_index,
		     &element_tag,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve element: %d.",
			 function,
			 element_index );

			goto on_error;
		}
		result = libphdi_xml_tag_compare_name(
			  element_tag,
			  (uint8_t *) "Disk_Parameters",
			  15,
			  error );

		if( result == -1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to compare name of element tag: %d.",
			 function,
			 element_index );

			goto on_error;
		}
		else if( result != 0 )
		{
			disk_descriptor_xml_file->disk_parameters_tag = element_tag;

			continue;
		}
		result = libphdi_xml_tag_compare_name(
			  element_tag,
			  (uint8_t *) "StorageData",
			  11,
			  error );

		if( result == -1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to compare name of element tag: %d.",
			 function,
			 element_index );

			goto on_error;
		}
		else if( result != 0 )
		{
			disk_descriptor_xml_file->storage_data_tag = element_tag;

			continue;
		}
		result = libphdi_xml_tag_compare_name(
			  element_tag,
			  (uint8_t *) "Snapshots",
			  9,
			  error );

		if( result == -1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to compare name of element tag: %d.",
			 function,
			 element_index );

			goto on_error;
		}
		else if( result != 0 )
		{
			disk_descriptor_xml_file->snapshots_tag = element_tag;

			continue;
		}
	}
	return( 1 );

on_error:
	if( disk_descriptor_xml_file->root_tag != NULL )
	{
		libphdi_xml_tag_free(
		 &( disk_descriptor_xml_file->root_tag ),
		 NULL );
	}
	disk_descriptor_xml_file->disk_parameters_tag = NULL;
	disk_descriptor_xml_file->storage_data_tag    = NULL;
	disk_descriptor_xml_file->snapshots_tag       = NULL;

	return( -1 );
}

/* Reads the disk descriptor XML file
 * Returns 1 if successful or -1 on error
 */
int libphdi_disk_descriptor_xml_file_read_file_io_handle(
     libphdi_disk_descriptor_xml_file_t *disk_descriptor_xml_file,
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error )
{
	uint8_t *data         = NULL;
	static char *function = "libphdi_disk_descriptor_xml_file_read_file_io_handle";
	size64_t file_size    = 0;
	ssize_t read_count    = 0;

	if( disk_descriptor_xml_file == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid disk descriptor XML file.",
		 function );

		return( -1 );
	}
	if( libbfio_handle_get_size(
	     file_io_handle,
	     &file_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve file size.",
		 function );

		goto on_error;
	}
	if( ( file_size < 2 )
	 || ( file_size > (size64_t) ( MEMORY_MAXIMUM_ALLOCATION_SIZE - 2 ) ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid file size value out of bounds.",
		 function );

		goto on_error;
	}
	/* Reserve space for 2 zero bytes at the end of the buffer
	 */
	data = (uint8_t *) memory_allocate(
	                    sizeof( uint8_t ) * (size_t) ( file_size + 2 ) );

	if( data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create data.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     data,
	     0,
	     (size_t) file_size + 2 ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear data.",
		 function );

		goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: reading disk descriptor XML file at offset: 0 (0x00000000)\n",
		 function );
	}
#endif
	read_count = libbfio_handle_read_buffer_at_offset(
	              file_io_handle,
	              data,
	              (size_t) file_size,
	              0,
	              error );

	if( read_count != (ssize_t) file_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read data at offset: 0 (0x00000000).",
		 function );

		goto on_error;
	}
	/* Lex wants 2 zero bytes at the end of the buffer
	 */
	if( data[ file_size - 1 ] != 0 )
	{
		file_size += 2;
	}
	else if( data[ file_size - 2 ] != 0 )
	{
		file_size += 1;
	}
	/* Lex wants a buffer it can write to
	 */
	if( libphdi_disk_descriptor_xml_file_read_data(
	     disk_descriptor_xml_file,
	     data,
	     file_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read data.",
		 function );

		goto on_error;
	}
	memory_free(
	 data );

	return( 1 );

on_error:
	if( data != NULL )
	{
		memory_free(
		 data );
	}
	if( disk_descriptor_xml_file->root_tag != NULL )
	{
		libphdi_xml_tag_free(
		 &( disk_descriptor_xml_file->root_tag ),
		 NULL );
	}
	disk_descriptor_xml_file->disk_parameters_tag = NULL;
	disk_descriptor_xml_file->storage_data_tag    = NULL;
	disk_descriptor_xml_file->snapshots_tag       = NULL;

	return( -1 );
}

/* Retrieves the disk parameters
 * Returns 1 if successful or -1 on error
 */
int libphdi_disk_descriptor_xml_file_get_disk_parameters(
     libphdi_disk_descriptor_xml_file_t *disk_descriptor_xml_file,
     libphdi_disk_parameters_t *disk_parameters,
     libcerror_error_t **error )
{
	libphdi_xml_tag_t *element_tag       = NULL;
	libphdi_xml_tag_t *encryption_tag    = NULL;
	libphdi_xml_tag_t *miscellaneous_tag = NULL;
	static char *function                = "libphdi_disk_descriptor_xml_file_get_disk_parameters";
	uint64_t value_64bit                 = 0;
	int element_index                    = 0;
	int number_of_elements               = 0;
	int result                           = 0;

	if( disk_descriptor_xml_file == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid disk descriptor XML file.",
		 function );

		return( -1 );
	}
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
	if( libphdi_xml_tag_get_number_of_elements(
	     disk_descriptor_xml_file->disk_parameters_tag,
	     &number_of_elements,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of elements.",
		 function );

		return( -1 );
	}
	for( element_index = 0;
	     element_index < number_of_elements;
	     element_index++ )
	{
		if( libphdi_xml_tag_get_element(
		     disk_descriptor_xml_file->disk_parameters_tag,
		     element_index,
		     &element_tag,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve element: %d.",
			 function,
			 element_index );

			return( -1 );
		}
		result = libphdi_xml_tag_compare_name(
			  element_tag,
			  (uint8_t *) "Cylinders",
			  9,
			  error );

		if( result == -1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to compare name of element tag: %d.",
			 function,
			 element_index );

			return( -1 );
		}
		else if( result != 0 )
		{
			if( libfvalue_utf8_string_copy_to_integer(
			     element_tag->value,
			     element_tag->value_size - 1,
			     (uint64_t *) &value_64bit,
			     64,
			     LIBFVALUE_INTEGER_FORMAT_TYPE_DECIMAL | LIBFVALUE_INTEGER_FORMAT_FLAG_UNSIGNED,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
				 "%s: unable to convert Cylinders value to integer.",
				 function );

				return( -1 );
			}
			if( value_64bit > (uint64_t) UINT32_MAX )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
				 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
				 "%s: invalid number of cylinders value out of bounds.",
				 function );

				return( -1 );
			}
			disk_parameters->number_of_cylinders = value_64bit;

			continue;
		}
		result = libphdi_xml_tag_compare_name(
			  element_tag,
			  (uint8_t *) "Disk_size",
			  9,
			  error );

		if( result == -1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to compare name of element tag: %d.",
			 function,
			 element_index );

			return( -1 );
		}
		else if( result != 0 )
		{
			if( libfvalue_utf8_string_copy_to_integer(
			     element_tag->value,
			     element_tag->value_size - 1,
			     (uint64_t *) &value_64bit,
			     64,
			     LIBFVALUE_INTEGER_FORMAT_TYPE_DECIMAL | LIBFVALUE_INTEGER_FORMAT_FLAG_UNSIGNED,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
				 "%s: unable to convert Disk_size value to integer.",
				 function );

				return( -1 );
			}
			if( value_64bit > (uint64_t) ( UINT64_MAX / 512 ) )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
				 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
				 "%s: invalid media size value out of bounds.",
				 function );

				return( -1 );
			}
			disk_parameters->media_size = (size64_t) value_64bit * 512;

			continue;
		}
		result = libphdi_xml_tag_compare_name(
			  element_tag,
			  (uint8_t *) "Encryption",
			  10,
			  error );

		if( result == -1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to compare name of element tag: %d.",
			 function,
			 element_index );

			return( -1 );
		}
		else if( result != 0 )
		{
			encryption_tag = element_tag;

			continue;
		}
		result = libphdi_xml_tag_compare_name(
			  element_tag,
			  (uint8_t *) "Heads",
			  5,
			  error );

		if( result == -1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to compare name of element tag: %d.",
			 function,
			 element_index );

			return( -1 );
		}
		else if( result != 0 )
		{
			if( libfvalue_utf8_string_copy_to_integer(
			     element_tag->value,
			     element_tag->value_size - 1,
			     (uint64_t *) &value_64bit,
			     64,
			     LIBFVALUE_INTEGER_FORMAT_TYPE_DECIMAL | LIBFVALUE_INTEGER_FORMAT_FLAG_UNSIGNED,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
				 "%s: unable to convert Heads value to integer.",
				 function );

				return( -1 );
			}
			if( value_64bit > (uint64_t) UINT32_MAX )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
				 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
				 "%s: invalid number of heads value out of bounds.",
				 function );

				return( -1 );
			}
			disk_parameters->number_of_heads = value_64bit;

			continue;
		}
		result = libphdi_xml_tag_compare_name(
			  element_tag,
			  (uint8_t *) "Miscellaneous",
			  13,
			  error );

		if( result == -1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to compare name of element tag: %d.",
			 function,
			 element_index );

			return( -1 );
		}
		else if( result != 0 )
		{
			miscellaneous_tag = element_tag;

			continue;
		}
		result = libphdi_xml_tag_compare_name(
			  element_tag,
			  (uint8_t *) "UID",
			  3,
			  error );

		if( result == -1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to compare name of element tag: %d.",
			 function,
			 element_index );

			return( -1 );
		}
		else if( result != 0 )
		{
/* TODO set identifier */
			continue;
		}
		result = libphdi_xml_tag_compare_name(
			  element_tag,
			  (uint8_t *) "Name",
			  4,
			  error );

		if( result == -1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to compare name of element tag: %d.",
			 function,
			 element_index );

			return( -1 );
		}
		else if( result != 0 )
		{
			if( libphdi_disk_parameters_set_name(
			     disk_parameters,
			     element_tag->value,
			     element_tag->value_size,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
				 "%s: unable to set name in disk parameters.",
				 function );

				return( -1 );
			}
			continue;
		}
		result = libphdi_xml_tag_compare_name(
			  element_tag,
			  (uint8_t *) "LogicSectorSize",
			  15,
			  error );

		if( result == -1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to compare name of element tag: %d.",
			 function,
			 element_index );

			return( -1 );
		}
		else if( result != 0 )
		{
			if( libfvalue_utf8_string_copy_to_integer(
			     element_tag->value,
			     element_tag->value_size - 1,
			     (uint64_t *) &value_64bit,
			     64,
			     LIBFVALUE_INTEGER_FORMAT_TYPE_DECIMAL | LIBFVALUE_INTEGER_FORMAT_FLAG_UNSIGNED,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
				 "%s: unable to convert LogicSectorSize value to integer.",
				 function );

				return( -1 );
			}
			if( value_64bit != 512 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
				 "%s: unsupported logical sector size: %" PRIu64 ".",
				 function,
				 value_64bit );

				return( -1 );
			}
			continue;
		}
		result = libphdi_xml_tag_compare_name(
			  element_tag,
			  (uint8_t *) "Padding",
			  7,
			  error );

		if( result == -1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to compare name of element tag: %d.",
			 function,
			 element_index );

			return( -1 );
		}
		else if( result != 0 )
		{
			if( libfvalue_utf8_string_copy_to_integer(
			     element_tag->value,
			     element_tag->value_size - 1,
			     (uint64_t *) &value_64bit,
			     64,
			     LIBFVALUE_INTEGER_FORMAT_TYPE_DECIMAL | LIBFVALUE_INTEGER_FORMAT_FLAG_UNSIGNED,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
				 "%s: unable to convert Padding value to integer.",
				 function );

				return( -1 );
			}
			if( value_64bit != 0 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
				 "%s: unsupported padding: %" PRIu64 ".",
				 function,
				 value_64bit );

				return( -1 );
			}
			continue;
		}
		result = libphdi_xml_tag_compare_name(
			  element_tag,
			  (uint8_t *) "PhysicalSectorSize",
			  18,
			  error );

		if( result == -1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to compare name of element tag: %d.",
			 function,
			 element_index );

			return( -1 );
		}
		else if( result != 0 )
		{
			if( libfvalue_utf8_string_copy_to_integer(
			     element_tag->value,
			     element_tag->value_size - 1,
			     (uint64_t *) &value_64bit,
			     64,
			     LIBFVALUE_INTEGER_FORMAT_TYPE_DECIMAL | LIBFVALUE_INTEGER_FORMAT_FLAG_UNSIGNED,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
				 "%s: unable to convert PhysicalSectorSize value to integer.",
				 function );

				return( -1 );
			}
			if( value_64bit != 4096 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
				 "%s: unsupported physical sector size: %" PRIu64 ".",
				 function,
				 value_64bit );

				return( -1 );
			}
			continue;
		}
		result = libphdi_xml_tag_compare_name(
			  element_tag,
			  (uint8_t *) "Sectors",
			  7,
			  error );

		if( result == -1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to compare name of element tag: %d.",
			 function,
			 element_index );

			return( -1 );
		}
		else if( result != 0 )
		{
			if( libfvalue_utf8_string_copy_to_integer(
			     element_tag->value,
			     element_tag->value_size - 1,
			     (uint64_t *) &value_64bit,
			     64,
			     LIBFVALUE_INTEGER_FORMAT_TYPE_DECIMAL | LIBFVALUE_INTEGER_FORMAT_FLAG_UNSIGNED,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
				 "%s: unable to convert Sectors value to integer.",
				 function );

				return( -1 );
			}
			disk_parameters->number_of_sectors = value_64bit;

			continue;
		}
/* TODO print unsupported tags */
	}
	if( encryption_tag != NULL )
	{
/* TODO check Encryption */
	}
	if( miscellaneous_tag != NULL )
	{
/* TODO check Miscellaneous */
	}
	return( 1 );
}

/* Retrieves the disk type
 * Returns 1 if successful or -1 on error
 */
int libphdi_disk_descriptor_xml_file_get_disk_type(
     libphdi_disk_descriptor_xml_file_t *disk_descriptor_xml_file,
     int *disk_type,
     libcerror_error_t **error )
{
	static char *function = "libphdi_disk_descriptor_xml_file_get_disk_type";

	if( disk_descriptor_xml_file == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid disk descriptor XML file.",
		 function );

		return( -1 );
	}
	if( disk_type == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid disk type.",
		 function );

		return( -1 );
	}
	*disk_type = disk_descriptor_xml_file->disk_type;

	return( 1 );
}

/* Retrieves the storage data
 * Returns 1 if successful or -1 on error
 */
int libphdi_disk_descriptor_xml_file_get_storage_data(
     libphdi_disk_descriptor_xml_file_t *disk_descriptor_xml_file,
     libcdata_array_t *extent_values_array,
     libcerror_error_t **error )
{
	libphdi_extent_values_t *extent_values = NULL;
	libphdi_image_values_t *image_values   = NULL;
	libphdi_xml_tag_t *element_tag         = NULL;
	libphdi_xml_tag_t *image_element_tag   = NULL;
	libphdi_xml_tag_t *storage_tag         = NULL;
	static char *function                  = "libphdi_disk_descriptor_xml_file_get_storage_data";
	off64_t end_offset                     = 0;
	off64_t start_offset                   = 0;
	uint64_t value_64bit                   = 0;
	int element_index                      = 0;
	int entry_index                        = 0;
	int image_element_index                = 0;
	int image_type                         = 0;
	int number_of_elements                 = 0;
	int number_of_image_elements           = 0;
	int number_of_snapshots                = 0;
	int number_of_storage_elements         = 0;
	int result                             = 0;
	int storage_element_index              = 0;

	if( disk_descriptor_xml_file == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid disk descriptor XML file.",
		 function );

		return( -1 );
	}
	if( libcdata_array_empty(
	     extent_values_array,
	     (int (*)(intptr_t **, libcerror_error_t **)) &libphdi_extent_values_free,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to empty extent values array.",
		 function );

		goto on_error;
	}
	if( libphdi_xml_tag_get_number_of_elements(
	     disk_descriptor_xml_file->storage_data_tag,
	     &number_of_storage_elements,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of storage elements.",
		 function );

		goto on_error;
	}
	if( ( number_of_snapshots > 1 )
	 && ( number_of_storage_elements > 1 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: split storage with snapshots currently not supported.",
		 function );

		goto on_error;
	}
	for( storage_element_index = 0;
	     storage_element_index < number_of_storage_elements;
	     storage_element_index++ )
	{
		if( libphdi_xml_tag_get_element(
		     disk_descriptor_xml_file->storage_data_tag,
		     storage_element_index,
		     &storage_tag,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve storage element: %d.",
			 function,
			 storage_element_index );

			goto on_error;
		}
		result = libphdi_xml_tag_compare_name(
			  storage_tag,
			  (uint8_t *) "Storage",
			  7,
			  error );

		if( result == -1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to compare name of storage element tag: %d.",
			 function,
			 storage_element_index );

			goto on_error;
		}
		else if( result == 0 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
			 "%s: unsupported storage tag: %d.",
			 function,
			 storage_element_index );

			goto on_error;
		}
		if( libphdi_extent_values_initialize(
		     &extent_values,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create extent values.",
			 function );

			goto on_error;
		}
		if( libphdi_xml_tag_get_number_of_elements(
		     storage_tag,
		     &number_of_elements,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve number of elements of storage tag: %d.",
			 function,
			 storage_element_index );

			goto on_error;
		}
		start_offset = -1;
		end_offset   = -1;

		for( element_index = 0;
		     element_index < number_of_elements;
		     element_index++ )
		{
			if( libphdi_xml_tag_get_element(
			     storage_tag,
			     element_index,
			     &element_tag,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
				 "%s: unable to retrieve element: %d of storage tag: %d.",
				 function,
				 element_index,
				 storage_element_index );

				goto on_error;
			}
			result = libphdi_xml_tag_compare_name(
				  element_tag,
				  (uint8_t *) "Blocksize",
				  9,
				  error );

			if( result == -1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
				 "%s: unable to compare name of element: %d of storage tag: %d.",
				 function,
				 element_index,
				 storage_element_index );

				goto on_error;
			}
			else if( result != 0 )
			{
				if( libfvalue_utf8_string_copy_to_integer(
				     element_tag->value,
				     element_tag->value_size - 1,
				     (uint64_t *) &value_64bit,
				     64,
				     LIBFVALUE_INTEGER_FORMAT_TYPE_DECIMAL | LIBFVALUE_INTEGER_FORMAT_FLAG_UNSIGNED,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
					 "%s: unable to convert Blocksize value to integer.",
					 function );

					goto on_error;
				}
				if( value_64bit != 2048 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
					 "%s: unsupported block size: %" PRIu64 ".",
					 function,
					 value_64bit );

					goto on_error;
				}
				continue;
			}
			result = libphdi_xml_tag_compare_name(
				  element_tag,
				  (uint8_t *) "End",
				  3,
				  error );

			if( result == -1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
				 "%s: unable to compare name of element: %d of storage tag: %d.",
				 function,
				 element_index,
				 storage_element_index );

				goto on_error;
			}
			else if( result != 0 )
			{
				if( libfvalue_utf8_string_copy_to_integer(
				     element_tag->value,
				     element_tag->value_size - 1,
				     (uint64_t *) &value_64bit,
				     64,
				     LIBFVALUE_INTEGER_FORMAT_TYPE_DECIMAL | LIBFVALUE_INTEGER_FORMAT_FLAG_UNSIGNED,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
					 "%s: unable to convert End value to integer.",
					 function );

					goto on_error;
				}
				if( value_64bit > (uint64_t) ( INT64_MAX / 512 ) )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
					 "%s: unsupported end sector: %" PRIu64 ".",
					 function,
					 value_64bit );

					goto on_error;
				}
				end_offset = (off64_t) value_64bit * 512;

				continue;
			}
			result = libphdi_xml_tag_compare_name(
				  element_tag,
				  (uint8_t *) "Image",
				  5,
				  error );

			if( result == -1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
				 "%s: unable to compare name of element: %d of storage tag: %d.",
				 function,
				 element_index,
				 storage_element_index );

				goto on_error;
			}
			else if( result != 0 )
			{
				if( libphdi_image_values_initialize(
				     &image_values,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
					 "%s: unable to create image values.",
					 function );

					goto on_error;
				}
				if( libphdi_xml_tag_get_number_of_elements(
				     element_tag,
				     &number_of_image_elements,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
					 "%s: unable to retrieve number of elements of image tag: %d of storage tag: %d.",
					 function,
					 element_index,
					 storage_element_index );

					goto on_error;
				}
				for( image_element_index = 0;
				     image_element_index < number_of_image_elements;
				     image_element_index++ )
				{
					if( libphdi_xml_tag_get_element(
					     element_tag,
					     image_element_index,
					     &image_element_tag,
					     error ) != 1 )
					{
						libcerror_error_set(
						 error,
						 LIBCERROR_ERROR_DOMAIN_RUNTIME,
						 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
						 "%s: unable to retrieve element: %d of image tag: %d of storage tag: %d.",
						 function,
						 image_element_index,
						 element_index,
						 storage_element_index );

						goto on_error;
					}
					result = libphdi_xml_tag_compare_name(
						  image_element_tag,
						  (uint8_t *) "GUID",
						  4,
						  error );

					if( result == -1 )
					{
						libcerror_error_set(
						 error,
						 LIBCERROR_ERROR_DOMAIN_RUNTIME,
						 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
						 "%s: unable to compare name of element: %d of image tag: %d of storage tag: %d.",
						 function,
						 image_element_index,
						 element_index,
						 storage_element_index );

						goto on_error;
					}
					else if( result != 0 )
					{
						if( libphdi_image_values_set_identifier(
						     image_values,
						     image_element_tag->value,
						     image_element_tag->value_size - 1,
						     error ) != 1 )
						{
							libcerror_error_set(
							 error,
							 LIBCERROR_ERROR_DOMAIN_RUNTIME,
							 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
							 "%s: unable to set image identifier.",
							 function );

							goto on_error;
						}
						continue;
					}
					result = libphdi_xml_tag_compare_name(
						  image_element_tag,
						  (uint8_t *) "File",
						  4,
						  error );

					if( result == -1 )
					{
						libcerror_error_set(
						 error,
						 LIBCERROR_ERROR_DOMAIN_RUNTIME,
						 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
						 "%s: unable to compare name of element: %d of image tag: %d of storage tag: %d.",
						 function,
						 image_element_index,
						 element_index,
						 storage_element_index );

						goto on_error;
					}
					else if( result != 0 )
					{
						if( libphdi_image_values_set_filename(
						     image_values,
						     image_element_tag->value,
						     image_element_tag->value_size - 1,
						     error ) != 1 )
						{
							libcerror_error_set(
							 error,
							 LIBCERROR_ERROR_DOMAIN_RUNTIME,
							 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
							 "%s: unable to set image filename.",
							 function );

							goto on_error;
						}
						continue;
					}
					result = libphdi_xml_tag_compare_name(
						  image_element_tag,
						  (uint8_t *) "Type",
						  4,
						  error );

					if( result == -1 )
					{
						libcerror_error_set(
						 error,
						 LIBCERROR_ERROR_DOMAIN_RUNTIME,
						 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
						 "%s: unable to compare name of element: %d of image tag: %d of storage tag: %d.",
						 function,
						 image_element_index,
						 element_index,
						 storage_element_index );

						goto on_error;
					}
					else if( result != 0 )
					{
						if( ( image_element_tag->value == NULL )
						 || ( image_element_tag->value_size == 0 ) )
						{
							libcerror_error_set(
							 error,
							 LIBCERROR_ERROR_DOMAIN_RUNTIME,
							 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
							 "%s: invalid type tag of element: %d of image tag: %d of storage tag: %d - missing value.",
							 function );

							goto on_error;
						}
						image_type = LIBPHDI_IMAGE_TYPE_UNKNOWN;

						if( ( image_element_tag->value_size == 6 )
						 && ( narrow_string_compare(
						       "Plain",
						       image_element_tag->value,
						       image_element_tag->value_size ) == 0 ) )
						{
							image_type = LIBPHDI_IMAGE_TYPE_PLAIN;
						}
						else if( ( image_element_tag->value_size == 11 )
						      && ( narrow_string_compare(
						            "Compressed",
						            image_element_tag->value,
						            image_element_tag->value_size ) == 0 ) )
						{
							image_type = LIBPHDI_IMAGE_TYPE_COMPRESSED;
						}
						image_values->type = image_type;

						if( disk_descriptor_xml_file->disk_type == 0 )
						{
							if( image_type == LIBPHDI_IMAGE_TYPE_COMPRESSED )
							{
								disk_descriptor_xml_file->disk_type = LIBPHDI_DISK_TYPE_EXPANDING;
							}
							else if( image_type == LIBPHDI_IMAGE_TYPE_PLAIN )
							{
								disk_descriptor_xml_file->disk_type = LIBPHDI_DISK_TYPE_FIXED;
							}
						}
						continue;
					}
/* TODO print unsupported tags */
				}
				if( libcdata_array_append_entry(
				     extent_values->image_values_array,
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

				continue;
			}
			result = libphdi_xml_tag_compare_name(
				  element_tag,
				  (uint8_t *) "Start",
				  5,
				  error );

			if( result == -1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
				 "%s: unable to compare name of element: %d of storage tag: %d.",
				 function,
				 element_index,
				 storage_element_index );

				goto on_error;
			}
			else if( result != 0 )
			{
				if( libfvalue_utf8_string_copy_to_integer(
				     element_tag->value,
				     element_tag->value_size - 1,
				     (uint64_t *) &value_64bit,
				     64,
				     LIBFVALUE_INTEGER_FORMAT_TYPE_DECIMAL | LIBFVALUE_INTEGER_FORMAT_FLAG_UNSIGNED,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
					 "%s: unable to convert Start value to integer.",
					 function );

					goto on_error;
				}
				if( value_64bit > (uint64_t) ( INT64_MAX / 512 ) )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
					 "%s: unsupported start sector: %" PRIu64 ".",
					 function,
					 value_64bit );

					goto on_error;
				}
				start_offset = (off64_t) value_64bit * 512;
			}
/* TODO print unsupported tags */
		}
		if( libphdi_extent_values_set_range(
		     extent_values,
		     start_offset,
		     end_offset,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
			 "%s: unable to set extent values range.",
			 function );

			goto on_error;
		}
		if( libcdata_array_append_entry(
		     extent_values_array,
		     &entry_index,
		     (intptr_t *) extent_values,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
			 "%s: unable to append extent values to array.",
			 function );

			goto on_error;
		}
		extent_values = NULL;
	}
	return( 1 );

on_error:
	if( image_values != NULL )
	{
		libphdi_image_values_free(
		 &image_values,
		 NULL );
	}
	if( extent_values != NULL )
	{
		libphdi_extent_values_free(
		 &extent_values,
		 NULL );
	}
	libcdata_array_empty(
	 extent_values_array,
	 (int (*)(intptr_t **, libcerror_error_t **)) &libphdi_extent_values_free,
	 NULL );

	return( -1 );
}

/* Retrieves the snapshots
 * Returns 1 if successful or -1 on error
 */
int libphdi_disk_descriptor_xml_file_get_snapshots(
     libphdi_disk_descriptor_xml_file_t *disk_descriptor_xml_file,
     libcdata_array_t *snapshot_values_array,
     libcerror_error_t **error )
{
	libphdi_snapshot_values_t *snapshot_values = NULL;
	libphdi_xml_tag_t *element_tag             = NULL;
	libphdi_xml_tag_t *snapshot_tag            = NULL;
	static char *function                      = "libphdi_disk_descriptor_xml_file_get_snapshots";
	int element_index                          = 0;
	int entry_index                            = 0;
	int number_of_elements                     = 0;
	int number_of_snapshot_elements            = 0;
	int result                                 = 0;
	int snapshot_element_index                 = 0;

	if( disk_descriptor_xml_file == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid disk descriptor XML file.",
		 function );

		return( -1 );
	}
	if( libcdata_array_empty(
	     snapshot_values_array,
	     (int (*)(intptr_t **, libcerror_error_t **)) &libphdi_snapshot_values_free,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to empty snapshot values array.",
		 function );

		goto on_error;
	}
	if( libphdi_xml_tag_get_number_of_elements(
	     disk_descriptor_xml_file->snapshots_tag,
	     &number_of_snapshot_elements,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of snapshot elements.",
		 function );

		goto on_error;
	}
	for( snapshot_element_index = 0;
	     snapshot_element_index < number_of_snapshot_elements;
	     snapshot_element_index++ )
	{
		if( libphdi_xml_tag_get_element(
		     disk_descriptor_xml_file->snapshots_tag,
		     snapshot_element_index,
		     &snapshot_tag,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve snaptshot element: %d.",
			 function,
			 snapshot_element_index );

			goto on_error;
		}
		result = libphdi_xml_tag_compare_name(
			  snapshot_tag,
			  (uint8_t *) "Shot",
			  4,
			  error );

		if( result == -1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to compare name of snapshot element tag: %d.",
			 function,
			 snapshot_element_index );

			goto on_error;
		}
		else if( result == 0 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
			 "%s: unsupported snapshot tag: %d.",
			 function,
			 snapshot_element_index );

			goto on_error;
		}
		if( libphdi_snapshot_values_initialize(
		     &snapshot_values,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create snapshot values.",
			 function );

			goto on_error;
		}
		if( libphdi_xml_tag_get_number_of_elements(
		     snapshot_tag,
		     &number_of_elements,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve number of elements of snapshot tag: %d.",
			 function,
			 snapshot_element_index );

			goto on_error;
		}
		for( element_index = 0;
		     element_index < number_of_elements;
		     element_index++ )
		{
			if( libphdi_xml_tag_get_element(
			     snapshot_tag,
			     element_index,
			     &element_tag,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
				 "%s: unable to retrieve element: %d of snapshot tag: %d.",
				 function,
				 element_index,
				 snapshot_element_index );

				goto on_error;
			}
			result = libphdi_xml_tag_compare_name(
				  element_tag,
				  (uint8_t *) "GUID",
				  4,
				  error );

			if( result == -1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
				 "%s: unable to compare name of element: %d of snapshot tag: %d.",
				 function,
				 element_index,
				 snapshot_element_index );

				goto on_error;
			}
			else if( result != 0 )
			{
				if( libphdi_snapshot_values_set_identifier(
				     snapshot_values,
				     element_tag->value,
				     element_tag->value_size - 1,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
					 "%s: unable to set snapshot identifier.",
					 function );

					goto on_error;
				}
				continue;
			}
			result = libphdi_xml_tag_compare_name(
				  element_tag,
				  (uint8_t *) "ParentGUID",
				  10,
				  error );

			if( result == -1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
				 "%s: unable to compare name of element: %d of snapshot tag: %d.",
				 function,
				 element_index,
				 snapshot_element_index );

				goto on_error;
			}
			else if( result != 0 )
			{
				if( libphdi_snapshot_values_set_parent_identifier(
				     snapshot_values,
				     element_tag->value,
				     element_tag->value_size - 1,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
					 "%s: unable to set snapshot parent identifier.",
					 function );

					goto on_error;
				}
				continue;
			}
/* TODO print unsupported tags */
		}
		if( libcdata_array_append_entry(
		     snapshot_values_array,
		     &entry_index,
		     (intptr_t *) snapshot_values,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
			 "%s: unable to append snapshot values to array.",
			 function );

			goto on_error;
		}
		snapshot_values = NULL;
	}
	return( 1 );

on_error:
	if( snapshot_values != NULL )
	{
		libphdi_snapshot_values_free(
		 &snapshot_values,
		 NULL );
	}
	libcdata_array_empty(
	 snapshot_values_array,
	 (int (*)(intptr_t **, libcerror_error_t **)) &libphdi_snapshot_values_free,
	 NULL );

	return( -1 );
}

/* Sets the root tag
 * Returns 1 if successful or -1 on error
 */
int libphdi_disk_descriptor_xml_file_set_root_tag(
     libphdi_disk_descriptor_xml_file_t *disk_descriptor_xml_file,
     libphdi_xml_tag_t *tag,
     libcerror_error_t **error )
{
	static char *function = "libphdi_disk_descriptor_xml_file_set_root_tag";

	if( disk_descriptor_xml_file == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid disk descriptor XML file.",
		 function );

		return( -1 );
	}
	if( tag == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid tag.",
		 function );

		return( -1 );
	}
	disk_descriptor_xml_file->root_tag = tag;

	return( 1 );
}

