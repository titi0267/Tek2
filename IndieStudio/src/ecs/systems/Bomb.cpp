/*
** EPITECH PROJECT, 2022
** indieStudio
** File description:
** BombExplosion
*/

#include "ecs/components/Bomb.hpp"
#include "ecs/components/Water.hpp"
#include "scenes/GameServerScene.hpp"
#include "ecs/components/Player.hpp"
#include "raylib/SoundManager.hpp"

void ecs::BombUpdateSystem::setSignature(ecs::ComponentManager &component)
{
    _signature = component.generateSignature<Transform, GridPosition, Bomb, Timer>();
}

void ecs::BombUpdateSystem::placeWater(ecs::Entity entity, ecs::World &world, bomberman::GameServerScene &scene)
{
    const Vector3 DIRECTIONS[4] = {
        { 0, 0, -1},
        { 0, 0,  1},
        {-1, 0,  0},
        { 1, 0,  0},
    };

    Transform &transform = world.getComponent<Transform>(entity);
    GridPosition &gPos = world.getComponent<ecs::GridPosition>(entity);
    Bomb &bomb = world.getComponent<ecs::Bomb>(entity);

    map::Map &map = scene.getMap();

    map.setCellAt(gPos.x, gPos.y, VOID);
    scene.spawnWater(transform.translation, gPos, {0, 0, 0}, 0, world);
    for (int i = 0; i < 4; i++) {
        for (int dist = 1; dist < bomb.bombDistance; dist ++) {
            Vector3 waterPos = transform.translation + DIRECTIONS[i] * dist;
            ecs::GridPosition waterGPos = gPos + ecs::GridPosition {(int) DIRECTIONS[i].x * dist, (int) DIRECTIONS[i].z * dist};

            if (!waterGPos.isValidPos(map))
                break;

            int cell = map.getCellAt(waterGPos.x, waterGPos.y);

            if (map.isWalkableCell(waterGPos.x, waterGPos.y)) {
                scene.spawnWater(waterPos, waterGPos, {DIRECTIONS[i].x, 0, DIRECTIONS[i].z}, 1, world);
            } else if (cell == DESTRUCTIBLE) {
                map.setCellAt(waterGPos.x, waterGPos.y, VOID);
                scene.deleteDestructible(waterGPos, world);
                scene.trySpawnBonus(waterPos, waterGPos, world);
                break;
            } else
                break;
        }
    }
}

void ecs::BombUpdateSystem::update(ecs::World &world)
{
    ecs::SceneManager &man = world.getRessource<ecs::SceneManager>();
    bomberman::GameServerScene &scene = dynamic_cast<bomberman::GameServerScene&>(man.getScene());
    std::vector<Entity> toDelete;

    for (ecs::Entity entity : _entities) {
        Timer &timer = world.getComponent<Timer>(entity);
        Bomb &bomb = world.getComponent<Bomb>(entity);

        if (timer.timeElapsed >= BOMB_EXPLODING_TIME) {
            world.getRessource<ecs::ServerManager>().playSound("water_sound");
            placeWater(entity, world, scene);
            world.getComponent<Player>(scene.getPlayers().at(bomb.playerId)).placedBombs--;
            toDelete.push_back(entity);
        }
    }
    for (Entity entity : toDelete) {
        world.getEntityCommands(entity).despawn();
        scene.deleteBomb(entity);
    }
}
