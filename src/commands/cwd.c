/*
** EPITECH PROJECT, 2022
** ftp
** File description:
** cwd
*/

#include "../../include/prototype.h"
#include "../../include/ftp_code.h"

char *get_path(char *buf, node_t client)
{
    char *temp = malloc(sizeof(char) * strlen(buf) + 1);
    char *path = malloc(sizeof(char) * strlen(client->path) + strlen(buf) + 3);
    char *no_slash;

    strcpy(path, client->path);
    strncpy(temp, buf + 4, strlen(buf) - 6);
    temp[strlen(buf) - 6] = '\0';
    no_slash = malloc(sizeof(char) * strlen(temp) + 3);
    no_slash[0] = '/';
    no_slash[1] = '\0';
    if (temp[0] != '/' && path[strlen(client->path)] != '/') {
        strcat(no_slash, temp);
        strcat(path, no_slash);
    } else
        strcat(path, temp);
    free(temp);
    free(no_slash);
    return (path);
}

int cannot_go_over(char *path, node_t client, main_t *_main)
{
    char *check_path = malloc(sizeof(char) * strlen(path));

    check_path = realpath(path, NULL);
    if (check_path == NULL ||
        strncmp(check_path, _main->path, strlen(_main->path)) != 0) {
        dprintf(client->connection, "550 Requested action not taken. File ");
        dprintf(client->connection, "unavailable (e.g., file not found, no ");
        dprintf(client->connection, "access).\r\n");
        free(check_path);
        return (-1);
    }
    client->path = strdup(check_path);
    free(check_path);
    return (0);
}

void parse_cwd(char *buf, node_t client, main_t *_main)
{
    char *path = get_path(buf, client);

    if (cannot_go_over(path, client, _main) == -1) {
        return;
    }
    dprintf(client->connection, "250 Requested file action okay,");
    dprintf(client->connection, " completed.\r\n");
}