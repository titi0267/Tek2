/*
** EPITECH PROJECT, 2022
** ftp
** File description:
** change_dir
*/

#include "../../include/prototype.h"
#include "../../include/ftp_code.h"

void parse_cdup(char *buf, node_t client, main_t *_main)
{
    char *path;
    int i = strlen(client->path);

    for (; i != -1; i--) {
        if (client->path[i] == '/' && i != 0) {
            client->path[i] = '\0';
            break;
        }
        if (client->path[i] == '/' && i == 0) {
            client->path[i + 1] = '\0';
            break;
        }
    }
    dprintf(client->connection, "200 Command okay.\r\n");
}