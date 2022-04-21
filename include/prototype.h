/*
** EPITECH PROJECT, 2022
** ftp
** File description:
** protoype
*/

#pragma once

#include "main_struct.h"
#include "ftp.h"

int parse_args(int ac, char **av);

int init_server(main_t *_main);
int server_loop(main_t *_main, node_t *client);

void client_part(main_t *_main, node_t *list, fd_set fd_to_read);

int new_fd_in_list(node_t *front, int connection);
int new_fd_in_list_back(node_t *front_ptr, int new_client);

void parse_user(char *buf, node_t client);
void parse_pass(char *buf, node_t client);
