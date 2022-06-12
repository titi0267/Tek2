/*
** EPITECH PROJECT, 2022
** B-YEP-400-STG-4-1-indiestudio-mathieu.brujan
** File description:
** GameScene
*/

#include "scenes/GameScene.hpp"

#include "ecs/engine/Network.hpp"
#include "ecs/engine/InternalServer.hpp"

#include "ecs/components/ColorTexture.hpp"
#include "ecs/components/Hitbox.hpp"
#include "ecs/components/DrawableModel.hpp"

#include "Setup.hpp"

static void serverMain(ecs::World *world, bool *run, std::string *port)
{
    bomberman::registerCriticalComponents(*world);
    bomberman::registerNetwork(*world, false);

    world->insertRessource<ecs::ServerManager>();
    world->getRessource<ecs::ServerManager>().startServer(*port);

    while (*run)
        world->updateServer();

    world->getRessource<ecs::ServerManager>().closeServer();
}

void bomberman::GameScene::successConn(ecs::World &world)
{
    std::cout << "success" << std::endl;
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
        world.getRessource<ecs::InternalServer>().startServer(serverMain, _port);
    world.getRessource<ecs::ClientManager>().attemptConnection(_ip, _port, this, success, failed);
}

void bomberman::GameScene::unloadScene(ecs::World &world)
{
    if (_startLocalServer)
        world.getRessource<ecs::InternalServer>().joinAndDestroy();
    world.killAllEntities();
}
