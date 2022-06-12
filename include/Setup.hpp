/*
** EPITECH PROJECT, 2022
** B-YEP-400-STG-4-1-indiestudio-mathieu.brujan
** File description:
** Setup
*/

#pragma once

#include "ecs/engine/World.hpp"

namespace bomberman {
    int WSA(void);

    void registerCriticalComponents(ecs::World &world);
    void registerRender(ecs::World &world);
    void registerInputs(ecs::World &world);
    void registerNetwork(ecs::World &world, bool client);
};