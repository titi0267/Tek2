/*
** EPITECH PROJECT, 2022
** B-PSU-400-STG-4-1-nmobjdump-timothe.coniel
** File description:
** elf32
*/

#include "../include/args.h"

void print_bin_type_min(Elf32_Shdr shdr, char *str, args_t *args)
{
    char *section_bin[] = {".text", ".comment", ".eh_frame", ".rodata",
    ".debug_line_str", ".debug_str", ".debug_line", ".debug_abbrev",
    ".debug_info", ".debug_aranges", ".data", ".got.plt", ".got", ".dynamic",
    ".fini_array", ".init_array", ".eh_frame_hdr", ".fini", ".plt", ".init",
    ".rela.plt", ".rela.dyn", ".gnu.version_r", ".gnu.version", ".dynstr",
    ".dynsym", ".gnu.hash", ".note.ABI-tag", ".note.gnu.build-id",
    ".note.gnu.property", ".interp", ".jcr", NULL};

    for (int z = 0; section_bin[z] != NULL ; z++) {
        if (print_section_name_min(section_bin, z, shdr, str) == 1)
            print_section_content_min(z, shdr, str, args);
    }
}

void print_object_type_min(Elf32_Shdr shdr, char *str, args_t *args)
{
    char *section_obj[] = {".text", ".rodata", ".comment",
    ".note.gnu.property", ".eh_frame", NULL};

    for (int z = 0; section_obj[z] != NULL; z++) {
        if (print_section_name_min(section_obj, z, shdr, str) == 1)
            print_section_content_min(z, shdr, str, args);
    }
}

void choose_print_type_min(args_t *args, Elf32_Shdr shdr, char *str)
{
    if (args->file_type == BIN || args->file_type == SHAREDL) {
        print_bin_type_min(shdr, str, args);
    } else if (args->file_type == OBJECT) {
        print_object_type_min(shdr, str, args);
    }
}

void iterate_section_min(args_t *args, Elf32_Ehdr *elf)
{
    Elf32_Shdr *shdr = (Elf32_Shdr *)((void *)elf + elf->e_shoff);
    char *str = (char *)((void *)elf + shdr[elf->e_shstrndx].sh_offset);

    for (int i = 0; i < elf->e_shnum; i++)
        choose_print_type_min(args, shdr[i], str);
}

int elf_32(struct stat buffer, int open_ret, args_t *args)
{
    Elf32_Ehdr *elf;

    elf = mmap(NULL, buffer.st_size, PROT_READ, MAP_PRIVATE, open_ret, 0);
    args->elf = elf;
    printf("\n%s:     file format elf32-i386\narchitecture: i386, flags ",
        args->flags[0]);
    if (args->file_type == OBJECT) {
        printf("0x00000102:\nEXEC_P, D_PAGED\n");
        printf("start address 0x%016lx\n\n", elf->e_entry);
    } else if (args->file_type == BIN || args->file_type == SHAREDL) {
        printf("0x00000102:\nEXEC_P, D_PAGED\n");
        printf("start address 0x%016lx\n\n", elf->e_entry);
    } else {
    }
    iterate_section_min(args, elf);
    return (0);
}
