/*
** EPITECH PROJECT, 2022
** B-YEP-400-STG-4-1-indiestudio-mathieu.brujan
** File description:
** ServerManager
*/

#include <iostream>
#include <iterator>
#include "ecs/engine/Network.hpp"
#include "ecs/engine/EntityCommands.hpp"

bool ecs::ServerManager::tryRead(ConnId conn, void *buf, std::size_t size)
{
    if (!_server->doesConnExists(conn))
        return true;
    if(_server->read(conn, buf, size) != size) {
        _server->disconnectConn(conn);
        return true;
    }
    return false;
}

void ecs::ServerManager::acceptNewConns()
{
    network::ConnId conn;

    while (_server->canAcceptConn()) {
        conn = _server->acceptClient();
        _activeConns.push_back(conn);
        _clientToServer.insert({conn, {}});
    }
}

void ecs::ServerManager::handleNetworkCommands(World &world)
{
    NetworkCommand cmd;
    ConnId conn;

    for (int i = 0; i < _activeConns.size(); i++) {
        conn = _activeConns[i];
        while (_server->doesConnExists(conn) && _server->canRead(conn)) {
            if (tryRead(conn, &cmd, sizeof(NetworkCommand)))
                break;
            switch (cmd) {
                case NetworkCommand::UPDATE_ENTITY:
                spawnOrUpdateClientEntity(conn, world);
                break;
                case NetworkCommand::KILL_ENTITY:
                killClientEntity(conn, world);
                break;
            }
        }
        if (!_server->doesConnExists(conn)) {
            _activeConns.erase(std::find(_activeConns.begin(), _activeConns.end(), conn));
            i--;
        }
    }
}

bool ecs::ServerManager::readClientEntityUpdate(ConnId conn, std::stringbuf &buffer)
{
    std::uint32_t nbComponents;
    ComponentType componentType;
    std::uint32_t componentSize;

    if (tryRead(conn, &nbComponents, sizeof(std::uint32_t)))
        return true;
    buffer.sputn((char*) &nbComponents, sizeof(std::uint32_t));
    for (std::uint32_t i = 0; i < nbComponents; i++) {
        if (tryRead(conn, &componentType, sizeof(ComponentType))
        ||  tryRead(conn, &componentSize, sizeof(std::uint32_t)))
            return true;

        std::string tmp;
        tmp.reserve(componentSize);

        if (tryRead(conn, tmp.data(), componentSize))
            return true;
        buffer.sputn((char*) &componentType, sizeof(ComponentType));
        buffer.sputn((char*) &componentSize, sizeof(std::uint32_t));
        buffer.sputn(tmp.data(), componentSize);
    }
    return false;
}

void ecs::ServerManager::spawnOrUpdateClientEntity(ConnId conn, World &world)
{
    auto &clientToServer = _clientToServer[conn];
    Entity serverEntity;
    std::stringbuf buffer;

    if (tryRead(conn, &serverEntity, sizeof(Entity)))
        return;
    readClientEntityUpdate(conn, buffer);
    if (clientToServer.find(serverEntity) != clientToServer.end())
        updateClientEntity(conn, serverEntity, buffer, world);
    else
        spawnClientEntity(conn, serverEntity, buffer, world);
}

void ecs::ServerManager::spawnClientEntity(ConnId conn, Entity serverEntity, std::stringbuf &buffer, World &world)
{
    const NetworkCommand cmd = NetworkCommand::UPDATE_ENTITY;
    EntityCommands entityCmds = world.spawn();
    Entity localEntity = entityCmds.getEntity();
    std::uint32_t nbComponents;
    ComponentType componentType;
    std::uint32_t componentSize;
    std::string data = buffer.str();

    std::cout << "--- Creating entity from server ---" << std::endl;
    _clientToServer[conn].insert({serverEntity, localEntity});
    for (ConnId client : _activeConns) {
        if (client == conn)
            continue;
        _server->write(client, (void*) &cmd, sizeof(NetworkCommand));
        _server->write(client, (void*) &serverEntity, sizeof(Entity));
        _server->write(client, (void*) data.c_str(), data.size());
    }
    buffer.sgetn((char*) &nbComponents, sizeof(std::uint32_t));
    for (std::uint32_t i = 0; i < nbComponents; i++) {
        buffer.sgetn((char*) &componentType, sizeof(ComponentType));
        buffer.sgetn((char*) &componentSize, sizeof(std::uint32_t));
        entityCmds.insertByType(componentType);
        buffer.sgetn((char*) world.getComponentManager().getComponentByType(componentType, localEntity), componentSize);
    }
}

void ecs::ServerManager::updateClientEntity(ConnId conn, Entity serverEntity, std::stringbuf &buffer, World &world)
{
    const NetworkCommand cmd = NetworkCommand::UPDATE_ENTITY;
    Entity localEntity = _clientToServer[conn][serverEntity];
    std::uint32_t nbComponents;
    ComponentType componentType;
    std::uint32_t componentSize;
    std::string data = buffer.str();

    std::cout << "Updating entity from server" << std::endl;
    for (ConnId client : _activeConns) {
        if (client == conn)
            continue;
        _server->write(client, (void*) &cmd, sizeof(NetworkCommand));
        _server->write(client, (void*) &serverEntity, sizeof(Entity));
        _server->write(client, (void*) data.c_str(), data.size());
    }
    buffer.sgetn((char*) &nbComponents, sizeof(std::uint32_t));
    for (std::uint32_t i = 0; i < nbComponents; i++) {
        buffer.sgetn((char*) &componentType, sizeof(ComponentType));
        buffer.sgetn((char*) &componentSize, sizeof(std::uint32_t));
        buffer.sgetn((char*) world.getComponentManager().getComponentByType(componentType, localEntity), componentSize);
    }
}

void ecs::ServerManager::killClientEntity(ConnId conn, World &world)
{
    Entity clientEntity;
    Entity localEntity;
    std::stringbuf buffer;
    std::string data;

    std::cout << "Killing entity from client" << std::endl;
    if (tryRead(conn, &clientEntity, sizeof(Entity)))
        return;
    localEntity = _clientToServer[conn][clientEntity];
    world.getEntityCommands(localEntity).despawn();
    _clientToServer[conn].erase(localEntity);
    createKillLocalEntityBuffer(localEntity, buffer);
    data = buffer.str();
    for (ConnId activeConn : _activeConns) {
        if (activeConn != conn)
            _server->write(activeConn, (void*) data.c_str(), data.size());
    }
}

void ecs::ServerManager::createUpdateLocalEntityBuffer(Entity entity, World &world, std::stringbuf &buffer)
{
    const NetworkCommand cmd = NetworkCommand::UPDATE_ENTITY;
    ComponentManager &compMan = world.getComponentManager();
    std::uint32_t total = 0;
    ComponentType type;
    std::uint32_t componentSize;

    for (const ComponentHash hash : MIRROR_COMPONENTS) {
        type = compMan.getComponentTypeByHash(hash);
        if (world.getComponentManager().hasComponentById(type, entity))
            total++;
    }
    buffer.sputn((char*) &cmd, sizeof(NetworkCommand));
    buffer.sputn((char*) &entity, sizeof(Entity));
    buffer.sputn((char*) &total, sizeof(std::uint32_t));
    for (const ComponentHash hash : MIRROR_COMPONENTS) {
        type = compMan.getComponentTypeByHash(hash);
        if (world.getComponentManager().hasComponentById(type, entity)) {
            componentSize = world.getComponentManager().getComponentSize(type);
            buffer.sputn((char*) &type, sizeof(ComponentType));
            buffer.sputn((char*) &componentSize, sizeof(std::uint32_t));
            buffer.sputn((char*) world.getComponentManager().getComponentByType(type, entity), componentSize);
        }
    }
}

void ecs::ServerManager::createKillLocalEntityBuffer(Entity entity, std::stringbuf &buffer)
{
    const NetworkCommand cmd = NetworkCommand::KILL_ENTITY;

    buffer.sputn((char*) &cmd, sizeof(NetworkCommand));
    buffer.sputn((char*) &entity, sizeof(Entity));
}

void ecs::ServerManager::updateLocalEntity(Entity entity, World &world)
{
    std::stringbuf buffer;
    createUpdateLocalEntityBuffer(entity, world, buffer);
    std::string data = buffer.str();

    std::cout << "Updating entity to clients" << std::endl;
    for (ConnId conn : _activeConns)
        _server->write(conn, (void*) data.c_str(), data.size());
}

void ecs::ServerManager::killLocalEntity(Entity entity, World &world)
{
    std::stringbuf buffer;
    createKillLocalEntityBuffer(entity, buffer);
    std::string data = buffer.str();

    std::cout << "Killing entity to clients" << std::endl;
    for (ConnId conn : _activeConns)
        _server->write(conn, (void*) data.c_str(), data.size());
}

void ecs::ServerUpdateSystem::setSignature(ComponentManager &component)
{
    _signature = component.generateSignature<MirrorEntity>();
}

void ecs::ServerUpdateSystem::update(World &world)
{
    ServerManager &man = world.getRessource<ServerManager>();

    man.acceptNewConns();
    man.handleNetworkCommands(world);
    for (Entity entity : _entities)
        man.updateLocalEntity(entity, world);
}
