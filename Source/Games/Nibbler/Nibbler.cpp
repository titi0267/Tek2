/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-arcade-alexandre.frantz
** File description:
** Nibbler
*/

#include "Nibbler.hpp"

Nibbler::Nibbler()
{
    _gum = true;
}

Nibbler::~Nibbler()
{
}

void Nibbler::init(ICore *coreHandle)
{
    ICore::Vector2u windowSize{1920, 1080};
    ICore::Vector2u windowSize2{10, 10};
    ICore::Vector2u windowSize3{10, 11};
    ICore::Vector2u windowSize4{10, 12};
    ICore::Vector2u windowSize5{10, 13};

    coreHandle->openWindow(windowSize);
    _sprite.push_back({windowSize2, coreHandle->loadTexture("./Assets/Menu/Background.png", ' ', ICore::Color::blue, ICore::Color::blue, 612, 437)});
    _sprite.push_back({windowSize5, coreHandle->loadTexture("./Assets/Nibbler/Gums.png", 'O', ICore::Color::red, ICore::Color::black, 612, 437)});
    _sprite.push_back({windowSize5, coreHandle->loadTexture("./Assets/Nibbler/Border.png", '#', ICore::Color::red, ICore::Color::black, 612, 437)});
    _sprite.push_back({windowSize2, coreHandle->loadTexture("./Assets/Nibbler/HeadRight.png", ' ', ICore::Color::blue, ICore::Color::red, 612, 437)});
    _sprite.push_back({windowSize2, coreHandle->loadTexture("./Assets/Nibbler/HeadLeft.png", ' ', ICore::Color::blue, ICore::Color::red, 612, 437)});
    _sprite.push_back({windowSize2, coreHandle->loadTexture("./Assets/Nibbler/HeadUp.png", ' ', ICore::Color::blue, ICore::Color::red, 612, 437)});
    _sprite.push_back({windowSize2, coreHandle->loadTexture("./Assets/Nibbler/HeadDown.png", ' ', ICore::Color::blue, ICore::Color::red, 612, 437)});
    _sprite.push_back({windowSize4, coreHandle->loadTexture("./Assets/Nibbler/BodyVertical.png", ' ', ICore::Color::black, ICore::Color::red, 612, 437)});
    _sprite.push_back({windowSize4, coreHandle->loadTexture("./Assets/Nibbler/BodyHorizontal.png", ' ', ICore::Color::black, ICore::Color::red, 612, 437)});
    _sprite.push_back({windowSize4, coreHandle->loadTexture("./Assets/Nibbler/BodyCornerLeftUp.png", ' ', ICore::Color::black, ICore::Color::red, 612, 437)});
    _sprite.push_back({windowSize4, coreHandle->loadTexture("./Assets/Nibbler/BodyCornerRightUp.png", ' ', ICore::Color::black, ICore::Color::red, 612, 437)});
    _sprite.push_back({windowSize4, coreHandle->loadTexture("./Assets/Nibbler/BodyCornerLeftDown.png", ' ', ICore::Color::black, ICore::Color::red, 612, 437)});
    _sprite.push_back({windowSize4, coreHandle->loadTexture("./Assets/Nibbler/BodyCornerRightDown.png", ' ', ICore::Color::black, ICore::Color::red, 612, 437)});
    _sprite.push_back({windowSize5, coreHandle->loadTexture("./Assets/Nibbler/TailUp.png", ' ', ICore::Color::green, ICore::Color::red, 612, 437)});
    _sprite.push_back({windowSize5, coreHandle->loadTexture("./Assets/Nibbler/TailDown.png", ' ', ICore::Color::green, ICore::Color::red, 612, 437)});
    _sprite.push_back({windowSize5, coreHandle->loadTexture("./Assets/Nibbler/TailLeft.png", ' ', ICore::Color::green, ICore::Color::red, 612, 437)});
    _sprite.push_back({windowSize5, coreHandle->loadTexture("./Assets/Nibbler/TailRight.png", ' ', ICore::Color::green, ICore::Color::red, 612, 437)});

    coreHandle->setFramerate(10);
    coreHandle->setPixelsPerCell(8);
    _core = coreHandle;
}

void Nibbler::update()
{
    ;
}

bool Nibbler::checkSnakePosX(unsigned random)
{
    for (int d = 3; d < _snakeSize + 3; d++) {
        if (_sprite[d].pixelPosition.x == random) //pas les bonnes sprites
            return true;
    }
    return false;
}

bool Nibbler::checkSnakePosY(unsigned random)
{
    for (int d = 3; d < _snakeSize + 3; d++) {
        if (_sprite[d].pixelPosition.y == random) //pas les bonnes sprites ?
            return true;
    }
    return false;
}

bool Nibbler::checkSnakeHeadPosX(unsigned random, int whichHead)
{
    if (_sprite[whichHead].pixelPosition.x == random)
        return true;
    return false;
}

bool Nibbler::checkSnakeHeadPosY(unsigned random, int whichHead)
{
    if (_sprite[whichHead].pixelPosition.x == random)
        return true;
    return false;
}

void Nibbler::setGum(int headDirection)
{
    int randomX;
    int randomY;

    if (_gum == true) {
        if (checkSnakeHeadPosX(_sprite[1].pixelPosition.x, headDirection) == false)
            ;
    }
    if (_gum == false) {
        randomX = rand() % 19 + 1;
        randomY = rand() % 10 + 1;
        while (1) {
            if (checkSnakePosX(randomX) == false && checkSnakePosY(randomY) == false)// && (randomY != 0 && randomY != 10) && (randomX != 0 && randomX != 20))
                break;
            randomX = rand() % 19 + 1;
            randomY = rand() % 10 + 1;
        }
        _sprite[1].pixelPosition.x = randomX;
        _sprite[1].pixelPosition.y = randomY;
        _gum == true;
    }
}

void Nibbler::draw()
{
    ;
}
