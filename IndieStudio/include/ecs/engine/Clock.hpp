/*
** EPITECH PROJECT, 2022
** B-YEP-400-STG-4-1-indiestudio-mathieu.brujan
** File description:
** Clock
*/

#pragma once

#include <chrono>

namespace ecs {

    class Clock {
        using Sysclock = std::chrono::system_clock;

        Sysclock::time_point _lastUpdate;
        Sysclock::duration _delta;

        public:
        Clock() : _lastUpdate(Sysclock::now()), _delta(std::chrono::milliseconds(0)) {};

        void update()
        {
            std::chrono::time_point now = Sysclock::now();
            _delta = now - _lastUpdate;
            _lastUpdate = now;
        }

        double getDeltaSec()
        {
            #ifdef __linux__
                return _delta.count() / 1000000000.0;
            #elif _WIN32
                return _delta.count() / 10000000.0;
            #endif
        }

        std::uint64_t getNanoSec()
        {
            #ifdef __linux__
                return _delta.count();
            #elif _WIN32
                return _delta.count() * 100;
            #endif
        }
    };
}
