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
#include "raylib/Matrix.hpp"
#include <utility>

void bomberman::ServerScene::spawnBottle(Vector3 pos, ecs::GridPosition gPos, ecs::World &world)
{
    Transform transform = {pos, QuaternionIdentity(), {1, 1, 1}};

    world.spawn().insert(transform, gPos, ecs::ModelRef {"bottle"}, ecs::MirrorEntity {});
}

void bomberman::ServerScene::spawnChair(Vector3 pos, ecs::GridPosition gPos, ecs::World &world)
{
    Transform transform = {pos, QuaternionIdentity(), {1, 1, 1}};

    world.spawn().insert(transform, ecs::ModelRef {"chair"}, ecs::MirrorEntity {});
}

void bomberman::ServerScene::spawnWall(Vector3 pos, ecs::GridPosition gPos, Vector3 size, ecs::World &world)
{

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
            pos = {(float) x - width / 2.0f, 0, (float) y - height / 2.0f};
            switch (_map.getCellAt(x, y)) {
                case DESTRUCTIBLE:
                spawnChair(pos, {x, y}, world);
                break;
                case WALL:
                spawnBottle(pos, {x, y}, world);
                break;
            }
        }
    }
}

void bomberman::ServerScene::loadScene(ecs::World &world)
{
    for (int i = 0; i < 4; i++)
        _actions.insert({i, ecs::DO_NOTHING});

    world.spawn().insert(Transform {{0, 2, 0}, QuaternionIdentity(), {1, 1, 1}}, ecs::GridPosition{0, 0},
    ecs::Movement{}, ecs::Player{0}, ecs::ModelRef("button"), ecs::MirrorEntity {});

    generateMapProps(world);
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

map::Map bomberman::ServerScene::getMap() const
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
