/*
** EPITECH PROJECT, 2022
** B-YEP-400-STG-4-1-indiestudio-mathieu.brujan
** File description:
** GameScene
*/

#include "scenes/GameScene.hpp"

void bomberman::GameScene::loadScene(ecs::World &world)
{

}

void bomberman::GameScene::unloadScene(ecs::World &world)
{
    world.killAllEntities();
}
