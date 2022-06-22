/*
** EPITECH PROJECT, 2022
** B-PSU-400-STG-4-1-nmobjdump-timothe.coniel
** File description:
** elf32_bis
*/

#include "../include/args.h"

void print_hexa_min(int a, int b, Elf32_Shdr shdr, unsigned char *section)
{
    if (a + b >= shdr.sh_size)
        printf("  ");
    else
        printf("%02x", section[a + b]);
    if (b != 0 && (b + 1) % 4 == 0)
        printf(" ");
}

void print_ascii_min(int a, int b, Elf32_Shdr shdr, unsigned char *section)
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

void print_section_content_min(int z, Elf32_Shdr shdr, char *str, args_t *args)
{
    Elf32_Ehdr *elf = (Elf32_Ehdr *)args->elf;
    unsigned char *section_str = (unsigned char *)elf + shdr.sh_offset;

    for (int a = 0; a < shdr.sh_size; a += 16) {
        printf(" %04x ", (unsigned int)shdr.sh_addr + a);
        for (int b = 0; b < 16; b++) {
            print_hexa_min(a, b, shdr, section_str);
        }
        printf(" ");
        for (int b = 0; b < 16; b++) {
            print_ascii_min(a, b, shdr, section_str);
        }
        printf("\n");
    }
}

int print_section_name_min(char *section[], int z, Elf32_Shdr shdr, char *str)
{
    if (strcmp(&str[shdr.sh_name], section[z]) == 0)
        printf("Contents of section %s:\n", &str[shdr.sh_name]);
    else
        return (0);
    return (1);
}
