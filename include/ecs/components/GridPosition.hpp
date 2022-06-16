/*
** EPITECH PROJECT, 2022
** B-YEP-400-STG-4-1-indiestudio-mathieu.brujan
** File description:
** GridPosition
*/

#pragma once

#include <unordered_map>
#include "Map.hpp"

namespace ecs {
    struct GridPosition {
        int x;
        int y;

        GridPosition(int x = 0, int y = 0) : x(x), y(y) {};

        bool operator==(const GridPosition &other) const
        {
            return x == other.x && y == other.y;
        }

        bool isValidPos(const map::Map &map) const
        {
            return x >= 0 && y >= 00 && x < map.getWidth() && y < map.getHeight();
        }
    };

    inline GridPosition operator+(const GridPosition &lhs, const GridPosition &rhs)
    {
        return GridPosition(lhs.x + rhs.x, lhs.y + rhs.y);
    }
};

namespace std {
    template<>
    struct hash<ecs::GridPosition>
    {
        std::size_t operator()(const ecs::GridPosition &pos) const
        {
            return (hash<int>()(pos.x) ^ hash<int>()(pos.y));
        }
    };
}
