/*
** EPITECH PROJECT, 2022
** B-YEP-400-STG-4-1-indiestudio-mathieu.brujan
** File description:
** PlayAnimation
*/

#pragma once

#include <string>
#include "ecs/engine/System.hpp"
#include "ecs/engine/World.hpp"

namespace ecs {
    struct PlayAnimation {
        char animation[255];
        int animIndex = 0;
        float duration = 0;
        int frameCounter = 0;
        float timeElapsed = 0;
        int actualFrame = 0;
        bool loop = false;

        PlayAnimation() { animation[0] = 0; };

        void play(const std::string &animation, int animIndex, float duration, bool loop)
        {
            if (this->animation == animation && this->animIndex == animIndex)
                return;
            animation.copy(this->animation, 255);
            this->animation[animation.size()] = 0;
            this->animIndex = animIndex;
            this->duration = duration;
            frameCounter = 0;
            timeElapsed = 0;
            actualFrame = 0;
            this->loop = loop;
        }

        void stop()
        {
            animation[0] = 0;
            animIndex = 0;
            duration = 0;
            frameCounter = 0;
            timeElapsed = 0;
            actualFrame = 0;
            loop = false;
        }

        bool isPlaying()
        {
            return animation[0] != 0;
        }
    };

    class AnimationUpdateSystem : public ASystem {
        public:
        AnimationUpdateSystem() { _stage = Stages::RENDER_UPDATE; };

        void setSignature(ecs::ComponentManager &component);
        void update(ecs::World &world);
    };
};
