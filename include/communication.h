/*
** EPITECH PROJECT, 2022
** teams
** File description:
** communication
*/

#pragma once

#define CMD_ERROR 84
#define MAX_NAME_LENGTH 32
#define MAX_DESCRIPTION_LENGTH 255
#define MAX_BODY_LENGTH 512

enum command_id {
    HELP,
    LOGIN,
    LOGOUT,
    USERS,
    USER,
    SEND,
    MESSAGES,
    SUBSCRIBE,
    SUBSCRIBED,
    UNSUBSCRIBE,
    USE, // a faire + en dessous
    CREATE,
    LIST,
    INFO
};

typedef struct cli_login_s {
    char name[MAX_NAME_LENGTH];
} cli_login_t;

typedef struct cli_messages_s {
    char user_uuid[MAX_NAME_LENGTH];
} cli_messages_t;

typedef struct cli_send_s {
    char user_uuid[MAX_NAME_LENGTH];
    char body[MAX_BODY_LENGTH];
} cli_send_t;

typedef struct cli_users_s {
    char user_uuid[MAX_NAME_LENGTH];
} cli_users_t;

typedef struct cli_subscribe_s {
    char team_uuid[MAX_NAME_LENGTH];
} cli_subscribe_t;

typedef struct cli_subscribed_s {
    char team_uuid[MAX_NAME_LENGTH];
} cli_subscribed_t;

typedef struct cli_unsubscribe_s {
    char team_uuid[MAX_NAME_LENGTH];
} cli_unsubscribe_t;

typedef struct cli_use_s {
    char team_uuid[MAX_NAME_LENGTH];
    char channel_uuid[MAX_NAME_LENGTH];
    char thread_uuid[MAX_NAME_LENGTH];
} cli_use_t;

typedef struct cli_create_s {
    char team_uuid[MAX_NAME_LENGTH];
    char comment_body[MAX_BODY_LENGTH];
} cli_create_t;

typedef struct message_s {
    short command;
} message_t;