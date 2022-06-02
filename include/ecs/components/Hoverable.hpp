/*
** EPITECH PROJECT, 2022
** epi-cs
** File description:
** Hoverable
*/

#pragma once

#include "ecs/engine/World.hpp"
#include "ecs/engine/System.hpp"

#include "Hitbox.hpp"

namespace ecs {
    struct Hoverable {
        bool isHover;
        bool updated;

        Hoverable() : isHover(false), updated(false) {};
    };

    class HoverUpdateSystem : public ecs::ASystem {
        public:
        HoverUpdateSystem() { _stage = ecs::Stages::INPUT_UPDATE; };

        void setSignature(ecs::ComponentManager &component);
        void update(ecs::World &world);
    };
}
