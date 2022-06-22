/*
** EPITECH PROJECT, 2022
** bomberman
** File description:
** LaunchButton
*/

#include "ecs/components/LaunchButton.hpp"
#include "ecs/components/Disappear.hpp"
#include "ecs/components/Text3D.hpp"
#include "ecs/engine/LaunchManager.hpp"

void ecs::LaunchButtonSystem::setSignature(ecs::ComponentManager &component)
{
    _signature = component.generateSignature<Disappear, LaunchButton, Text3D>();
}

void ecs::LaunchButtonSystem::update(ecs::World &world)
{
    LaunchManager &launch = world.getRessource<LaunchManager>();
    for (Entity entity : _entities) {
        Disappear &disap = world.getComponent<Disappear>(entity);
        LaunchButton &but = world.getComponent<LaunchButton>(entity);
        Text3D &text = world.getComponent<Text3D>(entity);

        if (but.title) {
            text.setText(launch.getName(but.host, but.butNum));
            if (launch.getGamepad(but.host, but.butNum)) {
                Color a = BLUE;
                a.a = text.color.a;
                text.color = a;
            }
            else {
                Color a = GREEN;
                a.a = text.color.a;
                text.color = a;
            }
        }
        else
            text.setText(launch.getKeyText(but.host, but.butNum, but.bind));
        if (launch.getNbPlayers(but.host) > but.butNum)
            disap.disap = true;
        else
            disap.disap = false;
    }
}
