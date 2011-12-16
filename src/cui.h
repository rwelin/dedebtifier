/*
 * Dedebtifier
 *
 * cui.h
 *
 * Author: Robert Welin <robert dot welin at gmail dot com>
 * Last Change: Fri December 16 2011
 *
 */

#ifndef CUI_H_
#define CUI_H_

#define NAME "Dedebtifier"
#define SPLIT_CHARS "£"

#include "unittest.h"
#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include "debts.h"

#define NAMES_MAX 16
#define MAX_ERROR 0.001

typedef struct
{
    bool do_help;
    bool payer_spec;
    char payer[NAME_SIZE];
    int  namesc;
    char names[NAMES_MAX][NAME_SIZE];
    bool accumulate;
    char amount_str[1024];
    bool file_spec;
    char debts_file[NAME_SIZE];
} Options;

/* Prototypes */
void  print_help(void);
Options parse_options(int, const char*[]);
void  parse_amounts(char const*, float*);
Debts parse_debts_string(char const*, const int, char**, char const*);
void  execute(const Options);

/* Testing Prototypes */
#if _UNITTEST_
void test_parse_options(void);
void test_parse_amounts(void);
void test_parse_debts_string(void);
#endif

#endif
