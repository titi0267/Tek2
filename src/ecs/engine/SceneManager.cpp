/*
** EPITECH PROJECT, 2022
** B-YEP-400-STG-4-1-indiestudio-mathieu.brujan
** File description:
** SceneManager
*/

#include "ecs/engine/SceneManager.hpp"
#include "scenes/MainMenuScene.hpp"

void ecs::SceneManager::loadDefaultScene(ecs::World &world)
{
    _actualScene = std::make_unique<bomberman::MainMenuScene>();
    _actualSceneType = MAIN_MENU_SCENE;
    _actualScene->loadScene(world);
}

void ecs::SceneManager::changeScene(ecs::World &world, Scenes scene, const void *data)
{
    _actualScene->unloadScene(world);
    _actualScene = SCENES_LIST[scene](data);
    _actualSceneType = scene;
    _actualScene->loadScene(world);
}
