/*
** EPITECH PROJECT, 2022
** B-PSU-400-STG-4-1-nmobjdump-timothe.coniel
** File description:
** parsing
*/

#include "../include/args.h"

int use_mmap(int open_ret, args_t *args, struct stat buffer)
{
    Elf64_Ehdr *elf;
    int is_64 = 0;
    int status;

    elf = mmap(NULL, buffer.st_size, PROT_READ, MAP_PRIVATE, open_ret, 0);
    if (elf->e_ident[EI_CLASS] == ELFCLASSNONE)
        return (ERROR);
    (elf->e_ident[EI_CLASS] == ELFCLASS64) ?
        elf_64(elf, args) : elf_32(buffer, open_ret, args);
    return (0);
}

int parse_args(int ac, char **av, args_t *args)
{
    int b = 0;

    args->flags = malloc(sizeof(char*) * (ac + 1));
    if (args->flags == NULL)
        return (ERROR);
    for (int i = 1; i < ac; i++) {
        b = store_file(args, av[i]);
        if (b == ERROR)
            return (ERROR);
        else if (b == 0) {
            args->flags[i] = malloc(strlen(av[i]) * sizeof(char) + 1);
            for (int t = 0; av[i][t] != '\0'; t++)
                args->flags[i][t] = av[i][t];
            args->flag_nbr += 1;
        }
    }
    return (0);
}

int file_error(args_t *args)
{
    args->file[args->error_file] = strdup(args->flags[0]);
    args->error_file += 1;
    return (-1);
}

int open_file(args_t *args, char *av)
{
    int open_ret = 0;
    int z = 0;

    if (av[0] != '-') {
        open_ret = open(av, O_RDONLY);
        if (args->file_nbr != 0)
            free(args->flags[0]);
        args->flags[0] = malloc(strlen(av) * sizeof(char) + 2);
        if (args->flags[0] == NULL)
            exit (84);
        args->file_nbr += 1;
        for (; av[z] != '\0'; z++)
            args->flags[0][z] = av[z];
        args->flags[0][z] = '\0';
    }
    if (open_ret == -1) {
        file_error(args);
        return (-1);
    }
    return (open_ret);
}

int store_file(args_t *args, char *av)
{
    int open_ret = 0;
    int status;
    struct stat buffer;

    open_ret = open_file(args, av);
    if (open_ret != 0 && open_ret != -1) {
        if (av[strlen(av) - 2] == '.' && av[strlen(av) - 1] == 'o')
            args->file_type = OBJECT;
        else if (strlen(av) >= 3 && av[strlen(av) - 3] == '.' && av[strlen(av) - 2]
            == 's' && av[strlen(av) - 1] == 'o')
            args->file_type = SHAREDL;
        else
            args->file_type = BIN;
        status = fstat(open_ret, &buffer);
        use_mmap(open_ret, args, buffer);
    }
    return (open_ret);
}
