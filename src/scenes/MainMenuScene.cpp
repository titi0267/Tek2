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
#include "scenes/GameScene.hpp"

#include "ecs/engine/EntityCommands.hpp"

#include "raylib/Camera.hpp"
#include "raylib/Window.hpp"
#include "raylib/Sound.hpp"

#include "raylib/SoundManager.hpp"

#include "raylib/TextureManager.hpp"
#include "raylib/ModelManager.hpp"
#include "raylib/AnimationManager.hpp"
#include "raylib/FontManager.hpp"
#include "raylib/ShaderManager.hpp"

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
#include "ecs/components/TextInput.hpp"
#include "ecs/components/BackgroundRotation.hpp"
#include "ecs/components/Timer.hpp"
#include "ecs/components/ShaderValueSetter.hpp"

void toggleLoadKeyboard(ecs::World &world, ecs::Entity entity)
{
    ecs::BindManager &bind = world.getRessource<ecs::BindManager>();

    try {
        bind.load(false, bind.getLoadStr(false));
    }
    catch (std::invalid_argument) {
        world.getComponent<ecs::Tint>(entity) = RED;
        return;
    }
    world.getComponent<ecs::Tint>(entity) = GREEN;
}

void toggleLoadGamepad(ecs::World &world, ecs::Entity entity)
{
    ecs::BindManager &bind = world.getRessource<ecs::BindManager>();

    try {
        bind.load(true, bind.getLoadStr(true));
    }
    catch (std::invalid_argument) {
        world.getComponent<ecs::Tint>(entity) = RED;
        return;
    }
    world.getComponent<ecs::Tint>(entity) = GREEN;
}

void toggleSaveKeyboard(ecs::World &world, ecs::Entity entity)
{
    ecs::BindManager &bind = world.getRessource<ecs::BindManager>();

    bind.save(0);
    world.getComponent<ecs::Tint>(entity) = GREEN;
}

void toggleSaveGamepad(ecs::World &world, ecs::Entity entity)
{
    ecs::BindManager &bind = world.getRessource<ecs::BindManager>();

    bind.save(1);
    world.getComponent<ecs::Tint>(entity) = GREEN;
}

void toggleKeyRecordFunction(ecs::World &world, ecs::Entity entity)
{
    ecs::SingleKeyRecorder &key = world.getComponent<ecs::SingleKeyRecorder>(entity);
    ecs::BindManager &bind = world.getRessource<ecs::BindManager>();

    key.recording = true;
    key.first = true;
    bind.toggleSetOff(key.gamepad);
    if (!bind.getRecording(key.gamepad))
        bind.toggleRecording(key.gamepad);
    if (bind.getTextInput(key.gamepad))
        bind.toggleTextInput(key.gamepad);
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

void startFunction(ecs::World &world, ecs::Entity entity)
{
    world.getRessource<ecs::SceneManager>().changeScene(ecs::GAME_SCENE,
    std::make_shared<bomberman::GameSceneArgs>("127.0.0.1", "4242", true, 1));
}

void connectFunction(ecs::World &world, ecs::Entity entity)
{
    world.getRessource<ecs::SceneManager>().changeScene(ecs::GAME_SCENE,
    std::make_shared<bomberman::GameSceneArgs>("127.0.0.1", "4242", false, 1));
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
        scene.getMoveDest() = {0, 15, 0};
        world.getComponent<ecs::Tint>(entity) = RED;
    } catch (std::bad_cast) {};
}

void upFunction(ecs::World &world, ecs::Entity entity)
{
    ecs::SceneManager &man = world.getRessource<ecs::SceneManager>();

    try {
        ecs::MoveRequesterSceneModule &scene = dynamic_cast<ecs::MoveRequesterSceneModule&>(man.getScene());

        scene.getMovementRequest() = true;
        scene.getMoveDest() = {0, -15, 0};
        world.getComponent<ecs::Tint>(entity) = RED;
    } catch (std::bad_cast) {};
}

void rightFunction(ecs::World &world, ecs::Entity entity)
{
    ecs::SceneManager &man = world.getRessource<ecs::SceneManager>();

    try {
        ecs::MoveRequesterSceneModule &scene = dynamic_cast<ecs::MoveRequesterSceneModule&>(man.getScene());

        scene.getMovementRequest() = true;
        scene.getMoveDest() = {15, 0, 0};
        world.getComponent<ecs::Tint>(entity) = RED;
    } catch (std::bad_cast) {};
}

void leftFunction(ecs::World &world, ecs::Entity entity)
{
    ecs::SceneManager &man = world.getRessource<ecs::SceneManager>();

    try {
        ecs::MoveRequesterSceneModule &scene = dynamic_cast<ecs::MoveRequesterSceneModule&>(man.getScene());

        scene.getMovementRequest() = true;
        scene.getMoveDest() = {-15, 0, 0};
        world.getComponent<ecs::Tint>(entity) = RED;
    } catch (std::bad_cast) {};
}

void setProgressShaderValue(ecs::World &world, ecs::Entity entity)
{
    raylib::ShaderManager &man = world.getRessource<raylib::ShaderManager>();
    raylib::Shader &shader = man.getShader("progress_button");
    static int progressLoc = -1;
    static int colorLoc = -1;
    float percentage = 0.5f;
    Vector4 color = {1.0, 1.0, 0.0, 1.0};

    if (progressLoc == -1) {
        progressLoc = shader.getShaderLocation("progress");
        colorLoc = shader.getShaderLocation("progressColor");
    }
    shader.setShaderValue(progressLoc, &percentage, SHADER_UNIFORM_FLOAT);
    shader.setShaderValue(colorLoc, &color, SHADER_UNIFORM_VEC4);
}

void bomberman::MainMenuScene::loadScene(ecs::World &world)
{
    raylib::Camera &cam = world.getRessource<raylib::Camera>();

    cam.setPosition({0, 0, 2});
    cam.setTarget({0, 0, 0});
    spawnBackground(world);
    generateMainMenu(world);
    generateSettingsMenu(world);
}

void bomberman::MainMenuScene::unloadScene(ecs::World &world)
{
    world.killAllEntities();
}

void bomberman::MainMenuScene::spawnBackground(ecs::World &world)
{
    world.spawn().insert(Transform {{0, 0, -8}, QuaternionFromEuler(0, 0, PI), {1, 1, 1}}, ecs::TextureRef{"epitech"},
    ecs::DrawableCube{{0, 0, 0}, {36, 20, 0.1}}, ecs::BackgroundRotation {}, ecs::Timer {});
}

void bomberman::MainMenuScene::generateMainMenu(ecs::World &world)
{
    Quaternion rot = QuaternionIdentity();
    auto &man = world.getRessource<raylib::SoundManager>();
    auto &music = man.getSound("main_menu_music");

    music.playSound();

    world.spawn().insert(Transform {{0, 2.25, -2}, QuaternionIdentity(), {1, 1, 1}},
    ecs::ModelRef{"logo"}, ecs::SceneMoveElement{MOVE_SPEED});

    spawnButton({{0,  1.25, -2}, rot, {1, 1, 1}}, "Start", {WHITE, GREEN}, startFunction, world);
    spawnButton({{0,  0.50, -2}, rot, {1, 1, 1}}, "Connect", {WHITE, GREEN}, connectFunction, world);
    spawnButton({{0, -0.50, -2}, rot, {1, 1, 1}}, "Tutorial", {WHITE, GRAY}, quitFunction, world);
    spawnButton({{0, -1.25, -2}, rot, {1, 1, 1}}, "Settings", {WHITE, GRAY}, rightFunction, world);
    spawnButton({{0, -2.50, -2}, rot, {1, 1, 1}}, "Quit", {WHITE, RED}, quitFunction, world);
}

void bomberman::MainMenuScene::generateAudioSettingsMenu(ecs::World &world)
{
    Quaternion rot = QuaternionIdentity();
    float y = 2.75;

    spawnTitleButton({{-30, y, -2}, rot, {1, 1, 1}}, "Settings Menu", world);
    spawnToggleButton({{-30, y - 1, -2}, rot, {1, 1, 1}}, "Music is on!", {BLUE, BLUE}, toggleFunction, world, ecs::ToggleButton::MUSIC);
    spawnToggleButton({{-30, y - 2, -2}, rot, {1, 1, 1}}, "Sound is on!", {BLUE, BLUE}, toggleFunction, world, ecs::ToggleButton::SOUND);
    // CHANGE WITH NUANCER
    spawnProgressButton({{-30, y - 3, -2}, rot, {1, 1, 1}}, ("Music: 100" ), {BLUE, BLUE}, toggleFunction, world, ecs::ToggleButton::SOUND);
    spawnProgressButton({{-30, y - 4, -2}, rot, {1, 1, 1}}, ("Sound: 100"), {BLUE, BLUE}, toggleFunction, world, ecs::ToggleButton::SOUND);
    // CHANGE WITH NUANCER
    spawnButton({{-30, y - 5, -2}, rot, {1, 1, 1}}, "Back", {WHITE, GRAY}, leftFunction, world);
}

void bomberman::MainMenuScene::generateGamepadPart(ecs::World &world)
{
    Quaternion rot = QuaternionIdentity();
    ecs::SingleKeyRecorder a = {true, IBind::UP};
    ecs::SingleKeyRecorder b = {true, IBind::LEFT};
    ecs::SingleKeyRecorder c = {true, IBind::RIGHT};
    ecs::SingleKeyRecorder d = {true, IBind::DOWN};
    ecs::SingleKeyRecorder e = {true, IBind::PLACE};
    ecs::TextInputSettings first = {true, false};
    ecs::TextInputSettings second = {true, true};

    spawnStaticButton({{-28, -12.25, -2}, rot, {1, 1, 1}}, "Up", world);
    spawnStaticButton({{-28, -13.25, -2}, rot, {1, 1, 1}}, "Left", world);
    spawnStaticButton({{-28, -14.25, -2}, rot, {1, 1, 1}}, "Right", world);
    spawnStaticButton({{-28, -15.25, -2}, rot, {1, 1, 1}}, "Down", world);
    spawnStaticButton({{-28, -16.25, -2}, rot, {1, 1, 1}}, "Place bomb", world);
    spawnSquareButton({{-25.5, -12.25, -2}, rot, {1, 1, 1}}, " ", {WHITE, GRAY}, toggleKeyRecordFunction, world, a);
    spawnSquareButton({{-25.5, -13.25, -2}, rot, {1, 1, 1}}, " ", {WHITE, GRAY}, toggleKeyRecordFunction, world, b);
    spawnSquareButton({{-25.5, -14.25, -2}, rot, {1, 1, 1}}, " ", {WHITE, GRAY}, toggleKeyRecordFunction, world, c);
    spawnSquareButton({{-25.5, -15.25, -2}, rot, {1, 1, 1}}, " ", {WHITE, GRAY}, toggleKeyRecordFunction, world, d);
    spawnSquareButton({{-25.5, -16.25, -2}, rot, {1, 1, 1}}, " ", {WHITE, GRAY}, toggleKeyRecordFunction, world, e);
    spawnStaticButton({{-33, -12.75, -2}, rot, {1, 1, 1}}, "Load from:", world);
    spawnTextInputButton({{-33.5, -13.75, -2}, rot, {1, 1, 1}}, "", {WHITE, BLUE}, world, first);
    spawnSquareButton({{-31, -13.75, -2}, rot, {1, 1, 1}}, "OK", {WHITE, GRAY}, toggleLoadGamepad, world);
    spawnStaticButton({{-33, -14.75, -2}, rot, {1, 1, 1}}, "Save to:", world);
    spawnTextInputButton({{-33.5, -15.75, -2}, rot, {1, 1, 1}}, "", {WHITE, BLUE}, world, second);
    spawnSquareButton({{-31, -15.75, -2}, rot, {1, 1, 1}}, "OK", {WHITE, GRAY}, toggleSaveGamepad, world);
    spawnButton({{-30, -17.25, -2}, rot, {1, 1, 1}}, "Back", {WHITE, GRAY}, leftFunction, world);
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
    ecs::TextInputSettings first = {false, false};
    ecs::TextInputSettings second = {false, true};

    spawnStaticButton({{-2, -12.25, -2}, rot, {1, 1, 1}}, "Up", world);
    spawnStaticButton({{-2, -13.25, -2}, rot, {1, 1, 1}}, "Left", world);
    spawnStaticButton({{-2, -14.25, -2}, rot, {1, 1, 1}}, "Right", world);
    spawnStaticButton({{-2, -15.25, -2}, rot, {1, 1, 1}}, "Down", world);
    spawnStaticButton({{-2, -16.25, -2}, rot, {1, 1, 1}}, "Place bomb", world);
    spawnSquareButton({{-4.5, -12.25, -2}, rot, {1, 1, 1}}, " ", {WHITE, GRAY}, toggleKeyRecordFunction, world, a);
    spawnSquareButton({{-4.5, -13.25, -2}, rot, {1, 1, 1}}, " ", {WHITE, GRAY}, toggleKeyRecordFunction, world, b);
    spawnSquareButton({{-4.5, -14.25, -2}, rot, {1, 1, 1}}, " ", {WHITE, GRAY}, toggleKeyRecordFunction, world, c);
    spawnSquareButton({{-4.5, -15.25, -2}, rot, {1, 1, 1}}, " ", {WHITE, GRAY}, toggleKeyRecordFunction, world, d);
    spawnSquareButton({{-4.5, -16.25, -2}, rot, {1, 1, 1}}, " ", {WHITE, GRAY}, toggleKeyRecordFunction, world, e);
    spawnStaticButton({{3, -12.75, -2}, rot, {1, 1, 1}}, "Load from:", world);
    spawnTextInputButton({{3.5, -13.75, -2}, rot, {1, 1, 1}}, "", {WHITE, BLUE}, world, first);
    spawnSquareButton({{1, -13.75, -2}, rot, {1, 1, 1}}, "OK", {WHITE, GRAY}, toggleLoadKeyboard, world);
    spawnStaticButton({{3, -14.75, -2}, rot, {1, 1, 1}}, "Save to:", world);
    spawnTextInputButton({{3.5, -15.75, -2}, rot, {1, 1, 1}}, "", {WHITE, BLUE}, world, second);
    spawnSquareButton({{1, -15.75, -2}, rot, {1, 1, 1}}, "OK", {WHITE, GRAY}, toggleSaveKeyboard, world);
    spawnButton({{0, -17.25, -2}, rot, {1, 1, 1}}, "Back", {WHITE, GRAY}, rightFunction, world);
}

void bomberman::MainMenuScene::generateKeybindsSettingsMenu(ecs::World &world)
{
    Quaternion rot = QuaternionIdentity();

    spawnTitleButton({{-15, -12.25, -2}, rot, {1, 1, 1}}, "Keybinds Menu", world);
    spawnButton({{-17, -14.25, -2}, rot, {1, 1, 1}}, "Gamepad", {WHITE, GRAY}, rightFunction, world);
    spawnButton({{-13, -14.25, -2}, rot, {1, 1, 1}}, "Keyboard", {WHITE, GRAY}, leftFunction, world);
    spawnButton({{-15, -17.25, -2}, rot, {1, 1, 1}}, "Back", {WHITE, GRAY}, upFunction, world);
    generateGamepadPart(world);
    generateKeyboardPart(world);
}

void bomberman::MainMenuScene::generateGraphicalSettingsMenu(ecs::World &world)
{
    Quaternion rot = QuaternionIdentity();
    float y = 17.75;

    spawnTitleButton({{-15, y, -2}, rot, {1, 1, 1}}, "Graphical settings", world);
    spawnFullscreenButton({{-17.50, y - 1, -2}, rot, {1, 1, 1}}, "Fullscreen", {WHITE, GRAY}, fullscreenFunction, world, {true, false, false});
    spawnFullscreenButton({{-12.50, y - 1, -2}, rot, {1, 1, 1}}, "Windowed", {GREEN, GRAY}, windowedFunction, world, {false, false, false});
    spawnResolutionButton({{-19, y - 2, -2}, rot, {1, 1, 1}}, "1600x900", {WHITE, GRAY}, setResFunction, world, {1600, 900});
    spawnResolutionButton({{-15, y - 2, -2}, rot, {1, 1, 1}}, "1280x720", {WHITE, GRAY}, setResFunction, world, {1280, 720});
    spawnResolutionButton({{-11, y - 2, -2}, rot, {1, 1, 1}}, "854x480", {WHITE, GRAY}, setResFunction, world, {854, 480});
    spawnFPSButton({{-19, y - 3, -2}, rot, {1, 1, 1}}, "30FPS", {WHITE, GRAY}, setFPSFunction, world, {30});
    spawnFPSButton({{-15, y - 3, -2}, rot, {1, 1, 1}}, "60FPS", {WHITE, GRAY}, setFPSFunction, world, {60});
    spawnFPSButton({{-11, y - 3, -2}, rot, {1, 1, 1}}, "Screen rate", {WHITE, GRAY}, setFPSFunction, world, {GetMonitorRefreshRate(GetCurrentMonitor())});
    spawnToggleButton({{-15, y - 4, -2}, rot, {1, 1, 1}}, "Show FPS", {RED, RED}, toggleFunction, world, ecs::ToggleButton::SHOW_FPS);
    spawnButton({{-15, y - 5, -2}, rot, {1, 1, 1}}, "Back", {WHITE, GRAY}, downFunction, world);
}

void bomberman::MainMenuScene::generateSettingsMenu(ecs::World &world)
{
    Quaternion rot = QuaternionIdentity();
    float y = 2.75;

    generateGraphicalSettingsMenu(world);
    generateAudioSettingsMenu(world);
    generateKeybindsSettingsMenu(world);
    spawnTitleButton({{-15, y, -2}, rot, {1, 1, 1}}, "Settings Menu", world);
    spawnButton({{-15, y - 1, -2}, rot, {1, 1, 1}}, "Graphical", {WHITE, GRAY}, upFunction, world);
    spawnButton({{-15, y - 2, -2}, rot, {1, 1, 1}}, "Audio", {WHITE, GRAY}, rightFunction, world);
    spawnButton({{-15, y - 3, -2}, rot, {1, 1, 1}}, "Keybinds", {WHITE, GRAY}, downFunction, world);
    spawnButton({{-15, y - 4, -2}, rot, {1, 1, 1}}, "Main Menu", {WHITE, GRAY}, leftFunction, world);
}

void bomberman::MainMenuScene::spawnButton(const Transform &transform, const std::string &text,
const ecs::HoverTint &hoverTint, ClickCallbackFct doOnClick, ecs::World &world)
{
    const float BUTTON_SIZE = 3;

    world.spawn().insert(transform,
    ecs::Text3D {text, BLACK, {0, 0, 0.06}, 12}, ecs::FontRef {"emulogic"},
    ecs::ModelRef {"button"}, hoverTint.base,
    ecs::Hitbox{{-BUTTON_SIZE / 2, -0.4, -0.05}, {BUTTON_SIZE / 2, 0.4, 0.05}},
    ecs::Hoverable {}, hoverTint, ecs::HoverRotate {}, ecs::Timer {}, ecs::Timer {}, ecs::Clickable {doOnClick},
    ecs::SceneMoveElement {MOVE_SPEED});
}

void bomberman::MainMenuScene::spawnFullscreenButton(const Transform &transform, const std::string &text,
const ecs::HoverTint &hoverTint, ClickCallbackFct doOnClick, ecs::World &world, const ecs::FullscreenButton &but)
{
    const float BUTTON_SIZE = 3;

    world.spawn().insert(transform,
    ecs::Text3D {text, BLACK, {0, 0, 0.06}, 12}, ecs::FontRef {"emulogic"},
    ecs::ModelRef {"button"}, hoverTint.base,
    ecs::Hitbox{{-BUTTON_SIZE / 2, -0.4, -0.05}, {BUTTON_SIZE / 2, 0.4, 0.05}},
    ecs::Hoverable {}, hoverTint, ecs::HoverRotate {}, ecs::Timer {}, ecs::Timer {}, ecs::Clickable {doOnClick},
    ecs::SceneMoveElement {MOVE_SPEED}, but);
}

void bomberman::MainMenuScene::spawnResolutionButton(const Transform &transform, const std::string &text,
const ecs::HoverTint &hoverTint, ClickCallbackFct doOnClick, ecs::World &world, const ecs::ResolutionButton &res)
{
    const float BUTTON_SIZE = 3;

    world.spawn().insert(transform,
    ecs::Text3D {text, BLACK, {0, 0, 0.06}, 12}, ecs::FontRef {"emulogic"},
    ecs::ModelRef {"button"}, hoverTint.base,
    ecs::Hitbox{{-BUTTON_SIZE / 2, -0.4, -0.05}, {BUTTON_SIZE / 2, 0.4, 0.05}},
    ecs::Hoverable {}, hoverTint, ecs::HoverRotate {}, ecs::Timer {}, ecs::Timer {}, ecs::Clickable {doOnClick},
    ecs::SceneMoveElement {MOVE_SPEED}, res);
}

void bomberman::MainMenuScene::spawnFPSButton(const Transform &transform, const std::string &text,
const ecs::HoverTint &hoverTint, ClickCallbackFct doOnClick, ecs::World &world, const ecs::FPSButton &but)
{
    const float BUTTON_SIZE = 3;

    world.spawn().insert(transform,
    ecs::Text3D {text, BLACK, {0, 0, 0.06}, 12}, ecs::FontRef {"emulogic"},
    ecs::ModelRef {"button"}, hoverTint.base,
    ecs::Hitbox{{-BUTTON_SIZE / 2, -0.4, -0.05}, {BUTTON_SIZE / 2, 0.4, 0.05}},
    ecs::Hoverable {}, hoverTint, ecs::HoverRotate {}, ecs::Timer {}, ecs::Clickable {doOnClick},
    ecs::SceneMoveElement {MOVE_SPEED}, but);
}

void bomberman::MainMenuScene::spawnToggleButton(const Transform &transform, const std::string &text,
const ecs::HoverTint &hoverTint, ClickCallbackFct doOnClick, ecs::World &world, ecs::ToggleButton::Usage usage)
{
    const float BUTTON_SIZE = 3;

    world.spawn().insert(transform,
    ecs::Text3D {text, BLACK, {0, 0, 0.06}, 12}, ecs::FontRef {"emulogic"},
    ecs::ModelRef {"button"}, hoverTint.base,
    ecs::Hitbox{{-BUTTON_SIZE / 2, -0.4, -0.05}, {BUTTON_SIZE / 2, 0.4, 0.05}},
    ecs::Hoverable {}, hoverTint, ecs::HoverRotate {}, ecs::Timer {}, ecs::Clickable {doOnClick},
    ecs::SceneMoveElement {MOVE_SPEED}, ecs::ToggleButton {usage});
}

void bomberman::MainMenuScene::spawnProgressButton(const Transform &transform, const std::string &text,
const ecs::HoverTint &hoverTint, ClickCallbackFct doOnClick, ecs::World &world, ecs::ToggleButton::Usage usage)
{
    const float BUTTON_SIZE = 3;

    world.spawn().insert(transform,
    ecs::Text3D {text, BLACK, {0, 0, 0.06}, 12}, ecs::FontRef {"emulogic"},
    ecs::ModelRef {"progress_button"}, hoverTint.base,
    ecs::Hitbox{{-BUTTON_SIZE / 2, -0.4, -0.05}, {BUTTON_SIZE / 2, 0.4, 0.05}},
    ecs::Hoverable {}, hoverTint, ecs::HoverRotate {}, ecs::Timer {}, ecs::Clickable {doOnClick},
    ecs::SceneMoveElement {MOVE_SPEED}, ecs::ToggleButton {usage},
    ecs::ShaderValueSetter{setProgressShaderValue});
}

void bomberman::MainMenuScene::spawnTextInputButton(const Transform &transform, const std::string &text,
const ecs::HoverTint &hoverTint, ecs::World &world, ecs::TextInputSettings &set)
{
    const float BUTTON_SIZE = 3;

    world.spawn().insert(transform,
    ecs::Text3D {text, BLACK, {0, 0, 0.06}, 12}, ecs::FontRef {"emulogic"},
    ecs::ModelRef {"button"}, hoverTint.base,
    ecs::Hitbox{{-BUTTON_SIZE / 2, -0.4, -0.05}, {BUTTON_SIZE / 2, 0.4, 0.05}},
    ecs::Hoverable {}, hoverTint,
    ecs::SceneMoveElement {MOVE_SPEED}, set);
}

void bomberman::MainMenuScene::spawnStaticButton(const Transform &transform, const std::string &text, ecs::World &world)
{
    const float BUTTON_SIZE = 3;

    world.spawn().insert(transform,
    ecs::Text3D {text, BLACK, {0, 0, 0.06}, 12}, ecs::FontRef {"emulogic"},
    ecs::ModelRef {"button"}, ecs::SceneMoveElement {MOVE_SPEED});
}

void bomberman::MainMenuScene::spawnTitleButton(const Transform &transform, const std::string &text, ecs::World &world)
{
    const float BUTTON_SIZE = 3;

    world.spawn().insert(transform,
    ecs::Text3D {text, BLACK, {0, 0, 0.06}, 12}, ecs::FontRef {"emulogic"},
    ecs::ModelRef {"large_button"}, ecs::SceneMoveElement {MOVE_SPEED});
}

void bomberman::MainMenuScene::spawnSquareButton(const Transform &transform, const std::string &text,
const ecs::HoverTint &hoverTint, ClickCallbackFct doOnClick, ecs::World &world)
{
    const float BUTTON_SIZE = 3;

    world.spawn().insert(transform,
    ecs::Text3D {text, BLACK, {0, 0, 0.06}, 12}, ecs::FontRef {"emulogic"},
    ecs::ModelRef {"square_button"}, hoverTint.base,
    ecs::Hitbox{{-BUTTON_SIZE / 2, -0.4, -0.05}, {BUTTON_SIZE / 2, 0.4, 0.05}},
    ecs::Hoverable {}, hoverTint, ecs::Clickable {doOnClick},
    ecs::SceneMoveElement {MOVE_SPEED});
}

void bomberman::MainMenuScene::spawnSquareButton(const Transform &transform, const std::string &text,
const ecs::HoverTint &hoverTint, ClickCallbackFct doOnClick, ecs::World &world, ecs::SingleKeyRecorder &recorder)
{
    const float BUTTON_SIZE = 3;

    world.spawn().insert(transform,
    ecs::Text3D {text, BLACK, {0, 0, 0.06}, 12}, ecs::FontRef {"emulogic"},
    ecs::ModelRef {"square_button"}, hoverTint.base,
    ecs::Hitbox{{-BUTTON_SIZE / 2, -0.4, -0.05}, {BUTTON_SIZE / 2, 0.4, 0.05}},
    ecs::Hoverable {}, hoverTint, ecs::Clickable {doOnClick},
    ecs::SceneMoveElement {MOVE_SPEED}, recorder);
}
