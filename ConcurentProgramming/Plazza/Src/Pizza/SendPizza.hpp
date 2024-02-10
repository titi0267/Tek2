/*
** EPITECH PROJECT, 2022
** plazza
** File description:
** SendPizza
*/

#pragma once
#include <iostream>
#include <cstdint>

typedef struct SendPizza_s {
    uint32_t pizzaId;
    uint32_t size;
    uint32_t doe;
    uint32_t tomato;
    uint32_t gruyere;
    uint32_t ham;
    uint32_t mushroom;
    uint32_t steak;
    uint32_t eggplant;
    uint32_t goat_cheese;
    uint32_t chief_love;
    bool statusCmd;
} SendPizza_t;
