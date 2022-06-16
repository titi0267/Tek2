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

#include <iostream>
#include "raylib/Matrix.hpp"

const float ROTATIONS[4] = {
    0, PI / 2.0, PI, 3 * PI / 2.0,
};

void bomberman::GameServerScene::spawnDestructible(Vector3 pos, ecs::GridPosition gPos, ecs::World &world)
{
    float rot = ROTATIONS[std::rand() % 4] + (PI / 16.0) * ((std::rand() % 100) / 100.0 - 0.5);
    Transform transform = {pos, QuaternionFromEuler(0, rot, 0), {1, 1, 1}};
    ecs::Entity entity = world.spawn().insert(transform, ecs::ModelRef {"bag"}, ecs::MirrorEntity {}).getEntity();

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

    world.spawn().insert(transform,
    ecs::DrawableCube {{0, 0, 0}, {mapSize.x, 0.1, mapSize.y}},
    ecs::TextureRef("ground"), ecs::MirrorEntity {});
}

void bomberman::GameServerScene::generateMapProps(ecs::World &world)
{
    int width = _map.getWidth();
    int height = _map.getHeight();
    Vector3 pos;

    spawnFloor({(float) width, (float) height}, world);
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            pos = {(float) x - width / 2.0f + 0.5f, 0, (float) y - height / 2.0f + 0.5f};
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
    Transform transform = {pos, QuaternionIdentity(), {1, 1, 1}};
    ecs::Entity entity = world.spawn().insert(ecs::Player{id}, transform, gPos,
    ecs::Movement{}, ecs::ModelRef("player"), ecs::Skin{"mathieu"}, ecs::PlayAnimation{}, ecs::MirrorEntity {}).getEntity();

    _players.insert(entity);
}

void bomberman::GameServerScene::spawnBomb(Vector3 pos, ecs::GridPosition gPos, ecs::World &world)
{
    Transform transform = {pos, QuaternionIdentity(), {1, 1, 1}};
    ecs::Entity entity = world.spawn().insert(ecs::BombId {}, transform, gPos,
    ecs::ModelRef {"bottle"}, ecs::Timer{}, ecs::MirrorEntity {}).getEntity();

    std::cout << "Spawn bomb " << (int) entity <<std::endl;
    _bombs.insert(entity);
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

    _water.insert(entity);
}

void bomberman::GameServerScene::deleteWater(ecs::Entity water)
{
    _water.erase(water);
}

void bomberman::GameServerScene::deleteDestructible(ecs::GridPosition &pos, ecs::World &world)
{
    ecs::Entity entity = _destructibles[pos];

    _destructibles.erase(pos);
    world.getEntityCommands(entity).despawn();
}

void bomberman::GameServerScene::loadScene(ecs::World &world)
{
    int playerId = 0;
    int width = _map.getWidth();
    int height = _map.getHeight();
    Vector3 pos;

    world.registerSystems<GameExecuteActionUpdateSystem,
    ecs::WaterUpdateSystem, ecs::BombUpdateSystem, ecs::MovementUpdateSystem>();

    for (int i = 0; i < 4; i++)
        _actions.insert({i, ecs::DO_NOTHING});

    generateMapProps(world);

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (_map.getCellAt(x, y) == SPAWN) {
                pos = {(float) x - width / 2.0f, 0, (float) y - height / 2.0f};
                spawnPlayer(playerId++, pos, {x, y}, world);
            }
        }
    }

    world.getRessource<ecs::PlayersManager>().stopAcceptingPlayers();
    world.getRessource<ecs::ServerManager>().moveCameras({0, 12, 5}, {0, 0, 0});
}

void bomberman::GameServerScene::unloadScene(ecs::World &world)
{
    world.killAllEntities();
    world.unregisterSystems<GameExecuteActionUpdateSystem,
    ecs::WaterUpdateSystem, ecs::BombUpdateSystem, ecs::MovementUpdateSystem>();
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
