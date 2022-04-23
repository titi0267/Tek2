/*
** EPITECH PROJECT, 2022
** ftp
** File description:
** retr
*/

#include "../../include/prototype.h"
#include "../../include/ftp_code.h"

int pasv_server_accept(node_t client)
{
    socklen_t addr_len;
    struct sockaddr_in new_addr;
    int new_cli;

    addr_len = sizeof(struct sockaddr_in);
    new_cli = accept(client->server_fd, (struct sockaddr*)&new_addr, &addr_len);
    if (new_cli >= 0)
        client->fd_client_pasv = new_cli;
    else
        fprintf(stderr, "Error: Accept failed: %s\n", strerror(errno));

}

void parse_retr(char *buf, node_t client, main_t *_main)
{
    if (client->logged_in == FALSE) {
        dprintf(client->connection, "530 Not logged in.\r\n");
        return;
    }
    if (client->pasv == FALSE) {
        dprintf(client->connection, "Not in passive mode\r\n");
        return;
    }
    if (FD_ISSET(client->server_fd, &(client->fd_to_read))) {
            pasv_server_accept(client);
        }
    dprintf(client->connection, "502 Command not found.\r\n");
}