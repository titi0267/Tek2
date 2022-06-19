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
    struct TextInputSettings {
        std::string input;
        bool toggle;
        bool gamepad;
        bool save;
        TextInputSettings() : input(""), toggle(false) {};
        TextInputSettings(bool gamepad, bool save) : input(""), toggle(false), gamepad(gamepad), save(save) {};
    };
    class TextInputSettingsSystem : public ecs::ASystem {
        public:
        TextInputSettingsSystem() { _stage = ecs::Stages::INPUT_UPDATE; };

        void setSignature(ecs::ComponentManager &component);
        void update(ecs::World &world);
    };
    struct TextInputPort {
        std::string input;
        bool toggle;
        TextInputPort() : input(""), toggle(false) {};
    };
    class TextInputPortSystem : public ecs::ASystem {
        public:
        TextInputPortSystem() { _stage = ecs::Stages::INPUT_UPDATE; };

        void setSignature(ecs::ComponentManager &component);
        void update(ecs::World &world);
    };
}