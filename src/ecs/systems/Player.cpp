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
    static float timeElapsed = 0;

    for (ecs::Entity entity : _entities) {
        Player &player = world.getComponent<Player>(entity);
        Transform &transform = world.getComponent<Transform>(entity);

        if (player.bootsBonus == true) {
           timeElapsed += clock.getDeltaSec();
            if (timeElapsed > 4) {
                player.bootsBonus = false;
                timeElapsed = 0;
                player.playerNewSpeed = 0;
            } else
                player.playerNewSpeed = 2;
        }
    }
}