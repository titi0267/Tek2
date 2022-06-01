/*
** EPITECH PROJECT, 2022
** teams
** File description:
** create_thread
*/

#include "../../../include/teams.h"

void ret_thread_error(client_list_t *client)
{
    server_thread_info_t thread_info;

    memset(&thread_info, 0, sizeof(thread_info));
    memset(thread_info.name, 0, MAX_NAME_LENGTH);
    memset(thread_info.team_uuid, 0, MAX_NAME_LENGTH);
    memset(thread_info.description, 0, MAX_DESCRIPTION_LENGTH);
    memset(thread_info.channel_uuid, 0, MAX_NAME_LENGTH);
    memset(thread_info.thread_uid, 0, MAX_NAME_LENGTH);
    thread_info.is_valid = 0;
    write(client->fd, &thread_info, sizeof(server_thread_info_t));
}

server_thread_info_t create_thread_info(cli_create_t payload, char *id)
{
    server_thread_info_t thread_info;

    memset(&thread_info, 0, sizeof(thread_info));
    memset(thread_info.name, 0, MAX_NAME_LENGTH);
    memset(thread_info.team_uuid, 0, MAX_NAME_LENGTH);
    memset(thread_info.description, 0, MAX_DESCRIPTION_LENGTH);
    memset(thread_info.channel_uuid, 0, MAX_NAME_LENGTH);
    memset(thread_info.thread_uid, 0, MAX_NAME_LENGTH);
    thread_info.is_valid = 1;
    strcpy(thread_info.name, payload.name);
    strcpy(thread_info.team_uuid, payload.team_uuid);
    strcpy(thread_info.description, payload.description);
    strcpy(thread_info.channel_uuid,payload.channel_uuid);
    strcpy(thread_info.thread_uid, id);
    return (thread_info);
}

void create_first_thread(client_list_t *client, cli_create_t payload)
{
    int fd = 0;
    server_thread_info_t thread_info;
    char *path = malloc(100);

    sprintf(path, "./saves/teams/t_%d/c_%d/th_1",
    atoi(payload.team_uuid), atoi(payload.channel_uuid));
    mkdir(path, 0777);
    sprintf(path, "./saves/teams/t_%d/c_%d/th_1/thread_info.txt",
    atoi(payload.team_uuid), atoi(payload.channel_uuid));
    fd = open(path, O_RDWR | O_CREAT, 0777);
    if (fd == -1)
        return;
    thread_info = create_thread_info(payload, "1");
    write(fd, &thread_info, sizeof(server_thread_info_t));
    write(client->fd, &thread_info, sizeof(server_thread_info_t));
    server_event_team_created(thread_info.team_uuid,
    thread_info.name, client->uid);
    server_event_thread_created(thread_info.channel_uuid,
    thread_info.team_uuid, client->uid,
    thread_info.name, thread_info.description);
}

void create_next_thread(client_list_t *client,
cli_create_t payload, char *last_id)
{
    char *path = malloc(100);
    server_thread_info_t thread_info;
    int fd = 0;

    sprintf(path, "./saves/teams/t_%d/c_%d/th_%d", atoi(payload.team_uuid)
    , atoi(payload.channel_uuid), atoi(last_id) + 1);
    mkdir(path, 0777);
    sprintf(path, "./saves/teams/t_%d/c_%d/th_%d/thread_info.txt"
    , atoi(payload.team_uuid), atoi(payload.channel_uuid), atoi(last_id) + 1);
    fd = open(path, O_RDWR | O_CREAT, 0777);
    if (fd == -1)
        return;
    thread_info = create_thread_info(payload, increment_str(atoi(last_id)));
    write(fd, &thread_info, sizeof(server_thread_info_t));
    write(client->fd, &thread_info, sizeof(server_thread_info_t));
    server_event_thread_created(thread_info.channel_uuid,
    thread_info.team_uuid, client->uid,
    thread_info.name, thread_info.description);
}

void create_thread(client_list_t *client, cli_create_t payload)
{
    struct dirent *ep;
    DIR *dir;
    char *path = malloc(MAX_NAME_LENGTH);
    char *buff = "";

    sprintf(path, "./saves/teams/t_%d/c_%d",
    atoi(payload.team_uuid), atoi(payload.channel_uuid));
    dir = opendir(path);
    if (!dir)
        return (ret_thread_error(client));
    while ((ep = readdir(dir))) {
        if (strncmp(ep->d_name, "th_", 3) == 0)
            buff = ep->d_name;
    }
    if (strlen(buff) == 0)
        return (create_first_thread(client, payload));
    buff += 2;
    create_next_thread(client, payload, buff);
}