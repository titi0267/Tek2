/*
** EPITECH PROJECT, 2022
** B-PDG-300-STG-3-1-PDGD05-timothe.coniel
** File description:
** copy
*/

#include "string.h"

size_t copy(const string_t *this, char *s, size_t n, size_t pos)
{
    if (this == NULL || this->str == NULL || n + pos >= strlen(this->str)) {
        return (0);
    }
    for (int i = 0; i < n; i++) {
        s[i] = this->str[pos + i];
    }
    return (n);
}
