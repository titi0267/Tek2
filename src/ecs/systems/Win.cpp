/*
** EPITECH PROJECT, 2022
** indieStudio
** File description:
** Win
*/

#include "ecs/components/Win.hpp"
#include "ecs/components/Timer.hpp"
#include "ecs/engine/Clock.hpp"
#include "ecs/engine/Network.hpp"

void ecs::WinUpdateSystem::setSignature(ecs::ComponentManager &component)
{
    _signature = component.generateSignature<Win, Timer>();
}

void ecs::WinUpdateSystem::update(ecs::World &world)
{
    static float pos = 0;
    Clock &clock = world.getRessource<Clock>();

    for (ecs::Entity entity : _entities) {
        Win &win = world.getComponent<Win>(entity);
        Timer &timer = world.getComponent<Timer>(entity);

        world.getRessource<ecs::ServerManager>().moveCameras({0, 14, 4}, {0, 0, 0});
    }
}