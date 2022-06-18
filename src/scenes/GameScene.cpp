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

void bomberman::successConn(ecs::World &world, void *data)
{
    bomberman::GameScene *scene = (bomberman::GameScene*) data;

    std::cout << "Connection succeed" << std::endl;
    world.getRessource<ecs::ClientManager>().initPlayers(scene->getNbPlayersOnClient());
}

void bomberman::failedConn(ecs::World &world, void *data)
{
    std::cout << "Connection falied" << std::endl;
    world.getRessource<ecs::SceneManager>().changeScene(ecs::MAIN_MENU_SCENE, nullptr);
}

void bomberman::GameScene::loadScene(ecs::World &world)
{
    ecs::ConnectionSuccessFct success = &bomberman::successConn;
    ecs::ConnectionFailedFct failed = &bomberman::failedConn;

    if (_startLocalServer)
        world.getRessource<ecs::InternalServer>().startServer(_port);
    world.getRessource<ecs::ClientManager>().attemptConnection(_ip, _port, this, success, failed);
    world.getRessource<raylib::Camera>().setPosition({0, 0, 2});
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
    world.getRessource<ecs::SceneManager>().changeScene(ecs::MAIN_MENU_SCENE, nullptr);
}

void bomberman::GameScene::playerIdAssigned(ecs::PlayerId id, ecs::World &world, InputFile file)
{
    std::cout << "player id : " << id << std::endl;
    world.spawn().insert(ecs::PlayerInputs{ file }, ecs::PlayerAction{ id }, ecs::MirrorEntity{});
}
