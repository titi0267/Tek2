/*
** EPITECH PROJECT, 2022
** ftp
** File description:
** user
*/

#include "../../include/prototype.h"
#include "../../include/ftp_code.h"

void parse_user(char *buf, node_t client, main_t *_main)
{
    if (strcmp(buf, USER) == 0 && client->logged_in == 0) {
        dprintf(client->connection, "331 User name okay, need password.\r\n");
        client->logged_in = 1;
        return;
    } else if (strcmp(buf, USER) == 0 && client->logged_in == 1) {
        dprintf(client->connection, "230 User logged in, proceed.\r\n");
    } else {
        dprintf(client->connection, "430 Invalid username or password\r\n");
    }
}