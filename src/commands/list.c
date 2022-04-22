/*
** EPITECH PROJECT, 2022
** ftp
** File description:
** list
*/

#include "../../include/prototype.h"
#include "../../include/ftp_code.h"

void parse_list(char *buf, node_t client, main_t *_main)
{
    dprintf(client->connection, "502 Command not found.\r\n");
}