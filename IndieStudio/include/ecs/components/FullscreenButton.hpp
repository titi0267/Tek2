/*
** EPITECH PROJECT, 2022
** bomberman
** File description:
** FullscreenButton
*/

#pragma once

#include "ecs/engine/World.hpp"

namespace ecs {
    struct FullscreenButton {
        bool fullscreen;
        bool timeout;
        bool change;
    };

    class FullscreenButtonSystem : public ecs::ASystem {
        public:
        FullscreenButtonSystem() { _stage = ecs::Stages::INPUT_UPDATE;};

        void setSignature(ecs::ComponentManager &component);
        void update(ecs::World &world);
    };
}