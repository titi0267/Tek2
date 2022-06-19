/*
** EPITECH PROJECT, 2022
** indieStudio
** File description:
** Win
*/

#include "ecs/components/Win.hpp"
#include "ecs/components/Timer.hpp"
#include "ecs/engine/Clock.hpp"
#include "ecs/engine/SceneManager.hpp"
#include "ecs/engine/Network.hpp"

void ecs::WinUpdateSystem::setSignature(ecs::ComponentManager &component)
{
    _signature = component.generateSignature<Win, Timer>();
}

void ecs::WinUpdateSystem::update(ecs::World &world)
{
    Clock &clock = world.getRessource<Clock>();

    for (ecs::Entity entity : _entities) {
        Win &win = world.getComponent<Win>(entity);
        Timer &timer = world.getComponent<Timer>(entity);

        timer.timeElapsed += clock.getDeltaSec();
        if (timer.timeElapsed >= 5)
            world.getRessource<ecs::SceneManager>().changeScene(SERVER_LOBBY_SCENE, nullptr);
    }
}
