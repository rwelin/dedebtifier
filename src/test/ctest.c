/*
 * ctest
 *
 * ctest.c 
 *
 * Author: Robert Welin <robert dot welin at gmail dot com>
 * Last Change: Thu October 06 2011
 *
 * A library of functions for automated unittesting
 */

#include "ctest.h"

/*
 * Runs a test
 *
 * Parameter 1: The test to run
 * Parameter 2: The name of the module to test
 */
void exec_test(void (*test)(void), char *name)
{
    printf("  - %s\n", name);
    (*test)();
}

/*
 * Runs a test suite
 *
 * Parameter 1: The test suite
 * Parameter 2: The name of the module to be tested
 */
void exec_test_suite(void (*test_suite)(void), char *module)
{
    printf(":: Running test suite for %s\n", module);
    (*test_suite)();
    printf("%s: All tests passed.\n", module);
}

