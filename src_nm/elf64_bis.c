/*
** EPITECH PROJECT, 2022
** B-PSU-400-STG-4-1-nmobjdump-timothe.coniel
** File description:
** elf64_bis
*/

#include "../include/nm.h"

void print_type(Elf64_Sym sym, Elf64_Shdr *shdr, node_t *front, char *str)
{
    node_t node = (*front);
    char c;

    if (ELF64_ST_BIND(sym.st_info) == STB_GNU_UNIQUE)
        node->type = 'u';
    else if (ELF64_ST_BIND(sym.st_info) == STB_WEAK) {
        node->type = 'W';
        if (sym.st_shndx == SHN_UNDEF)
            node->type = 'w';
    } else if (ELF64_ST_BIND(sym.st_info) == STB_WEAK && ELF64_ST_TYPE(sym.st_info) == STT_OBJECT) {
        node->type = 'V';
      if (sym.st_shndx == SHN_UNDEF)
        node->type = 'v';
    }
    else if (sym.st_shndx == SHN_UNDEF)
        node->type = 'U';
    else if (sym.st_shndx == SHN_ABS)
        node->type = 'A';
    else if (sym.st_shndx == SHN_COMMON)
        node->type = 'C';
    else if (shdr[sym.st_shndx].sh_type == SHT_NOBITS
       && shdr[sym.st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE))
        node->type = 'B';
    else if (shdr[sym.st_shndx].sh_type == SHT_PROGBITS
       && shdr[sym.st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE))
        node->type = 'D';
    else if (shdr[sym.st_shndx].sh_type == SHT_PROGBITS
       && shdr[sym.st_shndx].sh_flags == (SHF_ALLOC | SHF_EXECINSTR))
        node->type = 'T';
    else if (shdr[sym.st_shndx].sh_type == SHT_DYNAMIC)
        node->type = 'D';
    else if (shdr[sym.st_shndx].sh_type == SHT_PROGBITS
       && shdr[sym.st_shndx].sh_flags == SHF_ALLOC)
        node->type = 'R';
    else if (shdr[sym.st_shndx].sh_type == SHT_NOTE)
        node->type = 'R';
    else {
        node->type = 'D';
    }
    if (ELF64_ST_BIND(sym.st_info) == STB_LOCAL && node->type != '?')
        node->type += 32;
}
