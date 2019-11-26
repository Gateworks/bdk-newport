AC_INIT([aapl-BSD], [2.4.0])
AC_PREREQ([2.68])
AC_COPYRIGHT([Copyright (c) 2013-2016 Avago Technologies. All rights reserved.])
AC_CONFIG_SRCDIR([src/aapl_core.c])
AC_CONFIG_AUX_DIR([config])
AM_CONFIG_HEADER([config.h])
AC_CANONICAL_SYSTEM
AM_INIT_AUTOMAKE

# Checks for programs
AC_PROG_CC
AC_PROG_CPP
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET

# Set up libtool
AC_CONFIG_MACRO_DIR(m4)
LT_INIT([dlopen win32-dll])
AC_SUBST([LIBTOOL_DEPS])

# Checks for libraries:

# Checks for header files:
AC_CHECK_HEADERS([fcntl.h inttypes.h netdb.h netinet/in.h stdint.h stdlib.h string.h sys/ioctl.h sys/socket.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics:
AC_TYPE_INT64_T
AC_TYPE_SIZE_T

# Checks for library functions:
AC_CHECK_FUNCS([gethostbyname memmove memset socket strchr strerror strrchr strspn strstr strtol strtoul])

# Building for Windows needs extra libraries.
case ${host_os} in
   mingw32 | cygwin)
      EXTRA_LDFLAGS="-lws2_32 -lm"
      EXTRA_LIBTOOL_ARGS_DLL=-no-undefined
      ;;
   darwin*)
      EXTRA_LDFLAGS="-L/opt/local/lib/ -lm"
      EXTRA_LIBTOOL_ARGS_DLL=
      ;;
   *)
      EXTRA_LDFLAGS=-lm
      EXTRA_LIBTOOL_ARGS_DLL=
      ;;
esac

AC_SUBST(EXTRA_LDFLAGS)
AC_SUBST(EXTRA_LIBTOOL_ARGS_DLL)

# Specify which files to create:
AC_CONFIG_FILES(
   [Makefile]
   [src/Makefile]
)

dnl Specify which links to create:
dnl AC_CONFIG_LINKS(
dnl    [DEST:SRC]
dnl )

# Create the files and links:
AC_OUTPUT
