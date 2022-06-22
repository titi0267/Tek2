/*
** EPITECH PROJECT, 2022
** teams
** File description:
** main
*/

#include "../include/teams.h"

int usage(void)
{
    printf("USAGE: ./myteams_cli ip port\n");
    printf("    ip is the server ip address"
    " on which the server socket listens\n");
    printf("    port is the port number on which the server socket listens\n");
    return (0);
}

int check_args(int ac, char **av)
{
    if (ac == 2) {
        if (strcmp(av[1], "-help") == 0)
            exit(usage());
        return (ERROR);
    }
    if (ac != 3)
        return (ERROR);
    return (0);
}

int main(int ac, char **av)
{
    client_t *client;

    if (check_args(ac, av) == ERROR)
        return (ERROR);
    client = init_struct(av);
    if (client == NULL)
        return (ERROR);
    loop(client);
    return (0);
}
