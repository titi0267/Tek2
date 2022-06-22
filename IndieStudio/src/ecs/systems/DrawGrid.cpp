/*
** EPITECH PROJECT, 2022
** B-YEP-400-STG-4-1-indiestudio-mathieu.brujan
** File description:
** DrawGrid
*/

#include "ecs/components/Grid.hpp"
#include "raylib/Matrix.hpp"
#include "raylib/GL.hpp"
#include "raylib/Camera.hpp"

void ecs::drawGrid(Transform &transform, int size, float spacing)
{
    raylib::Matrix mat = raylib::Matrix::fromTransform(transform);
    int halfSize = size / 2;
    float halfSpacing = spacing / 2;
    int start = -halfSize - 1;
    int end = halfSize;

    raylib::RlMatrixPush push;
    raylib::rlMultMatrix(mat);
    raylib::rlBegin(RL_LINES);
    raylib::rlColor3f(0.2, 0.2, 0.2);
    for (int i = start; i <= end; i++) {
        raylib::rlVertex3f(Vector3 {i * spacing + halfSpacing, 0, (float) start * spacing + halfSpacing});
        raylib::rlVertex3f(Vector3 {i * spacing + halfSpacing, 0, (float)  end  * spacing + halfSpacing});

        raylib::rlVertex3f(Vector3 {(float) start * spacing + halfSpacing, 0, i * spacing + halfSpacing});
        raylib::rlVertex3f(Vector3 {(float)  end  * spacing + halfSpacing, 0, i * spacing + halfSpacing});
    }
    raylib::rlEnd();
}

void ecs::DrawGridSystem::setSignature(ecs::ComponentManager &component)
{
    _signature = component.generateSignature<Transform, Grid>();
}

void ecs::DrawGridSystem::update(ecs::World &world)
{
    raylib::Camera &cam = world.getRessource<raylib::Camera>();

    cam.begin3DMode();
    for (ecs::Entity entity : _entities) {
        Transform &transform = world.getComponent<Transform>(entity);
        Grid &grid = world.getComponent<Grid>(entity);

        drawGrid(transform, grid.size, grid.spacing);
    }
    cam.end3DMode();
}
