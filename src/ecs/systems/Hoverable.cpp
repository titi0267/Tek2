/*
** EPITECH PROJECT, 2022
** epi-cs
** File description:
** Hoverable
*/

#include "ecs/components/Hoverable.hpp"
#include "ecs/components/HoverTint.hpp"
#include "ecs/components/HoverRotate.hpp"
#include "ecs/components/ColorTexture.hpp"

#include "raylib/Window.hpp"
#include "raylib/Camera.hpp"

#include <iostream>
#include <limits>

void ecs::HoverUpdateSystem::setSignature(ecs::ComponentManager &component)
{
    _signature = component.generateSignature<Transform, Hitbox>();
}

void ecs::HoverUpdateSystem::update(ecs::World &world)
{
    raylib::Window &window = world.getRessource<raylib::Window>();
    raylib::Camera &cam = world.getRessource<raylib::Camera>();
    raylib::Ray ray = cam.getMouseRay(window.getMousePos());

    Hoverable *hitHover = nullptr;
    float hitDist = std::numeric_limits<float>::max();
    ecs::Entity hitEntity;

    for (ecs::Entity entity : _entities) {
        Transform &transform = world.getComponent<Transform>(entity);
        Hitbox &hitbox = world.getComponent<Hitbox>(entity);

        BoundingBox box = hitbox.getBoundingBox(transform);
        RayCollision collision = ray.getCollisionBox(box);

        if (world.hasComponent<Hoverable>(entity)) {
            Hoverable &hover = world.getComponent<Hoverable>(entity);

            hover.updated = hover.isHover != false;
            hover.isHover = false;
        }
        if (collision.hit && collision.distance < hitDist) {
            if (world.hasComponent<Hoverable>(entity))
                hitHover = &world.getComponent<Hoverable>(entity);
            else
                hitHover  = nullptr;
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
    _signature = component.generateSignature<Tint, Hoverable, HoverTint>();
}

void ecs::HoverTintUpdateSystem::update(ecs::World &world)
{
    for (ecs::Entity entity : _entities) {
        Hoverable &hover = world.getComponent<Hoverable>(entity);
        HoverTint &hoverTint = world.getComponent<HoverTint>(entity);
        if (!hover.updated)
            continue;
        if (hover.isHover)
            world.getComponent<Tint>(entity) = hoverTint.onHover;
        else
            world.getComponent<Tint>(entity) = hoverTint.base;
    }
}

void ecs::HoverRotateUpdateSystem::setSignature(ecs::ComponentManager &component)
{
    _signature = component.generateSignature<Hoverable, Transform, HoverRotate>();
}

void ecs::HoverRotateUpdateSystem::update(ecs::World &world)
{
    for (ecs::Entity entity : _entities) {
        Hoverable &hover = world.getComponent<Hoverable>(entity);
        Transform &transform = world.getComponent<Transform>(entity);
        HoverRotate &rotate = world.getComponent<HoverRotate>(entity);
        Vector3 rot = QuaternionToEuler(transform.rotation);

        if (rotate.inRotation) {
            rot.x += PI / 4.0 / 15;
            transform.rotation = QuaternionFromEuler(rot.x, rot.y, rot.z);
            if (!hover.isHover && rot.x <= 1e-04 && rot.x >= -1e-04) {
                rot.x = 0;
                rotate.inRotation = false;
            }
        }
        else if (hover.isHover)
            rotate.inRotation = true;
    }
}
