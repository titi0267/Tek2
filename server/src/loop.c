/*
** EPITECH PROJECT, 2022
** teams
** File description:
** main
*/

#include "../include/teams.h"
#include <time.h>
#include <signal.h>

static int isRunning = 1;

void command_loop(teams_t *teams)
{
    client_list_t *fd_node = teams->head;
    int read_ret = 0;

    for (; fd_node != NULL; fd_node = fd_node->next) {
        if (!FD_ISSET(fd_node->fd, &teams->fds->read))
            continue;
        read_ret = read(fd_node->fd, fd_node->message, sizeof(message_t));
        if (read_ret <= 0) {
            close(fd_node->fd);
            remove_in_list(teams, fd_node->fd);
            break;
        }
        memset(fd_node->message, 0, sizeof(message_t));
    }
}

void sigintHandler(int sig_num)
{
    UNUSED(sig_num);
    isRunning = 0;
}

void loop_accept(teams_t *teams)
{
    int new_fd = 0;
    struct sockaddr_in client;
    unsigned int len = 0;

    if (FD_ISSET(teams->socket_fd, &teams->fds->read)) {
        new_fd = accept(teams->socket_fd, (struct sockaddr *) &client, &len);
        if (new_fd >= 0)
            push_back(teams, new_fd);
        if (teams->select_ret == 1)
            return;
    }
    command_loop(teams);
}

void clear_fds(teams_t *teams)
{
    FD_ZERO(&teams->fds->read);
    FD_ZERO(&teams->fds->write);
    FD_ZERO(&teams->fds->exeptions);
    FD_SET(teams->socket_fd, &teams->fds->read);
    FD_SET(teams->socket_fd, &teams->fds->write);
    FD_SET(teams->socket_fd, &teams->fds->exeptions);
}

void loop(teams_t *teams)
{
    signal(SIGINT, sigintHandler);

    while (isRunning) {
        clear_fds(teams);
        set_all_fd(teams);
        teams->select_ret = select(FD_SETSIZE, &teams->fds->read,
        &teams->fds->write,  &teams->fds->exeptions, NULL);
        if (teams->select_ret >= 0)
            loop_accept(teams);
    }
    free_all(teams);
}