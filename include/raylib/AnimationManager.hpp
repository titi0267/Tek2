/*
** EPITECH PROJECT, 2022
** epi-cs
** File description:
** AnimationManager
*/

#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include "Animation.hpp"

namespace raylib {
    class AnimationInvalidIndex {};

    class AnimationManager {
        std::unordered_map<std::string, std::vector<Animation>> _animations;

        public:
        void loadAnimations(const std::string &id, const std::string path)
        {
            unsigned int animCount = 0;
            ModelAnimation *anims;

            if (_animations.find(id) != _animations.end())
                throw std::runtime_error("Animation ID already used");
            _animations.insert({id, std::vector<Animation>()});
            anims = LoadModelAnimations(path.c_str(), &animCount);
            for (unsigned int i = 0; i < animCount; i++)
                _animations[id].push_back(Animation(std::move(anims[i])));
            RL_FREE(anims);
        }

        Animation &getAnimation(const std::string &id, int index)
        {
            if (_animations.find(id) == _animations.end())
                throw std::runtime_error("Animation " + id + " does not exists");
            else if (_animations[id].size() < index)
                throw std::runtime_error("Animation " + id + " has not #" + std::to_string(index));
            return _animations[id].at(index);
        }
    };
}
