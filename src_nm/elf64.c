/*
** EPITECH PROJECT, 2022
** B-PSU-400-STG-4-1-nmobjdump-timothe.coniel
** File description:
** elf64
*/

#include "../include/nm.h"

void sort_print_nm(nm_t *nm, node_t list)
{
    reset_positions(&list);
    format_str(list);
    for (int i = 0; i < get_list_size(list); i++) {
        node_add_front(&list, find_highest(&list));
    }
    nm_output(list, nm);
    list_clear(&list);
}

int elf_64_nm(Elf64_Ehdr *elf, nm_t *nm)
{
    Elf64_Shdr *shdr = (Elf64_Shdr *)((void *)elf + elf->e_shoff);
    Elf64_Sym *sym;
    shdr->sh_flags
    char *str;
    node_t list = NULL;

    for (int i = 0; i < elf->e_shnum; i++) {
        if (shdr[i].sh_type == SHT_SYMTAB) {
            sym = (Elf64_Sym *)((void *)elf + shdr[i].sh_offset);
            str = (void *)elf + shdr[shdr[i].sh_link].sh_offset;
            nm->sym_size = shdr[i].sh_size / shdr[i].sh_entsize;
            break;
        }
    }
    for (int i = 0, z = 0; i < nm->sym_size; i++) {
        if (sym[i].st_info != STT_FILE && sym[i].st_name != 0) {
            create_list(&list, &(str[sym[i].st_name]), z, sym[i].st_value);
            print_type(sym[i], shdr, &list, &(str[sym[i].st_name]));
            z++;
        }
    }
    sort_print_nm(nm, list);
}
