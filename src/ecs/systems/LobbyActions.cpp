/*
** EPITECH PROJECT, 2022
** B-YEP-400-STG-4-1-indiestudio-mathieu.brujan
** File description:
** LobbyActions
*/

#include "scenes/LobbyServerScene.hpp"
#include "ecs/components/Player.hpp"

void bomberman::LobbyExecuteActionUpdateSystem::setSignature(ecs::ComponentManager &component)
{
    _signature = component.generateSignature<ecs::Player>();
}

void bomberman::LobbyExecuteActionUpdateSystem::update(ecs::World &world)
{
    ecs::SceneManager &man = world.getRessource<ecs::SceneManager>();
    LobbyServerScene &scene = dynamic_cast<LobbyServerScene&>(man.getScene());
    bool change = false;

    for (ecs::Entity entity : _entities) {
        ecs::Player &player = world.getComponent<ecs::Player>(entity);

        if (scene.getPlayerAction(player.id) == ecs::MOVE_UP) {
            scene.setPlayerReady(player.id);
            change = true;
        }
    }
    if (change)
        scene.checkReady(world);
}
