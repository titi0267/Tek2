/*
** EPITECH PROJECT, 2022
** teams
** File description:
** main
*/

#include "../include/teams.h"

void usage(void)
{
    printf("USAGE: ./myteams_server port\n\n");
    printf("    port is the port number on which the server socket listens.\n");
}

int handle_args(int ac, char **av)
{
    if (ac != 2)
        return (ERROR);
    if (strcmp(av[1], "-help") == 0) {
        usage();
        return (ERROR);
    }
    return (0);
}

int main(int ac, char **av)
{
    teams_t *teams;

    if (handle_args(ac, av) == ERROR)
        return (ERROR);
    teams = init_struct(av[1]);
    if (teams == NULL)
        return (ERROR);
    loop(teams);
    return (0);
}