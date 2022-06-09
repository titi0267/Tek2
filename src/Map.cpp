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

map::Map::Map(int height, int width, int nbrPlayer, int complexity) : _height(height), _width(width), _nbrPlayer(nbrPlayer), _map(height * width, VOID), _complexity(complexity)
{
    if (!(_height % 2 && _width % 2))
        throw std::invalid_argument("x and y size must be odd");
    setPlayer();
    setWall();
    setDestructible();
}

map::Map::~Map()
{
}

int map::Map::getHeight()
{
    return (_height);
}

int map::Map::getWidth()
{
    return (_width);
}

void map::Map::setWall()
{
    int layer = 1;

    if (_height >= 7 && _width >= 7)
        layer++;
    if (_height >= 9 && _width >= 9)
        layer++;
    layer = std::rand() % layer;
    switch (layer) {
    case 0:
        cruxGen();
        break;
    case 1:
        squareGen();
        break;
    case 2:
        addGen();
        break;
    default:
        break;
    }
    return;
}

void map::Map::cruxGen()
{
    for (int i = 1; i < MAP_Y; i++) {
        for (int j = 1; j < MAP_X; j++) {
            if (i % 2 != 0 && j % 2 != 0)
                setCellsAt(j, i, WALL);
        }
    }
}

void map::Map::squareGen()
{
    //UP LEFT
    setCellsAt(1, 1, WALL);
    setCellsAt(2, 1, WALL);
    setCellsAt(1, 2, WALL);

    //UP RIGHT
    setCellsAt(MAP_X - 2, 1, WALL);
    setCellsAt(MAP_X - 3, 1, WALL);
    setCellsAt(MAP_X - 2, 2, WALL);

    // DOWN LEFT
    setCellsAt(1, MAP_Y - 2, WALL);
    setCellsAt(2, MAP_Y - 2, WALL);
    setCellsAt(1, MAP_Y - 3, WALL);

    // DOWN RIGHT
    setCellsAt(MAP_X - 2, MAP_Y - 2, WALL);
    setCellsAt(MAP_X - 3, MAP_Y - 2, WALL);
    setCellsAt(MAP_X - 2, MAP_Y - 3, WALL);

    // CENTRE
    for (int i = 3; i < MAP_Y - 3; i++) {
        for (int j = 3; j < MAP_X - 3; j++) {
            setCellsAt(j, i, WALL);
        }
    }
}

void map::Map::addGen()
{
    for (int i = 1; i < MAP_Y - 1; i++) {
        setCellsAt(MAP_X / 2, i, WALL);
        setCellsAt(i, MAP_Y / 2, WALL);
    }

    //UP LEFT
    setCellsAt(2, 2, WALL);
    setCellsAt(2, 1, WALL);
    setCellsAt(1, 2, WALL);

    //UP RIGHT
    setCellsAt(MAP_X - 3, 2, WALL);
    setCellsAt(MAP_X - 3, 1, WALL);
    setCellsAt(MAP_X - 2, 2, WALL);

    // DOWN LEFT
    setCellsAt(2, MAP_Y - 3, WALL);
    setCellsAt(2, MAP_Y - 2, WALL);
    setCellsAt(1, MAP_Y - 3, WALL);

    // DOWN RIGHT
    setCellsAt(MAP_X - 3, MAP_Y - 3, WALL);
    setCellsAt(MAP_X - 3, MAP_Y - 2, WALL);
    setCellsAt(MAP_X - 2, MAP_Y - 3, WALL);
}

void map::Map::setDestructible()
{
    for (int i = 0; i < MAP_Y; i++) {
        for (int j = 2; j < MAP_X - 2; j++) {
            if (getCellsAt(j, i) == VOID && std::rand() % _complexity)
                setCellsAt(j, i, DESTRUCTIBLE);
            continue;
        }
    }
    for (int i = 2; i < MAP_Y - 2; i++) {
        if (std::rand() % _complexity)
            setCellsAt(0, i, DESTRUCTIBLE);
        if (std::rand() % _complexity)
            setCellsAt(MAP_X - 1, i, DESTRUCTIBLE);
    }
}

void map::Map::setPlayer()
{
    setCellsAt(0, 0, SPAWN);
    setCellsAt(MAP_X - 1, MAP_Y - 1, SPAWN);
    if (_nbrPlayer >= 3)
        setCellsAt(0, MAP_Y - 1, SPAWN);
    if (_nbrPlayer >= 4)
        setCellsAt(MAP_X - 1, 0, SPAWN);
}

ecs::EntityCommands spawnBag(Vector3 pos, ecs::World &world)
{
    Transform transform = {pos, {0, 0, 0}, {0.5, 0.5, 0.5}};
    raylib::Model &bag = world.getRessource<raylib::ModelManager>().loadModel("./assets/bottle.iqm");

    return world.spawn().insert(transform, ecs::ModelRef {&bag});
}

ecs::EntityCommands spawnChair(Vector3 pos, ecs::World &world)
{
    Transform transform = {pos, {0, 0, 0}, {0.5, 0.5, 0.5}};
    raylib::Model &chair = world.getRessource<raylib::ModelManager>().loadModel("./assets/chair.iqm");

    return world.spawn().insert(transform, ecs::ModelRef {&chair});
}

ecs::EntityCommands spawnBottom(Vector3 pos, Vector3 size, ecs::World &world)
{
    Transform transform = {pos, {0, 0, 0}, size};
    raylib::Texture &texBottom = world.getRessource<raylib::TextureManager>().loadTexture("./assets/textures/ground.png");

    return world.spawn().insert(transform,
        ecs::DrawableCube {{0, 0, -0.05}, {1, 1, 0.1}}, ecs::TextureRef(&texBottom)
    );
}

ecs::EntityCommands spawnWall(Vector3 pos, Vector3 size, ecs::World &world)
{

}

void map::Map::print(ecs::World &world)
{
    spawnBottom({0, 7, -5.3}, {9 + 1, 9 + 1, 1}, world);
    spawnWall({0, 0, 0}, {0, 0, 0}, world);
    for (int i = 0; i < MAP_Y; i++) {
        for (int j = 0; j < MAP_X; j++) {
            switch (_map[j + i * _width]) {
            case VOID:
                std::cout << " ";
                break;
            case WALL:
                spawnChair({static_cast<float>(j - 4), static_cast<float>(i + 2), -5}, world);
                std::cout << "#";
                break;
            case SPAWN:
                std::cout << "P";
                break;
            case DESTRUCTIBLE:
                spawnBag({static_cast<float>(j - 4), static_cast<float>(i + 2), -5}, world);
                std::cout << "x";
                break;
            case BOMB:
                std::cout << "o";
                break;
            default:
                break;
            }
            if (j == _width - 1)
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
        std::cout <<it;
    std::cout << std::endl;
}

int map::Map::getCellsAt(int x, int y)
{
    return (_map[x + y * _width]);
}

void map::Map::setCellsAt(int x, int y, int val)
{
    _map[x + y * _width] = val;
}

std::vector<int> map::Map::getMap()
{
    return _map;
}


void map::Map::save(std::string name)
{
    std::ofstream saving(name + ".mbt");
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
