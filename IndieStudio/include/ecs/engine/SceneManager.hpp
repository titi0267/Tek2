/*
** EPITECH PROJECT, 2022
** B-YEP-400-STG-4-1-indiestudio-mathieu.brujan
** File description:
** SceneManager
*/

#pragma once

#include <memory>
#include <functional>
#include <unordered_map>
#include "ecs/engine/World.hpp"

namespace ecs {
    enum Scenes {
        INTRO_SCENE,
        MAIN_MENU_SCENE,
        GAME_SCENE,
        SERVER_GAME_SCENE,
        SERVER_LOBBY_SCENE,
        SERVER_WIN_SCENE,
    };

    class IScene {
        public:
        virtual void loadScene(ecs::World &world) = 0;
        virtual void unloadScene(ecs::World &world) = 0;
        virtual void entityKilled(ecs::Entity entity, ecs::World &world) = 0;
    };

    extern std::unordered_map<Scenes, std::function<std::unique_ptr<IScene>(const void*)>> SCENES_LIST;

    class SceneManager {
        std::unique_ptr<IScene> _actualScene;
        Scenes _actualSceneType;

        bool _changeRequested = false;
        Scenes _nextScene;
        std::shared_ptr<void> _nextSceneData = nullptr;

        public:
        void loadDefaultScene(ecs::World &world);
        void loadServerScene(ecs::World &world);
        void changeScene(Scenes scene, const std::shared_ptr<void> &data);
        void executeSceneChange(ecs::World &world);

        IScene &getScene() { return *_actualScene; };
        Scenes getSceneType() { return _actualSceneType; };
    };
}
