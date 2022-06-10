/*
** EPITECH PROJECT, 2022
** B-YEP-400-STG-4-1-indiestudio-mathieu.brujan
** File description:
** ClientManager
*/

#include <iostream>
#include <sstream>
#include "ecs/engine/Network.hpp"
#include "ecs/engine/EntityCommands.hpp"
#include "network/SocketError.hpp"

bool ecs::ClientManager::tryRead(void *buf, std::size_t size)
{
    if (!_client->isConnected())
        return true;
    if( _client->read(buf, size) != size) {
        _client->disconnect();
        return true;
    }
    return false;
}

void ecs::ClientManager::attemptConnection(const std::string &ip,
const std::string &port, ConnectionSuccessFct success, ConnectionFailedFct failed)
{
    _ip = ip;
    _port = port;
    _success = success;
    _failed = failed;
    _connAttempted = true;
    _tryConnCount = 0;
    _lastTry = std::chrono::system_clock::now();
}

void ecs::ClientManager::tryConnection(ecs::World &world)
{
    auto now = std::chrono::system_clock::now();

    if (now - _lastTry < std::chrono::milliseconds(500))
        return;
    try {
        connectTo(_ip, _port);
        std::cout << "Successfully connected to " << _ip << ":" << _port << std::endl;
        _connAttempted = false;
        _success(world);
    } catch(network::SocketError) {
        if (_tryConnCount == 5) {
            std::cout << "Failed all connection attempts" << std::endl;
            _connAttempted = false;
            _failed(world);
            return;
        }
        _lastTry = now;
        _tryConnCount++;
        std::cout << "Failed connection attempt (" << _tryConnCount << " / 5)" << std::endl;
    }
}

void ecs::ClientManager::handleNetworkCommands(World &world)
{
    NetworkCommand cmd;

    _client->updateRWStates();
    while (_client->isConnected() && _client->canRead()) {
        if (tryRead(&cmd, sizeof(NetworkCommand)))
            break;
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

bool ecs::ClientManager::readServerEntityUpdate(std::stringbuf &buffer)
{
    std::uint32_t nbComponents;
    ComponentType componentType;
    std::uint32_t componentSize;

    if (tryRead(&nbComponents, sizeof(std::uint32_t)))
        return true;
    buffer.sputn((char*) &nbComponents, sizeof(std::uint32_t));
    for (std::uint32_t i = 0; i < nbComponents; i++) {
        if (tryRead(&componentType, sizeof(ComponentType))
        ||  tryRead(&componentSize, sizeof(std::uint32_t)))
            return true;

        char tmp[componentSize];

        if (tryRead(tmp, componentSize))
            return true;
        buffer.sputn((char*) &componentType, sizeof(ComponentType));
        buffer.sputn((char*) &componentSize, sizeof(std::uint32_t));
        buffer.sputn(tmp, componentSize);
    }
    return false;
}

void ecs::ClientManager::spawnOrUpdateServerEntity(World &world)
{
    Entity serverEntity;
    std::stringbuf buffer;

    if (tryRead(&serverEntity, sizeof(Entity))
    || readServerEntityUpdate(buffer))
        return;
    if (_serverToClient.find(serverEntity) != _serverToClient.end())
        updateServerEntity(serverEntity, buffer, world);
    else
        spawnServerEntity(serverEntity, buffer, world);
}

void ecs::ClientManager::spawnServerEntity(Entity serverEntity, std::stringbuf &buffer, World &world)
{
    EntityCommands entityCmds = world.spawn();
    Entity localEntity = entityCmds.getEntity();
    std::uint32_t nbComponents;
    ComponentType componentType;
    std::uint32_t componentSize;

    std::cout << "--- Creating entity from server ---" << std::endl;
    _serverToClient.insert({serverEntity, localEntity});
    buffer.sgetn((char*) &nbComponents, sizeof(std::uint32_t));
    for (std::uint32_t i = 0; i < nbComponents; i++) {
        buffer.sgetn((char*) &componentType, sizeof(ComponentType));
        buffer.sgetn((char*) &componentSize, sizeof(std::uint32_t));
        entityCmds.insertByType(componentType);
        buffer.sgetn((char*) world.getComponentManager().getComponentByType(componentType, localEntity), componentSize);
    }
}

void ecs::ClientManager::updateServerEntity(Entity serverEntity, std::stringbuf &buffer, World &world)
{
    Entity localEntity = _serverToClient[serverEntity];
    std::uint32_t nbComponents;
    ComponentType componentType;
    std::uint32_t componentSize;

    std::cout << "Updating entity from server" << std::endl;
    buffer.sgetn((char*) &nbComponents, sizeof(std::uint32_t));
    for (std::uint32_t i = 0; i < nbComponents; i++) {
        buffer.sgetn((char*) &componentType, sizeof(ComponentType));
        buffer.sgetn((char*) &componentSize, sizeof(std::uint32_t));
        buffer.sgetn((char*) world.getComponentManager().getComponentByType(componentType, localEntity), componentSize);
    }
}

void ecs::ClientManager::killServerEntity(World &world)
{
    Entity serverEntity;
    Entity localEntity;

    if (tryRead(&serverEntity, sizeof(Entity)))
        return;
    std::cout << "Entity killed from server" << std::endl;
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

void ecs::ClientUpdateSystem::setSignature(ComponentManager &component)
{
    _signature = component.generateSignature<MirrorEntity>();
}

void ecs::ClientUpdateSystem::update(World &world)
{
    ClientManager &man = world.getRessource<ClientManager>();

    if (!man.isConnected()) {
        if (man.isConnectionAttempt())
            man.tryConnection(world);
        if (!man.isConnected())
            return;
    }
    man.handleNetworkCommands(world);
    for (Entity entity : _entities)
        man.updateLocalEntity(entity, world);
}
