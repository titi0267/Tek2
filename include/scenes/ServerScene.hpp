/*
** EPITECH PROJECT, 2022
** B-YEP-400-STG-4-1-indiestudio-mathieu.brujan
** File description:
** ServerScene
*/

#pragma once

#include "ecs/engine/World.hpp"
#include "ecs/engine/SceneManager.hpp"
#include "ecs/engine/Network.hpp"

namespace bomberman {
    class ServerScene : public ecs::IScene {
        public:
        void loadScene(ecs::World &world);
        void unloadScene(ecs::World &world);
        void entityKilled(ecs::Entity entity,ecs::World &world);
    };
}
