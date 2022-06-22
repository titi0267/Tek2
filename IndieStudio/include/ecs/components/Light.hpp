/*
** EPITECH PROJECT, 2022
** B-YEP-400-STG-4-1-indiestudio-mathieu.brujan
** File description:
** Light
*/

#pragma once

#include "ecs/engine/System.hpp"
#include "ecs/engine/World.hpp"
#include "raylib/Vectors.hpp"
#include "raylib/Shader.hpp"

#define MAX_LIGHTS 32
#define LIGHT_POINT 0
#define LIGHT_DIRECTIONAL 1

namespace ecs {
    struct Light {
        int type;
        Vector3 offset;
        Vector3 dir;
        Vector4 color;

        Light() : type(0), dir({0}), color({0}) {};
        Light(Vector4 color, Vector3 offset) : type(LIGHT_POINT), offset(offset), dir({0}), color(color) {};
        Light(Vector3 dir, Vector4 color) : type(LIGHT_DIRECTIONAL), offset({0}), dir(dir), color(color) {};
    };

    struct GpuLight {
        int enabledLoc = -1;
        int typeLoc = -1;
        int posLoc = -1;
        int dirLoc = -1;
        int colorLoc = -1;
    };

    class LightUpdateSystem : public ecs::ASystem {
        bool _init = false;
        int _ambientLoc = -1;
        int _viewPosLoc = -1;
        GpuLight _lights[MAX_LIGHTS];

        void init(raylib::Shader &shader);
        void updateLight(int i, Vector3 pos, const Light &light, raylib::Shader &shader);
        void disableLight(int i, raylib::Shader &shader);
        void updateViewPos(Vector3 pos, raylib::Shader &shader);
        void updateAmbient(Vector4 color, raylib::Shader &shader);

        public:
        LightUpdateSystem() { _stage = ecs::RENDER_UPDATE; };

        void setSignature(ecs::ComponentManager &component);
        void update(ecs::World &world);
    };
}
