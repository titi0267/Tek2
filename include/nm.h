/*
** EPITECH PROJECT, 2022
** B-PSU-400-STG-4-1-nmobjdump-timothe.coniel
** File description:
** nm
*/

#pragma once
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <elf.h>
#include <sys/mman.h>
#include <sys/stat.h>

#define ERROR_FILE(name) fprintf(stderr, "nm: '%s': No such file\n", name);

#define ERROR 84

typedef struct nm_s
{
    char **flags;
    int file_type;
    int flag_nbr;
    void *elf;
    int error_file;
    int file_nbr;
    size_t size;
    char *str;
    Elf64_Sym *section_str;
    int multiple_files;
    int sym_size;
} nm_t;

typedef struct list_s
{
    char *sym;
    char *sym_clear;
    int sorted;
    int position;
    char type;
    Elf64_Addr adress;
    struct list_s *next;
} list_t;

typedef list_t *node_t;

enum NM {
    OBJ,
    SHL,
    BN
};

int elf_64_nm(Elf64_Ehdr *elf, nm_t *nm);
int elf_32_nm(struct stat buffer, int open_ret, nm_t *nm);
int parse_args(int ac, char **av, nm_t *nm);
void print_type(Elf64_Sym sym, Elf64_Shdr *shdr, node_t *front, char *str);
void format_str(node_t list);
int create_list(node_t *front, char *name, int i, Elf64_Addr addr);
node_t find_highest(node_t *front);
void list_clear(node_t *front_ptr);
int node_add_front(node_t *front, node_t node);
int del_elem_at_position(node_t *front_ptr, unsigned int position);
int del_elem_at_front(node_t *front_ptr);
void nm_output(node_t list, nm_t *nm);
int get_list_size(node_t list);
void reset_positions(node_t *front);
int list_is_empty(node_t list);
int file_error(nm_t *nm);
void store_flags(int i, char **av, nm_t *nm);