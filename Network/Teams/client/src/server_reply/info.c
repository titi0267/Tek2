/*
** EPITECH PROJECT, 2022
** teams
** File description:
** info
*/

#include "../../include/teams.h"
#include "../../include/reply.h"
#include "../../include/command.h"

static void print_team(server_create_info_t info)
{
    if (info.error == TEAM_ERROR) {
        client_error_unknown_team(info.team_uuid);
        return;
    }
    client_print_team(info.team_uuid, info.name, info.description);
}

static void print_channel(server_create_info_t info)
{
    if (info.error == TEAM_ERROR) {
        client_error_unknown_team(info.team_uuid);
        return;
    }
    if (info.error == CHANNEL_ERROR) {
        client_error_unknown_channel(info.channel_uuid);
        return;
    }
    client_print_channel(info.channel_uuid, info.name, info.description);
}

static void print_thread(server_create_info_t info)
{
    if (info.error == TEAM_ERROR) {
        client_error_unknown_team(info.team_uuid);
        return;
    }
    if (info.error == CHANNEL_ERROR) {
        client_error_unknown_channel(info.channel_uuid);
        return;
    }
    if (info.error == THREAD_ERROR) {
        client_error_unknown_thread(info.thread_uid);
        return;
    }
    client_print_thread(info.thread_uid, info.creator_uuid,
        info.time, info.name, info.description);
}

static void select_use(client_t *client, server_create_info_t info)
{
    read(client->socket_fd, &info, sizeof(server_create_info_t));
    switch (info.create_type)
    {
    case DEFAULT:
        client_print_user(info.creator_uuid, info.name, 1);
        break;
    case TEAMS:
        print_team(info);
        break;
    case CHANNEL:
        print_channel(info);
        break;
    case THREADS:
        print_thread(info);
    }
}

void r_info(client_t *client)
{
    server_create_info_t info;

    select_use(client, info);
}