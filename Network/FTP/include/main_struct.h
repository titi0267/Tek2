/*
** EPITECH PROJECT, 2022
** ftp
** File description:
** main_struct
*/

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define ERROR_CODE 84
#define ERROR_PORT "Error: Port must be a number: <%s>\n"
#define TRUE 1
#define FALSE 0

typedef struct main_s {
    int port;
    char *path;
    int server_fd;
    char buf[1024];
    int user_deleted;
    int port_pasv;
} main_t;
