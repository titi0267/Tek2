/*
** EPITECH PROJECT, 2022
** ftp
** File description:
** retr
*/

#include "../../include/prototype.h"
#include "../../include/ftp_code.h"

void parse_retr(char *buf, node_t client, main_t *_main)
{
    if (client->logged_in == FALSE) {
        dprintf(client->connection, "530 Not logged in.\r\n");
        return;
    }
    if (client->pasv == FALSE) {
        dprintf(client->connection, "Not in passive mode\r\n");
        return;
    }
    dprintf(client->connection, "226 Command not found.\r\n");
}