/*
** EPITECH PROJECT, 2022
** B-CCP-400-STG-4-1-panoramix-timothe.coniel
** File description:
** panoramix
*/

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>

#define ERROR_CODE 84

typedef struct parameters_s {
    int nb_villager;
    int pot_size;
    int nb_fights;
    int nb_refills;
    int initial_pot_size;
} parameters_t;

int parse_args(int ac, char **av, parameters_t *params);
int usage(void);
int threads(parameters_t *params);