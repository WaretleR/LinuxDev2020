AC_INIT([guess], [1.0])
AM_INIT_AUTOMAKE([foreign])
AC_CONFIG_SRCDIR([guess.c])
DX_INIT_DOXYGEN(guess)

AC_PROG_CC
AC_PATH_PROG([HELP2MAN], [help2man])

AC_CHECK_HEADERS([libintl.h locale.h stdlib.h string.h])

AC_CHECK_FUNCS([setlocale])

AC_CONFIG_FILES([Makefile
                Doxyfile])
AC_OUTPUT