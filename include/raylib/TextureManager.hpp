/*
** EPITECH PROJECT, 2022
** epi-cs
** File description:
** TextureManager
*/

#pragma once

#include <unordered_map>
#include "Texture.hpp"

namespace raylib {
    class TextureManager {
        std::unordered_map<std::string, Texture> _textures;

        public:
        Texture &loadTexture(const std::string &path)
        {
            if (_textures.find(path) == _textures.end())
                _textures.insert({path, Texture(path)});
            return _textures.at(path);
        }
    };
}
