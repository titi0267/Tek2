/*
** EPITECH PROJECT, 2022
** B-YEP-400-STG-4-1-indiestudio-mathieu.brujan
** File description:
** Network
*/

#pragma once

#include <memory>
#include <unordered_map>
#include <iostream>
#include "network/IClient.hpp"
#include "network/IServer.hpp"
#include "network/CPSocket.hpp"
#include "World.hpp"

namespace ecs {
    const std::size_t NB_MIRROR_COMPONENTS = 2;
    extern const ComponentHash MIRROR_COMPONENTS[NB_MIRROR_COMPONENTS];

    enum class NetworkCommand : uint8_t {
        UPDATE_ENTITY,
        KILL_ENTITY,
    };

    struct MirrorEntity {};

    class INetworkManager {
        public:
        virtual void handleNetworkCommands(World &world) = 0;

        virtual void updateLocalEntity(Entity entity, World &world) = 0;
        virtual void killLocalEntity(Entity entity, World &world) = 0;

        virtual bool isConnected() = 0;
    };

    class ServerManager : public INetworkManager {
        using ConnId = network::ConnId;

        std::unique_ptr<network::IServer> _server;
        std::vector<ConnId> _activeConns;
        std::unordered_map<network::ConnId, std::unordered_map<Entity, Entity>> _clientToServer;

        void spawnOrUpdateClientEntity(ConnId conn, World &world);
        void spawnClientEntity(ConnId conn, Entity serverEntity, World &world);
        void updateClientEntity(ConnId conn, Entity serverEntity, World &world);
        void killClientEntity(ConnId conn, World &world);

        void sendUpdateLocalEntity(ConnId conn, Entity localEntity, std::uint32_t total, World &world);
        void sendKillLocalEntity(ConnId conn, Entity localEntity);

        public:
        ServerManager() : _server(network::CPSocket::createServer()) {};
        ~ServerManager() = default;

        void handleNetworkCommands(World &world);

        void updateLocalEntity(Entity entity, World &world);
        void killLocalEntity(Entity entity, World &world);

        bool isConnected() { return true; };
    };

    class ClientManager : public INetworkManager {
        std::unique_ptr<network::IClient> _client;
        std::unordered_map<Entity, Entity> _serverToClient;

        void spawnOrUpdateServerEntity(World &world);
        void spawnServerEntity(Entity serverEntity,World &world);
        void updateServerEntity(Entity serverEntity,World &world);
        void killServerEntity(World &world);

        public:
        ClientManager() : _client(network::CPSocket::createClient()) {};
        ~ClientManager() = default;

        void handleNetworkCommands(World &world);

        void updateLocalEntity(Entity entity, World &world);
        void killLocalEntity(Entity entity, World &world);

        void connectTo(const std::string &ip = "127.0.0.1", const std::string &port = "4242") { _client->connectTo(ip, port); };
        void disconnect() { _client->disconnect(); };
        bool isConnected() { return _client->isConnected(); };
    };

    template<class NetworkManagerImpl>
    class NetworkUpdateSystem : public ASystem {
        public:
        NetworkUpdateSystem() { _stage = NETWORK_UPDATE; };

        void setSignature(ComponentManager &component)
        {
            _signature = component.generateSignature<MirrorEntity>();
        }

        void update(World &world)
        {
            INetworkManager &man = world.getRessource<NetworkManagerImpl>();

            if (!man.isConnected())
                return;
            man.handleNetworkCommands(world);
            for (Entity entity : _entities)
                man.updateLocalEntity(entity, world);
        }
    };
}
