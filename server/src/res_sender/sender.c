/*
** EPITECH PROJECT, 2022
** teams
** File description:
** sender
*/

#include "../../include/teams.h"

void send_to_uid(teams_t *server, int command_id, void *buff, char *uid)
{
    client_list_t *loop = server->head;
    message_t message;

    message.command = command_id;
    for (; loop; loop = loop->next) {
        if (strcmp(loop->uid, uid) == 0) {
            write(loop->fd, &message, sizeof(message_t));
            write(loop->fd, buff, sizeof(*buff));
        }
    }
}

void send_to_everyone_except(teams_t *server, int command_id,
void *buff, char *except)
{
    client_list_t *loop = server->head;
    message_t message;

    message.command = command_id;
    for (; loop; loop = loop->next) {
        if (strcmp(loop->uid, except)) {
            write(loop->fd, &message, sizeof(message_t));
            write(loop->fd, buff, sizeof(*buff));
        }
    }
}

void send_to_everyone(teams_t *server, int command_id, void *buff)
{
    client_list_t *loop = server->head;
    message_t message;

    message.command = command_id;
    for (; loop; loop = loop->next) {
        write(loop->fd, &message, sizeof(message_t));
        write(loop->fd, buff, sizeof(*buff));
    }
}