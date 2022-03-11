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

int free_func(args_t *args)
{
    int z = args->error_file;

    for (int i = 0; i <= args->flag_nbr; i++)
        free(args->flags[i]);
    free(args->flags);
    for (int i = 0; i != args->error_file; i++)
        free(args->file[i]);
    free(args->file);
    free(args);
    if (z != 0)
        return (84);
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
    args->file = malloc(sizeof(char *) * ac);
    if (ac == 1)
        usage();
    if (ac > 1) {
        if (parse_args(ac, av, args) == ERROR)
            usage();
    }
    for (int i = 0; i != args->error_file; i++)
        ERROR_FILE(args->file[i]);
    return (free_func(args));
}
