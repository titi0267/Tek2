/*
** EPITECH PROJECT, 2022
** teams
** File description:
** logging
*/

#pragma once

typedef struct logging_s {
    int (*client_event_logged_in)(char const *user_uuid, const char *user_name);
    int (*client_event_logged_out)(char const *user_uuid, const char *user_name);
    int (*client_event_private_message_received)(char const *user_uuid, char const *message_body);
} logging_t;