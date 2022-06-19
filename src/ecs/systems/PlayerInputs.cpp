/*
** EPITECH PROJECT, 2022
** indieStudio
** File description:
** PlayerInputs
*/

#include <iostream>

#include "ecs/engine/SceneManager.hpp"

#include "ecs/components/PlayerInputs.hpp"
#include "ecs/components/Movement.hpp"
#include "ecs/components/Bomb.hpp"
#include "ecs/components/Player.hpp"
#include "ecs/components/PlayAnimation.hpp"

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
        if (input.gamepad) {
            if (window.isButtonDown(0, (GamepadButton)input.bombKey))
                action.action = PLACE_BOMB;
            else if ((tmp = window.isButtonDown(0, (GamepadButton)input.upKey)) ^ window.isButtonDown(0, (GamepadButton)input.downKey))
                action.action = tmp ? MOVE_UP : MOVE_DOWN;
            else if ((tmp = window.isButtonDown(0, (GamepadButton)input.leftKey)) ^ window.isButtonDown(0, (GamepadButton)input.rightKey))
                action.action = tmp ? MOVE_LEFT : MOVE_RIGHT;
        }
        else {
            if (window.isKeyDown((KeyboardKey)input.bombKey))
                action.action = PLACE_BOMB;
            else if ((tmp = window.isKeyDown((KeyboardKey)input.upKey)) ^ window.isKeyDown((KeyboardKey)input.downKey))
                action.action = tmp ? MOVE_UP : MOVE_DOWN;
            else if ((tmp = window.isKeyDown((KeyboardKey)input.leftKey)) ^ window.isKeyDown((KeyboardKey)input.rightKey))
                action.action = tmp ? MOVE_LEFT : MOVE_RIGHT;
        }
   }
}

void ecs::PlayerActionUpdateSystem::setSignature(ecs::ComponentManager &component)
{
    _signature = component.generateSignature<PlayerAction>();
}

void ecs::PlayerActionUpdateSystem::update(ecs::World &world)
{
    ecs::SceneManager &man = world.getRessource<ecs::SceneManager>();
    ecs::SceneActionsHandleModule &scene = dynamic_cast<ecs::SceneActionsHandleModule&>(man.getScene());

    for (ecs::Entity entity : _entities) {
        PlayerAction &action = world.getComponent<PlayerAction>(entity);

        scene.setActionUpdatedThisFrame(action.id, scene.getPlayerAction(action.id) != action.action);
        scene.setPlayerAction(action.id, action.action);
    }
}
