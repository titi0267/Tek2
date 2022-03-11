/*
** EPITECH PROJECT, 2022
** B-PSU-400-STG-4-1-nmobjdump-timothe.coniel
** File description:
** args
*/

#pragma once
#define ERROR 84

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <elf.h>
#include <sys/mman.h>
#include <sys/stat.h>


typedef struct file_s
{
    char **flags;
    int file_type;
    int flag_nbr;
    void *elf;
} args_t;

enum File {
    OBJECT,
    SHAREDL,
    BIN
};

int flag_f_64(args_t *args);