/*
** EPITECH PROJECT, 2022
** B-YEP-400-STG-4-1-indiestudio-mathieu.brujan
** File description:
** Timer
*/

#include "ecs/engine/Clock.hpp"
#include "ecs/components/Timer.hpp"

void ecs::TimerUpdateSystem::setSignature(ecs::ComponentManager &component)
{
    _signature = component.generateSignature<Timer>();
}

void ecs::TimerUpdateSystem::update(ecs::World &world)
{
    ecs::Clock &clock = world.getRessource<ecs::Clock>();

    for (Entity entity : _entities) {
        ecs::Timer &timer = world.getComponent<ecs::Timer>(entity);

        timer.timeElapsed += clock.getDeltaSec();
    }
}
