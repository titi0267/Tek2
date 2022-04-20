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
#include <sys/user.h>
#include "syscall.h"

int print_error(char *what);
char **path_to_array(char *path, char *command);
int fork_and_execve(char **command, char **env);
int ftrace_command(char **command, char **env);
void print_com(struct user_regs_struct regs, long rax);
int path_command(char **command, char **env);
int check_existence(char *command);
int check_abs(char *command);
int parent_process_command(pid_t pid);

#define UNUSED(x) (void)(x)

#define ERROR 84