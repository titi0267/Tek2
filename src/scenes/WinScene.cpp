/*
** EPITECH PROJECT, 2022
** indieStudio
** File description:
** WinScene
*/

#include "scenes/WinScene.hpp"
#include "ecs/components/DrawableModel.hpp"
#include "ecs/components/Skin.hpp"
#include "ecs/engine/Network.hpp"
#include "raylib/Camera.hpp"

void bomberman::WinScene::spawnBackground(ecs::World &world)
{
    ;
}

void bomberman::WinScene::spawnPlayer(ecs::PlayerId id, Vector3 pos, ecs::World &world)
{
    Transform transform = {pos, QuaternionIdentity(), {1, 1, 1}};
    ecs::Entity entity;
    switch (id) {
        case 0:
            entity = world.spawn().insert(ecs::Player{id}, transform,
            ecs::ModelRef("player"), ecs::Skin{"mathieu"}, ecs::MirrorEntity {}).getEntity();
        break;
        case 1:
            entity = world.spawn().insert(ecs::Player{id}, transform,
            ecs::ModelRef("player"), ecs::Skin{"ludovic"}, ecs::MirrorEntity {}).getEntity();
        break;
        case 2:
            entity = world.spawn().insert(ecs::Player{id}, transform,
            ecs::ModelRef("player"), ecs::Skin{"timothe"}, ecs::MirrorEntity {}).getEntity();
        break;
        case 3:
            entity = world.spawn().insert(ecs::Player{id}, transform,
            ecs::ModelRef("player"), ecs::Skin{"jeffrey"}, ecs::MirrorEntity {}).getEntity();
        break;
    }
}

void bomberman::WinScene::loadScene(ecs::World &world)
{
    raylib::Camera &cam = world.getRessource<raylib::Camera>();

}

void bomberman::WinScene::unloadScene(ecs::World &world)
{
    world.killAllEntities();
}

void bomberman::WinScene::entityKilled(ecs::Entity entity, ecs::World &world)
{
    if (world.hasComponent<ecs::MirroredEntity>(entity))
        world.getRessource<ecs::ServerManager>().deleteClientEntity(entity, world);
    else if (world.hasComponent<ecs::MirrorEntity>(entity))
        world.getRessource<ecs::ServerManager>().killLocalEntity(entity, world);
}