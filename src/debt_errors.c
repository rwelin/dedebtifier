/*
 * Dedebtifier
 *
 * debt_errors.c
 *
 * Author: Robert Welin <robert dot welin at gmail dot com>
 * Last Change: Thu October 06 2011
 *
 */

#include "debt_errors.h"

/*
 * If a null pointer is used, this function is called
 */
void null_pointer_exception(void)
{
    printf("Null pointer exception\n");
    exit(1);
}

/*
 * If there is a NoSuchFile error, this function is called
 *
 * Parameter 1: Name of non-existing file
 */
void no_such_file_error(const char *file_name)
{
    printf("No such file: %s\n", file_name);
    exit(1);
}
