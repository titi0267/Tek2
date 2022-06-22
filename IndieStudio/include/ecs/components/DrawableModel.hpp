/*
** EPITECH PROJECT, 2022
** B-YEP-400-STG-4-1-indiestudio-mathieu.brujan
** File description:
** DrawableModel
*/

#pragma once

#include "ecs/engine/World.hpp"
#include "ecs/engine/System.hpp"

#include "raylib/Model.hpp"

namespace ecs {
    struct ModelRef {
        char modelId[255];

        ModelRef(const std::string &id = "") { id.copy(modelId, 255); modelId[id.size()] = 0; };
    };

    class DrawableModelSystem : public ecs::ASystem {
        public:
        DrawableModelSystem() : ecs::ASystem() { _stage = ecs::DRAW_WORLD; };

        void setSignature(ecs::ComponentManager &component);
        void update(ecs::World &world);
    };
}
