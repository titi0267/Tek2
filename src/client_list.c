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

int new_fd_in_list_back(node_t *front_ptr, int new_client)
{
    node_t new_node = malloc(sizeof(*new_node));
    node_t last_node;

    if (new_node == NULL)
        exit(ERROR_CODE);
    new_node->connection = new_client;
    new_node->next = NULL;
    if (*front_ptr == NULL) {
        (*front_ptr) = new_node;
        return (0);
    }
    last_node = (*front_ptr);
    while (last_node->next != NULL)
        last_node = last_node->next;
    last_node->next = new_node;
    dprintf(new_node->connection, "220\r\n");
    return (0);
}

int add_connection(node_t *list, int new_client)
{
    node_t client = (*list);

    for (; client != NULL; client = client->next) {
        if (client->connection < 0) {
            client->connection = new_client;
            dprintf(client->connection, "220\r\n");
            break;
        }
    }
    return (0);
}
