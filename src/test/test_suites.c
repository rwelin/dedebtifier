/*
 * Dedebtifier
 *
 * test_suites.c
 *
 * Author: Robert Welin <robert dot welin at gmail dot com>
 * Last Change: Fri December 16 2011
 *
 */

#include "test_suites.h"

/*
 * Test suite for debts.c
 */
void test_suite_debts(void)
{
#if _UNITTEST_
    printf("WIBBLE\n");
    exec_test(&test_new_debts, "new_debts");
    exec_test(&test_new_triangle, "new_triangle");
    exec_test(&test_delete_triangle, "delete_triangle");
    exec_test(&test_new_debt, "new_debt");
    exec_test(&test_new_person, "new_person");
    exec_test(&test_in_debt, "in_debt");
    exec_test(&test_add_debt, "add_debt");
    exec_test(&test_delete_debts, "delete_debts");
    exec_test(&test_add_person, "add_person");
    exec_test(&test_get_debt, "get_debt");
    exec_test(&test_get_person, "get_person");
    exec_test(&test_get_names, "get_names");
    exec_test(&test_read_names, "read_names");
    exec_test(&test_read_debts, "read_debts");
    exec_test(&test_remove_debt, "remove_debt");
    exec_test(&test_debts_to_string, "debts_to_string");
    exec_test(&test_merge_debts, "merge_debts");
    exec_test(&test_write_debts, "write_debts");
    exec_test(&test_get_person_net_debt, "get_person_net_debt");
    exec_test(&test_get_net_debts, "get_net_debts");
    exec_test(&test_find_triangle_with, "find_triangle_with");
    exec_test(&test_find_triangle, "find_triangle");
    exec_test(&test_clean_debts, "clean_debts");
    exec_test(&test_simplify_triangle, "simplify_triangle");
    exec_test(&test_simplify_mutual_debts, "simplify_mutual_debts");
    exec_test(&test_simplify_debts, "simplify_debts");
    exec_test(&test_pretty_print_debts, "pretty_print_debts");
#endif
}

void test_suite_utilities(void)
{
#if _UNITTEST_
    exec_test(&test_length, "length");
#endif
}

void test_suite_cui(void)
{
#if _UNITTEST_
    exec_test(&test_parse_amounts, "parse_amounts");
    exec_test(&test_parse_debts_string, "parse_debts_string");
    exec_test(&test_parse_options, "parse_options");
#endif
}

void exec_tests(void)
{
#if _UNITTEST_
    exec_test_suite(&test_suite_utilities, "utilities.c");
    exec_test_suite(&test_suite_debts, "debts.c");
    exec_test_suite(&test_suite_cui, "cui.c");
#endif
}
