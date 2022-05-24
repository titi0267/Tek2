/*
** EPITECH PROJECT, 2022
** teams
** File description:
** communication
*/

#pragma once

#define CMD_ERROR 84
#define MAX_NAME_LENGTH 32
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
    USE,
    CREATE,
    LIST,
    INFO
};

typedef struct cli_login_s {
    char name[33];
} cli_login_t;

typedef struct message_s {
    short command;
} message_t;