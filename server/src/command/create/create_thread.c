/*
** EPITECH PROJECT, 2022
** teams
** File description:
** create_thread
*/

#include "../../../include/teams.h"
#include <time.h>

void ret_thread_error(client_list_t *client, cli_create_t payload,
int error_status)
{
    server_create_info_t thread_info;
    message_t message = {CREATE};

    memset(&thread_info, 0, sizeof(thread_info));
    memset(thread_info.name, 0, MAX_NAME_LENGTH);
    memset(thread_info.team_uuid, 0, MAX_NAME_LENGTH);
    memset(thread_info.description, 0, MAX_DESCRIPTION_LENGTH);
    memset(thread_info.channel_uuid, 0, MAX_NAME_LENGTH);
    memset(thread_info.thread_uid, 0, MAX_NAME_LENGTH);
    memset(thread_info.creator_uuid, 0, MAX_NAME_LENGTH);
    thread_info.error = error_status;
    thread_info.create_type = CHANNEL;
    thread_info.time = time(NULL);
    strcpy(thread_info.name, payload.name);
    strcpy(thread_info.team_uuid, payload.team_uuid);
    strcpy(thread_info.description, payload.description);
    strcpy(thread_info.channel_uuid,payload.channel_uuid);
    strcpy(thread_info.creator_uuid, client->uid);
    write(client->fd, &message, sizeof(message_t));
    write(client->fd, &thread_info, sizeof(server_create_info_t));
}

server_create_info_t create_thread_info(client_list_t *client,
cli_create_t payload, char *id)
{
    server_create_info_t thread_info;

    memset(&thread_info, 0, sizeof(thread_info));
    memset(thread_info.name, 0, MAX_NAME_LENGTH);
    memset(thread_info.team_uuid, 0, MAX_NAME_LENGTH);
    memset(thread_info.description, 0, MAX_DESCRIPTION_LENGTH);
    memset(thread_info.channel_uuid, 0, MAX_NAME_LENGTH);
    memset(thread_info.thread_uid, 0, MAX_NAME_LENGTH);
    memset(thread_info.creator_uuid, 0, MAX_NAME_LENGTH);
    thread_info.error = NO_ERROR;
    thread_info.time = time(NULL);
    thread_info.create_type = CHANNEL;
    strcpy(thread_info.name, payload.name);
    strcpy(thread_info.team_uuid, payload.team_uuid);
    strcpy(thread_info.description, payload.description);
    strcpy(thread_info.channel_uuid,payload.channel_uuid);
    strcpy(thread_info.creator_uuid, client->uid);
    strcpy(thread_info.thread_uid, id);
    return (thread_info);
}

void create_first_thread(teams_t *server,
client_list_t *client, cli_create_t payload)
{
    int fd = 0;
    server_create_info_t thread_info;
    char *path = malloc(100);
    sprintf(path, "./saves/teams/t_%d/c_%d/th_1",
    atoi(payload.team_uuid), atoi(payload.channel_uuid));
    mkdir(path, 0777);
    sprintf(path, "./saves/teams/t_%d/c_%d/th_1/thread_info.txt",
    atoi(payload.team_uuid), atoi(payload.channel_uuid));
    fd = open(path, O_RDWR | O_CREAT, 0777);
    if (fd == -1)
        return;
    thread_info = create_thread_info(client, payload, "1");
    write(fd, &thread_info, sizeof(server_create_info_t));
    send_to_team(server, &thread_info, sizeof(server_create_info_t),
    thread_info.team_uuid);
    server_event_team_created(thread_info.team_uuid,
    thread_info.name, client->uid);
    server_event_thread_created(thread_info.channel_uuid,
    thread_info.team_uuid, client->uid,
    thread_info.name, thread_info.description);
}

void create_next_thread(teams_t *server, client_list_t *client,
cli_create_t payload, char *last_id)
{
    char *path = malloc(100);
    server_create_info_t thread_info;
    int fd = 0;

    sprintf(path, "./saves/teams/t_%d/c_%d/th_%d", atoi(payload.team_uuid)
    , atoi(payload.channel_uuid), atoi(last_id) + 1);
    mkdir(path, 0777);
    sprintf(path, "./saves/teams/t_%d/c_%d/th_%d/thread_info.txt"
    , atoi(payload.team_uuid), atoi(payload.channel_uuid), atoi(last_id) + 1);
    fd = open(path, O_RDWR | O_CREAT, 0777);
    if (fd == -1)
        return;
    thread_info = create_thread_info(client,
    payload, increment_str(atoi(last_id)));
    write(fd, &thread_info, sizeof(server_create_info_t));
    send_to_team(server, &thread_info, sizeof(server_create_info_t),
    thread_info.team_uuid);
    server_event_thread_created(thread_info.channel_uuid,
    thread_info.team_uuid, client->uid,
    thread_info.name, thread_info.description);
}

void create_thread(teams_t *server, client_list_t *client,
cli_create_t req)
{
    struct dirent *ep;
    DIR *dir;
    char *path = malloc(MAX_NAME_LENGTH);
    char *buff = "";

    if (!is_subscribed(req.team_uuid, client->uid))
        return (ret_thread_error(client, req, UNAUTHORIZED));
    sprintf(path, "./saves/teams/t_%d/c_%d", atoi(req.team_uuid),
    atoi(req.channel_uuid));
    dir = opendir(path);
    if (!dir)
        return (ret_thread_error(client, req, get_thread_error_level(req)));
    if (thread_name_already_exist(req.team_uuid, req.channel_uuid, req.name))
        return (ret_thread_error(client, req, THREAD_NAME_ALREADY_TAKEN));
    while ((ep = readdir(dir)))
        strncmp(ep->d_name, "th_", 3) == 0 ?  buff = ep->d_name : 0;
    if (strlen(buff++) == 0)
        return (create_first_thread(server, client, req));
    create_next_thread(server, client, req, ++buff);
}