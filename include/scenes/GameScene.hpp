/*
** EPITECH PROJECT, 2022
** B-YEP-400-STG-4-1-indiestudio-mathieu.brujan
** File description:
** GameScene
*/

#pragma once

#include "ecs/engine/SceneManager.hpp"

namespace bomberman {
    class GameScene : public ecs::IScene {
        public:
        void loadScene(ecs::World &world);
        void unloadScene(ecs::World &world);
    };
}
