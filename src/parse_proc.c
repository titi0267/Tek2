/*
** EPITECH PROJECT, 2022
** ftrace
** File description:
** parse_proc
*/

#include "ftrace.h"

int nm_bin(ftrace_t *ftrace, int d)
{
    Elf *relf;
    nm_t *nm = malloc(sizeof(nm_t));
    int fd = 0;
    GElf_Ehdr ehdr;

    fd = open(ftrace->maps[d].path, O_RDONLY);
    if (fd == -1) {
        printf("failed to open %s$\n", ftrace->maps[d].path);
        return (84);
    }
    if ((relf = elf_begin(fd, ELF_C_READ, NULL)) == NULL)
        printf("IT DOESNT BEGIN: %i\n", fd);
        //printf("o");
    //nm->elf = (void *)elf;
    if (elf_kind(relf) != ELF_K_ELF){}
    if (gelf_getehdr(relf, &ehdr) == NULL){}
        //;//printf("FUck help me\n");
    printf("end nm_bin\n");
    //printf("p_vaddr 0x%jx\n" , (uintmax_t)phdr.p_vaddr);
    //printf("p_memsz 0x%jx\n" , (uintmax_t)phdr.p_memsz);
    if (gelf_getclass(relf) == ELFCLASSNONE )
        return (ERROR);
    //printf("elf_type 0x%jx\n", (uintmax_t)ehdr.e_machine);
    elf_64_nm(relf, nm);
    return (0);
}

int find_binary(char *buf, ftrace_t *ftrace, int line_index)
{
    int i = strlen(buf) - 2;
    int cmd_len = strlen(ftrace->bin_name) - 1;

    if (buf == NULL)
        return (84);
    //printf("i = %i | buf = $%c$\n", i, buf[i]);
    for (; buf[i] != '/'; i--, cmd_len--) {
        if (buf[i] != ftrace->bin_name[cmd_len])
            break;
    }
    if ((cmd_len == 0 || ftrace->bin_name[cmd_len] == '/') && line_index < 4) {
        //printf("it was right bin with %i\n", line_index);
        //printf("%s", buf);
        sscanf(buf, "%jx-%jx %*c%*c%*c%*c %jx %*jx:%*jx %*d %[^\n]", &ftrace->maps[line_index].start, &ftrace->maps[line_index].end, &ftrace->maps[line_index].offset, ftrace->maps[line_index].path);
        printf("0x%jx - 0x%jx | offset 0x%jx | path = %s\n", ftrace->maps[line_index].start, ftrace->maps[line_index].end, ftrace->maps[line_index].offset, ftrace->maps[line_index].path);
        ftrace->maps[line_index + 1].last_array = -1;
        ftrace->maps[line_index].last_array = 0;
        ftrace->maps_init = 1;
        return (1);
    }
    //printf("return 84\n");
    return (84);
}



int open_proc(pid_t pid, ftrace_t *ftrace)
{
    char *proc = my_strcat("/proc/", my_getchar((int)pid));
    FILE *fp;
    char buf[1500];
    int line_index = 0;
    int find_bin_ret = 1;

    UNUSED(table);
    fp = fopen(my_strcat(proc, "/maps"), "r");
    if (fp == NULL) {
        printf("failed to open /proc\n");
        return (84);
    }
    while (find_bin_ret == 1) {
        if (fgets(buf, 1499, fp) == NULL)
            break;
        //printf("%s\n", buf);
        find_bin_ret = find_binary(buf, ftrace, line_index);
        if (find_bin_ret == 1)
            line_index++;
        memset(buf, 0, 1499);
    }
    fclose(fp);
    return (0);
}

/*
564cd8bbe000-564cd8bbf000 r--p 00000000 103:06 20062471                  /home/timothe/git_epi/trace/ftrace/a.out
564cd8bbf000-564cd8bc0000 r-xp 00001000 103:06 20062471                  /home/timothe/git_epi/trace/ftrace/a.out
564cd8bc0000-564cd8bc1000 r--p 00002000 103:06 20062471                  /home/timothe/git_epi/trace/ftrace/a.out
564cd8bc1000-564cd8bc2000 r--p 00002000 103:06 20062471                  /home/timothe/git_epi/trace/ftrace/a.out
564cd8bc2000-564cd8bc3000 rw-p 00003000 103:06 20062471                  /home/timothe/git_epi/trace/ftrace/a.out
564cda638000-564cda659000 rw-p 00000000 00:00 0                          [heap]
7fc77ba06000-7fc77ba08000 rw-p 00000000 00:00 0 
7fc77ba08000-7fc77ba34000 r--p 00000000 103:06 20588326                  /usr/lib/libc.so.6
7fc77ba34000-7fc77bbaa000 r-xp 0002c000 103:06 20588326                  /usr/lib/libc.so.6
7fc77bbaa000-7fc77bbfe000 r--p 001a2000 103:06 20588326                  /usr/lib/libc.so.6
7fc77bbfe000-7fc77bbff000!
*/
/*
564cd8bbe000-564cd8bbf000 r--p 00000000 103:06 20062471                  /home/timothe/git_epi/trace/ftrace/a.out
564cd8bbf000-564cd8bc0000 r-xp 00001000 103:06 20062471                  /home/timothe/git_epi/trace/ftrace/a.out
564cd8bc0000-564cd8bc1000 r--p 00002000 103:06 20062471                  /home/timothe/git_epi/trace/ftrace/a.out
564cd8bc1000-564cd8bc3000 rw-p 00002000 103:06 20062471                  /home/timothe/git_epi/trace/ftrace/a.out
7fc77ba06000-7fc77ba08000 rw-p 00000000 00:00 0 
7fc77ba08000-7fc77ba34000 r--p 00000000 103:06 20588326                  /usr/lib/libc.so.6
7fc77ba34000-7fc77bbaa000 r-xp 0002c000 103:06 20588326                  /usr/lib/libc.so.6
7fc77bbaa000-7fc77bbfe000 r--p 001a2000 103:06 20588326                  /usr/lib/libc.so.6
7fc77bbfe000-7fc77bbff000 ---p 001f6000 103:06 20588326                  /usr/lib/libc.so.6
7fc77bbff000-7fc77bc05000 rw-p 001f6000 103:06 20588326                  /usr/lib/libc.so.6
7fc77bc05000-7fc77bc14000 rw-p 0000!
*/