/*
** EPITECH PROJECT, 2022
** epi-cs
** File description:
** World
*/

#include <iostream>
#include "ecs/engine/World.hpp"
#include "ecs/engine/EntityCommands.hpp"
#include "raylib/Window.hpp"

void ecs::World::updateClient()
{
    raylib::Window &window = getRessource<raylib::Window>();

    _systems.updateStage(*this, NETWORK_UPDATE);
    _systems.updateStage(*this, INPUT_UPDATE);
    _systems.updateStage(*this, UPDATE);
    _systems.updateStage(*this, RENDER_UPDATE);
    window.beginDrawing();
    window.clear(SKYBLUE);
    DrawFPS(10, 10);
    _systems.updateStage(*this, DRAW_WORLD);
    _systems.updateStage(*this, DRAW_HUD);
    window.endDrawing();
}

void ecs::World::updateServer()
{
    _systems.updateStage(*this, NETWORK_UPDATE);
    _systems.updateStage(*this, INPUT_UPDATE);
    _systems.updateStage(*this, UPDATE);
}

void ecs::World::killAllEntities()
{
    std::deque<Entity> cpy = _livingEntities;

     for (Entity entity : cpy)
        EntityCommands(entity, *this).despawn();
}

ecs::EntityCommands ecs::World::spawn()
{
    Entity entity = _entities.createEntity();

    _livingEntities.push_back(entity);
    return ecs::EntityCommands(entity, *this);
};

ecs::EntityCommands ecs::World::getEntityCommands(Entity entity)
{
    return ecs::EntityCommands(entity, *this);
}
