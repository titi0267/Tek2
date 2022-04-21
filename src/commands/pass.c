/*
** EPITECH PROJECT, 2022
** ftp
** File description:
** pass
*/

#include "../../include/prototype.h"
#include "../../include/ftp_code.h"

void parse_pass(char *buf, node_t client)
{
    if (strcmp(buf, PASS) == 0) {
        dprintf(client->connection, "230 User logged in, proceed.\r\n");
        return;
    }
}