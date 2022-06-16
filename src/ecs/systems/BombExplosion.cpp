/*
** EPITECH PROJECT, 2022
** indieStudio
** File description:
** BombExplosion
*/

#include "ecs/components/BombExplosion.hpp"
#include "ecs/components/Water.hpp"
#include "scenes/GameServerScene.hpp"

void ecs::BombExplosionUpdateSystem::placeWater(ecs::Entity entity, ecs::World &world, bomberman::GameServerScene &scene)
{
    Transform &transform = world.getComponent<Transform>(entity);
    ecs::GridPosition &gPos = world.getComponent<ecs::GridPosition>(entity);
    map::Map &map = scene.getMap();
    ecs::BombId &bomb = world.getComponent<ecs::BombId>(entity);
    ecs::Timer &timer = world.getComponent<ecs::Timer>(entity);
    static std::vector<float> counter = {-1.0, -1.0, -1.0, -1.0};
    const std::unordered_map<ecs::Actions, Vector3> DIRECTIONS = {
        {ecs::MOVE_UP, {0, 0, -1 - counter.at(0)}},
        {ecs::MOVE_DOWN, {0, 0, 1 + counter.at(1)}},
        {ecs::MOVE_LEFT, {-1 - counter.at(2), 0, 0}},
        {ecs::MOVE_RIGHT, {1 + counter.at(3), 0, 0}}
    };

    for (auto itr = DIRECTIONS.begin(); itr != DIRECTIONS.end(); itr++) {
        Vector3 moveVec =  itr->second;
        ecs::GridPosition gDest = gPos + ecs::GridPosition {(int) moveVec.x, (int) moveVec.z};

        if (gDest.x < 0 || gDest.y < 0 || gDest.x > map.getWidth() - 1 || gDest.y > map.getHeight() - 1)
            continue;
        if (map.getCellAt(gDest.x, gDest.y) != VOID && map.getCellAt(gDest.x, gDest.y) == SPAWN)
            continue;
        if (timer.timeElapsed >= 2) {
            std::cout << "Bomb explode"<< std::endl;
            scene.spawnWater(transform.translation, gPos, world);
            counter.at(itr->first - 1) += 1;

        }
    }
}

void ecs::BombExplosionUpdateSystem::setSignature(ecs::ComponentManager &component)
{
    _signature = component.generateSignature<BombExplosion, Water>();
}

void ecs::BombExplosionUpdateSystem::update(ecs::World &world)
{
    ecs::SceneManager &man = world.getRessource<ecs::SceneManager>();
    bomberman::GameServerScene &scene = dynamic_cast<bomberman::GameServerScene&>(man.getScene());

    for (ecs::Entity entity : _entities) {
        BombExplosion &bombExplosion = world.getComponent<BombExplosion>(entity);
        Water &water = world.getComponent<Water>(entity);

        std::cout << "Place water" << std::endl;
        placeWater(entity, world, scene);
        scene.deleteBomb(entity);
    }
}