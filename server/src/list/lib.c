/*
** EPITECH PROJECT, 2022
** teams
** File description:
** list_lib
*/

#include "../../include/teams.h"

void free_list(teams_t *teams)
{
    client_list_t *tmp;

    while (teams->head != NULL) {
        tmp = teams->head;
        teams->head = teams->head->next;
        free(tmp);
    }
}

void remove_in_list(teams_t *teams, int fd)
{
    client_list_t *tmp;
    client_list_t *current = teams->head;

    if (teams->head->fd == fd) {
        tmp = teams->head;
        teams->head = teams->head->next;
        free(tmp);
        return;
    }
    for (; current->next != NULL; current = current->next) {
        if (current->next->fd == fd) {
            tmp = current->next;
            current->next = current->next->next;
            free(tmp);
            break;
        }
    }
}

void dump(teams_t *teams)
{
    client_list_t *loop = teams->head;

    for (; loop != NULL; loop = loop->next)
        printf("%d ", loop->fd);
    printf("\n");
}

void push_back(teams_t *teams, int fd)
{
    client_list_t *new_node = malloc(sizeof(client_list_t));
    client_list_t *end  = teams->head;
    if (!new_node)
        return;
    new_node->fd = fd;
    new_node->message = malloc(sizeof(message_t));
    new_node->next = NULL;
    if (teams->head == NULL) {
        teams->head = new_node;
        return;
    }
    for (; end->next != NULL; end = end->next);
    end->next = new_node;
}

void set_all_fd(teams_t *teams)
{
    client_list_t *loop = teams->head;

    for (; loop != NULL; loop = loop->next) {
        FD_SET(loop->fd, &teams->fds->read);
        FD_SET(loop->fd, &teams->fds->write);
        FD_SET(loop->fd, &teams->fds->exeptions);
    }
}