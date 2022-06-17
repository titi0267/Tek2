/*
** EPITECH PROJECT, 2022
** indie
** File description:
** AiFunc
*/

#include <algorithm>
#include "AiFunc.hpp"

ecs::Actions AiFunc::update(map::Map &map, bomberman::GameServerScene &scene, ecs::World &world, ecs::GridPosition pos)
{
    std::vector<ecs::Actions (*)(map::Map, std::deque<BombStruct>, std::deque<PlayerStruct>, std::deque<ItemStruct>, ecs::GridPosition)>
                            _functions = {goSafe, goItem, goKill, goReach};
    ecs::Actions act;
    std::deque<BombStruct> bomb =  setBomb(scene.getBombs(), world);
    std::deque<PlayerStruct> player = setPlayer(scene.getPlayers(), world);
    std::deque<ItemStruct> item = setItem(scene.getBonus(), world);

    defineDangerous(map, bomb);
    for (auto fct : _functions) {
        if ((act = fct(map, bomb, player, item, pos)) != ecs::Actions::DO_NOTHING)
            return (act);
    }
    return (ecs::Actions::DO_NOTHING);  
}

std::deque<BombStruct> AiFunc::setBomb(std::set<ecs::Entity> list, ecs::World &world)
{
    BombStruct tmp;
    std::deque<BombStruct> bomb;

    for (auto actual : list) {
        tmp.pos = world.getComponent<ecs::GridPosition>(actual);
        tmp.size = 4;
        tmp.time = world.getComponent<ecs::Timer>(actual).timeElapsed;
        bomb.push_back(tmp);
    }
    return (bomb);
}

std::deque<PlayerStruct> AiFunc::setPlayer(std::set<ecs::Entity> list, ecs::World &world)
{
    PlayerStruct tmp;
    std::deque<PlayerStruct> player;

    for (auto actual : list) {
        tmp.pos = world.getComponent<ecs::GridPosition>(actual);
        player.push_back(tmp);
    }
    return (player);
}

std::deque<ItemStruct> AiFunc::setItem(std::set<ecs::Entity> list, ecs::World &world)
{
    ItemStruct tmp;
    std::deque<ItemStruct> item;

    for (auto actual : list) {
        tmp.pos = world.getComponent<ecs::GridPosition>(actual);
        item.push_back(tmp);
    }
    return (item);
}

ecs::Actions AiFunc::goSafe(map::Map map, std::deque<BombStruct> bomb, std::deque<PlayerStruct> player, std::deque<ItemStruct> item, ecs::GridPosition pos)
{
    ecs::Actions randoum[] = {ecs::Actions::MOVE_UP, ecs::Actions::MOVE_RIGHT, ecs::Actions::MOVE_DOWN, ecs::Actions::MOVE_LEFT};

    if (map.getCellAt(pos.x, pos.y) != DANGEROUS)
        return (ecs::Actions::DO_NOTHING);
    if (map.getCellAt(pos.x - 1, pos.y) == VOID)
        return (ecs::Actions::MOVE_LEFT);
    if (map.getCellAt(pos.x + 1, pos.y) == VOID)
        return (ecs::Actions::MOVE_RIGHT);
    if (map.getCellAt(pos.x, pos.y - 1) == VOID)
        return (ecs::Actions::MOVE_UP);
    if (map.getCellAt(pos.x, pos.y + 1) == VOID)
        return (ecs::Actions::MOVE_DOWN);
    return (randoum[std::rand() % 4]);
}

ecs::Actions AiFunc::goItem(map::Map map, std::deque<BombStruct> bomb, std::deque<PlayerStruct> player, std::deque<ItemStruct> item, ecs::GridPosition pos)
{
    std::deque<ecs::Actions> tmp;
    if (item.empty())
        return (ecs::Actions::DO_NOTHING);
    for (auto actual : item) {
        if ((tmp = PathFinding(map, pos, actual.pos))[0] != ecs::Actions::DO_NOTHING)
            return (tmp[0]);
    }
    return (ecs::Actions::DO_NOTHING);
}

ecs::Actions AiFunc::goKill(map::Map map, std::deque<BombStruct> bomb, std::deque<PlayerStruct> player, std::deque<ItemStruct> item, ecs::GridPosition pos)
{
    std::deque<ecs::Actions> tmp;
    for (auto actual : item) {
        if ((tmp = PathFinding(map, pos, actual.pos)).size() <= 4)
            return(ecs::PLACE_BOMB);
    }
    return (ecs::Actions::DO_NOTHING);
}

ecs::Actions AiFunc::goReach(map::Map map, std::deque<BombStruct> bomb, std::deque<PlayerStruct> player, std::deque<ItemStruct> item, ecs::GridPosition pos)
{
    ecs::Actions randoum[] = {ecs::Actions::MOVE_UP, ecs::Actions::MOVE_RIGHT, ecs::Actions::MOVE_DOWN, ecs::Actions::MOVE_LEFT
    , ecs::Actions::DO_NOTHING};

    std::deque<ecs::Actions> tmp;
    for (auto actual : player) {
        if ((tmp = PathFinding(map, pos, actual.pos))[0] != ecs::Actions::DO_NOTHING)
            return (tmp[0]);
    }
    if (map.getCellAt(pos.x - 1, pos.y) == DESTRUCTIBLE ||
        map.getCellAt(pos.x + 1, pos.y) == DESTRUCTIBLE ||
        map.getCellAt(pos.x, pos.y - 1) == DESTRUCTIBLE ||
        map.getCellAt(pos.x, pos.y + 1) == DESTRUCTIBLE)
        return (ecs::Actions::PLACE_BOMB);
    return (randoum[std::rand() % 5]);
}

std::deque<ecs::Actions> AiFunc::PathFinding(map::Map &map, ecs::GridPosition in, ecs::GridPosition out)
{
    std::deque<ecs::GridPosition> actual;
    std::deque<ecs::GridPosition> next;
    std::deque<ecs::GridPosition>::iterator itr;
    std::deque<ecs::Actions> result;
    std::vector<int> pathfind = map.getMap();

    actual.push_back(in);
    defineNext(actual, next, pathfind, map.getWidth());
    itr = std::find(next.begin(), next.end(), out);
    for (int i = 0; itr != next.end(); i++) {
        if (next.empty()) {
            result.push_back(ecs::Actions::DO_NOTHING);
            return (result);
        }
        for (int j = 0; j < next.size(); j++)
            pathfind[next[j].x + next[j].y *  map.getWidth()] = i;
        defineNext(actual, next, pathfind, map.getWidth());
        itr = std::find(next.begin(), next.end(), out);
    }
    for (int i = pathfind[out.x + out.y * map.getWidth()] - 1; i != 0; i--) {
        if (pathfind[out.x - 1 + out.y * map.getWidth()] == i) {
            out.x = out.x - 1;
            result.push_back(ecs::Actions::MOVE_LEFT);
        } else if (pathfind[out.x + 1 + out.y * map.getWidth()] == i) {
            out.x = out.x + 1;
            result.push_back(ecs::Actions::MOVE_RIGHT);
        } else if (pathfind[out.x + (out.y + 1) * map.getWidth()] == i) {
            out.y = out.y + 1;
            result.push_back(ecs::Actions::MOVE_DOWN);
        } else if (pathfind[out.x + (out.y - 1) * map.getWidth()] == i) {
            out.y = out.y - 1;
            result.push_back(ecs::Actions::MOVE_UP);
        }
    }
    return (result);
}

void AiFunc::defineNext(std::deque<ecs::GridPosition> actual, std::deque<ecs::GridPosition> &next, std::vector<int> &map, int width)
{
    ecs::GridPosition posNext;

    next.clear();
    for (int i = 0; i < actual.size(); i++) {
        int tmp_x = actual[i].x;
        int tmp_y = actual[i].y;
        if (tmp_x - 1 >= 0 && map[tmp_x - 1 +  tmp_y * width] == VOID) {
            posNext.x = tmp_x - 1;
            posNext.y = tmp_y;
            next.push_back(posNext);
        } if (tmp_x + 1 < width && map[tmp_x + 1 + tmp_y * width] == VOID) {
            posNext.x = tmp_x + 1;
            posNext.y = tmp_y;
            next.push_back(posNext);
        } if (tmp_y - 1 >= 0 && map[tmp_x +  (tmp_y - 1) * width] == VOID) {
            posNext.x = tmp_x;
            posNext.y = tmp_y - 1;
            next.push_back(posNext);
        } if (tmp_y + 1 < width && map[tmp_x + (tmp_y + 1) * width] == VOID) {
            posNext.x = tmp_x;
            posNext.y = tmp_y + 1;
            next.push_back(posNext);
        }
    }
}

void AiFunc::defineDangerous(map::Map &map, std::deque<BombStruct> bomb)
{
    for (auto actual : bomb)
        defineBomb(actual.pos.x, actual.pos.y, map, 4);
}

void AiFunc::defineBomb(int x, int y, map::Map &map, int bomb_length)
{
    int line[4] = {1, 1, 1, 1};

    map.setCellAt(x, y, DANGEROUS);
    for (int i = 1; i < bomb_length; i++) {
        if (line[0] && ((map.getCellAt(x - i, y) == VOID || map.getCellAt(x - i, y) >= 0) && x != 0)) {
            map.setCellAt(x - i, y, DANGEROUS);
        } else
            line[0] = 0;

        if (line[1] && ((map.getCellAt(x + i, y) == VOID || map.getCellAt(x + i, y) >= 0)) && x < map.getWidth()) {
            map.setCellAt(x + i, y, DANGEROUS);
        } else
            line[1] = 0;


        if (line[2] && ((map.getCellAt(x, y - i) == VOID || map.getCellAt(x, y - i) >= 0) && y != 0)) {
            map.setCellAt(x, y - i, DANGEROUS);
        } else
            line[2] = 0;


        if (line[3] && ((map.getCellAt(x, y + i) == VOID || map.getCellAt(x, y + i) >= 0) && y < map.getHeight())) {
            map.setCellAt(x, y + i, DANGEROUS);
        } else
            line[3] = 0;
    }
}