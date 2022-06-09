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
        Shader &loadShader(const std::string &id, const std::string &vs, const std::string &fs)
        {
            if (_shaders.find(id) != _shaders.end())
                throw std::runtime_error("Shader " + id + " alredy used");
            _shaders.insert({id, Shader(vs, fs)});
            return _shaders.at(id);
        }

        Shader &getShader(const std::string &id)
        {
            if (_shaders.find(id) == _shaders.end())
                throw std::runtime_error("Shader " + id + " does not exists");
            return _shaders.at(id);
        }
    };
}
