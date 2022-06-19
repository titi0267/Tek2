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
#include "ecs/components/Light.hpp"
#include "ecs/components/Text3D.hpp"
#include "ecs/components/CameraFollow.hpp"

void bomberman::LobbyServerScene::spawnPlayer(ecs::PlayerId id, ecs::World &world)
{
    ecs::SkinManager &skinMan = world.getRessource<ecs::SkinManager>();
    std::string skin;
    const Vector3 CAM_POS = {-5, 0, 3};

    float posAngle = PI - PI / 12.0 + PI / 20.0 + id * PI / 5.0f;
    Vector3 pos = CAM_POS + Vector3 {std::cos(posAngle) * 6, 0, std::sin(posAngle) * 6};

    float rotAngle = std::atan2(CAM_POS.x - pos.x, CAM_POS.z - pos.z);
    Quaternion rot = QuaternionFromEuler(0, rotAngle, 0);

    if (skinMan.hasSkinAssigned(id))
        skin = skinMan.getPlayerSkin(id);
    else
        skin = skinMan.assignRandomSkin(id);

    ecs::Entity entity = world.spawn().insert(ecs::Player{id}, Transform {pos, rot, {1, 1, 1}},
    ecs::ModelRef("player"), ecs::Skin{skin}, ecs::Light{Vector4 {1.0, 0.0, 0.0, 1.0}, Vector3 {0, 2, 0}}, ecs::MirrorEntity {}).getEntity();

    _players.insert({id, entity});
    _ready.insert({id, false});
}

void bomberman::LobbyServerScene::loadScene(ecs::World &world)
{
    ecs::ServerManager &man = world.getRessource<ecs::ServerManager>();
    char buf[255];

    world.registerSystems<LobbyExecuteActionUpdateSystem, ecs::PlayerActionUpdateSystem>();
    for (int i = 0; i < 4; i++) {
        _actions.insert({i, ecs::DO_NOTHING});
        _updatedThisFrame.insert({i, false});
    }
    std::snprintf(buf, 255, "%s %hu", man.getIp().c_str(), man.getPort());
    world.spawn().insert(Transform{{0, 0, 0}, QuaternionIdentity(), {1, 1, 1}}, ecs::ModelRef{"amphi"}, ecs::MirrorEntity{});
    world.spawn().insert(Transform{{0, 0, 0}, QuaternionIdentity(), {1, 1, 1}}, ecs::Light{Vector3{-1, -1, -1}, Vector4{0.8, 0.8, 0.8, 1.0}}, ecs::MirrorEntity{});

    world.spawn().insert(Transform{{0, 3.5, -5}, QuaternionIdentity(), {1, 1, 1}}, ecs::ModelRef{"large_button"}, ecs::FontRef{"emulogic"},
    ecs::Text3D{buf, BLACK, {0, 0, 0.1}, 12}, ecs::CameraFollow{}, ecs::MirrorEntity{});

    world.spawn().insert(Transform{{0, -0.8, -2}, QuaternionIdentity(), {0.3, 0.3, 0.3}}, ecs::ModelRef{"button"}, ecs::FontRef{"emulogic"},
    ecs::Text3D{"</> : Skins", BLACK, {0, 0, 0.1}, 12}, ecs::CameraFollow{}, ecs::MirrorEntity{});
    world.spawn().insert(Transform{{0, -1, -2}, QuaternionIdentity(), {0.3, 0.3, 0.3}}, ecs::ModelRef{"button"}, ecs::FontRef{"emulogic"},
    ecs::Text3D{" ^ : Ready", BLACK, {0, 0, 0.1}, 12}, ecs::CameraFollow{}, ecs::MirrorEntity{});
    world.getRessource<ecs::ServerManager>().moveCameras({-5, 4.5, 3}, {-10, -2, -2});

    for (ecs::PlayerId id : man.getAssignedIds())
        spawnPlayer(id, world);
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
    world.getRessource<ecs::ServerManager>().moveCamera(conn, {-5, 4.5, 3}, {-10, -2, -2});
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
    spawnPlayer(id, world);
}

void bomberman::LobbyServerScene::setPlayerReady(ecs::PlayerId id, ecs::World &world)
{
    _ready[id] ^= 1;
    if (_ready[id])
        world.getComponent<ecs::Light>(_players[id]).color = Vector4 {0.0, 1.0, 0.5, 1.0};
    else
        world.getComponent<ecs::Light>(_players[id]).color = Vector4 {1.0, 0.0, 0.0, 1.0};
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
