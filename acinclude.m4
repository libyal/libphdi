dnl Function to detect if libphdi dependencies are available
AC_DEFUN([AX_LIBPHDI_CHECK_LOCAL],
 [dnl Check for internationalization functions in libphdi/libphdi_i18n.c 
 AC_CHECK_FUNCS([bindtextdomain])
 ])

