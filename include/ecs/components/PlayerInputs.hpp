/*
** EPITECH PROJECT, 2022
** indieStudio
** File description:
** PlayerInputs
*/

#pragma once

#include "raylib/Window.hpp"
#include "ecs/engine/System.hpp"
#include "ecs/engine/World.hpp"
#include "ecs/engine/PlayerId.hpp"

namespace ecs {
    using Key = ::KeyboardKey;

    enum Actions {
        DO_NOTHING,
        MOVE_UP,
        MOVE_DOWN,
        MOVE_LEFT,
        MOVE_RIGHT,
        PLACE_BOMB,
    };

    struct PlayerAction {
        PlayerId id;
        Actions action = DO_NOTHING;

        PlayerAction(PlayerId id = -1) : id(id) {};
    };

    struct PlayerInputs {
        Key upKey;
        Key downKey;
        Key leftKey;
        Key rightKey;
        Key bombKey;

        public:
        PlayerInputs(Key up = KEY_W, Key down = KEY_S, Key left = KEY_A, Key right = KEY_D, Key bomb = KEY_Q)
            : upKey(up), downKey(down), leftKey(left), rightKey(right), bombKey(bomb) {};
    };

    class PlayerInputsUpdateSystem : public ecs::ASystem {
        public:
        PlayerInputsUpdateSystem() { _stage = ecs::Stages::INPUT_UPDATE; };

        void setSignature(ecs::ComponentManager &component);
        void update(ecs::World &world);
    };

    class PlayerActionUpdateSystem : public ecs::ASystem {
        public:
        PlayerActionUpdateSystem() { _stage = ecs::Stages::INPUT_UPDATE; };

        void setSignature(ecs::ComponentManager &component);
        void update(ecs::World &world);
    };

    class SceneActionsHandleModule {
        public:
        virtual void setPlayerAction(ecs::PlayerId id, ecs::Actions action) = 0;
        virtual ecs::Actions getPlayerAction(ecs::PlayerId id) const = 0;
    };
}
