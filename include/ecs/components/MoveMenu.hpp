/*
** EPITECH PROJECT, 2022
** bomberman
** File description:
** MoveMenu
*/

#pragma once

#include "ecs/engine/System.hpp"

#include "raylib/Window.hpp"

namespace ecs {
    struct MoveMenu {
        bool *right;
        bool *left;
        bool *up;
        bool *down;
        bool inMovementRight;
        bool inMovementLeft;
        bool inMovementUp;
        bool inMovementDown;
        Vector3 destination;
        float speed;
        MoveMenu () : right(nullptr), left(nullptr) {};
        MoveMenu (bool *right, bool *left, bool *up, bool *down, float speed) : right(right), up(up), down(down), left(left), inMovementRight(false), inMovementLeft(false), inMovementUp(false), inMovementDown(false), speed(speed) {};
    };
    class MoveMenuElementSystem : public ecs::ASystem {
        public:
            MoveMenuElementSystem() { _stage = ecs::Stages::RENDER_UPDATE; };
            void setSignature(ecs::ComponentManager &component);
            void update(ecs::World &world);
            bool moveRight(Vector3 &translation, MoveMenu &moveMenu);
            bool moveLeft(Vector3 &translation, MoveMenu &moveMenu);
        protected:
        private:
    };
}
