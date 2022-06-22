/*
** EPITECH PROJECT, 2022
** B-YEP-400-STG-4-1-indiestudio-mathieu.brujan
** File description:
** Light
*/

#include <iostream>
#include "ecs/components/Light.hpp"
#include "raylib/ShaderManager.hpp"
#include "raylib/Camera.hpp"
#include "raylib/headers/rlgl.h"

void ecs::LightUpdateSystem::init(raylib::Shader &shader)
{
    char buf[255];
    GpuLight light;

    std::cout << "[LIGHTS] Init shader locations" << std::endl;
    _ambientLoc = shader.getShaderLocation("ambient");
    _viewPosLoc = shader.getShaderLocation("viewPos");
    for (int i = 0; i < MAX_LIGHTS; i++) {
        std::snprintf(buf, 255, "lights[%i].enabled", i);
        light.enabledLoc = shader.getShaderLocation(buf);

        std::snprintf(buf, 255, "lights[%i].type", i);
        light.typeLoc = shader.getShaderLocation(buf);

        std::snprintf(buf, 255, "lights[%i].pos", i);
        light.posLoc = shader.getShaderLocation(buf);

        std::snprintf(buf, 255, "lights[%i].dir", i);
        light.dirLoc = shader.getShaderLocation(buf);

        std::snprintf(buf, 255, "lights[%i].color", i);
        light.colorLoc = shader.getShaderLocation(buf);

        _lights[i] = light;
    }
    updateAmbient({0.6f, 0.6f, 0.6f, 1.0f}, shader);
    _init = true;
}

void ecs::LightUpdateSystem::updateLight(int i, Vector3 pos, const Light &light, raylib::Shader &shader)
{
    int enableVal = 1;
    Vector3 truePos = pos + light.offset;

    shader.setShaderValue(_lights[i].enabledLoc, &enableVal, SHADER_UNIFORM_INT);
    shader.setShaderValue(_lights[i].typeLoc, &light.type, SHADER_UNIFORM_INT);
    shader.setShaderValue(_lights[i].posLoc, &truePos, SHADER_UNIFORM_VEC3);
    shader.setShaderValue(_lights[i].dirLoc, &light.dir, SHADER_UNIFORM_VEC3);
    shader.setShaderValue(_lights[i].colorLoc, &light.color, SHADER_UNIFORM_VEC4);
}

void ecs::LightUpdateSystem::disableLight(int i, raylib::Shader &shader)
{
    int enableVal = 0;

    shader.setShaderValue(_lights[i].enabledLoc, &enableVal, SHADER_UNIFORM_INT);
}

void ecs::LightUpdateSystem::updateViewPos(Vector3 pos, raylib::Shader &shader)
{
    shader.setShaderValue(_viewPosLoc, &pos, SHADER_UNIFORM_VEC3);
}

void ecs::LightUpdateSystem::updateAmbient(Vector4 color, raylib::Shader &shader)
{
    shader.setShaderValue(_ambientLoc, &color, SHADER_UNIFORM_VEC4);
}

void ecs::LightUpdateSystem::setSignature(ecs::ComponentManager &component)
{
    _signature = component.generateSignature<Transform, Light>();
}

void ecs::LightUpdateSystem::update(ecs::World &world)
{
    raylib::ShaderManager &man = world.getRessource<raylib::ShaderManager>();
    raylib::Camera &cam = world.getRessource<raylib::Camera>();
    raylib::Shader &shader = man.getShader("light");
    int i = 0;

    if (!_init)
        init(shader);
    for (Entity entity : _entities) {
        if (i == MAX_LIGHTS)
            break;
        Transform &transform = world.getComponent<Transform>(entity);
        Light &light = world.getComponent<Light>(entity);
        updateLight(i, transform.translation, light, shader);
        i++;
    }
    for (; i < MAX_LIGHTS; i++)
        disableLight(i, shader);
    updateViewPos(cam.getPosition(), shader);
}
