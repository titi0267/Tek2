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

        void loadAnimationFile(const std::string path)
        {
            unsigned int animCount = 0;
            ModelAnimation *anims = LoadModelAnimations(path.c_str(), &animCount);

            _animations.insert({path, std::vector<Animation>()});
            for (unsigned int i = 0; i < animCount; i++)
                _animations[path].push_back(Animation(std::move(anims[i])));
            RL_FREE(anims);
        }

        public:
        Animation &loadAnimation(const std::string path, int index)
        {
            if (_animations.find(path) == _animations.end())
                loadAnimationFile(path);
            if (index >= _animations[path].size())
                throw AnimationInvalidIndex();
            return _animations.at(path)[index];
        }
    };
}
