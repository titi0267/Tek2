/*
** EPITECH PROJECT, 2022
** B-YEP-400-STG-4-1-indiestudio-mathieu.brujan
** File description:
** ItemRotation
*/

#pragma once

#include "ecs/engine/System.hpp"
#include "ecs/engine/World.hpp"

namespace ecs {
    struct ItemRotation {
        float speed;
        float height;

        ItemRotation(float speed = 0, float height = 0) : speed(speed), height(height) {};
    };

    class ItemRotationUpdateSystem : public ecs::ASystem {
        public:
        ItemRotationUpdateSystem() { _stage = UPDATE; };

        void setSignature(ecs::ComponentManager &component);
        void update(ecs::World &world);
    };
};