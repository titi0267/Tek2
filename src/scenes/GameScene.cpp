/*
** EPITECH PROJECT, 2022
** B-YEP-400-STG-4-1-indiestudio-mathieu.brujan
** File description:
** GameScene
*/

#include "scenes/GameScene.hpp"

#include "ecs/engine/Network.hpp"
#include "ecs/engine/InternalServer.hpp"
#include "ecs/engine/PlayersManager.hpp"
#include "ecs/engine/EntityCommands.hpp"

#include "ecs/components/ColorTexture.hpp"
#include "ecs/components/Hitbox.hpp"
#include "ecs/components/DrawableModel.hpp"
#include "ecs/components/PlayerInputs.hpp"

#include "raylib/Camera.hpp"

#include "Setup.hpp"

void bomberman::GameScene::successConn(ecs::World &world)
{
    std::cout << "success" << std::endl;
    world.getRessource<ecs::ClientManager>().initPlayers(_nbPlayers);
}

void bomberman::GameScene::failedConn(ecs::World &world)
{
    std::cout << "failed" << std::endl;
    world.getRessource<ecs::SceneManager>().changeScene(world, ecs::MAIN_MENU_SCENE, nullptr);
}

void bomberman::GameScene::loadScene(ecs::World &world)
{
    ecs::ConnectionSuccessFct success = (ecs::ConnectionSuccessFct) &bomberman::GameScene::successConn;
    ecs::ConnectionFailedFct failed = (ecs::ConnectionFailedFct) &bomberman::GameScene::failedConn;

    if (_startLocalServer)
        world.getRessource<ecs::InternalServer>().startServer(_port);
    world.getRessource<ecs::ClientManager>().attemptConnection(_ip, _port, this, success, failed);
    world.getRessource<raylib::Camera>().setPosition({0, 12, 5});
    world.getRessource<raylib::Camera>().setTarget({0, 0, 0});
}

void bomberman::GameScene::unloadScene(ecs::World &world)
{
    if (_startLocalServer)
        world.getRessource<ecs::InternalServer>().joinAndDestroy();
    world.killAllEntities();
}

void bomberman::GameScene::entityKilled(ecs::Entity entity, ecs::World &world)
{
    if (world.getRessource<ecs::ClientManager>().isConnected()
    && world.hasComponent<ecs::MirrorEntity>(entity))
        world.getRessource<ecs::ClientManager>().killLocalEntity(entity, world);
}

void bomberman::GameScene::onDisconnect(ecs::World &world)
{
    std::cout << "disconnect" << std::endl;
    world.getRessource<ecs::SceneManager>().changeScene(world, ecs::MAIN_MENU_SCENE, nullptr);
}

void bomberman::GameScene::playerIdAssigned(ecs::PlayerId id, ecs::World &world)
{
    std::cout << "player id : " << id << std::endl;
    world.spawn().insert(ecs::PlayerInputs{}, ecs::PlayerAction{id}, ecs::MirrorEntity{});
}
