/*
** EPITECH PROJECT, 2022
** ftp
** File description:
** pass
*/

#include "../../include/prototype.h"
#include "../../include/ftp_code.h"

void parse_pass(char *buf, node_t client, main_t *_main)
{
    if (client->logged_in == 0) {
        dprintf(client->connection, "332 Need account for login.\r\n");
    } else if (client->logged_in == 1) {
        if (strcmp(buf, PASS) == 0)
            dprintf(client->connection, "230 User logged in, proceed.\r\n");
        else
            dprintf(client->connection, "530 Invalid username or password\r\n");
    } else {
        dprintf(client->connection, "530 Invalid username or password\r\n");
    }
}