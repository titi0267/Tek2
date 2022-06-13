/*
** EPITECH PROJECT, 2022
** indieStudio
** File description:
** PlayerInputs
*/

#include "ecs/components/PlayerInputs.hpp"

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
