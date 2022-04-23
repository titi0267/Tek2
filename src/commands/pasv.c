/*
** EPITECH PROJECT, 2022
** ftp
** File description:
** pasv
*/

#include "../../include/prototype.h"
#include "../../include/ftp_code.h"

void parse_pasv(char *buf, node_t client, main_t *_main)
{
    int new_server;

    if (client->logged_in == FALSE) {
        dprintf(client->connection, "530 Not logged in.\r\n");
        return;
    }
    new_server = bind_server(_main, 0);
    if (new_server == -1) {
        dprintf(client->connection, "502 Command not found.\r\n");
    }
    client->pasv = TRUE;
    client->server_fd = new_server;
}