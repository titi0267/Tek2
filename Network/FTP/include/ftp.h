/*
** EPITECH PROJECT, 2022
** ftp
** File description:
** main
*/

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/select.h>

#define MAX_CLIENT 10

typedef struct client_s {
    int connection;
    char *path;
    int logged_in;
    int pasv;
    int server_fd;
    int fd_client_pasv;
    int port;
    struct client_s *next;
} client_t;

typedef client_t *node_t;
