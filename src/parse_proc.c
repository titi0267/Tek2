/*
** EPITECH PROJECT, 2022
** ftrace
** File description:
** parse_proc
*/

#include "ftrace.h"

int nm_bin(ftrace_t *ftrace, nm_t *nm)
{
    Elf64_Ehdr *elf;
    Elf64_Shdr *shdr;
    int fd;
    struct stat buffer;

    UNUSED(table);
    fd = open(ftrace->bin_name, O_RDONLY);
    if (fd == -1)
        return (84);
    fstat(fd, &buffer);
    elf = mmap(NULL, buffer.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    nm->elf = (void *)elf;
    if (elf->e_ident[EI_CLASS] == ELFCLASSNONE)
        return (ERROR);
    if (elf->e_ident[EI_CLASS] == ELFCLASS64) {
        shdr = (Elf64_Shdr *)((void *)elf + elf->e_shoff);
        elf_64_nm(elf, nm, shdr);
    }
    close(fd);
    return (0);
}
