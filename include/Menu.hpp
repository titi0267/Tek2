/*
** EPITECH PROJECT, 2022
** indieStudio
** File description:
** Menu
*/

#pragma once
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
#include "ecs/components/Text3D.hpp"
#include "ecs/components/ColorTexture.hpp"

namespace bomberman {
    using ClickCallbackFct = void (*)(ecs::World &world, ecs::Entity entity);
    class Menu {
        public:
            Menu();
            ~Menu();
            void setTextureToModel(ecs::World &world, const std::string &texturePath, const std::string &modelPath);
            void mainScene(ecs::World &world);
            ecs::EntityCommands spawnButton(ecs::World &world, Transform transform, std::string text, float buttonSize, ecs::HoverTint hoverTint, ClickCallbackFct doOnClick);

        protected:
        private:
    };
}
