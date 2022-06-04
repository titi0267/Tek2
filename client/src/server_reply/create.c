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
    if (create.error == TEAM_NAME_ALREADY_TAKEN) {
        client_error_already_exist();
        return;
    }
    client_event_team_created(create.team_uuid,
        create.name, create.description);
    if (strcmp(create.creator_uuid, client->user_uuid) == 0)
        client_print_team_created(create.team_uuid,
            create.name, create.description);
}

void team_print(server_create_info_t create, client_t *client)
{
    if (create.error == TEAM_ERROR) {
        client_error_unknown_team(create.team_uuid);
        return;
    }
    if (create.error == CHANNEL_NAME_ALREADY_TAKEN) {
        client_error_already_exist();
        return;
    }
    if (create.error == UNAUTHORIZED) {
        client_error_unauthorized();
        return;
    }
    client_event_channel_created(create.channel_uuid,
        create.name, create.description);
    if (strcmp(create.creator_uuid, client->user_uuid) == 0)
        client_print_channel_created(create.channel_uuid,
            create.name, create.description);
}

void channel_print(server_create_info_t create, client_t *client)
{
    switch (create.error) {
        case TEAM_ERROR:
            client_error_unknown_team(create.team_uuid);
            break;
        case CHANNEL_ERROR:
            client_error_unknown_channel(create.channel_uuid);
            break;
        case THREAD_NAME_ALREADY_TAKEN:
            client_error_already_exist();
            break;
        case UNAUTHORIZED:
            client_error_unauthorized();
            break;
        default:
            client_event_thread_created(create.thread_uid, create.creator_uuid,
                create.time, create.name, create.description);
            if (strcmp(create.creator_uuid, client->user_uuid) == 0)
                client_print_thread_created(create.thread_uid,
                create.creator_uuid, create.time, create.name,
                create.description);
            break;
    }
}

void thread_print(server_create_info_t create, client_t *client)
{
        switch (create.error) {
        case TEAM_ERROR:
            client_error_unknown_team(create.team_uuid);
            break;
        case CHANNEL_ERROR:
            client_error_unknown_channel(create.channel_uuid);
            break;
        case THREAD_ERROR:
        client_error_unknown_thread(create.thread_uid);
            break;
        case UNAUTHORIZED:
            client_error_unauthorized();
            break;
        default:
            client_event_thread_reply_received(create.team_uuid,
                create.thread_uid, create.creator_uuid, create.comment_body);
            if (strcmp(create.creator_uuid, client->user_uuid) == 0)
                client_print_reply_created(create.thread_uid,
                    create.creator_uuid, create.time, create.comment_body);
            break;
        }
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