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

void ecs::ServerManager::handleNetworkCommands(World &world)
{
    NetworkCommand cmd;
    ConnId conn;

    while (_server->canAcceptConn()) {
        conn = _server->acceptClient();
        _activeConns.push_back(conn);
        _clientToServer.insert({conn, {}});
    }
    for (int i = 0; i < _activeConns.size(); i++) {
        conn = _activeConns[i];
        while (_server->canRead(conn)) {
            if (_server->read(conn, &cmd, sizeof(NetworkCommand)) == 0) {
                _activeConns.erase(_activeConns.begin() + i);
                i--;
                break;
            }
            switch (cmd) {
                case NetworkCommand::UPDATE_ENTITY:
                spawnOrUpdateClientEntity(conn, world);
                break;
                case NetworkCommand::KILL_ENTITY:
                killClientEntity(conn, world);
                break;
            }
        }
    }
}
void ecs::ServerManager::spawnOrUpdateClientEntity(ConnId conn, World &world)
{
    Entity serverEntity;
    auto &clientToServer = _clientToServer[conn];

    _server->read(conn, &serverEntity, sizeof(Entity));
    if (clientToServer.find(serverEntity) != clientToServer.end())
        updateClientEntity(conn, serverEntity, world);
    else
        spawnClientEntity(conn, serverEntity, world);
}

void ecs::ServerManager::spawnClientEntity(ConnId conn, Entity serverEntity,World &world)
{
    EntityCommands entityCmds = world.spawn();
    Entity localEntity = entityCmds.getEntity();
    std::uint32_t nbComponents;
    ComponentType componentType;
    std::uint32_t componentSize;

    std::cout << "--- Creating entity from client ---" << std::endl;
    _clientToServer[conn].insert({serverEntity, localEntity});
    _server->read(conn, &nbComponents, sizeof(std::uint32_t));
    for (std::uint32_t i = 0; i < nbComponents; i++) {
        _server->read(conn, &componentType, sizeof(ComponentType));
        _server->read(conn, &componentSize, sizeof(std::uint32_t));
        entityCmds.insertByType(componentType);
        _server->read(conn, world.getComponentManager().getComponentByType(componentType, localEntity), componentSize);
    }
    for (ConnId activeConn : _activeConns) {
        if (activeConn != conn)
            sendUpdateLocalEntity(activeConn, localEntity, nbComponents, world);
    }
}

void ecs::ServerManager::updateClientEntity(ConnId conn, Entity serverEntity, World &world)
{
    Entity localEntity = _clientToServer[conn][serverEntity];
    std::uint32_t nbComponents;
    ComponentType componentType;
    std::uint32_t componentSize;

    std::cout << "Updating entity from client" << std::endl;
    _server->read(conn, &nbComponents, sizeof(std::uint32_t));
    for (std::uint32_t i = 0; i < nbComponents; i++) {
        _server->read(conn, &componentType, sizeof(ComponentType));
        _server->read(conn, &componentSize, sizeof(std::uint32_t));
        _server->read(conn, world.getComponentManager().getComponentByType(componentType, localEntity), componentSize);
    }
    for (ConnId activeConn : _activeConns) {
        if (activeConn != conn)
            sendUpdateLocalEntity(activeConn, localEntity, nbComponents, world);
    }
}

void ecs::ServerManager::killClientEntity(ConnId conn, World &world)
{
    Entity serverEntity;
    Entity localEntity;

    std::cout << "Killing entity from client" << std::endl;
    _server->read(conn, &serverEntity, sizeof(Entity));
    localEntity = _clientToServer[conn][serverEntity];
    world.getEntityCommands(localEntity).despawn();
    _clientToServer[conn].erase(serverEntity);
    for (ConnId activeConn : _activeConns) {
        if (activeConn != conn)
            sendKillLocalEntity(activeConn, localEntity);
    }
}

void ecs::ServerManager::updateLocalEntity(Entity entity, World &world)
{
    ComponentManager &compMan = world.getComponentManager();
    ComponentType type;
    std::uint32_t total = 0;

    std::cout << "Updating entity to clients" << std::endl;
    for (const ComponentHash hash : MIRROR_COMPONENTS) {
        type = compMan.getComponentTypeByHash(hash);
        if (world.getComponentManager().hasComponentById(type, entity))
            total++;
    }
    for (ConnId conn : _activeConns) {
        sendUpdateLocalEntity(conn, entity, total, world);
    }
}

void ecs::ServerManager::killLocalEntity(Entity entity, World &world)
{
    std::cout << "Killing entity to clients" << std::endl;
    for (ConnId conn : _activeConns)
        sendKillLocalEntity(conn, entity);
}

void ecs::ServerManager::sendUpdateLocalEntity(ConnId conn, Entity localEntity, std::uint32_t total, World &world)
{
    const NetworkCommand cmd = NetworkCommand::UPDATE_ENTITY;
    ComponentManager &compMan = world.getComponentManager();
    ComponentType type;
    std::uint32_t componentSize;

    _server->write(conn, (void*) &cmd, sizeof(NetworkCommand));
    _server->write(conn, &localEntity, sizeof(Entity));
    _server->write(conn, &total, sizeof(std::uint32_t));
    for (const ComponentHash hash : MIRROR_COMPONENTS) {
        type = compMan.getComponentTypeByHash(hash);
        if (world.getComponentManager().hasComponentById(type, localEntity)) {
            componentSize = world.getComponentManager().getComponentSize(type);
            _server->write(conn, &type, sizeof(ComponentType));
            _server->write(conn, &componentSize, sizeof(std::uint32_t));
            _server->write(conn, world.getComponentManager().getComponentByType(type, localEntity), componentSize);
        }
    }
}

void ecs::ServerManager::sendKillLocalEntity(ConnId conn, Entity localEntity)
{
    const NetworkCommand cmd = NetworkCommand::KILL_ENTITY;

    _server->write(conn, (void*) &cmd, sizeof(NetworkCommand));
    _server->write(conn, &localEntity, sizeof(Entity));
}
