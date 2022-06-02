/*
** EPITECH PROJECT, 2022
** epi-cs
** File description:
** Entity
*/

#pragma once

#include <cstdint>
#include <deque>
#include <map>
#include <bitset>

namespace ecs {
    enum class Entity : std::uint64_t {};
    const std::size_t MAX_ENTITIES = 1000;
}
