/*
** EPITECH PROJECT, 2022
** epi-cs
** File description:
** DrawableCube
*/

#pragma once

#include "ecs/engine/World.hpp"
#include "ecs/engine/System.hpp"
#include "ecs/components/ColorTexture.hpp"

namespace ecs {
    struct DrawableCube {
        Vector3 offset;
        Vector3 scale;

        public:
        DrawableCube(Vector3 offset = {0}, Vector3 scale = {1}) : offset(offset), scale(scale) {};

        void renderColor(Color &color);
        void renderTexture(raylib::Texture &texture, Tint tint);
    };

    class DrawTextureCubeSystem : public ecs::ASystem {
        public:
        DrawTextureCubeSystem() : ecs::ASystem() { _stage = ecs::DRAW_WORLD; };

        void setSignature(ecs::ComponentManager &component);
        void update(ecs::World &world);
    };
}
