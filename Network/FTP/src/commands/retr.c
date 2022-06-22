/*
** EPITECH PROJECT, 2022
** ftp
** File description:
** retr
*/

#include "../../include/prototype.h"
#include "../../include/ftp_code.h"
#include <fcntl.h>

void read_file(char *filename, node_t client)
{
    FILE *file = fopen(filename, "rb");
    char *buffer;
    long fsize;

    if (file == NULL) {
        printf("failed to open : $%s$\n", filename);
        return;
    }
    fseek(file, 0, SEEK_END);
    fsize = ftell(file);
    fseek(file, 0, SEEK_SET);
    buffer = malloc(sizeof(char) * (fsize + 1));
    fread(buffer, 1, fsize, file);
    fclose(file);
    buffer[fsize] = 0;
    dprintf(client->fd_client_pasv, "%s\r\n", buffer);
    free(buffer);
}

void open_file(char *buf, node_t client)
{
    char *file = malloc(sizeof(char) * strlen(buf) + 1);
    int fd;

    if (buf[4] != ' ' || buf[5] == '\r')
        return;
    strncpy(file, buf + 5, strlen(buf) - 7);
    file[strlen(buf) - 7] = '\0';
    read_file(file, client);
    free(file);
}

void fork_program(char *buf, node_t client)
{
    if (fork() != 0)
        return;
    open_file(buf, client);
    exit(0);
}

void parse_retr(char *buf, node_t client, main_t *_main)
{
    if (client->logged_in == FALSE) {
        dprintf(client->connection, "530 Not logged in.\r\n");
        return;
    }
    if (client->pasv == FALSE) {
        dprintf(client->connection, "500 Not in passive mode\r\n");
        return;
    }
    if (client->fd_client_pasv == -1) {
        dprintf(client->connection, "550 \r\n");
        return;
    }
    dprintf(client->connection, "150 File status okay; about to open data " \
        "connection.\r\n");
    fork_program(buf, client);
    dprintf(client->connection, "226 Command not found.\r\n");
    close(client->fd_client_pasv);
    close(client->server_fd);
    client->pasv = FALSE;
}