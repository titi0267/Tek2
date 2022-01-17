/*
** EPITECH PROJECT, 2022
** B-PDG-300-STG-3-1-PDGD04am-timothe.coniel
** File description:
** print
*/
#include <stdio.h>
#include "print.h"
#include <string.h>

void print_normal(const char *str)
{
    printf("%s\n", str);
}

void print_reverse(const char *str)
{
    for (int i = strlen(str); i >= 0; i--) {
        printf("%c", str[i]);
    }
    printf("\n");
}

void print_upper(const char *str)
{
    for (int i = 0; i <= (int)strlen(str); i++) {
        if (str[i] >= 97 && str[i] <= 122) 
            printf("%c", str[i] - 32);
        else
            printf("%c", str[i]);
    }
    printf("\n");
}

void print_42(const char *str)
{
    str = "42";
    print_normal(str);
}

void do_action(action_t action, const char *str )
{
    void (*functionName[4]) (const char *) = {print_normal, print_reverse, print_upper, print_42};

    (*functionName[action]) (str);
}

int main ( void )
{
const char * str = "So long , and thanks for all the fish .";
do_action ( PRINT_NORMAL , str ) ;
do_action ( PRINT_REVERSE , str ) ;
do_action ( PRINT_UPPER , str ) ;
do_action ( PRINT_42 , str ) ;
return (0) ;
}