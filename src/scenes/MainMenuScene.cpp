/*
** EPITECH PROJECT, 2022
** indieStudio
** File description:
** Menu
*/

#include <iostream>
#include <fstream>
#include <sstream>

#include "scenes/MainMenuScene.hpp"

#include "ecs/engine/EntityCommands.hpp"

#include "raylib/Camera.hpp"
#include "raylib/Window.hpp"
#include "raylib/Sound.hpp"

#include "raylib/SoundManager.hpp"

#include "raylib/TextureManager.hpp"
#include "raylib/ModelManager.hpp"
#include "raylib/AnimationManager.hpp"
#include "raylib/FontManager.hpp"

#include "ecs/components/DrawableCube.hpp"
#include "ecs/components/DrawableModel.hpp"
#include "ecs/components/Hitbox.hpp"
#include "ecs/components/Clickable.hpp"
#include "ecs/components/Hoverable.hpp"
#include "ecs/components/HoverTint.hpp"
#include "ecs/components/HoverRotate.hpp"
#include "ecs/components/SceneMoveElement.hpp"
#include "ecs/components/Text3D.hpp"
#include "ecs/components/ColorTexture.hpp"

void setResFunction(ecs::World &world, ecs::Entity entity)
{
    ecs::ResolutionButton &res = world.getComponent<ecs::ResolutionButton>(entity);
    raylib::Window &win = world.getRessource<raylib::Window>();

    if (win.getWindowSize().x == res.width && win.getWindowSize().y == res.height)
        return;
    win.resize({(float)res.width,(float)res.height});
}

void showFPSFunction(ecs::World &world, ecs::Entity entity)
{
    ecs::ShowFPSButton &but = world.getComponent<ecs::ShowFPSButton>(entity);
    raylib::Window &win = world.getRessource<raylib::Window>();

    but.show = !but.show;
}

void setFPSFunction(ecs::World &world, ecs::Entity entity)
{
    ecs::FPSButton &but = world.getComponent<ecs::FPSButton>(entity);
    raylib::Window &win = world.getRessource<raylib::Window>();

    if (win.getFPS() == but.fps)
        return;
    win.setTargetFPS(but.fps);
}

void windowedFunction(ecs::World &world, ecs::Entity entity)
{
    world.getRessource<raylib::Window>().setWindowed();
}

void fullscreenFunction(ecs::World &world, ecs::Entity entity)
{
    world.getComponent<ecs::FullscreenButton>(entity).change = true;
    world.getComponent<ecs::FullscreenButton>(entity).timeout = true;
}

void quitFunction(ecs::World &world, ecs::Entity entity)
{
    world.getComponent<ecs::Tint>(entity) = RED;
    world.getRessource<raylib::Window>().toggleClose();
}

void downFunction(ecs::World &world, ecs::Entity entity)
{
    ecs::SceneManager &man = world.getRessource<ecs::SceneManager>();

    try {
        ecs::MoveRequesterSceneModule &scene = dynamic_cast<ecs::MoveRequesterSceneModule&>(man.getScene());

        scene.getMovementRequest() = true;
        scene.getMoveDest() = {0, 10, 0};
        world.getComponent<ecs::Tint>(entity) = RED;
    } catch (std::bad_cast) {};
}

void upFunction(ecs::World &world, ecs::Entity entity)
{
    ecs::SceneManager &man = world.getRessource<ecs::SceneManager>();

    try {
        ecs::MoveRequesterSceneModule &scene = dynamic_cast<ecs::MoveRequesterSceneModule&>(man.getScene());

        scene.getMovementRequest() = true;
        scene.getMoveDest() = {0, -10, 0};
        world.getComponent<ecs::Tint>(entity) = RED;
    } catch (std::bad_cast) {};
}

void rightFunction(ecs::World &world, ecs::Entity entity)
{
    ecs::SceneManager &man = world.getRessource<ecs::SceneManager>();

    try {
        ecs::MoveRequesterSceneModule &scene = dynamic_cast<ecs::MoveRequesterSceneModule&>(man.getScene());

        scene.getMovementRequest() = true;
        scene.getMoveDest() = {10, 0, 0};
        world.getComponent<ecs::Tint>(entity) = RED;
    } catch (std::bad_cast) {};
}

void leftFunction(ecs::World &world, ecs::Entity entity)
{
    ecs::SceneManager &man = world.getRessource<ecs::SceneManager>();

    try {
        ecs::MoveRequesterSceneModule &scene = dynamic_cast<ecs::MoveRequesterSceneModule&>(man.getScene());

        scene.getMovementRequest() = true;
        scene.getMoveDest() = {-10, 0, 0};
        world.getComponent<ecs::Tint>(entity) = RED;
    } catch (std::bad_cast) {};
}

void bomberman::MainMenuScene::loadScene(ecs::World &world)
{
    generateMainMenu(world);
    generateSettingsMenu(world);
}

void bomberman::MainMenuScene::unloadScene(ecs::World &world)
{
    world.killAllEntities();
}

void bomberman::MainMenuScene::generateMainMenu(ecs::World &world)
{
    Quaternion rot = QuaternionIdentity();

    spawnButton({{0, 2.75, -2}, rot, {1, 1, 1}}, "Start", {WHITE, GREEN}, quitFunction, world);
    spawnButton({{0, 1.75, -2}, rot, {1, 1, 1}}, "Tutorial", {WHITE, GRAY}, quitFunction, world);
    spawnButton({{0, 0.75, -2}, rot, {1, 1, 1}}, "Settings", {WHITE, GRAY}, rightFunction, world);
    spawnButton({{0, -0.75, -2}, rot, {1, 1, 1}}, "Quit", {WHITE, RED}, quitFunction, world);
}

void bomberman::MainMenuScene::generateAudioSettingsMenu(ecs::World &world)
{

}

void bomberman::MainMenuScene::generateGraphicalSettingsMenu(ecs::World &world)
{
    Quaternion rot = QuaternionIdentity();
    auto &man = world.getRessource<raylib::SoundManager>();
    auto &music = man.getSound("main_menu_music");

    music.playSound();
    spawnFullscreenButton({{-12.50, 12.75, -2}, rot, {1, 1, 1}}, "Fullscreen", {WHITE, GRAY}, fullscreenFunction, world, {true, false, false});
    spawnFullscreenButton({{-7.50, 12.75, -2}, rot, {1, 1, 1}}, "Windowed", {GREEN, GRAY}, windowedFunction, world, {false, false, false});
    spawnResolutionButton({{-14, 11.75, -2}, rot, {1, 1, 1}}, "1600x900", {WHITE, GRAY}, setResFunction, world, {1600, 900});
    spawnResolutionButton({{-10, 11.75, -2}, rot, {1, 1, 1}}, "1280x720", {WHITE, GRAY}, setResFunction, world, {1280, 720});
    spawnResolutionButton({{-6, 11.75, -2}, rot, {1, 1, 1}}, "854x480", {WHITE, GRAY}, setResFunction, world, {854, 480});
    spawnFPSButton({{-14, 10.75, -2}, rot, {1, 1, 1}}, "30FPS", {WHITE, GRAY}, setFPSFunction, world, {30});
    spawnFPSButton({{-10, 10.75, -2}, rot, {1, 1, 1}}, "60FPS", {WHITE, GRAY}, setFPSFunction, world, {60});
    spawnFPSButton({{-6, 10.75, -2}, rot, {1, 1, 1}}, "Screen rate", {WHITE, GRAY}, setFPSFunction, world, {GetMonitorRefreshRate(GetCurrentMonitor())});
    spawnShowFPSButton({{-10, 9.75, -2}, rot, {1, 1, 1}}, "Show FPS", {RED, RED}, showFPSFunction, world);
    spawnButton({{-10, 8.75, -2}, rot, {1, 1, 1}}, "Back", {WHITE, GRAY}, downFunction, world);
}

void bomberman::MainMenuScene::generateSettingsMenu(ecs::World &world)
{
    Quaternion rot = QuaternionIdentity();

    generateGraphicalSettingsMenu(world);
    spawnButton({{-10, 2.75, -2}, rot, {1, 1, 1}}, "Graphical", {WHITE, GRAY}, upFunction, world);
    spawnButton({{-10, 1.75, -2}, rot, {1, 1, 1}}, "Audio", {WHITE, GRAY}, rightFunction, world);
    spawnButton({{-10, 0.75, -2}, rot, {1, 1, 1}}, "Keybinds", {WHITE, GRAY}, downFunction, world);
    spawnButton({{-10, -0.75, -2}, rot, {1, 1, 1}}, "Main Menu", {WHITE, GRAY}, leftFunction, world);
    spawnButton({{-20, 2.75, -2}, rot, {1, 1, 1}}, "Back", {WHITE, GRAY}, leftFunction, world);
    spawnButton({{-10, -7.25, -2}, rot, {1, 1, 1}}, "Back", {WHITE, GRAY}, upFunction, world);
}

void bomberman::MainMenuScene::spawnButton(const Transform &transform, const std::string &text,
const ecs::HoverTint &hoverTint, ClickCallbackFct doOnClick, ecs::World &world)
{
    const float BUTTON_SIZE = 3;

    world.spawn().insert(transform,
    ecs::Text3D {text, BLACK, {0, 0, 0.06}, 12}, ecs::FontRef {"emulogic"},
    ecs::ModelRef {"button"}, hoverTint.base,
    ecs::Hitbox{{-BUTTON_SIZE / 2, -0.4, -0.05}, {BUTTON_SIZE / 2, 0.4, 0.05}},
    ecs::Hoverable {}, hoverTint, ecs::HoverRotate {}, ecs::Clickable {doOnClick},
    ecs::SceneMoveElement {0.7});
}

void bomberman::MainMenuScene::spawnFullscreenButton(const Transform &transform, const std::string &text,
const ecs::HoverTint &hoverTint, ClickCallbackFct doOnClick, ecs::World &world, const ecs::FullscreenButton &but)
{
    const float BUTTON_SIZE = 3;

    world.spawn().insert(transform,
    ecs::Text3D {text, BLACK, {0, 0, 0.06}, 12}, ecs::FontRef {"emulogic"},
    ecs::ModelRef {"button"}, hoverTint.base,
    ecs::Hitbox{{-BUTTON_SIZE / 2, -0.4, -0.05}, {BUTTON_SIZE / 2, 0.4, 0.05}},
    ecs::Hoverable {}, hoverTint, ecs::HoverRotate {}, ecs::Clickable {doOnClick},
    ecs::SceneMoveElement {0.7}, but);
}

void bomberman::MainMenuScene::spawnResolutionButton(const Transform &transform, const std::string &text,
const ecs::HoverTint &hoverTint, ClickCallbackFct doOnClick, ecs::World &world, const ecs::ResolutionButton &res)
{
    const float BUTTON_SIZE = 3;

    world.spawn().insert(transform,
    ecs::Text3D {text, BLACK, {0, 0, 0.06}, 12}, ecs::FontRef {"emulogic"},
    ecs::ModelRef {"button"}, hoverTint.base,
    ecs::Hitbox{{-BUTTON_SIZE / 2, -0.4, -0.05}, {BUTTON_SIZE / 2, 0.4, 0.05}},
    ecs::Hoverable {}, hoverTint, ecs::HoverRotate {}, ecs::Clickable {doOnClick},
    ecs::SceneMoveElement {0.7}, res);
}

void bomberman::MainMenuScene::spawnFPSButton(const Transform &transform, const std::string &text,
const ecs::HoverTint &hoverTint, ClickCallbackFct doOnClick, ecs::World &world, const ecs::FPSButton &but)
{
    const float BUTTON_SIZE = 3;

    world.spawn().insert(transform,
    ecs::Text3D {text, BLACK, {0, 0, 0.06}, 12}, ecs::FontRef {"emulogic"},
    ecs::ModelRef {"button"}, hoverTint.base,
    ecs::Hitbox{{-BUTTON_SIZE / 2, -0.4, -0.05}, {BUTTON_SIZE / 2, 0.4, 0.05}},
    ecs::Hoverable {}, hoverTint, ecs::HoverRotate {}, ecs::Clickable {doOnClick},
    ecs::SceneMoveElement {0.7}, but);
}

void bomberman::MainMenuScene::spawnShowFPSButton(const Transform &transform, const std::string &text,
const ecs::HoverTint &hoverTint, ClickCallbackFct doOnClick, ecs::World &world)
{
    const float BUTTON_SIZE = 3;

    world.spawn().insert(transform,
    ecs::Text3D {text, BLACK, {0, 0, 0.06}, 12}, ecs::FontRef {"emulogic"},
    ecs::ModelRef {"button"}, hoverTint.base,
    ecs::Hitbox{{-BUTTON_SIZE / 2, -0.4, -0.05}, {BUTTON_SIZE / 2, 0.4, 0.05}},
    ecs::Hoverable {}, hoverTint, ecs::HoverRotate {}, ecs::Clickable {doOnClick},
    ecs::SceneMoveElement {0.7}, ecs::ShowFPSButton {});
}
