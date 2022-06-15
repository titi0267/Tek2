/*
** EPITECH PROJECT, 2022
** B-YEP-400-STG-4-1-indiestudio-mathieu.brujan
** File description:
** ServerScene
*/

#include "scenes/ServerScene.hpp"
#include "ecs/components/DrawableModel.hpp"
#include "ecs/components/DrawableCube.hpp"
#include "ecs/components/ColorTexture.hpp"
#include "ecs/engine/EntityCommands.hpp"
#include "ecs/components/PlayerInputs.hpp"
#include "ecs/components/Movement.hpp"
#include "ecs/components/Player.hpp"
#include "ecs/components/DrawableModel.hpp"
#include "ecs/components/Bomb.hpp"
#include "ecs/components/Timer.hpp"
#include "ecs/components/PlayAnimation.hpp"
#include "raylib/Matrix.hpp"
#include <utility>

const float ROTATIONS[4] = {
    0, PI / 2.0, PI, 3 * PI / 2.0,
};

void bomberman::ServerScene::spawnDestructible(Vector3 pos, ecs::GridPosition gPos, ecs::World &world)
{
    float rot = ROTATIONS[std::rand() % 4] + (PI / 16.0) * ((std::rand() % 100) / 100.0 - 0.5);
    Transform transform = {pos, QuaternionFromEuler(0, rot, 0), {1, 1, 1}};

    world.spawn().insert(transform, ecs::ModelRef {"bag"}, ecs::MirrorEntity {});
}

void bomberman::ServerScene::spawnWall(Vector3 pos, ecs::GridPosition gPos, ecs::World &world)
{
    float rot = ROTATIONS[std::rand() % 4] + (PI / 16.0) * ((std::rand() % 100) / 100.0 - 0.5);
    Transform transform = {pos, QuaternionFromEuler(0, rot, 0), {1, 1, 1}};

    world.spawn().insert(transform, ecs::ModelRef {"chair"}, ecs::MirrorEntity {});
}

void bomberman::ServerScene::spawnFloor(Vector2 mapSize, ecs::World &world)
{
    Transform transform = {{0, 0, 0}, QuaternionIdentity(), {1, 1, 1}};

    world.spawn().insert(transform,
    ecs::DrawableCube {{0, 0, 0}, {mapSize.x, 0.1, mapSize.y}},
    ecs::TextureRef("ground"), ecs::MirrorEntity {});
}

void bomberman::ServerScene::generateMapProps(ecs::World &world)
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

void bomberman::ServerScene::spawnPlayer(ecs::PlayerId id, Vector3 pos, ecs::GridPosition gPos, ecs::World &world)
{
    Transform transform = {pos, QuaternionIdentity(), {1, 1, 1}};
    ecs::Entity entity = world.spawn().insert(ecs::Player{id}, transform, gPos,
    ecs::Movement{}, ecs::ModelRef("player"), ecs::PlayAnimation{}, ecs::MirrorEntity {}).getEntity();

    _players.insert({id, entity});

}

void bomberman::ServerScene::spawnBomb(Vector3 pos, ecs::GridPosition gPos, ecs::World &world)
{
    Transform transform = {pos, QuaternionIdentity(), {1, 1, 1}};
    ecs::Entity entity = world.spawn().insert(ecs::BombId{}, transform, gPos,
    ecs::ModelRef {"bottle"}, ecs::Timer{}, ecs::MirrorEntity {}).getEntity();

    _bombs.insert({world.getComponent<ecs::BombId>(entity), entity});
}

void bomberman::ServerScene::deleteBomb(ecs::BombId bomb)
{
    _bombs.erase(bomb);
}

void bomberman::ServerScene::loadScene(ecs::World &world)
{
    int playerId = 0;
    int width = _map.getWidth();
    int height = _map.getHeight();
    Vector3 pos;

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
}

void bomberman::ServerScene::unloadScene(ecs::World &world)
{
    world.killAllEntities();
}

void bomberman::ServerScene::entityKilled(ecs::Entity entity,ecs::World &world)
{
    if (world.hasComponent<ecs::MirrorEntity>(entity))
        world.getRessource<ecs::ServerManager>().killLocalEntity(entity, world);
}

map::Map &bomberman::ServerScene::getMap()
{
    return _map;
}

void bomberman::ServerScene::setPlayerAction(ecs::PlayerId id, ecs::Actions action)
{
    _actions.at(id) = action;
}

ecs::Actions bomberman::ServerScene::getPlayerAction(ecs::PlayerId id) const
{
    return _actions.at(id);
}
