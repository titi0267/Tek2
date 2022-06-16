/*
** EPITECH PROJECT, 2022
** indieStudio
** File description:
** WinScene
*/

#pragma once
#include "ecs/engine/EntityCommands.hpp"
#include "ecs/engine/SceneManager.hpp"
#include "ecs/components/Player.hpp"
#include "ecs/components/GridPosition.hpp"
#include "raylib/Vectors.hpp"

namespace bomberman {
    struct WinSceneArgs {
        ;
    };
    class WinScene : public ecs::IScene {
        ecs::Entity _entity;
        ecs::PlayerId _playerId;

        public:
        WinScene(const void *data) {};

        void loadScene(ecs::World &world);
        void unloadScene(ecs::World &world);
        void entityKilled(ecs::Entity entity, ecs::World &world);

        void spawnBackground(ecs::World &world);
        void spawnPlayer(ecs::PlayerId id, Vector3 pos, ecs::World &world);
    };
}
