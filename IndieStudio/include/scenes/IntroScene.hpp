/*
** EPITECH PROJECT, 2022
** indieStudio
** File description:
** IntroScene
*/

#pragma once
#include "ecs/engine/World.hpp"
#include "scenes/GameScene.hpp"
#include "raylib/Vectors.hpp"

namespace bomberman {
    class IntroScene : public ecs::IScene {
        std::set<ecs::Entity> omar;
        void spawnOmar(Vector3 pos, ecs::World &world);
        public:
        IntroScene() {};
        IntroScene(const void *data) {};

        void loadScene(ecs::World &world);
        void unloadScene(ecs::World &world);
        void entityKilled(ecs::Entity entity, ecs::World &world);

    };
};
