/*
** EPITECH PROJECT, 2022
** strace
** File description:
** fork_and_execve
*/

#include "ftrace.h"

int child_process_command(char **command, char **env, ftrace_t *ftrace)
{
    UNUSED(table);
    ptrace(PTRACE_TRACEME, 0, NULL, NULL);
    kill(getpid(), SIGSTOP);
    return (execve(ftrace->bin_name, command, env));
}

int parent_process_command(pid_t pid, ftrace_t *ftrace)
{
    int status = 0;
    long opcode = 0;
    struct user_regs_struct regs;
    long retval = 0;
    int i = 0;

    waitpid(pid, &status, 0);
    while (WIFSTOPPED(status)) {
        ptrace(PTRACE_GETREGS, pid, NULL, &regs);
        if ((opcode = ptrace(PTRACE_PEEKTEXT, pid, regs.rip, 0)) == -1)
            return (print_error("Error PTRACE\n"));
        //printf("adress = %llx\n", regs.rip);
        if ((unsigned int)(opcode | 0x00ffffff) == (unsigned int)0xE8ffffff) {
            for (int d = 0; ftrace->maps[d].last_array != -1; d++)
                nm_bin(ftrace, d);
        }
        if ((unsigned int)(opcode | 0xffff0000) == (unsigned int)0xffff050f) {
            ptrace(PTRACE_SINGLESTEP, pid, 0, 0);
            waitpid(pid, &status, 0);
            retval = ptrace(PTRACE_PEEKUSER, pid, sizeof(long)*RAX);
            print_com(regs, retval);
            if (i == 0 || strcmp(table[regs.rax].name, "execve") == 0 || strcmp(table[regs.rax].name, "brk") == 0 || strcmp(table[regs.rax].name, "mmap") == 0 || strcmp(table[regs.rax].name, "munmap") == 0)
                open_proc(pid, ftrace);
            i++;
        }
        ptrace(PTRACE_SINGLESTEP, pid, 0, 0);
        waitpid(pid, &status, 0);
    }fprintf(stderr, "+++ exited with %i +++\n", status);
    return (0);
}

int fork_and_execve(char **command, char **env, ftrace_t *ftrace)
{
    pid_t pid;

    ftrace->bin_name = malloc(sizeof(char) * strlen(command[0]) + 1);
    strcpy(ftrace->bin_name, command[0]);
    if ((pid = fork()) == -1)
        return (print_error("fork() error\n"));
    else if (pid == 0)
        return (child_process_command(command, env, ftrace));
    return (parent_process_command(pid, ftrace));
}