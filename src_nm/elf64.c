/*
** EPITECH PROJECT, 2022
** B-PSU-400-STG-4-1-nmobjdump-timothe.coniel
** File description:
** elf64
*/

#include "../include/nm.h"

int my_strcmp(const char *s1, const char *s2)
{
    int a = strlen(s1);
    int b = strlen(s2);
    int c;

    c = (strlen(s1) < strlen(s2)) ? b : a;
    for (int i = 0; i != c; i++) {
        if (s1[i] > s2[i]) {
            if (s2[i] == '@')
                return (-1);
            return (1);
        }
        else if (s1[i] < s2[i]) {
            if (s1[i] == '@' || s2[i] == '@')
                return (1);
            return (-1);
        }
    }
    return (0);
}

node_t find_highest(node_t *front)
{
    node_t find_node = (*front);
    node_t node = (*front);
    int b = 0;

    for (; node->sorted == -1 && node != NULL; node = node->next);
    find_node = node;
    for (; node != NULL; node = node->next) {
        b = my_strcmp(find_node->sym_clear, node->sym_clear);
        if (b < 0 && node->sorted != -1) {
            find_node = node;
        } else if (b == 0 && node->sorted != -1) {
            if (my_strcmp(find_node->sym, node->sym) < 0)
                find_node = node;
        }
    }
    return (find_node);
}

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
