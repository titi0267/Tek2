/*
** EPITECH PROJECT, 2022
** teams
** File description:
** parse_command
*/

#include "../include/teams.h"
#include "../include/command.h"

int parse_cmd(char *buff)
{
    char cmd[16][16] = {"/help", "/login", "/logout", "/users", "/user",
        "/send", "/messages", "/subscribe", "/subscribed", "/unsubscribe",
        "/use", "/create", "/list", "/info", 0};
    int (*command[14]) (char *) = {c_help, c_login, c_logout, c_users, c_user,
        c_send, c_messages, c_subscribe, c_subscribed, c_unsubscribe, c_use,
        c_create, c_list, c_info};
    int len;

    for (len = 0; buff[len] != ' ' && buff[len] != '\n'
        && buff[len] != '\0'; len++);
    for (int i = 0; i < 15; i++) {
        if (strlen(cmd[i]) == len && strncmp(cmd[i], buff, len) == 0) {
            return ((command[i](buff + len)));
        }
    }
    return (84);
}