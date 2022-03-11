/*
** EPITECH PROJECT, 2022
** nm_objdump
** File description:
** main
*/

#include "args.h"

void usage()
{
    printf("Usage :\n");
}

void free_func(args_t *args)
{
    for (int i = 0; i < args->flag_nbr; i++) {
        free(args->flags[i]);
    }
    free(args->flags);
    free(args);
}

int main(int ac, char **av)
{
    args_t *args = malloc(sizeof(args_t));

    if (args == NULL)
        return (ERROR);
    args->flag_nbr = 0;
    args->error_file = 0;
    if (ac == 1)
        usage();
    if (ac > 1) {
        if (parse_args(ac, av, args) == ERROR)
            usage();
    }
    if (args->error_file == ERROR) {
        ERROR_FILE(args->flags[0]);
        return (84);
    }
    free_func(args);
}
