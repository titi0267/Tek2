/*
** EPITECH PROJECT, 2022
** B-YEP-400-STG-4-1-indiestudio-mathieu.brujan
** File description:
** InternalServer
*/

#pragma once

#include <thread>
#include <memory>
#include "ecs/engine/World.hpp"

namespace ecs {
    using InternalServerMainFct = void (*)(ecs::World *world, bool *run);

    class InternalServer {
        std::thread _thread;
        std::unique_ptr<ecs::World> _serverWorld = nullptr;
        bool _run = true;

        public:
        void startServer(InternalServerMainFct fct)
        {
            _run = true;
            _serverWorld = std::make_unique<ecs::World>();
            _thread = std::thread(fct, _serverWorld.get(), &_run);
        }

        void joinAndDestroy()
        {
            _run = false;
            _thread.join();
            _serverWorld.reset();
            _thread = std::thread();
        }
    };
}
