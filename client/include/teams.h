/*
** EPITECH PROJECT, 2022
** ftp
** File description:
** ftp
*/

#pragma once

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <dirent.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>

#include "../../include/communication.h"
#include "../../libs/myteams/logging_client.h"

#define ERROR 84
#define BUFFER_SIZE 1024
#define UNUSED(x) (void)(x)

enum user_status {
    NOT_LOGGED,
    LOGGED
};

typedef struct client_s {
    int socket_fd;
    int client_fd;
    enum use use_status;
    char pseudo[MAX_NAME_LENGTH];
    char user_uuid[MAX_NAME_LENGTH];
    char team_uuid[MAX_NAME_LENGTH];
    char channel_uuid[MAX_NAME_LENGTH];
    char thread_uuid[MAX_NAME_LENGTH];
    enum user_status log_status;
    fd_set client_rd;
    char tmp_login[MAX_NAME_LENGTH];
    int logout;
} client_t;

client_t *init_struct(char **av);
int parse_cmd(char *buff, client_t *client);
void get_server_recv(client_t *client, message_t msg);
void loop(client_t *client);
void free_all(client_t *client, char *buff);
