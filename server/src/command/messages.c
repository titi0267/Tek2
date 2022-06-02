/*
** EPITECH PROJECT, 2022
** teams
** File description:
** messages
*/

#include "../../include/teams.h"

int open_good_fd(client_list_t *client, cli_messages_t message)
{
    int me = atoi(client->uid);
    int to_send = atoi(message.user_uuid);
    char *buff = malloc(MAX_NAME_LENGTH);

    if (to_send == 0 || !user_exist(message.user_uuid))
        return (-1);
    sprintf(buff, "./saves/message/conv%d_%d.txt",
    (me <= to_send) ? me : to_send, (me <= to_send) ? to_send : me);
    return (open(buff, O_RDWR | O_APPEND | O_CREAT, 0777));
}

void messages(teams_t *server, client_list_t *client)
{
    cli_messages_t messages;
    message_t command = {MESSAGES};
    server_message_t server_message = get_default_message();
    int fd = 0;
    int read_ret = 0;

    UNUSED(server);
    read(client->fd, &messages, sizeof(cli_messages_t));
    fd = open_good_fd(client, messages);
    write(client->fd, &command, sizeof(message_t));
    if (fd == -1) {
        write(client->fd, &server_message, sizeof(server_message_t));
        return;
    }
    while ((read_ret = read(fd, &server_message, sizeof(server_message_t)))
    != 0 && read_ret != -1)
        write(client->fd, &server_message, sizeof(server_message_t));
    server_message = get_default_message();
    write(client->fd, &server_message, sizeof(server_message_t));
}