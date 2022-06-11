/*
** EPITECH PROJECT, 2022
** bomberman
** File description:
** ShowFPSButton
*/

#pragma once

#include "ecs/engine/World.hpp"

namespace ecs {
    struct ShowFPSButton {
        bool show;
        bool precedent;
        ShowFPSButton () : show(false), precedent(false) {};
    };

    class ShowFPSButtonSystem : public ecs::ASystem {
        public:
        ShowFPSButtonSystem() { _stage = ecs::Stages::INPUT_UPDATE;};

        void setSignature(ecs::ComponentManager &component);
        void update(ecs::World &world);
    };
}
