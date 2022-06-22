/*
** EPITECH PROJECT, 2022
** ia
** File description:
** IsMusic
*/

#pragma once

namespace ecs {
    struct IsMusic {
        bool volume;

        IsMusic() : volume(false) {};
        IsMusic(bool volume) : volume(volume) {};
    };
}