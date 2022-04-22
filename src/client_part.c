/*
** EPITECH PROJECT, 2022
** ftp
** File description:
** client_part
*/

#include "../include/ftp.h"
#include "../include/prototype.h"
#include "../include/main_struct.h"

int parse_recieved(node_t client, main_t *_main)
{
    void (*parse_command[14]) (char *, node_t, main_t *) = {parse_user,
        parse_pass, parse_noop, parse_quit, parse_help, parse_path, parse_cdup,
        parse_cwd, parse_dele, parse_pasv, parse_port, parse_retr, parse_stor,
        parse_list};
    char *command[15] = {"USER", "PASS", "NOOP", "QUIT", "HELP", "PWD ",
        "CDUP", "CWD ", "DELE", "PASV", "PORT", "RETR", "STOR", "LIST", 0};
    int i = 0;

    for (i = 0; command[i] != 0; i++) {
        if (strncmp("QUIT", _main->buf, 3) == 0) {
            (*parse_command[i]) (_main->buf, client, _main);
            return (-1);
        }
        if (strncmp(command[i], _main->buf, 3) == 0) {
            (*parse_command[i]) (_main->buf, client, _main);
            break;
        }
    }
    if (i == 14) {
        dprintf(client->connection, "502 Command not found.\r\n");
    }
}

void client_value(int read_ret, node_t client, main_t *_main, node_t *front_ptr)
{
    if (read_ret > 0) {
        _main->buf[read_ret] = '\0';
        printf("%s", _main->buf);
        if (parse_recieved(client, _main) == -1)
            read_ret = -1;
    }
    if (read_ret <= 0) {
        //printf("client quit\n");
        close(client->connection);
        if (delete_fd(front_ptr, client->connection) == 1)
            _main->user_deleted = 1;
    }
}

void client_part(main_t *_main, node_t *list, fd_set fd_to_read)
{
    node_t client = (*list);
    int read_ret = 0;

    for (client = client->next; client != NULL; client = client->next) {
        if (FD_ISSET(client->connection, &fd_to_read)) {
            read_ret = read(client->connection, _main->buf, 500);
            client_value(read_ret, client, _main, list);
        }
        if (_main->user_deleted == 1) {
            break;
        }
        if (read_ret == -1) {
            printf("recieved failed for fd: %d []\n", client->connection);
            break;
        }
    }
    memset(_main->buf, 0, 500);
    //free(_main->buf);
}
