/*
 * Library cluster_table type test program
 *
 * Copyright (C) 2010-2022, Joachim Metz <joachim.metz@gmail.com>
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
#include <file_stream.h>
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include "qcow_test_libcerror.h"
#include "qcow_test_libqcow.h"
#include "qcow_test_macros.h"
#include "qcow_test_memory.h"
#include "qcow_test_unused.h"

#include "../libqcow/libqcow_cluster_table.h"

#if defined( __GNUC__ ) && !defined( LIBQCOW_DLL_IMPORT )

/* Tests the libqcow_cluster_table_initialize function
 * Returns 1 if successful or 0 if not
 */
int qcow_test_cluster_table_initialize(
     void )
{
	libcerror_error_t *error               = NULL;
	libqcow_cluster_table_t *cluster_table = NULL;
	int result                             = 0;

#if defined( HAVE_QCOW_TEST_MEMORY )
	int number_of_malloc_fail_tests        = 1;
	int number_of_memset_fail_tests        = 1;
	int test_number                        = 0;
#endif

	/* Test regular cases
	 */
	result = libqcow_cluster_table_initialize(
	          &cluster_table,
	          &error );

	QCOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	QCOW_TEST_ASSERT_IS_NOT_NULL(
	 "cluster_table",
	 cluster_table );

	QCOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libqcow_cluster_table_free(
	          &cluster_table,
	          &error );

	QCOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	QCOW_TEST_ASSERT_IS_NULL(
	 "cluster_table",
	 cluster_table );

	QCOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libqcow_cluster_table_initialize(
	          NULL,
	          &error );

	QCOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	QCOW_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	cluster_table = (libqcow_cluster_table_t *) 0x12345678UL;

	result = libqcow_cluster_table_initialize(
	          &cluster_table,
	          &error );

	cluster_table = NULL;

	QCOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	QCOW_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

#if defined( HAVE_QCOW_TEST_MEMORY )

	for( test_number = 0;
	     test_number < number_of_malloc_fail_tests;
	     test_number++ )
	{
		/* Test libqcow_cluster_table_initialize with malloc failing
		 */
		qcow_test_malloc_attempts_before_fail = test_number;

		result = libqcow_cluster_table_initialize(
		          &cluster_table,
		          &error );

		if( qcow_test_malloc_attempts_before_fail != -1 )
		{
			qcow_test_malloc_attempts_before_fail = -1;

			if( cluster_table != NULL )
			{
				libqcow_cluster_table_free(
				 &cluster_table,
				 NULL );
			}
		}
		else
		{
			QCOW_TEST_ASSERT_EQUAL_INT(
			 "result",
			 result,
			 -1 );

			QCOW_TEST_ASSERT_IS_NULL(
			 "cluster_table",
			 cluster_table );

			QCOW_TEST_ASSERT_IS_NOT_NULL(
			 "error",
			 error );

			libcerror_error_free(
			 &error );
		}
	}
	for( test_number = 0;
	     test_number < number_of_memset_fail_tests;
	     test_number++ )
	{
		/* Test libqcow_cluster_table_initialize with memset failing
		 */
		qcow_test_memset_attempts_before_fail = test_number;

		result = libqcow_cluster_table_initialize(
		          &cluster_table,
		          &error );

		if( qcow_test_memset_attempts_before_fail != -1 )
		{
			qcow_test_memset_attempts_before_fail = -1;

			if( cluster_table != NULL )
			{
				libqcow_cluster_table_free(
				 &cluster_table,
				 NULL );
			}
		}
		else
		{
			QCOW_TEST_ASSERT_EQUAL_INT(
			 "result",
			 result,
			 -1 );

			QCOW_TEST_ASSERT_IS_NULL(
			 "cluster_table",
			 cluster_table );

			QCOW_TEST_ASSERT_IS_NOT_NULL(
			 "error",
			 error );

			libcerror_error_free(
			 &error );
		}
	}
#endif /* defined( HAVE_QCOW_TEST_MEMORY ) */

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( cluster_table != NULL )
	{
		libqcow_cluster_table_free(
		 &cluster_table,
		 NULL );
	}
	return( 0 );
}

/* Tests the libqcow_cluster_table_free function
 * Returns 1 if successful or 0 if not
 */
int qcow_test_cluster_table_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libqcow_cluster_table_free(
	          NULL,
	          &error );

	QCOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	QCOW_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libqcow_cluster_table_get_number_of_references function
 * Returns 1 if successful or 0 if not
 */
int qcow_test_cluster_table_get_number_of_references(
     void )
{
	libcerror_error_t *error               = NULL;
	libqcow_cluster_table_t *cluster_table = NULL;
	int number_of_references               = 0;
	int result                             = 0;

	/* Initialize test
	 */
	result = libqcow_cluster_table_initialize(
	          &cluster_table,
	          &error );

	QCOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	QCOW_TEST_ASSERT_IS_NOT_NULL(
	 "cluster_table",
	 cluster_table );

	QCOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libqcow_cluster_table_get_number_of_references(
	          cluster_table,
	          &number_of_references,
	          &error );

	QCOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	QCOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libqcow_cluster_table_get_number_of_references(
	          NULL,
	          &number_of_references,
	          &error );

	QCOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	QCOW_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libqcow_cluster_table_get_number_of_references(
	          cluster_table,
	          NULL,
	          &error );

	QCOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	QCOW_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Clean up
	 */
	result = libqcow_cluster_table_free(
	          &cluster_table,
	          &error );

	QCOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	QCOW_TEST_ASSERT_IS_NULL(
	 "cluster_table",
	 cluster_table );

	QCOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( cluster_table != NULL )
	{
		libqcow_cluster_table_free(
		 &cluster_table,
		 NULL );
	}
	return( 0 );
}

/* Tests the libqcow_cluster_table_get_reference_by_index function
 * Returns 1 if successful or 0 if not
 */
int qcow_test_cluster_table_get_reference_by_index(
     void )
{
	libcerror_error_t *error               = NULL;
	libqcow_cluster_table_t *cluster_table = NULL;
	uint64_t reference                     = 0;
	int number_of_references               = 0;
	int result                             = 0;

	/* Initialize test
	 */
	result = libqcow_cluster_table_initialize(
	          &cluster_table,
	          &error );

	QCOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	QCOW_TEST_ASSERT_IS_NOT_NULL(
	 "cluster_table",
	 cluster_table );

	QCOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libqcow_cluster_table_get_number_of_references(
	          cluster_table,
	          &number_of_references,
	          &error );

	QCOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	QCOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	if( number_of_references > 0 )
	{
		result = libqcow_cluster_table_get_reference_by_index(
		          cluster_table,
		          0,
		          &reference,
		          &error );

		QCOW_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

		QCOW_TEST_ASSERT_IS_NULL(
		 "error",
		 error );
	}
	/* Test error cases
	 */
	result = libqcow_cluster_table_get_reference_by_index(
	          NULL,
	          0,
	          &reference,
	          &error );

	QCOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	QCOW_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libqcow_cluster_table_get_reference_by_index(
	          cluster_table,
	          -1,
	          &reference,
	          &error );

	QCOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	QCOW_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libqcow_cluster_table_get_reference_by_index(
	          cluster_table,
	          0,
	          NULL,
	          &error );

	QCOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	QCOW_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Clean up
	 */
	result = libqcow_cluster_table_free(
	          &cluster_table,
	          &error );

	QCOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	QCOW_TEST_ASSERT_IS_NULL(
	 "cluster_table",
	 cluster_table );

	QCOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( cluster_table != NULL )
	{
		libqcow_cluster_table_free(
		 &cluster_table,
		 NULL );
	}
	return( 0 );
}

/* Tests the libqcow_cluster_table_read function
 * Returns 1 if successful or 0 if not
 */
int qcow_test_cluster_table_read(
     void )
{
	libcerror_error_t *error               = NULL;
	libqcow_cluster_table_t *cluster_table = NULL;
	int result                             = 0;

	/* Initialize test
	 */
	result = libqcow_cluster_table_initialize(
	          &cluster_table,
	          &error );

	QCOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	QCOW_TEST_ASSERT_IS_NOT_NULL(
	 "cluster_table",
	 cluster_table );

	QCOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libqcow_cluster_table_read(
	          NULL,
	          NULL,
	          0,
	          0,
	          &error );

	QCOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	QCOW_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libqcow_cluster_table_read(
	          cluster_table,
	          NULL,
	          0,
	          0,
	          &error );

	QCOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	QCOW_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libqcow_cluster_table_read(
	          cluster_table,
	          NULL,
	          -1,
	          0,
	          &error );

	QCOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	QCOW_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Clean up
	 */
	result = libqcow_cluster_table_free(
	          &cluster_table,
	          &error );

	QCOW_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	QCOW_TEST_ASSERT_IS_NULL(
	 "cluster_table",
	 cluster_table );

	QCOW_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( cluster_table != NULL )
	{
		libqcow_cluster_table_free(
		 &cluster_table,
		 NULL );
	}
	return( 0 );
}

#endif /* defined( __GNUC__ ) && !defined( LIBQCOW_DLL_IMPORT ) */

/* The main program
 */
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
int wmain(
     int argc QCOW_TEST_ATTRIBUTE_UNUSED,
     wchar_t * const argv[] QCOW_TEST_ATTRIBUTE_UNUSED )
#else
int main(
     int argc QCOW_TEST_ATTRIBUTE_UNUSED,
     char * const argv[] QCOW_TEST_ATTRIBUTE_UNUSED )
#endif
{
	QCOW_TEST_UNREFERENCED_PARAMETER( argc )
	QCOW_TEST_UNREFERENCED_PARAMETER( argv )

#if defined( __GNUC__ ) && !defined( LIBQCOW_DLL_IMPORT )

	QCOW_TEST_RUN(
	 "libqcow_cluster_table_initialize",
	 qcow_test_cluster_table_initialize );

	QCOW_TEST_RUN(
	 "libqcow_cluster_table_free",
	 qcow_test_cluster_table_free );

	QCOW_TEST_RUN(
	 "libqcow_cluster_table_get_number_of_references",
	 qcow_test_cluster_table_get_number_of_references );

	QCOW_TEST_RUN(
	 "libqcow_cluster_table_get_reference_by_index",
	 qcow_test_cluster_table_get_reference_by_index );

	QCOW_TEST_RUN(
	 "libqcow_cluster_table_read",
	 qcow_test_cluster_table_read );

#endif /* defined( __GNUC__ ) && !defined( LIBQCOW_DLL_IMPORT ) */

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}

