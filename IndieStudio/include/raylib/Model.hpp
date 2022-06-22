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
#include "Animation.hpp"

namespace raylib {
    using RaylibModel = ::Model;

    class Model {
        RaylibModel _model;

        public:
        Model(const std::string &path) : _model(LoadModel(path.c_str())) {};
        ~Model() { if (_model.boneCount) UnloadModel(_model); };
        Model(Model &model) = delete;
        Model(Model &&model) : _model(model._model) { model._model = { 0 }; };

        void draw(Color tint = {255, 255, 255, 255})
        {
            DrawModel(_model, {0}, {1}, tint);
        }

        void drawWires(Color tint = {255, 255, 255, 255})
        {
            DrawModelWires(_model, {0}, {1}, tint);
        }

        void drawAnimation(Animation &anim, Animation &resetAnim, int frame, Color tint = {255, 255, 255, 255})
        {
            UpdateModelAnimation(_model, anim.getAnimation(), frame);
            draw(tint);
            UpdateModelAnimation(_model, resetAnim.getAnimation(), 0);
        }

        unsigned int getBonesCount() { return _model.boneCount; };
        unsigned int getMaterialCount() { return _model.materialCount; };

        RaylibModel &getModel() { return _model; };
        MaterialView getMaterialView(int matIndex) { return MaterialView(_model.materials[matIndex]); };
    };
}
