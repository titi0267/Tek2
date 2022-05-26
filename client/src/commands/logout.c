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
    if (client->user_uuid[0] != 0)
        client_event_logged_out(client->user_uuid, client->pseudo);
    return (LOGOUT);
}