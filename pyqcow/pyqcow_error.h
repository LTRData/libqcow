/*
 * Error functions
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

#if !defined( _PYQCOW_ERROR_H )
#define _PYQCOW_ERROR_H

#include <common.h>
#include <types.h>

#include "pyqcow_libcerror.h"
#include "pyqcow_python.h"

#define PYQCOW_ERROR_STRING_SIZE	2048

#if defined( __cplusplus )
extern "C" {
#endif

void pyqcow_error_fetch(
      libcerror_error_t **error,
      int error_domain,
      int error_code,
      const char *format_string,
      ... );

void pyqcow_error_fetch_and_raise(
      PyObject *exception_object,
      const char *format_string,
      ... );

void pyqcow_error_raise(
      libcerror_error_t *error,
      PyObject *exception_object,
      const char *format_string,
      ... );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _PYQCOW_ERROR_H ) */

