/*
** EPITECH PROJECT, 2022
** epi-cs
** File description:
** Model
*/

#pragma once

#include <string>
#include "headers/raylib.h"
#include "MaterialView.hpp"

namespace raylib {
    using RaylibModel = ::Model;

    class Model {
        RaylibModel _model;

        public:
        Model(const std::string &path) : _model(LoadModel(path.c_str())) {};
        ~Model() { if (_model.boneCount) UnloadModel(_model); };
        Model(Model &model) = delete;
        Model(Model &&model) : _model(model._model) { model._model = { 0 }; };

        void draw(Vector3 position, float scale = 1.0f, Color tint = {255, 255, 255, 255})
        {
            DrawModel(_model, position, scale, tint);
        }

        void drawWires(Vector3 position, float scale = 1.0f, Color tint = {255, 255, 255, 255})
        {
            DrawModelWires(_model, position, scale, tint);
        }

        unsigned int getBonesCount() { return _model.boneCount; };
        unsigned int getMaterialCount() { return _model.materialCount; };

        RaylibModel &getModel() { return _model; };
        MaterialView getMaterialView(int matIndex) { return MaterialView(_model.materials[matIndex]); };
    };
}
