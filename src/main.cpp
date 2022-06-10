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
    world.registerComponents<ecs::Clickable, ecs::Hoverable, ecs::HoverTint, ecs::HoverRotate, ecs::SceneMoveElement, ecs::ResolutionButton, ecs::FullscreenButton, ecs::FPSButton>();
    world.registerSystems<ecs::ClickUpdateSystem, ecs::HoverUpdateSystem, ecs::HoverTintUpdateSystem, ecs::HoverRotateUpdateSystem, ecs::SceneMoveElementSystem, ecs::ResolutionButtonSystem, ecs::FullscreenButtonSystem, ecs::FPSButtonSystem>();
}

void setTextureToModel(const std::string &texturePath, const std::string &modelPath, ecs::World &world)
{
    raylib::TextureManager &textureMan = world.getRessource<raylib::TextureManager>();
    raylib::ModelManager &modelMan = world.getRessource<raylib::ModelManager>();

    raylib::Model &buttonModel = modelMan.loadModel(modelPath);
    raylib::Texture &buttonText = textureMan.loadTexture(texturePath);
    buttonModel.getMaterialView(0).setTexture(MATERIAL_MAP_DIFFUSE, buttonText);
}

int main()
{
    ecs::World world{};

    registerBasicComponents(world);
    registerRender(world);
    registerMouseInputs(world);

// ---------------------------------

    world.insertRessource<raylib::Window>();
    world.insertRessource<raylib::Camera>(Vector3 {0.0, 0.0, 2.0}, Vector3 {0.0, 0.0, -4.0});
    world.insertRessource<raylib::TextureManager>();
    world.insertRessource<raylib::ModelManager>();
    world.insertRessource<raylib::AnimationManager>();
    world.insertRessource<raylib::FontManager>();
    world.insertRessource<ecs::SceneManager>();

// ---------------------------------

    world.getRessource<ecs::SceneManager>().loadDefaultScene(world);

    setTextureToModel("./assets/textures/button_txt.png", "./assets/mesh/button.iqm", world);

// ---------------------------------

    raylib::Window &window = world.getRessource<raylib::Window>();

    window.setTargetFPS(60);
    window.resize({1280, 720});
    while (!window.shouldClose())
        world.update();
}
