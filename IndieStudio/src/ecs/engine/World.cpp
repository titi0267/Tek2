/*
** EPITECH PROJECT, 2022
** epi-cs
** File description:
** World
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include "ecs/engine/World.hpp"
#include "ecs/engine/EntityCommands.hpp"
#include "raylib/Window.hpp"

void ecs::World::updateClient()
{
    raylib::Window &window = getRessource<raylib::Window>();

    getRessource<ecs::SceneManager>().executeSceneChange(*this);
    _systems.updateStage(*this, NETWORK_UPDATE);
    _systems.updateStage(*this, TIME_UPDATE);
    _systems.updateStage(*this, INPUT_UPDATE);
    _systems.updateStage(*this, UPDATE);
    _systems.updateStage(*this, RENDER_UPDATE);
    window.beginDrawing();
    window.clear(BLACK);
    _systems.updateStage(*this, DRAW_WORLD);
    _systems.updateStage(*this, DRAW_HUD);
    if (window.shouldShowFPS())
        window.drawFPS(10, 10);
    window.endDrawing();
}

void ecs::World::updateServer()
{
    getRessource<ecs::SceneManager>().executeSceneChange(*this);
    _systems.updateStage(*this, NETWORK_UPDATE);
    _systems.updateStage(*this, TIME_UPDATE);
    _systems.updateStage(*this, INPUT_UPDATE);
    _systems.updateStage(*this, UPDATE);
    _systems.updateStage(*this, RENDER_UPDATE);
}

void ecs::World::killAllEntities()
{
    std::deque<Entity> cpy = _livingEntities;

     for (Entity entity : cpy)
        EntityCommands(entity, *this).despawn();
    _entities.reset();
    _components.reset();
    _livingEntities.clear();
}

void ecs::World::decodeEntities(std::ifstream &file)
{
    std::uint32_t nbEntities;
    std::uint32_t nbComponents = 0;
    ComponentType type = 0;
    std::uint32_t componentSize = 0;

    file.read((char*) &nbEntities, sizeof(std::uint32_t));
    for (int i = 0; i < nbEntities; i++) {
        EntityCommands entityCmds = spawn();
        Entity entity = entityCmds.getEntity();

        file.read((char*) &nbComponents, sizeof(std::uint32_t));
        for (int i = 0; i < nbComponents; i++) {
            file.read((char*) &type, sizeof(ComponentType));
            file.read((char*) &componentSize, sizeof(std::uint32_t));
            entityCmds.insertByType(type);
            file.read((char*) _components.getComponentByType(type, entity), componentSize);
        }
    }
}

void ecs::World::encodeEntity(Entity entity, std::stringbuf &buffer)
{
    std::uint32_t nbComponents = 0;
    std::uint32_t componentSize = 0;
    ecs::Signature sign = _entities.getSignature(entity);
    std::stringbuf localBuf;
    std::string data;

    for (ComponentType i = 0; i < MAX_COMPONENTS; i++) {
        if (sign.test(i)) {
            nbComponents++;
            componentSize = _components.getComponentSize(i);
            localBuf.sputn((char*) &i, sizeof(ComponentType));
            localBuf.sputn((char*) &componentSize, sizeof(std::uint32_t));
            localBuf.sputn((char*) _components.getComponentByType(i, entity), componentSize);
        }
    }
    data = localBuf.str();
    buffer.sputn((char*) &nbComponents, sizeof(std::uint32_t));
    buffer.sputn(data.c_str(), data.size());
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
