/*
** EPITECH PROJECT, 2022
** ftp
** File description:
** list
*/

#include "../../include/prototype.h"
#include "../../include/ftp_code.h"
#include <dirent.h>

void list_dir(node_t client)
{
    DIR *d;
    struct dirent *dir;
    d = opendir(".");
    if (d) {
        while ((dir = readdir(d)) != NULL) {
            dprintf(client->fd_client_pasv, "%s\r\n", dir->d_name);
        }
        closedir(d);
    }
}

void new_program(node_t client, main_t *_main)
{
    if (fork() != 0)
        return;
    list_dir(client);
    exit(0);
}

void parse_list(char *buf, node_t client, main_t *_main)
{
    if (client->logged_in == FALSE) {
        dprintf(client->connection, "530 Not logged in.\r\n");
        return;
    }
    dprintf(client->connection, "150 File status okay; about to open data " \
        "connection.\r\n");
    new_program(client, _main);
    dprintf(client->connection, "226 Closing data connection." \
            "Requested file action successful (for example, file" \
            "transfer or file abort).\r\n");
    close(client->fd_client_pasv);
    close(client->server_fd);
    client->pasv = FALSE;
}