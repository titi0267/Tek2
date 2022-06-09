/*
** EPITECH PROJECT, 2022
** epi-cs
** File description:
** ClickUpdate
*/

#include "ecs/components/Clickable.hpp"

#include "raylib/Window.hpp"
#include "raylib/Camera.hpp"

#include <limits>

void ecs::ClickUpdateSystem::setSignature(ecs::ComponentManager &component)
{
    _signature = component.generateSignature<Transform, Hitbox>();
}

void ecs::ClickUpdateSystem::update(ecs::World &world)
{
    raylib::Window &window = world.getRessource<raylib::Window>();

    if (!window.isMouseButtonPressed(MOUSE_BUTTON_LEFT))
        return;

    raylib::Camera &cam = world.getRessource<raylib::Camera>();
    raylib::Ray ray = cam.getMouseRay(window.getMousePos());

    Clickable *hitClick = nullptr;
    float hitDist = std::numeric_limits<float>::max();
    ecs::Entity hitEntity;

    for (ecs::Entity entity : _entities) {
        Transform &transform = world.getComponent<Transform>(entity);
        Hitbox &hitbox = world.getComponent<Hitbox>(entity);
        BoundingBox box = hitbox.getBoundingBox(transform);
        RayCollision collision = ray.getCollisionBox(box);

        if (collision.hit && collision.distance < hitDist) {
            if (world.hasComponent<Clickable>(entity))
                hitClick = &world.getComponent<Clickable>(entity);
            else
                hitClick  = nullptr;
            hitDist = collision.distance;
            hitEntity = entity;
        }
    }

    if (hitClick)
        hitClick->callback(world, hitEntity);
}