/*
 * Python object wrapper of libphdi_image_descriptor_t
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
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( HAVE_WINAPI )
#include <stdlib.h>
#endif

#include "pyphdi_error.h"
#include "pyphdi_image_descriptor.h"
#include "pyphdi_handle.h"
#include "pyphdi_integer.h"
#include "pyphdi_libcerror.h"
#include "pyphdi_libphdi.h"
#include "pyphdi_python.h"
#include "pyphdi_unused.h"

PyMethodDef pyphdi_image_descriptor_object_methods[] = {

	/* Functions to access the image descriptor values */

	{ "get_type",
	  (PyCFunction) pyphdi_image_descriptor_get_type,
	  METH_NOARGS,
	  "get_type() -> Integer\n"
	  "\n"
	  "Retrieves the type." },

	{ "get_filename",
	  (PyCFunction) pyphdi_image_descriptor_get_filename,
	  METH_NOARGS,
	  "get_filename() -> Unicode string or None\n"
	  "\n"
	  "Retrieves the filename." },

	/* Sentinel */
	{ NULL, NULL, 0, NULL }
};

PyGetSetDef pyphdi_image_descriptor_object_get_set_definitions[] = {

	{ "type",
	  (getter) pyphdi_image_descriptor_get_type,
	  (setter) 0,
	  "The type.",
	  NULL },

	{ "filename",
	  (getter) pyphdi_image_descriptor_get_filename,
	  (setter) 0,
	  "The filename.",
	  NULL },

	/* Sentinel */
	{ NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyphdi_image_descriptor_type_object = {
	PyVarObject_HEAD_INIT( NULL, 0 )

	/* tp_name */
	"pyphdi.image_descriptor",
	/* tp_basicsize */
	sizeof( pyphdi_image_descriptor_t ),
	/* tp_itemsize */
	0,
	/* tp_dealloc */
	(destructor) pyphdi_image_descriptor_free,
	/* tp_print */
	0,
	/* tp_getattr */
	0,
	/* tp_setattr */
	0,
	/* tp_compare */
	0,
	/* tp_repr */
	0,
	/* tp_as_number */
	0,
	/* tp_as_sequence */
	0,
	/* tp_as_mapping */
	0,
	/* tp_hash */
	0,
	/* tp_call */
	0,
	/* tp_str */
	0,
	/* tp_getattro */
	0,
	/* tp_setattro */
	0,
	/* tp_as_buffer */
	0,
	/* tp_flags */
	Py_TPFLAGS_DEFAULT,
	/* tp_doc */
	"pyphdi image descriptor object (wraps libphdi_image_descriptor_t)",
	/* tp_traverse */
	0,
	/* tp_clear */
	0,
	/* tp_richcompare */
	0,
	/* tp_weaklistoffset */
	0,
	/* tp_iter */
	0,
	/* tp_iternext */
	0,
	/* tp_methods */
	pyphdi_image_descriptor_object_methods,
	/* tp_members */
	0,
	/* tp_getset */
	pyphdi_image_descriptor_object_get_set_definitions,
	/* tp_base */
	0,
	/* tp_dict */
	0,
	/* tp_descr_get */
	0,
	/* tp_descr_set */
	0,
	/* tp_dictoffset */
	0,
	/* tp_init */
	(initproc) pyphdi_image_descriptor_init,
	/* tp_alloc */
	0,
	/* tp_new */
	0,
	/* tp_free */
	0,
	/* tp_is_gc */
	0,
	/* tp_bases */
	NULL,
	/* tp_mro */
	NULL,
	/* tp_cache */
	NULL,
	/* tp_subclasses */
	NULL,
	/* tp_weaklist */
	NULL,
	/* tp_del */
	0
};

/* Creates a new image descriptor object
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyphdi_image_descriptor_new(
           libphdi_image_descriptor_t *image_descriptor,
           PyObject *parent_object )
{
	pyphdi_image_descriptor_t *pyphdi_image_descriptor = NULL;
	static char *function                                = "pyphdi_image_descriptor_new";

	if( image_descriptor == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid image descriptor.",
		 function );

		return( NULL );
	}
	pyphdi_image_descriptor = PyObject_New(
	                            struct pyphdi_image_descriptor,
	                            &pyphdi_image_descriptor_type_object );

	if( pyphdi_image_descriptor == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to initialize image descriptor.",
		 function );

		goto on_error;
	}
	if( pyphdi_image_descriptor_init(
	     pyphdi_image_descriptor ) != 0 )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to initialize image descriptor.",
		 function );

		goto on_error;
	}
	pyphdi_image_descriptor->image_descriptor = image_descriptor;
	pyphdi_image_descriptor->parent_object     = parent_object;

	Py_IncRef(
	 (PyObject *) pyphdi_image_descriptor->parent_object );

	return( (PyObject *) pyphdi_image_descriptor );

on_error:
	if( pyphdi_image_descriptor != NULL )
	{
		Py_DecRef(
		 (PyObject *) pyphdi_image_descriptor );
	}
	return( NULL );
}

/* Initializes an image descriptor object
 * Returns 0 if successful or -1 on error
 */
int pyphdi_image_descriptor_init(
     pyphdi_image_descriptor_t *pyphdi_image_descriptor )
{
	static char *function = "pyphdi_image_descriptor_init";

	if( pyphdi_image_descriptor == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid image descriptor.",
		 function );

		return( -1 );
	}
	/* Make sure libphdi image descriptor is set to NULL
	 */
	pyphdi_image_descriptor->image_descriptor = NULL;

	return( 0 );
}

/* Frees an image descriptor object
 */
void pyphdi_image_descriptor_free(
      pyphdi_image_descriptor_t *pyphdi_image_descriptor )
{
	libcerror_error_t *error    = NULL;
	struct _typeobject *ob_type = NULL;
	static char *function       = "pyphdi_image_descriptor_free";

	if( pyphdi_image_descriptor == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid image descriptor.",
		 function );

		return;
	}
	if( pyphdi_image_descriptor->image_descriptor == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid image descriptor - missing libphdi image descriptor.",
		 function );

		return;
	}
	ob_type = Py_TYPE(
	           pyphdi_image_descriptor );

	if( ob_type == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: missing ob_type.",
		 function );

		return;
	}
	if( ob_type->tp_free == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid ob_type - missing tp_free.",
		 function );

		return;
	}
	if( libphdi_image_descriptor_free(
	     &( pyphdi_image_descriptor->image_descriptor ),
	     &error ) != 1 )
	{
		pyphdi_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to free libphdi image descriptor.",
		 function );

		libcerror_error_free(
		 &error );
	}
	if( pyphdi_image_descriptor->parent_object != NULL )
	{
		Py_DecRef(
		 (PyObject *) pyphdi_image_descriptor->parent_object );
	}
	ob_type->tp_free(
	 (PyObject*) pyphdi_image_descriptor );
}

/* Retrieves the type
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyphdi_image_descriptor_get_type(
           pyphdi_image_descriptor_t *pyphdi_image_descriptor,
           PyObject *arguments PYPHDI_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error = NULL;
	PyObject *integer_object = NULL;
	static char *function    = "pyphdi_image_descriptor_get_type";
	int result               = 0;
	int type                 = 0;

	PYPHDI_UNREFERENCED_PARAMETER( arguments )

	if( pyphdi_image_descriptor == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid image descriptor.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libphdi_image_descriptor_get_type(
	          pyphdi_image_descriptor->image_descriptor,
	          &type,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyphdi_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve type.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
#if PY_MAJOR_VERSION >= 3
	integer_object = PyLong_FromLong(
	                  (long) type );
#else
	integer_object = PyInt_FromLong(
	                  (long) type );
#endif
	return( integer_object );
}

/* Retrieves the filename
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyphdi_image_descriptor_get_filename(
           pyphdi_image_descriptor_t *pyphdi_image_descriptor,
           PyObject *arguments PYPHDI_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error = NULL;
	PyObject *string_object  = NULL;
	const char *errors       = NULL;
	uint8_t *filename        = NULL;
	static char *function    = "pyphdi_image_descriptor_get_filename";
	size_t filename_size     = 0;
	int result               = 0;

	PYPHDI_UNREFERENCED_PARAMETER( arguments )

	if( pyphdi_image_descriptor == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid image descriptor.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libphdi_image_descriptor_get_utf8_filename_size(
	          pyphdi_image_descriptor->image_descriptor,
	          &filename_size,
	          &error );

	Py_END_ALLOW_THREADS

	if( result == -1 )
	{
		pyphdi_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve filename size.",
		 function );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	else if( ( result == 0 )
	      || ( filename_size == 0 ) )
	{
		Py_IncRef(
		 Py_None );

		return( Py_None );
	}
	filename = (uint8_t *) PyMem_Malloc(
	                        sizeof( uint8_t ) * filename_size );

	if( filename == NULL )
	{
		PyErr_Format(
		 PyExc_IOError,
		 "%s: unable to create filename.",
		 function );

		goto on_error;
	}
	Py_BEGIN_ALLOW_THREADS

	result = libphdi_image_descriptor_get_utf8_filename(
		  pyphdi_image_descriptor->image_descriptor,
		  filename,
		  filename_size,
		  &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyphdi_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve filename.",
		 function );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	/* Pass the string length to PyUnicode_DecodeUTF8
	 * otherwise it makes the end of string character is part
	 * of the string
	 */
	string_object = PyUnicode_DecodeUTF8(
			 (char *) filename,
			 (Py_ssize_t) filename_size - 1,
			 errors );

	PyMem_Free(
	 filename );

	return( string_object );

on_error:
	if( filename != NULL )
	{
		PyMem_Free(
		 filename );
	}
	return( NULL );
}

