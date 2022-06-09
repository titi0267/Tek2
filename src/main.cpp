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
    world.insertRessource<raylib::Camera>(Vector3 {0.0, 0.0, 2.0}, Vector3 {0.0, 0.0, -4.0});
    world.insertRessource<raylib::TextureManager>();
    world.insertRessource<raylib::ModelManager>();
    world.insertRessource<raylib::AnimationManager>();
    world.insertRessource<raylib::FontManager>();
    world.insertRessource<raylib::ShaderManager>();
    world.insertRessource<ecs::SceneManager>();

// ----- [INIT RESSOURCES] -----

    raylib::ShaderManager &shaderMan = world.getRessource<raylib::ShaderManager>();
    shaderMan.loadShader("button", "./assets/shaders/button.vs", "./assets/shaders/button.fs");

    raylib::TextureManager &textureMan = world.getRessource<raylib::TextureManager>();
    textureMan.loadTexture("button", "./assets/textures/button_txt.png");

    raylib::ModelManager &modelMan = world.getRessource<raylib::ModelManager>();
    raylib::Model &buttonModel = modelMan.loadModel("button", "./assets/mesh/button.iqm");
    buttonModel.getMaterialView(0)
    .setTexture(textureMan.getTexture("button"))
    .setColor(Color {125, 255, 125, 255})
    .setShader(shaderMan.getShader("button"));

    raylib::FontManager &fontMan = world.getRessource<raylib::FontManager>();
    fontMan.loadFont("emulogic", "./assets/fonts/emulogic.ttf");

// ------ [START + RUN GAME] ------

    world.getRessource<ecs::SceneManager>().loadDefaultScene(world);

    raylib::Window &window = world.getRessource<raylib::Window>();

    window.setTargetFPS(60);
    window.resize({1280, 720});
    while (!window.shouldClose())
        world.update();
}
