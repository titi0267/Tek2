/*
** EPITECH PROJECT, 2022
** teams
** File description:
** create
*/

#include "../../../include/teams.h"

void create_command(teams_t *server, client_list_t *client)
{
    cli_create_t client_payload;

    read(client->fd, &client_payload, sizeof(cli_create_t));
    switch (client_payload.args_nbr) {
        case DEFAUL
    }
}