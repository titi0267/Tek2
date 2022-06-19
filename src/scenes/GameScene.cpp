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
#include "ecs/components/Text3D.hpp"
#include "ecs/components/CameraFollow.hpp"
#include "ecs/components/HoverRotate.hpp"
#include "ecs/components/HoverTint.hpp"
#include "ecs/components/Clickable.hpp"
#include "ecs/components/Hoverable.hpp"
#include "ecs/components/Timer.hpp"

#include "raylib/Camera.hpp"
#include "raylib/SoundManager.hpp"

#include "Setup.hpp"

void bomberman::disconnectFunction(ecs::World &world, ecs::Entity entity)
{
    world.getRessource<ecs::ClientManager>().disconnect();
    world.getRessource<ecs::SceneManager>().changeScene(ecs::MAIN_MENU_SCENE, nullptr);
}

void bomberman::successConn(ecs::World &world, void *data)
{
    bomberman::GameScene *scene = (bomberman::GameScene*) data;

    std::cout << "[CLIENT] Connection succeed" << std::endl;
    world.getRessource<ecs::ClientManager>().initPlayers(scene->getNbPlayersOnClient());
}

void bomberman::failedConn(ecs::World &world, void *data)
{
    std::cout << "[CLIENT] Connection falied" << std::endl;
    world.getRessource<ecs::SceneManager>().changeScene(ecs::MAIN_MENU_SCENE, nullptr);
}

void bomberman::GameScene::loadScene(ecs::World &world)
{
    ecs::ConnectionSuccessFct success = &bomberman::successConn;
    ecs::ConnectionFailedFct failed = &bomberman::failedConn;
    auto &man = world.getRessource<raylib::SoundManager>();
    auto &music = man.getSound("game_music");

    music.playSound();
    if (_startLocalServer)
        world.getRessource<ecs::InternalServer>().startServer(_port);
    world.getRessource<ecs::ClientManager>().attemptConnection(_ip, _port, this, success, failed);
    world.getRessource<raylib::Camera>().setPosition({0, 0, 2});
    world.getRessource<raylib::Camera>().setTarget({0, 0, 0});

    world.registerSystem<GameToggleQuitButtonSystem>();

    world.spawn().insert(Transform {{-3.5, -4, -3}, QuaternionFromEuler(0, PI / 8.0, 0), {0.3, 0.5, 0.5}},
    ecs::ModelRef{"button"}, ecs::FontRef {"emulogic"}, ecs::Text3D{"Quitter", BLACK, {0, 0, 0.1}, 12},
    ecs::Hoverable {}, ecs::HoverRotate{}, WHITE, ecs::HoverTint {WHITE, RED},
    ecs::Hitbox{{-3.0f / 2, -0.4, -0.05}, {3.0f / 2, 0.4, 0.05}},
    ecs::Clickable {disconnectFunction}, ecs::SceneMoveElement{0.1}, ecs::Timer{}, ecs::CameraFollow {});
}

void bomberman::GameScene::unloadScene(ecs::World &world)
{
    auto &man = world.getRessource<raylib::SoundManager>();
    auto &music = man.getSound("game_music");

    music.stopSound();
    if (_startLocalServer)
        world.getRessource<ecs::InternalServer>().joinAndDestroy();
    world.killAllEntities();
    world.unregisterSystem<GameToggleQuitButtonSystem>();
}

void bomberman::GameScene::entityKilled(ecs::Entity entity, ecs::World &world)
{
    ecs::ClientManager &man = world.getRessource<ecs::ClientManager>();

    if (man.isConnected() && world.hasComponent<ecs::MirrorEntity>(entity))
        man.killLocalEntity(entity, world);
    else if (world.hasComponent<ecs::MirroredEntity>(entity))
        man.deleteServerEntity(entity, world);
}

void bomberman::GameScene::onDisconnect(ecs::World &world)
{
    std::cout << "[CLIENT] Disconnect client" << std::endl;
    world.getRessource<ecs::SceneManager>().changeScene(ecs::MAIN_MENU_SCENE, nullptr);
}

void bomberman::GameScene::playerIdAssigned(ecs::PlayerId id, ecs::World &world, InputFile file)
{
    std::cout << "[CLIENT] Player ID assigned : " << id << std::endl;
    world.spawn().insert(ecs::PlayerInputs{ file }, ecs::PlayerAction{ id }, ecs::MirrorEntity{});
}
