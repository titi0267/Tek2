/*
** EPITECH PROJECT, 2022
** indie
** File description:
** Ai
*/

#pragma once

#include "ecs/engine/World.hpp"
#include "ecs/components/PlayerInputs.hpp"
#include "ecs/engine/System.hpp"
#include "ecs/engine/SceneManager.hpp"
#include "scenes/GameServerScene.hpp"

namespace ecs {
    enum State {
        IN_DANGER,
        ITEM_ON_MAP,
        ENEMY_KILLABLE,
        ENEMY_REACHABLE
    };
    struct Ai {
        ecs::State _state;
    };
    class AiSystem : public ecs::ASystem {
        public:
        AiSystem() : ecs::ASystem() {_stage = ecs::INPUT_UPDATE;};

        void setSignature(ecs::ComponentManager &component);
        void update(ecs::World &world);
    };
};
