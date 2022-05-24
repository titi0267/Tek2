/*
** EPITECH PROJECT, 2022
** teams
** File description:
** list
*/

#include "../../include/teams.h"
int c_list(char *buff)
{
    if (buff[0] != '\n')
        return (CMD_ERROR);
    printf("list\n");
    return (LIST);
}