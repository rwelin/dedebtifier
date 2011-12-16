/*
 * Dedebtifier
 *
 * main.c
 *
 * Author: Robert Welin <robert dot welin at gmail dot com>
 * Last Change: Fri December 16 2011
 *
 */ 

#include "main.h"

int main(int argc, const char *argv[])
{
#if _UNITTEST_
    exec_tests();
#else    
    execute(parse_options(argc, argv));
#endif
    return 0;
}
