/*
** EPITECH PROJECT, 2022
** B-YEP-400-STG-4-1-indiestudio-mathieu.brujan
** File description:
** LobbyGameScene
*/

#include "scenes/LobbyServerScene.hpp"

#include "ecs/engine/Network.hpp"
#include "ecs/engine/PlayersManager.hpp"
#include "ecs/engine/EntityCommands.hpp"

#include "ecs/components/DrawableModel.hpp"
#include "ecs/components/Skin.hpp"
#include "ecs/components/Player.hpp"

void bomberman::LobbyServerScene::spawnPlayer(ecs::PlayerId id, Vector3 pos, ecs::World &world)
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
    _players.insert({id, entity});
}

void bomberman::LobbyServerScene::loadScene(ecs::World &world)
{
    world.registerSystem<LobbyExecuteActionUpdateSystem>();
    for (int i = 0; i < 4; i++)
        _actions.insert({i, ecs::DO_NOTHING});
}

void bomberman::LobbyServerScene::unloadScene(ecs::World &world)
{
    world.killAllEntities();
    world.unregisterSystem<LobbyExecuteActionUpdateSystem>();
}

void bomberman::LobbyServerScene::entityKilled(ecs::Entity entity,ecs::World &world)
{
    if (world.hasComponent<ecs::MirroredEntity>(entity))
        world.getRessource<ecs::ServerManager>().deleteClientEntity(entity, world);
    else if (world.hasComponent<ecs::MirrorEntity>(entity))
        world.getRessource<ecs::ServerManager>().killLocalEntity(entity, world);
}

void bomberman::LobbyServerScene::onConnect(ConnId conn, ecs::World &world)
{
    world.getRessource<ecs::ServerManager>().moveCamera(conn, {0, 0, 2}, {0, 0, 0});
}

void bomberman::LobbyServerScene::onDisconnect(ConnId conn, ecs::World &world)
{
    ecs::PlayersManager &man = world.getRessource<ecs::PlayersManager>();
    std::vector<ecs::PlayerId> ids = man.getPlayersOfConn(conn);

    for (ecs::PlayerId id : ids) {
        ecs::Entity entity = _players[id];
        world.getEntityCommands(entity).despawn();
        _ready.erase(id);
    }
    checkReady(world);
}

void bomberman::LobbyServerScene::onPlayerIdAttributed(ecs::PlayerId id, ecs::World &world)
{
    Vector3 pos = {id * 2.0f - 3.0f, 0, -5};

    spawnPlayer(id, pos, world);
    _ready.insert({id, false});
}

void bomberman::LobbyServerScene::checkReady(ecs::World &world)
{
    bool allReady = true;

    if (_ready.size() == 0)
        return;
    for (auto &[id, ready] : _ready) {
        if (!ready) {
            allReady = false;
            break;
        }
    }
    if (allReady)
        world.getRessource<ecs::SceneManager>().changeScene(ecs::SERVER_GAME_SCENE, nullptr);
}

void bomberman::LobbyServerScene::setPlayerAction(ecs::PlayerId id, ecs::Actions action)
{
    _actions.at(id) = action;
}

ecs::Actions bomberman::LobbyServerScene::getPlayerAction(ecs::PlayerId id) const
{
    return _actions.at(id);
}
