/*
** EPITECH PROJECT, 2022
** epi-cs
** File description:
** main
*/

#include <iostream>
#include <fstream>
#include <sstream>

#include "ecs/engine/EntityCommands.hpp"
#include "ecs/engine/SceneManager.hpp"
#include "input/BindsManager.hpp"

#include "raylib/Camera.hpp"
#include "raylib/Window.hpp"

#include "raylib/TextureManager.hpp"
#include "raylib/ModelManager.hpp"
#include "raylib/AnimationManager.hpp"
#include "raylib/FontManager.hpp"
#include "raylib/ShaderManager.hpp"
#include "raylib/SoundManager.hpp"

#include "ecs/components/DrawableCube.hpp"
#include "ecs/components/DrawableModel.hpp"
#include "ecs/components/Hitbox.hpp"
#include "ecs/components/Clickable.hpp"
#include "ecs/components/Hoverable.hpp"
#include "ecs/components/HoverTint.hpp"
#include "ecs/components/HoverRotate.hpp"
#include "ecs/components/Text3D.hpp"
#include "ecs/components/ColorTexture.hpp"
#include "ecs/components/SceneMoveElement.hpp"
#include "ecs/components/ResolutionButton.hpp"
#include "ecs/components/FullscreenButton.hpp"
#include "ecs/components/FPSButton.hpp"
#include "ecs/components/ToggleButton.hpp"
#include "ecs/components/KeyRecorder.hpp"
#include "ecs/components/TextInput.hpp"

#include "Map.hpp"

void registerBasicComponents(ecs::World &world)
{
    world.registerComponents<Transform, ecs::Hitbox>();
}

void registerRender(ecs::World &world)
{
    world.registerComponents<ecs::DrawableCube, ecs::Tint, ecs::TextureRef>();
    world.registerSystem<ecs::DrawTextureCubeSystem>();

    world.registerComponent<ecs::ModelRef>();
    world.registerSystem<ecs::DrawableModelSystem>();

    world.registerComponents<ecs::Text3D, ecs::FontRef>();
    world.registerSystem<ecs::Draw3DTextSystem>();
}

void registerMouseInputs(ecs::World &world)
{
    world.registerComponents<ecs::Clickable, ecs::Hoverable, ecs::HoverTint, ecs::HoverRotate, ecs::SceneMoveElement, ecs::ResolutionButton, ecs::FullscreenButton, ecs::FPSButton, ecs::ToggleButton, ecs::SingleKeyRecorder, ecs::TextInput, ecs::TextInputSettings>();
    world.registerSystems<ecs::ClickUpdateSystem, ecs::HoverUpdateSystem, ecs::HoverTintUpdateSystem, ecs::HoverRotateUpdateSystem, ecs::SceneMoveElementSystem, ecs::ResolutionButtonSystem, ecs::FullscreenButtonSystem, ecs::FPSButtonSystem, ecs::ShowFPSButtonSystem, ecs::ToggleMusicButtonSystem, ecs::ToggleSoundButtonSystem, ecs::KeyRecorderSystem, ecs::TextInputSystem, ecs::TextInputSettingsSystem>();
}

int main()
{
    ecs::World world{};

// ---- [COMPONENTS + SYSTEMS] ----

    registerBasicComponents(world);
    registerRender(world);
    registerMouseInputs(world);

// ----- [GLOBAL RESSOURCES] -----

    world.insertRessource<raylib::Window>();
    world.insertRessource<raylib::Camera>(Vector3 {0.0, 0.0, 2.0}, Vector3 {0, 0, 0});
    world.insertRessource<raylib::TextureManager>();
    world.insertRessource<raylib::ModelManager>();
    world.insertRessource<raylib::AnimationManager>();
    world.insertRessource<raylib::FontManager>();
    world.insertRessource<raylib::ShaderManager>();
    world.insertRessource<raylib::SoundManager>();
    world.insertRessource<ecs::SceneManager>();
    world.insertRessource<ecs::BindManager>();

// ----- [INIT RESSOURCES] -----

    raylib::TextureManager &textureMan = world.getRessource<raylib::TextureManager>();
    raylib::ModelManager &modelMan = world.getRessource<raylib::ModelManager>();
    raylib::FontManager &fontMan = world.getRessource<raylib::FontManager>();
    raylib::ShaderManager &shaderMan = world.getRessource<raylib::ShaderManager>();
    raylib::SoundManager &soundMan = world.getRessource<raylib::SoundManager>();

    raylib::Model &bagModel = modelMan.loadModel("bottle", "./assets/models/bottle.iqm");
    raylib::Texture &bagText = textureMan.loadTexture("bottle", "./assets/textures/bottle.png");
    bagModel.getMaterialView(0).setTexture(bagText);

    raylib::Model &tableModel = modelMan.loadModel("table", "./assets/models/table.iqm");
    raylib::Texture &tableText = textureMan.loadTexture("table", "./assets/textures/table.png");
    tableModel.getMaterialView(0).setTexture(tableText);

    raylib::Model &chairModel = modelMan.loadModel("chair", "./assets/models/chair.iqm");
    raylib::Texture &chairText = textureMan.loadTexture("chair", "./assets/textures/chair.png");
    chairModel.getMaterialView(0).setTexture(chairText);

    raylib::Texture &buttonText = textureMan.loadTexture("button", "./assets/textures/button.png");
    raylib::Shader &buttonShader = shaderMan.loadShader("button", "./assets/shaders/button.vs", "./assets/shaders/button.fs");
    raylib::Model &buttonModel = modelMan.loadModel("button", "./assets/models/button.iqm");
    buttonModel.getMaterialView(0)
    .setTexture(buttonText);

    raylib::Texture &largeButtonText = textureMan.loadTexture("large_button", "./assets/textures/large_button.png");
    raylib::Model &largeButtonModel = modelMan.loadModel("large_button", "./assets/models/large_button.iqm");
    largeButtonModel.getMaterialView(0)
    .setTexture(largeButtonText);

    raylib::Texture &squareButtonText = textureMan.loadTexture("square_button", "./assets/textures/square_button.png");
    raylib::Model &squareButtonModel = modelMan.loadModel("square_button", "./assets/models/square_button.iqm");
    squareButtonModel.getMaterialView(0)
    .setTexture(squareButtonText);
    // .setColor(Color {125, 255, 125, 255})
    // .setShader(buttonShader)

    raylib::Sound &mainMenu = soundMan.loadSound("main_menu_music", "./assets/sounds/main_menu.mp3", true);

    textureMan.loadTexture("ground", "./assets/textures/ground.png");
    fontMan.loadFont("emulogic", "./assets/fonts/emulogic.ttf");

// ------ [START + RUN GAME] ------

    world.getRessource<ecs::SceneManager>().loadDefaultScene(world);

    raylib::Window &window = world.getRessource<raylib::Window>();

    window.setTargetFPS(60);
    window.resize({1280, 720});
    while (!window.shouldClose())
        world.update();
}
