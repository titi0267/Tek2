/*
** EPITECH PROJECT, 2022
** epi-cs
** File description:
** ColorTexture
*/

#pragma once

#include "raylib/headers/raylib.h"
#include "raylib/Texture.hpp"

namespace ecs {
    using Tint = ::Color;

    struct TextureRef {
        raylib::Texture *texture;

        TextureRef(raylib::Texture *texture = nullptr) : texture(texture) {};
    };
}
