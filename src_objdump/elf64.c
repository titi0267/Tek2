/*
** EPITECH PROJECT, 2022
** B-PSU-400-STG-4-1-nmobjdump-timothe.coniel
** File description:
** elf64
*/

#include "../include/args.h"

void print_bin_type(Elf64_Shdr shdr, char *str, args_t *args)
{
    char *section_bin[] = {".text", ".comment", ".eh_frame", ".rodata",
    ".debug_line_str", ".debug_str", ".debug_line", ".debug_abbrev",
    ".debug_info", ".debug_aranges", ".data", ".got.plt", ".got", ".dynamic",
    ".fini_array", ".init_array", ".eh_frame_hdr", ".fini", ".plt", ".init",
    ".rela.plt", ".rela.dyn", ".gnu.version_r", ".gnu.version", ".dynstr",
    ".dynsym", ".gnu.hash", ".note.ABI-tag", ".note.gnu.build-id",
    ".note.gnu.property", ".interp", ".jcr", NULL};

    for (int z = 0; section_bin[z] != NULL ; z++) {
        if (print_section_name(section_bin, z, shdr, str) == 1)
            print_section_content(z, shdr, str, args);
    }
}

void print_object_type(Elf64_Shdr shdr, char *str, args_t *args)
{
    char *section_obj[] = {".text", ".rodata", ".comment",
    ".note.gnu.property", ".eh_frame", NULL};

    for (int z = 0; section_obj[z] != NULL; z++) {
        if (print_section_name(section_obj, z, shdr, str) == 1)
            print_section_content(z, shdr, str, args);
    }

}

void choose_print_type(args_t *args, Elf64_Shdr shdr, char *str)
{
    if (args->file_type == BIN || args->file_type == SHAREDL) {
        print_bin_type(shdr, str, args);
    } else if (args->file_type == OBJECT) {
        print_object_type(shdr, str, args);
    }
}

void iterate_section(args_t *args, Elf64_Ehdr *elf)
{
    Elf64_Shdr *shdr = (Elf64_Shdr *)((void *)elf + elf->e_shoff);
    char *str = (char *)((void *)elf + shdr[elf->e_shstrndx].sh_offset);

    for (int i = 0; i < elf->e_shnum; i++)
        choose_print_type(args, shdr[i], str);
}

int elf_64(Elf64_Ehdr *elf, args_t *args)
{
    args->elf = elf;
    if (elf->e_machine == EM_X86_64)
        printf("\n%s:     file format elf64-x86-64\n", args->flags[0]);
    printf("architecture: i386:x86-64, flags");
    if (args->file_type == OBJECT) {
        printf(" 0x00000011:\nHAS_RELOC, HAS_SYMS\n");
        printf("start address 0x%016lx\n\n", elf->e_entry);
    }
    else if (args->file_type == BIN || args->file_type == SHAREDL) {
        printf(" 0x00000150:\nHAS_SYMS, DYNAMIC, D_PAGED\n");
        printf("start address 0x%016lx\n\n", elf->e_entry);
    } else {
    }
    iterate_section(args, elf);
    return (0);
}
