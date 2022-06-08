/*
** EPITECH PROJECT, 2022
** epi-cs
** File description:
** Movement
*/

#pragma once

#include "raylib/Vectors.hpp"

#include "ecs/engine/World.hpp"
#include "ecs/engine/System.hpp"

struct Movement {
    Vector3 dir;
    float speed;
};

class MoveSystem : public ecs::ASystem {

};
