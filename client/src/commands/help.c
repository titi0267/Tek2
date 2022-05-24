/*
** EPITECH PROJECT, 2022
** teams
** File description:
** help
*/

#include "../../include/command.h"

int c_help(char *buff)
{
    if (buff[0] != '\n')
        return (CMD_ERROR);
    printf("/help\n");
    return (HELP);
}