/*
** EPITECH PROJECT, 2022
** B-PDG-300-STG-3-1-PDGD05-timothe.coniel
** File description:
** insert
*/

#include "string.h"


void insert_s(string_t *this, size_t pos, const string_t *str)
{
    insert_c(this, pos, str->str);
}

void insert_c(string_t * this, size_t pos, const char *str)
{
    char *tmp = malloc(sizeof(char) * (strlen(this->str) + strlen(str) + 1));

    if (tmp == NULL)
        return;
    if ((int)pos < 0) {
        free(tmp);
        return;
    }
    if (pos >= strlen(this->str)) {
        free(tmp);
        this->append_c(this, str);
        return;
    }
    strncpy(tmp, this->str, pos);
    tmp[pos] = '\0';
    strcat(tmp, str);
    strcat(tmp, this->str + pos);
    assign_c(this, tmp);
    free(tmp);
}