/*
** EPITECH PROJECT, 2022
** teams
** File description:
** list
*/

#include "../../include/teams.h"
#include "../../include/command.h"

int c_list(char *buff, client_t *client)
{
    if (buff[0] != '\n')
        return (CMD_ERROR);
    printf("list\n");
    return (LIST);
}