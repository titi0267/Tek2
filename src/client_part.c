/*
** EPITECH PROJECT, 2022
** ftp
** File description:
** client_part
*/

#include "../include/ftp.h"
#include "../include/prototype.h"
#include "../include/main_struct.h"

void parse_recieved(char *buf, node_t client)
{
    void (*parse_command[2]) (char *, node_t) = {parse_user, parse_pass};
    char *command[15] = {"USER", "PASS", "CWD ", "CDUP", "QUIT", "DELE", "PWD ",
        "PASV", "PORT", "HELP", "NOOP", "RETR", "STOR", "LIST", 0};
    for (int i = 0; command[i] != 0; i++) {
        if (strncmp(command[i], buf, 3) == 0) {
            (*parse_command[i]) (buf, client);
            break;
        }
    }
}

void client_value(int read_ret, node_t client, char *buf)
{
    if (read_ret == 0) {
        close(client->connection);
        client->connection = -1;
    }
    if (read_ret > 0) {
        buf[read_ret] = '\0';
        printf("%s", buf);
        parse_recieved(buf, client);
    }
}

void client_part(main_t *_main, node_t *list, fd_set fd_to_read)
{
    node_t client = (*list);
    int read_ret = 0;
    char *buf = malloc(sizeof(char) * 500);

    for (client = client->next; client != NULL; client = client->next) {
        if (FD_ISSET(client->connection, &fd_to_read)) {
            read_ret = read(client->connection, buf, 500);
            client_value(read_ret, client, buf);
        }
        if (read_ret == -1) {
            printf("recieved failed for fd: %d []\n", client->connection);
            break;
        }
    }
}
