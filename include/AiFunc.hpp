/*
** EPITECH PROJECT, 2022
** indie
** File description:
** AiFunc
*/

#pragma once

#include "ecs/components/Ai.hpp"
#include "ecs/components/GridPosition.hpp"
#include "Map.hpp"

namespace ai {
    typedef struct Bomb {
        ecs::GridPosition pos;
        float time;
        int size;
    } BombStruct;

    typedef struct Player {
        ecs::PlayerId id;
        ecs::GridPosition pos;
    } PlayerStruct;

    typedef struct Item {
        ecs::GridPosition pos;
    } ItemStruct;

    typedef struct Water {
        ecs::GridPosition pos;
    } WaterStruct;

    class AiFunc {
        public:
        AiFunc() = delete;
        static ecs::Actions update(ecs::PlayerId aiId, bomberman::GameServerScene &scene, ecs::World &world);

        static std::deque<ecs::Actions> isAroundSafe(map::Map &map, ecs::GridPosition pos);

        static std::deque<BombStruct> setBomb(const std::set<ecs::Entity> &list, ecs::World &world);
        static std::deque<PlayerStruct> setPlayer(const std::unordered_map<ecs::PlayerId, ecs::Entity> &list, ecs::World &world);
        static std::deque<ItemStruct> setItem(const std::set<ecs::Entity> &list, ecs::World &world);
        static std::deque<WaterStruct> setWater(const std::set<ecs::Entity> &list, ecs::World &world);
        static void defineDangerous(map::Map &map, std::deque<BombStruct> &bomb);
        static void defineBomb(int x, int y, map::Map &map, int bomb_length);
        static void defineWater(map::Map &map, std::deque<WaterStruct> water);

        static ecs::Actions goSafe(ecs::PlayerId aiId, map::Map &map, std::deque<BombStruct> &bomb, std::deque<PlayerStruct> &player, std::deque<ItemStruct> &item, ecs::GridPosition pos);
        static ecs::Actions goItem(ecs::PlayerId aiId, map::Map &map, std::deque<BombStruct> &bomb, std::deque<PlayerStruct> &player, std::deque<ItemStruct> &item, ecs::GridPosition pos);
        static ecs::Actions goKill(ecs::PlayerId aiId, map::Map &map, std::deque<BombStruct> &bomb, std::deque<PlayerStruct> &player, std::deque<ItemStruct> &item, ecs::GridPosition pos);
        static ecs::Actions goReach(ecs::PlayerId aiId, map::Map &map, std::deque<BombStruct> &bomb, std::deque<PlayerStruct> &player, std::deque<ItemStruct> &item, ecs::GridPosition pos);

        static ecs::Actions PathFinding(map::Map &map, ecs::GridPosition in, ecs::GridPosition out);
        static ecs::Actions getClosestSafe(map::Map &map, ecs::GridPosition in);

        static void propagateDistField(std::deque<ecs::GridPosition> &actual, std::deque<ecs::GridPosition> &next, map::Map &map, std::vector<int> &distField, int distance);
        static ecs::GridPosition getPreviousCell(ecs::GridPosition pos, std::vector<int> &distField, map::Map &map);
    };
}