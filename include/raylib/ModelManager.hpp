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
        Model &loadModel(const std::string &id, const std::string &path)
        {
            if (_models.find(id) != _models.end())
                throw std::runtime_error("Model ID already used");
            _models.insert({id, Model(path)});
            return _models.at(id);
        }

        Model &getModel(const std::string &id)
        {
            return _models.at(id);
        }
    };
}
