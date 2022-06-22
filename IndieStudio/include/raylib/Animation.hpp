/*
** EPITECH PROJECT, 2022
** epi-cs
** File description:
** Animation
*/

#pragma once

#include <string>
#include "headers/raylib.h"

namespace raylib {
    using RaylibAnimation = ::ModelAnimation;

    class Animation {
        RaylibAnimation _anim;

        public:
        Animation(RaylibAnimation &&animation) : _anim(animation)
        {
            for (int frame = 0; frame < _anim.frameCount; frame++) {
                for (int bone = 0; bone < _anim.boneCount; bone++)
                    _anim.framePoses[frame][bone].scale = {1, 1, 1};
            }
        };
        ~Animation() { UnloadModelAnimation(_anim); };
        Animation(Animation &anim) = delete;
        Animation(Animation &&anim) : _anim(anim._anim) { anim._anim = { 0 }; };

        unsigned int getFramesCount() { return _anim.frameCount; };
        unsigned int getBonesCount() { return _anim.boneCount; };

        RaylibAnimation &getAnimation() { return _anim; };
    };
}
