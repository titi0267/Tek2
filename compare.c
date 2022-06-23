/*
** EPITECH PROJECT, 2022
** B-PDG-300-STG-3-1-PDGD05-timothe.coniel
** File description:
** compare
*/

#include "string.h"

int compare_s(const string_t *this, const string_t *str)
{
    return (compare_c(this, str->str));
}

int compare_c(const string_t *this, const char *str)
{
    return (strcmp(this->str, str));
}