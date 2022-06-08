/*
** EPITECH PROJECT, 2022
** bomberman
** File description:
** MoveMenu
*/

#include "ecs/components/MoveMenu.hpp"
#include "ecs/engine/World.hpp"

void ecs::MoveMenuElementSystem::setSignature(ecs::ComponentManager &component)
{
    _signature = component.generateSignature<Transform,MoveMenu>();
}


bool ecs::MoveMenuElementSystem::moveRight(Vector3 &translation, MoveMenu &moveMenu)
{
    if (translation.x < moveMenu.destination.x)
        translation.x += moveMenu.speed;
    if (translation.y < moveMenu.destination.y)
        translation.y += moveMenu.speed;
    if (translation.z < moveMenu.destination.z)
        translation.z += moveMenu.speed;
    if (translation.x >= moveMenu.destination.x && translation.y >= moveMenu.destination.y && translation.z >= moveMenu.destination.z) {
        translation = moveMenu.destination;
        return (false);
    }
    return (true);
}

bool ecs::MoveMenuElementSystem::moveLeft(Vector3 &translation, MoveMenu &moveMenu)
{
    if (translation.x > moveMenu.destination.x)
        translation.x -= moveMenu.speed;
    if (translation.y > moveMenu.destination.y)
        translation.y -= moveMenu.speed;
    if (translation.z > moveMenu.destination.z)
        translation.z -= moveMenu.speed;
    if (translation.x <= moveMenu.destination.x && translation.y <= moveMenu.destination.y && translation.z <= moveMenu.destination.z) {
        translation = moveMenu.destination;
        return (false);
    }
    return (true);
}

void ecs::MoveMenuElementSystem::update(ecs::World &world)
{
    bool *right = nullptr;
    bool *left = nullptr;
    bool *up = nullptr;
    bool *down = nullptr;

    for (ecs::Entity entity : _entities) {
        Transform &transform = world.getComponent<Transform>(entity);
        MoveMenu &moveMenu = world.getComponent<MoveMenu>(entity);

        right = moveMenu.right;
        left = moveMenu.left;
        up = moveMenu.up;
        down = moveMenu.down;
        if (*right || *left || *down || *up) {
            if (moveMenu.inMovementLeft || moveMenu.inMovementRight || moveMenu.inMovementUp || moveMenu.inMovementDown)
                break;
            moveMenu.destination = transform.translation;
            if (*right) {
                moveMenu.inMovementRight = true;
                moveMenu.destination.x += 10;
            }
            if (*left) {
                moveMenu.inMovementLeft = true;
                moveMenu.destination.x -= 10;
            }
            if (*down) {
                moveMenu.inMovementDown = true;
                moveMenu.destination.y += 10;
            }
            if (*up) {
                moveMenu.inMovementUp = true;
                moveMenu.destination.y -= 10;
            }
        }
        if (moveMenu.inMovementRight)
            moveMenu.inMovementRight = moveRight(transform.translation, moveMenu);
        if (moveMenu.inMovementLeft)
            moveMenu.inMovementLeft = moveLeft(transform.translation, moveMenu);
        if (moveMenu.inMovementDown)
            moveMenu.inMovementDown = moveRight(transform.translation, moveMenu);
        if (moveMenu.inMovementUp)
            moveMenu.inMovementUp = moveLeft(transform.translation, moveMenu);
    }
    *right = false;
    *left = false;
    *up = false;
    *down = false;
}
