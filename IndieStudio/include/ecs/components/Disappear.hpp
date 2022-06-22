/*
** EPITECH PROJECT, 2022
** bomberman
** File description:
** Disappear
*/

#pragma once

#include "ecs/engine/World.hpp"

namespace ecs {
    struct Disappear {
        bool disap;
        Disappear() : disap(false) {};
    };
    class DisappearSystem : public ecs::ASystem {
        public:
        DisappearSystem() { _stage = ecs::Stages::INPUT_UPDATE;};

        void setSignature(ecs::ComponentManager &component);
        void update(ecs::World &world);
        protected:
        private:
    };
}
