/*
** EPITECH PROJECT, 2022
** indieStudio
** File description:
** BombExplosion
*/

#include "ecs/components/BombExplosion.hpp"
#include "ecs/components/Water.hpp"
#include "scenes/GameServerScene.hpp"

void ecs::BombExplosionUpdateSystem::setSignature(ecs::ComponentManager &component)
{
    _signature = component.generateSignature<BombExplosion, Water>();
}

void ecs::BombExplosionUpdateSystem::update(ecs::World &world)
{
    //ecs::SceneManager &man = world.getRessource<ecs::SceneManager>();
    //bomberman::GameServerScene &scene = dynamic_cast<bomberman::GameServerScene&>(man.getScene());

    for (ecs::Entity entity : _entities) {
        BombExplosion &bombExplosion = world.getComponent<BombExplosion>(entity);
        Water &water = world.getComponent<Water>(entity);

        //scene.deleteBomb(entity);
    }
}