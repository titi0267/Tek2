/*
** EPITECH PROJECT, 2022
** indieStudio
** File description:
** Bomb
*/

#pragma once
#include "ecs/engine/World.hpp"
#include "ecs/engine/Component.hpp"

namespace ecs {
    struct BombId {
        std::uint64_t uniqueBombId;
        double droppedTime = 0;

        BombId()
        {
            static std::uint64_t uniqueId = 0;

            uniqueBombId = uniqueId++;
        };
    };
    class BombIdUpdateSystem : public ASystem {
        public:
        BombIdUpdateSystem() { _stage = ecs::Stages::UPDATE; };

        void setSignature(ecs::ComponentManager &component);
        void update(ecs::World &world);
    };
}