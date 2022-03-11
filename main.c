/*
** EPITECH PROJECT, 2022
** nm_objdump
** File description:
** main
*/

#include "args.h"

void usage()
{
    printf("Usage :\n");
}

void print_selection(char *section[], int z, Elf64_Shdr shdr, char *str, args_t *args)
{
    Elf64_Ehdr *elf = (Elf64_Ehdr *)args->elf;
    unsigned char *section_str = (unsigned char *)elf + shdr.sh_offset;

    if (strcmp(&str[shdr.sh_name], section[z]) == 0) {
        printf("Contents of section %s:\n", &str[shdr.sh_name]);
    } else
        return;
    for (int a = 0; a < shdr.sh_size; a+=16) {
        printf(" %04x ", shdr.sh_addr + a);
        for (int b = 0; b < 16; b++) {
            if (a + b >= shdr.sh_size) {
                printf("  ");
            }
            else
                printf("%02x", section_str[a + b]);
            if (b != 0 && (b + 1) % 4 == 0)
                printf(" ");
        }
        printf(" ");
        for (int b = 0; b < 16; b++) {
            if (a + b >= shdr.sh_size) {
                printf(" ");
            }
            else {
                if (isprint(section_str[a+b]) == 0)
                    printf(".");
                else
                    printf("%c", section_str[a + b]);
            }
        }
        printf("\n");
    }
}

void select_section(char *str, Elf64_Shdr shdr, args_t *args)
{
    int i = 0;
    char *section_obj[] = {".text", ".rodata", ".comment", ".note.gnu.property", ".eh_frame", NULL};
    char *section_bin[] = {".text", ".comment", ".eh_frame", ".rodata", ".debug_line_str", ".debug_str", ".debug_line", ".debug_abbrev", ".debug_info", ".debug_aranges", ".data", ".got.plt", ".got", ".dynamic", ".fini_array", ".init_array", ".eh_frame_hdr", ".fini", ".plt", ".init", ".rela.plt", ".rela.dyn", ".gnu.version_r", ".gnu.version", ".dynstr", ".dynsym", ".gnu.hash", ".note.ABI-tag", ".note.gnu.build-id", ".note.gnu.property", ".interp", NULL};

    if (args->file_type == BIN) {
        for (int z = 0; section_bin[z] != NULL ; z++) {
            print_selection(section_bin, z, shdr, str, args);
        }
    }
    if (args->file_type == OBJECT) {
        for (int z = 0; section_obj[z] != NULL; z++) {
            print_selection(section_obj, z, shdr, str, args);
        }
    }
    //printf("%s\n", &str[shdr.sh_name]);
    /*if ((strcmp(&str[shdr.sh_name], ".text") == 0) || strcmp(&str[shdr.sh_name], ".rodata") == 0 || strcmp(&str[shdr.sh_name], ".comment") == 0 || strcmp(&str[shdr.sh_name], ".comment") == 0) {
        printf("Contents of section %s:\n", &str[shdr.sh_name]);
    }
    if (strcmp(&str[shdr.sh_name], ".rodata") == 0) {
        printf("Contents of section %s:\n", &str[shdr.sh_name]);
    }*/
}
//002e7379 6d746162 002e7374 72746162
//554889e5 ba080000 00488d05 00000000

int print_section(args_t *args, Elf64_Ehdr *elf)
{
    Elf64_Shdr *shdr = (Elf64_Shdr *)((void *)elf + elf->e_shoff);
    char *str = (char *)((void *)elf + shdr[elf->e_shstrndx].sh_offset);

    for (int i = 0; i < elf->e_shnum; i++) {
        select_section(str, shdr[i], args);
    }
}

int elf_64(Elf64_Ehdr *elf, args_t *args)
{
    args->elf = elf;
    if (elf->e_machine == EM_X86_64)
        printf("\n%s:     file format elf64-x86-64\n", args->flags[0]);
    printf("architecture: i386:x86-64, flags");
    if (args->file_type == OBJECT) {
        printf(" 0x00000011:\nHAS_RELOC, HAS_SYMS\nstart address 0x%016lx\n\n", elf->e_entry);
    }
    else if (args->file_type == BIN) {
        printf(" 0x00000150:\nHAS_SYMS, DYNAMIC, D_PAGED\nstart address 0x%016lx\n\n", elf->e_entry);
    } else {
        //printf(" 0x00000150:\n", elf->e_entry);
    }
    print_section(args, elf);
}

int elf_32(struct stat buffer, int open_ret, args_t *args)
{
    Elf32_Ehdr *elf;

    elf = mmap(NULL, buffer.st_size, PROT_READ, MAP_PRIVATE, open_ret, 0);
    args->elf = elf;
    printf("\n%s:     file format elf32", args->flags[0]);
    if (elf->e_machine == EM_386)
        printf("-386\narchitecture: i386");
    else if (elf->e_machine == EM_X86_64)
        printf("-x86-64\narchitecture: i386:x86-64");
    if (args->file_type == OBJECT) {
        printf("0x00000011:\nHAS_RELOC, HAS_SYMS\nstart address 0x0000000000000000\n\n");
    }
    else if (args->file_type == BIN) {
        printf("0x00000115:\n");
    } else {
        printf("?:\n");
    }
}

int use_mmap(int open_ret, args_t *args, struct stat buffer)
{
    Elf64_Ehdr *elf;
    int is_64 = 0;
    int status;

    elf = mmap(NULL, buffer.st_size, PROT_READ, MAP_PRIVATE, open_ret, 0);
    if (elf->e_ident[EI_CLASS] == ELFCLASSNONE)
        return (ERROR);
    (elf->e_ident[EI_CLASS] == ELFCLASS64) ? elf_64(elf, args) : elf_32(buffer, open_ret, args);
    return (0);
}

int store_file(args_t *args, char *av)
{
    int open_ret = 0;
    int status;
    struct stat buffer;
    int z = 0;

    if (av[0] != '-') {
        open_ret = open(av, O_RDONLY);
        args->flags[0] = malloc(strlen(av) * sizeof(char) + 2);
        args->flag_nbr += 1;
        for (; av[z] != '\0'; z++)
            args->flags[0][z] = av[z];
        args->flags[0][z] = '\0';
    }
    if (open_ret == -1)
        return (ERROR);
    else if (open_ret == 0)
        return (0);
    if (av[strlen(av) - 2] == '.' && av[strlen(av) - 1] == 'o')
        args->file_type = OBJECT;
    else if (strlen(av) >= 3 && av[strlen(av) - 3] == '.' && av[strlen(av) - 2] == 's' && av[strlen(av) - 1] == 'o')
        args->file_type = SHAREDL;
    else
        args->file_type = BIN;
    status = fstat(open_ret, &buffer);
    use_mmap(open_ret, args, buffer);
    return (1);
}

int parse_args(int ac, char **av, args_t *args)
{
    int b = 0;

    args->flags = malloc(sizeof(char*) * (ac + 1));
    for (int i = 1; i < ac; i++) {
        b = store_file(args, av[i]);
        if (b == ERROR)
            return (ERROR);
        else if (b == 0) {
            args->flags[i] = malloc(strlen(av[i]) * sizeof(char) + 1);
            for (int t = 0; av[i][t] != '\0'; t++)
                args->flags[i][t] = av[i][t];
            args->flag_nbr += 1;
        }
    }
    return (0);
}

int main(int ac, char **av)
{
    args_t *args = malloc(sizeof(args_t));
    args->flag_nbr = 0;
    if (ac == 1)
        usage();
    if (ac > 1) {
        if (parse_args(ac, av, args) == ERROR)
            usage();
    }
    for (int i = 0; i < args->flag_nbr; i++) {
        free(args->flags[i]);
    }
    free(args->flags);
    free(args);
}
