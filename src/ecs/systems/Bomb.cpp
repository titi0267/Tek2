/*
** EPITECH PROJECT, 2022
** indieStudio
** File description:
** BombExplosion
*/

#include "ecs/components/Bomb.hpp"
#include "ecs/components/Water.hpp"
#include "scenes/GameServerScene.hpp"

void ecs::BombUpdateSystem::setSignature(ecs::ComponentManager &component)
{
    _signature = component.generateSignature<Transform, GridPosition, BombId, Timer>();
}

void ecs::BombUpdateSystem::placeWater(ecs::Entity entity, ecs::World &world, bomberman::GameServerScene &scene)
{
    const Vector3 DIRECTIONS[5] = {
        { 0, 0, -1},
        { 0, 0,  1},
        {-1, 0,  0},
        { 1, 0,  0},
        { 0, 0,  0},
    };

    Transform &transform = world.getComponent<Transform>(entity);
    ecs::GridPosition &gPos = world.getComponent<ecs::GridPosition>(entity);

    map::Map &map = scene.getMap();

    map.setCellAt(gPos.x, gPos.y, VOID);
    for (int i = 0; i < 5; i++) {
        Vector3 waterPos = transform.translation + DIRECTIONS[i];
        ecs::GridPosition waterGPos = gPos + ecs::GridPosition {(int) DIRECTIONS[i].x, (int) DIRECTIONS[i].z};

        if (!waterGPos.isValidPos(map))
            continue;

        int cell = map.getCellAt(waterGPos.x, waterGPos.y);

        if (cell == VOID || cell == SPAWN) {
            scene.spawnWater(waterPos, waterGPos, {DIRECTIONS[i].x, 0, DIRECTIONS[i].z}, 1, world);
        } else if (cell == DESTRUCTIBLE) {
            map.setCellAt(waterGPos.x, waterGPos.y, VOID);
            scene.deleteDestructible(waterGPos, world);
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

        std::cout << timer.timeElapsed << std::endl;
        if (timer.timeElapsed >= 5) {
            placeWater(entity, world, scene);
            toDelete.push_back(entity);
        }
    }
    for (Entity entity : toDelete) {
        world.getEntityCommands(entity).despawn();
        scene.deleteBomb(entity);
    }
}
