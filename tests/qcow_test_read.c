/*
 * Library read testing program
 *
 * Copyright (c) 2010-2014, Joachim Metz <joachim.metz@gmail.com>
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

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include <stdio.h>

#include "qcow_test_libcstring.h"
#include "qcow_test_libcerror.h"
#include "qcow_test_libqcow.h"
#include "qcow_test_unused.h"

/* Define to make qcow_test_read generate verbose output
#define QCOW_TEST_READ_VERBOSE
 */

#define QCOW_TEST_READ_BUFFER_SIZE	4096

/* Tests libqcow_file_seek_offset
 * Returns 1 if successful, 0 if not or -1 on error
 */
int qcow_test_seek_offset(
     libqcow_file_t *file,
     off64_t input_offset,
     int input_whence,
     off64_t expected_offset )
{
	libqcow_error_t *error = NULL;
	off64_t result_offset  = 0;
	int result             = 0;

	if( file == NULL )
	{
		return( -1 );
	}
	result_offset = libqcow_file_seek_offset(
	                 file,
	                 input_offset,
	                 input_whence,
	                 &error );

	if( expected_offset != result_offset )
	{
		fprintf(
		 stderr,
		 "Unexpected result offset: %" PRIi64 "\n",
		 result_offset );
	}
	else
	{
		result = 1;
	}
	if( error != NULL )
	{
		if( result != 1 )
		{
			libqcow_error_backtrace_fprint(
			 error,
			 stderr );
		}
		libqcow_error_free(
		 &error );
	}
	return( result );
}

/* Tests libqcow_file_read_buffer
 * Returns 1 if successful, 0 if not or -1 on error
 */
int qcow_test_read_buffer(
     libqcow_file_t *file,
     size64_t input_size,
     size64_t expected_size )
{
	uint8_t buffer[ QCOW_TEST_READ_BUFFER_SIZE ];

	libqcow_error_t *error  = NULL;
	size64_t remaining_size = 0;
	size64_t result_size    = 0;
	size_t read_size        = 0;
	ssize_t read_count      = 0;
	int result              = 0;

	if( file == NULL )
	{
		return( -1 );
	}
	remaining_size = input_size;

	while( remaining_size > 0 )
	{
		read_size = QCOW_TEST_READ_BUFFER_SIZE;

		if( remaining_size < (size64_t) read_size )
		{
			read_size = (size_t) remaining_size;
		}
		read_count = libqcow_file_read_buffer(
			      file,
			      buffer,
			      read_size,
			      &error );

		if( read_count < 0 )
		{
			break;
		}
		remaining_size -= (size64_t) read_count;
		result_size    += (size64_t) read_count;

		if( read_count != (ssize_t) read_size )
		{
			break;
		}
	}
	if( expected_size != result_size )
	{
		fprintf(
		 stderr,
		 "Unexpected read count: %" PRIu64 "\n",
		 result_size );
	}
	else
	{
		result = 1;
	}
	if( error != NULL )
	{
		if( result != 1 )
		{
			libqcow_error_backtrace_fprint(
			 error,
			 stderr );
		}
		libqcow_error_free(
		 &error );
	}
	return( result );
}

/* Tests libqcow_file_read_buffer_at_offset
 * Returns 1 if successful, 0 if not or -1 on error
 */
int qcow_test_read_buffer_at_offset(
     libqcow_file_t *file,
     off64_t input_offset,
     size64_t input_size,
     off64_t expected_offset,
     size64_t expected_size )
{
	uint8_t buffer[ QCOW_TEST_READ_BUFFER_SIZE ];

	libqcow_error_t *error  = NULL;
	off64_t result_offset   = 0;
	size64_t remaining_size = 0;
	size64_t result_size    = 0;
	size_t read_size        = 0;
	ssize_t read_count      = 0;
	int result              = 0;

	if( file == NULL )
	{
		return( -1 );
	}
	remaining_size = input_size;

	fprintf(
	 stdout,
	 "Testing reading buffer at offset: %" PRIi64 " and size: %" PRIu64 "\t",
	 input_offset,
	 input_size );

	while( remaining_size > 0 )
	{
		read_size = QCOW_TEST_READ_BUFFER_SIZE;

		if( remaining_size < (size64_t) read_size )
		{
			read_size = (size_t) remaining_size;
		}
		read_count = libqcow_file_read_buffer_at_offset(
			      file,
			      buffer,
			      read_size,
			      input_offset,
			      &error );

		if( read_count < 0 )
		{
			break;
		}
		input_offset   += (size64_t) read_count;
		remaining_size -= (size64_t) read_count;
		result_size    += (size64_t) read_count;

		if( read_count != (ssize_t) read_size )
		{
			break;
		}
	}
	if( libqcow_file_get_offset(
	     file,
	     &result_offset,
	     &error ) != 1 )
	{
		result = -1;
	}
	if( expected_offset != result_offset )
	{
		fprintf(
		 stderr,
		 "Unexpected offset: %" PRIi64 "\n",
		 result_offset );
	}
	else if( expected_size != result_size )
	{
		fprintf(
		 stderr,
		 "Unexpected read count: %" PRIu64 "\n",
		 result_size );
	}
	else
	{
		result = 1;
	}
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
		if( result != 1 )
		{
			libqcow_error_backtrace_fprint(
			 error,
			 stderr );
		}
		libqcow_error_free(
		 &error );
	}
	return( result );
}

/* Tests reading data at a specific offset
 * Returns 1 if successful, 0 if not or -1 on error
 */
int qcow_test_seek_offset_and_read_buffer(
     libqcow_file_t *file,
     off64_t input_offset,
     int input_whence,
     size64_t input_size,
     off64_t expected_offset,
     size64_t expected_size )
{
	const char *whence_string = NULL;
	int result                = 0;

	if( file == NULL )
	{
		return( -1 );
	}
	if( input_whence == SEEK_CUR )
	{
		whence_string = "SEEK_CUR";
	}
	else if( input_whence == SEEK_END )
	{
		whence_string = "SEEK_END";
	}
	else if( input_whence == SEEK_SET )
	{
		whence_string = "SEEK_SET";
	}
	else
	{
		whence_string = "UNKNOWN";
	}
	fprintf(
	 stdout,
	 "Testing reading buffer at offset: %" PRIi64 ", whence: %s and size: %" PRIu64 "\t",
	 input_offset,
	 whence_string,
	 input_size );

	result = qcow_test_seek_offset(
	          file,
	          input_offset,
	          input_whence,
	          expected_offset );

	if( result == 1 )
	{
		if( input_offset >= 0 )
		{
			result = qcow_test_read_buffer(
				  file,
				  input_size,
				  expected_size );
		}
	}
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

	return( result );
}

/* Tests reading data from a file
 * Returns 1 if successful, 0 if not or -1 on error
 */
int qcow_test_read_from_file(
     libqcow_file_t *file,
     size64_t media_size )
{
	int result = 0;

	if( file == NULL )
	{
		return( -1 );
	}
	if( media_size > (size64_t) INT64_MAX )
	{
		fprintf(
		 stderr,
		 "Media size exceeds maximum.\n" );

		return( -1 );
	}
	/* Case 0: test full read
	 */

	/* Test: offset: 0 size: <media_size>
	 * Expected result: offset: 0 size: <media_size>
	 */
	result = qcow_test_seek_offset_and_read_buffer(
	          file,
	          0,
	          SEEK_SET,
	          media_size,
	          0,
	          media_size );

	if( result != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test seek offset and read buffer.\n" );

		return( result );
	}
	/* Test: offset: 0 size: <media_size>
	 * Expected result: offset: 0 size: <media_size>
	 */
	result = qcow_test_seek_offset_and_read_buffer(
	          file,
	          0,
	          SEEK_SET,
	          media_size,
	          0,
	          media_size );

	if( result != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test seek offset and read buffer.\n" );

		return( result );
	}

	/* Case 1: test buffer at offset read
	 */

	/* Test: offset: <media_size / 7> size: <media_size / 2>
	 * Expected result: offset: <media_size / 7> size: <media_size / 2>
	 */
	result = qcow_test_seek_offset_and_read_buffer(
	          file,
	          (off64_t) ( media_size / 7 ),
	          SEEK_SET,
	          media_size / 2,
	          (off64_t) ( media_size / 7 ),
	          media_size / 2 );

	if( result != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test seek offset and read buffer.\n" );

		return( result );
	}
	/* Test: offset: <media_size / 7> size: <media_size / 2>
	 * Expected result: offset: <media_size / 7> size: <media_size / 2>
	 */
	result = qcow_test_seek_offset_and_read_buffer(
	          file,
	          (off64_t) ( media_size / 7 ),
	          SEEK_SET,
	          media_size / 2,
	          (off64_t) ( media_size / 7 ),
	          media_size / 2 );

	if( result != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test seek offset and read buffer.\n" );

		return( result );
	}

	/* Case 2: test read beyond media size
	 */

	if( media_size < 1024 )
	{
		/* Test: offset: <media_size - 1024> size: 4096
		 * Expected result: offset: -1 size: <undetermined>
		 */
		result = qcow_test_seek_offset_and_read_buffer(
		          file,
		          (off64_t) ( media_size - 1024 ),
		          SEEK_SET,
		          4096,
		          -1,
		          (size64_t) -1 );

		if( result != 1 )
		{
			fprintf(
			 stderr,
			 "Unable to test seek offset and read buffer.\n" );

			return( result );
		}
		/* Test: offset: <media_size - 1024> size: 4096
		 * Expected result: offset: -1 size: <undetermined>
		 */
		result = qcow_test_seek_offset_and_read_buffer(
		          file,
		          (off64_t) ( media_size - 1024 ),
		          SEEK_SET,
		          4096,
		          -1,
		          (size64_t) -1 );

		if( result != 1 )
		{
			fprintf(
			 stderr,
			 "Unable to test seek offset and read buffer.\n" );

			return( result );
		}
	}
	else
	{
		/* Test: offset: <media_size - 1024> size: 4096
		 * Expected result: offset: <media_size - 1024> size: 1024
		 */
		result = qcow_test_seek_offset_and_read_buffer(
		          file,
		          (off64_t) ( media_size - 1024 ),
		          SEEK_SET,
		          4096,
		          (off64_t) ( media_size - 1024 ),
		          1024 );

		if( result != 1 )
		{
			fprintf(
			 stderr,
			 "Unable to test read.\n" );

			return( result );
		}
		/* Test: offset: <media_size - 1024> size: 4096
		 * Expected result: offset: <media_size - 1024> size: 1024
		 */
		result = qcow_test_seek_offset_and_read_buffer(
		          file,
		          (off64_t) ( media_size - 1024 ),
		          SEEK_SET,
		          4096,
		          (off64_t) ( media_size - 1024 ),
		          1024 );

		if( result != 1 )
		{
			fprintf(
			 stderr,
			 "Unable to test seek offset and read buffer.\n" );

			return( result );
		}
	}
	/* Case 3: test buffer at offset read
	 */

	/* Test: offset: <media_size / 7> size: <media_size / 2>
	 * Expected result: offset: < ( media_size / 7 ) + ( media_size / 2 ) > size: <media_size / 2>
	 */
	result = qcow_test_read_buffer_at_offset(
	          file,
	          (off64_t) ( media_size / 7 ),
	          media_size / 2,
	          (off64_t) ( media_size / 7 ) + ( media_size / 2 ),
	          media_size / 2 );

	if( result != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test read buffer at offset.\n" );

		return( result );
	}
	/* Test: offset: <media_size / 7> size: <media_size / 2>
	 * Expected result: offset: < ( media_size / 7 ) + ( media_size / 2 ) > size: <media_size / 2>
	 */
	result = qcow_test_read_buffer_at_offset(
	          file,
	          (off64_t) ( media_size / 7 ),
	          media_size / 2,
	          (off64_t) ( media_size / 7 ) + ( media_size / 2 ),
	          media_size / 2 );

	if( result != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test read buffer at offset.\n" );

		return( result );
	}
	return( 1 );
}

/* The main program
 */
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
int wmain( int argc, wchar_t * const argv[] )
#else
int main( int argc, char * const argv[] )
#endif
{
	libqcow_error_t *error = NULL;
	libqcow_file_t *file   = NULL;
	size64_t media_size    = 0;

	if( argc < 2 )
	{
		fprintf(
		 stderr,
		 "Missing filename.\n" );

		return( EXIT_FAILURE );
	}
#if defined( HAVE_DEBUG_OUTPUT ) && defined( QCOW_TEST_READ_VERBOSE )
	libqcow_notify_set_verbose(
	 1 );
	libqcow_notify_set_stream(
	 stderr,
	 NULL );
#endif
	/* Initialization
	 */
	if( libqcow_file_initialize(
	     &file,
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to create file.\n" );

		goto on_error;
	}
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
	if( libqcow_file_open_wide(
	     file,
	     argv[ 1 ],
	     LIBQCOW_OPEN_READ,
	     &error ) != 1 )
#else
	if( libqcow_file_open(
	     file,
	     argv[ 1 ],
	     LIBQCOW_OPEN_READ,
	     &error ) != 1 )
#endif
	{
		fprintf(
		 stderr,
		 "Unable to open file.\n" );

		goto on_error;
	}
	if( libqcow_file_get_media_size(
	     file,
	     &media_size,
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to retrieve media size.\n" );

		goto on_error;
	}
	fprintf(
	 stdout,
	 "Media size: %" PRIu64 " bytes\n",
	 media_size );

	if( qcow_test_read_from_file(
	     file,
	     media_size ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to read from file.\n" );

		goto on_error;
	}
	/* Clean up
	 */
	if( libqcow_file_close(
	     file,
	     &error ) != 0 )
	{
		fprintf(
		 stderr,
		 "Unable to close file.\n" );

		goto on_error;
	}
	if( libqcow_file_free(
	     &file,
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to free file.\n" );

		goto on_error;
	}
	return( EXIT_SUCCESS );

on_error:
	if( error != NULL )
	{
		libqcow_error_backtrace_fprint(
		 error,
		 stderr );
		libqcow_error_free(
		 &error );
	}
	if( file != NULL )
	{
		libqcow_file_close(
		 file,
		 NULL );
		libqcow_file_free(
		 &file,
		 NULL );
	}
	return( EXIT_FAILURE );
}

