/*
** EPITECH PROJECT, 2022
** ftp
** File description:
** client_list
*/

#include "../include/ftp.h"
#include "../include/prototype.h"

int new_fd_in_list(node_t *front, int connection)
{
    node_t new_node = malloc(sizeof(*new_node));

    if (new_node == NULL)
        return (0);
    new_node->connection = connection;
    new_node->next = (*front);
    (*front) = new_node;
    return (1);
}

int new_fd_in_list_back(node_t *front_ptr, int new_client, main_t *_main)
{
    node_t new_node = malloc(sizeof(*new_node));
    node_t last_node = (*front_ptr);

    if (new_node == NULL)
        exit(ERROR_CODE);
    new_node->connection = new_client;
    new_node->logged_in = 0;
    new_node->path = realpath(_main->path, NULL);
    new_node->next = NULL;
    if (*front_ptr == NULL) {
        (*front_ptr) = new_node;
        return (0);
    }
    for (; last_node->next; last_node = last_node->next);
    last_node->next = new_node;
    dprintf(new_node->connection, "220 Service ready for new user.\r\n");
    return (0);
}

int delete_fd(node_t *front_ptr, int connection)
{
    node_t tmp = (*front_ptr);
    node_t node;

    if (front_ptr == NULL)
        return (0);
    for (; tmp->next->connection != connection && tmp != NULL; tmp = tmp->next);
    if (tmp == NULL || tmp->next == NULL)
        return (0);
    node = tmp->next->next;
    free(tmp->next);
    tmp->next = node;
    return (1);
}
