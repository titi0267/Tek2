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
    if (strcmp(buf, PASS) == 0 && client->logged_in == 1) {
        dprintf(client->connection, "230 User logged in, proceed.\r\n");
        return;
    } else if (strcmp(buf, PASS) == 0 && client->logged_in == 0) {
        dprintf(client->connection, "332 Need account for login.\r\n");
        client->logged_in = 1;
    } else {
        dprintf(client->connection, "430 Invalid username or password\r\n");
    }
}