/*
** EPITECH PROJECT, 2022
** B-YEP-400-STG-4-1-indiestudio-mathieu.brujan
** File description:
** LobbyActions
*/

#include "scenes/LobbyServerScene.hpp"
#include "ecs/engine/SkinManager.hpp"
#include "ecs/components/Player.hpp"
#include "ecs/components/Skin.hpp"

void bomberman::LobbyExecuteActionUpdateSystem::setSignature(ecs::ComponentManager &component)
{
    _signature = component.generateSignature<ecs::Player>();
}

void bomberman::LobbyExecuteActionUpdateSystem::update(ecs::World &world)
{
    ecs::SkinManager &skinMan = world.getRessource<ecs::SkinManager>();
    ecs::SceneManager &man = world.getRessource<ecs::SceneManager>();
    LobbyServerScene &scene = dynamic_cast<LobbyServerScene&>(man.getScene());
    bool change = false;

    for (ecs::Entity entity : _entities) {
        ecs::Player &player = world.getComponent<ecs::Player>(entity);
        ecs::Actions action = scene.getPlayerAction(player.id);

        if (action == ecs::MOVE_LEFT && scene.isActionUpdatedThisFrame(player.id)) {
            skinMan.unassignedSkin(player.id, true);
            skinMan.assignLastSkin(player.id);
            world.getComponent<ecs::Skin>(entity) = ecs::Skin(skinMan.getPlayerSkin(player.id));
        } else if (action == ecs::MOVE_RIGHT && scene.isActionUpdatedThisFrame(player.id)) {
            skinMan.unassignedSkin(player.id, false);
            skinMan.assignFirstSkin(player.id);
            world.getComponent<ecs::Skin>(entity) = ecs::Skin(skinMan.getPlayerSkin(player.id));
        }

        if (action == ecs::MOVE_UP && scene.isActionUpdatedThisFrame(player.id)) {
            scene.setPlayerReady(player.id, world);
            change = true;
        }
    }
    if (change)
        scene.checkReady(world);
}
