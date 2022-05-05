/*
** EPITECH PROJECT, 2022
** ftrace
** File description:
** elf64
*/

#include "ftrace.h"

int elf_64_nm(Elf *elf, nm_t *nm, ftrace_t *ftrace, int index, unsigned long long rip, GElf_Ehdr ehdr)
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
            printf("failed\n");
            break;
        }
    }*/
        for (size_t i = 0; i < i_sym; i++) {
            gelf_getsym(data, i, &sym);
            for (size_t n = 0; n < i_phdr; n++) {
                if(gelf_getphdr(elf, n, &phdr) != &phdr) {
                    printf("failed\n");
                    break;
                }
                if (phdr.p_vaddr < sym.st_value && (phdr.p_vaddr + phdr.p_memsz) > sym.st_value) {
                    //printf("Smybol in program %lx : %s with %jx\n", n, elf_strptr(elf, shdr.sh_link, sym.st_name), sym.st_value + ftrace->maps[index].start);
                    //sym.st_value -= phdr.p_vaddr;
                    sym.st_value += (ftrace->maps[index].start - phdr.p_vaddr);
                    printf("ehdr = %lx | %jx = val | vaddr = %jx\n", (long unsigned int)&ehdr, sym.st_value, phdr.p_vaddr);
                    if (sym.st_value == rip)
                        printf("Entering funciton : %s\n", elf_strptr(elf, shdr.sh_link, sym.st_name));
                }
            }
            //printf("Next sym\n");
        }
    //}
          //      printf("sym = %s : %p\n", elf_strptr(elf, shdr.sh_link, sym.st_name), sym.st_value);
    elf_end(elf);
    UNUSED(table);
    return (0);
}