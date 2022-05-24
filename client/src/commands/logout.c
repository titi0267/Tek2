/*
** EPITECH PROJECT, 2022
** teams
** File description:
** logout
*/

#include "../../include/teams.h"
#include "../../include/command.h"

int c_logout(char *buff, client_t *client)
{
    if (buff[0] != '\n')
        return (CMD_ERROR);
    printf("logout\n");
    return (LOGOUT);
}