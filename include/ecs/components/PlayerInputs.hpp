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

    enum PlayerAction {
        DO_NOTHING,
        MOVE_UP,
        MOVE_DOWN,
        MOVE_LEFT,
        MOVE_RIGHT,
        PLACE_BOMB,
    };

    struct PlayerInputs {
        PlayerId id;
        PlayerAction action = DO_NOTHING;

        Key upKey;
        Key downKey;
        Key leftKey;
        Key rightKey;
        Key bombKey;

        public:
        PlayerInputs() : id(-1) {};
        PlayerInputs(PlayerId id, Key up = KEY_W, Key down = KEY_S, Key left = KEY_A, Key right = KEY_D, Key bomb = KEY_Q)
            : id(id), upKey(up), downKey(down), leftKey(left), rightKey(right), bombKey(bomb) {};
    };

    class PlayerInputsUpdateSystem : public ecs::ASystem {
        public:
        PlayerInputsUpdateSystem() { _stage = ecs::Stages::INPUT_UPDATE; };

        void setSignature(ecs::ComponentManager &component);
        void update(ecs::World &world);
    };
}
