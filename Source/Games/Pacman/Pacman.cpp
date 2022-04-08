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
    ICore::Vector2u windowsSize{39, 20};
    ICore::Vector2u border{0, 0};
    ICore::Vector2u pacman{19, 12};
    ICore::Vector2u ghost1{18, 10};
    ICore::Vector2u ghost2{19, 10};
    ICore::Vector2u ghost3{20, 10};

    coreHandle->openWindow(windowsSize);
    _sprite.push_back({border, coreHandle->loadTexture("./Assets/Pacman/Border/cornerBotLeft.png", '#', ICore::Color::black, ICore::Color::black, 8, 8)});
    _sprite.push_back({border, coreHandle->loadTexture("./Assets/Pacman/Border/cornerBotRight.png", '#', ICore::Color::black, ICore::Color::black, 8, 8)});
    _sprite.push_back({border, coreHandle->loadTexture("./Assets/Pacman/Border/cornerTopLeft.png", '#', ICore::Color::black, ICore::Color::black, 8, 8)});
    _sprite.push_back({border, coreHandle->loadTexture("./Assets/Pacman/Border/cornerTopRight.png", '#', ICore::Color::black, ICore::Color::black, 8, 8)});
    _sprite.push_back({border, coreHandle->loadTexture("./Assets/Pacman/Border/wallVertical.png", '#', ICore::Color::black, ICore::Color::black, 8, 8)});
    _sprite.push_back({border, coreHandle->loadTexture("./Assets/Pacman/Border/wallHorizon.png", '#', ICore::Color::black, ICore::Color::black, 8, 8)});
    _sprite.push_back({border, coreHandle->loadTexture("./Assets/Pacman/Other/littlePacGum.png", '.', ICore::Color::black, ICore::Color::black, 8, 8)});
    _sprite.push_back({border, coreHandle->loadTexture("./Assets/Pacman/Border/doubleAngleBot.png", '#', ICore::Color::black, ICore::Color::black, 8, 8)});
    _sprite.push_back({border, coreHandle->loadTexture("./Assets/Pacman/Border/doubleAngleTop.png", '#', ICore::Color::black, ICore::Color::black, 8, 8)});
    _sprite.push_back({border, coreHandle->loadTexture("./Assets/Pacman/Border/doubleAngleLeft.png", '#', ICore::Color::black, ICore::Color::black, 8, 8)});
    _sprite.push_back({border, coreHandle->loadTexture("./Assets/Pacman/Border/doubleAngleRight.png", '#', ICore::Color::black, ICore::Color::black, 8, 8)});
    _sprite.push_back({border, coreHandle->loadTexture("./Assets/Pacman/Border/oneBotWall.png", '#', ICore::Color::black, ICore::Color::black, 8, 8)});
    _sprite.push_back({border, coreHandle->loadTexture("./Assets/Pacman/Border/oneTopWall.png", '#', ICore::Color::black, ICore::Color::black, 8, 8)});
    _sprite.push_back({border, coreHandle->loadTexture("./Assets/Pacman/Border/oneLeftWall.png", '#', ICore::Color::black, ICore::Color::black, 8, 8)});
    _sprite.push_back({border, coreHandle->loadTexture("./Assets/Pacman/Border/oneRightWall.png", '#', ICore::Color::black, ICore::Color::black, 8, 8)});
    _sprite.push_back({border, coreHandle->loadTexture("./Assets/Pacman/Border/blackWall.png", '#', ICore::Color::black, ICore::Color::black, 8, 8)});
    _sprite.push_back({border, coreHandle->loadTexture("./Assets/Pacman/Border/ballWall.png", '#', ICore::Color::black, ICore::Color::black, 8, 8)});
    _sprite.push_back({border, coreHandle->loadTexture("./Assets/Pacman/Border/door.png", '#', ICore::Color::black, ICore::Color::black, 8, 8)});
    _sprite.push_back({pacman, coreHandle->loadTexture("./Assets/Pacman/Other/pacmanLeft.png", '#', ICore::Color::black, ICore::Color::black, 8, 8)});
    _sprite.push_back({ghost1, coreHandle->loadTexture("./Assets/Pacman/Other/pinkBot.png", '#', ICore::Color::black, ICore::Color::black, 8, 8)});
    _sprite.push_back({ghost2, coreHandle->loadTexture("./Assets/Pacman/Other/blueBot.png", '#', ICore::Color::black, ICore::Color::black, 8, 8)});
    _sprite.push_back({ghost3, coreHandle->loadTexture("./Assets/Pacman/Other/redBot.png", '#', ICore::Color::black, ICore::Color::black, 8, 8)});

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
        if (_map[i] == 'r')
            _core->renderSprite({{_sprite[4].pixelPosition.x + z, _sprite[4].pixelPosition.y + y}, _sprite[4].texture});
        if (_map[i] == 't')
            _core->renderSprite({{_sprite[5].pixelPosition.x + z, _sprite[5].pixelPosition.y + y}, _sprite[5].texture});
        if (_map[i] == '.')
            _core->renderSprite({{_sprite[6].pixelPosition.x + z, _sprite[6].pixelPosition.y + y}, _sprite[6].texture});
        if (_map[i] == 'u')
            _core->renderSprite({{_sprite[7].pixelPosition.x + z, _sprite[7].pixelPosition.y + y}, _sprite[7].texture});
        if (_map[i] == 'h')
            _core->renderSprite({{_sprite[8].pixelPosition.x + z, _sprite[8].pixelPosition.y + y}, _sprite[8].texture});
        if (_map[i] == 'c')
            _core->renderSprite({{_sprite[9].pixelPosition.x + z, _sprite[9].pixelPosition.y + y}, _sprite[9].texture});
        if (_map[i] == 'f')
            _core->renderSprite({{_sprite[10].pixelPosition.x + z, _sprite[10].pixelPosition.y + y}, _sprite[10].texture});
        if (_map[i] == 'g')
            _core->renderSprite({{_sprite[11].pixelPosition.x + z, _sprite[11].pixelPosition.y + y}, _sprite[11].texture});
        if (_map[i] == 'k')
            _core->renderSprite({{_sprite[12].pixelPosition.x + z, _sprite[12].pixelPosition.y + y}, _sprite[12].texture});
        if (_map[i] == 'l')
            _core->renderSprite({{_sprite[13].pixelPosition.x + z, _sprite[13].pixelPosition.y + y}, _sprite[13].texture});
        if (_map[i] == 'm')
            _core->renderSprite({{_sprite[14].pixelPosition.x + z, _sprite[14].pixelPosition.y + y}, _sprite[14].texture});
        if (_map[i] == 'b')
            _core->renderSprite({{_sprite[15].pixelPosition.x + z, _sprite[15].pixelPosition.y + y}, _sprite[15].texture});
        if (_map[i] == 'p')
            _core->renderSprite({{_sprite[16].pixelPosition.x + z, _sprite[16].pixelPosition.y + y}, _sprite[16].texture});
        if (_map[i] == '-')
            _core->renderSprite({{_sprite[17].pixelPosition.x + z, _sprite[17].pixelPosition.y + y}, _sprite[17].texture});
        if (_map[i] == 'C')
            _core->renderSprite({{_sprite[18].pixelPosition.x, _sprite[18].pixelPosition.y}, _sprite[18].texture});
        if (_map[i] == 'X')
            _core->renderSprite({{_sprite[19].pixelPosition.x, _sprite[19].pixelPosition.y}, _sprite[19].texture});
        if (_map[i] == 'Y')
            _core->renderSprite({{_sprite[20].pixelPosition.x, _sprite[20].pixelPosition.y}, _sprite[20].texture});
        if (_map[i] == 'Z')
            _core->renderSprite({{_sprite[21].pixelPosition.x, _sprite[21].pixelPosition.y}, _sprite[21].texture});
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