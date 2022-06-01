/*
** EPITECH PROJECT, 2022
** indie
** File description:
** Map
*/

#ifndef MAP_HPP_
#define MAP_HPP_

#include <vector>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <fstream>
#include <iterator>

#define MAP_X _width
#define MAP_Y _height

class Map {
    public:
        Map(int _height, int _width, int nbrPlayer, int complexity);
        ~Map();
        int getCellsAt(int x, int y);
        void setCellsAt(int x, int y, int val);
        void dump();
        void print();
        void save(std::string name);
        void load(std::string filename);
        std::vector<int> sendMap();
    protected:
        int _height;
        int _width;
        int _nbrPlayer;
        int _complexity;
        std::vector<int> _map;
    private:
        void setPlayer();
        void setWall();
        void setDestructible();
        void cruxGen();
        void squareGen();
        void addGen();
};

#endif /* !MAP_HPP_ */
