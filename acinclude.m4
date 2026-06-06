dnl Checks for required headers and functions
dnl
dnl Version: 20260606

dnl Function to detect if libphdi dependencies are available
AC_DEFUN([AX_LIBPHDI_CHECK_LOCAL],
  [AC_PROG_LEX(noyywrap)
  AC_PROG_YACC

  dnl Check for internationalization functions in libphdi/libphdi_i18n.c
  AC_CHECK_FUNCS([bindtextdomain])
])

dnl Function to check if DLL support is needed
AC_DEFUN([AX_LIBPHDI_CHECK_DLL_SUPPORT],
  [AS_IF(
    [test "x$enable_shared" = xyes && test "x$ac_cv_enable_static_executables" = xno],
    [AS_CASE(
      [$host],
      [*cygwin* | *mingw* | *msys*],
      [AC_DEFINE(
        [HAVE_DLLMAIN],
        [1],
        [Define to 1 to enable the DllMain function.])
      AC_SUBST(
        [HAVE_DLLMAIN],
        [1])

      AC_SUBST(
        [LIBPHDI_DLL_EXPORT],
        ["-DLIBPHDI_DLL_EXPORT"])

      AC_SUBST(
        [LIBPHDI_DLL_IMPORT],
        ["-DLIBPHDI_DLL_IMPORT"])
      ])
    ])
  ])

