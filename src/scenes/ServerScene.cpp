/*
** EPITECH PROJECT, 2022
** B-YEP-400-STG-4-1-indiestudio-mathieu.brujan
** File description:
** ServerScene
*/

#include "scenes/ServerScene.hpp"

void bomberman::ServerScene::loadScene(ecs::World &world)
{
}

void bomberman::ServerScene::unloadScene(ecs::World &world)
{
    world.killAllEntities();
}

void bomberman::ServerScene::entityKilled(ecs::Entity entity,ecs::World &world)
{
    if (world.hasComponent<ecs::MirrorEntity>(entity))
        world.getRessource<ecs::ServerManager>().killLocalEntity(entity, world);
}

void bomberman::ServerScene::setPlayerAction(ecs::PlayerId id, ecs::Actions action)
{
    _actions.at(id) = action;
}
