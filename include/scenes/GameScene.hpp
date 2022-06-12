/*
** EPITECH PROJECT, 2022
** B-YEP-400-STG-4-1-indiestudio-mathieu.brujan
** File description:
** GameScene
*/

#pragma once

#include "ecs/engine/SceneManager.hpp"

namespace bomberman {
    struct GameSceneArgs {
        std::string ip;
        std::string port;
        bool startLocalServer;
        int nbPlayers;
    };

    class GameScene : public ecs::IScene {
        std::string _ip;
        std::string _port;
        bool _startLocalServer;
        int _nbPlayers;

        void successConn(ecs::World &world);
        void failedConn(ecs::World &world);

        public:
        GameScene(const void *data) : _ip(((GameSceneArgs*) data)->ip), _port(((GameSceneArgs*) data)->port),
        _startLocalServer(((GameSceneArgs*) data)->startLocalServer), _nbPlayers(((GameSceneArgs*) data)->nbPlayers) {};

        void loadScene(ecs::World &world);
        void unloadScene(ecs::World &world);
    };
}
