/*
** EPITECH PROJECT, 2022
** teams
** File description:
** setup
*/

#include "../include/teams.h"

int print_error(char *str)
{
    write(1, str, strlen(str));
    return (ERROR);
}

int create_client(char *address, char *port)
{
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in client;
    int size = sizeof(client);
    int check_accept = 0;

    client.sin_family = AF_INET;
    client.sin_addr.s_addr = inet_addr(address);
    client.sin_port = htons(atoi(port));
    check_accept = connect(fd, (struct sockaddr *) &client, size);
    if (check_accept == -1)
        return (print_error("Cannot accept\n"));
    return (fd);
}

client_t *init_struct(char **av)
{
    client_t *client;

    if (atoi(av[2]) == 0)
        return (NULL);
    client = malloc(sizeof(client_t));
    if (client == NULL)
        return (NULL);
    client->socket_fd = create_client(av[1], av[2]);
    if (client->socket_fd == ERROR)
        return (NULL);
    memset(client->pseudo, 0, MAX_NAME_LENGTH);
    client->log_status = NOT_LOGGED;
    return (client);
}