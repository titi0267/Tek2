/*
** EPITECH PROJECT, 2022
** B-PSU-402-STG-4-1-strace-timothe.coniel
** File description:
** no_options
*/

#include "../include/main.h"

int no_options(int ac, char **av, int i, strace_t *strace)
{
    int b = 0;

    strace->is_command = TRUE;
    if ((strace->command = malloc(sizeof(char *) *
        ((ac - i) + 1))) == NULL)
        exit(ERROR);
    for (; i < ac; i++, b++) {
        if ((strace->command[b] = malloc(sizeof(char) *
            (strlen(av[i]) + 1))) == NULL)
            exit(ERROR);
        strcpy(strace->command[b], av[i]);
    }
    strace->command[b] = NULL;
    run_command(strace);
    return (0);
}

int wait_for_syscall(strace_t *strace)
{
    int status;

    while (1) {
        ptrace(PTRACE_SINGLESTEP, strace->prev_pid, 0, 0);
        waitpid(strace->prev_pid, &status, 0);
        if (WIFSTOPPED(status) && WSTOPSIG(status) & 0x80)
            return (0);
        if (WIFEXITED(status))
            return (1);
    }
    return (0);
}

void exec_ptrace(strace_t *strace)
{
    int status, syscall, retval;

    waitpid(strace->prev_pid, &status, 0);
    ptrace(PTRACE_SETOPTIONS, strace->prev_pid, 0, PTRACE_O_TRACESYSGOOD);
    while(1) {
        if (wait_for_syscall(strace) != 0)
            break;
        syscall = ptrace(PTRACE_PEEKUSER, strace->prev_pid,
            sizeof(long) * ORIG_RAX);
        printf("syscall(%d) = ", syscall);
        if (wait_for_syscall(strace) != 0)
            break;
        retval = ptrace(PTRACE_PEEKUSER, strace->prev_pid,
            sizeof(long) * RAX);
        printf("%d\n", retval);
    }
}

int run_command(strace_t *strace)
{
    int status;

    if ((strace->prev_pid = fork()) == -1) {
        return (-1);
    } else if (strace->prev_pid == 0) {
        ptrace(PTRACE_TRACEME);
        kill(getpid(), SIGSTOP);
        execve(strace->command[0], strace->command, strace->envp);
        printf("strace: Can't stat '%s': No such file or directory\n",
            strace->command[0]);
        return (1);
    } else {
        exec_ptrace(strace);
        return (0);
    }
    return (1);
}
