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
        PlayerAction action = DO_NOTHING;

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
}
