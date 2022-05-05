/*
** EPITECH PROJECT, 2022
** ftrace
** File description:
** elf64
*/

#include "ftrace.h"

int elf_64_nm(Elf *elf, nm_t *nm)
{
    GElf_Sym sym;
    GElf_Shdr shdr;
    GElf_Phdr phdr;
    char *name;
    Elf_Scn *scn = NULL;
    size_t shstrndx, i_phdr = 0, i_sym = 0;
    Elf_Data *data = NULL;
    char *symbole_name;

    if (elf_getshdrstrndx(elf, &shstrndx) != 0){}
    while ((scn = elf_nextscn(elf, scn)) != NULL) {
        if (gelf_getshdr(scn, &shdr) != &shdr){}
        if ((name = elf_strptr(elf, shstrndx, shdr.sh_name)) == NULL){}
        if (shdr.sh_type == SHT_SYMTAB)
            break;
        //printf("Section %-4.4jd %s\n", (uintmax_t)elf_ndxscn(scn), name);
    }
    if ((data = elf_getdata(scn, data)) != NULL) {}
    if (elf_getphdrnum(elf, &i_phdr) == -1){}
    i_sym = shdr.sh_size / gelf_fsize(elf, ELF_T_SYM, 1, data->d_version);
    /*for (size_t i = 0; i < i_phdr; i++) {
        if(gelf_getphdr(elf, i, &phdr) != &phdr) {
            printf("failed break\n");
            break;
        }*/
        //printf("vadrr 0x%jx | memsz 0x%jx\n", phdr.p_vaddr, phdr.p_memsz);
        for (size_t i = 0; i < i_sym; i++) {
            gelf_getsym(data, i, &sym);
            //symbole_name = strdup(elf_strptr(elf, shdr.sh_link, sym.st_name));
            //if (phdr.p_vaddr < sym.st_value && phdr.p_vaddr + phdr.p_memsz > sym.st_value) {
                printf("Here : %s\n", elf_strptr(elf, shdr.sh_link, sym.st_name));
            //if (strcmp(elf_strptr(elf, shdr.sh_link, sym.st_name), "main") == 0) {
            //}
            //printf("main 0x%jx\n", sym.st_value);
            //}
        }
    //}
          //      printf("sym = %s : %p\n", elf_strptr(elf, shdr.sh_link, sym.st_name), sym.st_value);
    elf_end(elf);
    UNUSED(table);
    return (0);
}