/*
** EPITECH PROJECT, 2022
** indieStudio
** File description:
** Player
*/

#pragma once

#include "ecs/engine/PlayerId.hpp"
#include "ecs/engine/System.hpp"

namespace ecs {
    const float SPEED_BOOST = 2.0f;

    const float SPEED_DURATION = 2.0f;
    const float TIG_DURATION = 2.0f;

    struct Player {
        PlayerId id;
        bool alive = true;

        float speed = 2;
        int bombRange = 4;
        int maxBombs = 1;

        int placedBombs = 0;
        int tigs = 0;

        float tigDuration = 0;
        float speedDuration = 0;

        Player(PlayerId id = -1) : id(id) {};
    };

    class PlayerUpdateSystem : public ecs::ASystem {
        public:
        PlayerUpdateSystem() { _stage = ecs::Stages::UPDATE; };

        void setSignature(ecs::ComponentManager &component);
        void update(ecs::World &world);
    };

    class PlayerCollisionUpdateSystem : public ecs::ASystem {
        public:
        PlayerCollisionUpdateSystem() { _stage = ecs::Stages::UPDATE; };

        void setSignature(ecs::ComponentManager &component);
        void update(ecs::World &world);
    };
}
