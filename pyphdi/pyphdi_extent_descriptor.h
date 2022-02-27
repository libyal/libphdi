/*
 * Python object wrapper of libphdi_extent_descriptor_t
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

#if !defined( _PYPHDI_EXTENT_DESCRIPTOR_H )
#define _PYPHDI_EXTENT_DESCRIPTOR_H

#include <common.h>
#include <types.h>

#include "pyphdi_handle.h"
#include "pyphdi_libphdi.h"
#include "pyphdi_python.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct pyphdi_extent_descriptor pyphdi_extent_descriptor_t;

struct pyphdi_extent_descriptor
{
	/* Python object initialization
	 */
	PyObject_HEAD

	/* The libphdi extent descriptor
	 */
	libphdi_extent_descriptor_t *extent_descriptor;

	/* The parent object
	 */
	PyObject *parent_object;
};

extern PyMethodDef pyphdi_extent_descriptor_object_methods[];
extern PyTypeObject pyphdi_extent_descriptor_type_object;

PyObject *pyphdi_extent_descriptor_new(
           libphdi_extent_descriptor_t *extent_descriptor,
           PyObject *parent_object );

int pyphdi_extent_descriptor_init(
     pyphdi_extent_descriptor_t *pyphdi_extent_descriptor );

void pyphdi_extent_descriptor_free(
      pyphdi_extent_descriptor_t *pyphdi_extent_descriptor );

PyObject *pyphdi_extent_descriptor_get_type(
           pyphdi_extent_descriptor_t *pyphdi_extent_descriptor,
           PyObject *arguments );

PyObject *pyphdi_extent_descriptor_get_offset(
           pyphdi_extent_descriptor_t *pyphdi_extent_descriptor,
           PyObject *arguments );

PyObject *pyphdi_extent_descriptor_get_size(
           pyphdi_extent_descriptor_t *pyphdi_extent_descriptor,
           PyObject *arguments );

PyObject *pyphdi_extent_descriptor_get_filename(
           pyphdi_extent_descriptor_t *pyphdi_extent_descriptor,
           PyObject *arguments );

PyObject *pyphdi_extent_descriptor_get_number_of_images(
           pyphdi_extent_descriptor_t *pyphdi_extent_descriptor,
           PyObject *arguments );

PyObject *pyphdi_extent_descriptor_get_image_descriptor_by_index(
           PyObject *pyphdi_extent_descriptor,
           int imagesindex );

PyObject *pyphdi_extent_descriptor_get_image_descriptor(
           pyphdi_extent_descriptor_t *pyphdi_extent_descriptor,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pyphdi_extent_descriptor_get_image_descriptors(
           pyphdi_extent_descriptor_t *pyphdi_extent_descriptor,
           PyObject *arguments );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _PYPHDI_EXTENT_DESCRIPTOR_H ) */

