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
        Texture &loadTexture(const std::string &id, const std::string &path)
        {
            if (_textures.find(id) != _textures.end())
                throw std::runtime_error("Texture ID already used");
            _textures.insert({id, Texture(path)});
            return _textures.at(id);
        }

        Texture &getTexture(const std::string &id)
        {
            if (_textures.find(id) == _textures.end())
                throw std::runtime_error("Texture " + id + " does not exists");
            return _textures.at(id);
        }
    };
}
