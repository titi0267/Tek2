/*
** EPITECH PROJECT, 2022
** indieStudio
** File description:
** Water
*/

#pragma once
#include "ecs/engine/World.hpp"

namespace ecs {
    struct Water {
        Vector3 dir;
        int distance;
        bool expanded = false;

        Water(Vector3 dir = {0}, int distance = 0) : dir(dir), distance(distance) {};
    };

    class WaterUpdateSystem : public ASystem {
        public:
        WaterUpdateSystem() { _stage = ecs::Stages::UPDATE; };

        void setSignature(ecs::ComponentManager &component);
        void update(ecs::World &world);
    };

    class WaterCollisionUpdateSystem : public ASystem {
        public:
        WaterCollisionUpdateSystem() { _stage = ecs::Stages::UPDATE; };

        void setSignature(ecs::ComponentManager &component);
        void update(ecs::World &world);
    };
}
