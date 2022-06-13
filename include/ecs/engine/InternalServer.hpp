/*
** EPITECH PROJECT, 2022
** B-YEP-400-STG-4-1-indiestudio-mathieu.brujan
** File description:
** InternalServer
*/

#pragma once

#include <thread>
#include <memory>
#include <string>
#include "ecs/engine/World.hpp"

namespace ecs {
    class InternalServer {
        std::thread _thread;
        std::unique_ptr<ecs::World> _serverWorld = nullptr;
        std::string _port;
        bool _run = false;

        void serverMain();

        public:
        void startServer(const std::string &port);
        void joinAndDestroy();

        bool isRunning() { return _run; };
    };
}
