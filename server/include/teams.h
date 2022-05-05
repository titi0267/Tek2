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

#include "./command.h"

#define ERROR 84
#define MAX_CONNECTIONS 15
#define BUFFER_SIZE 1024
#define UNUSED(x) (void)(x)

enum user_status {
    NOT_LOGGED,
    LOGGED
};

typedef struct client_list_s {
    struct client_list_s *next;
    message_t *message;
    int fd;
} client_list_t;

typedef struct fd_set_s {
    fd_set read;
    fd_set write;
    fd_set exeptions;
} fd_set_t;

typedef struct ftp_s {
    int socket_fd;
    int select_ret;
    client_list_t *head;
    fd_set_t *fds;
} teams_t;

int setup_server(char *port);
void loop(teams_t *teams);
teams_t *init_struct(char *port);
void push_back(teams_t *teams, int fd);
void set_all_fd(teams_t *teams);
void free_list(teams_t *teams);
void free_all(teams_t *teams);
void remove_in_list(teams_t *teams, int fd);