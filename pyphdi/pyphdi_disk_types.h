/*
 * Python object definition of the libphdi disk types
 *
 * Copyright (C) 2015-2016, Joachim Metz <joachim.metz@gmail.com>
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This software is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this software.  If not, see <http://www.gnu.org/licenses/>.
 */

#if !defined( _PYPHDI_DISK_TYPES_H )
#define _PYPHDI_DISK_TYPES_H

#include <common.h>
#include <types.h>

#include "pyphdi_libphdi.h"
#include "pyphdi_python.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct pyphdi_disk_types pyphdi_disk_types_t;

struct pyphdi_disk_types
{
	/* Python object initialization
	 */
	PyObject_HEAD
};

extern PyTypeObject pyphdi_disk_types_type_object;

int pyphdi_disk_types_init_type(
     PyTypeObject *type_object );

PyObject *pyphdi_disk_types_new(
           void );

int pyphdi_disk_types_init(
     pyphdi_disk_types_t *pyphdi_disk_types );

void pyphdi_disk_types_free(
      pyphdi_disk_types_t *pyphdi_disk_types );

#if defined( __cplusplus )
}
#endif

#endif

