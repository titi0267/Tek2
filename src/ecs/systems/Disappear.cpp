/*
** EPITECH PROJECT, 2022
** bomberman
** File description:
** Disappear
*/

#include "ecs/engine/LaunchManager.hpp"
#include "ecs/components/Disappear.hpp"
#include "ecs/components/ColorTexture.hpp"
#include "ecs/components/Text3D.hpp"
#include <iostream>

void ecs::DisappearSystem::setSignature(ecs::ComponentManager &component)
{
    _signature = component.generateSignature<Disappear, ecs::Tint, Text3D>();
}

void ecs::DisappearSystem::update(ecs::World &world)
{
    LaunchManager &launch = world.getRessource<LaunchManager>();
    for (Entity entity : _entities) {
        Disappear &disap = world.getComponent<Disappear>(entity);
        Tint &tint = world.getComponent<Tint>(entity);
        Text3D &text = world.getComponent<Text3D>(entity);

        if (disap.disap) {
            tint.a = 255;
            text.color.a = 255;
        }
        else {
            tint.a = 0;
            text.color.a = 0;
        }
    }

}