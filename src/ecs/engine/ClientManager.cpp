/*
** EPITECH PROJECT, 2022
** B-YEP-400-STG-4-1-indiestudio-mathieu.brujan
** File description:
** ClientManager
*/

#include <iostream>
#include "ecs/engine/Network.hpp"
#include "ecs/engine/EntityCommands.hpp"

void ecs::ClientManager::handleNetworkCommands(World &world)
{
    NetworkCommand cmd;

    _client->updateRWStates();
    while (_client->canRead()) {
        if (_client->read(&cmd, sizeof(NetworkCommand)) == 0) {
            _client->disconnect();
            break;
        }
        switch (cmd) {
            case NetworkCommand::UPDATE_ENTITY:
            spawnOrUpdateServerEntity(world);
            break;
            case NetworkCommand::KILL_ENTITY:
            killServerEntity(world);
            break;
        }
    }
}

void ecs::ClientManager::spawnOrUpdateServerEntity(World &world)
{
    Entity serverEntity;

    _client->read(&serverEntity, sizeof(Entity));
    if (_serverToClient.find(serverEntity) != _serverToClient.end())
        updateServerEntity(serverEntity, world);
    else
        spawnServerEntity(serverEntity, world);
}

void ecs::ClientManager::spawnServerEntity(Entity serverEntity, World &world)
{
    EntityCommands entityCmds = world.spawn();
    Entity localEntity = entityCmds.getEntity();
    std::uint32_t nbComponents;
    ComponentType componentType;
    std::uint32_t componentSize;

    std::cout << "--- Creating entity from server ---" << std::endl;
    _serverToClient.insert({serverEntity, localEntity});
    _client->read(&nbComponents, sizeof(std::uint32_t));
    std::cout << "- Entity has " << nbComponents << " components ! " << std::endl;
    for (std::uint32_t i = 0; i < nbComponents; i++) {
        _client->read(&componentType, sizeof(ComponentType));
        _client->read(&componentSize, sizeof(std::uint32_t));
        std::cout << "- Insert Component " << std::to_string((int) componentType) << std::endl;
        entityCmds.insertByType(componentType);
        _client->read(world.getComponentManager().getComponentByType(componentType, localEntity), componentSize);
    }
}

void ecs::ClientManager::updateServerEntity(Entity serverEntity, World &world)
{
    Entity localEntity = _serverToClient[serverEntity];
    std::uint32_t nbComponents;
    ComponentType componentType;
    std::uint32_t componentSize;

    std::cout << "Updating entity from server" << std::endl;
    _client->read(&nbComponents, sizeof(std::uint32_t));
    for (std::uint32_t i = 0; i < nbComponents; i++) {
        _client->read(&componentType, sizeof(ComponentType));
        _client->read(&componentSize, sizeof(std::uint32_t));
        _client->read(world.getComponentManager().getComponentByType(componentType, localEntity), componentSize);
    }
}

void ecs::ClientManager::killServerEntity(World &world)
{
    Entity serverEntity;
    Entity localEntity;

    std::cout << "Entity killed from server" << std::endl;
    _client->read(&serverEntity, sizeof(Entity));
    localEntity = _serverToClient[serverEntity];
    world.getEntityCommands(localEntity).despawn();
    _serverToClient.erase(serverEntity);
}

void ecs::ClientManager::updateLocalEntity(Entity entity, World &world)
{
    const NetworkCommand cmd = NetworkCommand::UPDATE_ENTITY;
    ComponentManager &compMan = world.getComponentManager();
    ComponentType type;
    std::uint32_t total = 0;
    std::uint32_t componentSize;

    std::cout << "Sending entity to server" << std::endl;
    for (const ComponentHash hash : MIRROR_COMPONENTS) {
        type = compMan.getComponentTypeByHash(hash);
        if (world.getComponentManager().hasComponentById(type, entity))
            total++;
    }
    _client->write((void*) &cmd, sizeof(NetworkCommand));
    _client->write(&entity, sizeof(Entity));
    _client->write(&total, sizeof(std::uint32_t));
    for (const ComponentHash hash : MIRROR_COMPONENTS) {
        type = compMan.getComponentTypeByHash(hash);
        if (world.getComponentManager().hasComponentById(type, entity)) {
            componentSize = world.getComponentManager().getComponentSize(type);
            _client->write(&type, sizeof(ComponentType));
            _client->write(&componentSize, sizeof(std::uint32_t));
            _client->write(world.getComponentManager().getComponentByType(type, entity), componentSize);
        }
    }
}

void ecs::ClientManager::killLocalEntity(Entity entity, World &world)
{
    const NetworkCommand cmd = NetworkCommand::KILL_ENTITY;

    std::cout << "Killing local entity" << std::endl;
    _client->write((void*) &cmd, sizeof(NetworkCommand));
    _client->write(&entity, sizeof(Entity));
}
