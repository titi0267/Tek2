/*
** EPITECH PROJECT, 2022
** epi-cs
** File description:
** Matrix
*/

#pragma once

#include "headers/raylib.h"
#include "headers/raymath.h"

namespace raylib {
    using RaylibMatrix = ::Matrix;

    class Matrix {
        RaylibMatrix _mat;

        public:
        Matrix() : _mat(MatrixIdentity()) {};
        Matrix(const RaylibMatrix &mat) : _mat(mat) {};

        static Matrix fromTransform(Transform &transform)
        {
            return fromScale(transform.scale) *
            fromQuaternion(transform.rotation) *
            fromTranslate(transform.translation);
        }

        static Matrix fromTranslate(Vector3 &translate)
        {
            return Matrix(MatrixTranslate(translate.x, translate.y, translate.z));
        }

        static Matrix fromQuaternion(Quaternion &quat)
        {
            return Matrix(QuaternionToMatrix(quat));
        }

        static Matrix fromScale(Vector3 &scale)
        {
            return Matrix(MatrixScale(scale.x, scale.y, scale.z));
        }

        Matrix &operator=(const Matrix &other)
        {
            _mat = other._mat;
            return *this;
        }

        Matrix &operator*(const Matrix &other)
        {
            _mat = MatrixMultiply(_mat, other._mat);
            return *this;
        }

        Matrix &operator*=(const Matrix &other)
        {
            _mat = (*this * other)._mat;
            return *this;
        }

        Matrix inverse()
        {
            return MatrixInvert(_mat);
        }

        const RaylibMatrix &getMatrix() const
        {
            return _mat;
        }

        float16 getValues() const
        {
            return MatrixToFloatV(_mat);
        }
    };
}
