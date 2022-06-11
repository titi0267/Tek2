/*
** EPITECH PROJECT, 2022
** indieStudio
** File description:
** PlayerDoAction
*/

#pragma once

#include "ecs/engine/System.hpp"
#include "ecs/engine/World.hpp"

namespace ecs
{
    struct PlayerDoAction {
        PlayerDoAction() {};
        void goUp() {};
        void goDown() {};
        void goLeft() {};
        void goRight() {};
        void doAction() {};
    };
    class PlayerDoActionUpdateSystem : public ASystem {
        PlayerDoActionUpdateSystem() { _stage = ecs::Stages::INPUT_UPDATE; };

        void setSignature(ecs::ComponentManager &component);
        void update(ecs::World &world);
    };
}