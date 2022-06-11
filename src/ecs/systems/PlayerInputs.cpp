/*
** EPITECH PROJECT, 2022
** indieStudio
** File description:
** PlayerInputs
*/

#include "ecs/components/PlayerInputs.hpp"

void ecs::PlayerInputsUpdateSystem::setSignature(ecs::ComponentManager &component)
{
    _signature = component.generateSignature<PlayerInputs>();
}

void ecs::PlayerInputsUpdateSystem::update(ecs::World &world)
{
    raylib::Window &window = world.getRessource<raylib::Window>();

    for (ecs::Entity entity : _entities) {
        PlayerInputs &input = world.getComponent<PlayerInputs>(entity);

        input.action = DO_NOTHING;
        if (window.isKeyDown(input.bombKey))
            input.action = PLACE_BOMB;
        else if (window.isKeyDown(input.upKey) ^ window.isKeyDown(input.downKey))
            input.action = window.isKeyDown(input.upKey) ? MOVE_UP : MOVE_DOWN;
        else if (window.isKeyDown(input.leftKey) ^ window.isKeyDown(input.rightKey))
            input.action = window.isKeyDown(input.leftKey) ? MOVE_LEFT : MOVE_RIGHT;
   }
}
