/*
** EPITECH PROJECT, 2022
** ftp
** File description:
** change_dir
*/

#include "../../include/prototype.h"
#include "../../include/ftp_code.h"

char *move_dir(char *old_pwd)
{
    int i = strlen(old_pwd);

    for (; i != -1; i--) {
        if (old_pwd[i] == '/' && i != 0) {
            old_pwd[i] = '\0';
            break;
        }
        if (old_pwd[i] == '/' && i == 0) {
            old_pwd[i + 1] = '\0';
            break;
        }
    }
    return (old_pwd);
}

int cant_go_here(char *old_pwd, node_t client, main_t *_main)
{
    char *path = malloc(sizeof(char) * strlen(old_pwd));

    path = realpath(move_dir(old_pwd), NULL);
    if (path == NULL || strlen(path) < strlen(_main->path) ||
        (strlen(path) >= strlen(_main->path) &&
        strncmp(path, _main->path, strlen(_main->path)) != 0)) {
        dprintf(client->connection, "550 Requested action not taken. File " \
            "unavailable (e.g., file not found, no access).\r\n");
        free(path);
        free(old_pwd);
        return (-1);
    }
    strcpy(client->path, path);
    return (0);
}

void parse_cdup(char *buf, node_t client, main_t *_main)
{
    char *old_pwd;

    client->pasv = FALSE;
    if (client->logged_in == FALSE) {
        dprintf(client->connection, "530 Not logged in.\r\n");
        return;
    }
    old_pwd = malloc(sizeof(char) * strlen(client->path) + 1);
    strcpy(old_pwd, client->path);
    if (cant_go_here(old_pwd, client, _main) == -1) {
        return;
    }
    dprintf(client->connection, "200 Command okay.\r\n");
}