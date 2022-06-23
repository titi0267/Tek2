/*
** EPITECH PROJECT, 2022
** B-PDG-300-STG-3-1-PDGD05-timothe.coniel
** File description:
** assign
*/

#include "string.h"

void assign_c(string_t *this, const char *s)
{
    string_destroy(this);
    this->str = strdup(s);
}

void assign_s(string_t *this, const string_t *str)
{
    assign_c(this, str->str);
}
