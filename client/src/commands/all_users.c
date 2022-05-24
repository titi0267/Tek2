/*
** EPITECH PROJECT, 2022
** teams
** File description:
** users
*/

#include "../../include/command.h"

int c_users(char *buff)
{
    if (buff[0] != '\n')
        return (CMD_ERROR);
    printf("users\n");
    return (USERS);
}