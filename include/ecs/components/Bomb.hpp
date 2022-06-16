/*
** EPITECH PROJECT, 2022
** indieStudio
** File description:
** Bomb
*/

#pragma once
#include "ecs/engine/World.hpp"
#include "ecs/engine/Component.hpp"
#include "raylib/Vectors.hpp"
#include <iostream>

namespace ecs {
    struct BombId {
        std::uint64_t uniqueBombId = 0;

        BombId()
        {
            static std::uint64_t uniqueId = 0;

            uniqueBombId = uniqueId++;
        };

        bool operator==(const BombId &bomb) const
        {
            return uniqueBombId == bomb.uniqueBombId;
        }
    };

    class BombUpdateSystem : public ASystem {
        public:
        BombUpdateSystem() { _stage = ecs::Stages::DRAW_WORLD; };

        void setSignature(ecs::ComponentManager &component);
        void update(ecs::World &world);
    };
}

namespace std {
    template<>
    struct hash<ecs::BombId>
    {
        std::size_t operator()(const ecs::BombId &bomb) const
        {
            return (hash<std::uint64_t>()(bomb.uniqueBombId));
        }
    };
}
