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
#include "ecs/components/PlayerInputs.hpp"
#include "ecs/engine/PlayerId.hpp"
#include "ecs/engine/EntityCommands.hpp"
#include "ecs/components/GridPosition.hpp"
#include "raylib/Vectors.hpp"
#include "Map.hpp"

namespace bomberman {
    class ServerScene : public ecs::IScene {
        std::unordered_map<ecs::PlayerId, ecs::Actions> _actions;
        map::Map _map;

        void spawnBottle(Vector3 pos, ecs::GridPosition gPos, ecs::World &world);
        void spawnChair(Vector3 pos, ecs::GridPosition gPos, ecs::World &world);
        void spawnWall(Vector3 pos, ecs::GridPosition gPos, Vector3 size, ecs::World &world);
        void spawnFloor(Vector2 mapSize, ecs::World &world);
        void generateMapProps(ecs::World &world);

        public:
        ServerScene() : _map(9, 9, 4, 1) {};
        ServerScene(const void *data) : _map(9, 9, 4, 1) {};

        void loadScene(ecs::World &world);
        void unloadScene(ecs::World &world);
        void entityKilled(ecs::Entity entity,ecs::World &world);

        void setPlayerAction(ecs::PlayerId id, ecs::Actions action);
        map::Map getMap() const;
        ecs::Actions getPlayerAction(ecs::PlayerId id) const;
    };
}
