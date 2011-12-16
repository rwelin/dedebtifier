/*
 * dedebitfier_test
 *
 * dedebitfier_test.c
 *
 * Author: Robert Welin <robert dot welin at gmail dot com>
 * Last Change: Fri December 16 2011
 *
 * A program for automatic testing of dedebtifier. When run
 * this program should never fail. If it does dedebtifier is 
 * broken.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define RANDOM rand() % 100
int main(int argc, const char *argv[])
{
    int d0, d1, d2, d3;
    char *names[32] = {"David","Jake","Robert","Sam"};
    char cmd[256];
    for (int i = 0; i < 1000; i++)
    {
        d0 = RANDOM;
        d1 = RANDOM;
        d2 = RANDOM;
        d3 = RANDOM;
        sprintf(cmd, "dedebtifier -f debts -p %s -n David -n Jake -n Robert -n Sam -a p%dp%dp%dp%d", names[rand() % 4], d0, d1, d2, d3);
        system(cmd);
    }
    return 0;
}
