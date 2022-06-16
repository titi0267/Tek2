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

void toggleKeyRecordFunction(ecs::World &world, ecs::Entity entity)
{
    ecs::SingleKeyRecorder &key = world.getComponent<ecs::SingleKeyRecorder>(entity);
    ecs::BindManager &bind = world.getRessource<ecs::BindManager>();

    key.recording = true;
    key.first = true;
    bind.toggleSetOff(key.gamepad);
}

void setResFunction(ecs::World &world, ecs::Entity entity)
{
    ecs::ResolutionButton &res = world.getComponent<ecs::ResolutionButton>(entity);
    raylib::Window &win = world.getRessource<raylib::Window>();

    if (win.getWindowSize().x == res.width && win.getWindowSize().y == res.height)
        return;
    win.resize({(float)res.width,(float)res.height});
}

void toggleFunction(ecs::World &world, ecs::Entity entity)
{
    ecs::ToggleButton &but = world.getComponent<ecs::ToggleButton>(entity);
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
    auto &man = world.getRessource<raylib::SoundManager>();
    auto &music = man.getSound("main_menu_music");

    music.playSound();
    spawnButton({{0, 2.75, -2}, rot, {1, 1, 1}}, "Start", {WHITE, GREEN}, quitFunction, world);
    spawnButton({{0, 1.75, -2}, rot, {1, 1, 1}}, "Tutorial", {WHITE, GRAY}, quitFunction, world);
    spawnButton({{0, 0.75, -2}, rot, {1, 1, 1}}, "Settings", {WHITE, GRAY}, rightFunction, world);
    spawnButton({{0, -0.75, -2}, rot, {1, 1, 1}}, "Quit", {WHITE, RED}, quitFunction, world);
}

void bomberman::MainMenuScene::generateAudioSettingsMenu(ecs::World &world)
{
    Quaternion rot = QuaternionIdentity();
    float y = 2.75;

    spawnTitleButton({{-20, y, -2}, rot, {1, 1, 1}}, "Settings Menu", world);
    spawnToggleButton({{-20, y - 1, -2}, rot, {1, 1, 1}}, "Music is on!", {BLUE, BLUE}, toggleFunction, world, ecs::ToggleButton::MUSIC);
    spawnToggleButton({{-20, y - 2, -2}, rot, {1, 1, 1}}, "Sound is on!", {BLUE, BLUE}, toggleFunction, world, ecs::ToggleButton::SOUND);
    // CHANGE WITH NUANCER
    spawnToggleButton({{-20, y - 3, -2}, rot, {1, 1, 1}}, ("Music: 100" ), {BLUE, BLUE}, toggleFunction, world, ecs::ToggleButton::SOUND);
    spawnToggleButton({{-20, y - 4, -2}, rot, {1, 1, 1}}, ("Sound: 100"), {BLUE, BLUE}, toggleFunction, world, ecs::ToggleButton::SOUND);
    // CHANGE WITH NUANCER
    spawnButton({{-20, y - 5, -2}, rot, {1, 1, 1}}, "Back", {WHITE, GRAY}, leftFunction, world);
}

void bomberman::MainMenuScene::generateGamepadPart(ecs::World &world)
{
    Quaternion rot = QuaternionIdentity();
    ecs::SingleKeyRecorder a = {true, IBind::UP};
    ecs::SingleKeyRecorder b = {true, IBind::LEFT};
    ecs::SingleKeyRecorder c = {true, IBind::RIGHT};
    ecs::SingleKeyRecorder d = {true, IBind::DOWN};
    ecs::SingleKeyRecorder e = {true, IBind::PLACE};

    spawnStaticButton({{-19.5, -7.25, -2}, rot, {1, 1, 1}}, "Up", world);
    spawnStaticButton({{-19.5, -8.25, -2}, rot, {1, 1, 1}}, "Left", world);
    spawnStaticButton({{-19.5, -9.25, -2}, rot, {1, 1, 1}}, "Right", world);
    spawnStaticButton({{-19.5, -10.25, -2}, rot, {1, 1, 1}}, "Down", world);
    spawnStaticButton({{-19.5, -11.25, -2}, rot, {1, 1, 1}}, "Place a bomb", world);
    spawnSquareButton({{-17, -7.25, -2}, rot, {1, 1, 1}}, " ", {WHITE, GRAY}, toggleKeyRecordFunction, world, a);
    spawnSquareButton({{-17, -8.25, -2}, rot, {1, 1, 1}}, " ", {WHITE, GRAY}, toggleKeyRecordFunction, world, b);
    spawnSquareButton({{-17, -9.25, -2}, rot, {1, 1, 1}}, " ", {WHITE, GRAY}, toggleKeyRecordFunction, world, c);
    spawnSquareButton({{-17, -10.25, -2}, rot, {1, 1, 1}}, " ", {WHITE, GRAY}, toggleKeyRecordFunction, world, d);
    spawnSquareButton({{-17, -11.25, -2}, rot, {1, 1, 1}}, " ", {WHITE, GRAY}, toggleKeyRecordFunction, world, e);
    spawnStaticButton({{-23.5, -7.75, -2}, rot, {1, 1, 1}}, "Load from:", world);
    spawnStaticButton({{-24, -8.75, -2}, rot, {1, 1, 1}}, "", world);
    spawnSquareButton({{-22, -8.75, -2}, rot, {1, 1, 1}}, "OK", {WHITE, GRAY}, upFunction, world);
    spawnStaticButton({{-23.5, -9.75, -2}, rot, {1, 1, 1}}, "Save to:", world);
    spawnStaticButton({{-24, -10.75, -2}, rot, {1, 1, 1}}, "", world);
    spawnSquareButton({{-22, -10.75, -2}, rot, {1, 1, 1}}, "OK", {WHITE, GRAY}, upFunction, world);
    spawnButton({{-20, -12.25, -2}, rot, {1, 1, 1}}, "Back", {WHITE, GRAY}, leftFunction, world);
}

void bomberman::MainMenuScene::generateKeyboardPart(ecs::World &world)
{
    Quaternion rot = QuaternionIdentity();
    int i = 0;
    ecs::SingleKeyRecorder a = {false, IBind::UP};
    ecs::SingleKeyRecorder b = {false, IBind::LEFT};
    ecs::SingleKeyRecorder c = {false, IBind::RIGHT};
    ecs::SingleKeyRecorder d = {false, IBind::DOWN};
    ecs::SingleKeyRecorder e = {false, IBind::PLACE};

    spawnStaticButton({{-0.5, -7.25, -2}, rot, {1, 1, 1}}, "Up", world);
    spawnStaticButton({{-0.5, -8.25, -2}, rot, {1, 1, 1}}, "Left", world);
    spawnStaticButton({{-0.5, -9.25, -2}, rot, {1, 1, 1}}, "Right", world);
    spawnStaticButton({{-0.5, -10.25, -2}, rot, {1, 1, 1}}, "Down", world);
    spawnStaticButton({{-0.5, -11.25, -2}, rot, {1, 1, 1}}, "Place a bomb", world);
    spawnSquareButton({{-3, -7.25, -2}, rot, {1, 1, 1}}, " ", {WHITE, GRAY}, toggleKeyRecordFunction, world, a);
    spawnSquareButton({{-3, -8.25, -2}, rot, {1, 1, 1}}, " ", {WHITE, GRAY}, toggleKeyRecordFunction, world, b);
    spawnSquareButton({{-3, -9.25, -2}, rot, {1, 1, 1}}, " ", {WHITE, GRAY}, toggleKeyRecordFunction, world, c);
    spawnSquareButton({{-3, -10.25, -2}, rot, {1, 1, 1}}, " ", {WHITE, GRAY}, toggleKeyRecordFunction, world, d);
    spawnSquareButton({{-3, -11.25, -2}, rot, {1, 1, 1}}, " ", {WHITE, GRAY}, toggleKeyRecordFunction, world, e);
    spawnStaticButton({{3.5, -7.75, -2}, rot, {1, 1, 1}}, "Load from:", world);
    spawnStaticButton({{4, -8.75, -2}, rot, {1, 1, 1}}, "", world);
    spawnSquareButton({{2, -8.75, -2}, rot, {1, 1, 1}}, "OK", {WHITE, GRAY}, upFunction, world);
    spawnStaticButton({{3.5, -9.75, -2}, rot, {1, 1, 1}}, "Save to:", world);
    spawnStaticButton({{4, -10.75, -2}, rot, {1, 1, 1}}, "", world);
    spawnSquareButton({{2, -10.75, -2}, rot, {1, 1, 1}}, "OK", {WHITE, GRAY}, upFunction, world);
    spawnButton({{0, -12.25, -2}, rot, {1, 1, 1}}, "Back", {WHITE, GRAY}, rightFunction, world);
}

void bomberman::MainMenuScene::generateKeybindsSettingsMenu(ecs::World &world)
{
    Quaternion rot = QuaternionIdentity();

    spawnTitleButton({{-10, -7.25, -2}, rot, {1, 1, 1}}, "Keybinds Menu", world);
    spawnButton({{-12, -9.25, -2}, rot, {1, 1, 1}}, "Gamepad", {WHITE, GRAY}, rightFunction, world);
    spawnButton({{-8, -9.25, -2}, rot, {1, 1, 1}}, "Keyboard", {WHITE, GRAY}, leftFunction, world);
    spawnButton({{-10, -12.25, -2}, rot, {1, 1, 1}}, "Back", {WHITE, GRAY}, upFunction, world);
    generateGamepadPart(world);
    generateKeyboardPart(world);
}

void bomberman::MainMenuScene::generateGraphicalSettingsMenu(ecs::World &world)
{
    Quaternion rot = QuaternionIdentity();
    float y = 12.75;

    spawnTitleButton({{-10, y, -2}, rot, {1, 1, 1}}, "Graphical settings", world);
    spawnFullscreenButton({{-12.50, y - 1, -2}, rot, {1, 1, 1}}, "Fullscreen", {WHITE, GRAY}, fullscreenFunction, world, {true, false, false});
    spawnFullscreenButton({{-7.50, y - 1, -2}, rot, {1, 1, 1}}, "Windowed", {GREEN, GRAY}, windowedFunction, world, {false, false, false});
    spawnResolutionButton({{-14, y - 2, -2}, rot, {1, 1, 1}}, "1600x900", {WHITE, GRAY}, setResFunction, world, {1600, 900});
    spawnResolutionButton({{-10, y - 2, -2}, rot, {1, 1, 1}}, "1280x720", {WHITE, GRAY}, setResFunction, world, {1280, 720});
    spawnResolutionButton({{-6, y - 2, -2}, rot, {1, 1, 1}}, "854x480", {WHITE, GRAY}, setResFunction, world, {854, 480});
    spawnFPSButton({{-14, y - 3, -2}, rot, {1, 1, 1}}, "30FPS", {WHITE, GRAY}, setFPSFunction, world, {30});
    spawnFPSButton({{-10, y - 3, -2}, rot, {1, 1, 1}}, "60FPS", {WHITE, GRAY}, setFPSFunction, world, {60});
    spawnFPSButton({{-6, y - 3, -2}, rot, {1, 1, 1}}, "Screen rate", {WHITE, GRAY}, setFPSFunction, world, {GetMonitorRefreshRate(GetCurrentMonitor())});
    spawnToggleButton({{-10, y - 4, -2}, rot, {1, 1, 1}}, "Show FPS", {RED, RED}, toggleFunction, world, ecs::ToggleButton::SHOW_FPS);
    spawnButton({{-10, y - 5, -2}, rot, {1, 1, 1}}, "Back", {WHITE, GRAY}, downFunction, world);
}

void bomberman::MainMenuScene::generateSettingsMenu(ecs::World &world)
{
    Quaternion rot = QuaternionIdentity();
    float y = 2.75;

    generateGraphicalSettingsMenu(world);
    generateAudioSettingsMenu(world);
    generateKeybindsSettingsMenu(world);
    spawnTitleButton({{-10, y, -2}, rot, {1, 1, 1}}, "Settings Menu", world);
    spawnButton({{-10, y - 1, -2}, rot, {1, 1, 1}}, "Graphical", {WHITE, GRAY}, upFunction, world);
    spawnButton({{-10, y - 2, -2}, rot, {1, 1, 1}}, "Audio", {WHITE, GRAY}, rightFunction, world);
    spawnButton({{-10, y - 3, -2}, rot, {1, 1, 1}}, "Keybinds", {WHITE, GRAY}, downFunction, world);
    spawnButton({{-10, y - 4, -2}, rot, {1, 1, 1}}, "Main Menu", {WHITE, GRAY}, leftFunction, world);
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

void bomberman::MainMenuScene::spawnToggleButton(const Transform &transform, const std::string &text,
const ecs::HoverTint &hoverTint, ClickCallbackFct doOnClick, ecs::World &world, ecs::ToggleButton::Usage usage)
{
    const float BUTTON_SIZE = 3;

    world.spawn().insert(transform,
    ecs::Text3D {text, BLACK, {0, 0, 0.06}, 12}, ecs::FontRef {"emulogic"},
    ecs::ModelRef {"button"}, hoverTint.base,
    ecs::Hitbox{{-BUTTON_SIZE / 2, -0.4, -0.05}, {BUTTON_SIZE / 2, 0.4, 0.05}},
    ecs::Hoverable {}, hoverTint, ecs::HoverRotate {}, ecs::Clickable {doOnClick},
    ecs::SceneMoveElement {0.7}, ecs::ToggleButton {usage});
}

void bomberman::MainMenuScene::spawnStaticButton(const Transform &transform, const std::string &text, ecs::World &world)
{
    const float BUTTON_SIZE = 3;

    world.spawn().insert(transform,
    ecs::Text3D {text, BLACK, {0, 0, 0.06}, 12}, ecs::FontRef {"emulogic"},
    ecs::ModelRef {"button"}, ecs::SceneMoveElement {0.7});
}

void bomberman::MainMenuScene::spawnTitleButton(const Transform &transform, const std::string &text, ecs::World &world)
{
    const float BUTTON_SIZE = 3;

    world.spawn().insert(transform,
    ecs::Text3D {text, BLACK, {0, 0, 0.06}, 12}, ecs::FontRef {"emulogic"},
    ecs::ModelRef {"large_button"}, ecs::SceneMoveElement {0.7});
}

void bomberman::MainMenuScene::spawnSquareButton(const Transform &transform, const std::string &text,
const ecs::HoverTint &hoverTint, ClickCallbackFct doOnClick, ecs::World &world)
{
    const float BUTTON_SIZE = 3;

    world.spawn().insert(transform,
    ecs::Text3D {text, BLACK, {0, 0, 0.06}, 12}, ecs::FontRef {"emulogic"},
    ecs::ModelRef {"square_button"}, hoverTint.base,
    ecs::Hitbox{{-BUTTON_SIZE / 2, -0.4, -0.05}, {BUTTON_SIZE / 2, 0.4, 0.05}},
    ecs::Hoverable {}, hoverTint, ecs::HoverRotate {}, ecs::Clickable {doOnClick},
    ecs::SceneMoveElement {0.7});
}

void bomberman::MainMenuScene::spawnSquareButton(const Transform &transform, const std::string &text,
const ecs::HoverTint &hoverTint, ClickCallbackFct doOnClick, ecs::World &world, ecs::SingleKeyRecorder &recorder)
{
    const float BUTTON_SIZE = 3;

    world.spawn().insert(transform,
    ecs::Text3D {text, BLACK, {0, 0, 0.06}, 12}, ecs::FontRef {"emulogic"},
    ecs::ModelRef {"square_button"}, hoverTint.base,
    ecs::Hitbox{{-BUTTON_SIZE / 2, -0.4, -0.05}, {BUTTON_SIZE / 2, 0.4, 0.05}},
    ecs::Hoverable {}, hoverTint, ecs::HoverRotate {}, ecs::Clickable {doOnClick},
    ecs::SceneMoveElement {0.7}, recorder);
}