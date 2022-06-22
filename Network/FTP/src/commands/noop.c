/*
** EPITECH PROJECT, 2022
** ftp
** File description:
** noop
*/

#include "../../include/prototype.h"
#include "../../include/ftp_code.h"

void parse_noop(char *buf, node_t client, main_t *_main)
{
    client->pasv = FALSE;
    dprintf(client->connection, "200 Command okay.\r\n");
}