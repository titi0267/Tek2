/*
** EPITECH PROJECT, 2022
** epi-cs
** File description:
** HoverTint
*/

#pragma once

#include "ecs/engine/World.hpp"
#include "ecs/engine/System.hpp"

namespace ecs {
    struct HoverTint {
        Color base;
        Color onHover;

        HoverTint() : base(WHITE), onHover(WHITE) {};
        HoverTint(Color base, Color onHover) : base(base), onHover(onHover) {};
    };
    class HoverTintUpdateSystem : public ecs::ASystem {
        public:
        HoverTintUpdateSystem() { _stage = ecs::Stages::RENDER_UPDATE; };

        void setSignature(ecs::ComponentManager &component);
        void update(ecs::World &world);
    };
}
