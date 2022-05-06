/*
** EPITECH PROJECT, 2022
** teams
** File description:
** command
*/

#pragma once

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

typedef struct message_s {
    short command;
} message_t;
