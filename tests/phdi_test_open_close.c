/*
 * Library open close testing program
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

#include <common.h>
#include <file_stream.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include "phdi_test_libcerror.h"
#include "phdi_test_libcstring.h"
#include "phdi_test_libcsystem.h"
#include "phdi_test_libphdi.h"

/* Tests single open and close of a handle
 * Returns 1 if successful, 0 if not or -1 on error
 */
int phdi_test_single_open_close_handle(
     libcstring_system_character_t *filename,
     int access_flags,
     int expected_result )
{
	libcerror_error_t *error = NULL;
	libphdi_handle_t *handle = NULL;
	static char *function    = "phdi_test_single_open_close_handle";
	char *access_string      = NULL;
	int result               = 0;

	if( access_flags == LIBPHDI_OPEN_READ )
	{
		access_string = "read";
	}
	else if( access_flags == LIBPHDI_OPEN_WRITE )
	{
		access_string = "write";
	}
	else
	{
		access_string = "UNKNOWN";
	}
	fprintf(
	 stdout,
	 "Testing single open close of: " );

	if( filename != NULL )
	{
		fprintf(
		 stdout,
		 "%" PRIs_LIBCSTRING_SYSTEM "",
		 filename );
	}
	else
	{
		fprintf(
		 stdout,
		 "NULL" );
	}
	fprintf(
	 stdout,
	 " with access: %s\t",
	 access_string );

	if( libphdi_handle_initialize(
	     &handle,
	     &error ) != 1 )
	{
		libcerror_error_set(
		 &error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create handle.",
		 function );

		goto on_error;
	}
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
	result = libphdi_handle_open_wide(
	          handle,
	          filename,
	          access_flags,
	          &error );
#else
	result = libphdi_handle_open(
	          handle,
	          filename,
	          access_flags,
	          &error );
#endif
	if( result == 1 )
	{
		if( libphdi_handle_close(
		     handle,
		     &error ) != 0 )
		{
			libcerror_error_set(
			 &error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_CLOSE_FAILED,
			 "%s: unable to close handle.",
			 function );

			goto on_error;
		}
	}
	if( libphdi_handle_free(
	     &handle,
	     &error ) != 1 )
	{
		libcerror_error_set(
		 &error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to free handle.",
		 function );

		goto on_error;
	}
	result = ( expected_result == result );

	if( result == 1 )
	{
		fprintf(
		 stdout,
		 "(PASS)" );
	}
	else
	{
		fprintf(
		 stdout,
		 "(FAIL)" );
	}
	fprintf(
	 stdout,
	 "\n" );

	if( error != NULL )
	{
		libcerror_error_backtrace_fprint(
		 error,
		 stderr );
		libcerror_error_free(
		 &error );
	}
	return( result );

on_error:
	if( error != NULL )
	{
		libcerror_error_backtrace_fprint(
		 error,
		 stderr );
		libcerror_error_free(
		 &error );
	}
	if( handle != NULL )
	{
		libphdi_handle_free(
		 &handle,
		 NULL);
	}
	return( -1 );
}

/* Tests multiple open and close of a handle
 * Returns 1 if successful, 0 if not or -1 on error
 */
int phdi_test_multi_open_close_handle(
     libcstring_system_character_t *filename,
     int access_flags,
     int expected_result )
{
	libcerror_error_t *error = NULL;
	libphdi_handle_t *handle = NULL;
	static char *function    = "phdi_test_multi_open_close_handle";
	char *access_string      = NULL;
	int result               = 0;

	if( access_flags == LIBPHDI_OPEN_READ )
	{
		access_string = "read";
	}
	else if( access_flags == LIBPHDI_OPEN_WRITE )
	{
		access_string = "write";
	}
	else
	{
		access_string = "UNKNOWN";
	}
	fprintf(
	 stdout,
	 "Testing multi open close of: " );

	if( filename != NULL )
	{
		fprintf(
		 stdout,
		 "%" PRIs_LIBCSTRING_SYSTEM "",
		 filename );
	}
	else
	{
		fprintf(
		 stdout,
		 "NULL" );
	}
	fprintf(
	 stdout,
	 " with access: %s\t",
	 access_string );

	if( libphdi_handle_initialize(
	     &handle,
	     &error ) != 1 )
	{
		libcerror_error_set(
		 &error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create handle.",
		 function );

		goto on_error;
	}
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
	result = libphdi_handle_open_wide(
	          handle,
	          filename,
	          access_flags,
	          &error );
#else
	result = libphdi_handle_open(
	          handle,
	          filename,
	          access_flags,
	          &error );
#endif
	if( result == 1 )
	{
		if( libphdi_handle_close(
		     handle,
		     &error ) != 0 )
		{
			libcerror_error_set(
			 &error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_CLOSE_FAILED,
			 "%s: unable to close handle.",
			 function );

			goto on_error;
		}
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
		result = libphdi_handle_open_wide(
		          handle,
		          filename,
		          access_flags,
		          &error );
#else
		result = libphdi_handle_open(
		          handle,
		          filename,
		          access_flags,
		          &error );
#endif
		if( result == 1 )
		{
			if( libphdi_handle_close(
			     handle,
			     &error ) != 0 )
			{
				libcerror_error_set(
				 &error,
				 LIBCERROR_ERROR_DOMAIN_IO,
				 LIBCERROR_IO_ERROR_CLOSE_FAILED,
				 "%s: unable to close handle.",
				 function );

				goto on_error;
			}
		}
	}
	if( libphdi_handle_free(
	     &handle,
	     &error ) != 1 )
	{
		libcerror_error_set(
		 &error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to free handle.",
		 function );

		goto on_error;
	}
	result = ( expected_result == result );

	if( result == 1 )
	{
		fprintf(
		 stdout,
		 "(PASS)" );
	}
	else
	{
		fprintf(
		 stdout,
		 "(FAIL)" );
	}
	fprintf(
	 stdout,
	 "\n" );

	if( error != NULL )
	{
		libcerror_error_backtrace_fprint(
		 error,
		 stderr );
		libcerror_error_free(
		 &error );
	}
	return( result );

on_error:
	if( error != NULL )
	{
		libcerror_error_backtrace_fprint(
		 error,
		 stderr );
		libcerror_error_free(
		 &error );
	}
	if( handle != NULL )
	{
		libphdi_handle_free(
		 &handle,
		 NULL);
	}
	return( -1 );
}

/* The main program
 */
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
int wmain( int argc, wchar_t * const argv[] )
#else
int main( int argc, char * const argv[] )
#endif
{
	libcstring_system_character_t *source = NULL;
	libcstring_system_integer_t option    = 0;

	while( ( option = libcsystem_getopt(
	                   argc,
	                   argv,
	                   _LIBCSTRING_SYSTEM_STRING( "" ) ) ) != (libcstring_system_integer_t) -1 )
	{
		switch( option )
		{
			case (libcstring_system_integer_t) '?':
			default:
				fprintf(
				 stderr,
				 "Invalid argument: %" PRIs_LIBCSTRING_SYSTEM ".\n",
				 argv[ optind - 1 ] );

				return( EXIT_FAILURE );
		}
	}
	if( optind == argc )
	{
		fprintf(
		 stderr,
		 "Missing source file or device.\n" );

		return( EXIT_FAILURE );
	}
	source = argv[ optind ];

#if defined( HAVE_DEBUG_OUTPUT ) && defined( PHDI_TEST_OPEN_CLOSE_VERBOSE )
	libphdi_notify_set_verbose(
	 1 );
	libphdi_notify_set_stream(
	 stderr,
	 NULL );
#endif

	/* Case 0: single open and close of a handle using filename
	 */
	if( phdi_test_single_open_close_handle(
	     source,
	     LIBPHDI_OPEN_READ,
	     1 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test single open close.\n" );

		return( EXIT_FAILURE );
	}
	if( phdi_test_single_open_close_handle(
	     NULL,
	     LIBPHDI_OPEN_READ,
	     -1 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test single open close.\n" );

		return( EXIT_FAILURE );
	}
	if( phdi_test_single_open_close_handle(
	     source,
	     LIBPHDI_OPEN_WRITE,
	     -1 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test single open close.\n" );

		return( EXIT_FAILURE );
	}
	/* Case 1: multiple open and close of a handle using filename
	 */
	if( phdi_test_multi_open_close_handle(
	     source,
	     LIBPHDI_OPEN_READ,
	     1 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test multi open close.\n" );

		return( EXIT_FAILURE );
	}
	return( EXIT_SUCCESS );
}

