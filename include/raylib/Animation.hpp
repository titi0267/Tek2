/*
** EPITECH PROJECT, 2022
** epi-cs
** File description:
** Animation
*/

#pragma once

#include <string>
#include "Model.hpp"
#include "headers/raylib.h"

namespace raylib {
    using RaylibAnimation = ::ModelAnimation;

    class Animation {
        RaylibAnimation _anim;

        public:
        Animation(RaylibAnimation &&animation) : _anim(animation) {};
        ~Animation() { UnloadModelAnimation(_anim); };
        Animation(Animation &anim) = delete;
        Animation(Animation &&anim) : _anim(anim._anim) { anim._anim = { 0 }; };

        void update(Model &model, int frame) { UpdateModelAnimation(model.getModel(), _anim, frame); };

        unsigned int getFramesCount() { return _anim.frameCount; };
        unsigned int getBonesCount() { return _anim.boneCount; };
        bool isValid(Model &model) { return IsModelAnimationValid(model.getModel(), _anim); }

        RaylibAnimation &getAnimation() { return _anim; };
    };
}
