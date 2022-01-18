/*
** EPITECH PROJECT, 2022
** B-PDG-300-STG-3-1-PDGD05-timothe.coniel
** File description:
** string_handle
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "string.h"

void string_init(string_t *this, const char *s)
{
    this->str = (char *)s;
    this->assign_c = &assign_c;
    this->append_c = &append_c;
}

void string_destroy (string_t *this)
{
    this->str = NULL;
    free(this->str);
}

void assign_s(string_t *this, const string_t *str)
{
    this->str = str->str;
}

void assign_c(string_t *this, const char *s)
{
    this->str = (char *)s;
}

void append_s(string_t *this, const string_t *ap)
{
    //strcat(this->str, ap->str);
}

void append_c(string_t *this, const char *ap)
{
    char *res = this->str;

    this->str = malloc(sizeof(char) * (strlen(this->str) + strlen(ap) + 1));
    strcat(strcpy(this->str,res), ap);
}

/*int main ( void )
{
string_t s;
string_init(&s, "Hello World") ;
printf ("%s\n", s . str ) ;
string_destroy (& s ) ;
return (0) ;
}*/
/*
int main (void)
{
string_t s ;
string_init(&s, "") ;
s.str = "Hello";
printf("%s\n", s.str);
s.append_c(&s, " World");
//s.assign_c(&s, "Hello World");
printf ("%s\n", s.str) ;
string_destroy(&s) ;
return (0) ;
}*/