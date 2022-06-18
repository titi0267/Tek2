/*
** EPITECH PROJECT, 2022
** B-YEP-400-STG-4-1-indiestudio-mathieu.brujan
** File description:
** LobbyGameScene
*/

#include "scenes/LobbyServerScene.hpp"

#include "ecs/engine/Network.hpp"
#include "ecs/engine/PlayersManager.hpp"
#include "ecs/engine/SkinManager.hpp"
#include "ecs/engine/EntityCommands.hpp"

#include "ecs/components/DrawableModel.hpp"
#include "ecs/components/Skin.hpp"
#include "ecs/components/Player.hpp"
#include "ecs/components/SpawnBonus.hpp"

void bomberman::LobbyServerScene::spawnPlayer(ecs::PlayerId id, const std::string &skin, Vector3 pos, ecs::World &world)
{
    Transform transform = {pos, QuaternionIdentity(), {1, 1, 1}};
    ecs::Entity entity = world.spawn().insert(ecs::Player{id}, transform,
    ecs::ModelRef("player"), ecs::Skin{skin}, ecs::MirrorEntity {}).getEntity();

    _players.insert({id, entity});
}

void bomberman::LobbyServerScene::loadScene(ecs::World &world)
{
    world.registerSystems<LobbyExecuteActionUpdateSystem, ecs::PlayerActionUpdateSystem>();
    for (int i = 0; i < 4; i++) {
        _actions.insert({i, ecs::DO_NOTHING});
        _updatedThisFrame.insert({i, false});
    }
}

void bomberman::LobbyServerScene::unloadScene(ecs::World &world)
{
    world.killAllEntities();
    world.unregisterSystems<LobbyExecuteActionUpdateSystem, ecs::PlayerActionUpdateSystem>();
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
    ecs::SkinManager &skinMan = world.getRessource<ecs::SkinManager>();

    for (ecs::PlayerId id : ids) {
        ecs::Entity entity = _players[id];
        skinMan.unassignedSkin(id, false);
        world.getEntityCommands(entity).despawn();
        _ready.erase(id);
    }
    checkReady(world);
}

void bomberman::LobbyServerScene::onPlayerIdAttributed(ecs::PlayerId id, ecs::World &world)
{
    ecs::SkinManager &skinMan = world.getRessource<ecs::SkinManager>();
    Vector3 pos = {id * 2.0f - 3.0f, 0, -5};
    const std::string &skin = skinMan.assignRandomSkin(id);

    spawnPlayer(id, skin, pos, world);
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
