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

#include "raylib/Camera.hpp"
#include "raylib/Window.hpp"

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
#include "ecs/components/Text3D.hpp"
#include "ecs/components/ColorTexture.hpp"
#include "ecs/components/SceneMoveElement.hpp"

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
    world.registerComponents<ecs::Clickable, ecs::Hoverable, ecs::HoverTint, ecs::HoverRotate, ecs::SceneMoveElement>();
    world.registerSystems<ecs::ClickUpdateSystem, ecs::HoverUpdateSystem, ecs::HoverTintUpdateSystem, ecs::HoverRotateUpdateSystem, ecs::SceneMoveElementSystem>();
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
    world.insertRessource<ecs::SceneManager>();

// ----- [INIT RESSOURCES] -----

    raylib::TextureManager &textureMan = world.getRessource<raylib::TextureManager>();
    raylib::ModelManager &modelMan = world.getRessource<raylib::ModelManager>();
    raylib::FontManager &fontMan = world.getRessource<raylib::FontManager>();
    raylib::ShaderManager &shaderMan = world.getRessource<raylib::ShaderManager>();

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
    // .setColor(Color {125, 255, 125, 255})
    // .setShader(buttonShader)

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
