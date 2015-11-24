dnl $Id$
dnl config.m4 for extension replace_function

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

dnl PHP_ARG_WITH(replace_function, for replace_function support,
dnl Make sure that the comment is aligned:
dnl [  --with-replace_function             Include replace_function support])

dnl Otherwise use enable:

dnl PHP_ARG_ENABLE(replace_function, whether to enable replace_function support,
dnl Make sure that the comment is aligned:
dnl [  --enable-replace_function           Enable replace_function support])

if test "$PHP_REPLACE_FUNCTION" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-replace_function -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/replace_function.h"  # you most likely want to change this
  dnl if test -r $PHP_REPLACE_FUNCTION/$SEARCH_FOR; then # path given as parameter
  dnl   REPLACE_FUNCTION_DIR=$PHP_REPLACE_FUNCTION
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for replace_function files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       REPLACE_FUNCTION_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$REPLACE_FUNCTION_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the replace_function distribution])
  dnl fi

  dnl # --with-replace_function -> add include path
  dnl PHP_ADD_INCLUDE($REPLACE_FUNCTION_DIR/include)

  dnl # --with-replace_function -> check for lib and symbol presence
  dnl LIBNAME=replace_function # you may want to change this
  dnl LIBSYMBOL=replace_function # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $REPLACE_FUNCTION_DIR/lib, REPLACE_FUNCTION_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_REPLACE_FUNCTIONLIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong replace_function lib version or lib not found])
  dnl ],[
  dnl   -L$REPLACE_FUNCTION_DIR/lib -lm
  dnl ])
  dnl
  dnl PHP_SUBST(REPLACE_FUNCTION_SHARED_LIBADD)

  PHP_NEW_EXTENSION(replace_function, replace_function.c, $ext_shared)
fi
