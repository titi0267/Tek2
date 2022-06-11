/*
** EPITECH PROJECT, 2022
** indieStudio
** File description:
** PlayerInputAction
*/

#pragma once

#include "ecs/engine/System.hpp"
#include "ecs/engine/World.hpp"
#include "raylib.h"

namespace ecs {
    enum Direction {
        UP,
        DOWN,
        LEFT,
        RIGHT,
        ACTION
    };
    struct PlayerInputAction {
        int _up;
        int _down;
        int _left;
        int _right;
        int _action;
        Direction _currentAction;

        public:
            PlayerInputAction(int up, int down, int left, int right, int action) : _up(up), _down(down), _left(left), _right(right), _action(action), _currentAction(UP) {};

            void PlayerSetKeys(int up, int down, int left, int right, int action);
            bool getUp() const { return IsKeyDown(_up); };
            bool getDown() const { return IsKeyDown(_down); };
            bool getLeft() const { return IsKeyDown(_left); };
            bool getRight() const { return IsKeyDown(_right); };
            bool getAction() const { return IsKeyDown(_action); };
            bool getCurrentAction() const { return _currentAction; };
            void setCurrentAction(Direction chooseDir) { _currentAction = chooseDir; };
    };
    class PlayerInputActionUpdateSystem : public ecs::ASystem {
        public:
            PlayerInputActionUpdateSystem() { _stage = ecs::Stages::INPUT_UPDATE; };

            void setSignature(ecs::ComponentManager &component);
            void update(ecs::World &world);
    };
}