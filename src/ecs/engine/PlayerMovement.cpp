/*
** EPITECH PROJECT, 2022
** indieStudio
** File description:
** PlayerInputAction
*/

#include "ecs/components/PlayerInputAction.hpp"
#include "ecs/components/PlayerDoAction.hpp"

void ecs::PlayerDoActionUpdateSystem::setSignature(ecs::ComponentManager &component)
{
    _signature = component.generateSignature<PlayerDoAction>();
}

void ecs::PlayerInputAction::PlayerSetKeys(int up, int down, int left, int right, int action)
{
    _up = up;
    _down = down;
    _left = left;
    _right = right;
    _action = action;
}

void ecs::PlayerDoActionUpdateSystem::update(ecs::World &world)
{
    for (ecs::Entity entity : _entities) {
        PlayerDoAction &playerDoAction = world.getComponent<PlayerDoAction>(entity);
        PlayerInputAction &playerInputAction = world.getComponent<PlayerInputAction>(entity);

        switch (playerInputAction.getCurrentAction())
        {
        case Direction::UP:
            playerDoAction.goUp();
            break;
        case Direction::DOWN:
            playerDoAction.goDown();
            break;
        case Direction::LEFT:
            playerDoAction.goLeft();
            break;
        case Direction::RIGHT:
            playerDoAction.goRight();
            break;
        case Direction::ACTION:
            playerDoAction.doAction();
            break;
        default:
            break;
        }
    }
}

void ecs::PlayerInputActionUpdateSystem::setSignature(ecs::ComponentManager &component)
{
    _signature = component.generateSignature<PlayerInputAction>();
}

void ecs::PlayerInputActionUpdateSystem::update(ecs::World &world)
{

    for (ecs::Entity entity : _entities) {
        PlayerInputAction &playerInputAction = world.getComponent<PlayerInputAction>(entity);

        if (playerInputAction.getUp() == true) {
            playerInputAction.setCurrentAction(Direction::UP);
        }
        if (playerInputAction.getDown() == true) {
            playerInputAction.setCurrentAction(Direction::DOWN);
        }
        if (playerInputAction.getLeft() == true) {
            playerInputAction.setCurrentAction(Direction::LEFT);
        }
        if (playerInputAction.getRight() == true) {
            playerInputAction.setCurrentAction(Direction::RIGHT);
        }
        if (playerInputAction.getAction() == true) {
            playerInputAction.setCurrentAction(Direction::ACTION);
        }
    }
}