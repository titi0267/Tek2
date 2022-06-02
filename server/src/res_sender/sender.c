/*
** EPITECH PROJECT, 2022
** teams
** File description:
** sender
*/

#include "../../include/teams.h"

void send_to_uid(teams_t *server, int command_id, send_payload_t payload,
char *uid)
{
    client_list_t *loop = server->head;
    message_t message;

    message.command = command_id;
    for (; loop; loop = loop->next) {
        if (strcmp(loop->uid, uid) == 0) {
            write(loop->fd, &message, sizeof(message_t));
            write(loop->fd, payload.buff, payload.size);
        }
    }
}

void send_to_everyone_except(teams_t *server, int command_id,
send_payload_t payload, char *except)
{
    client_list_t *loop = server->head;
    message_t message;

    message.command = command_id;
    for (; loop; loop = loop->next) {
        if (strcmp(loop->uid, except)) {
            write(loop->fd, &message, sizeof(message_t));
            write(loop->fd, payload.buff, payload.size);
        }
    }
}

void send_to_everyone(teams_t *server, int command_id, void *buff, size_t size)
{
    client_list_t *loop = server->head;
    message_t message;

    message.command = command_id;
    for (; loop; loop = loop->next) {
        write(loop->fd, &message, sizeof(message_t));
        write(loop->fd, buff, size);
    }
}