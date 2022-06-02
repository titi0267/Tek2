/*
** EPITECH PROJECT, 2022
** epi-cs
** File description:
** Camera
*/

#pragma once

#include "Ray.hpp"
#include "Vectors.hpp"

namespace raylib {
    using RaylibCamera = ::Camera3D;

    class Camera {
        RaylibCamera _cam;

        public:
        Camera(Vector3 position = Vector3{0.0f, 0.0f, 0.0f},
                Vector3 target =  Vector3{0.0f, 0.0f, 1.0f})
        {
            _cam.position = position;
            _cam.target = target;
            _cam.up = Vector3{0.0, 1.0, 0.0};
            _cam.projection = CameraProjection::CAMERA_PERSPECTIVE;
            _cam.fovy = 80.0f;
        };
        Camera(Camera &cam) = delete;
        Camera(Camera &&cam) : _cam(cam._cam) { cam._cam = {0}; };

        Vector3 getPosition() { return _cam.position; };
        void setPosition(Vector3 pos) { _cam.position = pos; };
        void move(Vector3 vec) { _cam.position += (_cam.position, vec); }

        Vector3 getTarget() { return _cam.target; };
        void setTarget(Vector3 target) { _cam.target = target; };
        void moveTarget(Vector3 vec) { _cam.target += (_cam.target, vec); }

        void setFOV(float fov) { _cam.fovy = fov; };

        void begin3DMode() { BeginMode3D(_cam); }
        void end3DMode() { EndMode3D(); }

        Ray getMouseRay(Vector2 mousePos) { return Ray(GetMouseRay(mousePos, _cam)); };

        RaylibCamera &getCamera() { return _cam; };
    };
}
