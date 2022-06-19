/*
** EPITECH PROJECT, 2022
** ia
** File description:
** PlayMusic
*/

#include "ecs/engine/SceneManager.hpp"
#include "ecs/components/PlayMusic.hpp"
#include "raylib/SoundManager.hpp"

void ecs::PlayMusicSystem::setSignature(ecs::ComponentManager &component)
{
    _signature.set();
}

void ecs::PlayMusicSystem::update(ecs::World &world)
{
    ecs::SceneManager &man = world.getRessource<ecs::SceneManager>();
    raylib::SoundManager &sMan = world.getRessource<raylib::SoundManager>();

    if (man.getSceneType() == ecs::MAIN_MENU_SCENE) {
        if (!sMan.getSound("main_menu_music").isSoundPlaying())
            sMan.getSound("main_menu_music").playSound();
    }
    else if (man.getSceneType() == ecs::GAME_SCENE) {
        if (!sMan.getSound("game_music").isSoundPlaying())
            sMan.getSound("game_music").playSound();
    }
}
