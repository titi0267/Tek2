/*
** EPITECH PROJECT, 2022
** ia
** File description:
** PlayMusic
*/

#pragma once

#include "ecs/engine/System.hpp"

namespace ecs {
    class PlayMusicSystem : public ecs::ASystem {
        public:
            PlayMusicSystem() { _stage = ecs::Stages::UPDATE; };
            void setSignature(ecs::ComponentManager &component);
            void update(ecs::World &world);
        protected:
        private:
    };
}