/*
** EPITECH PROJECT, 2022
** indie
** File description:
** Ai
*/

#include "ecs/components/Ai.hpp"
#include "ecs/components/ColorTexture.hpp"
#include "Map.hpp"
#include "AiFunc.hpp"

void ecs::AiSystem::setSignature(ComponentManager &component)
{
    _signature = component.generateSignature<Ai, PlayerAction>();
}

void ecs::AiSystem::update(ecs::World &world)
{
    ecs::SceneManager &man = world.getRessource<ecs::SceneManager>();
    bomberman::GameServerScene &scene = dynamic_cast<bomberman::GameServerScene&>(man.getScene());

    for (Entity entity : _entities) {
        // Ai &ai = world.getComponent<Ai>(entity);
        PlayerAction &action = world.getComponent<PlayerAction>(entity);
        ecs::Actions newAction = ai::AiFunc::update(action.id, scene, world);
        action.action = newAction;
    }
}
