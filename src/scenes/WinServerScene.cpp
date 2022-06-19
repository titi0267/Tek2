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
#include "ecs/components/Win.hpp"
#include "ecs/components/Timer.hpp"
#include "ecs/components/PlayAnimation.hpp"

void bomberman::WinServerScene::spawnBackground(ecs::World &world)
{
    ;
}

void bomberman::WinServerScene::spawnPlayer(ecs::PlayerId id, Vector3 pos, ecs::SkinManager &skinMan, ecs::World &world, bool winner)
{
    Transform transform = {pos, QuaternionIdentity(), {1, 1, 1}};
    ecs::GridPosition gPos = {0, 0};

    ecs::Entity entity = world.spawn().insert(transform, gPos, ecs::ModelRef("player"), ecs::Player {id},
    ecs::Skin {skinMan.getPlayerSkin(id)}, ecs::PlayAnimation {}, ecs::Timer {}, ecs::MirrorEntity {}).getEntity();

    if (winner) {
        world.getComponent<ecs::PlayAnimation>(entity).play("playerAnims", 3, 0.5, true, 4);
    } else {
        world.getComponent<ecs::PlayAnimation>(entity).play("playerAnims", 2, 0.5, true, 4);
    }

    _players.insert({id, entity});
}

void bomberman::WinServerScene::loadScene(ecs::World &world)
{
    float offset = -3;
    ecs::SkinManager &skinMan = world.getRessource<ecs::SkinManager>();
    world.getRessource<ecs::ServerManager>().moveCameras({0, 7, 3}, {0, -1, -2});
    world.registerSystem<ecs::WinUpdateSystem>();

    if (this->_noWinner) {
        spawnPlayer(0, {-4.5, -0.5, -2}, skinMan, world, false);
        spawnPlayer(1, {-1.5, -0.5, -2}, skinMan, world, false);
        spawnPlayer(2, { 1.5, -0.5, -2}, skinMan, world, false);
        spawnPlayer(3, { 4.5, -0.5, -2}, skinMan, world, false);
    } else {
        spawnPlayer(_winner, {0, 1.5, -3.5}, skinMan, world, true);
        for (int i = 0; i < 4; i++) {
            if (_winner == i)
                continue;
            spawnPlayer(i, {offset, 0, -2}, skinMan, world, false);
            offset += 3;
        }
    }
    world.spawn().insert(Transform{{0, 0, 0}, QuaternionIdentity(), {0.7, 0.7, 0.7}}, ecs::ModelRef{"amphi"}, ecs::MirrorEntity{});
    world.spawn().insert(Transform{{0, 0, 0}, QuaternionIdentity(), {1, 1, 1}}, ecs::Light{Vector3{-1, -1, -1}, Vector4{0.8, 0.8, 0.8, 1.0}}, ecs::MirrorEntity{});
    world.spawn().insert(Transform{{0, 0, -3.5}, QuaternionIdentity(), {1, 1, 1}}, ecs::ModelRef{"table"}, ecs::Light{Vector3{0, 4, 0}, Vector4{1.0, 1.0, 0.0, 1.0}}, ecs::MirrorEntity{});
    std::remove("bombitek.dat");
    std::remove("bombitek.map");
}

void bomberman::WinServerScene::unloadScene(ecs::World &world)
{
    world.unregisterSystem<ecs::WinUpdateSystem>();
    world.killAllEntities();
    world.getRessource<ecs::ServerManager>().reloadClientsGame();
}

void bomberman::WinServerScene::entityKilled(ecs::Entity entity, ecs::World &world)
{
    if (world.hasComponent<ecs::MirroredEntity>(entity))
        world.getRessource<ecs::ServerManager>().deleteClientEntity(entity, world);
    else if (world.hasComponent<ecs::MirrorEntity>(entity))
        world.getRessource<ecs::ServerManager>().killLocalEntity(entity, world);
}
