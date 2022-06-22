/*
** EPITECH PROJECT, 2022
** teams
** File description:
** info_user
*/

#include "../../../include/teams.h"

void info_user(client_list_t *client, cli_create_t payload)
{
    server_create_info_t user = get_create_info_struct();
    message_t message = {INFO};

    UNUSED(payload);
    strcpy(user.name, client->pseudo);
    strcpy(user.creator_uuid, client->uid);
    user.create_type = DEFAULT;
    write(client->fd, &message, sizeof(message_t));
    write(client->fd, &user, sizeof(server_create_info_t));
}