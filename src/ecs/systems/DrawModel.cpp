/*
** EPITECH PROJECT, 2022
** epi-cs
** File description:
** DrawModel
*/

#include "ecs/components/DrawableModel.hpp"
#include "ecs/components/ColorTexture.hpp"
#include "ecs/components/PlayAnimation.hpp"
#include "ecs/components/Skin.hpp"
#include "ecs/components/CameraFollow.hpp"

#include "raylib/Camera.hpp"
#include "raylib/Matrix.hpp"
#include "raylib/GL.hpp"
#include "raylib/ModelManager.hpp"
#include "raylib/TextureManager.hpp"
#include "raylib/AnimationManager.hpp"

void ecs::DrawableModelSystem::setSignature(ComponentManager &component)
{
    _signature = component.generateSignature<Transform, ModelRef>();
}

void ecs::DrawableModelSystem::update(ecs::World &world)
{
    raylib::Camera &camera = world.getRessource<raylib::Camera>();
    raylib::ModelManager &modelMan = world.getRessource<raylib::ModelManager>();
    raylib::TextureManager &textMan = world.getRessource<raylib::TextureManager>();
    raylib::AnimationManager &animMan = world.getRessource<raylib::AnimationManager>();
    raylib::Matrix invViewMat = camera.getViewMatrix().inverse();

    camera.begin3DMode();
    for (auto entity : _entities) {
        Transform &transform = world.getComponent<Transform>(entity);
        ModelRef &modelRef = world.getComponent<ModelRef>(entity);
        raylib::Model &model = modelMan.getModel(modelRef.modelId);

        raylib::Matrix mat = raylib::Matrix::fromTransform(transform);
        Tint tint = WHITE;

        if (world.hasComponent<CameraFollow>(entity))
            mat = mat * invViewMat;

        if (world.hasComponent<Tint>(entity))
            tint = world.getComponent<Tint>(entity);

        if (world.hasComponent<Skin>(entity)) {
            Skin &skin = world.getComponent<Skin>(entity);
            model.getMaterialView(skin.matId).setTexture(textMan.getTexture(skin.texture));
        }

        raylib::RlMatrixPush push;
        raylib::rlMultMatrix(mat);

        if (world.hasComponent<PlayAnimation>(entity)) {
            PlayAnimation &playAnim = world.getComponent<PlayAnimation>(entity);
            if (!playAnim.isPlaying()) {
                model.draw(tint);
                continue;
            }

            raylib::Animation &anim = animMan.getAnimation(playAnim.animation, playAnim.animIndex);
            raylib::Animation &resetAnim = animMan.getAnimation(playAnim.animation, playAnim.resetIndex);
            model.drawAnimation(anim, resetAnim, playAnim.actualFrame, tint);
        } else
            model.draw(tint);
    }
    camera.end3DMode();
}
