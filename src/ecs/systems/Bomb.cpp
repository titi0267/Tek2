/*
** EPITECH PROJECT, 2022
** indieStudio
** File description:
** Bomb
*/

#include "ecs/components/Bomb.hpp"
#include "ecs/engine/Clock.hpp"
#include <unordered_map>
#include "raylib/Vectors.hpp"



void ecs::BombIdUpdateSystem::setSignature(ecs::ComponentManager &component)
{
    _signature = component.generateSignature<BombId, Transform>();
}

void ecs::BombIdUpdateSystem::update(ecs::World &world)
{
    Clock &clock = world.getRessource<Clock>();

    for (ecs::Entity entity : _entities) {
        BombId &bombId = world.getComponent<BombId>(entity);
        bombId.droppedTime += clock.getDeltaSec();
    }
}
