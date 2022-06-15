/*
** EPITECH PROJECT, 2022
** indieStudio
** File description:
** Player
*/

#pragma once

#include "ecs/engine/PlayerId.hpp"

namespace ecs {
    struct Player {
        PlayerId id;

        Player(PlayerId id = -1) : id(id) {};
    };
}
