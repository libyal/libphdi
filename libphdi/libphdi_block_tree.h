/*
 * Block tree functions
 *
 * Copyright (C) 2015-2024, Joachim Metz <joachim.metz@gmail.com>
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

#if !defined( _LIBPHDI_BLOCK_TREE_H )
#define _LIBPHDI_BLOCK_TREE_H

#include <common.h>
#include <types.h>

#include "libphdi_block_descriptor.h"
#include "libphdi_block_tree_node.h"
#include "libphdi_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libphdi_block_tree libphdi_block_tree_t;

struct libphdi_block_tree
{
	/* The block tree root node
	 */
	libphdi_block_tree_node_t *root_node;

	/* The leaf value size
	 */
	size64_t leaf_value_size;
};

int libphdi_block_tree_initialize(
     libphdi_block_tree_t **block_tree,
     size64_t size,
     size64_t leaf_value_size,
     libcerror_error_t **error );

int libphdi_block_tree_free(
     libphdi_block_tree_t **block_tree,
     int (*value_free_function)(
            intptr_t **value,
            libcerror_error_t **error ),
     libcerror_error_t **error );

int libphdi_block_tree_get_block_descriptor_by_offset(
     libphdi_block_tree_t *block_tree,
     off64_t offset,
     libphdi_block_descriptor_t **block_descriptor,
     off64_t *block_offset,
     libcerror_error_t **error );

int libphdi_block_tree_insert_block_descriptor_by_offset(
     libphdi_block_tree_t *block_tree,
     off64_t offset,
     libphdi_block_descriptor_t *block_descriptor,
     int *leaf_value_index,
     libphdi_block_tree_node_t **leaf_block_tree_node,
     libphdi_block_descriptor_t **existing_block_descriptor,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBPHDI_BLOCK_TREE_H ) */

