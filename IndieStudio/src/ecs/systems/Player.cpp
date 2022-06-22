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
#include "ecs/components/PlayAnimation.hpp"
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

    for (ecs::Entity entity : _entities) {
        Player &player = world.getComponent<Player>(entity);
        Transform &transform = world.getComponent<Transform>(entity);

        if (player.tigDuration > 0) {
            player.tigDuration -= clock.getDeltaSec();
            if (player.tigDuration < 0) {
                player.tigDuration = 0;
                world.getComponent<ecs::PlayAnimation>(entity).play("playerAnims", 0, 1 / player.speed, false, 4);
            }
        }

        if (player.speedDuration > 0) {
            player.speedDuration -= clock.getDeltaSec();
            if (player.speedDuration <= 0)
                player.speed = BASE_SPEED;
            if (player.speedDuration < 0)
                player.speedDuration = 0;
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

    const std::unordered_map<ecs::PlayerId, Entity> &players = scene.getPlayers();
    std::vector<std::tuple<Entity, Player&, GridPosition&>> playersAlive;

    for (auto &[id, pEntity] : players) {
        Player &player = world.getComponent<Player>(pEntity);

        if (player.alive) {
            GridPosition &gPos = world.getComponent<GridPosition>(pEntity);
            GridPosition &gPosCpy = world.getComponent<GridPosition>(pEntity);
            playersAlive.push_back({pEntity, player, gPos});
        }
    }

    for (ecs::Entity entity : _entities) {
        Player &thisPlayer = world.getComponent<Player>(entity);
        ecs::GridPosition &pos = world.getComponent<ecs::GridPosition>(entity);

        if (thisPlayer.alive && thisPlayer.tigs > 0) {
            for (auto &[pEntity, player, pPos] : playersAlive) {
                if (pEntity != entity && pos == pPos && player.tigDuration <= 0) {
                    player.tigDuration = TIG_DURATION;
                    thisPlayer.tigs--;
                    world.getComponent<ecs::PlayAnimation>(pEntity).play("playerAnims", 1, 1 / TIG_DURATION, false, 4);
                    if (thisPlayer.tigs <= 0)
                        break;
                }
            }
        }
    }
}
