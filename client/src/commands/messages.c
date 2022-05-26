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
    if (client->log_status == NOT_LOGGED || check_is_arg(buff) == CMD_ERROR
        || check_valid_cmd_type(buff) == CMD_ERROR ||
        check_valid_uuid(buff) == CMD_ERROR)
        return (CMD_ERROR);
    buff += 2;
    printf("Messages from ");
    for (int i = 0; i < strlen(buff) - 2; i++)
        cli_msgs.user_uuid[i] = buff[i];
    printf("%s\n", cli_msgs.user_uuid);
    msg.command = MESSAGES;
    write(client->socket_fd, &msg, sizeof(message_t));
    printf("%s\n", cli_msgs.user_uuid);
    write(client->socket_fd, &cli_msgs, sizeof(cli_messages_t));
    //client_private_message_print_messages()
    return (MESSAGES);
}