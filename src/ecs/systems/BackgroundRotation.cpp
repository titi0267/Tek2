/*
** EPITECH PROJECT, 2022
** B-YEP-400-STG-4-1-indiestudio-mathieu.brujan
** File description:
** BackgroundRotation
*/

#include <iostream>
#include "ecs/components/BackgroundRotation.hpp"
#include "ecs/components/Timer.hpp"
#include "raylib/Vectors.hpp"

void ecs::BackgroundRotationUpdateSystem::setSignature(ecs::ComponentManager &component)
{
    _signature = component.generateSignature<Transform, Timer, BackgroundRotation>();
}

void ecs::BackgroundRotationUpdateSystem::update(ecs::World &world)
{
    for (Entity entity : _entities) {
        Transform &transform = world.getComponent<Transform>(entity);
        Timer &timer = world.getComponent<Timer>(entity);
        float pitch = std::sin(timer.timeElapsed / 15.0 * PI) * PI / 64.0;
        float yaw = std::cos(timer.timeElapsed / 10.0 * PI) * PI / 64.0;

        if (timer.timeElapsed >= 60.0)
            timer.timeElapsed = fmod(timer.timeElapsed, 60.0);
        transform.rotation = QuaternionFromEuler(pitch, yaw, PI);
    }
}
