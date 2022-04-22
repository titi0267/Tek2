/*
** EPITECH PROJECT, 2022
** ftp
** File description:
** help
*/

#include "../../include/prototype.h"
#include "../../include/ftp_code.h"

/*  rhelp in ftp    */
void parse_help(char *buf, node_t client, main_t *_main)
{
    dprintf(client->connection, "214 Help message. On how to use the server ");
    dprintf(client->connection, "or the meaning of a particular non-standard ");
    dprintf(client->connection, "command. This reply is useful only to the ");
    dprintf(client->connection, "human user.\r\n");
}