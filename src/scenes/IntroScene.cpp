/*
** EPITECH PROJECT, 2022
** indieStudio
** File description:
** IntroScene
*/

#include "scenes/IntroScene.hpp"
#include "ecs/engine/Entity.hpp"
#include "ecs/engine/EntityCommands.hpp"
#include "ecs/engine/System.hpp"
#include  "ecs/components/DrawableModel.hpp"
#include "ecs/components/Intro.hpp"
#include "ecs/engine/World.hpp"
#include "ecs/components/Timer.hpp"
#include "ecs/engine/Clock.hpp"
#include "raylib/Window.hpp"
#include "ecs/engine/Ressources.hpp"
#include "ecs/engine/Component.hpp"
#include "raylib/Camera.hpp"
#include "raylib/SoundManager.hpp"
#include "raylib/Sound.hpp"


void ecs::IntroUpdateSystem::setSignature(ecs::ComponentManager &component)
{
    _signature = component.generateSignature<Intro, Timer>();
}

void ecs::IntroUpdateSystem::update(ecs::World &world)
{
    ecs::Clock &clock = world.getRessource<ecs::Clock>();
    for (ecs::Entity entity : _entities) {
        Intro &intro = world.getComponent<Intro>(entity);
        Timer &timer = world.getComponent<Timer>(entity);

        timer.timeElapsed += clock.getDeltaSec();
        if (timer.timeElapsed >= 10) {
            std::cout << "CHANGE SCENE"<< std::endl;
            world.getRessource<ecs::SceneManager>().changeScene(ecs::MAIN_MENU_SCENE, nullptr);
        }
    }
}

void bomberman::IntroScene::loadScene(ecs::World &world)
{
    world.getRessource<raylib::Camera>().setPosition({0, 0, 2});
    world.getRessource<raylib::Camera>().setTarget({0, 0, 0});
    auto &man = world.getRessource<raylib::SoundManager>();
    auto &music = man.getSound("omar_voice");

    music.playSound();
    spawnOmar({0, -1.5, -3}, world);
}

void bomberman::IntroScene::spawnOmar(Vector3 pos, ecs::World &world)
{
    world.registerSystem<ecs::IntroUpdateSystem>();

    Transform transform = {pos, QuaternionIdentity(), {1, 1, 1}};
    ecs::Entity entity = world.spawn().insert(transform, ecs::ModelRef {"omar"}, ecs::Intro {}, ecs::Timer {}).getEntity();

    omar.insert(entity);
}

void bomberman::IntroScene::unloadScene(ecs::World &world)
{
    world.killAllEntities();
    world.unregisterSystem<ecs::IntroUpdateSystem>();
}

void bomberman::IntroScene::entityKilled(ecs::Entity entity, ecs::World &world)
{

}
