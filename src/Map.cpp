/*
** EPITECH PROJECT, 2022
** indie
** File description:
** Map
*/

#include "ecs/engine/EntityCommands.hpp"

#include "raylib/Camera.hpp"
#include "raylib/Window.hpp"

#include "raylib/TextureManager.hpp"
#include "raylib/ModelManager.hpp"
#include "raylib/AnimationManager.hpp"
#include "raylib/FontManager.hpp"

#include "ecs/components/DrawableCube.hpp"
#include "ecs/components/DrawableModel.hpp"
#include "ecs/components/Hitbox.hpp"
#include "ecs/components/Clickable.hpp"
#include "ecs/components/HoverTint.hpp"
#include "ecs/components/Text3D.hpp"
#include "ecs/components/ColorTexture.hpp"

#include "Map.hpp"

map::Map::Map(int height, int width, int nbrPlayer, int complexity)
    : _height(height), _width(width), _nbrPlayer(nbrPlayer), _map(height * width, VOID), _complexity(complexity)
{
    if (!(_height % 2 && _width % 2))
        throw std::invalid_argument("x and y size must be odd");
    setPlayer();
    setWall();
    setDestructible();
}

void map::Map::setWall()
{
    const std::unordered_map<int, void(map::Map::*)()> GENS = {
        {0, &Map::cruxGen}, {1, &Map::squareGen}, {2, &Map::addGen},
    };
    int layer = 1;

    if (_height >= 7 && _width >= 7)
        layer++;
    if (_height >= 9 && _width >= 9)
        layer++;
    layer = std::rand() % layer;
    ((*this).*(GENS.at(layer)))();
}

void map::Map::cruxGen()
{
    for (int i = 1; i < MAP_Y; i++) {
        for (int j = 1; j < MAP_X; j++) {
            if (i % 2 != 0 && j % 2 != 0)
                setCellAt(j, i, WALL);
        }
    }
}

void map::Map::squareGen()
{
    //UP LEFT
    setCellAt(1, 1, WALL);
    setCellAt(2, 1, WALL);
    setCellAt(1, 2, WALL);

    //UP RIGHT
    setCellAt(MAP_X - 2, 1, WALL);
    setCellAt(MAP_X - 3, 1, WALL);
    setCellAt(MAP_X - 2, 2, WALL);

    // DOWN LEFT
    setCellAt(1, MAP_Y - 2, WALL);
    setCellAt(2, MAP_Y - 2, WALL);
    setCellAt(1, MAP_Y - 3, WALL);

    // DOWN RIGHT
    setCellAt(MAP_X - 2, MAP_Y - 2, WALL);
    setCellAt(MAP_X - 3, MAP_Y - 2, WALL);
    setCellAt(MAP_X - 2, MAP_Y - 3, WALL);

    // CENTRE
    for (int i = 3; i < MAP_Y - 3; i++) {
        for (int j = 3; j < MAP_X - 3; j++) {
            setCellAt(j, i, WALL);
        }
    }
}

void map::Map::addGen()
{
    for (int i = 1; i < MAP_Y - 1; i++) {
        setCellAt(MAP_X / 2, i, WALL);
        setCellAt(i, MAP_Y / 2, WALL);
    }

    //UP LEFT
    setCellAt(2, 2, WALL);
    setCellAt(2, 1, WALL);
    setCellAt(1, 2, WALL);

    //UP RIGHT
    setCellAt(MAP_X - 3, 2, WALL);
    setCellAt(MAP_X - 3, 1, WALL);
    setCellAt(MAP_X - 2, 2, WALL);

    // DOWN LEFT
    setCellAt(2, MAP_Y - 3, WALL);
    setCellAt(2, MAP_Y - 2, WALL);
    setCellAt(1, MAP_Y - 3, WALL);

    // DOWN RIGHT
    setCellAt(MAP_X - 3, MAP_Y - 3, WALL);
    setCellAt(MAP_X - 3, MAP_Y - 2, WALL);
    setCellAt(MAP_X - 2, MAP_Y - 3, WALL);
}

void map::Map::setDestructible()
{
    for (int i = 0; i < MAP_Y; i++) {
        for (int j = 2; j < MAP_X - 2; j++) {
            if (getCellAt(j, i) == VOID && std::rand() % _complexity)
                setCellAt(j, i, DESTRUCTIBLE);
            continue;
        }
    }
    for (int i = 2; i < MAP_Y - 2; i++) {
        if (std::rand() % _complexity)
            setCellAt(0, i, DESTRUCTIBLE);
        if (std::rand() % _complexity)
            setCellAt(MAP_X - 1, i, DESTRUCTIBLE);
    }
}

void map::Map::setPlayer()
{
    setCellAt(0, 0, SPAWN);
    setCellAt(MAP_X - 1, MAP_Y - 1, SPAWN);
    if (_nbrPlayer >= 3)
        setCellAt(0, MAP_Y - 1, SPAWN);
    if (_nbrPlayer >= 4)
        setCellAt(MAP_X - 1, 0, SPAWN);
}

void map::Map::print(ecs::World &world)
{
    const std::unordered_map<int, char> REPR = {
        {VOID, ' '}, {WALL, '#'}, {SPAWN, 'P'}, {DESTRUCTIBLE, 'x'}, {BOMB, 'o'},
    };

    for (int y = 0; y < MAP_Y; y++) {
        for (int x = 0; x < MAP_X; x++) {
            std::cout << REPR.at(_map[x + y * _width]);
            if (x == _width - 1)
                std::cout << std::endl;
        }
    }
}

void map::Map::dump()
{
    std::cout << "DUMP MAP OBJECT" << std::endl;
    std::cout << "Height: " << _height << std::endl;
    std::cout << "Width: " << _width << std::endl;
    std::cout << "Nbr Player: " << _nbrPlayer << std::endl;
    for (int i = 0; i < MAP_Y; i++) {
        for (int j = 0; j < MAP_X; j++) {
            std::cout << _map[j + i * _width];
            if (j == _width - 1)
                std::cout << std::endl;
        }
    }
    std::cout << "Map brute : ";
    for (auto const &it : _map)
        std::cout << it;
    std::cout << std::endl;
}

void map::Map::save(std::string name)
{
    std::ofstream saving(name);
    saving << _height << "\n" << _width << "\n";
    std::ostream_iterator<int> saving_it(saving, "\n");
    std::copy(_map.begin(), _map.end(), saving_it);
}

void map::Map::load(std::string filename)
{
    std::ifstream filestr(filename);
    std::string str;
    int tmp = 0;
    _map.clear();

    while (std::getline(filestr, str)) {
        if (tmp == 0) {
            _height = std::stoi(str);
            tmp++;
        } else if (tmp == 1) {
            _width = std::stoi(str);
            tmp++;
        }
        else if (str.size() > 0)
            _map.push_back(std::stoi(str));
    }
}
