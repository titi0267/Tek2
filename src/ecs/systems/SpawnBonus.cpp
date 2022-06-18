/*
** EPITECH PROJECT, 2022
** indieStudio
** File description:
** SpawnBonus
*/

#include "ecs/components/SpawnBonus.hpp"
#include "scenes/GameServerScene.hpp"
#include "ecs/components/Player.hpp"

void ecs::SpawnBonusUpdateSystem::setSignature(ecs::ComponentManager &component)
{
    _signature = component.generateSignature<GridPosition, SpawnBonus>();
}

void ecs::SpawnBonusUpdateSystem::update(ecs::World &world)
{
    ecs::SceneManager &man = world.getRessource<ecs::SceneManager>();
    bomberman::GameServerScene &scene = dynamic_cast<bomberman::GameServerScene&>(man.getScene());
    map::Map &map = scene.getMap();

    const std::set<Entity> &players = scene.getPlayers();
    std::vector<std::tuple<Entity, Player&, GridPosition&>> playersAlive;
    std::vector<ecs::Entity> toDelete;

    for (Entity pEntity : players) {
        Player &player = world.getComponent<Player>(pEntity);

        if (player.alive) {
            GridPosition &gPos = world.getComponent<GridPosition>(pEntity);
            playersAlive.push_back({pEntity, player, gPos});
        }
    }
    for (ecs::Entity entity : _entities) {
        Transform &transform = world.getComponent<Transform>(entity);
        ecs::GridPosition &pos = world.getComponent<ecs::GridPosition>(entity);
        ecs::SpawnBonus &spawnBonus = world.getComponent<ecs::SpawnBonus>(entity);

        for (auto [pEntity, player, gPos] : playersAlive) {
            if (pos == gPos) {
                std::cout << "GET ENTITY" << std::endl;
                switch (spawnBonus.bonus) {
                    case ecs::Bonus::BOMBBONUS:
                        player.bombBonus = true;
                        break;
                    case ecs::Bonus::BOOTS:
                        player.bootsBonus = true;
                        break;
                    case ecs::Bonus::EXPLODE:
                        player.explodeBonus = true;
                        break;
                    case ecs::Bonus::TIG:
                        player.tigBonus = true;
                        break;
                }
                toDelete.push_back(entity);
            }
        }
    }
    for (ecs::Entity entity : toDelete) {
        world.getEntityCommands(entity).despawn();
        scene.deleteBonus(entity);
    }
}
