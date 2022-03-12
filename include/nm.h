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

#define ERROR_FILE(file_name) printf("objdump: '%s': No such file\n", file_name);

#define ERROR 84

typedef struct nm_s
{
    char **flags;
    int file_type;
    int flag_nbr;
    void *elf;
    int error_file;
    int file_nbr;
    char **file;
    size_t size;
    char *str;
    Elf64_Sym *section_str;
} nm_t;

typedef struct list_s
{
    char *sym;
    int sorted;
    int position;
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
char *strdup(const char *c);