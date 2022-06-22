/*
** EPITECH PROJECT, 2022
** indieStudio
** File description:
** SpawnBonus
*/

#include "ecs/components/SpawnBonus.hpp"
#include "scenes/GameServerScene.hpp"
#include "ecs/components/Player.hpp"

const std::unordered_map<ecs::Bonus, ecs::BonusApplyEffectFct> ecs::BONUS_FCT =
{
    {ecs::BONUS_BOMB, [](ecs::Player &player){player.maxBombs++; }},
    {ecs::BONUS_BOOTS, [](ecs::Player &player){player.speed = ecs::SPEED_BOOST; player.speedDuration = ecs::SPEED_DURATION; }},
    {ecs::BONUS_RANGE, [](ecs::Player &player){player.bombRange++; }},
    {ecs::BONUS_TIG, [](ecs::Player &player){player.tigs++; }},
};

void ecs::SpawnBonusUpdateSystem::setSignature(ecs::ComponentManager &component)
{
    _signature = component.generateSignature<GridPosition, SpawnBonus>();
}

void ecs::SpawnBonusUpdateSystem::update(ecs::World &world)
{
    ecs::SceneManager &man = world.getRessource<ecs::SceneManager>();
    bomberman::GameServerScene &scene = dynamic_cast<bomberman::GameServerScene&>(man.getScene());
    map::Map &map = scene.getMap();

    const std::unordered_map<PlayerId, Entity> &players = scene.getPlayers();
    std::vector<std::tuple<Entity, Player&, GridPosition&>> playersAlive;
    std::vector<ecs::Entity> toDelete;

    for (auto &[id, pEntity] : players) {
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
                world.getRessource<ecs::ServerManager>().playSound("bonus_sound");
                BONUS_FCT.at(spawnBonus.bonus)(player);
                toDelete.push_back(entity);
                break;
            }
        }
    }

    for (ecs::Entity entity : toDelete) {
        world.getEntityCommands(entity).despawn();
        scene.deleteBonus(entity);
    }
}
