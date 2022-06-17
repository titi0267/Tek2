/*
** EPITECH PROJECT, 2022
** epi-cs
** File description:
** Movement
*/

#pragma once

#include "raylib/Vectors.hpp"

#include "ecs/engine/World.hpp"
#include "ecs/engine/System.hpp"

namespace ecs {
    struct Movement {
        bool isMoving = false;
        Vector3 dest = {0};
        double speed = 0;

        void move(Vector3 dest, float speed)
        {
            this->dest = dest;
            this->speed = speed;
            this->isMoving = true;
        }
    };

    class MovementUpdateSystem : public ecs::ASystem {
        public:
        MovementUpdateSystem() {ecs::Stages::UPDATE; };

        void setSignature(ecs::ComponentManager &component);
        void update(ecs::World &world);
    };
}