/*
** EPITECH PROJECT, 2022
** epi-cs
** File description:
** Hoverable
*/

#include "ecs/components/Hoverable.hpp"
#include "ecs/components/HoverTint.hpp"
#include "ecs/components/ColorTexture.hpp"

#include "raylib/Window.hpp"
#include "raylib/Camera.hpp"

void ecs::HoverUpdateSystem::setSignature(ecs::ComponentManager &component)
{
    _signature = component.generateSignature<Transform, Hoverable, Hitbox>();
}

void ecs::HoverUpdateSystem::update(ecs::World &world)
{
    raylib::Window &window = world.getRessource<raylib::Window>();
    raylib::Camera &cam = world.getRessource<raylib::Camera>();
    raylib::Ray ray = cam.getMouseRay(window.getMousePos());

    Hoverable *hitHover = nullptr;
    float hitDist = MAXFLOAT;
    ecs::Entity hitEntity;

    for (ecs::Entity entity : _entities) {
        Transform &transform = world.getComponent<Transform>(entity);
        Hitbox &hitbox = world.getComponent<Hitbox>(entity);
        Hoverable &hover = world.getComponent<Hoverable>(entity);

        BoundingBox box = hitbox.getBoundingBox(transform);
        RayCollision collision = ray.getCollisionBox(box);

        hover.updated = hover.isHover != false;
        hover.isHover = false;
        if (collision.hit && collision.distance < hitDist) {
            hitHover = &hover;
            hitDist = collision.distance;
            hitEntity = entity;
        }
    }

    if (hitHover) {
        hitHover->isHover = true;
        hitHover->updated = !hitHover->updated;
    }
}

void ecs::HoverTintUpdateSystem::setSignature(ecs::ComponentManager &component)
{
    _signature = component.generateSignature<Tint, Hoverable>();
}

void ecs::HoverTintUpdateSystem::update(ecs::World &world)
{
    for (ecs::Entity entity : _entities) {
        Hoverable &hover = world.getComponent<Hoverable>(entity);

        if (!hover.updated)
            continue;
        if (hover.isHover)
            world.getComponent<Tint>(entity) = SKYBLUE;
        else
            world.getComponent<Tint>(entity) = WHITE;
    }
}
