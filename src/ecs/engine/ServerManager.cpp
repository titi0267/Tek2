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
#include "ecs/engine/PlayersManager.hpp"

void ecs::ServerManager::sendCmd(ConnId conn, NetworkCommand cmd)
{
    _server->write(conn, (void*) &cmd, sizeof(NetworkCommand));
}

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

std::vector<network::ConnId> ecs::ServerManager::acceptNewConns(ecs::World &world)
{
    SceneManager &man = world.getRessource<ecs::SceneManager>();
    ServerNetworkSceneModule &scene = dynamic_cast<ServerNetworkSceneModule&>(man.getScene());
    network::ConnId conn;
    std::vector<network::ConnId> newConns;

    while (_server->canAcceptConn()) {
        conn = _server->acceptClient();
        _activeConns.push_back(conn);
        _clientToServer.insert({conn, {}});
        newConns.push_back(conn);
        scene.onConnect(conn, world);
    }
    return newConns;
}

void ecs::ServerManager::handleClientDisconnection(ConnId conn, World &world)
{
    SceneManager &man = world.getRessource<ecs::SceneManager>();
    ServerNetworkSceneModule &scene = dynamic_cast<ServerNetworkSceneModule&>(man.getScene());
    auto &entitites = _clientToServer[conn];

    scene.onDisconnect(conn, world);
    for (auto &[client, local] : entitites)
        world.getEntityCommands(local).despawn();
    world.getRessource<PlayersManager>().clientDisconnect(conn);
    _clientToServer.erase(conn);
    _activeConns.erase(std::find(_activeConns.begin(), _activeConns.end(), conn));
}

void ecs::ServerManager::handleNetworkCommands(World &world)
{
    NetworkCommand cmd;
    ConnId conn;

    for (int i = 0; i < _activeConns.size(); i++) {
        conn = _activeConns[i];
        while (_server->doesConnExists(conn) && _server->canRead(conn)) {
            if (!_server->canWrite(conn))
                break;
            if (tryRead(conn, &cmd, sizeof(NetworkCommand)))
                break;
            switch (cmd) {
                case NetworkCommand::UPDATE_ENTITY:
                spawnOrUpdateClientEntity(conn, world);
                break;
                case NetworkCommand::KILL_ENTITY:
                killClientEntity(conn, world);
                break;
                case NetworkCommand::INIT_PLAYERS:
                initPlayers(conn, world);
                break;
            }
        }
        if (!_server->doesConnExists(conn)) {
            handleClientDisconnection(conn, world);
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

void ecs::ServerManager::spawnClientEntity(ConnId conn, Entity clientEntity, std::stringbuf &buffer, World &world)
{
    EntityCommands entityCmds = world.spawn();
    Entity localEntity = entityCmds.getEntity();
    std::uint32_t nbComponents;
    ComponentType componentType;
    std::uint32_t componentSize;
    std::string data = buffer.str();

    std::cout << "[SERVER] Creating entity from server, " << conn << ", " << (int) clientEntity << " -> " << (int) localEntity << std::endl;
    _clientToServer[conn].insert({clientEntity, localEntity});
    // for (ConnId client : _activeConns) {
    //     if (client == conn)
    //         continue;
    //     sendCmd(client, NetworkCommand::UPDATE_ENTITY);
    //     _server->write(client, (void*) &serverEntity, sizeof(Entity));
    //     _server->write(client, (void*) data.c_str(), data.size());
    // }
    buffer.sgetn((char*) &nbComponents, sizeof(std::uint32_t));
    for (std::uint32_t i = 0; i < nbComponents; i++) {
        buffer.sgetn((char*) &componentType, sizeof(ComponentType));
        buffer.sgetn((char*) &componentSize, sizeof(std::uint32_t));
        entityCmds.insertByType(componentType);
        buffer.sgetn((char*) world.getComponentManager().getComponentByType(componentType, localEntity), componentSize);
    }
    entityCmds.insert(MirroredEntity{conn, clientEntity});
}

void ecs::ServerManager::updateClientEntity(ConnId conn, Entity clientEntity, std::stringbuf &buffer, World &world)
{
    Entity localEntity = _clientToServer[conn][clientEntity];
    std::uint32_t nbComponents;
    ComponentType componentType;
    std::uint32_t componentSize;
    std::string data = buffer.str();

    // std::cout << "[SERVER] Updating entity from client" << std::endl;
    // for (ConnId client : _activeConns) {
    //     if (client == conn)
    //         continue;
    //     sendCmd(client, NetworkCommand::UPDATE_ENTITY);
    //     _server->write(client, (void*) &serverEntity, sizeof(Entity));
    //     _server->write(client, (void*) data.c_str(), data.size());
    // }
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

    // std::cout << "[SERVER] Killing entity from client" << std::endl;
    if (tryRead(conn, &clientEntity, sizeof(Entity)))
        return;
    localEntity = _clientToServer[conn][clientEntity];
    world.getEntityCommands(localEntity).despawn();
    _clientToServer[conn].erase(localEntity);
    createKillLocalEntityBuffer(localEntity, buffer);
    data = buffer.str();
    // for (ConnId activeConn : _activeConns) {
    //     if (activeConn != conn)
    //         _server->write(activeConn, (void*) data.c_str(), data.size());
    // }
}

void ecs::ServerManager::updateLocalEntity(Entity entity, World &world)
{
    std::stringbuf buffer;
    createUpdateLocalEntityBuffer(entity, world, buffer);
    std::string data = buffer.str();
    MirrorEntity &mirror = world.getComponent<MirrorEntity>(entity);

    if (mirror.prevData == data)
        return;
    // std::cout << "[SERVER] Updating entity to clients" << std::endl;
    // std::cout << "Buffer size: " << data.size() << std::endl;
    for (ConnId conn : _activeConns)
        _server->write(conn, (void*) data.c_str(), data.size());
    mirror.prevData = data;
}

void ecs::ServerManager::killLocalEntity(Entity entity, World &world)
{
    std::stringbuf buffer;
    createKillLocalEntityBuffer(entity, buffer);
    std::string data = buffer.str();

    // std::cout << "[SERVER] Killing entity to clients" << std::endl;
    for (ConnId conn : _activeConns)
        _server->write(conn, (void*) data.c_str(), data.size());
}

void ecs::ServerManager::sendEntityToNewConns(std::vector<network::ConnId> &newConns, Entity entity, World &world)
{
    MirrorEntity &mirror = world.getComponent<MirrorEntity>(entity);

    for (network::ConnId conn : newConns)
        _server->write(conn, (void*) mirror.prevData.c_str(), mirror.prevData.size());
}

void ecs::ServerManager::initPlayers(ConnId conn, World &world)
{
    SceneManager &sceneMan = world.getRessource<ecs::SceneManager>();
    ServerNetworkSceneModule &scene = dynamic_cast<ServerNetworkSceneModule&>(sceneMan.getScene());
    PlayersManager &man = world.getRessource<PlayersManager>();
    std::uint32_t nbPlayers;
    PlayerId id;

    std::cout << "[SERVER] Creating players" << std::endl;
    if (tryRead(conn, &nbPlayers, sizeof(std::uint32_t)))
        return;
    if (!man.canAcceptPlayers(nbPlayers)) {
        std::cout << "[SERVER] New players not accepted" << std::endl;
        sendCmd(conn, NetworkCommand::PLAYERS_REJECTED);
        return;
    }
    std::cout << "[SERVER] New players accepted" << std::endl;
    sendCmd(conn, NetworkCommand::PLAYERS_CREATED);
    for (int i = 0; i < nbPlayers; i++) {
        id = man.reservePlayerId(conn);
        scene.onPlayerIdAttributed(id, world);
        _server->write(conn, &id, sizeof(PlayerId));
    }
}

void ecs::ServerManager::moveCameras(Vector3 pos, Vector3 target)
{
    for (ConnId conn : _activeConns)
        moveCamera(conn, pos, target);
}

void ecs::ServerManager::moveCamera(ConnId conn, Vector3 pos, Vector3 target)
{
    sendCmd(conn, NetworkCommand::MOVE_CAMERA);
    _server->write(conn, &pos, sizeof(Vector3));
    _server->write(conn, &target, sizeof(Vector3));
}

void ecs::ServerManager::deleteClientEntity(Entity entity, World &world)
{
    MirroredEntity &mirrored = world.getComponent<MirroredEntity>(entity);

    if (!_server->doesConnExists(mirrored.conn))
        return;
    std::cout << "Delete " << (int) mirrored.foreignEntity << " from " << mirrored.conn << std::endl;
    _clientToServer[mirrored.conn].erase(mirrored.foreignEntity);
}

void ecs::ServerUpdateSystem::setSignature(ComponentManager &component)
{
    _signature = component.generateSignature<MirrorEntity>();
}

void ecs::ServerUpdateSystem::update(World &world)
{
    ServerManager &man = world.getRessource<ServerManager>();
    std::vector<network::ConnId> newConns = man.acceptNewConns(world);

    man.handleNetworkCommands(world);
    for (Entity entity : _entities) {
        MirrorEntity &mirror = world.getComponent<MirrorEntity>(entity);

        if (newConns.size() && mirror.prevData != "")
            man.sendEntityToNewConns(newConns, entity, world);
        man.updateLocalEntity(entity, world);
    }
}
