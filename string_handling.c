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
}

void string_destroy (string_t *this)
{
    this->str = NULL;
}

void assign_s(string_t *this, const string_t *str)
{
    this->str = str->str;
}

void assign_c(string_t *this, const char *s)
{
    this->str = (char *)s;
}
