/*
** EPITECH PROJECT, 2022
** B-YEP-400-STG-4-1-indiestudio-mathieu.brujan
** File description:
** GridPosition
*/

#pragma once

namespace ecs {
    struct GridPosition {
        int x;
        int y;

        GridPosition(int x = 0, int y = 0) : x(x), y(y) {};
    };

    inline GridPosition operator+(const GridPosition &lhs, const GridPosition &rhs)
    {
        return GridPosition(lhs.x + rhs.x, lhs.y + rhs.y);
    }
};
