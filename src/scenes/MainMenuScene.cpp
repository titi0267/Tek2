/*
** EPITECH PROJECT, 2022
** indieStudio
** File description:
** Menu
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>
#include <filesystem>

#include "scenes/MainMenuScene.hpp"
#include "scenes/GameScene.hpp"

#include "ecs/engine/EntityCommands.hpp"
#include "ecs/engine/LaunchManager.hpp"

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
#include "ecs/components/IsMusic.hpp"
#include "ecs/components/Disappear.hpp"

void checkIp(ecs::World &world, ecs::Entity entity)
{
    std::smatch match;
    ecs::Text3D &but = world.getComponent<ecs::Text3D>(entity);
    Color &col = world.getComponent<Color>(entity);
    std::string text = but.getText();

    if (!std::regex_search(text, match, std::regex("((?:[0-9]{1,3}.){3}[0-9]{1,3})((?:[0-9]{0,5}))?")))
        col = RED;
    else
        col = GREEN;
}

void swapProfile(ecs::World &world, ecs::Entity entity)
{
    ecs::LaunchManager &man = world.getRessource<ecs::LaunchManager>();
    ecs::LaunchButton &but = world.getComponent<ecs::LaunchButton>(entity);

    man.swap(but.host, but.butNum);
}

void incNbPlayerHostFunction(ecs::World &world, ecs::Entity entity)
{
    ecs::LaunchManager &man = world.getRessource<ecs::LaunchManager>();
    ecs::Text3D &text = world.getComponent<ecs::Text3D>(entity);

    if (man.getNbPlayers(true) == 4)
        man.setNbPlayers(true, 1);
    else
        man.setNbPlayers(true, man.getNbPlayers(true) + 1);
    switch (man.getNbPlayers(true))
    {
        case 1:
            text.setText("Solo");
            text.color = BLACK;
            break;
        case 2:
            text.setText("Duo");
            text.color = YELLOW;
            break;
        case 3:
            text.setText("Trio");
            text.color = ORANGE;
            break;
        default:
            text.setText("Full!");
            text.color = RED;
            break;
    }
}

void incNbPlayerConnectFunction(ecs::World &world, ecs::Entity entity)
{
    ecs::LaunchManager &man = world.getRessource<ecs::LaunchManager>();
    ecs::Text3D &text = world.getComponent<ecs::Text3D>(entity);

    if (man.getNbPlayers(false) == 3)
        man.setNbPlayers(false, 1);
    else
        man.setNbPlayers(false, man.getNbPlayers(false) + 1);
    switch (man.getNbPlayers(false))
    {
        case 1:
            text.setText("Solo");
            text.color = BLACK;
            break;
        case 2:
            text.setText("Duo");
            text.color = ORANGE;
            break;
        default:
            text.setText("Full!");
            text.color = RED;
            break;
    }
}

void deleteGameSave(ecs::World &world, ecs::Entity entity)
{
    if (std::filesystem::exists("bombitek.dat") && std::filesystem::exists("bombitek.map")) {
        std::remove("bombitek.dat");
        std::remove("bombitek.map");
    }
}

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

void getPercentage(ecs::World &world, ecs::Entity entity)
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
    ecs::LaunchManager &launch = world.getRessource<ecs::LaunchManager>();
    world.getRessource<ecs::SceneManager>().changeScene(ecs::GAME_SCENE,
    std::make_shared<bomberman::GameSceneArgs>("127.0.0.1", launch.getPort(), true, launch.getNbPlayers(true)));
}

void connectFunction(ecs::World &world, ecs::Entity entity)
{
    ecs::LaunchManager &man = world.getRessource<ecs::LaunchManager>();
    std::smatch match;
    Color &col = world.getComponent<Color>(entity);

    if (!std::regex_search(man.getIpPort(), match, std::regex("((?:[0-9]{1,3}.){3}[0-9]{1,3}) ((?:[0-9]{0,5}))?"))) {
        col = RED;
        return;
    }
    world.getRessource<ecs::SceneManager>().changeScene(ecs::GAME_SCENE,
    std::make_shared<bomberman::GameSceneArgs>(match[1].str(), match[2].str(), false, man.getNbPlayers(false)));
}

void quitFunction(ecs::World &world, ecs::Entity entity)
{
    world.getComponent<ecs::Tint>(entity) = RED;
    world.getRessource<raylib::Window>().toggleClose();
}

void soundUp(ecs::World &world, ecs::Entity entity)
{
    raylib::SoundManager &man = world.getRessource<raylib::SoundManager>();
    float vol = man.getSoundVolume() + 0.1;
    man.setSoundVolume(vol > 1 ? 1 : vol);
    man.applySoundVolume();
}

void soundDown(ecs::World &world, ecs::Entity entity)
{
    raylib::SoundManager &man = world.getRessource<raylib::SoundManager>();
    float vol = man.getSoundVolume() - 0.1;
    man.setSoundVolume(vol < 0 ? 0 : vol);
    man.applySoundVolume();
}

void musicUp(ecs::World &world, ecs::Entity entity)
{
    raylib::SoundManager &man = world.getRessource<raylib::SoundManager>();
    float vol = man.getMusicVolume() + 0.1;

    man.setMusicVolume(vol > 1 ? 1 : vol);
    man.applyMusicVolume();
}

void musicDown(ecs::World &world, ecs::Entity entity)
{
    raylib::SoundManager &man = world.getRessource<raylib::SoundManager>();
    float vol = man.getMusicVolume() - 0.1;

    man.setMusicVolume(vol < 0 ? 0 : vol);
    man.applyMusicVolume();
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
    raylib::SoundManager &sMan = world.getRessource<raylib::SoundManager>();
    ecs::IsMusic &music = world.getComponent<ecs::IsMusic>(entity);
    static int progressLoc = -1;
    static int colorLoc = -1;
    float percentage = music.volume ? sMan.getMusicVolume() : sMan.getSoundVolume();
    Vector4 color = {1.0, 1.0, 0.0, 1.0};

    if (progressLoc == -1) {
        progressLoc = shader.getShaderLocation("progress");
        colorLoc = shader.getShaderLocation("progressColor");
    }
    shader.setShaderValue(progressLoc, &percentage, SHADER_UNIFORM_FLOAT);
    shader.setShaderValue(colorLoc, &color, SHADER_UNIFORM_VEC4);
}

void startMenu(ecs::World &world, ecs::Entity entity)
{
    ecs::LaunchManager &man = world.getRessource<ecs::LaunchManager>();

    man.reload();
    upFunction(world, entity);
}

void connectMenu(ecs::World &world, ecs::Entity entity)
{
    ecs::LaunchManager &man = world.getRessource<ecs::LaunchManager>();

    man.reload();
    leftFunction(world, entity);
}

void bomberman::MainMenuScene::loadScene(ecs::World &world)
{
    raylib::Camera &cam = world.getRessource<raylib::Camera>();

    world.getRessource<ecs::LaunchManager>().reload();
    cam.setPosition({0, 0, 2});
    cam.setTarget({0, 0, 0});
    spawnBackground(world);
    generateMainMenu(world);
    generateStartMenu(world);
    generateConnectMenu(world);
    generateSettingsMenu(world);
}

void bomberman::MainMenuScene::unloadScene(ecs::World &world)
{
    auto &man = world.getRessource<raylib::SoundManager>();
    auto &music = man.getSound("main_menu_music");

    music.stopSound();
    world.killAllEntities();
}

void bomberman::MainMenuScene::spawnBackground(ecs::World &world)
{
    world.spawn().insert(Transform {{0, 0, -8}, QuaternionFromEuler(0, 0, PI), {1, 1, 1}}, ecs::TextureRef{"epitech"},
    ecs::DrawableCube{{0, 0, 0}, {36, 20, 0.1}}, ecs::BackgroundRotation {}, ecs::Timer {});
}

void bomberman::MainMenuScene::generateStartMenu(ecs::World &world)
{
    Quaternion rot = QuaternionIdentity();

    spawnTitleButton({{0, 17.75, -2}, rot, {1, 1, 1}}, "Start menu", world);
    spawnTextInputPort({{-4, 17.00, -2}, rot, {1, 1, 1}}, "Custom Port", {WHITE, BLUE}, world);
    spawnButton({{0, 17.00, -2}, rot, {1, 1, 1}}, "Solo", {WHITE, GRAY}, incNbPlayerHostFunction, world);
    spawnLaunchButton({{-3, 16.25, -2}, rot, {1, 1, 1}}, "", world, {true, 0}, swapProfile);
    spawnLittleSquareButton({{-5.00, 15.50, -2}, rot, {1, 1, 1}}, "", world, {true, 0, IBind::UP});
    spawnLittleSquareButton({{-4.00, 15.50, -2}, rot, {1, 1, 1}}, "", world, {true, 0, IBind::DOWN});
    spawnLittleSquareButton({{-3.00, 15.50, -2}, rot, {1, 1, 1}}, "", world, {true, 0, IBind::LEFT});
    spawnLittleSquareButton({{-2.00, 15.50, -2}, rot, {1, 1, 1}}, "", world, {true, 0, IBind::RIGHT});
    spawnLittleSquareButton({{-1.00, 15.50, -2}, rot, {1, 1, 1}}, "", world, {true, 0, IBind::PLACE});
    spawnLaunchButton({{3, 16.25, -2}, rot, {1, 1, 1}}, "", world, {true, 1}, swapProfile);
    spawnLittleSquareButton({{5.00, 15.50, -2}, rot, {1, 1, 1}}, "", world, {true, 1, IBind::PLACE});
    spawnLittleSquareButton({{4.00, 15.50, -2}, rot, {1, 1, 1}}, "", world, {true, 1, IBind::RIGHT});
    spawnLittleSquareButton({{3.00, 15.50, -2}, rot, {1, 1, 1}}, "", world, {true, 1, IBind::LEFT});
    spawnLittleSquareButton({{2.00, 15.50, -2}, rot, {1, 1, 1}}, "", world, {true, 1, IBind::DOWN});
    spawnLittleSquareButton({{1.00, 15.50, -2}, rot, {1, 1, 1}}, "", world, {true, 1, IBind::UP});
    spawnLaunchButton({{-3, 14.75, -2}, rot, {1, 1, 1}}, "", world, {true, 2}, swapProfile);
    spawnLittleSquareButton({{-5.00, 14.00, -2}, rot, {1, 1, 1}}, "", world, {true, 2, IBind::UP});
    spawnLittleSquareButton({{-4.00, 14.00, -2}, rot, {1, 1, 1}}, "", world, {true, 2, IBind::DOWN});
    spawnLittleSquareButton({{-3.00, 14.00, -2}, rot, {1, 1, 1}}, "", world, {true, 2, IBind::LEFT});
    spawnLittleSquareButton({{-2.00, 14.00, -2}, rot, {1, 1, 1}}, "", world, {true, 2, IBind::RIGHT});
    spawnLittleSquareButton({{-1.00, 14.00, -2}, rot, {1, 1, 1}}, "", world, {true, 2, IBind::PLACE});
    spawnLaunchButton({{3, 14.75, -2}, rot, {1, 1, 1}}, "", world, {true, 3}, swapProfile);
    spawnLittleSquareButton({{5.00, 14.00, -2}, rot, {1, 1, 1}}, "", world, {true, 3, IBind::PLACE});
    spawnLittleSquareButton({{4.00, 14.00, -2}, rot, {1, 1, 1}}, "", world, {true, 3, IBind::RIGHT});
    spawnLittleSquareButton({{3.00, 14.00, -2}, rot, {1, 1, 1}}, "", world, {true, 3, IBind::LEFT});
    spawnLittleSquareButton({{2.00, 14.00, -2}, rot, {1, 1, 1}}, "", world, {true, 3, IBind::DOWN});
    spawnLittleSquareButton({{1.00, 14.00, -2}, rot, {1, 1, 1}}, "", world, {true, 3, IBind::UP});
    spawnButton({{0, 13.25, -2}, rot, {1, 1, 1}}, "Lets go!", {GREEN, BLUE}, startFunction, world);
    spawnButton({{0, 12.50, -2}, rot, {1, 1, 1}}, "Back", {WHITE, GRAY}, downFunction, world);
    spawnButton({{4, 12.675, -2}, rot, {1, 1, 1}}, "Suppr. save", {ORANGE, RED}, deleteGameSave, world);
}

void bomberman::MainMenuScene::generateConnectMenu(ecs::World &world)
{
    Quaternion rot = QuaternionIdentity();

    spawnTitleButton({{15, 2.75, -2}, rot, {1, 1, 1}}, "Connect menu", world);
    spawnButton({{15, 2.00, -2}, rot, {1, 1, 1}}, "Solo", {WHITE, GRAY}, incNbPlayerConnectFunction, world);
    spawnStaticButton({{12, 1.25, -2}, rot, {1, 1, 1}}, "IP/PORT:", world);
    spawnTextInput({{12, 0.50, -2}, rot, {1, 1, 1}}, "0.0.0.0 0", {WHITE, BLUE}, world, checkIp);
    spawnLaunchButton({{18, 1.25, -2}, rot, {1, 1, 1}}, "", world, {false, 0}, swapProfile);
    spawnLittleSquareButton({{20.00, 0.50, -2}, rot, {1, 1, 1}}, "", world, {false, 0, IBind::PLACE});
    spawnLittleSquareButton({{19.00, 0.50, -2}, rot, {1, 1, 1}}, "", world, {false, 0, IBind::RIGHT});
    spawnLittleSquareButton({{18.00, 0.50, -2}, rot, {1, 1, 1}}, "", world, {false, 0, IBind::LEFT});
    spawnLittleSquareButton({{17.00, 0.50, -2}, rot, {1, 1, 1}}, "", world, {false, 0, IBind::DOWN});
    spawnLittleSquareButton({{16.00, 0.50, -2}, rot, {1, 1, 1}}, "", world, {false, 0, IBind::UP});
    spawnLaunchButton({{12, -0.25, -2}, rot, {1, 1, 1}}, "", world, {false, 1}, swapProfile);
    spawnLittleSquareButton({{10.00, -1.00, -2}, rot, {1, 1, 1}}, "", world, {false, 1, IBind::UP});
    spawnLittleSquareButton({{11.00, -1.00, -2}, rot, {1, 1, 1}}, "", world, {false, 1, IBind::DOWN});
    spawnLittleSquareButton({{12.00, -1.00, -2}, rot, {1, 1, 1}}, "", world, {false, 1, IBind::LEFT});
    spawnLittleSquareButton({{13.00, -1.00, -2}, rot, {1, 1, 1}}, "", world, {false, 1, IBind::RIGHT});
    spawnLittleSquareButton({{14.00, -1.00, -2}, rot, {1, 1, 1}}, "", world, {false, 1, IBind::PLACE});
    spawnLaunchButton({{18, -0.25, -2}, rot, {1, 1, 1}}, "", world, {false, 2}, swapProfile);
    spawnLittleSquareButton({{20.00, -1.00, -2}, rot, {1, 1, 1}}, "", world, {false, 2, IBind::PLACE});
    spawnLittleSquareButton({{19.00, -1.00, -2}, rot, {1, 1, 1}}, "", world, {false, 2, IBind::RIGHT});
    spawnLittleSquareButton({{18.00, -1.00, -2}, rot, {1, 1, 1}}, "", world, {false, 2, IBind::LEFT});
    spawnLittleSquareButton({{17.00, -1.00, -2}, rot, {1, 1, 1}}, "", world, {false, 2, IBind::DOWN});
    spawnLittleSquareButton({{16.00, -1.00, -2}, rot, {1, 1, 1}}, "", world, {false, 2, IBind::UP});
    spawnButton({{15, -1.75, -2}, rot, {1, 1, 1}}, "Lets go!", {GREEN, BLUE}, connectFunction, world);
    spawnButton({{15, -2.50, -2}, rot, {1, 1, 1}}, "Back", {WHITE, GRAY}, rightFunction, world);
}

void bomberman::MainMenuScene::generateMainMenu(ecs::World &world)
{
    Quaternion rot = QuaternionIdentity();
    auto &man = world.getRessource<raylib::SoundManager>();
    auto &music = man.getSound("main_menu_music");

    music.playSound();

    world.spawn().insert(Transform {{0, 2.25, -2}, QuaternionIdentity(), {1, 1, 1}},
    ecs::ModelRef{"logo"}, ecs::SceneMoveElement{MOVE_SPEED});

    spawnButton({{0,  1.25, -2}, rot, {1, 1, 1}}, "Start", {WHITE, GREEN}, startMenu, world);
    spawnButton({{0,  0.50, -2}, rot, {1, 1, 1}}, "Connect", {WHITE, GREEN}, connectMenu, world);
    spawnButton({{0, -1.00, -2}, rot, {1, 1, 1}}, "Settings", {WHITE, GRAY}, rightFunction, world);
    spawnButton({{0, -2.50, -2}, rot, {1, 1, 1}}, "Quit", {WHITE, RED}, quitFunction, world);
}

void bomberman::MainMenuScene::generateAudioSettingsMenu(ecs::World &world)
{
    Quaternion rot = QuaternionIdentity();
    float y = 2.75;

    spawnTitleButton({{-30, y, -2}, rot, {1, 1, 1}}, "Settings Menu", world);
    spawnToggleButton({{-30, y - 1, -2}, rot, {1, 1, 1}}, "Music is on", {BLUE, BLUE}, toggleFunction, world, ecs::ToggleButton::MUSIC);
    spawnToggleButton({{-30, y - 2, -2}, rot, {1, 1, 1}}, "Sound is on", {BLUE, BLUE}, toggleFunction, world, ecs::ToggleButton::SOUND);
    spawnSquareButton({{-32.5, y - 3, -2}, rot, {1, 1, 1}}, "-", {WHITE, GRAY}, musicDown, world);
    spawnProgressButton({{-30, y - 3, -2}, rot, {1, 1, 1}}, ("Music Vol" ), {BLUE, BLUE}, world, true);
    spawnSquareButton({{-27.5, y - 3, -2}, rot, {1, 1, 1}}, "+", {WHITE, GRAY}, musicUp, world);
    spawnSquareButton({{-32.5, y - 4, -2}, rot, {1, 1, 1}}, "-", {WHITE, GRAY}, soundDown, world);
    spawnProgressButton({{-30, y - 4, -2}, rot, {1, 1, 1}}, ("Sound Vol"), {BLUE, BLUE}, world, false);
    spawnSquareButton({{-27.5, y - 4, -2}, rot, {1, 1, 1}}, "+", {WHITE, GRAY}, soundUp, world);
    spawnButton({{-30, y - 5, -2}, rot, {1, 1, 1}}, "Back", {WHITE, GRAY}, leftFunction, world);
}

void bomberman::MainMenuScene::generateGamepadPart(ecs::World &world)
{
    Quaternion rot = QuaternionIdentity();

    spawnStaticButton({{-28, -12.25, -2}, rot, {1, 1, 1}}, "Up", world);
    spawnStaticButton({{-28, -13.25, -2}, rot, {1, 1, 1}}, "Left", world);
    spawnStaticButton({{-28, -14.25, -2}, rot, {1, 1, 1}}, "Right", world);
    spawnStaticButton({{-28, -15.25, -2}, rot, {1, 1, 1}}, "Down", world);
    spawnStaticButton({{-28, -16.25, -2}, rot, {1, 1, 1}}, "Place bomb", world);
    spawnSquareButton({{-25.5, -12.25, -2}, rot, {1, 1, 1}}, " ", {WHITE, GRAY}, toggleKeyRecordFunction, world, {true, IBind::UP});
    spawnSquareButton({{-25.5, -13.25, -2}, rot, {1, 1, 1}}, " ", {WHITE, GRAY}, toggleKeyRecordFunction, world, {true, IBind::LEFT});
    spawnSquareButton({{-25.5, -14.25, -2}, rot, {1, 1, 1}}, " ", {WHITE, GRAY}, toggleKeyRecordFunction, world, {true, IBind::RIGHT});
    spawnSquareButton({{-25.5, -15.25, -2}, rot, {1, 1, 1}}, " ", {WHITE, GRAY}, toggleKeyRecordFunction, world, {true, IBind::DOWN});
    spawnSquareButton({{-25.5, -16.25, -2}, rot, {1, 1, 1}}, " ", {WHITE, GRAY}, toggleKeyRecordFunction, world, {true, IBind::PLACE});
    spawnStaticButton({{-33, -12.75, -2}, rot, {1, 1, 1}}, "Load from:", world);
    spawnTextInputSettingsButton({{-33.5, -13.75, -2}, rot, {1, 1, 1}}, "", {WHITE, BLUE}, world, {true, false});
    spawnSquareButton({{-31, -13.75, -2}, rot, {1, 1, 1}}, "OK", {WHITE, GRAY}, toggleLoadGamepad, world);
    spawnStaticButton({{-33, -14.75, -2}, rot, {1, 1, 1}}, "Save to:", world);
    spawnTextInputSettingsButton({{-33.5, -15.75, -2}, rot, {1, 1, 1}}, "", {WHITE, BLUE}, world, {true, true});
    spawnSquareButton({{-31, -15.75, -2}, rot, {1, 1, 1}}, "OK", {WHITE, GRAY}, toggleSaveGamepad, world);
    spawnButton({{-30, -17.25, -2}, rot, {1, 1, 1}}, "Back", {WHITE, GRAY}, leftFunction, world);
}

void bomberman::MainMenuScene::generateKeyboardPart(ecs::World &world)
{
    Quaternion rot = QuaternionIdentity();
    int i = 0;

    spawnStaticButton({{-2, -12.25, -2}, rot, {1, 1, 1}}, "Up", world);
    spawnStaticButton({{-2, -13.25, -2}, rot, {1, 1, 1}}, "Left", world);
    spawnStaticButton({{-2, -14.25, -2}, rot, {1, 1, 1}}, "Right", world);
    spawnStaticButton({{-2, -15.25, -2}, rot, {1, 1, 1}}, "Down", world);
    spawnStaticButton({{-2, -16.25, -2}, rot, {1, 1, 1}}, "Place bomb", world);
    spawnSquareButton({{-4.5, -12.25, -2}, rot, {1, 1, 1}}, " ", {WHITE, GRAY}, toggleKeyRecordFunction, world, {false, IBind::UP});
    spawnSquareButton({{-4.5, -13.25, -2}, rot, {1, 1, 1}}, " ", {WHITE, GRAY}, toggleKeyRecordFunction, world, {false, IBind::LEFT});
    spawnSquareButton({{-4.5, -14.25, -2}, rot, {1, 1, 1}}, " ", {WHITE, GRAY}, toggleKeyRecordFunction, world, {false, IBind::RIGHT});
    spawnSquareButton({{-4.5, -15.25, -2}, rot, {1, 1, 1}}, " ", {WHITE, GRAY}, toggleKeyRecordFunction, world, {false, IBind::DOWN});
    spawnSquareButton({{-4.5, -16.25, -2}, rot, {1, 1, 1}}, " ", {WHITE, GRAY}, toggleKeyRecordFunction, world, {false, IBind::PLACE});
    spawnStaticButton({{3, -12.75, -2}, rot, {1, 1, 1}}, "Load from:", world);
    spawnTextInputSettingsButton({{3.5, -13.75, -2}, rot, {1, 1, 1}}, "", {WHITE, BLUE}, world, {false, false});
    spawnSquareButton({{1, -13.75, -2}, rot, {1, 1, 1}}, "OK", {WHITE, GRAY}, toggleLoadKeyboard, world);
    spawnStaticButton({{3, -14.75, -2}, rot, {1, 1, 1}}, "Save to:", world);
    spawnTextInputSettingsButton({{3.5, -15.75, -2}, rot, {1, 1, 1}}, "", {WHITE, BLUE}, world, {false, true});
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
    ecs::Hoverable {}, hoverTint, ecs::HoverRotate {}, ecs::Timer {}, ecs::Clickable {doOnClick},
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
    ecs::Hoverable {}, hoverTint, ecs::HoverRotate {}, ecs::Timer {}, ecs::Clickable {doOnClick},
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
    ecs::Hoverable {}, hoverTint, ecs::HoverRotate {}, ecs::Timer {}, ecs::Clickable {doOnClick},
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
const ecs::HoverTint &hoverTint, ecs::World &world, bool isMusic)
{
    const float BUTTON_SIZE = 3;

    world.spawn().insert(transform,
    ecs::Text3D {text, BLACK, {0, 0, 0.06}, 12}, ecs::FontRef {"emulogic"},
    ecs::ModelRef {"progress_button"}, hoverTint.base,
    ecs::Hitbox{{-BUTTON_SIZE / 2, -0.4, -0.05}, {BUTTON_SIZE / 2, 0.4, 0.05}},
    ecs::Hoverable {}, hoverTint, ecs::HoverRotate {}, ecs::Timer {},
    ecs::SceneMoveElement {MOVE_SPEED},
    ecs::ShaderValueSetter{setProgressShaderValue}, ecs::IsMusic {isMusic});
}

void bomberman::MainMenuScene::spawnTextInputSettingsButton(const Transform &transform, const std::string &text,
const ecs::HoverTint &hoverTint, ecs::World &world, const ecs::TextInputSettings &set)
{
    const float BUTTON_SIZE = 3;

    world.spawn().insert(transform,
    ecs::Text3D {text, BLACK, {0, 0, 0.06}, 12}, ecs::FontRef {"emulogic"},
    ecs::ModelRef {"button"}, hoverTint.base,
    ecs::Hitbox{{-BUTTON_SIZE / 2, -0.4, -0.05}, {BUTTON_SIZE / 2, 0.4, 0.05}},
    ecs::Hoverable {}, hoverTint,
    ecs::SceneMoveElement {MOVE_SPEED}, set);
}

void bomberman::MainMenuScene::spawnTextInput(const Transform &transform, const std::string &text,
const ecs::HoverTint &hoverTint, ecs::World &world, ClickCallbackFct doOnClick)
{
    const float BUTTON_SIZE = 5;

    world.spawn().insert(transform,
    ecs::Text3D {text, BLACK, {0, 0, 0.06}, 12}, ecs::FontRef {"emulogic"},
    ecs::ModelRef {"large_button"}, hoverTint.base,
    ecs::Hitbox{{-BUTTON_SIZE / 2, -0.4, -0.05}, {BUTTON_SIZE / 2, 0.4, 0.05}},
    ecs::Hoverable {}, hoverTint,
    ecs::SceneMoveElement {MOVE_SPEED}, ecs::TextInput {}, ecs::Clickable {doOnClick});
}

void bomberman::MainMenuScene::spawnTextInputPort(const Transform &transform, const std::string &text, const ecs::HoverTint &hoverTint, ecs::World &world)
{
    const float BUTTON_SIZE = 5;

    world.spawn().insert(transform,
    ecs::Text3D {text, BLACK, {0, 0, 0.06}, 12}, ecs::FontRef {"emulogic"},
    ecs::ModelRef {"button"}, hoverTint.base,
    ecs::Hitbox{{-BUTTON_SIZE / 2, -0.4, -0.05}, {BUTTON_SIZE / 2, 0.4, 0.05}},
    ecs::Hoverable {}, hoverTint,
    ecs::SceneMoveElement {MOVE_SPEED}, ecs::TextInputPort {});
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
const ecs::HoverTint &hoverTint, ClickCallbackFct doOnClick, ecs::World &world, const ecs::SingleKeyRecorder &recorder)
{
    const float BUTTON_SIZE = 3;

    world.spawn().insert(transform,
    ecs::Text3D {text, BLACK, {0, 0, 0.06}, 12}, ecs::FontRef {"emulogic"},
    ecs::ModelRef {"square_button"}, hoverTint.base,
    ecs::Hitbox{{-BUTTON_SIZE / 2, -0.4, -0.05}, {BUTTON_SIZE / 2, 0.4, 0.05}},
    ecs::Hoverable {}, hoverTint, ecs::Clickable {doOnClick},
    ecs::SceneMoveElement {MOVE_SPEED}, recorder);
}

void bomberman::MainMenuScene::spawnLaunchButton(const Transform &transform, const std::string &text,
ecs::World &world, const ecs::LaunchButton &but, ClickCallbackFct doOnClick)
{
    const float BUTTON_SIZE = 3;

    world.spawn().insert(transform,
    ecs::Text3D {text, BLACK, {0, 0, 0.06}, 12}, ecs::FontRef {"emulogic"},
    ecs::ModelRef {"button"}, WHITE, ecs::Hitbox{{-BUTTON_SIZE / 2, -0.4, -0.05}, {BUTTON_SIZE / 2, 0.4, 0.05}},
    ecs::SceneMoveElement {MOVE_SPEED}, but, ecs::Disappear {}, ecs::Clickable{doOnClick}, ecs::HoverTint { WHITE, GRAY });
}

void bomberman::MainMenuScene::spawnLittleSquareButton(const Transform &transform, const std::string &text,
ecs::World &world, const ecs::LaunchButton &but)
{
    const float BUTTON_SIZE = 1;

    world.spawn().insert(transform,
    ecs::Text3D {text, BLACK, {0, 0, 0.06}, 12}, ecs::FontRef {"emulogic"},
    ecs::ModelRef {"square_button"}, WHITE, but, ecs::Disappear {},
    ecs::SceneMoveElement {MOVE_SPEED});
}
