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

        int getHeight() const { return _height; };
        int getWidth() const { return _width; };
        int getCellAt(int x, int y) const { return (_map[x + y * _width]); };
        void setCellAt(int x, int y, int val) { _map[x + y * _width] = val; };

        void dump();
        void print(ecs::World &world);
        void save(std::string name);
        void load(std::string filename);
        std::vector<int> &getMap() { return _map; };
    };
}
