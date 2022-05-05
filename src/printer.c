/*
** EPITECH PROJECT, 2022
** strace
** File description:
** printer
*/

#include "ftrace.h"

static int i = 0;
void print_com(struct user_regs_struct regs, long rax)
{
    unsigned long long paramArray[] = {regs.rdi, regs.rsi,
    regs.rdx, regs.r10, regs.r8, regs.r9};

    i++;
    //printf("sys = %i\n", i);
    fprintf(stderr, "Syscall %s(", table[regs.rax].name);
    for (int i = 0; i < table[regs.rax].nb_arg; i++)
        fprintf(stderr, i == table[regs.rax].nb_arg - 1 ?
        "%#llx" : "%#llx, ", paramArray[i]);
    fprintf(stderr, ") = %#lx\n", rax);
}