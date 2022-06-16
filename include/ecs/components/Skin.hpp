/*
** EPITECH PROJECT, 2022
** B-YEP-400-STG-4-1-indiestudio-mathieu.brujan
** File description:
** Skin
*/

#pragma once

#include <string>

namespace ecs {
    struct Skin {
        int matId;
        char texture[255];

        Skin(const std::string &text = "", int matId = 0) : matId(matId)
        {
            texture[text.copy(texture, 255)] = 0;
        }
    };
}
