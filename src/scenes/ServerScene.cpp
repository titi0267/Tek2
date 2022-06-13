/*
** EPITECH PROJECT, 2022
** B-YEP-400-STG-4-1-indiestudio-mathieu.brujan
** File description:
** ServerScene
*/

#include "scenes/ServerScene.hpp"

#include "ecs/engine/EntityCommands.hpp"
#include "ecs/components/PlayerInputs.hpp"
#include "ecs/components/Movement.hpp"
#include "ecs/components/Player.hpp"
#include "ecs/components/DrawableModel.hpp"
#include <utility>

void bomberman::ServerScene::loadScene(ecs::World &world)
{
    world.spawn().insert(Transform {{0, 0, -3}, QuaternionIdentity(), {1, 1, 1}},
    ecs::Movement{}, ecs::Player{0}, ecs::ModelRef("button"));
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

ecs::Actions bomberman::ServerScene::getPlayerAction(ecs::PlayerId id) const
{
    return _actions.at(id);
}

void bomberman::ServerScene::addToMap(ecs::PlayerId id, ecs::Actions action)
{
    _actions.insert(std::make_pair(id, action));
}