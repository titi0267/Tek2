/*
** EPITECH PROJECT, 2022
** teams
** File description:
** command_main
*/

#include "../../include/teams.h"
#include "../../../include/communication.h"

void error(teams_t *server, client_list_t *client)
{
    UNUSED(client);
    UNUSED(server);
    printf("ERROR\n");
}

void choose_command(teams_t *server, client_list_t *client)
{
    void (*command[8])(teams_t *server, client_list_t *) =
    {error, login, error, users, user, send_message, messages, subscribe};

    if (client->buff->command > 8)
        return;
    (command[client->buff->command])(server, client);
}

