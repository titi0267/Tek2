/*
** EPITECH PROJECT, 2022
** teams
** File description:
** create_reply
*/

#include "../../../include/teams.h"
#include <time.h>

void ret_reply_error(client_list_t *client, cli_create_t payload, int error)
{
    server_create_info_t reply_info;
    message_t message = {CREATE};

    memset(&reply_info, 0, sizeof(reply_info));
    memset(reply_info.name, 0, MAX_NAME_LENGTH);
    memset(reply_info.team_uuid, 0, MAX_NAME_LENGTH);
    memset(reply_info.description, 0, MAX_DESCRIPTION_LENGTH);
    memset(reply_info.channel_uuid, 0, MAX_NAME_LENGTH);
    memset(reply_info.thread_uid, 0, MAX_NAME_LENGTH);
    memset(reply_info.comment_body, 0, MAX_BODY_LENGTH);
    reply_info.error = error;
    reply_info.create_type = THREADS;
    reply_info.time = time(NULL);
    strcpy(reply_info.name, payload.name);
    strcpy(reply_info.team_uuid, payload.team_uuid);
    strcpy(reply_info.description, payload.description);
    strcpy(reply_info.channel_uuid,payload.channel_uuid);
    strcpy(reply_info.thread_uid, payload.thread_uuid);
    strcpy(reply_info.creator_uuid, client->uid);
    strcpy(reply_info.comment_body, payload.comment_body);
    write(client->fd, &message, sizeof(message_t));
    write(client->fd, &reply_info, sizeof(server_create_info_t));
}

server_create_info_t create_reply_info(client_list_t *client,
cli_create_t payload)
{
    server_create_info_t reply_info;

    memset(&reply_info, 0, sizeof(reply_info));
    memset(reply_info.name, 0, MAX_NAME_LENGTH);
    memset(reply_info.team_uuid, 0, MAX_NAME_LENGTH);
    memset(reply_info.description, 0, MAX_DESCRIPTION_LENGTH);
    memset(reply_info.channel_uuid, 0, MAX_NAME_LENGTH);
    memset(reply_info.thread_uid, 0, MAX_NAME_LENGTH);
    memset(reply_info.creator_uuid, 0, MAX_NAME_LENGTH);
    memset(reply_info.comment_body, 0, MAX_BODY_LENGTH);
    reply_info.error = NO_ERROR;
    reply_info.create_type = THREADS;
    reply_info.time = time(NULL);
    strcpy(reply_info.name, payload.name);
    strcpy(reply_info.team_uuid, payload.team_uuid);
    strcpy(reply_info.description, payload.description);
    strcpy(reply_info.channel_uuid,payload.channel_uuid);
    strcpy(reply_info.thread_uid, payload.thread_uuid);
    strcpy(reply_info.creator_uuid, client->uid);
    strcpy(reply_info.comment_body, payload.comment_body);
    return (reply_info);
}

void create_reply(teams_t *server, client_list_t *client, cli_create_t payload)
{
    char *path = malloc(100);
    server_create_info_t reply_info;
    int fd = 0;

    if (!is_subscribed(payload.team_uuid, client->uid))
        return (ret_reply_error(client, payload, UNAUTHORIZED));
    sprintf(path, "./saves/teams/t_%d/c_%d/th_%d/reply.txt",
    atoi(payload.team_uuid), atoi(payload.channel_uuid),
    atoi(payload.thread_uuid));
    fd = open(path, O_CREAT | O_RDWR | O_APPEND, 0777);
    if (fd == -1)
        return (ret_reply_error(client, payload,
        get_reply_error_level(payload)));
    reply_info = create_reply_info(client, payload);
    write(fd, &reply_info, sizeof(server_create_info_t));
    send_to_team(server, &reply_info, sizeof(server_create_info_t),
    reply_info.team_uuid);
    write(client->fd, &reply_info, sizeof(server_create_info_t));
    server_event_reply_created(reply_info.thread_uid, client->uid,
    reply_info.description);
}