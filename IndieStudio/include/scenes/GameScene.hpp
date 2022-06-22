/*
** EPITECH PROJECT, 2022
** B-YEP-400-STG-4-1-indiestudio-mathieu.brujan
** File description:
** GameScene
*/

#pragma once

#include "ecs/engine/SceneManager.hpp"
#include "ecs/engine/Network.hpp"
#include "ecs/engine/PlayersManager.hpp"
#include "ecs/engine/System.hpp"
#include "ecs/engine/World.hpp"
#include "ecs/components/SceneMoveElement.hpp"
#include "input/InputFile.hpp"

namespace bomberman {
    void disconnectFunction(ecs::World &world, ecs::Entity entity);
    void successConn(ecs::World &world, void *obj);
    void failedConn(ecs::World &world, void *obj);

    struct GameSceneArgs {
        std::string ip;
        std::string port;
        bool startLocalServer;
        int nbPlayers;

        GameSceneArgs(const std::string &ip, const std::string &port, bool localServer, int nbPlayers) :
            ip(ip), port(port), startLocalServer(localServer), nbPlayers(nbPlayers) {};
    };

    class GameScene : public ecs::IScene, public ecs::ClientNetworkSceneModule, public ecs::MoveRequesterSceneModule {
        std::string _ip;
        std::string _port;
        bool _startLocalServer;
        int _nbPlayers;

        bool _moveRequest = false;
        Vector3 _move = {0, 0, 0};
        bool _buttonToggle = false;

        public:
        GameScene(const void *data) : _ip(((GameSceneArgs*) data)->ip), _port(((GameSceneArgs*) data)->port),
        _startLocalServer(((GameSceneArgs*) data)->startLocalServer), _nbPlayers(((GameSceneArgs*) data)->nbPlayers) {};

        void loadScene(ecs::World &world);
        void unloadScene(ecs::World &world);
        void entityKilled(ecs::Entity entity,ecs::World &world);

        int getNbPlayersOnClient() { return _nbPlayers; };
        void onDisconnect(ecs::World &world);
        void playerIdAssigned(ecs::PlayerId id, ecs::World &world, InputFile file);

        bool &getMovementRequest() { return _moveRequest; };
        Vector3 &getMoveDest() { return _move; };
        bool &getQuitButtonToggle() { return _buttonToggle; };
        bool getHost() { return _startLocalServer; };
    };

    class GameToggleQuitButtonSystem : public ecs::ASystem {
        public:
        GameToggleQuitButtonSystem() { _stage = ecs::INPUT_UPDATE; };

        void setSignature(ecs::ComponentManager &component);
        void update(ecs::World &world);
        void playerIdAssigned(ecs::PlayerId id, ecs::World &world, InputFile file);
    };
}
