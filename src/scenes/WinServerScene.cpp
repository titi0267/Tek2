/*
** EPITECH PROJECT, 2022
** indieStudio
** File description:
** WinServerScene
*/

#include "scenes/WinServerScene.hpp"
#include "ecs/components/DrawableModel.hpp"
#include "ecs/components/Skin.hpp"
#include "ecs/engine/Network.hpp"
#include "raylib/Camera.hpp"
#include "ecs/engine/SkinManager.hpp"
#include "ecs/components/Light.hpp"

void bomberman::WinServerScene::spawnBackground(ecs::World &world)
{
    ;
}

void bomberman::WinServerScene::spawnPlayer(ecs::PlayerId id, Vector3 pos, ecs::SkinManager &skinMan, ecs::World &world)
{
    Transform transform = {pos, QuaternionIdentity(), {1, 1, 1}};
    ecs::GridPosition gPos = {0, 0};


    ecs::Entity entity = world.spawn().insert(transform, gPos, ecs::ModelRef("player"), ecs::Player {id}, ecs::Skin {skinMan.getPlayerSkin(id)}, ecs::MirrorEntity {}).getEntity();
    std::cout << "SPAWNED PLAYER"<<std::endl;

    _players.insert({id, entity});
}

void bomberman::WinServerScene::loadScene(ecs::World &world)
{
    ecs::SkinManager &skinMan = world.getRessource<ecs::SkinManager>();
    world.getRessource<ecs::ServerManager>().moveCameras({0, 7, 3}, {0, 0, 0});

    spawnPlayer(0, {-5, 0, -4}, skinMan, world);
    spawnPlayer(1, {-2, 0, -4}, skinMan, world);
    spawnPlayer(2, {1, 0, -4}, skinMan, world);
    spawnPlayer(3, {4, 0, -4}, skinMan, world);
    world.spawn().insert(Transform{{0, 0, 0}, QuaternionIdentity(), {0.7, 0.7, 0.7}}, ecs::ModelRef{"amphi"}, ecs::MirrorEntity{});
    world.spawn().insert(Transform{{0, 0, 0}, QuaternionIdentity(), {1, 1, 1}}, ecs::Light{Vector3{-1, -1, -1}, Vector4{0.8, 0.8, 0.8, 1.0}}, ecs::MirrorEntity{});
    std::remove("bombitek.dat");
    std::remove("bombitek.map");
}

void bomberman::WinServerScene::unloadScene(ecs::World &world)
{
    world.killAllEntities();
}

void bomberman::WinServerScene::entityKilled(ecs::Entity entity, ecs::World &world)
{
    if (world.hasComponent<ecs::MirroredEntity>(entity))
        world.getRessource<ecs::ServerManager>().deleteClientEntity(entity, world);
    else if (world.hasComponent<ecs::MirrorEntity>(entity))
        world.getRessource<ecs::ServerManager>().killLocalEntity(entity, world);
}
