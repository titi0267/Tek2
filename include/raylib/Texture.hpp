/*
** EPITECH PROJECT, 2022
** epi-cs
** File description:
** Texture
*/

#pragma once

#include <string>
#include <stdexcept>
#include "headers/raylib.h"

namespace raylib {
    using RaylibTexture = ::Texture2D;

    class Texture {
        bool _created;
        RaylibTexture _texture;

        public:
        Texture(const std::string &path) : _created(true), _texture(LoadTexture(path.c_str()))
        {
            if (_texture.width == 0 || _texture.height == 0)
                throw std::runtime_error("Could not load texture " + path);
            SetTextureFilter(_texture, TEXTURE_FILTER_ANISOTROPIC_16X);
            SetTextureWrap(_texture, TEXTURE_WRAP_CLAMP);
        };
        Texture(const RaylibTexture &texture) : _created(false), _texture(texture) {};

        ~Texture() { if (_created) UnloadTexture(_texture); };
        Texture(Texture &texture) = delete;
        Texture(Texture &&texture) : _created(texture._created), _texture(texture._texture) { texture._texture = { 0 }; };

        RaylibTexture &getTexture() { return _texture; };
        int getWidth() { return _texture.width; };
        int getHeight() { return _texture.height; };
    };
}
