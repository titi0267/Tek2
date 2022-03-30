/*
** EPITECH PROJECT, 2022
** B-PSU-402-STG-4-1-strace-timothe.coniel
** File description:
** main
*/

#pragma once

#include <stdio.h>
#include <string.h>
#include <sys/ptrace.h>
#include <stdlib.h>
#include <unistd.h>

#define ERROR 84
#define TRUE 1
#define FALSE 0

typedef struct strace_s {
    char **envp;
    char **command;
    int is_command;
    int pid;
    int prev_pid;
} strace_t;

int flag_s(void);
int flag_p(int ac, char **av, int i, strace_t *strace);
int no_options(int ac, char **av, int i, strace_t *strace);
int run_file(strace_t *strace);
