/*
** EPITECH PROJECT, 2022
** teams
** File description:
** is_bigger_id
*/

#include <stdlib.h>

int is_bigger_id(char *folder_first, char *folder_second)
{
    char *folder_f = folder_first;
    char *folder_s = folder_second;

    for (; folder_f[0] != '_'; folder_f++);
    folder_f++;
    for (; folder_s[0] != '_'; folder_s++);
    folder_s++;
    return (atoi(folder_f) > atoi(folder_s));
}