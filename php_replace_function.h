/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2013 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author:                                                              |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifndef PHP_REPLACE_FUNCTION_H
#define PHP_REPLACE_FUNCTION_H

extern zend_module_entry replace_function_module_entry;
#define phpext_replace_function_ptr &replace_function_module_entry

#define PHP_REPLACE_FUNCTION_VERSION "0.1.0" /* Replace with version number for your extension */

#define append_prefix "replace_"
#define append_prefix_len 8

#ifdef PHP_WIN32
#   define PHP_REPLACE_FUNCTION_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
#   define PHP_REPLACE_FUNCTION_API __attribute__ ((visibility("default")))
#else
#   define PHP_REPLACE_FUNCTION_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

PHP_MINIT_FUNCTION(replace_function);
PHP_MSHUTDOWN_FUNCTION(replace_function);
PHP_RINIT_FUNCTION(replace_function);
PHP_RSHUTDOWN_FUNCTION(replace_function);
PHP_MINFO_FUNCTION(replace_function);

PHP_FUNCTION(replace_function);
PHP_FUNCTION(old_func);

typedef void (*php_func)(INTERNAL_FUNCTION_PARAMETERS);

static void php_override_function(TSRMLS_C);
static void php_override_func(char *name, uint len, php_func handler, php_func *stash TSRMLS_DC);
static int register_new_func(char *func_name, uint nKeyLength, zend_function *func);


PHP_FUNCTION(confirm_replace_function_compiled);    /* For testing, remove later. */

/*
    Declare any global variables you may need between the BEGIN
    and END macros here:

ZEND_BEGIN_MODULE_GLOBALS(replace_function)
    long  global_value;
    char *global_string;
ZEND_END_MODULE_GLOBALS(replace_function)
*/

/* In every utility function you add that needs to use variables
   in php_replace_function_globals, call TSRMLS_FETCH(); after declaring other
   variables used by that function, or better yet, pass in TSRMLS_CC
   after the last function argument and declare your utility function
   with TSRMLS_DC after the last declared argument.  Always refer to
   the globals in your function as REPLACE_FUNCTION_G(variable).  You are
   encouraged to rename these macros something shorter, see
   examples in any other php module directory.
*/

#ifdef ZTS
#define REPLACE_FUNCTION_G(v) TSRMG(replace_function_globals_id, zend_replace_function_globals *, v)
#else
#define REPLACE_FUNCTION_G(v) (replace_function_globals.v)
#endif

#endif  /* PHP_REPLACE_FUNCTION_H */


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
