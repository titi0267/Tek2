/*
** EPITECH PROJECT, 2022
** B-YEP-400-STG-4-1-indiestudio-mathieu.brujan
** File description:
** ItemRotation
*/

#include <iostream>
#include "ecs/components/ItemRotation.hpp"
#include "ecs/components/Timer.hpp"
#include "raylib/Vectors.hpp"

void ecs::ItemRotationUpdateSystem::setSignature(ecs::ComponentManager &component)
{
    _signature = component.generateSignature<Transform, ItemRotation, Timer>();
}

void ecs::ItemRotationUpdateSystem::update(ecs::World &world)
{
    for (Entity entity : _entities) {
        Transform &transform = world.getComponent<Transform>(entity);
        ItemRotation &rot = world.getComponent<ItemRotation>(entity);
        Timer &timer = world.getComponent<Timer>(entity);
        float advance = rot.speed * timer.timeElapsed;

        if (advance >= 1) {
            timer.timeElapsed = std::fmod(timer.timeElapsed, 1.0 / rot.speed);
            advance = std::fmod(advance, 1.0f);
        }
        transform.translation.y = std::sin(advance * 2 * PI) * rot.height + rot.height / 2.0;
        transform.rotation = QuaternionFromEuler(0, advance * 2 * PI, 0);
    }
}
