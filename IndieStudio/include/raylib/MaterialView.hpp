/*
** EPITECH PROJECT, 2022
** epi-cs
** File description:
** MaterialView
*/

#pragma once

#include "headers/raylib.h"
#include "Texture.hpp"
#include "Shader.hpp"

namespace raylib {
    using RaylibMaterial = ::Material;

    class MaterialView {
        RaylibMaterial &_mat;

        public:
        MaterialView(RaylibMaterial &mat) : _mat(mat) {};

        MaterialView &setTexture(Texture &texture)
        {
            _mat.maps[MATERIAL_MAP_DIFFUSE].texture = texture.getTexture();
            return *this;
        }

        MaterialView &setColor(const Color &color)
        {
            _mat.maps[MATERIAL_MAP_DIFFUSE].color = color;
            return *this;
        }

        MaterialView &setShader(const Shader &shader)
        {
            _mat.shader = shader.getShader();
            return *this;
        }
    };
}
