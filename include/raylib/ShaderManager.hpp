/*
** EPITECH PROJECT, 2022
** B-YEP-400-STG-4-1-indiestudio-mathieu.brujan
** File description:
** ShaderManager
*/

#pragma once

#include <stdexcept>
#include <unordered_map>
#include "Shader.hpp"

namespace raylib {
    class ShaderManager {
        std::unordered_map<std::string, Shader> _shaders;

        public:
        void loadShader(const std::string &id, const std::string &vs, const std::string &fs)
        {
            if (_shaders.find(id) != _shaders.end())
                throw std::runtime_error("Shader ID alredy used");
            _shaders.insert({id, Shader(vs, fs)});
        }

        Shader &getShader(const std::string &id)
        {
            return _shaders.at(id);
        }
    };
}
