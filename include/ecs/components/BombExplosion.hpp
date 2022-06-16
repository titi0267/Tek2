/*
** EPITECH PROJECT, 2022
** indieStudio
** File description:
** BombExplosion
*/

#pragma once
#include "ecs/engine/World.hpp"
#include "ecs/engine/Component.hpp"
#include "scenes/GameServerScene.hpp"

namespace ecs {
    struct BombExplosion {
        BombExplosion() {};
    };
    class BombExplosionUpdateSystem : public ecs::ASystem {
        void placeWater(ecs::Entity entity, ecs::World &world, bomberman::GameServerScene &scene);

        public:
        BombExplosionUpdateSystem() { _stage = ecs::Stages::DRAW_WORLD; };

        void setSignature(ecs::ComponentManager &component);
        void update(ecs::World &world);
    };
}