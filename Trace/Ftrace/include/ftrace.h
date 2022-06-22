/*
** EPITECH PROJECT, 2022
** B-PSU-402-STG-4-1-strace-ludovic.sutter
** File description:
** ftrace
*/

#pragma once

#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/ptrace.h>
#include <sys/reg.h>
#include <fcntl.h>
#include <sys/user.h>
#include <elf.h>
#include <libelf.h>
#include <gelf.h>
#include <sys/mman.h>
#include "syscall.h"

typedef struct ftrace_s {
    char *bin_name;
} ftrace_t;


typedef struct list_s {
    char *sym;
    char *sym_clear;
    char type;
    Elf64_Addr adress;
    struct list_s *next;
} list_t;

typedef list_t *node_t;

typedef struct nm_s {
    char **flags;
    int file_type;
    int flag_nbr;
    void *elf;
    int error_file;
    int file_nbr;
    size_t size;
    char *str;
    Elf64_Sym *section_str;
    int sym_size;
} nm_t;

int print_error(char *what);
char **path_to_array(char *path, char *command);
int fork_and_execve(char **command, char **env, ftrace_t *ftrace);
int ftrace_command(char **command, char **env, ftrace_t *ftrace);
void print_com(struct user_regs_struct regs, long rax);
int path_command(char **command, char **env, ftrace_t *ftrace);
int check_existence(char *command);
int check_abs(char *command);
int parent_process_command(pid_t pid, ftrace_t *ftrace);
int open_proc(pid_t pid, ftrace_t *ftrace);
void print_type(Elf64_Sym sym, Elf64_Shdr *shdr, node_t *front);
int elf_64_nm(Elf64_Ehdr *elf, nm_t *nm, Elf64_Shdr *shdr);
int print_list(node_t list);
int create_list(node_t *front, char *name, Elf64_Addr addr);
int nm_bin(ftrace_t *ftrace, nm_t *nm);
char *my_strcat(char *begin, char *end);
char *my_getchar(int nbr);

#define UNUSED(x) (void)(x)

#define ERROR 84