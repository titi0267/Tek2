/*
** EPITECH PROJECT, 2022
** indie
** File description:
** AiFunc
*/

#pragma once

#include "ecs/components/Ai.hpp"
#include "Map.hpp"

namespace ai {
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
        AiFunc() = delete;
        static ecs::Actions update(ecs::PlayerId aiId, bomberman::GameServerScene &scene, ecs::World &world);

        static std::deque<BombStruct> setBomb(const std::set<ecs::Entity> &list, ecs::World &world);
        static std::deque<PlayerStruct> setPlayer(const std::unordered_map<ecs::PlayerId, ecs::Entity> &list, ecs::World &world);
        static std::deque<ItemStruct> setItem(const std::set<ecs::Entity> &list, ecs::World &world);

        static void defineDangerous(map::Map &map, std::deque<BombStruct> &bomb);
        static void defineBomb(int x, int y, map::Map &map, int bomb_length);
        static void defineNext(std::deque<ecs::GridPosition> &actual, std::deque<ecs::GridPosition> &next, std::vector<int> &map, int width);

        static ecs::Actions goSafe(map::Map &map, std::deque<BombStruct> &bomb, std::deque<PlayerStruct> &player, std::deque<ItemStruct> &item, ecs::GridPosition pos);
        static ecs::Actions goItem(map::Map &map, std::deque<BombStruct> &bomb, std::deque<PlayerStruct> &player, std::deque<ItemStruct> &item, ecs::GridPosition pos);
        static ecs::Actions goKill(map::Map &map, std::deque<BombStruct> &bomb, std::deque<PlayerStruct> &player, std::deque<ItemStruct> &item, ecs::GridPosition pos);
        static ecs::Actions goReach(map::Map &map, std::deque<BombStruct> &bomb, std::deque<PlayerStruct> &player, std::deque<ItemStruct> &item, ecs::GridPosition pos);

        static std::deque<ecs::Actions> PathFinding(map::Map &map, ecs::GridPosition in, ecs::GridPosition out);
    };
}