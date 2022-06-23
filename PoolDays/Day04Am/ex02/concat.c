/*
** EPITECH PROJECT, 2022
** B-PDG-300-STG-3-1-PDGD04am-timothe.coniel
** File description:
** concat
*/
#include <stdio.h>
#include "concat.h"
#include <string.h>
#include <stdlib.h>

void concat_strings(const char *str1, const char *str2, char **res)
{
    (*res) = malloc(sizeof(char) * (strlen(str1) + strlen(str2))+1);
    strcat(strcpy((*res), str1), str2);
}

void concat_struct(concat_t *str)
{
    str->res = malloc(sizeof(char) *
    (strlen(str->str1) + strlen(str->str2)) + 1);
    strcat(strcpy(str->res,str->str1), str->str2);
}
