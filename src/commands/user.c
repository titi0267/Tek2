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
    if (strcmp(buf, USER) == 0) {
        dprintf(client->connection, "331 User name okay, need password.\r\n");
        return;
    }
}