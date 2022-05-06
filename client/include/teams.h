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

typedef struct client_s {
    int socket_fd;
} client_t;

client_t *init_struct(char **av);
