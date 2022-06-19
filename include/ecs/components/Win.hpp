/*
** EPITECH PROJECT, 2022
** indieStudio
** File description:
** Win
*/

#pragma once

#include "ecs/engine/World.hpp"
#include "ecs/engine/System.hpp"

namespace ecs {
    class WinUpdateSystem : public ASystem {
        float _time = 0;

        public:
        WinUpdateSystem() { _stage = ecs::Stages::UPDATE; };

        void setSignature(ecs::ComponentManager &component);
        void update(ecs::World &world);
    };
};