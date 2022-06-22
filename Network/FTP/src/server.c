/*
** EPITECH PROJECT, 2022
** ftp
** File description:
** server
*/

#include "../include/prototype.h"
#include "../include/main_struct.h"
#include "../include/ftp.h"

int bind_server(main_t *_main, int server_port)
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
    if (bind(sck, (struct sockaddr *)&my_socket, sizeof(my_socket)) == -1
        || listen(sck, 5) == -1)
        return (-1);
    socklen = sizeof(my_socket);
    getsockname(sck, (struct sockaddr *)&my_socket, &socklen);
    _main->port_pasv = htons(my_socket.sin_port);
    return (sck);
}

int init_server(main_t *_main)
{
    node_t client = NULL;

    _main->server_fd = bind_server(_main, _main->port);
    _main->port_pasv = 0;
    if (_main->server_fd == -1)
        return (ERROR_CODE);
    new_fd_in_list(&client, _main->server_fd);
    server_loop(_main, &client);
    return (0);
}