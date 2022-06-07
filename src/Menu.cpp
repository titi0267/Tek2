/*
** EPITECH PROJECT, 2022
** indieStudio
** File description:
** Menu
*/

#include <iostream>
#include <fstream>
#include <sstream>

#include "ecs/engine/EntityCommands.hpp"

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
#include "../include/Menu.hpp"

bomberman::Menu::Menu()
{
}

bomberman::Menu::~Menu()
{
}

void bomberman::Menu::setTextureToModel(ecs::World &world, const std::string &texturePath, const std::string &modelPath)
{
    raylib::TextureManager &textureMan = world.getRessource<raylib::TextureManager>();
    raylib::ModelManager &modelMan = world.getRessource<raylib::ModelManager>();

    raylib::Model &buttonModel = modelMan.loadModel(modelPath);
    raylib::Texture &buttonText = textureMan.loadTexture(texturePath);
    buttonModel.getMaterialView(0).setTexture(MATERIAL_MAP_DIFFUSE, buttonText);
}

void testClick(ecs::World &world, ecs::Entity entity)
{
    world.getComponent<ecs::Tint>(entity) = RED;
}

void quitFunction(ecs::World &world, ecs::Entity entity)
{
    world.getComponent<ecs::Tint>(entity) = RED;
    world.getRessource<raylib::Window>().toggleClose();
}

ecs::EntityCommands bomberman::Menu::spawnButton(ecs::World &world, Transform transform, std::string text, float buttonSize, ecs::HoverTint hoverTint, ClickCallbackFct doOnClick)
{
    raylib::Font &font = world.getRessource<raylib::FontManager>().loadFont("./assets/fonts/emulogic.ttf");
    raylib::Model &model = world.getRessource<raylib::ModelManager>().loadModel("./assets/mesh/button.iqm");

    return world.spawn().insert(transform,
    ecs::Text3D {text, BLACK, {0, 0, 0.06}, 12}, ecs::FontRef {&font},
    ecs::DrawableCube {{0, 0, -0.05}, {buttonSize, 0.8, 0.1}}, ecs::ModelRef {&model}, WHITE,
    ecs::Hitbox{{-buttonSize / 2, -0.4, -0.05}, {buttonSize / 2, 0.4, 0.05}},
    ecs::Hoverable {}, hoverTint, ecs::HoverRotate {}, ecs::Clickable {doOnClick});
}

void bomberman::Menu::mainScene(ecs::World &world)
{
    spawnButton(world, {{0, 2.75, -2}, QuaternionFromEuler(0, 0, 0), {1, 1, 1}}, "Start", 3, {WHITE, GREEN}, testClick);
    spawnButton(world, {{0, 1.75, -2}, QuaternionFromEuler(0, 0, 0), {1, 1, 1}}, "Tutorial", 3, {WHITE, GRAY}, testClick);
    spawnButton(world, {{0, 0.75, -2}, QuaternionFromEuler(0, 0, 0), {1, 1, 1}}, "Settings", 3, {WHITE, GRAY}, testClick);
    spawnButton(world, {{0, -0.75, -2}, QuaternionFromEuler(0, 0, 0), {1, 1, 1}}, "Quit", 3, {WHITE, RED}, quitFunction);
}