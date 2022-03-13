/*
** EPITECH PROJECT, 2022
** B-PSU-400-STG-4-1-nmobjdump-timothe.coniel
** File description:
** elf64
*/

#include "../include/nm.h"

int elf_64_nm(Elf64_Ehdr *elf, nm_t *nm)
{
    Elf64_Shdr *shdr = (Elf64_Shdr *)((void *)elf + elf->e_shoff);
    Elf64_Sym *section_str;
    char *str;
    int size;
    node_t list = NULL;

    for (int i = 0; i < elf->e_shnum; i++) {
        if (shdr[i].sh_type == SHT_SYMTAB) {
            section_str = (Elf64_Sym *)((void *)elf + shdr[i].sh_offset);
            str = (void *)elf + shdr[shdr[i].sh_link].sh_offset;
            size = shdr[i].sh_size / shdr[i].sh_entsize;
            break;
        }
    }
    for (int i = 0, z = 0; i < size; i++) {
        if (section_str[i].st_info != STT_FILE && section_str[i].st_name != 0) {
            create_list(&list, &(str[section_str[i].st_name]), z, section_str[i].st_value);
            print_type(section_str[i], shdr, &list, &(str[section_str[i].st_name]));
            z++;
        }
    }
    reset_positions(&list);
    format_str(list);
    for (int i = 0; i < get_list_size(list); i++) {
        node_add_front(&list, find_highest(&list));
    }
    nm_output(list, nm);
    list_clear(&list);
    return (1);
}
