/*
** EPITECH PROJECT, 2022
** bomberman
** File description:
** SingleKeyRecorder
*/

#include "ecs/components/KeyRecorder.hpp"
#include "ecs/components/Text3D.hpp"
#include "ecs/components/HoverTint.hpp"
#include "ecs/components/ColorTexture.hpp"

#include "raylib/Window.hpp"

void ecs::KeyRecorderSystem::setSignature(ecs::ComponentManager &component)
{
    _signature = component.generateSignature<Text3D, SingleKeyRecorder, HoverTint>();
}

void ecs::KeyRecorderSystem::update(ecs::World &world)
{
    ecs::BindManager &bind = world.getRessource<ecs::BindManager>();
    raylib::Window &win = world.getRessource<raylib::Window>();

    for (auto entity : _entities) {
        Text3D &text = world.getComponent<Text3D>(entity);
        SingleKeyRecorder &key = world.getComponent<SingleKeyRecorder>(entity);
        HoverTint &hTint = world.getComponent<HoverTint>(entity);
        Tint &tint = world.getComponent<Tint>(entity);

        text.text = bind.getKeyText(key.gamepad, key.bind);
        if (!key.recording)
            continue;
        if (bind.getSetOff(key.gamepad)) {
            if (!key.first) {
                tint = WHITE;
                hTint.base = WHITE;
                hTint.onHover = GRAY;
                key.recording = false;
                continue;
            }
            tint = BLUE;
            hTint.base = BLUE;
            hTint.onHover = SKYBLUE;
            key.first = false;
        }
        if (!key.gamepad) {
            int ch = win.getKeyPressed();
            bool toggle = false;
            while (win.getKeyPressed() != 0);
            if (!ch)
                continue;
            try {
                bind.setKey(false, key.bind, ch);
                text.text = bind.getKeyText(key.gamepad, key.bind);
            }
            catch (std::invalid_argument) {
                continue;
            }
            tint = WHITE;
            hTint.base = WHITE;
            hTint.onHover = GRAY;
            key.recording = false;
        }
    }
    if (bind.getSetOff(true))
        bind.toggleSetOff(true);
    if (bind.getSetOff(false))
        bind.toggleSetOff(false);
}