/*
** EPITECH PROJECT, 2022
** epi-cs
** File description:
** DrawModel
*/

#include "ecs/components/DrawableModel.hpp"
#include "ecs/components/ColorTexture.hpp"
#include "ecs/components/PlayAnimation.hpp"

#include "raylib/Camera.hpp"
#include "raylib/Matrix.hpp"
#include "raylib/GL.hpp"
#include "raylib/ModelManager.hpp"
#include "raylib/AnimationManager.hpp"

void ecs::DrawableModelSystem::setSignature(ComponentManager &component)
{
    _signature = component.generateSignature<Transform, ModelRef>();
}

void ecs::DrawableModelSystem::update(ecs::World &world)
{
    raylib::Camera &camera = world.getRessource<raylib::Camera>();
    raylib::ModelManager &modelMan = world.getRessource<raylib::ModelManager>();
    raylib::AnimationManager &animMan = world.getRessource<raylib::AnimationManager>();

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

        if (world.hasComponent<PlayAnimation>(entity)) {
            PlayAnimation &playAnim = world.getComponent<PlayAnimation>(entity);
            if (!playAnim.isPlaying()) {
                modelMan.getModel(modelRef.modelId).draw(tint);
                continue;
            }

            raylib::Animation &anim = animMan.getAnimation(playAnim.animation, playAnim.animIndex);
            modelMan.getModel(modelRef.modelId).drawAnimation(anim, playAnim.actualFrame, tint);
        } else
            modelMan.getModel(modelRef.modelId).draw(tint);
    }
    camera.end3DMode();
}