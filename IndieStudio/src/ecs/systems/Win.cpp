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
    _signature.set();
}

void ecs::WinUpdateSystem::update(ecs::World &world)
{
    _time += world.getRessource<Clock>().getDeltaSec();

    if (_time >= 10)
        world.getRessource<ecs::SceneManager>().changeScene(SERVER_LOBBY_SCENE, nullptr);
}
