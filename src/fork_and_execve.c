/*
** EPITECH PROJECT, 2022
** strace
** File description:
** fork_and_execve
*/

#include "ftrace.h"

int child_process_command(char **command, char **env)
{
    UNUSED(table);
    ptrace(PTRACE_TRACEME, 0, NULL, NULL);
    kill(getpid(), SIGSTOP);
    return (execve(command[0], command, env));
}

int parent_process_command(pid_t pid)
{
    int status = 0;
    long opcode = 0;
    struct user_regs_struct regs;
    long retval = 0;

    waitpid(pid, &status, 0);
    while (WIFSTOPPED(status)) {
        ptrace(PTRACE_GETREGS, pid, NULL, &regs);
        if ((opcode = ptrace(PTRACE_PEEKTEXT, pid, regs.rip, 0)) == -1)
            return (print_error("Error PTRACE\n"));
        if ((unsigned int)(opcode | 0x00ffffff) == (unsigned int)0xE8ffffff)
            open_proc(pid);
        if ((unsigned int)(opcode | 0xffff0000) == (unsigned int)0xffff050f) {
            ptrace(PTRACE_SINGLESTEP, pid, 0, 0);
            waitpid(pid, &status, 0);
            retval = ptrace(PTRACE_PEEKUSER, pid, sizeof(long)*RAX);
            print_com(regs, retval);
        }ptrace(PTRACE_SINGLESTEP, pid, 0, 0);
        waitpid(pid, &status, 0);
    }fprintf(stderr, "+++ exited with %i +++\n", status);
    return (0);
}

int fork_and_execve(char **command, char **env)
{
    pid_t pid;

    if ((pid = fork()) == -1)
        return (print_error("fork() error\n"));
    else if (pid == 0)
        return (child_process_command(command, env));
    return (parent_process_command(pid));
}