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
int bind_server(main_t *_main, int server_port);
int server_loop(main_t *_main, node_t *client);

void client_part(main_t *_main, node_t *list, fd_set fd_to_read);

int new_fd_in_list(node_t *front, int connection);
int new_fd_in_list_back(node_t *front_ptr, int new_client, main_t *_main);
int delete_fd(node_t *front_ptr, int connection);

void parse_user(char *buf, node_t client, main_t *_main);
void parse_pass(char *buf, node_t client, main_t *_main);
void parse_noop(char *buf, node_t client, main_t *_main);
void parse_quit(char *buf, node_t client, main_t *_main);
void parse_help(char *buf, node_t client, main_t *_main);
void parse_path(char *buf, node_t client, main_t *_main);
void parse_cdup(char *buf, node_t client, main_t *_main);
void parse_cwd(char *buf, node_t client, main_t *_main);
void parse_dele(char *buf, node_t client, main_t *_main);
void parse_pasv(char *buf, node_t client, main_t *_main);
void parse_port(char *buf, node_t client, main_t *_main);
void parse_retr(char *buf, node_t client, main_t *_main);
void parse_stor(char *buf, node_t client, main_t *_main);
void parse_list(char *buf, node_t client, main_t *_main);