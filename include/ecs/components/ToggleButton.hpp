/*
** EPITECH PROJECT, 2022
** bomberman
** File description:
** ShowFPSButton
*/

#pragma once

#include "ecs/engine/World.hpp"

namespace ecs {
    struct ToggleButton {
        enum Usage {
            SHOW_FPS,
            MUSIC,
            SOUND
        };
        bool show;
        bool precedent;
        Usage usage;

        ToggleButton () : show(false), precedent(false), usage(SHOW_FPS) {};
        ToggleButton (Usage usage) : show(false), precedent(false), usage(usage) {};
    };

    class ShowFPSButtonSystem : public ecs::ASystem {
        public:
        ShowFPSButtonSystem() { _stage = ecs::Stages::INPUT_UPDATE;};

        void setSignature(ecs::ComponentManager &component);
        void update(ecs::World &world);
    };

    class ToggleMusicButtonSystem : public ecs::ASystem {
        public:
        ToggleMusicButtonSystem() { _stage = ecs::Stages::INPUT_UPDATE;};

        void setSignature(ecs::ComponentManager &component);
        void update(ecs::World &world);
    };

    class ToggleSoundButtonSystem : public ecs::ASystem {
        public:
        ToggleSoundButtonSystem() { _stage = ecs::Stages::INPUT_UPDATE;};

        void setSignature(ecs::ComponentManager &component);
        void update(ecs::World &world);
    };
}
