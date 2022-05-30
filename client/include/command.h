/*
** EPITECH PROJECT, 2022
** teams
** File description:
** command
*/

#pragma once
#include <stdio.h>
#include <string.h>
#include "./teams.h"

int c_help(char *, client_t *);
int c_login(char *, client_t *);
int c_logout(char *, client_t *);
int c_users(char *, client_t *);
int c_user(char *, client_t *);
int c_send(char *, client_t *);
int c_messages(char *, client_t *);
int c_subscribe(char *, client_t *);
int c_subscribed(char *, client_t *);
int c_unsubscribe(char *, client_t *);
int c_use(char *, client_t *);
int c_create(char *, client_t *);
int c_list(char *, client_t *);
int c_info(char *, client_t *);
int check_is_arg(char *buff);
int check_valid_cmd_type(char *buff);
int check_valid_uuid(char *buff);
int check_valid_length(char *buff, int max_sz);