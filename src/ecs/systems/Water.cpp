/*
** EPITECH PROJECT, 2022
** indieStudio
** File description:
** Water
*/

#include "ecs/engine/SceneManager.hpp"
#include "scenes/GameServerScene.hpp"
#include "ecs/components/Water.hpp"
#include "ecs/components/Timer.hpp"
#include "ecs/components/GridPosition.hpp"
#include "ecs/components/Player.hpp"
#include "ecs/components/Movement.hpp"
#include "raylib/Vectors.hpp"
#include <iostream>

void ecs::WaterUpdateSystem::setSignature(ecs::ComponentManager &component)
{
    _signature = component.generateSignature<Water, Timer, Transform, GridPosition>();
}

void ecs::WaterUpdateSystem::update(ecs::World &world)
{
    ecs::SceneManager &man = world.getRessource<ecs::SceneManager>();
    bomberman::GameServerScene &scene = dynamic_cast<bomberman::GameServerScene&>(man.getScene());
    map::Map &map = scene.getMap();
    std::vector<Entity> toDelete;

    for (ecs::Entity entity : _entities) {
        Transform &transform = world.getComponent<Transform>(entity);
        ecs::GridPosition &gPos = world.getComponent<ecs::GridPosition>(entity);
        Timer &timer = world.getComponent<Timer>(entity);
        Water &water = world.getComponent<Water>(entity);

        if (!water.expanded && timer.timeElapsed >= 0.2) {
            Vector3 pos = transform.translation + water.dir;
            ecs::GridPosition newGPos = gPos + ecs::GridPosition{(int) water.dir.x, (int) water.dir.z};

            water.expanded = true;

            if (water.distance >= 4 || !newGPos.isValidPos(map))
                continue;

            int cell = map.getCellAt(newGPos.x, newGPos.y);

            if (cell == VOID || cell == SPAWN) {
                scene.spawnWater(pos, newGPos, water.dir, water.distance + 1, world);
            } else if (cell == DESTRUCTIBLE) {
                map.setCellAt(newGPos.x, newGPos.y, VOID);
                scene.deleteDestructible(newGPos, world);
            }
        }

        if (timer.timeElapsed >= 1)
            toDelete.push_back(entity);
    }
    for (Entity entity : toDelete) {
        world.getEntityCommands(entity).despawn();
        scene.deleteWater(entity);
    }
}

void ecs::WaterCollisionUpdateSystem::setSignature(ecs::ComponentManager &component)
{
    _signature = component.generateSignature<GridPosition, Water>();
}

void ecs::WaterCollisionUpdateSystem::update(ecs::World &world)
{
    ecs::SceneManager &man = world.getRessource<ecs::SceneManager>();
    bomberman::GameServerScene &scene = dynamic_cast<bomberman::GameServerScene&>(man.getScene());
    const std::set<Entity> &players = scene.getPlayers();
    std::vector<std::tuple<Entity, Player&, GridPosition&>> playersAlive;

    for (Entity pEntity : players) {
        Player &player = world.getComponent<Player>(pEntity);

        if (player.alive) {
            GridPosition &gPos = world.getComponent<GridPosition>(pEntity);
            playersAlive.push_back({pEntity, player, gPos});
        }
    }
    for (Entity entity : _entities) {
        GridPosition &pos = world.getComponent<GridPosition>(entity);

        for (auto [pEntity, player, gPos] : playersAlive) {
            if (pos == gPos) {
                Transform &transform = world.getComponent<Transform>(pEntity);
                Vector3 deathPos = transform.translation + Vector3{0, 100, 0};

                player.alive = false;
                world.getComponent<Movement>(pEntity).move(deathPos, 25);
            }
        }
    }
}
