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
    void (*command[12])(teams_t *server, client_list_t *) =
    {error, login, logout, users, user, send_message, messages, subscribe,
    subscribed_command, unsubscribe, error, create_command};

    if (client->buff->command > 11)
        return;
    (command[client->buff->command])(server, client);
}

