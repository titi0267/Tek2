/*
** EPITECH PROJECT, 2022
** teams
** File description:
** create
*/

#include "../../include/teams.h"
#include "../../include/reply.h"
#include "../../include/command.h"

void default_print(server_create_info_t create, client_t *client)
{
    if (create.is_valid == 0) {
        client_error_already_exist();
        return;
    }
    client_event_team_created(create.team_uuid,
        create.name, create.description);
    if (create.id == client->user_uuid)
        client_print_team_created(create.team_uuid,
            create.name, create.description);
}

void team_print(server_create_info_t create, client_t *client)
{
    if (create.is_valid == 0) {
        client_error_already_exist();
        return;
    }
    client_event_channel_created(create.channel_uuid,
        create.name, create.description);
    if (create.id == client->user_uuid)
        client_print_channel_created(create.channel_uuid,
            create.name, create.description);
}

void channel_print(server_create_info_t create, client_t *client)
{
    if (create.is_valid == 0) {
        client_error_already_exist();
        return;
    }
    //client_event_thread_created()
    if (create.id == client->user_uuid)
        ;
    //client_print_thread_created(create.thread_uid, create.); //only user who created the thread
}

void thread_print(server_create_info_t create, client_t *client)
{
    if (create.is_valid == 0) {
        client_error_unknown_thread(create.thread_uid);
        return;
    }
    //client_event_thread_reply_received(create.team_uuid, create.thread_uid, create., create.)
    if (create.id == client->user_uuid)
        ;
        //client_print_reply_created(create.thread_uid, create.)
}

void r_create(client_t *client)
{
    server_create_info_t create;

    read(client->socket_fd, &create, sizeof(server_create_info_t));
    switch (create.create_type) {
        case DEFAULT:
            default_print(create, client);
            break;
        case TEAMS:
            team_print(create, client);
            break;
        case CHANNEL:
            channel_print(create, client);
            break;
        case THREADS:
            thread_print(create, client);
            break;
    }
}