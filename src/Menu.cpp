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
#include "ecs/components/MenuElement.hpp"
#include "ecs/components/Text3D.hpp"
#include "ecs/components/ColorTexture.hpp"
#include "../include/Menu.hpp"

bomberman::Menu::Menu(ecs::World &world) : _world(world)
{
    actual = ecs::MainMenu;
    change = false;
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

void testClick(ecs::World &world, ecs::Entity entity)
{
    world.getComponent<ecs::Tint>(entity) = RED;
}

void graphicalFunction(ecs::World &world, ecs::Entity entity)
{
    world.getComponent<ecs::Tint>(entity) = RED;
    *(world.getComponent<ecs::MenuElement>(entity).actual) = ecs::Graphical;
    *(world.getComponent<ecs::MenuElement>(entity).change) = true;
}

void optionFunction(ecs::World &world, ecs::Entity entity)
{
    world.getComponent<ecs::Tint>(entity) = RED;
    *(world.getComponent<ecs::MenuElement>(entity).actual) = ecs::Settings;
    *(world.getComponent<ecs::MenuElement>(entity).change) = true;
}

void quitFunction(ecs::World &world, ecs::Entity entity)
{
    world.getComponent<ecs::Tint>(entity) = RED;
    world.getRessource<raylib::Window>().toggleClose();
}

void mainMenuFunction(ecs::World &world, ecs::Entity entity)
{
    world.getComponent<ecs::Tint>(entity) = RED;
    *(world.getComponent<ecs::MenuElement>(entity).actual) = ecs::MainMenu;
    *(world.getComponent<ecs::MenuElement>(entity).change) = true;
}

ecs::EntityCommands bomberman::Menu::spawnMainMenuButton(ecs::MenuMovement pos, std::string text, float buttonSize, ecs::HoverTint hoverTint, ClickCallbackFct doOnClick)
{
    raylib::Font &font = _world.getRessource<raylib::FontManager>().loadFont("./assets/fonts/emulogic.ttf");
    raylib::Model &model = _world.getRessource<raylib::ModelManager>().loadModel("./assets/mesh/button.iqm");
    Transform transform = pos.actual ? pos.active : pos.passive;

    return _world.spawn().insert(transform,
    ecs::Text3D {text, BLACK, {0, 0, 0.06}, 12}, ecs::FontRef {&font},
    ecs::DrawableCube {{0, 0, -0.05}, {buttonSize, 0.8, 0.1}}, ecs::ModelRef {&model}, WHITE,
    ecs::Hitbox{{-buttonSize / 2, -0.4, -0.05}, {buttonSize / 2, 0.4, 0.05}},
    ecs::Hoverable {}, hoverTint, ecs::HoverRotate {}, ecs::Clickable {doOnClick},
    ecs::MenuElement {&actual, ecs::MainMenu, &change, pos});
}

ecs::EntityCommands bomberman::Menu::spawnSettingsButton(ecs::MenuMovement pos, std::string text, float buttonSize, ecs::HoverTint hoverTint, ClickCallbackFct doOnClick)
{
    raylib::Font &font = _world.getRessource<raylib::FontManager>().loadFont("./assets/fonts/emulogic.ttf");
    raylib::Model &model = _world.getRessource<raylib::ModelManager>().loadModel("./assets/mesh/button.iqm");
    Transform transform = pos.actual ? pos.active : pos.passive;

    return _world.spawn().insert(transform,
    ecs::Text3D {text, BLACK, {0, 0, 0.06}, 12}, ecs::FontRef {&font},
    ecs::DrawableCube {{0, 0, -0.05}, {buttonSize, 0.8, 0.1}}, ecs::ModelRef {&model}, WHITE,
    ecs::Hitbox{{-buttonSize / 2, -0.4, -0.05}, {buttonSize / 2, 0.4, 0.05}},
    ecs::Hoverable {}, hoverTint, ecs::HoverRotate {}, ecs::Clickable {doOnClick},
    ecs::MenuElement {&actual, ecs::Settings, &change, pos});
}

void bomberman::Menu::generateMainMenu()
{
    Transform active = {{0, 2.75, -2}, QuaternionFromEuler(0, 0, 0), {1, 1, 1}};
    Transform passive = active;
    passive.translation.x += 10;
    bool actual = true;
    bool right = false;
    float move = 0.1;
    ecs::MenuMovement pos = {active, passive, actual, right, move};

    spawnMainMenuButton(pos, "Start", 3, {WHITE, GREEN}, testClick);
    pos.active.translation.y -= 1;
    pos.passive.translation.y -= 1;
    spawnMainMenuButton(pos, "Tutorial", 3, {WHITE, GRAY}, testClick);
    pos.active.translation.y -= 1;
    pos.passive.translation.y -= 1;
    spawnMainMenuButton(pos, "Settings", 3, {WHITE, GRAY}, optionFunction);
    pos.active.translation.y = -0.75;
    pos.passive.translation.y = -0.75;
    spawnMainMenuButton(pos, "Quit", 3, {WHITE, RED}, quitFunction);
}

void bomberman::Menu::generateSettingsMenu()
{
    Transform active = {{0, 2.75, -2}, QuaternionFromEuler(0, 0, 0), {1, 1, 1}};
    Transform passive = active;
    passive.translation.x -= 10;
    bool actual = false;
    bool right = true;
    float move = 0.1;
    ecs::MenuMovement pos = {active, passive, actual, right, move};

    spawnSettingsButton(pos, "Graphical", 3, {WHITE, GRAY}, quitFunction);
    pos.active.translation.y -= 1;
    pos.passive.translation.y -= 1;
    spawnSettingsButton(pos, "Main Menu", 3, {WHITE, GRAY}, mainMenuFunction);
}

void bomberman::Menu::mainScene()
{
    generateMainMenu();
    generateSettingsMenu();
}