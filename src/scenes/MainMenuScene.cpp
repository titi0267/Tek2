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

    spawnButton({{0, 2.75, -2}, rot, {1, 1, 1}}, "Start", {WHITE, GREEN}, quitFunction, world);
    spawnButton({{0, 1.75, -2}, rot, {1, 1, 1}}, "Tutorial", {WHITE, GRAY}, quitFunction, world);
    spawnButton({{0, 0.75, -2}, rot, {1, 1, 1}}, "Settings", {WHITE, GRAY}, rightFunction, world);
    spawnButton({{0, -0.75, -2}, rot, {1, 1, 1}}, "Quit", {WHITE, RED}, quitFunction, world);
}

void bomberman::MainMenuScene::generateSettingsMenu(ecs::World &world)
{
    Quaternion rot = QuaternionIdentity();

    spawnButton({{-10, 2.75, -2}, rot, {1, 1, 1}}, "Graphical", {WHITE, GRAY}, upFunction, world);
    spawnButton({{-10, 1.75, -2}, rot, {1, 1, 1}}, "Audio", {WHITE, GRAY}, rightFunction, world);
    spawnButton({{-10, 0.75, -2}, rot, {1, 1, 1}}, "Keybinds", {WHITE, GRAY}, downFunction, world);
    spawnButton({{-10, -0.75, -2}, rot, {1, 1, 1}}, "Main Menu", {WHITE, GRAY}, leftFunction, world);
    spawnButton({{-10, 12.75, -2}, rot, {1, 1, 1}}, "Back", {WHITE, GRAY}, downFunction, world);
    spawnButton({{-20, 2.75, -2}, rot, {1, 1, 1}}, "Back", {WHITE, GRAY}, leftFunction, world);
    spawnButton({{-10, -7.25, -2}, rot, {1, 1, 1}}, "Back", {WHITE, GRAY}, upFunction, world);
}

void bomberman::MainMenuScene::spawnButton(const Transform &transform, const std::string &text,
const ecs::HoverTint &hoverTint, ClickCallbackFct doOnClick, ecs::World &world)
{
    const float BUTTON_SIZE = 3;
    raylib::Font &font = world.getRessource<raylib::FontManager>().loadFont("./assets/fonts/emulogic.ttf");
    raylib::Model &model = world.getRessource<raylib::ModelManager>().loadModel("./assets/mesh/button.iqm");

    world.spawn().insert(transform,
    ecs::Text3D {text, BLACK, {0, 0, 0.06}, 12}, ecs::FontRef {&font},
    ecs::ModelRef {&model}, WHITE,
    ecs::Hitbox{{-BUTTON_SIZE / 2, -0.4, -0.05}, {BUTTON_SIZE / 2, 0.4, 0.05}},
    ecs::Hoverable {}, hoverTint, ecs::HoverRotate {}, ecs::Clickable {doOnClick},
    ecs::SceneMoveElement {0.7});
}
