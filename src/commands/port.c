/*
** EPITECH PROJECT, 2022
** ftp
** File description:
** port
*/

#include "../../include/prototype.h"
#include "../../include/ftp_code.h"

void create_client(node_t client, int server_port)
{
    int sck;
    struct sockaddr_in my_socket;
    unsigned int socklen;

    sck = socket(AF_INET, SOCK_STREAM, 0);
    if (sck == -1) {
        fprintf(stderr, "Socket failed: %s\n", strerror(errno));
        return (-1);
    }
    my_socket.sin_family = AF_INET;
    my_socket.sin_port = htons(server_port);
    my_socket.sin_addr.s_addr = INADDR_ANY;
    connect(sck, (struct sockaddr *)&my_socket, sizeof(my_socket));
    return (sck);
}

void parse_port(char *buf, node_t client, main_t *_main)
{
    int server_port = 10;

    client->pasv = FALSE;
    if (client->logged_in == FALSE) {
        dprintf(client->connection, "530 Not logged in.\r\n");
        return;
    }
    //create_client(client, server_port);
    dprintf(client->connection, "502 Command not found.\r\n");
}