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
#include "../../libs/myteams/logging_server.h"

#define ERROR 84
#define MAX_CONNECTIONS 15
#define BUFFER_SIZE 1024
#define UNUSED(x) (void)(x)

enum user_status {
    NOT_LOGGED,
    LOGGED
};

typedef struct send_payload_s {
    void *buff;
    size_t size;
} send_payload_t;

typedef struct client_list_s {
    struct client_list_s *next;
    enum user_status status;
    char *uid;
    char *pseudo;
    message_t *buff;
    int fd;
} client_list_t;

typedef struct fd_set_s {
    fd_set read;
    fd_set write;
    fd_set exeptions;
} fd_set_t;

typedef struct teams_s {
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
void choose_command(teams_t *server, client_list_t *client);
void login(teams_t *server, client_list_t *client);
char *increment_str(int id);
void user(teams_t *server, client_list_t *client);
server_user_t get_default_user(void);
server_get_user_t default_get_user(void);
void users(teams_t *server, client_list_t *client);
int is_connected(teams_t *server, char *uid);
int user_exist(char *uid);
void send_message(teams_t *server, client_list_t *client);
void messages(teams_t *server, client_list_t *client);
server_message_t get_default_message(void);
void subscribe(teams_t *server, client_list_t *client);
void unsubscribe(teams_t *server, client_list_t *client);
void logout(teams_t *server, client_list_t *client);
void print_all_user(void);
void create_team(teams_t *server, client_list_t *client, cli_create_t payload);
void create_command(teams_t *server, client_list_t *client);
void create_chanel(teams_t *server, client_list_t *client,
cli_create_t payload);
int create_save(void);
void create_thread(teams_t *server, client_list_t *client,
cli_create_t payload);
void create_reply(teams_t *server, client_list_t *client,
cli_create_t payload);
void send_to_everyone(teams_t *server, int command_id,
void *buff, size_t size);
void send_to_uid(teams_t *server, int command_id, send_payload_t payload,
char *uid);
void send_to_everyone_logged(teams_t *server, int command_id,
void *buff, size_t size);
void send_last_subscribed_user(client_list_t *client);
void send_subscribed_error(client_list_t *client, int error_status);
void subscribed_command(teams_t *server, client_list_t *client);
void send_user_as_subscribed_payload(teams_t *server, client_list_t *client,
server_team_user_t team_user);
int is_subscribed(char *team_id, char *uid);
void send_team_as_subscribed_payload(client_list_t *client,
server_create_info_t team_info);
void send_to_team(teams_t *server, void *buff, size_t size, char *team_id);
int get_thread_error_level(cli_create_t payload);
int get_reply_error_level(cli_create_t payload);
int team_name_already_exist(char *new_team_name);
int channel_name_already_exist(char *team_uid, char *new_team_name);
int thread_name_already_exist(char *team_uid, char *channel_uid,
char *new_team_name);
int is_bigger_id(char *folder_first, char *folder_second);
server_create_info_t get_create_info_struct(void);
void send_sub_error(client_list_t *client);
void list_command(teams_t *server, client_list_t *client);
void list_thread(client_list_t *client, cli_create_t payload);
void list_team(client_list_t *client, cli_create_t payload);
void list_reply(client_list_t *client, cli_create_t payload);
void list_channel(client_list_t *client, cli_create_t payload);
void send_last_item(client_list_t *client);
void ret_thread_error(client_list_t *client, cli_create_t payload,
int error_status);
void ret_reply_error(client_list_t *client, cli_create_t payload, int error);
void ret_channel_error(client_list_t *client, cli_create_t payload,
int error_code);
void info_command(teams_t *server, client_list_t *client);
void info_user(client_list_t *client, cli_create_t payload);
void info_thread(client_list_t *client, cli_create_t payload);
void info_team(client_list_t *client, cli_create_t payload);
void info_channel(client_list_t *client, cli_create_t payload);
