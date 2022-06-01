/*
** EPITECH PROJECT, 2022
** teams
** File description:
** get_server_reply
*/

#include "../include/teams.h"
#include "../include/reply.h"

void r_help(void)
{
}

void r_use(void)
{
}

void get_server_recv(client_t *client, message_t msg)
{
    void (*command[14])(client_t *) =
    {r_help, r_login, r_logout, r_users, r_user, r_send, r_messages, r_subscribe,
    r_subscribed, r_unsubscribe, r_use, r_create, r_list, r_info};

    if (msg.command > 14)
        return;
    (command[msg.command])(client);
}
