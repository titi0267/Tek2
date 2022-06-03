/*
** EPITECH PROJECT, 2022
** teams
** File description:
** parse_command
*/

#include "../include/teams.h"
#include "../include/command.h"

int parse_cmd(char *buff, client_t *client)
{
    char *cmd[15] = {"/help", "/login", "/logout", "/users", "/user",
        "/send", "/messages", "/subscribe", "/subscribed", "/unsubscribe",
        "/use", "/create", "/list", "/info", 0};
    int (*command[14]) (char *, client_t *) = {c_help, c_login, c_logout,
        c_users, c_user, c_send, c_messages, c_subscribe, c_subscribed,
        c_unsubscribe, c_use, c_create, c_list, c_info};
    size_t len;

    for (; buff[0] != 0 && buff[0] == ' '; buff++);
    for (len = 0; buff[len] != ' ' && buff[len] != '\n'
        && buff[len] != '\0'; len++);
    for (int i = 0; i < 14; i++) {
        if (strlen(cmd[i]) == len && strncmp(cmd[i], buff, len) == 0) {
            return ((command[i]((buff + len), client)));
        }
    }
    return (84);
}