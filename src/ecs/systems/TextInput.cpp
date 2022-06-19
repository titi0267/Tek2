/*
** EPITECH PROJECT, 2022
** bomberman
** File description:
** TextInput
*/

#include "ecs/components/TextInput.hpp"
#include "ecs/components/Text3D.hpp"
#include "ecs/components/Hoverable.hpp"
#include "ecs/components/HoverTint.hpp"
#include "ecs/components/ColorTexture.hpp"

#include "ecs/engine/LaunchManager.hpp"

#include "input/BindsManager.hpp"

#include "raylib/Window.hpp"
#include <iostream>

void ecs::TextInputSystem::setSignature(ecs::ComponentManager &component)
{
    _signature = component.generateSignature<Text3D, TextInput, Hoverable>();
}

void ecs::TextInputSystem::update(ecs::World &world)
{
    ecs::BindManager &bind = world.getRessource<ecs::BindManager>();
    raylib::Window &win = world.getRessource<raylib::Window>();
    ecs::LaunchManager &man = world.getRessource<ecs::LaunchManager>();

    for (auto entity : _entities) {
        Text3D &text = world.getComponent<Text3D>(entity);
        Hoverable &hover = world.getComponent<Hoverable>(entity);
        TextInput &input = world.getComponent<TextInput>(entity);
        if (hover.isHover) {
            int ch = win.getKeyPressed();
            while (win.getKeyPressed() != 0);
            if (!ch)
                continue;
            if (ch == KEY_BACKSPACE)
                if (input.input.size())
                    input.input.resize(input.input.size() - 1);
            if (input.input.size() <= 18 && (ch == '.' || ch == KEY_SPACE || (ch >= KEY_ZERO && ch <= KEY_NINE)))
                input.input.push_back((char)ch);
            text.setText(input.input);
            man.setIpPort(text.text);
        }
    }
}

void ecs::TextInputSettingsSystem::setSignature(ecs::ComponentManager &component)
{
    _signature = component.generateSignature<Text3D, TextInputSettings, Hoverable>();
}

void ecs::TextInputSettingsSystem::update(ecs::World &world)
{
    ecs::BindManager &bind = world.getRessource<ecs::BindManager>();
    raylib::Window &win = world.getRessource<raylib::Window>();

    for (auto entity : _entities) {
        Text3D &text = world.getComponent<Text3D>(entity);
        Hoverable &hover = world.getComponent<Hoverable>(entity);
        TextInputSettings &input = world.getComponent<TextInputSettings>(entity);
        if (hover.isHover) {
            int ch = win.getKeyPressed();
            while (win.getKeyPressed() != 0);
            if (!ch)
                continue;
            if (ch == KEY_BACKSPACE)
                if (input.input.size())
                    input.input.resize(input.input.size() - 1);
            if (input.input.size() <= 7 && (ch == 58 || (ch >= KEY_A && ch <= KEY_Z) || (ch >= KEY_ZERO && ch <= KEY_NINE)))
                input.input.push_back((char)ch);
            text.setText(input.input);
            if (input.save)
                bind.setName(input.gamepad, text.text);
            else
                bind.setLoadStr(input.gamepad, text.text);
        }
    }
}
