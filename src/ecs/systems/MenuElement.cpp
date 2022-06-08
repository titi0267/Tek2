/*
** EPITECH PROJECT, 2022
** bomberman
** File description:
** MenuElement
*/

#include "ecs/components/MenuElement.hpp"

#include "ecs/engine/World.hpp"

#include "raylib/Window.hpp"

#include <iostream>

void ecs::MenuElementSystem::setSignature(ecs::ComponentManager &component)
{
    _signature = component.generateSignature<Transform, MenuElement>();
}

bool ecs::MenuElementSystem::move(Vector3 &translation, bool active, MenuMovement pos)
{
    Vector3 destination = active ? pos.active.translation : pos.passive.translation;
    std::cout << "------------------------- " << pos.move << std::endl;
    std::cout << translation.x << " " << destination.x << std::endl;
    std::cout << translation.y << " " << destination.y << std::endl;
    std::cout << translation.z << " " << destination.z << std::endl;
    if (active != pos.right && translation.x > destination.x)// || (move < 0 && ))
        translation.x -= pos.move;
    if (active == pos.right && translation.x < destination.x)
        translation.x += pos.move;
    if (active != pos.right && translation.y > destination.y)// || (move < 0 && ))
        translation.y -= pos.move;
    if (active == pos.right && translation.y < destination.y)
        translation.y += pos.move;
    if (active != pos.right && translation.z > destination.z)// || (move < 0 && ))
        translation.z -= pos.move;
    if (active == pos.right && translation.z < destination.z)
        translation.z += pos.move;
    if (active == pos.right && (translation.x >= destination.x && translation.y >= destination.y && translation.z >= destination.z)) {
        translation = destination;
        return (false);
    }
    if (active != pos.right && (translation.x <= destination.x && translation.y <= destination.y && translation.z <= destination.z)) {
        translation = destination;
        return (false);
    }
    return (true);
}

void ecs::MenuElementSystem::update(ecs::World &world)
{
    for (ecs::Entity entity : _entities) {
        Transform &transform = world.getComponent<Transform>(entity);
        MenuElement &menuElem = world.getComponent<MenuElement>(entity);

        std::cout << menuElem.travel << std::endl;
        if (!(*menuElem.change) && !menuElem.travel)
            return;
        menuElem.travel = move(transform.translation, *menuElem.actual == menuElem.belong, menuElem.pos);
    }
}
