/*
** EPITECH PROJECT, 2022
** B-YEP-400-STG-4-1-indiestudio-mathieu.brujan
** File description:
** Shader
*/

#pragma once

#include <string>
#include "headers/raylib.h"

namespace raylib {
    using RaylibShader = ::Shader;
    using ShaderLoc = int;

    class Shader {
        bool _created;
        RaylibShader _shader;

        public:
        Shader(const std::string &vs, const std::string &fs) :
            _created(true), _shader(LoadShader(vs.c_str(), fs.c_str())) {};
        ~Shader() { if (_created) UnloadShader(_shader); };
        Shader(Shader&) = delete;
        Shader(Shader &&other)
            : _created(other._created), _shader(other._shader) { other._created = false; };

        ShaderLoc getShaderLocation(const std::string &uniform) { return GetShaderLocation(_shader, uniform.c_str()); };
        void setShaderValue(ShaderLoc loc, const void *value, int type) { SetShaderValue(_shader, loc, value, type); };

        const RaylibShader &getShader() const { return _shader; };
    };
}
