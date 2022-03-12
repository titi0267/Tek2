/*
** EPITECH PROJECT, 2022
** B-PSU-400-STG-4-1-nmobjdump-timothe.coniel
** File description:
** elf64
*/

#include "../include/nm.h"

void print_type(Elf64_Sym sym, Elf64_Shdr *shdr, node_t *front, char *str)
{
    node_t node = (*front);
    char c;

    if (ELF64_ST_BIND(sym.st_info) == STB_GNU_UNIQUE)
        node->type = 'u';
    else if (ELF64_ST_BIND(sym.st_info) == STB_WEAK) {
        node->type = 'W';
        if (sym.st_shndx == SHN_UNDEF)
            node->type = 'w';
    } else if (ELF64_ST_BIND(sym.st_info) == STB_WEAK && ELF64_ST_TYPE(sym.st_info) == STT_OBJECT) {
        node->type = 'V';
      if (sym.st_shndx == SHN_UNDEF)
        node->type = 'v';
    }
    else if (sym.st_shndx == SHN_UNDEF)
        node->type = 'U';
    else if (sym.st_shndx == SHN_ABS)
        node->type = 'A';
    else if (sym.st_shndx == SHN_COMMON)
        node->type = 'C';
    else if (shdr[sym.st_shndx].sh_type == SHT_NOBITS
       && shdr[sym.st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE))
        node->type = 'B';
    else if (shdr[sym.st_shndx].sh_type == SHT_PROGBITS
       && shdr[sym.st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE))
        node->type = 'D';
    else if (shdr[sym.st_shndx].sh_type == SHT_PROGBITS
       && shdr[sym.st_shndx].sh_flags == (SHF_ALLOC | SHF_EXECINSTR))
        node->type = 'T';
    else if (shdr[sym.st_shndx].sh_type == SHT_DYNAMIC)
        node->type = 'D';
    else if (shdr[sym.st_shndx].sh_type == SHT_PROGBITS
       && shdr[sym.st_shndx].sh_flags == SHF_ALLOC)
        node->type = 'R';
    else if (shdr[sym.st_shndx].sh_type == SHT_NOTE)
        node->type = 'R';
    else {
        node->type = 'D';
    }
    if (ELF64_ST_BIND(sym.st_info) == STB_LOCAL && node->type != '?')
        node->type += 32;
}

int create_list(node_t *front, char *name, int i, Elf64_Addr addr)
{
    node_t new_node = malloc(sizeof(*new_node));

    if (new_node == NULL)
        return (0);
    new_node->sym = name;
    new_node->sorted = 1;
    new_node->position = i;
    new_node->adress = addr;
    new_node->next = (*front);
    (*front) = new_node;
    return (1);
}

int int_list_is_empty(node_t list)
{
    if (list == NULL)
        return (1);
    return (0);
}

int get_list_size(node_t list)
{
    int len = 0;

    if (int_list_is_empty(list) == 1)
        return (0);
    for (; list != NULL; list = list->next) {
        len++;
    }
    return (len);
}

int get_list_third(node_t list)
{
    int len = 0;

    if (int_list_is_empty(list) == 1)
        return (0);
    for (; list != NULL; list = list->next) {
        if (list->adress == NULL)
            printf("                 %c %s\n", list->type, list->sym);
        else
            printf("%016x %c %s\n", list->adress, list->type, list->sym);
        len++;
    }
    return (len);
}

int get_list_size_sec(node_t list)
{
    int len = 0;
    int i = 0;

    if (int_list_is_empty(list) == 1)
        return (0);
    for (; list != NULL; list = list->next) {
        list->sym_clear = malloc(sizeof(char) * strlen(list->sym) + 1);
        for (int z = 0, i = 0; list->sym[i] != '\0'; i++) {
            if (list->sym[i] != '_') {
                list->sym_clear[z] = list->sym[i];
                if (list->sym_clear[z] >= 65 && list->sym_clear[z] <= 90)
                    list->sym_clear[z] += 32;
                z++;
            }
        }
        //printf("%s\n", list->sym_clear);
        //for (int y = i, z = 0; list->sym[y] != '\0'; y++, z++)
            //list->sym_clear[z] = list->sym[y];
        //printf("%s\n", list->sym_clear);
        len++;
    }
    return (len);
}

void reset_positions(node_t *front)
{
    node_t list = (*front);

    for (int i = 0; list != NULL; list = list->next, i++) {
        list->position = i;
    }
}

int del_elem_at_position(node_t *front_ptr, unsigned int position)
{
    node_t tmp = (*front_ptr);
    node_t node;

    if (front_ptr == NULL)
        return (0);
    //if (position == 0)
      //  return (int_list_del_elem_at_front(front_ptr));
    for (; tmp->position != position - 1 && tmp != NULL; tmp = tmp->next);
    if (tmp == NULL || tmp->next == NULL)
        return (0);
    node = tmp->next->next;
    free(tmp->next);
    tmp->next = node;
    reset_positions(front_ptr);
    return (1);
}

int node_add_front(node_t *front, node_t node)
{
    node_t new_node = malloc(sizeof(*new_node));

    if (new_node == NULL)
        return (0);
    new_node->sym = node->sym;
    new_node->sorted = -1;
    new_node->position = 0;
    new_node->type = node->type;
    new_node->sym_clear = node->sym_clear;
    new_node->adress = node->adress;
    new_node->next = (*front);
    (*front) = new_node;
    del_elem_at_position(front, node->position);
    return (1);
}

int my_strcmp(const char *s1, const char *s2)
{
    int a = strlen(s1);
    int b = strlen(s2);
    int c;

    c = (strlen(s1) < strlen(s2)) ? b : a;
    for (int i = 0; i != c; i++) {
        if (s1[i] > s2[i]) {
            if (s1[i] == '@')
                return (1);
            if (s2[i] == '@')
                return (-1);
            return (1);
        }
        else if (s1[i] < s2[i]) {
            if (s1[i] == '@')
                return (1);
            if (s2[i] == '@')
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


void print_section_content(Elf64_Shdr *shdr, nm_t *nm, int i)
{
    Elf64_Ehdr *elf = (Elf64_Ehdr *)nm->elf;
    nm->section_str = (Elf64_Sym *)((char *)elf + shdr[i].sh_offset);
 
    nm->str = (elf + (shdr[shdr[i].sh_link].sh_offset));
    nm->size = shdr[i].sh_size / shdr[i].sh_entsize;
}

void list_clear(node_t *front_ptr)
{
    node_t node = *front_ptr;
    node_t next;

    while (node != NULL) {
        next = node->next;
        free(node);
        node = next;
    }
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
    //printf("Start LIST\n");
    //get_list_size_sec(list);
    reset_positions(&list);
    get_list_size_sec(list);
    for (int i = 0; i < get_list_size(list); i++) {
        node_add_front(&list, find_highest(&list));
    }
    get_list_third(list);
    //printf("NEW LIST\n");
    list_clear(&list);
    return (1);
}
