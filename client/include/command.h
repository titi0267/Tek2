/*
** EPITECH PROJECT, 2022
** teams
** File description:
** command
*/

#pragma once
#include <stdio.h>
#include <string.h>

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
int check_is_arg(char *buff);
int check_valid_cmd_type(char *buff);
int check_valid_uuid(char *buff);