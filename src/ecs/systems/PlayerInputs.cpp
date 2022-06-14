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
#include "ecs/components/Player.hpp"
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
    _signature = component.generateSignature<Transform, Player, Movement>();
}

void ecs::PlayerExecuteActionUpdateSystem::update(ecs::World &world)
{
    const std::unordered_map<Actions, Vector3> MOVEMENTS = {
        {MOVE_UP, {0, 0, -1}},
        {MOVE_DOWN, {0, 0, 1}},
        {MOVE_LEFT, {-1, 0, 0}},
        {MOVE_RIGHT, {1, 0, 0}}
    };
    ecs::SceneManager &man = world.getRessource<ecs::SceneManager>();
    bomberman::ServerScene &scene = dynamic_cast<bomberman::ServerScene&>(man.getScene());

    for (ecs::Entity entity : _entities) {
        Player &player = world.getComponent<Player>(entity);
        Transform &transform = world.getComponent<Transform>(entity);
        Vector3 pos = transform.translation;
        Movement &move = world.getComponent<Movement>(entity);
        Actions action = scene.getPlayerAction(player.id);

        if (action == DO_NOTHING || move.isMoving)
            continue;
        if (action == PLACE_BOMB) {

        } else {
            Vector3 dest = pos + MOVEMENTS.at(action);

            // if (scene.getMap().getCellAt(move.dest.x, move.dest.z) == VOID || scene.getMap().getCellAt(move.dest.x, move.dest.z) == SPAWN)
                move.move(dest, 2);
            // else
            //     std::cerr << "Can't go this way :" << scene.getMap().getCellAt(move.dest.x, move.dest.z) << std::endl;
        }
    }
}
