/*
** EPITECH PROJECT, 2022
** B-YEP-400-STG-4-1-indiestudio-mathieu.brujan
** File description:
** SceneList
*/

#include "ecs/engine/SceneManager.hpp"
#include "scenes/MainMenuScene.hpp"
#include "scenes/GameScene.hpp"

std::unordered_map<ecs::Scenes, std::function<std::unique_ptr<ecs::IScene>(void)>> ecs::SCENES_LIST = {
    {ecs::Scenes::MAIN_MENU_SCENE, [](){ return std::make_unique<bomberman::MainMenuScene>(); }},
    {ecs::Scenes::GAME_SCENE, [](){ return std::make_unique<bomberman::GameScene>(); }},
};
