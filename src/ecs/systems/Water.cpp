/*
** EPITECH PROJECT, 2022
** indieStudio
** File description:
** Water
*/

#include "ecs/components/Water.hpp"
#include "ecs/components/Timer.hpp"
#include "ecs/components/GridPosition.hpp"
#include "raylib/Vectors.hpp"

void ecs::WaterUpdateSystem::setSignature(ecs::ComponentManager &component)
{
    _signature = component.generateSignature<Water, Timer, Transform, GridPosition>();
}

void ecs::WaterUpdateSystem::update(ecs::World &world)
{
    for (ecs::Entity entity : _entities) {
        Timer &timer = world.getComponent<Timer>(entity);
        Water &water = world.getComponent<Water>(entity);
        Transform &transform = world.getComponent<Transform>(entity);

        if (timer.timeElapsed >= 0.2) {
            //boum;
        }
    }
}