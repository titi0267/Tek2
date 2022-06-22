/*
** EPITECH PROJECT, 2022
** indie
** File description:
** Map
*/

#pragma once

#include <vector>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <fstream>
#include <iterator>

#define MAP_X _width
#define MAP_Y _height

#define VOID 1
#define WALL 2
#define SPAWN 3
#define DESTRUCTIBLE 4
#define BOMB 5
#define DANGEROUS 6

namespace map {
    class Map {
        int _height;
        int _width;
        int _nbrPlayer;
        int _complexity;
        std::vector<int> _map;

        void setPlayer();
        void setWall();
        void setDestructible();
        void cruxGen();
        void squareGen();
        void addGen();

        public:
        Map(int _height, int _width, int nbrPlayer, int complexity);
        Map(const Map &other) : _height(other._height), _width(other._width),
        _nbrPlayer(other._nbrPlayer), _complexity(other._complexity), _map(other._map) {}

        int getHeight() const { return _height; };
        int getWidth() const { return _width; };
        int getCellAt(int x, int y) const { return (_map.at(x + y * _width)); };
        void setCellAt(int x, int y, int val) { _map.at(x + y * _width) = val; };
        bool isValidCell(int x, int y) { return x >= 0 && y >= 0 && x < _width && y < _height; };
        bool isWalkableCell(int x, int y) {
            int cell = _map.at(x + y * _width);

            return cell == VOID || cell == SPAWN || cell == DANGEROUS;
        };

        void dump();
        void print(ecs::World &world);
        void save(std::string name);
        void load(std::string filename);
        std::vector<int> &getMap() { return _map; };
    };
}
