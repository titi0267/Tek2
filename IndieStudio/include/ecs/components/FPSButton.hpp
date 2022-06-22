/*
** EPITECH PROJECT, 2022
** bomberman
** File description:
** FPSButton
*/

#pragma once

#include "ecs/engine/World.hpp"

namespace ecs {
    struct FPSButton {
        int fps;
        bool precedent;
        FPSButton () : fps(0), precedent(false) {};
        FPSButton (int fps) : fps(fps), precedent(false) {};
    };

    class FPSButtonSystem : public ecs::ASystem {
        public:
        FPSButtonSystem() { _stage = ecs::Stages::INPUT_UPDATE;};

        void setSignature(ecs::ComponentManager &component);
        void update(ecs::World &world);
    };
}