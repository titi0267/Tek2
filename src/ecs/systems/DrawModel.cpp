/*
** EPITECH PROJECT, 2022
** epi-cs
** File description:
** DrawModel
*/

#include "ecs/components/DrawableModel.hpp"
#include "ecs/components/ColorTexture.hpp"

#include "raylib/Camera.hpp"
#include "raylib/Matrix.hpp"
#include "raylib/GL.hpp"

void ecs::DrawableModelSystem::setSignature(ComponentManager &component)
{
    _signature = component.generateSignature<Transform, ModelRef>();
}

void ecs::DrawableModelSystem::update(ecs::World &world)
{
    raylib::Camera &camera = world.getRessource<raylib::Camera>();

    camera.begin3DMode();
    for (auto entity : _entities) {
        Transform &transform = world.getComponent<Transform>(entity);
        ModelRef &modelRef = world.getComponent<ModelRef>(entity);
        raylib::Matrix mat = raylib::Matrix::fromTransform(transform);
        Tint tint = WHITE;

        if (world.hasComponent<Tint>(entity))
            tint = world.getComponent<Tint>(entity);
        raylib::RlMatrixPush push;
        raylib::rlMultMatrix(mat);
        modelRef.model->draw({0}, 1.0f, tint);
    }
    camera.end3DMode();
}