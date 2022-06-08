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
#include "ecs/components/MoveMenu.hpp"
#include "ecs/components/Text3D.hpp"
#include "ecs/components/ColorTexture.hpp"
#include "../include/Menu.hpp"

bomberman::Menu::Menu(ecs::World &world) : _world(world)
{
}

bomberman::Menu::~Menu()
{
}

void bomberman::Menu::setTextureToModel(const std::string &texturePath, const std::string &modelPath)
{
    raylib::TextureManager &textureMan = _world.getRessource<raylib::TextureManager>();
    raylib::ModelManager &modelMan = _world.getRessource<raylib::ModelManager>();

    raylib::Model &buttonModel = modelMan.loadModel(modelPath);
    raylib::Texture &buttonText = textureMan.loadTexture(texturePath);
    buttonModel.getMaterialView(0).setTexture(MATERIAL_MAP_DIFFUSE, buttonText);
}

void quitFunction(ecs::World &world, ecs::Entity entity)
{
    world.getComponent<ecs::Tint>(entity) = RED;
    world.getRessource<raylib::Window>().toggleClose();
}

void downFunction(ecs::World &world, ecs::Entity entity)
{
    world.getComponent<ecs::Tint>(entity) = RED;
    *(world.getComponent<ecs::MoveMenu>(entity).down) = true;
}

void upFunction(ecs::World &world, ecs::Entity entity)
{
    world.getComponent<ecs::Tint>(entity) = RED;
    *(world.getComponent<ecs::MoveMenu>(entity).up) = true;
}

void rightFunction(ecs::World &world, ecs::Entity entity)
{
    world.getComponent<ecs::Tint>(entity) = RED;
    *(world.getComponent<ecs::MoveMenu>(entity).right) = true;
}

void leftFunction(ecs::World &world, ecs::Entity entity)
{
    world.getComponent<ecs::Tint>(entity) = RED;
    *(world.getComponent<ecs::MoveMenu>(entity).left) = true;
}

ecs::EntityCommands bomberman::Menu::spawnMainMenuButton(Transform transform, std::string text, float buttonSize, ecs::HoverTint hoverTint, ClickCallbackFct doOnClick)
{
    raylib::Font &font = _world.getRessource<raylib::FontManager>().loadFont("./assets/fonts/emulogic.ttf");
    raylib::Model &model = _world.getRessource<raylib::ModelManager>().loadModel("./assets/mesh/button.iqm");

    return _world.spawn().insert(transform,
    ecs::Text3D {text, BLACK, {0, 0, 0.06}, 12}, ecs::FontRef {&font},
    ecs::DrawableCube {{0, 0, -0.05}, {buttonSize, 0.8, 0.1}}, ecs::ModelRef {&model}, WHITE,
    ecs::Hitbox{{-buttonSize / 2, -0.4, -0.05}, {buttonSize / 2, 0.4, 0.05}},
    ecs::Hoverable {}, hoverTint, ecs::HoverRotate {}, ecs::Clickable {doOnClick},
    ecs::MoveMenu {&right, &left, &up, &down, 0.1});
}

ecs::EntityCommands bomberman::Menu::spawnSettingsButton(Transform transform, std::string text, float buttonSize, ecs::HoverTint hoverTint, ClickCallbackFct doOnClick)
{
    raylib::Font &font = _world.getRessource<raylib::FontManager>().loadFont("./assets/fonts/emulogic.ttf");
    raylib::Model &model = _world.getRessource<raylib::ModelManager>().loadModel("./assets/mesh/button.iqm");

    return _world.spawn().insert(transform,
    ecs::Text3D {text, BLACK, {0, 0, 0.06}, 12}, ecs::FontRef {&font},
    ecs::DrawableCube {{0, 0, -0.05}, {buttonSize, 0.8, 0.1}}, ecs::ModelRef {&model}, WHITE,
    ecs::Hitbox{{-buttonSize / 2, -0.4, -0.05}, {buttonSize / 2, 0.4, 0.05}},
    ecs::Hoverable {}, hoverTint, ecs::HoverRotate {}, ecs::Clickable {doOnClick},
    ecs::MoveMenu {&right, &left, &up, &down, 0.1});
}

void bomberman::Menu::generateMainMenu()
{
    spawnMainMenuButton({{0, 2.75, -2}, QuaternionFromEuler(0, 0, 0), {1, 1, 1}}, "Start", 3, {WHITE, GREEN}, quitFunction);
    spawnMainMenuButton({{0, 1.75, -2}, QuaternionFromEuler(0, 0, 0), {1, 1, 1}}, "Tutorial", 3, {WHITE, GRAY}, quitFunction);
    spawnMainMenuButton({{0, 0.75, -2}, QuaternionFromEuler(0, 0, 0), {1, 1, 1}}, "Settings", 3, {WHITE, GRAY}, rightFunction);
    spawnMainMenuButton({{0, -0.75, -2}, QuaternionFromEuler(0, 0, 0), {1, 1, 1}}, "Quit", 3, {WHITE, RED}, quitFunction);
}

void bomberman::Menu::generateSettingsMenu()
{
    spawnSettingsButton({{-10, 2.75, -2}, QuaternionFromEuler(0, 0, 0), {1, 1, 1}}, "Graphical", 3, {WHITE, GRAY}, upFunction);
    spawnSettingsButton({{-10, 1.75, -2}, QuaternionFromEuler(0, 0, 0), {1, 1, 1}}, "Audio", 3, {WHITE, GRAY}, rightFunction);
    spawnSettingsButton({{-10, 0.75, -2}, QuaternionFromEuler(0, 0, 0), {1, 1, 1}}, "Keybinds", 3, {WHITE, GRAY}, downFunction);
    spawnSettingsButton({{-10, -0.75, -2}, QuaternionFromEuler(0, 0, 0), {1, 1, 1}}, "Main Menu", 3, {WHITE, GRAY}, leftFunction);
    spawnSettingsButton({{-10, 12.75, -2}, QuaternionFromEuler(0, 0, 0), {1, 1, 1}}, "Back", 3, {WHITE, GRAY}, downFunction);
    spawnSettingsButton({{-20, 2.75, -2}, QuaternionFromEuler(0, 0, 0), {1, 1, 1}}, "Back", 3, {WHITE, GRAY}, leftFunction);
    spawnSettingsButton({{-10, -7.25, -2}, QuaternionFromEuler(0, 0, 0), {1, 1, 1}}, "Back", 3, {WHITE, GRAY}, upFunction);
}

void bomberman::Menu::mainScene()
{
    generateMainMenu();
    generateSettingsMenu();
}