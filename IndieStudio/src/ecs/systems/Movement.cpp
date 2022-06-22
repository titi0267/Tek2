/*
** EPITECH PROJECT, 2022
** indieStudio
** File description:
** Movement
*/

#include "ecs/engine/Clock.hpp"
#include "ecs/components/Movement.hpp"
#include "ecs/components/Player.hpp"
#include "ecs/engine/SceneManager.hpp"
#include "raylib/Vectors.hpp"

void ecs::MovementUpdateSystem::setSignature(ecs::ComponentManager &component)
{
    _signature = component.generateSignature<Movement, Transform>();
}

void ecs::MovementUpdateSystem::update(ecs::World &world)
{
    Clock &clock = world.getRessource<Clock>();

    for (ecs::Entity entity : _entities) {
        Transform &transform = world.getComponent<Transform>(entity);
        Vector3 &pos = transform.translation;
        Movement &move = world.getComponent<Movement>(entity);

        if (!move.isMoving)
            continue;

        if (world.hasComponent<ecs::Player>(entity)) {
            ecs::Player &player = world.getComponent<ecs::Player>(entity);
            if (player.alive && player.tigDuration > 0)
                continue;
        }

        Vector3 moveVec = normalize(move.dest - pos);
        float actualDistance = distance(pos, move.dest);
        Vector3 movement = moveVec * move.speed * clock.getDeltaSec();
        float endRange = distance(move.dest, move.dest + movement);

        if (actualDistance <= endRange) {
            pos = move.dest;
            move.isMoving = false;
            continue;
        }
        pos += movement;
    }
}