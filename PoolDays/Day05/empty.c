/*
** EPITECH PROJECT, 2022
** B-PDG-300-STG-3-1-PDGD05-timothe.coniel
** File description:
** empty
*/

#include "string.h"

int empty(const string_t *this)
{
    if (this == NULL || this->str == NULL || strlen(this->str) == 0)
        return (1);
    else
        return (0);
}