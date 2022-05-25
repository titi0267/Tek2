/*
** EPITECH PROJECT, 2022
** teams
** File description:
** messages
*/

#include "../../include/teams.h"
#include "../../include/command.h"

int c_messages(char *buff, client_t *client)
{
    message_t msg;
    cli_messages_t cli_msgs;

    memset(cli_msgs.user_uuid, 0, MAX_NAME_LENGTH);
    if (check_is_arg(buff) == CMD_ERROR || check_valid_cmd_type(buff)
        == CMD_ERROR || check_valid_uuid(buff) == CMD_ERROR)
        return (CMD_ERROR);
    buff += 2;
    printf("Messages from ");
    for (int i = 0; i < strlen(buff) - 2; i++) {
        printf("%c", buff[i]);
        cli_msgs.user_uuid[i] = buff[i];
    }
    puts("");
    msg.command = MESSAGES;
    write(client->socket_fd, &msg, sizeof(message_t));
    printf("%s\n", cli_msgs.user_uuid);
    write(client->socket_fd, &cli_msgs, sizeof(cli_messages_t));
    return (MESSAGES);
}