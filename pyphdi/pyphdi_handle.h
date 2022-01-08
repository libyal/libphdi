/*
 * Python object wrapper of libphdi_handle_t
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

#if !defined( _PYPHDI_HANDLE_H )
#define _PYPHDI_HANDLE_H

#include <common.h>
#include <types.h>

#include "pyphdi_libbfio.h"
#include "pyphdi_libphdi.h"
#include "pyphdi_python.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct pyphdi_handle pyphdi_handle_t;

struct pyphdi_handle
{
	/* Python object initialization
	 */
	PyObject_HEAD

	/* The libphdi handle
	 */
	libphdi_handle_t *handle;

	/* The libbfio file IO handle
	 */
	libbfio_handle_t *file_io_handle;

	/* The file IO pool
	 */
	libbfio_pool_t *file_io_pool;
};

extern PyMethodDef pyphdi_handle_object_methods[];
extern PyTypeObject pyphdi_handle_type_object;

int pyphdi_handle_init(
     pyphdi_handle_t *pyphdi_handle );

void pyphdi_handle_free(
      pyphdi_handle_t *pyphdi_handle );

PyObject *pyphdi_handle_signal_abort(
           pyphdi_handle_t *pyphdi_handle,
           PyObject *arguments );

PyObject *pyphdi_handle_open(
           pyphdi_handle_t *pyphdi_handle,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pyphdi_handle_open_file_object(
           pyphdi_handle_t *pyphdi_handle,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pyphdi_handle_open_extent_data_files(
           pyphdi_handle_t *pyphdi_handle,
           PyObject *arguments );

PyObject *pyphdi_handle_open_extent_data_files_as_file_objects(
           pyphdi_handle_t *pyphdi_handle,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pyphdi_handle_close(
           pyphdi_handle_t *pyphdi_handle,
           PyObject *arguments );

PyObject *pyphdi_handle_read_buffer(
           pyphdi_handle_t *pyphdi_handle,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pyphdi_handle_read_buffer_at_offset(
           pyphdi_handle_t *pyphdi_handle,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pyphdi_handle_seek_offset(
           pyphdi_handle_t *pyphdi_handle,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pyphdi_handle_get_offset(
           pyphdi_handle_t *pyphdi_handle,
           PyObject *arguments );

PyObject *pyphdi_handle_get_media_size(
           pyphdi_handle_t *pyphdi_handle,
           PyObject *arguments );

PyObject *pyphdi_handle_get_number_of_extents(
           pyphdi_handle_t *pyphdi_handle,
           PyObject *arguments );

PyObject *pyphdi_handle_get_extent_descriptor_by_index(
           PyObject *pyphdi_handle,
           int extent_index );

PyObject *pyphdi_handle_get_extent_descriptor(
           pyphdi_handle_t *pyphdi_handle,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pyphdi_handle_get_extent_descriptors(
           pyphdi_handle_t *pyphdi_handle,
           PyObject *arguments );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _PYPHDI_HANDLE_H ) */

