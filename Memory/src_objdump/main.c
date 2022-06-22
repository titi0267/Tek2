/*
** EPITECH PROJECT, 2022
** nm_objdump
** File description:
** main
*/

#include "../include/args.h"

int usage(void)
{
    return (ERROR);
}

int free_func(args_t *args)
{
    int z = args->error_file;

    for (int i = 0; i <= args->flag_nbr; i++)
        free(args->flags[i]);
    free(args->flags);
    free(args);
    if (z != 0)
        return (ERROR);
    return (0);
}

int main(int ac, char **av)
{
    args_t *args = malloc(sizeof(args_t));

    if (args == NULL)
        return (ERROR);
    args->flag_nbr = 0;
    args->error_file = 0;
    args->file_nbr = 0;
    if (ac == 1)
        return (usage());
    if (ac > 1) {
        if (parse_args(ac, av, args) == ERROR)
            usage();
    }
    return (free_func(args));
}
