/*
** EPITECH PROJECT, 2022
** B-YEP-400-STG-4-1-indiestudio-mathieu.brujan
** File description:
** GameServerScene
*/

#pragma once

#include "ecs/engine/World.hpp"
#include "ecs/engine/SceneManager.hpp"
#include "ecs/engine/Network.hpp"
#include "ecs/components/PlayerInputs.hpp"
#include "ecs/engine/PlayerId.hpp"
#include "ecs/engine/EntityCommands.hpp"
#include "ecs/components/GridPosition.hpp"
#include "ecs/components/PlayerInputs.hpp"
#include "ecs/components/Bomb.hpp"
#include "ecs/components/SpawnBonus.hpp"
#include "ecs/components/Timer.hpp"
#include "raylib/Vectors.hpp"
#include "Map.hpp"

namespace bomberman {
    const int BONUS_SPAWN_INV_CHANCE = 1;

    struct GameServerSceneArgs {
        bool reloadGame;

        GameServerSceneArgs(bool reload = false) : reloadGame(true) {};
    };

    class GameServerScene : public ecs::IScene, public ecs::SceneActionsHandleModule, public ecs::ServerNetworkSceneModule {
        using ConnId = network::ConnId;

        std::unordered_map<ecs::PlayerId, ecs::Actions> _actions;
        std::unordered_map<ecs::PlayerId, bool> _updatedThisFrame;

        map::Map _map;
        std::unordered_map<ecs::GridPosition, ecs::Entity> _destructibles;

        std::unordered_map<ecs::PlayerId, ecs::Entity> _players;
        std::set<ecs::Entity> _bombs;
        std::set<ecs::Entity> _water;
        std::set<ecs::Entity> _bonus;

        Vector3 mapCoordsToWorldCoords(int x, int y);

        void spawnDestructible(Vector3 pos, ecs::GridPosition gPos, ecs::World &world);
        void spawnWall(Vector3 pos, ecs::GridPosition gPos, ecs::World &world);
        void spawnFloor(Vector2 mapSize, ecs::World &world);
        void generateMapProps(ecs::World &world);

        void startNewGame(ecs::World &world);
        void loadSavedGame(ecs::World &world);

        public:
        GameServerScene(const void *data) : _map(15, 15, 4, 4) {};

        void loadScene(ecs::World &world);
        void unloadScene(ecs::World &world);
        void entityKilled(ecs::Entity entity,ecs::World &world);

        void spawnPlayer(ecs::PlayerId id, Vector3 pos, ecs::GridPosition gPos, ecs::World &world);
        void spawnBonus(Vector3 pos, ecs::GridPosition gPos, ecs::Bonus bonus, ecs::World &world);
        void deleteBonus(ecs::Entity bonus);
        void spawnBomb(Vector3 pos, ecs::GridPosition gPos, ecs::Player &player, ecs::World &world);
        void deleteBomb(ecs::Entity bomb);
        void spawnWater(Vector3 pos, ecs::GridPosition gPos, Vector3 dir, int distance, ecs::World &world);
        void deleteWater(ecs::Entity water);
        void deleteDestructible(ecs::GridPosition &pos, ecs::World &world);

        void trySpawnBonus(Vector3 pos, ecs::GridPosition gPos, ecs::World &world);

        void setPlayerAction(ecs::PlayerId id, ecs::Actions action);
        ecs::Actions getPlayerAction(ecs::PlayerId id) const;
        bool isActionUpdatedThisFrame(ecs::PlayerId id) const { return _updatedThisFrame.at(id); };
        void setActionUpdatedThisFrame(ecs::PlayerId id, bool updated) { _updatedThisFrame.at(id) = updated; };

        void onConnect(ConnId conn, ecs::World &world) {};
        void onDisconnect(ConnId conn, ecs::World &world) {};
        void onPlayerIdAttributed(ecs::PlayerId id, ecs::World &world) {};

        map::Map &getMap();

        const std::unordered_map<ecs::PlayerId, ecs::Entity> &getPlayers() { return _players; };
        const std::set<ecs::Entity> &getBombs() { return _bombs; };
        const std::set<ecs::Entity> &getWater() { return _water; };
        const std::set<ecs::Entity> &getBonus() { return _bonus; };
    };

    class GameExecuteActionUpdateSystem : public ecs::ASystem {
        void placeBomb(ecs::Entity entity, ecs::World &world, bomberman::GameServerScene &scene);
        void movePlayer(ecs::Entity entity, ecs::World &world, ecs::Actions action, map::Map &map);

        public:
        GameExecuteActionUpdateSystem() { _stage = ecs::Stages::UPDATE; };

        void setSignature(ecs::ComponentManager &component);
        void update(ecs::World &world);
    };

    class GameCheckWinSystem : public ecs::ASystem {
        public:
        GameCheckWinSystem() { _stage = ecs::Stages::UPDATE; };

        void setSignature(ecs::ComponentManager &component);
        void update(ecs::World &world);
    };
}
