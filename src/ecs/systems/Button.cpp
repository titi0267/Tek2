/*
** EPITECH PROJECT, 2022
** bomberman
** File description:
** Selection
*/

#include "raylib/Window.hpp"
#include "raylib/SoundManager.hpp"
#include "ecs/components/ColorTexture.hpp"
#include "ecs/components/HoverTint.hpp"
#include "ecs/components/ResolutionButton.hpp"
#include "ecs/components/FullscreenButton.hpp"
#include "ecs/components/FPSButton.hpp"
#include "ecs/components/ToggleButton.hpp"
#include "ecs/components/Text3D.hpp"
#include <iostream>

void ecs::ResolutionButtonSystem::setSignature(ecs::ComponentManager &component)
{
    _signature = component.generateSignature<ecs::ResolutionButton, ecs::HoverTint>();
}

void ecs::ResolutionButtonSystem::update(ecs::World &world)
{
    for (ecs::Entity entity: _entities) {
        ecs::ResolutionButton &res = world.getComponent<ResolutionButton>(entity);
        ecs::HoverTint &hTint = world.getComponent<HoverTint>(entity);
        ecs::Tint &tint = world.getComponent<Tint>(entity);
        raylib::Window &win = world.getRessource<raylib::Window>();


        if (win.isFullscreen()) {
            res.precedent = true;
            tint = RED;
            hTint.base = RED;
            hTint.onHover = RED;
            continue;
        }
        if (win.getWindowSize().x == res.width && win.getWindowSize().y == res.height) {
            res.precedent = true;
            hTint.base = BLUE;
            hTint.onHover = BLUE;
        }
        else {
            if (res.precedent == true) {
                tint = WHITE;
            }
            res.precedent = false;
            hTint.base = WHITE;
            hTint.onHover = GRAY;
        }
    }
}

void ecs::FullscreenButtonSystem::setSignature(ecs::ComponentManager &component)
{
    _signature = component.generateSignature<ecs::FullscreenButton, ecs::HoverTint>();
}

void ecs::FullscreenButtonSystem::update(ecs::World &world)
{
    for (ecs::Entity entity: _entities) {
        ecs::FullscreenButton &but = world.getComponent<FullscreenButton>(entity);
        ecs::HoverTint &hTint = world.getComponent<HoverTint>(entity);
        ecs::Tint &tint = world.getComponent<Tint>(entity);
        raylib::Window &win = world.getRessource<raylib::Window>();

        if (!but.timeout && but.change) {
            but.change = false;
            win.setFullscreen();
        }
        if (but.timeout) {
            but.timeout = false;
            int display = GetCurrentMonitor();
            win.resize({(float)GetMonitorWidth(display), (float)GetMonitorHeight(display)});
        }
        if (but.fullscreen) {
            if (win.isFullscreen()) {
                tint = BLUE;
                hTint.base = BLUE;
                hTint.onHover = BLUE;
                continue;
            }
            tint = WHITE;
            hTint.base = WHITE;
            hTint.onHover = GRAY;
        }
        else {
            if (win.isFullscreen()) {
                tint = WHITE;
                hTint.base = WHITE;
                hTint.onHover = GRAY;
                continue;
            }
            tint = BLUE;
            hTint.base = BLUE;
            hTint.onHover = BLUE;
        }
    }
}

void ecs::FPSButtonSystem::setSignature(ecs::ComponentManager &component)
{
    _signature = component.generateSignature<ecs::FPSButton, ecs::HoverTint>();
}

void ecs::FPSButtonSystem::update(ecs::World &world)
{
    for (ecs::Entity entity: _entities) {
        ecs::FPSButton &but = world.getComponent<FPSButton>(entity);
        ecs::HoverTint &hTint = world.getComponent<HoverTint>(entity);
        ecs::Tint &tint = world.getComponent<Tint>(entity);
        raylib::Window &win = world.getRessource<raylib::Window>();

        if (win.getFPS() == but.fps) {
            but.precedent = true;
            tint = BLUE;
            hTint.base = BLUE;
            hTint.onHover = BLUE;
        }
        else {
            if (but.precedent == true) {
                tint = WHITE;
            }
            but.precedent = false;
            hTint.base = WHITE;
            hTint.onHover = GRAY;
        }
    }
}

void ecs::ShowFPSButtonSystem::setSignature(ecs::ComponentManager &component)
{
    _signature = component.generateSignature<ecs::ToggleButton, ecs::HoverTint>();
}

void ecs::ShowFPSButtonSystem::update(ecs::World &world)
{
    for (ecs::Entity entity: _entities) {
        ecs::ToggleButton &but = world.getComponent<ToggleButton>(entity);
        if (but.usage != ecs::ToggleButton::SHOW_FPS)
            continue;
        ecs::HoverTint &hTint = world.getComponent<HoverTint>(entity);
        ecs::Tint &tint = world.getComponent<Tint>(entity);
        raylib::Window &win = world.getRessource<raylib::Window>();
        if (but.show) {
            if (!but.precedent)
                tint = BLUE;
            hTint.base = BLUE;
            hTint.onHover = GREEN;
            win.setShowFPS(true);
            but.precedent = true;
        }
        else {
            if (but.precedent)
                tint = RED;
            hTint.base = RED;
            hTint.onHover = GREEN;
            win.setShowFPS(false);
            but.precedent = false;
        }
    }
}

void ecs::ToggleMusicButtonSystem::setSignature(ecs::ComponentManager &component)
{
    _signature = component.generateSignature<ecs::ToggleButton, ecs::HoverTint>();
}

void ecs::ToggleMusicButtonSystem::update(ecs::World &world)
{
    for (ecs::Entity entity: _entities) {
        ecs::ToggleButton &but = world.getComponent<ToggleButton>(entity);
        if (but.usage != ecs::ToggleButton::MUSIC)
            continue;
        ecs::Text3D &text = world.getComponent<Text3D>(entity);
        ecs::HoverTint &hTint = world.getComponent<HoverTint>(entity);
        ecs::Tint &tint = world.getComponent<Tint>(entity);
        raylib::SoundManager &man = world.getRessource<raylib::SoundManager>();
        if (but.show) {
            if (!but.precedent) {
                tint = RED;
                text.setText("Music is off!");
                man.toggleMusic();
                man.setMusicVolume();
            }
            hTint.base = RED;
            hTint.onHover = GREEN;
            but.precedent = true;
        }
        else {
            if (but.precedent) {
                tint = BLUE;
                text.setText("Music is on!");
                man.toggleMusic();
                man.setMusicVolume();
            }
            hTint.base = BLUE;
            hTint.onHover = GREEN;
            but.precedent = false;
        }
    }
}

void ecs::ToggleSoundButtonSystem::setSignature(ecs::ComponentManager &component)
{
    _signature = component.generateSignature<ecs::ToggleButton, ecs::HoverTint, ecs::Text3D>();
}

void ecs::ToggleSoundButtonSystem::update(ecs::World &world)
{
    for (ecs::Entity entity: _entities) {
        ecs::ToggleButton &but = world.getComponent<ToggleButton>(entity);
        if (but.usage != ecs::ToggleButton::SOUND)
            continue;
        ecs::Text3D &text = world.getComponent<Text3D>(entity);
        ecs::HoverTint &hTint = world.getComponent<HoverTint>(entity);
        ecs::Tint &tint = world.getComponent<Tint>(entity);
        raylib::SoundManager &man = world.getRessource<raylib::SoundManager>();
        if (but.show) {
            if (!but.precedent) {
                text.setText("Sound is off!");
                tint = RED;
                man.toggleSound();
                man.setSoundVolume();
            }
            hTint.base = RED;
            hTint.onHover = GREEN;
            but.precedent = true;
        }
        else {
            if (but.precedent) {
                tint = BLUE;
                text.setText("Sound is on!");
                man.toggleSound();
                man.setSoundVolume();
            }
            hTint.base = BLUE;
            hTint.onHover = GREEN;
            but.precedent = false;
        }
    }
}