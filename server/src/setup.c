/*
** EPITECH PROJECT, 2022
** ftp
** File description:
** setup
*/


#include "../include/teams.h"

int setup_server(char *port)
{
    struct sockaddr_in server;
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    int check_bind = 0;

    if (fd == -1)
        return (ERROR);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(atoi(port));
    check_bind = bind(fd, (struct sockaddr *) &server, sizeof(server));
    if (check_bind == -1)
        return (ERROR);
    if (listen(fd, MAX_CONNECTIONS) == -1)
        return (ERROR);
    return (fd);
}

teams_t *init_struct(char *port)
{
    teams_t *teams;

    teams = malloc(sizeof(teams_t));
    if (teams == NULL || atoi(port) == 0)
        return (NULL);
    teams->fds = malloc(sizeof(fd_set_t));
    if (teams->fds == NULL) {
        free(teams);
        return (NULL);
    }
    teams->socket_fd = setup_server(port);
    if (teams->socket_fd == ERROR) {
        free(teams->fds);
        free(teams);
        return (NULL);
    }
    teams->select_ret = 0;
    teams->head = NULL;
    return (teams);
}