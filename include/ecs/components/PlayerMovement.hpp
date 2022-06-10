/*
** EPITECH PROJECT, 2022
** indieStudio
** File description:
** PlayerMovement
*/

#pragma once

#include "ecs/engine/System.hpp"
#include "ecs/engine/World.hpp"
#include "raylib.h"

namespace ecs {
    enum Direction {
        UP,
        DOWN,
        LEFT,
        RIGHT
    };
    struct PlayerMovement {
        Direction chooseDir;
        Vector3 pos;

        PlayerMovement() : chooseDir(UP), pos({0, 0, 0}) {};
    };
    class PlayerMovementUpdateSystem : public ecs::ASystem {
        public:
            PlayerMovementUpdateSystem() { _stage = ecs::Stages::INPUT_UPDATE; };

            void setSignature(ecs::ComponentManager &component);
            void update(ecs::World &world);
    };
}