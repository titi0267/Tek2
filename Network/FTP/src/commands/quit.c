/*
** EPITECH PROJECT, 2022
** ftp
** File description:
** parse_quit
*/

#include "../../include/prototype.h"
#include "../../include/ftp_code.h"

void parse_quit(char *buf, node_t client, main_t *_main)
{
    client->pasv = FALSE;
    dprintf(client->connection, "221 Service closing control connection. ");
    dprintf(client->connection, "Logged out if appropriate.\r\n");
}