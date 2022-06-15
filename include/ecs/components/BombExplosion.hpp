/*
** EPITECH PROJECT, 2022
** indieStudio
** File description:
** BombExplosion
*/

#pragma once
#include "ecs/engine/World.hpp"
#include "ecs/engine/Component.hpp"

namespace ecs {
    struct BombExplosion {
        BombExplosion() {};
    };
    class BombExplosionUpdateSystem : public ecs::ASystem {
        public:
        BombExplosionUpdateSystem() { _stage = ecs::Stages::UPDATE; };

        void setSignature(ecs::ComponentManager &component);
        void update(ecs::World &world);
    };
}