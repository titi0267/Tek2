/*
** EPITECH PROJECT, 2022
** teams
** File description:
** login
*/

#include "../../include/teams.h"
#include "../../../include/communication.h"

void login(client_list_t *client)
{
    cli_login_t login;

    read(client->fd, &login, sizeof(cli_login_t));
    client->pseudo = login.name;
}