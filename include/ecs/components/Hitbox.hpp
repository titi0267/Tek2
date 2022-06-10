/*
** EPITECH PROJECT, 2022
** epi-cs
** File description:
** Hitbox
*/

#pragma once

#include "raylib/headers/raylib.h"
#include "raylib/Matrix.hpp"
#include "raylib/Vectors.hpp"

namespace ecs {
    struct Hitbox {
        Vector3 min;
        Vector3 max;

        Hitbox() : min({ 0 }), max({ 0 }) {};
        Hitbox(Vector3 min, Vector3 max) : min(min), max(max) {};

        BoundingBox getBoundingBox(Transform &transform)
        {
            raylib::Matrix mat =
            raylib::Matrix::fromScale(transform.scale) *
            raylib::Matrix::fromQuaternion(transform.rotation) *
            raylib::Matrix::fromTranslate(transform.translation);

            return BoundingBox { min * mat, max * mat };
        };
    };
}
