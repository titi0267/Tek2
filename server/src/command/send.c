/*
** EPITECH PROJECT, 2022
** teams
** File description:
** send
*/

#include "../../include/teams.h"
#include <time.h>


server_message_t get_default_message(void)
{
    server_message_t message;

    message.is_valid = 0;
    message.time = time(NULL);
    memset(message.from, 0, MAX_NAME_LENGTH);
    memset(message.to, 0, MAX_NAME_LENGTH);
    memset(message.body, 0, MAX_BODY_LENGTH);
    return (message);
}

void write_send_error(client_list_t *client)
{
    server_message_t message = get_default_message();
    message_t command = {SEND};

    write(client->fd, &command, sizeof(message_t));
    write(client->fd, &message, sizeof(server_message_t));
}

int get_message_save_fd(client_list_t *client, cli_send_t message)
{
    int me = atoi(client->uid);
    int to_send = atoi(message.user_uuid);
    char *buff = malloc(MAX_NAME_LENGTH);

    if (to_send == 0 || !user_exist(message.user_uuid))
        return (-1);
    sprintf(buff, "./saves/message/conv%d_%d.txt",
    (me <= to_send) ? me : to_send, (me <= to_send) ? to_send : me);
    return (open(buff, O_RDWR | O_CREAT | O_APPEND, 0777));
}

void send_message(teams_t *server, client_list_t *client)
{
    cli_send_t message;
    server_message_t server_message = get_default_message();
    int fd = 0;

    read(client->fd, &message, sizeof(cli_send_t));
    fd = get_message_save_fd(client, message);
    if (fd == -1)
        return (write_send_error(client));
    server_message.is_valid = 1;
    strcpy(server_message.body, message.body);
    strcpy(server_message.to, message.user_uuid);
    strcpy(server_message.from, client->uid);
    write(fd, &server_message, sizeof(server_message_t));
    if (is_connected(server, message.user_uuid))
        send_to_uid(server, (int)SEND, (send_payload_t){&server_message,
        sizeof(server_message_t)}, message.user_uuid);
    server_event_private_message_sended(server_message.from,
    server_message.to, server_message.body);
}