/*
** EPITECH PROJECT, 2022
** B-YEP-400-STG-4-1-indiestudio-mathieu.brujan
** File description:
** InternalServer
*/

#include "ecs/engine/Network.hpp"
#include "ecs/engine/Clock.hpp"

#include "ecs/engine/InternalServer.hpp"
#include "ecs/engine/SceneManager.hpp"
#include "ecs/engine/PlayersManager.hpp"

#include "ecs/components/PlayerInputs.hpp"
#include "ecs/components/Movement.hpp"
#include "ecs/components/Bomb.hpp"
#include "ecs/components/BombExplosion.hpp"
#include "ecs/components/Timer.hpp"
#include "ecs/components/Water.hpp"
#include "ecs/components/Player.hpp"
#include "ecs/components/PlayAnimation.hpp"
#include "ecs/components/GridPosition.hpp"

#include "raylib/AnimationManager.hpp"

#include "Setup.hpp"
#include "Assets.hpp"

void ecs::InternalServer::serverMain()
{
    bomberman::registerCriticalComponents(*_serverWorld);
    bomberman::registerNetwork(*_serverWorld, false);

    _serverWorld->insertRessource<ServerManager>();
    _serverWorld->insertRessource<PlayersManager>(4);
    _serverWorld->insertRessource<SceneManager>();
    _serverWorld->insertRessource<raylib::AnimationManager>();
    _serverWorld->insertRessource<ecs::Clock>();

    _serverWorld->registerComponents<ecs::BombId, ecs::Water, ecs::BombExplosion,
    ecs::Timer, ecs::Player, ecs::GridPosition>();
    _serverWorld->registerSystems<ecs::WaterUpdateSystem, ecs::BombUpdateSystem, ecs::BombExplosionUpdateSystem,
    ecs::TimerUpdateSystem, ecs::PlayerActionUpdateSystem, ecs::MovementUpdateSystem,
    ecs::AnimationUpdateSystem>();

// ------

    _serverWorld->getRessource<ServerManager>().startServer(_port);
    _serverWorld->getRessource<SceneManager>().loadServerScene(*_serverWorld);

    bomberman::loadAnimations(*_serverWorld);

    ecs::Clock &clock = _serverWorld->getRessource<Clock>();

    const std::chrono::system_clock::duration updateDuration = std::chrono::milliseconds(50);
    std::chrono::system_clock::time_point prevUpdate = std::chrono::system_clock::now();

    while (_run) {
        std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
        std::chrono::system_clock::duration lastUpdateDur = now - prevUpdate;

        std::this_thread::sleep_for(updateDuration - lastUpdateDur);

        clock.update();
        _serverWorld->updateServer();
        prevUpdate = now;
    }

    _serverWorld->getRessource<ecs::ServerManager>().closeServer();
}

void ecs::InternalServer::startServer(const std::string &port)
{
    _port = port;
    _run = true;
    _serverWorld = std::make_unique<ecs::World>();
    _thread = std::thread(&ecs::InternalServer::serverMain, this);
}

void ecs::InternalServer::joinAndDestroy()
{
    if (!_run)
        return;
    _run = false;
    _thread.join();
    _serverWorld.reset();
    _thread = std::thread();
}
