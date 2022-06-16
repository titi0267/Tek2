/*
** EPITECH PROJECT, 2022
** indieStudio
** File description:
** WinServerScene
*/

#pragma once
#include "ecs/engine/EntityCommands.hpp"
#include "ecs/engine/SceneManager.hpp"
#include "ecs/engine/Network.hpp"
#include "ecs/components/Player.hpp"
#include "ecs/components/GridPosition.hpp"
#include "raylib/Vectors.hpp"

namespace bomberman {
    struct WinServerSceneArgs {
        ecs::PlayerId winner;
        bool noWinner;

        WinServerSceneArgs(ecs::PlayerId winner = 0, bool noWinner = true) : winner(winner), noWinner(noWinner) {};
    };

    class WinServerScene : public ecs::IScene, public ecs::ServerNetworkSceneModule {
        using ConnId = network::ConnId;

        ecs::PlayerId _winner;

        void spawnBackground(ecs::World &world);
        void spawnPlayer(ecs::PlayerId id, Vector3 pos, ecs::World &world);

        public:
        WinServerScene(const void *data) {};

        void loadScene(ecs::World &world);
        void unloadScene(ecs::World &world);
        void entityKilled(ecs::Entity entity, ecs::World &world);

        void onConnect(ConnId conn, ecs::World &world) {};
        void onDisconnect(ConnId conn, ecs::World &world) {};
        void onPlayerIdAttributed(ecs::PlayerId id, ecs::World &world) {};
    };
}
