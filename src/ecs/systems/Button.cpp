/*
** EPITECH PROJECT, 2022
** bomberman
** File description:
** Selection
*/

#include "raylib/Window.hpp"
#include "ecs/components/ColorTexture.hpp"
#include "ecs/components/HoverTint.hpp"
#include "ecs/components/ResolutionButton.hpp"
#include "ecs/components/FullscreenButton.hpp"
#include "ecs/components/FPSButton.hpp"
#include "ecs/components/ShowFPSButton.hpp"
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
    _signature = component.generateSignature<ecs::ShowFPSButton, ecs::HoverTint>();
}

void ecs::ShowFPSButtonSystem::update(ecs::World &world)
{
    for (ecs::Entity entity: _entities) {
        ecs::ShowFPSButton &but = world.getComponent<ShowFPSButton>(entity);
        ecs::HoverTint &hTint = world.getComponent<HoverTint>(entity);
        ecs::Tint &tint = world.getComponent<Tint>(entity);
        raylib::Window &win = world.getRessource<raylib::Window>();
        if (but.show) {
            if (!but.precedent)
                tint = BLUE;
            hTint.base = BLUE;
            hTint.onHover = GREEN;
            win.drawFPS(0, 0);
            but.precedent = true;
        }
        else {
            if (but.precedent)
                tint = RED;
            hTint.base = RED;
            hTint.onHover = GREEN;
            but.precedent = false;
        }
    }
}