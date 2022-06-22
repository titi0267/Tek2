/*
** EPITECH PROJECT, 2022
** ftrace
** File description:
** elf64
*/

#include "ftrace.h"

void print_entering(node_t *list)
{
    node_t node = (*list);

    for (; node != NULL; node = node->next) {
        if (node->type == 'T' && strcmp(node->sym, "_init") != 0
        && strcmp(node->sym, "_start") != 0 && strcmp(node->sym, "_fini") != 0) {
            printf("Entering function %s at %#08lx\n", node->sym, node->adress);
            printf("Leaving function %s\n", node->sym);
        }
    }
    UNUSED(table);
}

int elf_64_nm(Elf64_Ehdr *elf, nm_t *nm, Elf64_Shdr *shdr)
{
    Elf64_Sym *sym;
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
    for (int i = 0; i < nm->sym_size; i++) {
        if (sym[i].st_info != STT_FILE && sym[i].st_name != 0) {
            create_list(&list, &(str[sym[i].st_name]), sym[i].st_value);
            print_type(sym[i], shdr, &list);
        }
    }
    print_entering(&list);
    return (0);
}