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
        double droppedTime = 0;
        std::unordered_map<std::uint64_t, Vector3> bombPos;

        BombId(Vector3 pos = {-1, -1, -1})
        {
            static std::uint64_t uniqueId = 0;

            std::cout << "New bomb: " << uniqueId << std::endl;
            bombPos.insert({uniqueBombId, pos});
            std::cout << "Bomb numbers :" << bombPos.size() << std::endl;
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