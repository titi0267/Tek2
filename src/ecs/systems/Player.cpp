/*
** EPITECH PROJECT, 2022
** indieStudio
** File description:
** Player
*/

#include "ecs/components/Player.hpp"
#include "ecs/engine/Component.hpp"
#include "ecs/engine/System.hpp"
#include "ecs/components/Timer.hpp"
#include "ecs/components/SpawnBonus.hpp"
#include "scenes/GameServerScene.hpp"
#include "ecs/components/Movement.hpp"
#include "ecs/engine/Clock.hpp"

void ecs::PlayerUpdateSystem::setSignature(ecs::ComponentManager &component)
{
    _signature = component.generateSignature<Player, Transform, GridPosition>();
}

void ecs::PlayerUpdateSystem::update(ecs::World &world)
{
    ecs::SceneManager &man = world.getRessource<ecs::SceneManager>();
    bomberman::GameServerScene &scene = dynamic_cast<bomberman::GameServerScene&>(man.getScene());
    ecs::Clock &clock = world.getRessource<ecs::Clock>();
    static float timeElapsedBoots = 0;
    static float timeElapsedExplode = 0;
    static float timeElapsedStun = 0;

    for (ecs::Entity entity : _entities) {
        Player &player = world.getComponent<Player>(entity);
        Transform &transform = world.getComponent<Transform>(entity);

        if (player.bootsBonus == true) {
           timeElapsedBoots += clock.getDeltaSec();
           scene.setSpeedBonus(2);
            if (timeElapsedBoots > 4) {
                player.bootsBonus = false;
                timeElapsedBoots = 0;
                scene.setSpeedBonus(0);
            }
        }
        if (player.explodeBonus == true) {
            timeElapsedExplode += clock.getDeltaSec();
            scene.setExplodeBonus(1);
            if (timeElapsedExplode > 4) {
                timeElapsedExplode = 0;
                player.explodeBonus = false;
                scene.setExplodeBonus(0);
            }
        }
        if (player.bombBonus == true) {

        }
        if (player.isStun == true) {
            timeElapsedStun += clock.getDeltaSec();
            if (timeElapsedStun > 10)
                player.isStun = false;
        }
    }
}

void ecs::PlayerCollisionUpdateSystem::setSignature(ecs::ComponentManager &component)
{
    _signature = component.generateSignature<GridPosition, Player>();
}

void ecs::PlayerCollisionUpdateSystem::update(ecs::World &world)
{
    ecs::SceneManager &man = world.getRessource<ecs::SceneManager>();
    bomberman::GameServerScene &scene = dynamic_cast<bomberman::GameServerScene&>(man.getScene());
    map::Map &map = scene.getMap();

    const std::set<Entity> &players = scene.getPlayers();
    std::vector<std::tuple<Entity, Player&, GridPosition&>> playersAlive;
    std::vector<std::tuple<Entity, Player&, GridPosition&>> playersAliveCpy;
    const std::set<ecs::Entity> &playersCpy = scene.getPlayers();

    for (Entity pEntity : players) {
        Player &player = world.getComponent<Player>(pEntity);

        if (player.alive) {
            GridPosition &gPos = world.getComponent<GridPosition>(pEntity);
            GridPosition &gPosCpy = world.getComponent<GridPosition>(pEntity);
            playersAlive.push_back({pEntity, player, gPos});
            playersAliveCpy.push_back({pEntity, player, gPosCpy});
        }
    }
    for (ecs::Entity entity : _entities) {
        ecs::GridPosition &pos = world.getComponent<ecs::GridPosition>(entity);

        for (auto [pEntity, player, gPos] : playersAlive) {
            for (auto [playersCpy, playerCpy, gPosCpy] : playersAlive) {
                if (gPos == gPosCpy && player.id != playerCpy.id) {
                    if (player.tigBonus == true) {
                        playerCpy.isStun = true;
                        player.tigBonus = false;
                    }
                    if (playerCpy.tigBonus == true) {
                        player.isStun = true;
                        playerCpy.tigBonus = false;
                    }
                }
            }
        }
    }
}