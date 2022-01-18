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
    this->append_s = &append_s;
    this->assign_s = &assign_s;
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
    this->str = strcat(strcpy(this->str,res), ap);
}

