/*
** EPITECH PROJECT, 2022
** B-YEP-400-STG-4-1-indiestudio-mathieu.brujan
** File description:
** LobbyServerScene
*/

#pragma once

#include "ecs/engine/SceneManager.hpp"
#include "ecs/engine/World.hpp"
#include "ecs/engine/Network.hpp"
#include "ecs/components/PlayerInputs.hpp"

namespace bomberman {
    class LobbyServerScene : public ecs::IScene, public ecs::SceneActionsHandleModule, public ecs::ServerNetworkSceneModule {
        using ConnId = network::ConnId;

        std::unordered_map<ecs::PlayerId, ecs::Actions> _actions;
        std::unordered_map<ecs::PlayerId, bool> _updatedThisFrame;

        std::unordered_map<ecs::PlayerId, ecs::Entity> _players;
        std::unordered_map<ecs::PlayerId, bool> _ready;

        void spawnPlayer(ecs::PlayerId id, ecs::World &world);

        public:
        LobbyServerScene() {};
        LobbyServerScene(const void *data) {};

        void loadScene(ecs::World &world);
        void unloadScene(ecs::World &world);
        void entityKilled(ecs::Entity entity,ecs::World &world);

        void setPlayerAction(ecs::PlayerId id, ecs::Actions action);
        ecs::Actions getPlayerAction(ecs::PlayerId id) const;
        bool isActionUpdatedThisFrame(ecs::PlayerId id) const { return _updatedThisFrame.at(id); };
        void setActionUpdatedThisFrame(ecs::PlayerId id, bool updated) { _updatedThisFrame.at(id) = updated; };

        void onConnect(ConnId conn, ecs::World &world);
        void onDisconnect(ConnId conn, ecs::World &world);
        void onPlayerIdAttributed(ecs::PlayerId id, ecs::World &world);

        void setPlayerReady(ecs::PlayerId id, ecs::World &world);
        void checkReady(ecs::World &world);
    };

    class LobbyExecuteActionUpdateSystem : public ecs::ASystem {
        public:
        LobbyExecuteActionUpdateSystem() { _stage = ecs::Stages::UPDATE; };

        void setSignature(ecs::ComponentManager &component);
        void update(ecs::World &world);
    };
}
