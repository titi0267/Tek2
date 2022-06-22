/*
** EPITECH PROJECT, 2022
** B-YEP-400-STG-4-1-indiestudio-mathieu.brujan
** File description:
** Timer
*/

#pragma once

#include "ecs/engine/World.hpp"

namespace ecs {
    struct Timer {
        float timeElapsed = 0;

        Timer() {};
    };

    class TimerUpdateSystem : public ASystem {

        public:
        TimerUpdateSystem() { _stage = ecs::Stages::TIME_UPDATE; };

        void setSignature(ecs::ComponentManager &component);
        void update(ecs::World &world);
    };
}