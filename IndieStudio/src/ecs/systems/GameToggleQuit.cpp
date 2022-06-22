/*
** EPITECH PROJECT, 2022
** B-YEP-400-STG-4-1-indiestudio-mathieu.brujan
** File description:
** GameToggleButton
*/

#include "scenes/GameScene.hpp"
#include "raylib/Window.hpp"

void bomberman::GameToggleQuitButtonSystem::setSignature(ecs::ComponentManager &component)
{
    _signature.set();
}

void bomberman::GameToggleQuitButtonSystem::update(ecs::World &world)
{
    raylib::Window &window = world.getRessource<raylib::Window>();
    ecs::SceneManager &man = world.getRessource<ecs::SceneManager>();
    GameScene &scene = dynamic_cast<GameScene&>(man.getScene());
    bool &toggle = scene.getQuitButtonToggle();

    if (window.isKeyPressed(KEY_ESCAPE)) {
        scene.getMovementRequest() = true;
        if (!toggle) {
            scene.getMoveDest() = {0,  2, 0};
        } else {
            scene.getMoveDest() = {0, -2, 0};
        }
        toggle = !toggle;
    }
}
