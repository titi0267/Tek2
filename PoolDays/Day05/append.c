/*
** EPITECH PROJECT, 2022
** B-PDG-300-STG-3-1-PDGD05-timothe.coniel
** File description:
** append_c
*/

#include "string.h"
#include <stdlib.h>

void append_s(string_t *this, const string_t *ap)
{
    append_c(this, ap->str);

}

void append_c(string_t *this, const char *ap)
{
    char *tmp = NULL;

    tmp = malloc(sizeof(char) * (strlen(this->str) + strlen(ap) + 1));
    if (tmp == NULL)
        return;
    strcpy(tmp, this->str);
    strcat(tmp, ap);
    assign_c(this, tmp);
    free(tmp);
}
