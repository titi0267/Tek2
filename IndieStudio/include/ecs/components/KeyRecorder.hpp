/*
** EPITECH PROJECT, 2022
** bomberman
** File description:
** KeyRecorder
*/

#pragma once

#include "ecs/engine/System.hpp"
#include "input/BindsManager.hpp"

namespace ecs {
    struct SingleKeyRecorder {
        bool recording;
        bool first;
        bool gamepad;
        IBind::Binding bind;


        SingleKeyRecorder() : recording(false), first(false), gamepad(false), bind(IBind::UP) {};
        SingleKeyRecorder(bool gamepad, IBind::Binding bind) : recording(false), first(false), gamepad(gamepad), bind(bind) {};
    };
    class KeyRecorderSystem : public ecs::ASystem {
        public:
            KeyRecorderSystem() { _stage = ecs::Stages::INPUT_UPDATE; };

            void setSignature(ecs::ComponentManager &component);
            void update(ecs::World &world);
    };
}
