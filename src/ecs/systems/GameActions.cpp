/*
** EPITECH PROJECT, 2022
** B-YEP-400-STG-4-1-indiestudio-mathieu.brujan
** File description:
** GameActions
*/

#include "scenes/GameServerScene.hpp"
#include "ecs/components/Player.hpp"
#include "ecs/components/Movement.hpp"
#include "ecs/components/PlayAnimation.hpp"

void bomberman::GameExecuteActionUpdateSystem::setSignature(ecs::ComponentManager &component)
{
    _signature = component.generateSignature<Transform, ecs::GridPosition, ecs::Player, ecs::Movement, ecs::PlayAnimation>();
}

void bomberman::GameExecuteActionUpdateSystem::placeBomb(ecs::Entity entity, ecs::World &world, bomberman::GameServerScene &scene)
{
    Transform &transform = world.getComponent<Transform>(entity);
    ecs::GridPosition &gPos = world.getComponent<ecs::GridPosition>(entity);
    map::Map &map = scene.getMap();

    if (map.getCellAt(gPos.x, gPos.y) != VOID && map.getCellAt(gPos.x, gPos.y) != SPAWN)
        return;
    scene.spawnBomb(transform.translation, gPos, world);
}
void bomberman::GameExecuteActionUpdateSystem::placeWater(ecs::Entity entity, ecs::World &world, bomberman::GameServerScene &scene)
{
    Transform &transform = world.getComponent<Transform>(entity);
    ecs::GridPosition &gPos = world.getComponent<ecs::GridPosition>(entity);
    map::Map &map = scene.getMap();
    ecs::BombId &bomb = world.getComponent<ecs::BombId>(entity);
    ecs::Timer &timer = world.getComponent<ecs::Timer>(entity);
    static std::vector<float> counter = {-1.0, -1.0, -1.0, -1.0};
    const std::unordered_map<ecs::Actions, Vector3> DIRECTIONS = {
        {ecs::MOVE_UP, {0, 0, -1 - counter.at(0)}},
        {ecs::MOVE_DOWN, {0, 0, 1 + counter.at(1)}},
        {ecs::MOVE_LEFT, {-1 - counter.at(2), 0, 0}},
        {ecs::MOVE_RIGHT, {1 + counter.at(3), 0, 0}}
    };

    for (auto itr = DIRECTIONS.begin(); itr != DIRECTIONS.end(); itr++) {
        Vector3 moveVec =  itr->second;
        ecs::GridPosition gDest = gPos + ecs::GridPosition {(int) moveVec.x, (int) moveVec.z};

        if (gDest.x < 0 || gDest.y < 0 || gDest.x > map.getWidth() - 1 || gDest.y > map.getHeight() - 1)
            continue;
        if (map.getCellAt(gDest.x, gDest.y) != VOID && map.getCellAt(gDest.x, gDest.y) == SPAWN)
            continue;
        if (timer.timeElapsed >= 2) {
            std::cout << "Bomb explode"<< std::endl;
            scene.spawnWater(transform.translation, gPos, world);
            counter.at(itr->first - 1) += 1;

        }
    }
}

void bomberman::GameExecuteActionUpdateSystem::movePlayer(ecs::Entity entity, ecs::World &world, ecs::Actions action, map::Map &map)
{
    const std::unordered_map<ecs::Actions, Vector3> MOVEMENTS = {
        {ecs::MOVE_UP, {0, 0, -1}},
        {ecs::MOVE_DOWN, {0, 0, 1}},
        {ecs::MOVE_LEFT, {-1, 0, 0}},
        {ecs::MOVE_RIGHT, {1, 0, 0}}
    };
    const std::unordered_map<ecs::Actions, float> ROTATIONS = {
        {ecs::MOVE_UP, PI},
        {ecs::MOVE_DOWN, 0},
        {ecs::MOVE_LEFT, 3*  PI / 2.0},
        {ecs::MOVE_RIGHT, PI / 2.0},
    };

    Transform &transform = world.getComponent<Transform>(entity);
    ecs::GridPosition &gPos = world.getComponent<ecs::GridPosition>(entity);
    ecs::Movement &move = world.getComponent<ecs::Movement>(entity);

    Vector3 moveVec =  MOVEMENTS.at(action);
    ecs::GridPosition gDest = gPos + ecs::GridPosition {(int) moveVec.x, (int) moveVec.z};

    if (gDest.x < 0 || gDest.y < 0 || gDest.x > map.getWidth() - 1 || gDest.y > map.getHeight() - 1)
        return;

    if (map.getCellAt(gDest.x, gDest.y) == VOID || map.getCellAt(gDest.x, gDest.y) == SPAWN) {
        std::cout << "[MOVE] TO " << gDest.x << ", " << gDest.y << std::endl;
        gPos = gDest;
        move.move(transform.translation + moveVec, 2);
        transform.rotation = QuaternionFromEuler(0, ROTATIONS.at(action), 0);
        world.getComponent<ecs::PlayAnimation>(entity).play("playerAnims", 0, 0.5, false);
    } else
        std::cout << "Can't go this way :" << map.getCellAt(gDest.x, gDest.y) << std::endl;
}

void bomberman::GameExecuteActionUpdateSystem::update(ecs::World &world)
{
    ecs::SceneManager &man = world.getRessource<ecs::SceneManager>();
    bomberman::GameServerScene &scene = dynamic_cast<bomberman::GameServerScene&>(man.getScene());
    map::Map &map = scene.getMap();

    for (ecs::Entity entity : _entities) {
        ecs::Player &player = world.getComponent<ecs::Player>(entity);
        ecs::Actions action = scene.getPlayerAction(player.id);
        ecs::Movement &move = world.getComponent<ecs::Movement>(entity);

        if (action == ecs::DO_NOTHING || move.isMoving)
            continue;
        if (action == ecs::PLACE_BOMB) {
            placeBomb(entity, world, scene);
        } else {
            movePlayer(entity, world, action, map);
        }
    }
}
