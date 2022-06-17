/*
** EPITECH PROJECT, 2022
** epi-cs
** File description:
** GL
*/

#pragma once

#include "raylib/Matrix.hpp"
#include "raylib/Vectors.hpp"

#include "headers/raylib.h"
#include "headers/rlgl.h"

namespace raylib {
    class RlMatrixPush {
        public:
        RlMatrixPush() { rlPushMatrix(); };
        ~RlMatrixPush() { rlPopMatrix(); };
    };

    inline void rlBegin(int mode) { ::rlBegin(mode); };
    inline void rlEnd() { ::rlEnd(); };

    inline void rlMultMatrix(const raylib::Matrix &matrix) { ::rlMultMatrixf(matrix.getValues().v); };
    inline void rlTranslate(const Vector3 &translate) { ::rlTranslatef(translate.x, translate.y, translate.z); };

    inline void rlCheckRenderBatchLimit(int nb) { ::rlCheckRenderBatchLimit(nb); };
    inline void rlSetTexture(int texture) { ::rlSetTexture(texture); };

    inline void rlColor4ub(const Color &color) { ::rlColor4ub(color.r, color.g, color.b, color.a); };

    inline void rlNormal3f(const Vector3 &vec) { ::rlNormal3f(vec.x, vec.y, vec.z); };

    inline void rlTexCoord2f(const Vector2 &uv) { ::rlTexCoord2f(uv.x, uv.y); };
    inline void rlVertex3f(const Vector3 &pos) { ::rlVertex3f(pos.x, pos.y, pos.z); };

    inline void rlColor3f(float r, float g, float b) { ::rlColor3f(r, g, b); };
};
