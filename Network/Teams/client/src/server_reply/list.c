/*
** EPITECH PROJECT, 2022
** teams
** File description:
** list
*/

#include "../../include/teams.h"
#include "../../include/reply.h"
#include "../../include/command.h"

void print_channels(server_create_info_t list)
{
    if (list.error == TEAM_ERROR) {
        client_error_unknown_team(list.team_uuid);
        return;
    }
    client_team_print_channels(list.channel_uuid, list.name, list.description);
}

void print_threads(server_create_info_t list)
{
    if (list.error == TEAM_ERROR) {
        client_error_unknown_team(list.team_uuid);
        return;
    }
    if (list.error == CHANNEL_ERROR) {
        client_error_unknown_channel(list.channel_uuid);
        return;
    }
    client_channel_print_threads(list.thread_uid, list.creator_uuid,
        list.time, list.name, list.description);
}

void print_replies(server_create_info_t list)
{
    if (list.error == TEAM_ERROR) {
        client_error_unknown_team(list.team_uuid);
        return;
    }
    if (list.error == CHANNEL_ERROR) {
        client_error_unknown_channel(list.channel_uuid);
        return;
    }
    if (list.error == THREAD_ERROR) {
        client_error_unknown_thread(list.thread_uid);
        return;
    }
    client_thread_print_replies(list.thread_uid, list.creator_uuid,
        list.time, list.comment_body);
}

static void select_use(client_t *client, server_create_info_t list)
{
    while (1) {
        read(client->socket_fd, &list, sizeof(server_create_info_t));
        if (list.error == LAST)
            break;
        switch (list.create_type)
        {
        case DEFAULT:
            client_print_teams(list.team_uuid, list.name, list.description);
            break;
        case TEAMS:
            print_channels(list);
            break;
        case CHANNEL:
            print_threads(list);
            break;
        case THREADS:
            print_replies(list);
        }
    }
}

void r_list(client_t *client)
{
    server_create_info_t list;

    select_use(client, list);
}