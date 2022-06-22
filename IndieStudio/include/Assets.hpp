/*
** EPITECH PROJECT, 2022
** B-YEP-400-STG-4-1-indiestudio-mathieu.brujan
** File description:
** Assets
*/

#pragma once

#include "ecs/engine/World.hpp"

namespace bomberman {
    void loadTextures(ecs::World &world);
    void loadModels(ecs::World &world);
    void loadAnimations(ecs::World &world);
    void loadFonts(ecs::World &world);
    void loadShaders(ecs::World &world);
    void loadSounds(ecs::World &world);
    void applyAssetsToModels(ecs::World &world);
}
