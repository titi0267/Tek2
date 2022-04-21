/*
** EPITECH PROJECT, 2022
** ftp
** File description:
** parse_args
*/

#include "../include/main_struct.h"
#include "../include/prototype.h"

int usage()
{
    printf("USAGE: ./myftp port path\n");
    printf("       port is the port number on which the ");
    printf("server socket listens\n");
    printf("       path is the path to the home directory ");
    printf("for the Anonymous user\n");
    return (ERROR_CODE);
}

int store_args(main_t *_main, char **av)
{
    for (int i = 0; av[1][i] != 0; i++) {
        if (av[1][i] > 57 || av[1][i] < 48) {
            fprintf(stderr, ERROR_PORT, av[1]);
            return (ERROR_CODE);
        }
    }
    _main->port = atoi(av[1]);
    _main->path = av[2];
    return (0);
}

int parse_args(int ac, char **av)
{
    main_t *_main;

    if (ac == 2 && strcmp(av[1], "-help") == 0)
        return (usage());
    if (ac != 3)
        return (ERROR_CODE);
    _main = malloc(sizeof(main_t));
    if (_main == NULL)
        return (ERROR_CODE);
    if (store_args(_main, av) == ERROR_CODE || init_server(_main) == ERROR_CODE)
        return (ERROR_CODE);
    return (0);
}