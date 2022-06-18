/*
** EPITECH PROJECT, 2022
** bomberman
** File description:
** move
*/

#include "ecs/components/SceneMoveElement.hpp"
#include "ecs/engine/World.hpp"
#include "ecs/engine/SceneManager.hpp"
#include "raylib/Vectors.hpp"

void ecs::SceneMoveElementSystem::setSignature(ecs::ComponentManager &component)
{
    _signature = component.generateSignature<Transform, SceneMoveElement>();
}

bool ecs::SceneMoveElementSystem::move(Vector3 &translation, SceneMoveElement &move)
{
    Vector3 moveVec = normalize(move.destination - move.start);
    float actualDistance = distance(translation, move.destination);
    float totalDistance = distance(move.start, move.destination);
    Vector3 movement = moveVec * (std::sin(actualDistance / totalDistance * PI) * move.speed + 0.1);
    float endRange = distance(move.destination, move.destination + movement);

    if (actualDistance <= endRange) {
        translation = move.destination;
        return false;
    }
    translation += movement;
    return true;
}

void ecs::SceneMoveElementSystem::update(ecs::World &world)
{
    ecs::SceneManager &man = world.getRessource<ecs::SceneManager>();
    bool moveExecuted = false;

    try {
        ecs::MoveRequesterSceneModule &scene = dynamic_cast<ecs::MoveRequesterSceneModule&>(man.getScene());

        for (ecs::Entity entity : _entities) {
            Transform &transform = world.getComponent<Transform>(entity);
            SceneMoveElement &move = world.getComponent<SceneMoveElement>(entity);

            if (scene.getMovementRequest() && !move.inMovement) {
                move.start = transform.translation;
                move.destination = transform.translation + scene.getMoveDest();
                move.inMovement = true;
                moveExecuted = true;
            }
            if (move.inMovement)
                move.inMovement = this->move(transform.translation, move);
        }

        if (moveExecuted)
            scene.getMovementRequest() = false;
    } catch(std::bad_cast) {};
}
