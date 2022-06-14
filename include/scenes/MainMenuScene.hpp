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
#include "ecs/engine/SceneManager.hpp"

#include "raylib/Camera.hpp"
#include "raylib/Window.hpp"

#include "raylib/TextureManager.hpp"
#include "raylib/ModelManager.hpp"
#include "raylib/AnimationManager.hpp"
#include "raylib/FontManager.hpp"

#include "ecs/components/DrawableModel.hpp"
#include "ecs/components/Hitbox.hpp"
#include "ecs/components/Clickable.hpp"
#include "ecs/components/Hoverable.hpp"
#include "ecs/components/HoverTint.hpp"
#include "ecs/components/Text3D.hpp"
#include "ecs/components/ColorTexture.hpp"
#include "ecs/components/SceneMoveElement.hpp"
#include "ecs/components/ResolutionButton.hpp"
#include "ecs/components/FullscreenButton.hpp"
#include "ecs/components/FPSButton.hpp"
#include "ecs/components/ToggleButton.hpp"

namespace bomberman {
    class MainMenuScene : public ecs::IScene, public ecs::MoveRequesterSceneModule {
        using ClickCallbackFct = ecs::ClickCallbackFct;

        bool moveRequest = false;
        Vector3 moveDest = {0};

        public:
        void loadScene(ecs::World &world);
        void unloadScene(ecs::World &world);

        void generateMainMenu(ecs::World &world);
        void generateSettingsMenu(ecs::World &world);
        void generateGraphicalSettingsMenu(ecs::World &world);
        void generateAudioSettingsMenu(ecs::World &world);
        void generateKeybindsSettingsMenu(ecs::World &world);
        void generateGamepadPart(ecs::World &world);
        void generateKeyboardPart(ecs::World &world);

        void spawnButton(const Transform &transform, const std::string &text, const ecs::HoverTint &hoverTint, ClickCallbackFct doOnClick, ecs::World &world);
        void spawnResolutionButton(const Transform &transform, const std::string &text, const ecs::HoverTint &hoverTint, ClickCallbackFct doOnClick, ecs::World &world, const ecs::ResolutionButton &res);
        void spawnFullscreenButton(const Transform &transform, const std::string &text, const ecs::HoverTint &hoverTint, ClickCallbackFct doOnClick, ecs::World &world, const ecs::FullscreenButton &but);
        void spawnFPSButton(const Transform &transform, const std::string &text, const ecs::HoverTint &hoverTint, ClickCallbackFct doOnClick, ecs::World &world, const ecs::FPSButton &but);
        void spawnToggleButton(const Transform &transform, const std::string &text, const ecs::HoverTint &hoverTint, ClickCallbackFct doOnClick, ecs::World &world, ecs::ToggleButton::Usage usage);
        void spawnStaticButton(const Transform &transform, const std::string &text, ecs::World &world);
        void spawnTitleButton(const Transform &transform, const std::string &text, ecs::World &world);
        void spawnSquareButton(const Transform &transform, const std::string &text, const ecs::HoverTint &hoverTint, ClickCallbackFct doOnClick, ecs::World &world);

        bool &getMovementRequest() { return moveRequest; };
        Vector3 &getMoveDest() { return moveDest; };
    };
}
