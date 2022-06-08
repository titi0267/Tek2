/*
** EPITECH PROJECT, 2022
** epi-cs
** File description:
** Ray
*/

#pragma once

#include "headers/raylib.h"

namespace raylib {
    using RaylibRay = ::Ray;

    class Ray {
        RaylibRay _ray;

        public:
        Ray(RaylibRay ray) : _ray(ray) {};

        RayCollision getCollisionBox(BoundingBox &box) { return GetRayCollisionBox(_ray, box); };
    };
}
