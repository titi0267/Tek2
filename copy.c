/*
** EPITECH PROJECT, 2022
** B-PDG-300-STG-3-1-PDGD05-timothe.coniel
** File description:
** copy
*/

#include "string.h"

size_t copy(const string_t *this, char *s, size_t n, size_t pos)
{
    int j = 0;

    if (this == NULL || this->str == NULL || n + pos >= strlen(this->str)) {
        return (0);
    }
    for (int i = 0; i < n; i++) {
        if (pos + i < (size_t)length(this)) {
            s[i] = this->str[pos + i];
            j++;
        }
    }
    return ((size_t)j);
}
