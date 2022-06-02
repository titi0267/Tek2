/*
** EPITECH PROJECT, 2022
** teams
** File description:
** create
*/

#include "../../include/teams.h"
#include "../../include/reply.h"
#include "../../include/command.h"

void r_create(client_t *client)
{
    server_create_info_t create;

    read(client->socket_fd, &create, sizeof(server_create_info_t));
    if (create.is_valid == 0) {
        client_error_already_exist();
        return;
    }
    client_event_team_created(create.team_uuid,
        create.name, create.description);
    client_print_team_created(create.team_uuid,
        create.name, create.description);
}