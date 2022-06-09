/*
** EPITECH PROJECT, 2022
** B-YEP-400-STG-4-1-indiestudio-mathieu.brujan
** File description:
** SceneManager
*/

#pragma once

#include <memory>
#include "ecs/engine/World.hpp"

namespace ecs {
    enum Scenes {
        MAIN_MENU_SCENE,
    };

    class IScene {
        public:
        virtual void loadScene(ecs::World &world) = 0;
        virtual void unloadScene(ecs::World &world) = 0;
    };

    class SceneManager {
        std::unique_ptr<IScene> _actualScene;
        Scenes _actualSceneType;

        public:
        void loadDefaultScene(ecs::World &world);
        void changeScene(ecs::World &world);

        IScene &getScene() { return *_actualScene; };
        Scenes getSceneType() { return _actualSceneType; };
    };
}
