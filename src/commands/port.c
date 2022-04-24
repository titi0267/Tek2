/*
** EPITECH PROJECT, 2022
** ftp
** File description:
** port
*/

#include "../../include/prototype.h"
#include "../../include/ftp_code.h"

void parse_port(char *buf, node_t client, main_t *_main)
{
    int server_port = 10;

    client->pasv = FALSE;
    if (client->logged_in == FALSE) {
        dprintf(client->connection, "530 Not logged in.\r\n");
        return;
    }
    dprintf(client->connection, "500 Command not found.\r\n");
}