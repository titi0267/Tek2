/*
** EPITECH PROJECT, 2022
** epi-cs
** File description:
** ModelManager
*/

#pragma once

#include <unordered_map>
#include "Model.hpp"

namespace raylib {
    class ModelManager {
        std::unordered_map<std::string, Model> _models;

        public:
        Model &loadModel(std::string path)
        {
            if (_models.find(path) == _models.end())
                _models.insert({path, Model(path)});
            return _models.at(path);
        }
    };
}
