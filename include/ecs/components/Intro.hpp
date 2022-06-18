/*
** EPITECH PROJECT, 2022
** indieStudio
** File description:
** Intro
*/

#pragma once
#include "ecs/engine/System.hpp"

namespace ecs {
    struct Intro {
        Intro() {};
    };
    class IntroUpdateSystem : public ecs::ASystem {
        public:
        IntroUpdateSystem() { _stage = ecs::Stages::UPDATE; };

        void setSignature(ecs::ComponentManager &component);
        void update(ecs::World &world);
    };
};
