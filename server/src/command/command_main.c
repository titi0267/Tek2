/*
** EPITECH PROJECT, 2022
** teams
** File description:
** command_main
*/

#include "../../include/teams.h"
#include "../../../include/communication.h"

void error(client_list_t *client)
{
    UNUSED(client);
    printf("ERROR\n");
}

void choose_command(client_list_t *client)
{
    void (*command[5])(client_list_t *) = {error, login, error, error, user};

    printf("command: %d\n", client->buff->command);
    if (client->buff->command > 13)
        return;
    (command[client->buff->command])(client);
}

