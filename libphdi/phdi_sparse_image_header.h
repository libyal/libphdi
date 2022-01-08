/*
 * File header of a Parallels sparse storage data image
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

#if !defined( _PHDI_SPARSE_IMAGE_HEADER_H )
#define _PHDI_SPARSE_IMAGE_HEADER_H

#include <common.h>
#include <types.h>

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct phdi_sparse_image_header phdi_sparse_image_header_t;

struct phdi_sparse_image_header
{
	/* Signature
	 * Consists of 16 bytes
	 */
	uint8_t signature[ 16 ];

	/* The format version
	 * Consists of 4 bytes
	 */
	uint8_t format_version[ 4 ];

	/* The number of heads
	 * Consists of 4 bytes
	 */
	uint8_t number_of_heads[ 4 ];

	/* The number of cylinders
	 * Consists of 4 bytes
	 */
	uint8_t number_of_cylinders[ 4 ];

	/* The block size
	 * Consists of 4 bytes
	 */
	uint8_t block_size[ 4 ];

	/* The number of block allocation table entries
	 * Consists of 4 bytes
	 */
	uint8_t number_of_allocation_table_entries[ 4 ];

	/* The number of sectors
	 * Consists of 8 bytes
	 */
	uint8_t number_of_sectors[ 8 ];

	/* Unknown (in use?)
	 * Consists of 4 bytes
	 */
	uint8_t unknown1[ 4 ];

	/* The data start sector
	 * Consists of 4 bytes
	 */
	uint8_t data_start_sector[ 4 ];

	/* Unknown (padding)
	 * Consists of 12 bytes
	 */
	uint8_t unknown2[ 12 ];
};

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _PHDI_SPARSE_IMAGE_HEADER_H ) */

