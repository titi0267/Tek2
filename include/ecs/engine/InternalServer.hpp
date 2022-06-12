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
    using InternalServerMainFct = void (*)(ecs::World *world, bool *run, std::string *port);

    class InternalServer {
        std::thread _thread;
        std::unique_ptr<ecs::World> _serverWorld = nullptr;
        std::string _port;
        bool _run = false;

        public:
        void startServer(InternalServerMainFct fct, const std::string &port)
        {
            _port = port;
            _run = true;
            _serverWorld = std::make_unique<ecs::World>();
            _thread = std::thread(fct, _serverWorld.get(), &_run, &_port);
        }

        void joinAndDestroy()
        {
            if (!_run)
                return;
            _run = false;
            _thread.join();
            _serverWorld.reset();
            _thread = std::thread();
        }

        bool isRunning() { return _run; };
    };
}
