/*
** EPITECH PROJECT, 2022
** indieStudio
** File description:
** Bomb
*/

#include <unordered_map>
#include "ecs/components/Bomb.hpp"
#include "ecs/components/Timer.hpp"
#include "ecs/engine/Clock.hpp"
#include "raylib/Vectors.hpp"
#include "scenes/ServerScene.hpp"

void ecs::BombUpdateSystem::setSignature(ecs::ComponentManager &component)
{
    _signature = component.generateSignature<BombId, Timer, Transform>();
}

void ecs::BombUpdateSystem::update(ecs::World &world)
{
    SceneManager &man = world.getRessource<ecs::SceneManager>();
    Clock &clock = world.getRessource<Clock>();
    bomberman::ServerScene &scene = dynamic_cast<bomberman::ServerScene&>(man.getScene());

    for (ecs::Entity entity : _entities) {
        BombId &bomb = world.getComponent<BombId>(entity);
        Timer &timer = world.getComponent<Timer>(entity);
    }
}
