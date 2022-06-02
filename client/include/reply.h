/*
** EPITECH PROJECT, 2022
** teams
** File description:
** reply
*/

#pragma once

#include "teams.h"

void r_login(client_t *client);
void r_logout(client_t *client);
void r_user(client_t *client);
void r_users(client_t *client);
void r_send(client_t *client);
void r_messages(client_t *client);
void r_subscribe(client_t *client);
void r_subscribed(client_t *client);
void r_unsubscribe(client_t *client);
void r_create(client_t *client);
void r_list(client_t *client);
void r_info(client_t *client);

