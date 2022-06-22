/*
** EPITECH PROJECT, 2022
** $
** File description:
** subscribe_utils
*/

#include "../../include/teams.h"

void send_sub_error(client_list_t *client)
{
    server_sub_t subscribe_res;
    message_t command = {SUBSCRIBE};

    memset(&subscribe_res, 0, sizeof(subscribe_res));
    subscribe_res.exist = 0;
    memset(subscribe_res.team_uid, 0, MAX_NAME_LENGTH);
    memset(subscribe_res.user_uuid, 0, MAX_NAME_LENGTH);
    write(client->fd, &command, sizeof(message_t));
    write(client->fd, &subscribe_res, sizeof(server_sub_t));
}