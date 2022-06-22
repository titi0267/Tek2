/*
** EPITECH PROJECT, 2022
** bomberman
** File description:
** RotateOnHover
*/

#pragma once

#include "ecs/engine/System.hpp"

namespace ecs {
    struct HoverRotate {
        bool inRotation;

        HoverRotate() : inRotation(false) {};
    };
    class HoverRotateUpdateSystem : public ecs::ASystem {
        public:
            HoverRotateUpdateSystem() { _stage = ecs::Stages::RENDER_UPDATE; };

            void setSignature(ecs::ComponentManager &component);
            void update(ecs::World &world);
    };
}
