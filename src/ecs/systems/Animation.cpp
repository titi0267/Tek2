/*
** EPITECH PROJECT, 2022
** B-YEP-400-STG-4-1-indiestudio-mathieu.brujan
** File description:
** Animation
*/

#include <iostream>
#include <cmath>
#include "ecs/engine/Clock.hpp"
#include "ecs/components/PlayAnimation.hpp"
#include "raylib/AnimationManager.hpp"

void ecs::AnimationUpdateSystem::setSignature(ecs::ComponentManager &component)
{
    _signature = component.generateSignature<PlayAnimation>();
}

void ecs::AnimationUpdateSystem::update(ecs::World &world)
{
    raylib::AnimationManager &man = world.getRessource<raylib::AnimationManager>();
    Clock &clock = world.getRessource<Clock>();

    for (Entity entity : _entities) {
        PlayAnimation &playAnim = world.getComponent<PlayAnimation>(entity);

        if (!playAnim.isPlaying())
            continue;

        raylib::Animation &anim = man.getAnimation(playAnim.animation, playAnim.animIndex);
        float timeBetweenFrames = playAnim.duration / anim.getFramesCount();
        int frame = std::floor(playAnim.timeElapsed / timeBetweenFrames);

        std::cout << "Anim frame: " << frame << std::endl;

        if (frame > anim.getFramesCount()) {
            if (!playAnim.loop) {
                playAnim.stop();
                continue;
            }
            frame %= anim.getFramesCount();
        }
        playAnim.actualFrame = frame;
        playAnim.timeElapsed += clock.getDeltaSec();
    }
}
