/*
** EPITECH PROJECT, 2022
** bomberman
** File description:
** ResolutionButton
*/

#pragma once

#include "ecs/engine/World.hpp"

namespace ecs {
    struct ResolutionButton {
        int width;
        int height;
        bool precedent;
        ResolutionButton () : width(0), height(0) {};
        ResolutionButton (int width, int height) : width(width), height(height), precedent(false) {};
    };

    class ResolutionButtonSystem : public ecs::ASystem {
        public:
        ResolutionButtonSystem() { _stage = ecs::Stages::INPUT_UPDATE;};

        void setSignature(ecs::ComponentManager &component);
        void update(ecs::World &world);
    };
}