/*
** EPITECH PROJECT, 2022
** teams
** File description:
** command
*/

#pragma once
#include <stdio.h>

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

int c_help(char *);
int c_login(char *);
int c_logout(char *);
int c_users(char *);
int c_user(char *);
int c_send(char *);
int c_messages(char *);
int c_subscribe(char *);
int c_subscribed(char *);
int c_unsubscribe(char *);
int c_use(char *);
int c_create(char *);
int c_list(char *);
int c_info(char *);
