/*
** EPITECH PROJECT, 2022
** B-YEP-400-STG-4-1-indiestudio-mathieu.brujan
** File description:
** GameActions
*/

#include "scenes/GameServerScene.hpp"
#include "ecs/components/Player.hpp"
#include "ecs/components/Movement.hpp"
#include "ecs/components/PlayAnimation.hpp"
#include "ecs/engine/Clock.hpp"

void bomberman::GameExecuteActionUpdateSystem::setSignature(ecs::ComponentManager &component)
{
    _signature = component.generateSignature<Transform, ecs::GridPosition, ecs::Player, ecs::Movement, ecs::PlayAnimation>();
}

void bomberman::GameExecuteActionUpdateSystem::placeBomb(ecs::Entity entity, ecs::World &world, bomberman::GameServerScene &scene)
{
    Transform &transform = world.getComponent<Transform>(entity);
    ecs::GridPosition &gPos = world.getComponent<ecs::GridPosition>(entity);
    map::Map &map = scene.getMap();

    if (map.getCellAt(gPos.x, gPos.y) != VOID && map.getCellAt(gPos.x, gPos.y) != SPAWN)
        return;
    scene.spawnBomb(transform.translation, gPos, world);
    map.setCellAt(gPos.x, gPos.y, BOMB);
}

void bomberman::GameExecuteActionUpdateSystem::movePlayer(ecs::Entity entity, ecs::World &world, ecs::Actions action, map::Map &map)
{
    const std::unordered_map<ecs::Actions, Vector3> MOVEMENTS = {
        {ecs::MOVE_UP, {0, 0, -1.2}},
        {ecs::MOVE_DOWN, {0, 0, 1.2}},
        {ecs::MOVE_LEFT, {-1.2, 0, 0}},
        {ecs::MOVE_RIGHT, {1.2, 0, 0}}
    };
    const std::unordered_map<ecs::Actions, float> ROTATIONS = {
        {ecs::MOVE_UP, PI},
        {ecs::MOVE_DOWN, 0},
        {ecs::MOVE_LEFT, 3.0 * PI / 2.0},
        {ecs::MOVE_RIGHT, PI / 2.0},
    };

    ecs::SceneManager &man = world.getRessource<ecs::SceneManager>();
    bomberman::GameServerScene &scene = dynamic_cast<bomberman::GameServerScene&>(man.getScene());

    Transform &transform = world.getComponent<Transform>(entity);
    ecs::GridPosition &gPos = world.getComponent<ecs::GridPosition>(entity);
    ecs::Movement &move = world.getComponent<ecs::Movement>(entity);
    ecs::Player &player = world.getComponent<ecs::Player>(entity);

    Vector3 moveVec =  MOVEMENTS.at(action);
    ecs::GridPosition gDest = gPos + ecs::GridPosition {(int) moveVec.x, (int) moveVec.z};

    if (gDest.x < 0 || gDest.y < 0 || gDest.x > map.getWidth() - 1 || gDest.y > map.getHeight() - 1)
        return;

    if ((map.getCellAt(gDest.x, gDest.y) == VOID || map.getCellAt(gDest.x, gDest.y) == SPAWN) && player.isStun == false) {
        std::cout << "[MOVE] TO " << gDest.x << ", " << gDest.y << " [SPEED] " << 2 + scene.getSpeedBonus() << std::endl;
        gPos = gDest;
        move.move(transform.translation + moveVec, 2 + scene.getSpeedBonus());
        transform.rotation = QuaternionFromEuler(0, ROTATIONS.at(action), 0);
        world.getComponent<ecs::PlayAnimation>(entity).play("playerAnims", 0, 0.5, false);
    } else
        std::cout << "Can't go this way :" << map.getCellAt(gDest.x, gDest.y) << std::endl;
}

void bomberman::GameExecuteActionUpdateSystem::update(ecs::World &world)
{
    ecs::SceneManager &man = world.getRessource<ecs::SceneManager>();
    bomberman::GameServerScene &scene = dynamic_cast<bomberman::GameServerScene&>(man.getScene());
    map::Map &map = scene.getMap();
    ecs::Clock &clock = world.getRessource<ecs::Clock>();

    for (ecs::Entity entity : _entities) {
        ecs::Player &player = world.getComponent<ecs::Player>(entity);
        ecs::Actions action = scene.getPlayerAction(player.id);
        ecs::Movement &move = world.getComponent<ecs::Movement>(entity);

        if (action == ecs::DO_NOTHING || move.isMoving || !player.alive)
            continue;
        if (action == ecs::PLACE_BOMB) {
            if (player.placeBomb == true)
                continue;
            if (player.explodeBonus == true) {
                player.explodePlaced = true;
                std::cout << "BONUS PLACED" << std::endl;
            }
            player.placeBomb = true;
            placeBomb(entity, world, scene);
        } else {
            movePlayer(entity, world, action, map);
        }
    }
}
