/*
** EPITECH PROJECT, 2022
** indieStudio
** File description:
** PlayerInputs
*/

#include "ecs/components/PlayerInputs.hpp"
#include "ecs/components/Movement.hpp"
#include "ecs/engine/SceneManager.hpp"
#include "scenes/ServerScene.hpp"
#include "ecs/components/Bomb.hpp"
#include "ecs/components/Player.hpp"
#include "ecs/components/PlayAnimation.hpp"
#include "ecs/components/Timer.hpp"
#include <iostream>

void ecs::PlayerInputsUpdateSystem::setSignature(ecs::ComponentManager &component)
{
    _signature = component.generateSignature<PlayerInputs, PlayerAction>();
}

void ecs::PlayerInputsUpdateSystem::update(ecs::World &world)
{
    raylib::Window &window = world.getRessource<raylib::Window>();
    bool tmp;

    for (ecs::Entity entity : _entities) {
        PlayerInputs &input = world.getComponent<PlayerInputs>(entity);
        PlayerAction &action = world.getComponent<PlayerAction>(entity);

        action.action = DO_NOTHING;
        if (window.isKeyDown(input.bombKey))
            action.action = PLACE_BOMB;
        else if ((tmp = window.isKeyDown(input.upKey)) ^ window.isKeyDown(input.downKey))
            action.action = tmp ? MOVE_UP : MOVE_DOWN;
        else if ((tmp = window.isKeyDown(input.leftKey)) ^ window.isKeyDown(input.rightKey))
            action.action = tmp ? MOVE_LEFT : MOVE_RIGHT;
   }
}

void ecs::PlayerActionUpdateSystem::setSignature(ecs::ComponentManager &component)
{
    _signature = component.generateSignature<PlayerAction>();
}

void ecs::PlayerActionUpdateSystem::update(ecs::World &world)
{
    ecs::SceneManager &man = world.getRessource<ecs::SceneManager>();
    bomberman::ServerScene &scene = dynamic_cast<bomberman::ServerScene&>(man.getScene());

    for (ecs::Entity entity : _entities) {
        PlayerAction &action = world.getComponent<PlayerAction>(entity);

        scene.setPlayerAction(action.id, action.action);
    }
}

void ecs::PlayerExecuteActionUpdateSystem::setSignature(ecs::ComponentManager &component)
{
    _signature = component.generateSignature<Transform, GridPosition, Player, Movement, PlayAnimation>();
}

void ecs::PlayerExecuteActionUpdateSystem::placeBomb(Entity entity, World &world, bomberman::ServerScene &scene)
{
    Transform &transform = world.getComponent<Transform>(entity);
    GridPosition &gPos = world.getComponent<GridPosition>(entity);
    map::Map &map = scene.getMap();

    if (map.getCellAt(gPos.x, gPos.y) != VOID && map.getCellAt(gPos.x, gPos.y) != SPAWN)
        return;
    scene.spawnBomb(transform.translation, gPos, world);
    //placWater(scene.getBomb())
}

void ecs::PlayerExecuteActionUpdateSystem::placeWater(Entity entity, World &world, bomberman::ServerScene &scene)
{
    Transform &transform = world.getComponent<Transform>(entity);
    GridPosition &gPos = world.getComponent<GridPosition>(entity);
    map::Map &map = scene.getMap();
    BombId &bomb = world.getComponent<BombId>(entity);
    Timer &timer = world.getComponent<Timer>(entity);
    static std::vector<float> counter = {-1.0, -1.0, -1.0, -1.0};
    const std::unordered_map<Actions, Vector3> DIRECTIONS = {
        {MOVE_UP, {0, 0, -1 - counter.at(0)}},
        {MOVE_DOWN, {0, 0, 1 + counter.at(1)}},
        {MOVE_LEFT, {-1 - counter.at(2), 0, 0}},
        {MOVE_RIGHT, {1 + counter.at(3), 0, 0}}
    };

    for (auto itr = DIRECTIONS.begin(); itr != DIRECTIONS.end(); itr++) {
        Vector3 moveVec =  itr->second;
        GridPosition gDest = gPos + GridPosition {(int) moveVec.x, (int) moveVec.z};

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

void ecs::PlayerExecuteActionUpdateSystem::movePlayer(Entity entity, World &world, Actions action, map::Map &map)
{
    const std::unordered_map<Actions, Vector3> MOVEMENTS = {
        {MOVE_UP, {0, 0, -1}},
        {MOVE_DOWN, {0, 0, 1}},
        {MOVE_LEFT, {-1, 0, 0}},
        {MOVE_RIGHT, {1, 0, 0}}
    };
    const std::unordered_map<Actions, float> ROTATIONS = {
        {MOVE_UP, PI},
        {MOVE_DOWN, 0},
        {MOVE_LEFT, 3*  PI / 2.0},
        {MOVE_RIGHT, PI / 2.0},
    };

    Transform &transform = world.getComponent<Transform>(entity);
    GridPosition &gPos = world.getComponent<GridPosition>(entity);
    Movement &move = world.getComponent<Movement>(entity);

    Vector3 moveVec =  MOVEMENTS.at(action);
    GridPosition gDest = gPos + GridPosition {(int) moveVec.x, (int) moveVec.z};

    if (gDest.x < 0 || gDest.y < 0 || gDest.x > map.getWidth() - 1 || gDest.y > map.getHeight() - 1)
        return;

    if (map.getCellAt(gDest.x, gDest.y) == VOID || map.getCellAt(gDest.x, gDest.y) == SPAWN) {
        std::cout << "[MOVE] TO " << gDest.x << ", " << gDest.y << std::endl;
        gPos = gDest;
        move.move(transform.translation + moveVec, 2);
        transform.rotation = QuaternionFromEuler(0, ROTATIONS.at(action), 0);
        world.getComponent<PlayAnimation>(entity).play("playerAnims", 0, 0.5, false);
    } else
        std::cout << "Can't go this way :" << map.getCellAt(gDest.x, gDest.y) << std::endl;
}

void ecs::PlayerExecuteActionUpdateSystem::update(ecs::World &world)
{
    ecs::SceneManager &man = world.getRessource<ecs::SceneManager>();
    bomberman::ServerScene &scene = dynamic_cast<bomberman::ServerScene&>(man.getScene());
    map::Map &map = scene.getMap();

    for (ecs::Entity entity : _entities) {
        Player &player = world.getComponent<Player>(entity);
        Actions action = scene.getPlayerAction(player.id);
        Movement &move = world.getComponent<Movement>(entity);

        if (action == DO_NOTHING || move.isMoving)
            continue;
        if (action == PLACE_BOMB) {
            placeBomb(entity, world, scene);
        } else {
            movePlayer(entity, world, action, map);
        }
    }
}
