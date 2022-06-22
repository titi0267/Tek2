/*
** EPITECH PROJECT, 2022
** ftrace
** File description:
** elf64_type
*/

#include "ftrace.h"

void print_type_fourth(Elf64_Sym sym, Elf64_Shdr *shdr, node_t node)
{
    if (shdr[sym.st_shndx].sh_type == SHT_PROGBITS
        && shdr[sym.st_shndx].sh_flags == SHF_ALLOC)
        node->type = 'R';
    else if (shdr[sym.st_shndx].sh_type == SHT_NOTE)
        node->type = 'R';
    else
        node->type = 'D';
}

void print_type_third(Elf64_Sym sym, Elf64_Shdr *shdr, node_t node)
{
    if (shdr[sym.st_shndx].sh_type == SHT_NOBITS
        && shdr[sym.st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE))
        node->type = 'B';
    else if (shdr[sym.st_shndx].sh_type == SHT_PROGBITS
        && shdr[sym.st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE))
        node->type = 'D';
    else {
        if (shdr[sym.st_shndx].sh_type == SHT_PROGBITS
            && shdr[sym.st_shndx].sh_flags == (SHF_ALLOC | SHF_EXECINSTR))
            node->type = 'T';
        else if (shdr[sym.st_shndx].sh_type == SHT_DYNAMIC)
            node->type = 'D';
        else
            print_type_fourth(sym, shdr, node);
    }
}

void print_type_sec(Elf64_Sym sym, Elf64_Shdr *shdr, node_t node)
{
    if (ELF64_ST_BIND(sym.st_info) == STB_WEAK &&
        ELF64_ST_TYPE(sym.st_info) == STT_OBJECT) {
        node->type = 'V';
        if (sym.st_shndx == SHN_UNDEF)
            node->type = 'v';
    } else if (sym.st_shndx == SHN_UNDEF)
        node->type = 'U';
    else {
        if (sym.st_shndx == SHN_ABS)
            node->type = 'A';
        else if (sym.st_shndx == SHN_COMMON)
            node->type = 'C';
        else
            print_type_third(sym, shdr, node);
    }
}

void print_type(Elf64_Sym sym, Elf64_Shdr *shdr, node_t *front)
{
    node_t node = (*front);

    if (ELF64_ST_BIND(sym.st_info) == STB_GNU_UNIQUE)
        node->type = 'u';
    else if (ELF64_ST_BIND(sym.st_info) == STB_WEAK) {
        node->type = 'W';
        if (sym.st_shndx == SHN_UNDEF)
            node->type = 'w';
    } else
        print_type_sec(sym, shdr, node);
    if (ELF64_ST_BIND(sym.st_info) == STB_LOCAL && node->type != '?')
        node->type += 32;
    UNUSED(table);
}


/*void print_type(Elf64_Sym sym, Elf64_Shdr *shdr, node_t *front)
{
    node_t node = (*front);

    if (shdr[sym.st_shndx].sh_type == SHT_PROGBITS
        && shdr[sym.st_shndx].sh_flags == (SHF_ALLOC | SHF_EXECINSTR))
        node->type = 'T';
    else
        node->type = '?';
    UNUSED(table);
}
*/