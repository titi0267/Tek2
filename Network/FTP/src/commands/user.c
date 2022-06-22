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
    if (client->logged_in == 0) {
        if (strcmp(buf, USER) == 0) {
            dprintf(client->connection, "331 User name okay, " \
                "need password.\r\n");
            client->logged_in = 1;
        } else {
            dprintf(client->connection, "331 User name okay, " \
                "need password.\r\n");
            client->logged_in = 2;
        }
    }
}