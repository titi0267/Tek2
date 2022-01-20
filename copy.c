/*
** EPITECH PROJECT, 2022
** B-PDG-300-STG-3-1-PDGD05-timothe.coniel
** File description:
** copy
*/

#include "string.h"

size_t copy(const string_t *this, char *s, size_t n, size_t pos)
{
    if (n + pos >= strlen(s)) {
        return (0);
    }
    strncpy(s, this->str + pos, n);
    return (n);
}
