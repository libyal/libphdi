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

#if !defined( _LIBPHDI_DISK_DESCRIPTOR_XML_FILE_H )
#define _LIBPHDI_DISK_DESCRIPTOR_XML_FILE_H

#include <common.h>
#include <types.h>

#include "libphdi_disk_parameters.h"
#include "libphdi_libbfio.h"
#include "libphdi_libcerror.h"
#include "libphdi_storage_table.h"
#include "libphdi_types.h"
#include "libphdi_xml_tag.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libphdi_disk_descriptor_xml_file libphdi_disk_descriptor_xml_file_t;

struct libphdi_disk_descriptor_xml_file
{
	/* The root XML tag
	 */
	libphdi_xml_tag_t *root_tag;

	/* The disk parameters XML tag
	 */
	libphdi_xml_tag_t *disk_parameters_tag;

	/* The storage data XML tag
	 */
	libphdi_xml_tag_t *storage_data_tag;

	/* The snapshots XML tag
	 */
	libphdi_xml_tag_t *snapshots_tag;
};

int libphdi_disk_descriptor_xml_file_initialize(
     libphdi_disk_descriptor_xml_file_t **disk_descriptor_xml_file,
     libcerror_error_t **error );

int libphdi_disk_descriptor_xml_file_free(
     libphdi_disk_descriptor_xml_file_t **disk_descriptor_xml_file,
     libcerror_error_t **error );

int libphdi_disk_descriptor_xml_file_read_data(
     libphdi_disk_descriptor_xml_file_t *disk_descriptor_xml_file,
     uint8_t *data,
     size_t data_size,
     libcerror_error_t **error );

int libphdi_disk_descriptor_xml_file_read_file_io_handle(
     libphdi_disk_descriptor_xml_file_t *disk_descriptor_xml_file,
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error );

int libphdi_disk_descriptor_xml_file_get_disk_parameters(
     libphdi_disk_descriptor_xml_file_t *disk_descriptor_xml_file,
     libphdi_disk_parameters_t *disk_parameters,
     libcerror_error_t **error );

int libphdi_disk_descriptor_xml_file_get_storage_data(
     libphdi_disk_descriptor_xml_file_t *disk_descriptor_xml_file,
     libphdi_storage_table_t *storage_table,
     libcerror_error_t **error );

int libphdi_disk_descriptor_xml_file_get_snapshots(
     libphdi_disk_descriptor_xml_file_t *disk_descriptor_xml_file,
     libcerror_error_t **error );

int libphdi_disk_descriptor_xml_file_set_root_tag(
     libphdi_disk_descriptor_xml_file_t *disk_descriptor_xml_file,
     libphdi_xml_tag_t *tag,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBPHDI_DISK_DESCRIPTOR_XML_FILE_H ) */

