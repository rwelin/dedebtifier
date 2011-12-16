/*
 * Dedebtifier
 *
 * debts.h
 *
 * Author: Robert Welin <robert dot welin at gmail dot com> 
 * Last Change: Fri December 16 2011
 *
 */

#ifndef DEBTS_H_
#define DEBTS_H_

#define _GNU_SOURCE

#include "unittest.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include "debt_errors.h"
#include "utilities.h"

#define NAME_SIZE 64

typedef struct Debt Debt;
typedef struct Person Person;

struct Debt {
    Person *person;
    float amount;
};

struct Person {
    char name[NAME_SIZE];
    Debt *debts;
    int number_of_debts;
};

typedef struct {
    Person *persons;
    int length;
} Debts;

typedef float** Triangle;

/* Protoypes */
Debts new_debts(void);
Triangle new_triangle(void);
void  delete_triangle(Triangle*);
Person new_person(const char* const, Debt* const, const int);
void  delete_debts(Person*);
Debt  new_debt(Person* const, const float);
int   in_debt(const Person* const, const char* const);
Debt* get_debt(const Person* const, const char* const);
Person* get_person(const Debts* const, const char*);
char** get_names(const Debts);
void  add_person(Debts*, const Person);
void  add_debt(Person* const, const Debt* const);
Debts merge_debts(const Debts* const, const Debts* const);
void  remove_debt(Person*, const char*);
Debts read_names(const char*);
Debts read_debts(const char*);
float get_person_net_debt(const Debts* const, const char*);
void  get_net_debts(const Debts* const, float* const);
void  clean_debts(Debts*);
void  simplify_mutual_debts(Debts* const);
void  simplify_debts(Debts* const);
Triangle find_triangle_with(Person* const);
Triangle find_triangle(Debts* const);
void  simplify_triangle(Triangle);
void  debts_to_string(const Debts* const, char* const);
void  write_debts(const Debts* const, const char* const);
char* pretty_print_debts(Debts);
void  print_debts(const Debts* const);

/* Testing Prototypes */
#if _UNITTEST_
void test_new_debts(void);
void test_new_triangle(void);
void test_delete_triangle(void);
void test_new_person(void);
void test_delete_debts(void);
void test_new_debt(void);
void test_in_debt(void);
void test_get_debt(void);
void test_get_person(void);
void test_get_names(void);
void test_merge_debts(void);
void test_read_names(void);
void test_read_debts(void);
void test_get_person_net_debt(void);
void test_get_net_debts(void);
void test_clean_debts(void);
void test_simplify_mutual_debts(void);
void test_simplify_debts(void);
void test_find_triangle_with(void);
void test_find_triangle(void);
void test_simplify_triangle(void);
void test_debts_to_string(void);
void test_pretty_print_debts(void);
void test_write_debts(void);
void test_add_person(void);
void test_add_debt(void);
void test_remove_debt(void);
#endif

#endif
