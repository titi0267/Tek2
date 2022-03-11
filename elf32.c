/*
** EPITECH PROJECT, 2022
** B-PSU-400-STG-4-1-nmobjdump-timothe.coniel
** File description:
** elf32
*/

#include "args.h"

int elf_32(struct stat buffer, int open_ret, args_t *args)
{
    Elf32_Ehdr *elf;

    elf = mmap(NULL, buffer.st_size, PROT_READ, MAP_PRIVATE, open_ret, 0);
    args->elf = elf;
    printf("\n%s:     file format elf32", args->flags[0]);
    if (elf->e_machine == EM_386)
        printf("-386\narchitecture: i386");
    else if (elf->e_machine == EM_X86_64)
        printf("-x86-64\narchitecture: i386:x86-64");
    if (args->file_type == OBJECT) {
        printf("0x00000011:\nHAS_RELOC, HAS_SYMS\nstart address 0x0000000000000000\n\n");
    }
    else if (args->file_type == BIN) {
        printf("0x00000115:\n");
    } else {
        printf("?:\n");
    }
    return (0);
}
