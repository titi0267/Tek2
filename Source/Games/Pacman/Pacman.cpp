/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-arcade-alexandre.frantz
** File description:
** Pacman
*/

#include "Pacman.hpp"

Pacman::Pacman()
{
    constructMap();
}

Pacman::~Pacman()
{
}

void Pacman::init(ICore *coreHandle)
{
    ICore::Vector2u windowsSize{1920, 1080};
    ICore::Vector2u border{0, 0};

    coreHandle->openWindow(windowsSize);
    _sprite.push_back({border, coreHandle->loadTexture("./Assets/Pacman/Border/cornerBotLeft.png", '#', ICore::Color::black, ICore::Color::black, 8, 8)});
    _sprite.push_back({border, coreHandle->loadTexture("./Assets/Pacman/Border/cornerBotRight.png", '#', ICore::Color::black, ICore::Color::black, 8, 8)});
    _sprite.push_back({border, coreHandle->loadTexture("./Assets/Pacman/Border/cornerTopLeft.png", '#', ICore::Color::black, ICore::Color::black, 8, 8)});
    _sprite.push_back({border, coreHandle->loadTexture("./Assets/Pacman/Border/cornerTopRight.png", '#', ICore::Color::black, ICore::Color::black, 8, 8)});
    _sprite.push_back({border, coreHandle->loadTexture("./Assets/Pacman/Border/oneBotWall.png", '#', ICore::Color::black, ICore::Color::black, 8, 8)});
    _sprite.push_back({border, coreHandle->loadTexture("./Assets/Pacman/Border/oneTopWall.png", '#', ICore::Color::black, ICore::Color::black, 8, 8)});
    //_sprite.push_back({border, coreHandle->loadTexture("./Assets/Pacman/Border/oneTopWall.png", '#', ICore::Color::black, ICore::Color::black, 8, 8)});
    _sprite.push_back({border, coreHandle->loadTexture("./Assets/Pacman/Other/littlePacGum.png", '.', ICore::Color::black, ICore::Color::black, 8, 8)});

    coreHandle->setFramerate(30);
    coreHandle->setPixelsPerCell(8);
    _core = coreHandle;
}

void Pacman::constructMap()
{
    std::ifstream map("./Maps/pacman_map1.txt", std::ios::in);
    char element;

    if (!map.fail()) {
        while (map.get(element))
            _map.push_back(element);
        std::cout << "map here:" << std::endl;
    } else {
        //error
        std::cout << "fail here:" << std::endl;
    }
}

void Pacman::update()
{
    ;
}

void Pacman::draw()
{
    _core->clearScreen(ICore::Color::black);
    for (int i = 0, y = 0, z = 0; i < _map.size(); i++, z++) {
        if (_map[i] == '1')
            _core->renderSprite({{_sprite[2].pixelPosition.x + z, _sprite[2].pixelPosition.y + y}, _sprite[2].texture});
        if (_map[i] == '2')
            _core->renderSprite({{_sprite[3].pixelPosition.x + z, _sprite[3].pixelPosition.y + y}, _sprite[3].texture});
        if (_map[i] == '3')
            _core->renderSprite({{_sprite[1].pixelPosition.x + z, _sprite[1].pixelPosition.y + y}, _sprite[1].texture});
        if (_map[i] == '4')
            _core->renderSprite({{_sprite[0].pixelPosition.x + z, _sprite[0].pixelPosition.y + y}, _sprite[0].texture});
        if (_map[i] == 'b')
            _core->renderSprite({{_sprite[4].pixelPosition.x + z, _sprite[4].pixelPosition.y + y}, _sprite[4].texture});
        if (_map[i] == 't')
            _core->renderSprite({{_sprite[5].pixelPosition.x + z, _sprite[5].pixelPosition.y + y}, _sprite[5].texture});
        if (_map[i] == '.')
            _core->renderSprite({{_sprite[6].pixelPosition.x + z, _sprite[6].pixelPosition.y + y}, _sprite[6].texture});
        if (_map[i] == '\n') {
            y++;
            z = -1;
        }
    }
    //_core->renderSprite(_sprite[1]);
}

std::unique_ptr<IGameModule> gEpitechArcadeGetGameModuleHandle()
{
    return std::make_unique<Pacman>();
}