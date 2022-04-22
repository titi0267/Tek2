/*
** EPITECH PROJECT, 2022
** ftp
** File description:
** server_loop
*/

#include "../include/prototype.h"
#include "../include/main_struct.h"
#include "../include/ftp.h"

void server_fd(main_t *_main, node_t *list, node_t client)
{
    socklen_t addr_len;
    struct sockaddr_in new_addr;
    int new_cli;

    addr_len = sizeof(struct sockaddr_in);
    new_cli = accept(_main->server_fd, (struct sockaddr*)&new_addr, &addr_len);
    if (new_cli >= 0)
        new_fd_in_list_back(list, new_cli, _main);
    else
        fprintf(stderr, "Error: Accept failed: %s\n", strerror(errno));
}

int fd_selected(main_t *_main, node_t *client, fd_set fd_to_read)
{
    node_t list = (*client);

    if (FD_ISSET(_main->server_fd, &fd_to_read))
        server_fd(_main, client, list);
    for (list = (*client); list != NULL; list = list->next) {
        if (FD_ISSET(list->connection, &fd_to_read))
            client_part(_main, client, fd_to_read);
        if (_main->user_deleted == 1) {
            _main->user_deleted = 0;
            break;
        }
    }
}

int server_loop(main_t *_main, node_t *client)
{
    node_t list = (*client);
    fd_set fd_to_read;
    int select_val;

    while (1) {
        FD_ZERO(&fd_to_read);
        for (list = (*client); list != NULL; list = list->next)
            FD_SET(list->connection, &fd_to_read);
        select_val = select(FD_SETSIZE, &fd_to_read, NULL, NULL, NULL);
        if (select_val != -1 && select_val != 0)
            fd_selected(_main, client, fd_to_read);
        else
            fprintf(stderr, "Error: Select failed: %s\n", strerror(errno));
    }
    return (0);
}
