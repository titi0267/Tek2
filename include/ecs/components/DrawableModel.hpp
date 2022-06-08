/*
** EPITECH PROJECT, 2022
** $
** File description:
** DrawableMesh
*/

#pragma once

#include "ecs/engine//World.hpp"
#include "ecs/engine/System.hpp"

#include "raylib/Model.hpp"

namespace ecs {
    struct ModelRef {
        raylib::Model *model;

        ModelRef(raylib::Model *model = nullptr) : model(model) {};
    };

    class DrawableModelSystem : public ecs::ASystem {
        public:
        DrawableModelSystem() : ecs::ASystem() { _stage = ecs::DRAW_WORLD; };

        void setSignature(ecs::ComponentManager &component);
        void update(ecs::World &world);
    };
}
