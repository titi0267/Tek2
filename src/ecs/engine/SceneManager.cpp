/*
** EPITECH PROJECT, 2022
** B-YEP-400-STG-4-1-indiestudio-mathieu.brujan
** File description:
** SceneManager
*/

#include "ecs/engine/SceneManager.hpp"
#include "scenes/MainMenuScene.hpp"
#include "scenes/LobbyServerScene.hpp"

void ecs::SceneManager::loadDefaultScene(ecs::World &world)
{
    _actualScene = std::make_unique<bomberman::MainMenuScene>();
    _actualSceneType = MAIN_MENU_SCENE;
    _actualScene->loadScene(world);
}

void ecs::SceneManager::loadServerScene(ecs::World &world)
{
    _actualScene = std::make_unique<bomberman::LobbyServerScene>();
    _actualSceneType = SERVER_LOBBY_SCENE;
    _actualScene->loadScene(world);
}

void ecs::SceneManager::changeScene(Scenes scene, const std::shared_ptr<void> &data)
{
    _changeRequested = true;
    _nextScene = scene;
    _nextSceneData = data;
}

void ecs::SceneManager::executeSceneChange(ecs::World &world)
{
    if (_changeRequested) {
        _actualScene->unloadScene(world);
        _actualScene = SCENES_LIST[_nextScene](_nextSceneData.get());
        _actualSceneType = _nextScene;
        _nextSceneData.reset();
        _changeRequested = false;
        _actualScene->loadScene(world);
    }
}
