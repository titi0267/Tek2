/*
** EPITECH PROJECT, 2022
** B-PSU-400-STG-4-1-nmobjdump-timothe.coniel
** File description:
** args
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

#define ERROR 84
#define ERROR_FILE(name) fprintf(stderr, "objdump: '%s': No such file\n", name);

typedef struct file_s
{
    char **flags;
    int file_type;
    int flag_nbr;
    void *elf;
    int error_file;
    int file_nbr;
} args_t;

enum File {
    OBJECT,
    SHAREDL,
    BIN
};

int parse_args(int ac, char **av, args_t *args);
int use_mmap(int open_ret, args_t *args, struct stat buffer);
int store_file(args_t *args, char *av);
int use_mmap(int open_ret, args_t *args, struct stat buffer);
void print_section_content(int z, Elf64_Shdr shdr, char *str, args_t *args);
int print_section_name(char *section[], int z, Elf64_Shdr shdr, char *str);
void select_section(char *str, Elf64_Shdr shdr, args_t *args, enum File type);
int elf_64(Elf64_Ehdr *elf, args_t *args);
int elf_32(struct stat buffer, int open_ret, args_t *args);
void store_flags(int i, args_t *args, char **av);
int print_section_name_min(char *section[], int z, Elf32_Shdr shdr, char *str);
void print_section_content_min(int z, Elf32_Shdr shdr, char *str, args_t *args);
