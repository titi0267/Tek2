/*
** EPITECH PROJECT, 2022
** B-YEP-400-STG-4-1-indiestudio-mathieu.brujan
** File description:
** BackgroundRotation
*/

#pragma once

#include "ecs/engine/System.hpp"
#include "ecs/engine/World.hpp"

namespace ecs {
    struct BackgroundRotation {};

    class BackgroundRotationUpdateSystem : public ecs::ASystem {
        public:
        BackgroundRotationUpdateSystem() { _stage = ecs::RENDER_UPDATE; };

        void setSignature(ecs::ComponentManager &component);
        void update(ecs::World &world);
    };
}
