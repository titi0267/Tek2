/*
** EPITECH PROJECT, 2022
** indie
** File description:
** AiFunc
*/

#pragma once

#include "ecs/components/Ai.hpp"
#include "Map.hpp"

typedef struct Bomb {
    ecs::GridPosition pos;
    float time;
    int size;
} BombStruct;

typedef struct Player {
    ecs::GridPosition pos;
} PlayerStruct;

typedef struct Item {
    ecs::GridPosition pos;
} ItemStruct;

class AiFunc {
    public:
        AiFunc() {};
        ~AiFunc() {};
        static ecs::Actions update(map::Map &map, bomberman::GameServerScene &scene, ecs::World &world, ecs::GridPosition pos);
        static std::deque<BombStruct> AiFunc::setBomb(std::set<ecs::Entity> list, ecs::World &world);
        static std::deque<PlayerStruct> AiFunc::setPlayer(std::set<ecs::Entity> list, ecs::World &world);
        static std::deque<ItemStruct> AiFunc::setItem(std::set<ecs::Entity> list, ecs::World &world);
        static void defineDangerous(map::Map &map, std::deque<BombStruct> bomb);
        static void defineBomb(int x, int y, map::Map &map, int bomb_length);
        static void defineNext(std::deque<ecs::GridPosition> actual, std::deque<ecs::GridPosition> &next, std::vector<int> &map, int width);
        static ecs::Actions AiFunc::goSafe(map::Map map, std::deque<BombStruct> bomb, std::deque<PlayerStruct> player, std::deque<ItemStruct> item, ecs::GridPosition pos);
        static ecs::Actions AiFunc::goItem(map::Map map, std::deque<BombStruct> bomb, std::deque<PlayerStruct> player, std::deque<ItemStruct> item, ecs::GridPosition pos);
        static ecs::Actions AiFunc::goKill(map::Map map, std::deque<BombStruct> bomb, std::deque<PlayerStruct> player, std::deque<ItemStruct> item, ecs::GridPosition pos);
        static ecs::Actions AiFunc::goReach(map::Map map, std::deque<BombStruct> bomb, std::deque<PlayerStruct> player, std::deque<ItemStruct> item, ecs::GridPosition pos);
        static std::deque<ecs::Actions> AiFunc::PathFinding(map::Map &map, ecs::GridPosition in, ecs::GridPosition out);
    protected:
    private:
};
