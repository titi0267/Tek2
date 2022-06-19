/*
** EPITECH PROJECT, 2022
** B-YEP-400-STG-4-1-indiestudio-mathieu.brujan
** File description:
** SceneList
*/

#include "ecs/engine/SceneManager.hpp"
#include "scenes/MainMenuScene.hpp"
#include "scenes/GameScene.hpp"
#include "scenes/GameServerScene.hpp"
#include "scenes/WinServerScene.hpp"
#include "scenes/LobbyServerScene.hpp"
#include "scenes/IntroScene.hpp"

std::unordered_map<ecs::Scenes, std::function<std::unique_ptr<ecs::IScene>(const void*)>> ecs::SCENES_LIST = {
    {ecs::Scenes::MAIN_MENU_SCENE, [](const void *data){ return std::make_unique<bomberman::MainMenuScene>(data); }},
    {ecs::Scenes::GAME_SCENE, [](const void *data){ return std::make_unique<bomberman::GameScene>(data); }},
    {ecs::Scenes::SERVER_GAME_SCENE, [](const void *data){ return std::make_unique<bomberman::GameServerScene>(data); }},
    {ecs::Scenes::SERVER_LOBBY_SCENE, [](const void *data){ return std::make_unique<bomberman::LobbyServerScene>(data); }},
    {ecs::Scenes::SERVER_WIN_SCENE, [](const void *data){ return std::make_unique<bomberman::WinServerScene>(data); }},
    {ecs::Scenes::INTRO_SCENE, [](const void *data){ return std::make_unique<bomberman::IntroScene>(data); }},
};
