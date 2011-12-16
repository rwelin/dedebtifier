/*
 * ctest
 *
 * ctest.h
 *
 * Author: Robert Welin <robert dot welin at gmail dot com>
 * Last Change: Thu October 06 2011
 *
 * A library of functions for automated unittesting
 */

#ifndef CTEST_H_
#define CTEST_H_

#include <stdio.h>

/* Prototypes */
void exec_test(void (*)(void),char*);
void exec_test_suite(void (*)(void),char*);

#endif
