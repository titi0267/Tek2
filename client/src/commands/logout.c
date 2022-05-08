/*
** EPITECH PROJECT, 2022
** teams
** File description:
** logout
*/

#include "../../include/command.h"

int c_logout(char *buff)
{
    if (buff[0] != '\n')
        return (CMD_ERROR);
    printf("logout\n");
    return (LOGOUT);
}