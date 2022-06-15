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
        Water() {};
    };
    class WaterUpdateSystem : public ASystem {
        public:
        WaterUpdateSystem() { _stage = ecs::Stages::UPDATE; };

        void setSignature(ecs::ComponentManager &component);
        void update(ecs::World &world);
    };
}
