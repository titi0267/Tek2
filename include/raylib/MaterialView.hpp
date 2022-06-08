/*
** EPITECH PROJECT, 2022
** epi-cs
** File description:
** MaterialView
*/

#pragma once

#include "headers/raylib.h"
#include "Texture.hpp"

namespace raylib {
    using RaylibMaterial = ::Material;

    class MaterialView {
        RaylibMaterial &_mat;

        public:
        MaterialView(RaylibMaterial &mat) : _mat(mat) {};

        void setTexture(int mapType, Texture &texture)
        {
            _mat = LoadMaterialDefault();
            SetMaterialTexture(&_mat, mapType, texture.getTexture());
        }
    };
}
