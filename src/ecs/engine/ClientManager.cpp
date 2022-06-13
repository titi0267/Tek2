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
#include "ecs/engine/SceneManager.hpp"
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

void ecs::ClientManager::handleDisconnect(World &world)
{
    ecs::SceneManager &man = world.getRessource<ecs::SceneManager>();
    NetworkSceneModule &scene = dynamic_cast<NetworkSceneModule&>(man.getScene());

    scene.onDisconnect(world);
}

void ecs::ClientManager::attemptConnection(const std::string &ip, const std::string &port,
void *obj, ConnectionSuccessFct success, ConnectionFailedFct failed)
{
    _ip = ip;
    _port = port;
    _obj = obj;
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
        std::cout << "[CLIENT] Successfully connected to " << _ip << ":" << _port << std::endl;
        _connAttempted = false;
        _success(_obj, world);
    } catch(network::SocketError) {
        if (_tryConnCount == 5) {
            std::cout << "[CLIENT] Failed all connection attempts" << std::endl;
            _connAttempted = false;
            _failed(_obj, world);
            return;
        }
        _lastTry = now;
        _tryConnCount++;
        std::cout << "[CLIENT] Failed connection attempt (" << _tryConnCount << " / 5)" << std::endl;
    }
}

void ecs::ClientManager::initPlayers(std::uint32_t nbPlayers)
{
    NetworkCommand cmd = NetworkCommand::INIT_PLAYERS;

    _client->write(&cmd, sizeof(NetworkCommand));
    _client->write(&nbPlayers, sizeof(std::uint32_t));
}

void ecs::ClientManager::handleNetworkCommands(World &world)
{
    NetworkCommand cmd;

    _client->updateRWStates();
    while (_client->isConnected() && _client->canRead()) {
        std::cout << "[CLIENT] Read from server" << std::endl;
        if (tryRead(&cmd, sizeof(NetworkCommand)))
            break;
        std::cout << "[CLIENT] CMD " << (int) cmd << " from server" << std::endl;
        switch (cmd) {
            case NetworkCommand::UPDATE_ENTITY:
            spawnOrUpdateServerEntity(world);
            break;
            case NetworkCommand::KILL_ENTITY:
            killServerEntity(world);
            break;
            case NetworkCommand::PLAYERS_CREATED:
            handlePlayersCreated(world);
            break;
            case NetworkCommand::DISCONNECT_CLIENT:
            case NetworkCommand::PLAYERS_REJECTED:
            _client->disconnect();
            break;
        }
    }
    if (!_client->isConnected())
        handleDisconnect(world);
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

        std::string tmp;
        tmp.reserve(componentSize);

        if (tryRead(tmp.data(), componentSize))
            return true;
        buffer.sputn((char*) &componentType, sizeof(ComponentType));
        buffer.sputn((char*) &componentSize, sizeof(std::uint32_t));
        buffer.sputn(tmp.data(), componentSize);
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

    std::cout << "[CLIENT] Creating entity from server" << std::endl;
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

    std::cout << "[CLIENT] Updating entity from server" << std::endl;
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
    std::cout << "[CLIENT] Entity killed from server" << std::endl;
    localEntity = _serverToClient[serverEntity];
    world.getEntityCommands(localEntity).despawn();
    _serverToClient.erase(serverEntity);
}

void ecs::ClientManager::updateLocalEntity(Entity entity, World &world)
{
    NetworkCommand cmd = NetworkCommand::UPDATE_ENTITY;
    ComponentManager &compMan = world.getComponentManager();
    ComponentType type;
    std::uint32_t total = 0;
    std::uint32_t componentSize;

    std::cout << "[CLIENT] Sending entity to server" << std::endl;
    for (const ComponentHash hash : MIRROR_COMPONENTS) {
        type = compMan.getComponentTypeByHash(hash);
        if (world.getComponentManager().hasComponentById(type, entity))
            total++;
    }
    _client->write(&cmd, sizeof(NetworkCommand));
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
    NetworkCommand cmd = NetworkCommand::KILL_ENTITY;

    std::cout << "[CLIENT] Killing local entity" << std::endl;
    _client->write(&cmd, sizeof(NetworkCommand));
    _client->write(&entity, sizeof(Entity));
}

void ecs::ClientManager::handlePlayersCreated(World &world)
{
    ecs::SceneManager &man = world.getRessource<ecs::SceneManager>();
    NetworkSceneModule &scene = dynamic_cast<NetworkSceneModule&>(man.getScene());
    int nbPlayers = scene.getNbPlayersOnClient();
    PlayerId id;

    std::cout << "[CLIENT] Players created" << std::endl;
    for (int i = 0; i < nbPlayers; i++) {
        if (tryRead(&id, sizeof(PlayerId)))
            return;
        scene.playerIdAssigned(id, world);
    }
}

void ecs::ClientUpdateSystem::setSignature(ComponentManager &component)
{
    _signature = component.generateSignature<MirrorEntity>();
}

void ecs::ClientUpdateSystem::update(World &world)
{
    ClientManager &man = world.getRessource<ClientManager>();

    if (!man.isConnected()) {
        if (!man.isConnectionAttempt())
            return;
        man.tryConnection(world);
        if (!man.isConnected())
            return;
    }
    man.handleNetworkCommands(world);
    for (Entity entity : _entities)
        man.updateLocalEntity(entity, world);
}
