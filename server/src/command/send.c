/*
** EPITECH PROJECT, 2022
** teams
** File description:
** send
*/

#include "../../include/teams.h"

server_message_t get_default_message()
{
    server_message_t message;

    message.is_valid = 0;
    memset(message.from, 0, MAX_NAME_LENGTH);
    memset(message.to, 0, MAX_NAME_LENGTH);
    memset(message.body, 0, MAX_BODY_LENGTH);
    return (message);
}

int get_message_save_fd(client_list_t *client, cli_send_t message)
{
    int me = atoi(client->uid);
    int to_send = atoi(message.user_uuid);
    char *buff;

    if (to_send == 0 || !user_exist(message.user_uuid))
        return (-1);
    sprintf(buff, "./saves/message/conv%d_%d.txt",
    (me <= to_send) ? me : to_send, (me <= to_send) ? to_send : me);
    return (open(buff, O_WRONLY | O_APPEND | O_CREAT));
}

void send_message(teams_t *server, client_list_t *client)
{
    cli_send_t message;
    server_message_t server_message = get_default_message();
    int fd = 0;

    UNUSED(server);
    read(client->fd, &message, sizeof(cli_send_t));
    fd = get_message_save_fd(client, message);
    if (fd == -1) {
        write(fd, &server_message, sizeof(server_message_t));
        write(client->fd, &server_message, sizeof(server_message_t));
    }
    server_message.is_valid = 1;
    strcpy(server_message.body, message.body);
    strcpy(server_message.to, message.user_uuid);
    strcpy(server_message.from, client->uid);
    write(fd, &server_message, sizeof(server_message_t));
    write(client->fd, &server_message, sizeof(server_message_t));
}