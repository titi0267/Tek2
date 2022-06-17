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
    _signature = component.generateSignature<Transform, AiSystem, PlayerAction>();
}

void ecs::AiSystem::update(ecs::World &world)
{
    map::Map &map = world.getRessource<map::Map>();
    ecs::SceneManager &man = world.getRessource<ecs::SceneManager>();
    bomberman::GameServerScene &scene = dynamic_cast<bomberman::GameServerScene&>(man.getScene());


    for (Entity entity : _entities) {
        AiSystem &ai = world.getComponent<AiSystem>(entity);
        PlayerAction &action = world.getComponent<PlayerAction>(entity);
        ecs::Actions newAction = AiFunc::update(map, scene, world, world.getComponent<GridPosition>(entity));
        action.action = newAction;
    }
}
