/*
** EPITECH PROJECT, 2022
** B-PSU-400-STG-4-1-nmobjdump-timothe.coniel
** File description:
** elf64
*/

#include "../include/nm.h"


int create_list(node_t *front, char *name, int i)
{
    node_t new_node = malloc(sizeof(*new_node));

    if (new_node == NULL)
        return (0);
    new_node->sym = name;
    new_node->sorted = 1;
    new_node->position = i;
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

int get_list_size_sec(node_t list)
{
    int len = 0;

    if (int_list_is_empty(list) == 1)
        return (0);
    for (; list != NULL; list = list->next) {
        printf("pos :%i = %s\n", list->position, list->sym);
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
    new_node->next = (*front);
    (*front) = new_node;
    del_elem_at_position(front, node->position);
    return (1);
}

node_t find_highest(node_t *front)
{
    node_t find_node = (*front);
    node_t node = (*front);

    for (; node->sorted == -1 && node != NULL; node = node->next);
    find_node = node;
    for (; node != NULL; node = node->next) {
        if (strcoll(find_node->sym, node->sym) < 0 && node->sorted != -1)
            find_node = node;
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
            create_list(&list, &(str[section_str[i].st_name]), z);
            z++;
        }
    }
    //printf("Start LIST\n");
    //get_list_size_sec(list);
    reset_positions(&list);
    for (int i = 0; i < get_list_size(list); i++) {
        node_add_front(&list, find_highest(&list));
    }
    //printf("NEW LIST\n");
    //get_list_size_sec(list);
    return (1);
}
