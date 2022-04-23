/*
** EPITECH PROJECT, 2022
** ftp
** File description:
** stor
*/

#include "../../include/prototype.h"
#include "../../include/ftp_code.h"

void parse_stor(char *buf, node_t client, main_t *_main)
{
    if (client->logged_in == FALSE) {
        dprintf(client->connection, "530 Not logged in.\r\n");
        return;
    }
    dprintf(client->connection, "502 Command not found.\r\n");
}