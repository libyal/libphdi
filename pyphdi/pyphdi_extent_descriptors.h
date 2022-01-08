/*
 * Python object definition of the sequence and iterator object of extent descriptors
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

#if !defined( _PYPHDI_EXTENT_DESCRIPTORS_H )
#define _PYPHDI_EXTENT_DESCRIPTORS_H

#include <common.h>
#include <types.h>

#include "pyphdi_libphdi.h"
#include "pyphdi_python.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct pyphdi_extent_descriptors pyphdi_extent_descriptors_t;

struct pyphdi_extent_descriptors
{
	/* Python object initialization
	 */
	PyObject_HEAD

	/* The parent object
	 */
	PyObject *parent_object;

	/* The get item by index callback function
	 */
	PyObject* (*get_item_by_index)(
	             PyObject *parent_object,
	             int index );

	/* The current index
	 */
	int current_index;

	/* The number of items
	 */
	int number_of_items;
};

extern PyTypeObject pyphdi_extent_descriptors_type_object;

PyObject *pyphdi_extent_descriptors_new(
           PyObject *parent_object,
           PyObject* (*get_item_by_index)(
                        PyObject *parent_object,
                        int index ),
           int number_of_items );

int pyphdi_extent_descriptors_init(
     pyphdi_extent_descriptors_t *sequence_object );

void pyphdi_extent_descriptors_free(
      pyphdi_extent_descriptors_t *sequence_object );

Py_ssize_t pyphdi_extent_descriptors_len(
            pyphdi_extent_descriptors_t *sequence_object );

PyObject *pyphdi_extent_descriptors_getitem(
           pyphdi_extent_descriptors_t *sequence_object,
           Py_ssize_t item_index );

PyObject *pyphdi_extent_descriptors_iter(
           pyphdi_extent_descriptors_t *sequence_object );

PyObject *pyphdi_extent_descriptors_iternext(
           pyphdi_extent_descriptors_t *sequence_object );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _PYPHDI_EXTENT_DESCRIPTORS_H ) */

