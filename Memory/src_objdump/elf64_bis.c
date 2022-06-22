/*
** EPITECH PROJECT, 2022
** B-PSU-400-STG-4-1-nmobjdump-timothe.coniel
** File description:
** elf64_bis
*/

#include "../include/args.h"

void print_hexa(int a, int b, Elf64_Shdr shdr, unsigned char *section)
{
    if (a + b >= shdr.sh_size)
        printf("  ");
    else
        printf("%02x", section[a + b]);
    if (b != 0 && (b + 1) % 4 == 0)
        printf(" ");
}

void print_ascii(int a, int b, Elf64_Shdr shdr, unsigned char *section)
{
    if (a + b >= shdr.sh_size)
        printf(" ");
    else {
        if (isprint(section[a + b]) == 0)
            printf(".");
        else
            printf("%c", section[a + b]);
    }
}

void print_section_content(int z, Elf64_Shdr shdr, char *str, args_t *args)
{
    Elf64_Ehdr *elf = (Elf64_Ehdr *)args->elf;
    unsigned char *section_str = (unsigned char *)elf + shdr.sh_offset;

    for (int a = 0; a < shdr.sh_size; a += 16) {
        printf(" %04x ", (unsigned int)shdr.sh_addr + a);
        for (int b = 0; b < 16; b++) {
            print_hexa(a, b, shdr, section_str);
        }
        printf(" ");
        for (int b = 0; b < 16; b++) {
            print_ascii(a, b, shdr, section_str);
        }
        printf("\n");
    }
}

int print_section_name(char *section[], int z, Elf64_Shdr shdr, char *str)
{
    if (strcmp(&str[shdr.sh_name], section[z]) == 0)
        printf("Contents of section %s:\n", &str[shdr.sh_name]);
    else
        return (0);
    return (1);
}
