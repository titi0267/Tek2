/*
** EPITECH PROJECT, 2022
** teams
** File description:
** reply
*/

#pragma once

#include "teams.h"

int r_login(client_t *client);
int r_logout(client_t *client);
int r_user(client_t *client);
int r_users(client_t *client);
int r_send(client_t *client);
int r_messages(client_t *client);
int r_subscribe(client_t *client);
int r_subscribed(client_t *client);
int r_unsubscribe(client_t *client);
int r_create(client_t *client);
int r_list(client_t *client);
int r_info(client_t *client);

