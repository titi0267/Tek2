/*
** EPITECH PROJECT, 2022
** B-YEP-400-STG-4-1-indiestudio-mathieu.brujan
** File description:
** Grid
*/

#pragma once

#include "ecs/engine/System.hpp"
#include "ecs/engine/World.hpp"
#include "raylib/Vectors.hpp"

namespace ecs {
    void drawGrid(Transform &transform, int size, float spacing);

    struct Grid {
        int size;
        float spacing;

        Grid(int size = 0, float spacing = 0) : size(size), spacing(spacing) {};
    };

    class DrawGridSystem : public ecs::ASystem {
        public:
        DrawGridSystem() { _stage = ecs::DRAW_WORLD; };

        void setSignature(ecs::ComponentManager &component);
        void update(ecs::World &world);
    };
};
