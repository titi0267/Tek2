/*
** EPITECH PROJECT, 2022
** indieStudio
** File description:
** SpawnBonus
*/

#include "ecs/components/SpawnBonus.hpp"
#include "scenes/GameServerScene.hpp"

void ecs::SpawnBonusUpdateSystem::setSignature(ecs::ComponentManager &component)
{
    _signature = component.generateSignature<SpawnBonus, GridPosition, Transform>();
}

void ecs::SpawnBonusUpdateSystem::update(ecs::World &world)
{
    ecs::SceneManager &man = world.getRessource<ecs::SceneManager>();
    bomberman::GameServerScene &scene = dynamic_cast<bomberman::GameServerScene&>(man.getScene());
    map::Map &map = scene.getMap();

    for (ecs::Entity entity : _entities) {
        Transform &transform = world.getComponent<Transform>(entity);
        ecs::GridPosition &gPos = world.getComponent<ecs::GridPosition>(entity);
    }
}