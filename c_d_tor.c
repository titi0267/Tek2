/*
** EPITECH PROJECT, 2022
** B-PDG-300-STG-3-1-PDGD05-timothe.coniel
** File description:
** string_handle
*/

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "string.h"

void string_init(string_t *this, const char *s)
{
    this->str = strdup(s);
    this->assign_c = &assign_c;
    this->append_c = &append_c;
    this->append_s = &append_s;
    this->assign_s = &assign_s;
}

void string_destroy(string_t *this)
{
    if (this != NULL && this->str != NULL)
        free(this->str);
}
