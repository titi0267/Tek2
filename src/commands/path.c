/*
** EPITECH PROJECT, 2022
** ftp
** File description:
** path
*/

#include "../../include/prototype.h"
#include "../../include/ftp_code.h"

void parse_path(char *buf, node_t client, main_t *_main)
{
    dprintf(client->connection, "257 %s created.\r\n", client->path);
}