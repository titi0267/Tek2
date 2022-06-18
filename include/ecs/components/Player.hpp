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
    struct Player {
        PlayerId id;
        bool alive = true;
        bool bombBonus = false;
        bool bootsBonus = false;
        bool tigBonus = false;
        bool explodeBonus = false;
        bool isStun = false;

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
