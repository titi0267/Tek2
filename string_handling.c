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
}

void string_destroy (string_t *this)
{
    this->str = NULL;
}