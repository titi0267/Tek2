/*
** EPITECH PROJECT, 2022
** ftp
** File description:
** dele
*/

#include "../../include/prototype.h"
#include "../../include/ftp_code.h"

char *get_path_del(char *buf, node_t client)
{
    char *temp = malloc(sizeof(char) * strlen(buf) + 1);
    char *path = malloc(sizeof(char) * strlen(client->path) + strlen(buf) + 3);
    char *no_slash;

    strcpy(path, client->path);
    strncpy(temp, buf + 5, strlen(buf) - 7);
    temp[strlen(buf) - 7] = '\0';
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

void parse_dele(char *buf, node_t client, main_t *_main)
{
    char *file = get_path_del(buf, client);
    char *path = realpath(file, NULL);

    if (path == NULL || remove(path) == -1) {
        dprintf(client->connection, "550 Requested action not taken. ");
        dprintf(client->connection, "File unavailable (e.g., file not found, ");
        dprintf(client->connection, "no access).\r\n");
        return;
    }
    dprintf(client->connection, "250 Requested file action okay, ");
    dprintf(client->connection, "completed.\r\n");
}