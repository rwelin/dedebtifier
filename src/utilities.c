/*
 * utilities.c
 *
 * A few useful functions
 *
 * Author: Robert Welin <robert dot welin at gmail dot com>
 * Last Change: Thu October 06 2011
 *
 */

#include "utilities.h"

/*
 * Calculates the length of a string
 *
 * Parameter 1: A string
 *
 * Returns: The lenght of the string
 */
int length(char *str)
{
    if (str[0] == '\0')
    {
        return 0;
    }
    else
    {
        return 1 + length(str+sizeof(char));
    }
}

/*
 * Test for length
 */
void test_length(void)
{
    char *str = "Hello, world!\n";
    assert(length(str) == 14);
}
