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

enum finded_user {
    FOUND,
    NOT_FOUND
};

enum use {
    DEFAULT,
    TEAMS,
    CHANNEL,
    THREADS
};

typedef struct server_team_info_s {
    char name[MAX_NAME_LENGTH];
    char description[MAX_DESCRIPTION_LENGTH];
    char team_uuid[MAX_NAME_LENGTH];
    int is_valid;
} server_team_info_t;

typedef struct server_chanel_info_s {
    char name[MAX_NAME_LENGTH];
    char description[MAX_DESCRIPTION_LENGTH];
    char team_uuid[MAX_NAME_LENGTH];
    char channel_uuid[MAX_NAME_LENGTH];
    int is_valid;
} server_chanel_info_t;

typedef struct server_thread_info_s {
    char name[MAX_NAME_LENGTH];
    char description[MAX_DESCRIPTION_LENGTH];
    char team_uuid[MAX_NAME_LENGTH];
    char channel_uuid[MAX_NAME_LENGTH];
    char thread_uid[MAX_NAME_LENGTH];
    int is_valid;
} server_thread_info_t;

typedef struct server_reply_info_s {
    char name[MAX_NAME_LENGTH];
    char description[MAX_DESCRIPTION_LENGTH];
    char team_uuid[MAX_NAME_LENGTH];
    char channel_uuid[MAX_NAME_LENGTH];
    char thread_uid[MAX_NAME_LENGTH];
    int is_valid;
} server_reply_info_t;

typedef struct server_unsub_s {
    int valid;
} server_unsub_t;

typedef struct server_sub_s {
    int exist;
} server_sub_t;

typedef struct server_team_user_s {
    int is_active;
    char pseudo[MAX_NAME_LENGTH];
    char uid[MAX_NAME_LENGTH];
} server_team_user_t;

typedef struct server_user_s {
    char pseudo[MAX_NAME_LENGTH];
    char uid[MAX_NAME_LENGTH];
} server_user_t;

typedef struct server_message_s {
    char from[MAX_NAME_LENGTH];
    char to[MAX_NAME_LENGTH];
    char body[MAX_BODY_LENGTH];
    int is_valid;
    long int time;
} server_message_t;

typedef struct server_get_user_s {
    int found;
    int connected;
    char pseudo[MAX_NAME_LENGTH];
    char uid[MAX_NAME_LENGTH];
} server_get_user_t;

typedef struct cli_login_s {
    char name[MAX_NAME_LENGTH];
} cli_login_t;

typedef struct cli_messages_s {
    char user_uuid[MAX_NAME_LENGTH];
} cli_messages_t;

typedef struct cli_logout_s {
    int logout;
} cli_logout_t;

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
    char name[MAX_NAME_LENGTH];
    char description[MAX_DESCRIPTION_LENGTH];
    char comment_body[MAX_BODY_LENGTH];
    char team_uuid[MAX_NAME_LENGTH];
    char channel_uuid[MAX_NAME_LENGTH];
    char thread_uuid[MAX_NAME_LENGTH];
    int args_nbr;
} cli_create_t;

typedef struct cli_list_s {
    int use_arg;
} cli_list_t;

typedef struct cli_info_s {
    int use_arg;
} cli_info_t;

typedef struct message_s {
    short command;
} message_t;