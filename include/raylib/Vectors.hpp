/*
** EPITECH PROJECT, 2022
** epi-cs
** File description:
** Vectors
*/

#pragma once

#include "Matrix.hpp"
#include "headers/raymath.h"

inline Vector3 operator+(const Vector3 &lhs, const Vector3 &rhs)
{
    return Vector3Add(lhs, rhs);
}

inline void operator+=(Vector3 &lhs, const Vector3 &rhs)
{
    lhs = lhs + rhs;
}

inline Vector3 operator-(const Vector3 &lhs, const Vector3 &rhs)
{
    return Vector3Subtract(lhs, rhs);
}

inline void operator-=(Vector3 &lhs, const Vector3 &rhs)
{
    lhs = lhs - rhs;
}

inline Vector3 operator*(const Vector3 &lhs, const raylib::Matrix &mat)
{
    return Vector3Transform(lhs, mat.getMatrix());
}
