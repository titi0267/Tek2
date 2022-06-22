/*
** EPITECH PROJECT, 2022
** B-PSU-400-STG-4-1-nmobjdump-timothe.coniel
** File description:
** parsing
*/

#include "../include/nm.h"

int use_mmap(int open_ret, nm_t *nm, struct stat buffer)
{
    Elf64_Ehdr *elf;
    int is_64 = 0;
    int status;

    elf = mmap(NULL, buffer.st_size, PROT_READ, MAP_PRIVATE, open_ret, 0);
    nm->elf = (void *)elf;
    if (elf == MAP_FAILED || elf->e_ident[EI_CLASS] == ELFCLASSNONE ||
        (elf->e_ident[EI_CLASS] != ELFCLASS32 &&
        elf->e_ident[EI_CLASS] != ELFCLASS64)) {
        printf("nm : %s: file format not recognized\n",
            nm->flags[nm->flag_nbr]);
        return (ERROR);
    }
    if (nm->multiple_files == 1)
        printf("\n%s:\n", nm->flags[0]);
    (elf->e_ident[EI_CLASS] == ELFCLASS64) ?
        elf_64_nm(elf, nm) : elf_32_nm(buffer, open_ret, nm);
    return (0);
}

int open_file(nm_t *nm, char *av)
{
    int open_ret = 0;
    int z = 0;

    if (av[0] != '-') {
        open_ret = open(av, O_RDONLY);
        if (nm->file_nbr != 0)
            free(nm->flags[0]);
        nm->flags[0] = malloc(strlen(av) * sizeof(char) + 2);
        if (nm->flags[0] == NULL)
            exit (84);
        nm->file_nbr += 1;
        for (; av[z] != '\0'; z++)
            nm->flags[0][z] = av[z];
        nm->flags[0][z] = '\0';
    }
    if (open_ret == -1) {
        file_error(nm);
        return (-1);
    }
    return (open_ret);
}

int store_file(nm_t *nm, char *av)
{
    int open_ret = 0;
    int status;
    struct stat buffer;

    open_ret = open_file(nm, av);
    if (open_ret != 0 && open_ret != -1) {
        if (av[strlen(av) - 2] == '.' && av[strlen(av) - 1] == 'o')
            nm->file_type = OBJ;
        else if (strlen(av) >= 3 && av[strlen(av) - 3] == '.'
            && av[strlen(av) - 2] == 's' && av[strlen(av) - 1] == 'o')
            nm->file_type = SHL;
        else
            nm->file_type = BN;
        status = fstat(open_ret, &buffer);
        use_mmap(open_ret, nm, buffer);
    }
    return (open_ret);
}

int store_args(int ac, char **av, int i, nm_t *nm)
{
    int b = 0;

    if (ac == 1)
        b = store_file(nm, "a.out");
    else
        b = store_file(nm, av[i]);
    if (b == ERROR)
        return (ERROR);
    else if (b == 0) {
        nm->flags[i] = malloc(strlen(av[i]) * sizeof(char) + 1);
        store_flags(i, av, nm);
        nm->flag_nbr += 1;
    }
    return (0);
}

int parse_args(int ac, char **av, nm_t *nm)
{
    int b = 0;
    int i = 1;

    nm->flags = malloc(sizeof(char *) * (ac + 1));
    if (nm->flags == NULL)
        return (ERROR);
    nm->multiple_files = multiple_files(ac, av);
    if (ac == 1)
        i = 0;
    for (; i < ac; i++) {
        if (store_args(ac, av, i, nm) == ERROR)
            return (ERROR);
    }
    return (0);
}
