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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_replace_function.h"

/* If you declare any globals in php_replace_function.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(replace_function)
*/

/* True global resources - no need for thread safety here */
static int le_replace_function;

static php_func t_func;

HashTable *stash_func;

/* {{{ replace_function_functions[]
 *
 * Every user visible function must have an entry in replace_function_functions[].
 */
const zend_function_entry replace_function_functions[] = {
    PHP_FE(confirm_replace_function_compiled,   NULL)       /* For testing, remove later. */
    PHP_FE(replace_function, NULL)
    PHP_FE_END  /* Must be the last line in replace_function_functions[] */
};
/* }}} */

/* {{{ replace_function_module_entry
 */
zend_module_entry replace_function_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
    STANDARD_MODULE_HEADER,
#endif
    "replace_function",
    replace_function_functions,
    PHP_MINIT(replace_function),
    PHP_MSHUTDOWN(replace_function),
    PHP_RINIT(replace_function),        /* Replace with NULL if there's nothing to do at request start */
    PHP_RSHUTDOWN(replace_function),    /* Replace with NULL if there's nothing to do at request end */
    PHP_MINFO(replace_function),
#if ZEND_MODULE_API_NO >= 20010901
    PHP_REPLACE_FUNCTION_VERSION,
#endif
    STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_REPLACE_FUNCTION
ZEND_GET_MODULE(replace_function)
#endif

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("replace_function.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_replace_function_globals, replace_function_globals)
    STD_PHP_INI_ENTRY("replace_function.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_replace_function_globals, replace_function_globals)
PHP_INI_END()
*/
/* }}} */

/* {{{ php_replace_function_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_replace_function_init_globals(zend_replace_function_globals *replace_function_globals)
{
    replace_function_globals->global_value = 0;
    replace_function_globals->global_string = NULL;
}
*/
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(replace_function)
{
    /* If you have INI entries, uncomment these lines
    REGISTER_INI_ENTRIES();
    */
    return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(replace_function)
{
    /* uncomment this line if you have INI entries
    UNREGISTER_INI_ENTRIES();
    */
    return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(replace_function)
{
    /*
    ALLOC_HASHTABLE(stash_func);
    zend_hash_init(stash_func, 64, NULL, ZVAL_PTR_DTOR, 0);
    */
    return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(replace_function)
{
    return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(replace_function)
{
    php_info_print_table_start();
    php_info_print_table_header(2, "replace_function support", "enabled");
    php_info_print_table_end();

    /* Remove comments if you have entries in php.ini
    DISPLAY_INI_ENTRIES();
    */
}
/* }}} */


/* Remove the following function when you have successfully modified config.m4
   so that your module can be compiled into PHP, it exists only for testing
   purposes. */

/* Every user-visible function in PHP should document itself in the source */
/* {{{ proto string confirm_replace_function_compiled(string arg)
   Return a string to confirm that the module is compiled in */
PHP_FUNCTION(confirm_replace_function_compiled)
{
    char *arg = NULL;
    int arg_len, len;
    char *strg;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &arg, &arg_len) == FAILURE) {
        return;
    }

    len = spprintf(&strg, 0, "Congratulations! You have successfully modified ext/%.78s/config.m4. Module %.78s is now compiled into PHP.", "replace_function", arg);
    RETURN_STRINGL(strg, len, 0);
}
/* }}} */
/* The previous line is meant for vim and emacs, so it can correctly fold and
   unfold functions in source code. See the corresponding marks just before
   function definition, where the functions purpose is also documented. Please
   follow this convention for the convenience of others editing your code.
*/

PHP_FUNCTION(replace_function)
{
    char *str = NULL;
    char *lcname;

    char *to_f = NULL;
    char *tcname;

    int str_len = 0;
    int to_f_len = 0;

    int ret = 0;
    zend_function *old_func, *new_func;
    zend_bool retval;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ss", &str, &str_len, &to_f, &to_f_len) == FAILURE) {
        RETURN_FALSE;
    }

    lcname = zend_str_tolower_dup(str, str_len);

    tcname = zend_str_tolower_dup(to_f, to_f_len);

    if (zend_hash_find(CG(function_table), lcname, str_len+1, (void **)&old_func)
            == SUCCESS && zend_hash_find(EG(function_table), tcname, to_f_len+1, (void **)&new_func) == SUCCESS) {
        if (old_func->type == ZEND_INTERNAL_FUNCTION) {

            if (new_func->type == ZEND_INTERNAL_FUNCTION) {
                //t_func = old_func->internal_function.handler;
                //add_stash_func(str, str_len, old_func);
                ret = register_new_func(str, str_len, old_func);
                old_func->internal_function = new_func->internal_function;
            } else if(new_func->type == ZEND_USER_FUNCTION) {
                //t_func = old_func->internal_function.handler;
                //add_stash_func(str, str_len, old_func);
                ret = register_new_func(str, str_len, old_func);

                old_func->op_array = new_func->op_array;
                old_func->type = ZEND_USER_FUNCTION;
            }
        } else if(old_func->type == ZEND_USER_FUNCTION) {
            if (new_func->type == ZEND_USER_FUNCTION) {
                old_func->op_array = new_func->op_array;
            } else if(new_func->type == ZEND_INTERNAL_FUNCTION) {
                old_func->internal_function = new_func->internal_function;
                old_func->type = ZEND_INTERNAL_FUNCTION;
            }
        }
        old_func->op_array = new_func->op_array;
        old_func->type = ZEND_USER_FUNCTION;
    }

    if (ret == SUCCESS)
        RETURN_TRUE;
    RETURN_FALSE;
}

static int register_new_func(char *func_name, uint nKeyLength, zend_function *func) {
    char *n_func_name;
    n_func_name = emalloc(64);
    memcpy(n_func_name, append_prefix, append_prefix_len);
    memcpy(n_func_name + append_prefix_len, func_name, nKeyLength);

    zend_function_entry override_functions[] = {
        { n_func_name, func->internal_function.handler, NULL, 0, 0},
        PHP_FE_END  /* Must be the last line in override_echo_functions[] */
    };
    if (zend_register_functions(NULL, override_functions, CG(function_table), MODULE_PERSISTENT TSRMLS_CC) == SUCCESS) {
        return SUCCESS;
    }
    return FAILURE;
}



/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
