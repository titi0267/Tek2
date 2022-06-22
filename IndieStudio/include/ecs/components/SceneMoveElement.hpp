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
    class MoveRequesterSceneModule {
        public:
        virtual bool &getMovementRequest() = 0;
        virtual Vector3 &getMoveDest() = 0;
    };

    struct SceneMoveElement {
        Vector3 start;
        Vector3 destination;
        bool inMovement;
        float speed;

        SceneMoveElement (float speed = 1) : inMovement(false), speed(speed) {};
    };

    class SceneMoveElementSystem : public ecs::ASystem {
        bool move(Vector3 &translation, SceneMoveElement &sceneMove);

        public:
        SceneMoveElementSystem() { _stage = ecs::Stages::RENDER_UPDATE; };
        void setSignature(ecs::ComponentManager &component);
        void update(ecs::World &world);
    };
}
