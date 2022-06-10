/*
** EPITECH PROJECT, 2022
** indieStudio
** File description:
** PlayerMovement
*/

#include "ecs/components/PlayerMovement.hpp"

void ecs::PlayerMovementUpdateSystem::setSignature(ecs::ComponentManager &component)
{
    _signature = component.generateSignature<PlayerMovement, Transform>();
}

void ecs::PlayerMovementUpdateSystem::update(ecs::World &world)
{
    for (ecs::Entity entity : _entities) {
        PlayerMovement &playerMovement = world.getComponent<PlayerMovement>(entity);
        Transform &transform = world.getComponent<Transform>(entity);

        //playerMovement.chooseDir = world.
    }
}