/*
** EPITECH PROJECT, 2022
** epi-cs
** File description:
** Clickable
*/

#pragma once

#include "ecs/engine/Entity.hpp"
#include "ecs/engine/World.hpp"
#include "ecs/engine/System.hpp"

#include "ecs/components/Hitbox.hpp"

namespace ecs {
    using ClickCallbackFct = void (*)(ecs::World &world, ecs::Entity entity);

    struct Clickable {
        ClickCallbackFct callback;

        Clickable() : callback(nullptr) {};
        Clickable(ClickCallbackFct callback) : callback(callback) {};
    };

    class ClickUpdateSystem : public ecs::ASystem {
        public:
        ClickUpdateSystem() { _stage = ecs::Stages::INPUT_UPDATE; };

        void setSignature(ecs::ComponentManager &component);
        void update(ecs::World &world);
    };
}
