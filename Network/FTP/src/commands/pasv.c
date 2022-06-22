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
        dprintf(client->connection, "500 Command not found.\r\n");
        return;
    }
    client->pasv = TRUE;
    client->server_fd = new_server;
    client->port = _main->port_pasv;
    dprintf(client->connection, "227 Entering Passive Mode (127,0,0,1,%i,%i)" \
        ".\r\n", client->port / 256, client->port % 256);
}