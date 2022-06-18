/*
** EPITECH PROJECT, 2022
** B-YEP-400-STG-4-1-indiestudio-mathieu.brujan
** File description:
** GameServerScene
*/

#include <utility>

#include "scenes/GameServerScene.hpp"
#include "scenes/LobbyServerScene.hpp"

#include "ecs/engine/EntityCommands.hpp"
#include "ecs/engine/PlayersManager.hpp"
#include "ecs/engine/SkinManager.hpp"

#include "ecs/components/DrawableModel.hpp"
#include "ecs/components/DrawableCube.hpp"
#include "ecs/components/ColorTexture.hpp"
#include "ecs/components/PlayerInputs.hpp"
#include "ecs/components/Movement.hpp"
#include "ecs/components/Player.hpp"
#include "ecs/components/DrawableModel.hpp"
#include "ecs/components/Bomb.hpp"
#include "ecs/components/Timer.hpp"
#include "ecs/components/Water.hpp"
#include "ecs/components/PlayAnimation.hpp"
#include "ecs/components/Skin.hpp"
#include "ecs/components/DestructibleTile.hpp"
#include "ecs/components/SpawnBonus.hpp"
#include "ecs/components/Ai.hpp"
#include "ecs/components/Grid.hpp"
#include "ecs/components/ItemRotation.hpp"

#include <iostream>
#include <filesystem>
#include "raylib/Matrix.hpp"

const float ROTATIONS[4] = {
    0, PI / 2.0, PI, 3 * PI / 2.0,
};

Vector3 bomberman::GameServerScene::mapCoordsToWorldCoords(int x, int y)
{
    int width = _map.getWidth();
    int height = _map.getHeight();
    float centeredX = x - width / 2.0f;
    float centeredY = y - height / 2.0f;

    return Vector3 {centeredX * 1.2f + 0.5f, 0, centeredY * 1.2f + 0.5f};
}

void bomberman::GameServerScene::spawnDestructible(Vector3 pos, ecs::GridPosition gPos, ecs::World &world)
{
    const ecs::Tint TINTS[5]= {
        {240, 90, 90, 255},
        {247, 235, 230, 255},
        {20, 111, 50, 255},
        {71, 20, 35, 255},
        {34, 35, 29, 255},
    };
    float rot = ROTATIONS[std::rand() % 4] + (PI / 16.0) * ((std::rand() % 100) / 100.0 - 0.5);
    Transform transform = {pos, QuaternionFromEuler(0, rot, 0), {1, 1, 1}};
    ecs::Entity entity = world.spawn().insert(transform, gPos, ecs::ModelRef {"bag"}, TINTS[std::rand() % 5],
    ecs::MirrorEntity {}, ecs::DestructibleTile {}).getEntity();

    _destructibles.insert({gPos, entity});
}

void bomberman::GameServerScene::spawnWall(Vector3 pos, ecs::GridPosition gPos, ecs::World &world)
{
    float rot = ROTATIONS[std::rand() % 4] + (PI / 16.0) * ((std::rand() % 100) / 100.0 - 0.5);
    Transform transform = {pos, QuaternionFromEuler(0, rot, 0), {1, 1, 1}};

    world.spawn().insert(transform, ecs::ModelRef {"chair"}, ecs::MirrorEntity {});
}

void bomberman::GameServerScene::spawnFloor(Vector2 mapSize, ecs::World &world)
{
    Transform transform = {{0, 0, 0}, QuaternionIdentity(), {1, 1, 1}};
    float sizeX = (mapSize.x + 1) * 1.25f;
    float sizeY = (mapSize.y + 1) * 1.25f;

    world.spawn().insert(transform,
    ecs::DrawableCube {{0, -0.1, 0}, {sizeX, 0.1, sizeY}},
    ecs::TextureRef("ground"), ecs::MirrorEntity {});
}

void bomberman::GameServerScene::generateMapProps(ecs::World &world)
{
    int width = _map.getWidth();
    int height = _map.getHeight();
    Vector3 pos;

    // spawnFloor({(float) width, (float) height}, world);
    world.spawn().insert(Transform {{0, 0, 0}, QuaternionIdentity(), {1, 1, 1}}, ecs::ModelRef{"amphi"}, ecs::MirrorEntity{});
    world.spawn().insert(Transform {{0, 0.01, 0}, QuaternionIdentity(), {1, 1, 1}}, ecs::Grid{width, 1.2}, ecs::MirrorEntity{});
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            pos = mapCoordsToWorldCoords(x, y);
            switch (_map.getCellAt(x, y)) {
                case DESTRUCTIBLE:
                spawnDestructible(pos, {x, y}, world);
                break;
                case WALL:
                spawnWall(pos, {x, y}, world);
                break;
            }
        }
    }
}

void bomberman::GameServerScene::spawnPlayer(ecs::PlayerId id, Vector3 pos, ecs::GridPosition gPos, ecs::World &world)
{
    ecs::SkinManager &skinMan = world.getRessource<ecs::SkinManager>();
    Transform transform = {pos, QuaternionIdentity(), {1, 1, 1}};

    ecs::Entity entity = world.spawn().insert(ecs::Player{id}, transform, gPos,
    ecs::Movement{}, ecs::ModelRef("player"), ecs::Skin{skinMan.getPlayerSkin(id)},
    ecs::PlayAnimation{}, ecs::MirrorEntity {}).getEntity();

    _players.insert({id, entity});
}

void bomberman::GameServerScene::createAi(ecs::PlayerId id, ecs::World &world)
{
    ecs::SkinManager &skinMan = world.getRessource<ecs::SkinManager>();

    std::cout << "Create AI #" << id << std::endl;
    skinMan.assignRandomSkin(id);
    world.spawn().insert(ecs::PlayerAction{id}, ecs::Ai{}).getEntity();
}

void bomberman::GameServerScene::spawnBomb(Vector3 pos, ecs::GridPosition gPos, ecs::Player &player, ecs::World &world)
{
    Transform transform = {pos, QuaternionIdentity(), {1, 1, 1}};
    ecs::Entity entity = world.spawn().insert(ecs::Bomb {player.id, player.bombRange}, transform, gPos,
    ecs::ModelRef {"bottle"}, ecs::Timer{}, ecs::MirrorEntity {}).getEntity();

    std::cout << "Spawn bomb " << (int) entity <<std::endl;
    _bombs.insert(entity);
    player.placedBombs++;
}

void bomberman::GameServerScene::deleteBomb(ecs::Entity bomb)
{
    _bombs.erase(bomb);
}

void bomberman::GameServerScene::spawnWater(Vector3 pos, ecs::GridPosition gPos, Vector3 dir, int distance, ecs::World &world)
{
    Transform transform = {pos, QuaternionIdentity(), {1, 1, 1}};
    ecs::Entity entity = world.spawn().insert(transform, gPos,
    ecs::ModelRef {"water"}, ecs::Timer {}, ecs::Water {dir, distance}, ecs::MirrorEntity {}).getEntity();

    std::cout << "Spawn water !" << std::endl;
    _water.insert(entity);
}

void bomberman::GameServerScene::deleteWater(ecs::Entity water)
{
    _water.erase(water);
}

void bomberman::GameServerScene::spawnBonus(Vector3 pos, ecs::GridPosition gPos, ecs::Bonus bonus, ecs::World &world)
{
    const std::unordered_map<ecs::Bonus, std::string> BONUS_TO_STR = {
        {ecs::BONUS_BOMB, "bonus_bomb"}, {ecs::BONUS_BOOTS, "bonus_boots"}, {ecs::BONUS_RANGE, "bonus_range"}, {ecs::BONUS_TIG, "bonus_tig"},
    };
    Transform transform = {pos, QuaternionIdentity(), {1, 1, 1}};
    ecs::Entity entity = world.spawn().insert(transform, gPos, ecs::ModelRef{BONUS_TO_STR.at(bonus)},
    ecs::SpawnBonus {bonus}, ecs::ItemRotation{0.5, 0.25}, ecs::Timer {}, ecs::MirrorEntity {}).getEntity();

    std::cout << "ADD " << BONUS_TO_STR.at(bonus) << std::endl;
    _bonus.insert(entity);
}

void bomberman::GameServerScene::deleteBonus(ecs::Entity bonus)
{
    _bonus.erase(bonus);
}

void bomberman::GameServerScene::deleteDestructible(ecs::GridPosition &pos, ecs::World &world)
{
    ecs::Entity entity = _destructibles[pos];

    _destructibles.erase(pos);
    world.getEntityCommands(entity).despawn();
}

void bomberman::GameServerScene::trySpawnBonus(Vector3 pos, ecs::GridPosition gPos, ecs::World &world)
{
    ecs::Bonus bonus;

    if (std::rand() % BONUS_SPAWN_INV_CHANCE == 0) {
        bonus = (ecs::Bonus) (std::rand() % ecs::BONUS_COUNT);
        spawnBonus(pos, gPos, bonus, world);
    }
}

void bomberman::GameServerScene::startNewGame(ecs::World &world)
{
    int width = _map.getWidth();
    int height = _map.getHeight();
    int playerId = 0;
    Vector3 pos;

    ecs::PlayersManager &playerMan = world.getRessource<ecs::PlayersManager>();
    while (playerMan.isIdAvailaible())
        createAi(playerMan.getNextPlayerId(), world);

    generateMapProps(world);
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (_map.getCellAt(x, y) == SPAWN) {
                pos = mapCoordsToWorldCoords(x, y);
                spawnPlayer(playerId++, pos, {x, y}, world);
            }
        }
    }
}

void bomberman::GameServerScene::loadSavedGame(ecs::World &world)
{
    ecs::SkinManager &skinMan = world.getRessource<ecs::SkinManager>();
    std::ifstream file("bombitek.dat", std::ios_base::in | std::ios_base::binary);
    ecs::PlayerId id;

    world.decodeEntities(file);
    for (ecs::Entity entity : world.getLivingEntities()) {
        if (world.hasComponent<ecs::Player>(entity)) {
            id = world.getComponent<ecs::Player>(entity).id;

            if (!skinMan.hasSkinAssigned(id))
                skinMan.assignRandomSkin(id);
            world.getComponent<ecs::Skin>(entity) = ecs::Skin(skinMan.getPlayerSkin(id));
            _players.insert({id, entity});
        } else if (world.hasComponent<ecs::Bomb>(entity))
            _bombs.insert(entity);
        else if (world.hasComponent<ecs::Water>(entity))
            _water.insert(entity);
        else if (world.hasComponent<ecs::DestructibleTile>(entity))
            _destructibles.insert({world.getComponent<ecs::GridPosition>(entity), entity});
        else if (world.hasComponent<ecs::SpawnBonus>(entity))
            _bonus.insert(entity);

        if (world.hasComponent<ecs::MirrorEntity>(entity))
            world.getComponent<ecs::MirrorEntity>(entity).size = 0;
    }
    _map.load("bombitek.map");
}

void bomberman::GameServerScene::loadScene(ecs::World &world)
{
    world.registerSystems<GameExecuteActionUpdateSystem, ecs::PlayerActionUpdateSystem,
    ecs::WaterUpdateSystem, ecs::WaterCollisionUpdateSystem,
    ecs::BombUpdateSystem, ecs::MovementUpdateSystem,
    GameCheckWinSystem, ecs::SpawnBonusUpdateSystem,
    ecs::AiSystem, ecs::PlayerUpdateSystem, ecs::PlayerCollisionUpdateSystem>();

    for (int i = 0; i < 4; i++) {
        _actions.insert({i, ecs::DO_NOTHING});
        _updatedThisFrame.insert({i, false});
    }

    if (std::filesystem::exists("bombitek.dat") && std::filesystem::exists("bombitek.map"))
        loadSavedGame(world);
    else
        startNewGame(world);

    world.getRessource<ecs::PlayersManager>().stopAcceptingPlayers();

    world.getRessource<ecs::PlayersManager>().stopAcceptingPlayers();
    world.getRessource<ecs::ServerManager>().moveCameras({0, 13, 3}, {0, 0, 0.5});
}

void bomberman::GameServerScene::unloadScene(ecs::World &world)
{
    std::ofstream file{"bombitek.dat", std::ios_base::out | std::ios_base::binary};
    std::uint32_t nbEntities = 0;
    std::stringbuf buffer{""};
    std::string data;

    _map.save("bombitek.map");
    for (ecs::Entity entity : world.getLivingEntities()) {
        if (!world.hasComponent<ecs::MirroredEntity>(entity)) {
            nbEntities++;
            world.encodeEntity(entity, buffer);
        }
    }
    data = buffer.str();
    file.write((char*) &nbEntities, sizeof(std::uint32_t));
    file.write(data.c_str(), data.size());

    world.killAllEntities();
    world.unregisterSystems<GameExecuteActionUpdateSystem, ecs::PlayerActionUpdateSystem,
    ecs::WaterUpdateSystem, ecs::WaterCollisionUpdateSystem,
    ecs::BombUpdateSystem, ecs::MovementUpdateSystem,
    GameCheckWinSystem, ecs::SpawnBonusUpdateSystem,
    ecs::AiSystem, ecs::PlayerUpdateSystem, ecs::PlayerCollisionUpdateSystem>();
}

void bomberman::GameServerScene::entityKilled(ecs::Entity entity,ecs::World &world)
{
    if (world.hasComponent<ecs::MirrorEntity>(entity))
        world.getRessource<ecs::ServerManager>().killLocalEntity(entity, world);
    else if (world.hasComponent<ecs::MirroredEntity>(entity))
        world.getRessource<ecs::ServerManager>().deleteClientEntity(entity, world);
}

map::Map &bomberman::GameServerScene::getMap()
{
    return _map;
}

void bomberman::GameServerScene::setPlayerAction(ecs::PlayerId id, ecs::Actions action)
{
    _actions.at(id) = action;
}

ecs::Actions bomberman::GameServerScene::getPlayerAction(ecs::PlayerId id) const
{
    return _actions.at(id);
}
