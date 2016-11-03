/*
 * Python object definition of the libphdi file
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

#if !defined( _PYPHDI_FILE_H )
#define _PYPHDI_FILE_H

#include <common.h>
#include <types.h>

#include "pyphdi_libbfio.h"
#include "pyphdi_libphdi.h"
#include "pyphdi_python.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct pyphdi_file pyphdi_file_t;

struct pyphdi_file
{
	/* Python object initialization
	 */
	PyObject_HEAD

	/* The libphdi file
	 */
	libphdi_file_t *file;

	/* The libbfio file IO handle
	 */
	libbfio_handle_t *file_io_handle;
};

extern PyMethodDef pyphdi_file_object_methods[];
extern PyTypeObject pyphdi_file_type_object;

PyObject *pyphdi_file_new(
           void );

PyObject *pyphdi_file_new_open(
           PyObject *self,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pyphdi_file_new_open_file_object(
           PyObject *self,
           PyObject *arguments,
           PyObject *keywords );

int pyphdi_file_init(
     pyphdi_file_t *pyphdi_file );

void pyphdi_file_free(
      pyphdi_file_t *pyphdi_file );

PyObject *pyphdi_file_signal_abort(
           pyphdi_file_t *pyphdi_file,
           PyObject *arguments );

PyObject *pyphdi_file_open(
           pyphdi_file_t *pyphdi_file,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pyphdi_file_open_file_object(
           pyphdi_file_t *pyphdi_file,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pyphdi_file_close(
           pyphdi_file_t *pyphdi_file,
           PyObject *arguments );

PyObject *pyphdi_file_read_buffer(
           pyphdi_file_t *pyphdi_file,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pyphdi_file_read_buffer_at_offset(
           pyphdi_file_t *pyphdi_file,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pyphdi_file_seek_offset(
           pyphdi_file_t *pyphdi_file,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pyphdi_file_get_offset(
           pyphdi_file_t *pyphdi_file,
           PyObject *arguments );

PyObject *pyphdi_file_get_media_size(
           pyphdi_file_t *pyphdi_file,
           PyObject *arguments );

#if defined( __cplusplus )
}
#endif

#endif

