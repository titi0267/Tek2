/*
** EPITECH PROJECT, 2022
** B-PDG-300-STG-3-1-PDGD05-timothe.coniel
** File description:
** length
*/

#include "string.h"

int length(const string_t *this)
{
    if (this == NULL || this->str == NULL)
        return (-1);
    return (strlen(this->str));
}