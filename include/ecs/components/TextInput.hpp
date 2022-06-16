/*
** EPITECH PROJECT, 2022
** bomberman
** File description:
** TextInput
*/

#pragma once

#include "ecs/engine/System.hpp"
#include <string>

namespace ecs {
    struct TextInput {
        std::string input;
        bool toggle;
        TextInput() : input(""), toggle(false) {};
    };
    class TextInputSystem : public ecs::ASystem {
        public:
        TextInputSystem() { _stage = ecs::Stages::INPUT_UPDATE; };

        void setSignature(ecs::ComponentManager &component);
        void update(ecs::World &world);
    };
}