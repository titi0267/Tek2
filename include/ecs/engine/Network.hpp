/*
** EPITECH PROJECT, 2022
** B-YEP-400-STG-4-1-indiestudio-mathieu.brujan
** File description:
** Network
*/

#pragma once

#include <memory>
#include <sstream>
#include <iostream>
#include <chrono>
#include <map>
#include <unordered_map>
#include "network/IClient.hpp"
#include "network/IServer.hpp"
#include "network/CPSocket.hpp"
#include "ecs/engine/World.hpp"
#include "ecs/engine/PlayerId.hpp"
#include "raylib/Vectors.hpp"

namespace ecs {
    using ConnId = network::ConnId;

    const std::size_t NB_MIRROR_COMPONENTS = 13;
    extern const ComponentHash MIRROR_COMPONENTS[NB_MIRROR_COMPONENTS];

    enum class NetworkCommand : uint8_t {
        UPDATE_ENTITY,
        KILL_ENTITY,
        INIT_PLAYERS,
        PLAYERS_CREATED,
        PLAYERS_REJECTED,
        DISCONNECT_CLIENT,
        MOVE_CAMERA,
    };

    struct MirrorEntity {
        char prevData[1024 * 4];
        std::uint32_t size = 0;

        std::string_view getView() { return std::string_view(prevData, size); };
    };

    struct MirroredEntity {
        ConnId conn;
        Entity foreignEntity;

        MirroredEntity(ConnId conn = 0,  Entity foreign = (Entity) 0) : conn(conn), foreignEntity(foreign) {};
    };

    void createUpdateLocalEntityBuffer(Entity entity, World &world, std::stringbuf &buffer);
    void createKillLocalEntityBuffer(Entity entity, std::stringbuf &buffer);

    class ServerManager {
        std::unique_ptr<network::IServer> _server;
        std::vector<ConnId> _activeConns;
        std::unordered_map<network::ConnId, std::map<Entity, Entity>> _clientToServer;

        void sendCmd(ConnId conn, NetworkCommand cmd);

        bool tryRead(ConnId conn, void *buf, std::size_t size);
        void handleClientDisconnection(ConnId conn, World &world);
        bool readClientEntityUpdate(ConnId conn, std::stringbuf &buffer);

        void spawnOrUpdateClientEntity(ConnId conn, World &world);
        void spawnClientEntity(ConnId conn, Entity serverEntity, std::stringbuf &buffer, World &world);
        void updateClientEntity(ConnId conn, Entity serverEntity, std::stringbuf &buffer, World &world);
        void killClientEntity(ConnId conn, World &world);

        void initPlayers(ConnId conn, World &world);

        public:
        ServerManager() : _server(network::CPSocket::createServer()) {};
        ~ServerManager() = default;

        void startServer(const std::string &port) { _server->createServer("127.0.0.1", port); };
        void closeServer() { _server->closeServer(); };

        std::vector<network::ConnId> acceptNewConns(World &world);
        void handleNetworkCommands(World &world);

        void updateLocalEntity(Entity entity, World &world);
        void killLocalEntity(Entity entity, World &world);

        void sendEntityToNewConns(std::vector<network::ConnId> &newConns, Entity entity, World &world);

        void moveCameras(Vector3 pos, Vector3 target);
        void moveCamera(ConnId conn, Vector3 pos, Vector3 target);

        void deleteClientEntity(Entity entity, World &world);
    };

    using ConnectionSuccessFct = void (*)(ecs::World &world, void *obj);
    using ConnectionFailedFct = void (*)(ecs::World &world, void *obj);

    class ClientManager {
        std::unique_ptr<network::IClient> _client;
        std::unordered_map<Entity, Entity> _serverToClient;

        std::string _ip;
        std::string _port;
        bool _connAttempted = false;
        int _tryConnCount = 0;
        void *_data = nullptr;
        ConnectionSuccessFct _success;
        ConnectionFailedFct _failed;
        float _lastTryDelta = 0;

        bool tryRead(void *buf, std::size_t size);
        void handleDisconnect(World &world);
        bool readServerEntityUpdate(std::stringbuf &buffer);

        void spawnOrUpdateServerEntity(World &world);
        void spawnServerEntity(Entity serverEntity, std::stringbuf &buffer, World &world);
        void updateServerEntity(Entity serverEntity, std::stringbuf &buffer, World &world);
        void killServerEntity(World &world);

        void handlePlayersCreated(World &world);
        void handleMoveCamera(World &world);

        public:
        ClientManager() : _client(network::CPSocket::createClient()) {};
        ~ClientManager() = default;

        void attemptConnection(const std::string &ip, const std::string &port,
        void *obj, ConnectionSuccessFct success, ConnectionFailedFct failed);
        void tryConnection(ecs::World &world);
        bool isConnectionAttempt() { return _connAttempted; };
        void initPlayers(std::uint32_t nbPlayers);

        void handleNetworkCommands(World &world);

        void updateLocalEntity(Entity entity, World &world);
        void killLocalEntity(Entity entity, World &world);

        void connectTo(const std::string &ip = "127.0.0.1", const std::string &port = "4243") { _client->connectTo(ip, port); };
        void disconnect() { _client->disconnect(); };
        bool isConnected() { return _client->isConnected(); };
    };

    class ServerUpdateSystem : public ASystem {
        public:
        ServerUpdateSystem() { _stage = NETWORK_UPDATE; };

        void setSignature(ComponentManager &component);
        void update(World &world);
    };

    class ClientUpdateSystem : public ASystem {
        public:
        ClientUpdateSystem() { _stage = NETWORK_UPDATE; };

        void setSignature(ComponentManager &component);
        void update(World &world);
    };

    class ClientNetworkSceneModule {
        public:
        virtual int getNbPlayersOnClient() = 0;
        virtual void onDisconnect(World &world) = 0;
        virtual void playerIdAssigned(PlayerId id, World &world) = 0;
    };

    class ServerNetworkSceneModule {
        public:
        virtual void onConnect(ConnId conn, World &world) = 0;
        virtual void onDisconnect(ConnId conn, World &world) = 0;
        virtual void onPlayerIdAttributed(PlayerId id, World &world) = 0;
    };
}
