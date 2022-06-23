/*
** EPITECH PROJECT, 2022
** B-PDG-300-STG-3-1-PDGD05-timothe.coniel
** File description:
** find
*/

#include "string.h"

int find_c(const string_t * this, const char * str, size_t pos)
{
    int j = 0;

    if (this == NULL || this->str == NULL || pos >= strlen(this->str)
        || str == NULL)
        return (-1);
    for (int i = pos; i <= strlen(this->str); i++) {
        for (j = 0; str[j] == this->str[i+j]; j++);
        if (j >= strlen(str))
            return (i);
    }
    return (-1);
}

int find_s(const string_t * this, const string_t * str, size_t pos)
{
    find_c(this, str->str, pos);
}