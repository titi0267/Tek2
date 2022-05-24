/*
** EPITECH PROJECT, 2022
** teams
** File description:
** users
*/

#include "../../include/teams.h"
#include "../../include/command.h"

int c_users(char *buff, client_t *client)
{
    if (buff[0] != '\n')
        return (CMD_ERROR);
    printf("users\n");
    return (USERS);
}