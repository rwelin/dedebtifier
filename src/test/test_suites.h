/*
 * Dedebtifier
 *
 * test_suites.h
 *
 * Author: Robert Welin <robert dot welin at gmail dot com>
 * Last Change: Fri December 16 2011
 *
 */

#ifndef TEST_SUITES_H_
#define TEST_SUITES_H_

#include "../unittest.h"
#include "ctest.h"
#include "../utilities.h"
#include "../debts.h"
#include "../cui.h"

/* Prototypes */
void test_suite_debts(void);
void test_suite_utilities(void);
void test_suite_cui(void);
void exec_tests(void);

#endif
