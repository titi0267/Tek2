/*
** EPITECH PROJECT, 2022
** B-PSU-400-STG-4-1-nmobjdump-timothe.coniel
** File description:
** format_string
*/

#include "../include/nm.h"

int format_str_bis(node_t list, int i, int z)
{
    if (list->sym[i] != '_') {
        list->sym_clear[z] = list->sym[i];
        if (list->sym_clear[z] >= 65 && list->sym_clear[z] <= 90)
            list->sym_clear[z] += 32;
        z++;
    }
    return (z);
}

void format_str(node_t list)
{
    int i = 0;
    int z = 0;

    for (; list != NULL; list = list->next) {
        list->sym_clear = malloc(sizeof(char) * strlen(list->sym) + 2);
        for (z = 0, i = 0; list->sym[i] != '\0'; i++) {
            z = format_str_bis(list, i, z);
        }
        list->sym_clear[z] = '\0';
    }
}
