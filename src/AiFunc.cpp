/*
** EPITECH PROJECT, 2022
** indie
** File description:
** AiFunc
*/

#include <algorithm>
#include "AiFunc.hpp"

ecs::Actions ai::AiFunc::update(ecs::PlayerId aiId, bomberman::GameServerScene &scene, ecs::World &world)
{
    std::vector<ecs::Actions (*)(ecs::PlayerId, map::Map&, std::deque<BombStruct>&, std::deque<PlayerStruct>&, std::deque<ItemStruct>&, ecs::GridPosition)>
                            _functions = {goSafe, goItem, goKill, goReach};
    std::deque<BombStruct> bomb =  setBomb(scene.getBombs(), world);
    std::deque<WaterStruct> water = setWater(scene.getWater(), world);
    std::deque<PlayerStruct> player = setPlayer(scene.getPlayers(), world);
    std::deque<ItemStruct> item = setItem(scene.getBonus(), world);
    ecs::GridPosition pos = world.getComponent<ecs::GridPosition>(scene.getPlayers().at(aiId));
    map::Map mapCpy = scene.getMap();
    ecs::Actions act;

    defineWater(mapCpy, water);
    defineDangerous(mapCpy, bomb);
    for (auto fct : _functions) {
        if ((act = fct(aiId, mapCpy, bomb, player, item, pos)) != ecs::Actions::DO_NOTHING)
            return (act);
    }
    return (ecs::Actions::DO_NOTHING);
}

void ai::AiFunc::defineWater(map::Map &map, std::deque<ai::WaterStruct> water)
{
    for (auto actual : water) {
        map.setCellAt(actual.pos.x, actual.pos.y, WALL);
    }
}

std::deque<ai::BombStruct> ai::AiFunc::setBomb(const std::set<ecs::Entity> &list, ecs::World &world)
{
    BombStruct tmp;
    std::deque<BombStruct> bomb;

    for (auto actual : list) {
        tmp.pos = world.getComponent<ecs::GridPosition>(actual);
        tmp.size = world.getComponent<ecs::Bomb>(actual).bombDistance;
        tmp.time = world.getComponent<ecs::Timer>(actual).timeElapsed;
        bomb.push_back(tmp);
    }
    return (bomb);
}

std::deque<ai::WaterStruct> ai::AiFunc::setWater(const std::set<ecs::Entity> &list, ecs::World &world)
{
    WaterStruct tmp;
    std::deque<WaterStruct> water;

    for (auto actual : list) {
        tmp.pos = world.getComponent<ecs::GridPosition>(actual);
        water.push_back(tmp);
    }
    return (water);
}

std::deque<ai::PlayerStruct> ai::AiFunc::setPlayer(const std::unordered_map<ecs::PlayerId, ecs::Entity> &list, ecs::World &world)
{
    PlayerStruct tmp;
    std::deque<PlayerStruct> player;

    for (auto &[id, entity] : list) {
        tmp.id = id;
        tmp.pos = world.getComponent<ecs::GridPosition>(entity);
        player.push_back(tmp);
    }
    return (player);
}

std::deque<ai::ItemStruct> ai::AiFunc::setItem(const std::set<ecs::Entity> &list, ecs::World &world)
{
    ItemStruct tmp;
    std::deque<ItemStruct> item;

    for (auto actual : list) {
        tmp.pos = world.getComponent<ecs::GridPosition>(actual);
        item.push_back(tmp);
    }
    return (item);
}

ecs::Actions ai::AiFunc::goSafe(ecs::PlayerId aiId, map::Map &map, std::deque<BombStruct> &bomb, std::deque<PlayerStruct> &player, std::deque<ItemStruct> &item, ecs::GridPosition pos)
{
    ecs::Actions randoum[4] = {ecs::Actions::MOVE_UP, ecs::Actions::MOVE_RIGHT, ecs::Actions::MOVE_DOWN, ecs::Actions::MOVE_LEFT};

    if (map.getCellAt(pos.x, pos.y) != DANGEROUS)
        return (ecs::Actions::DO_NOTHING);
    else
        return getClosestSafe(map, pos);
}

ecs::Actions ai::AiFunc::goItem(ecs::PlayerId aiId, map::Map &map, std::deque<BombStruct> &bomb, std::deque<PlayerStruct> &player, std::deque<ItemStruct> &item, ecs::GridPosition pos)
{
    ecs::Actions action;

    for (auto &actual : item) {
        if ((action = PathFinding(map, pos, actual.pos)) != ecs::DO_NOTHING)
            return action;
    }
    return (ecs::Actions::DO_NOTHING);
}

ecs::Actions ai::AiFunc::goKill(ecs::PlayerId aiId, map::Map &map, std::deque<BombStruct> &bomb, std::deque<PlayerStruct> &player, std::deque<ItemStruct> &item, ecs::GridPosition pos)
{
    ecs::Actions action;

    for (auto &actual : player) {
        if (actual.id != aiId && (action = PathFinding(map, pos, actual.pos)) != ecs::DO_NOTHING)
            return action;
    }
    return (ecs::Actions::DO_NOTHING);
}

ecs::Actions ai::AiFunc::goReach(ecs::PlayerId aiId, map::Map &map, std::deque<BombStruct> &bomb, std::deque<PlayerStruct> &player, std::deque<ItemStruct> &item, ecs::GridPosition pos)
{
    std::deque<ecs::Actions> randoum;
    ecs::Actions action;

    randoum = isAroundSafe(map, pos);
    if (((map.isValidCell(pos.x - 1, pos.y) && map.getCellAt(pos.x - 1, pos.y) == DESTRUCTIBLE)
    || (map.isValidCell(pos.x + 1, pos.y) && map.getCellAt(pos.x + 1, pos.y) == DESTRUCTIBLE)
    || (map.isValidCell(pos.x, pos.y - 1) && map.getCellAt(pos.x, pos.y - 1) == DESTRUCTIBLE)
    || (map.isValidCell(pos.x, pos.y + 1) && map.getCellAt(pos.x, pos.y + 1) == DESTRUCTIBLE))
    && (!randoum.empty()))
        return (ecs::Actions::PLACE_BOMB);
    randoum.push_back(ecs::Actions::DO_NOTHING);
    return (randoum[std::rand() % randoum.size()]);
}

std::deque<ecs::Actions> ai::AiFunc::isAroundSafe(map::Map &map, ecs::GridPosition pos)
{
    std::deque<ecs::Actions> tmp;
    if (map.isValidCell(pos.x - 1, pos.y) && map.isWalkableCell(pos.x - 1, pos.y) && map.getCellAt(pos.x - 1, pos.y) != DANGEROUS)
        tmp.push_back(ecs::Actions::MOVE_LEFT);
    if (map.isValidCell(pos.x + 1, pos.y) && map.isWalkableCell(pos.x + 1, pos.y) && map.getCellAt(pos.x + 1, pos.y) != DANGEROUS)
        tmp.push_back(ecs::Actions::MOVE_RIGHT);
    if (map.isValidCell(pos.x, pos.y - 1) && map.isWalkableCell(pos.x, pos.y - 1) && map.getCellAt(pos.x, pos.y - 1) != DANGEROUS)
        tmp.push_back(ecs::Actions::MOVE_UP);
    if (map.isValidCell(pos.x, pos.y + 1) && map.isWalkableCell(pos.x, pos.y + 1) && map.getCellAt(pos.x, pos.y + 1) != DANGEROUS)
        tmp.push_back(ecs::Actions::MOVE_DOWN);
    return (tmp);
}

ecs::Actions ai::AiFunc::PathFinding(map::Map &map, ecs::GridPosition in, ecs::GridPosition out)
{
    std::deque<ecs::GridPosition> actual;
    std::deque<ecs::GridPosition> next;
    std::vector<int> distField;
    ecs::GridPosition pos;
    ecs::GridPosition prevPos;
    int distance = 1;
    bool found = false;
    int index;

    distField.resize(map.getWidth() * map.getHeight(), -1);
    next.push_back(in);
    distField.at(in.toArrayIndex(map.getWidth())) = 0;
    do {
        actual = next;
        next.clear();
        propagateDistField(actual, next, map, distField, distance);
        distance++;
    } while (next.size() > 0 && !(found = (std::find(next.begin(), next.end(), out) != next.end())));

    if (!found)
        return ecs::Actions::DO_NOTHING;

    pos = out;
    do {
        prevPos = pos;
        pos = getPreviousCell(prevPos, distField, map);
        distance--;
        if (pos == in) {
            if (in.x < prevPos.x)
                return ecs::MOVE_RIGHT;
            if (in.x > prevPos.x)
                return ecs::MOVE_LEFT;
            if (in.y < prevPos.y)
                return ecs::MOVE_DOWN;
            if (in.y > prevPos.y)
                return ecs::MOVE_UP;
            return ecs::DO_NOTHING;
        }
    } while(distance >= 0);
    return ecs::DO_NOTHING;
}

ecs::Actions ai::AiFunc::getClosestSafe(map::Map &map, ecs::GridPosition in)
{
    std::deque<ecs::GridPosition> actual;
    std::deque<ecs::GridPosition> next;
    std::vector<int> distField;
    ecs::GridPosition pos;
    ecs::GridPosition prevPos;
    int distance = 1;
    bool found = false;
    int index;

    distField.resize(map.getWidth() * map.getHeight(), -1);
    next.push_back(in);
    distField.at(in.toArrayIndex(map.getWidth())) = 0;
    do {
        actual = next;
        next.clear();
        propagateDistField(actual, next, map, distField, distance);
        distance++;
        for (ecs::GridPosition testPos : next) {
            if (map.isWalkableCell(testPos.x, testPos.y) && map.getCellAt(testPos.x, testPos.y) != DANGEROUS) {
                pos = testPos;
                found = true;
                break;
            }
        }
    } while (next.size() > 0 && !found);

    if (!found)
        return ecs::Actions::DO_NOTHING;

    do {
        prevPos = pos;
        pos = getPreviousCell(prevPos, distField, map);
        distance--;
        if (pos == in) {
            if (in.x < prevPos.x)
                return ecs::MOVE_RIGHT;
            if (in.x > prevPos.x)
                return ecs::MOVE_LEFT;
            if (in.y < prevPos.y)
                return ecs::MOVE_DOWN;
            if (in.y > prevPos.y)
                return ecs::MOVE_UP;
            return ecs::DO_NOTHING;
        }
    } while(distance >= 0);
    return ecs::DO_NOTHING;
}

void ai::AiFunc::propagateDistField(std::deque<ecs::GridPosition> &actual, std::deque<ecs::GridPosition> &next, map::Map &map, std::vector<int> &distField, int distance)
{
    const ecs::GridPosition DIRECTIONS[4] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    ecs::GridPosition posNext;
    int width = map.getWidth();
    int index;

    for (ecs::GridPosition &pos : actual) {
        for (int i = 0; i < 4; i++) {
            posNext = pos + DIRECTIONS[i];
            index = posNext.toArrayIndex(map.getWidth());
            if (!map.isValidCell(posNext.x, posNext.y) || distField.at(index) != -1)
                continue;
            if (map.isWalkableCell(posNext.x, posNext.y)) {
                distField.at(index) = distance;
                next.push_back(posNext);
            }
        }
    }
}

ecs::GridPosition ai::AiFunc::getPreviousCell(ecs::GridPosition pos, std::vector<int> &distField, map::Map &map)
{
    const ecs::GridPosition DIRECTIONS[4] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    int width = map.getWidth();
    int distance = distField.at(pos.toArrayIndex(width));
    ecs::GridPosition posNext;
    int val;

    for (int i = 0; i < 4; i++) {
        posNext = pos + DIRECTIONS[i];
        if (!posNext.isValidPos(map))
            continue;
        val = distField.at(posNext.toArrayIndex(width));
        if (val > -1 && val < distance)
            return posNext;
    }
    throw std::runtime_error("Could not find previous cell, this should never happen");
}

void ai::AiFunc::defineDangerous(map::Map &map, std::deque<BombStruct> &bomb)
{
    for (auto actual : bomb)
        defineBomb(actual.pos.x, actual.pos.y, map, actual.size);
}

void ai::AiFunc::defineBomb(int x, int y, map::Map &map, int bomb_length)
{
    int line[4] = {1, 1, 1, 1};

    map.setCellAt(x, y, DANGEROUS);
    for (int i = 1; i < bomb_length; i++) {
        if (line[0] && (x - i) >= 0 && map.isWalkableCell(x - i, y)) {
            map.setCellAt(x - i, y, DANGEROUS);
        } else
            line[0] = 0;

        if (line[1] && (x + i) < map.getWidth() && map.isWalkableCell(x + i, y)) {
            map.setCellAt(x + i, y, DANGEROUS);
        } else
            line[1] = 0;


        if (line[2] && (y - i) >= 0 && map.isWalkableCell(x, y - i)) {
            map.setCellAt(x, y - i, DANGEROUS);
        } else
            line[2] = 0;

        if (line[3] && (y + i) < map.getHeight() && map.isWalkableCell(x, y + i)) {
            map.setCellAt(x, y + i, DANGEROUS);
        } else
            line[3] = 0;
    }
}
