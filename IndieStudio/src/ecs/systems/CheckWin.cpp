/*
** EPITECH PROJECT, 2022
** B-YEP-400-STG-4-1-indiestudio-mathieu.brujan
** File description:
** CheckWin
*/

#include "scenes/GameServerScene.hpp"
#include "scenes/WinServerScene.hpp"
#include "ecs/components/Player.hpp"

void bomberman::GameCheckWinSystem::setSignature(ecs::ComponentManager &component)
{
    _signature = component.generateSignature<ecs::Player>();
}

void bomberman::GameCheckWinSystem::update(ecs::World &world)
{
    ecs::PlayerId winner = -1;
    int aliveCount = 0;

    for (ecs::Entity entity : _entities) {
        ecs::Player &player = world.getComponent<ecs::Player>(entity);

        if (player.alive) {
            winner = player.id;
            aliveCount++;
            if (aliveCount > 1)
                return;
        }
    }

    if (aliveCount == 1) {
        world.getRessource<ecs::SceneManager>().changeScene(ecs::SERVER_WIN_SCENE,
        std::make_shared<bomberman::WinServerSceneArgs>(winner, false));
    } else if (aliveCount == 0) {
        world.getRessource<ecs::SceneManager>().changeScene(ecs::SERVER_WIN_SCENE,
        std::make_shared<bomberman::WinServerSceneArgs>(0, true));
    }
}
