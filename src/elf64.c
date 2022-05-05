/*
** EPITECH PROJECT, 2022
** ftrace
** File description:
** elf64
*/

#include "ftrace.h"

int elf_64_nm(Elf *elf, nm_t *nm, GElf_Phdr phdr)
{
    GElf_Sym sym;
    GElf_Shdr shdr;
    char *name;
    Elf_Scn *scn = NULL;
    size_t shstrndx, n = 0;
    Elf_Data *data = NULL;

    if (elf_getshdrstrndx(elf, &shstrndx) != 0){}
    while ((scn = elf_nextscn(elf, scn)) != NULL) {
        if (gelf_getshdr(scn, &shdr) != &shdr){}
        if ((name = elf_strptr(elf, shstrndx, shdr.sh_name)) == NULL){}
        if (shdr.sh_type == SHT_SYMTAB)
            break;
        //printf("Section %-4.4jd %s\n", (uintmax_t)elf_ndxscn(scn), name);
    }
    if ((data = elf_getdata(scn, data)) != NULL) {}
    n = shdr.sh_size / shdr.sh_entsize;
    for (size_t i = 0; i < n; i++) {
        gelf_getsym(data, i, &sym);
        if (strcmp(elf_strptr(elf, shdr.sh_link, sym.st_name), "main") == 0) {
            printf("main 0x%jx\n", sym.st_value);
        }
        //15848 vaddr
//536 memsz
//4447 main
        //if (phdr.p_vaddr < sym.st_value && phdr.p_vaddr + phdr.p_memsz > sym.st_value)
          //      printf("sym = %s : %p\n", elf_strptr(elf, shdr.sh_link, sym.st_name), sym.st_value);
    }
    elf_end(elf);
    UNUSED(table);
    return (0);
}