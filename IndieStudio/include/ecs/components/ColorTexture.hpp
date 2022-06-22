/*
** EPITECH PROJECT, 2022
** epi-cs
** File description:
** ColorTexture
*/

#pragma once

#include "raylib/Texture.hpp"

namespace ecs {
    using Tint = ::Color;

    struct TextureRef {
        char textureId[255];

        TextureRef(const std::string &id = "") { id.copy(textureId, 255); textureId[id.size()] = 0;};
    };
}
