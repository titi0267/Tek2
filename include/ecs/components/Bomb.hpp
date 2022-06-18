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
#include "ecs/engine/PlayerId.hpp"
#include <iostream>

namespace bomberman {
    class GameServerScene;
}

namespace ecs {
    const float BOMB_EXPLODING_TIME = 3.0f;

    struct Bomb {
        ecs::PlayerId playerId = -1;
        int bombDistance = 0;

        Bomb(ecs::PlayerId id = -1, int bombDistance = 0) : playerId(id), bombDistance(bombDistance) {};
    };

    class BombUpdateSystem : public ASystem {
        void placeWater(ecs::Entity entity, ecs::World &world, bomberman::GameServerScene &scene);

        public:
        BombUpdateSystem() { _stage = ecs::Stages::UPDATE; };

        void setSignature(ecs::ComponentManager &component);
        void update(ecs::World &world);
    };
}
