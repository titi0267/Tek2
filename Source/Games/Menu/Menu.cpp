/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-arcade-alexandre.frantz
** File description:
** Menu
*/

#include "Menu.hpp"

Menu::Menu()
{
}

Menu::~Menu()
{
}

void Menu::init(ICore *coreHandle)
{
    ICore::Vector2u windowSize{1920, 1080};
    ICore::Vector2u windowSize2{11, 11};
    ICore::Vector2u windowSize3{10, 11};
    ICore::Vector2u windowSize4{10, 12};
    ICore::Vector2u windowSize5{10, 13};

    coreHandle->openWindow(windowSize);
    //_sprite.push_back({windowSize2, coreHandle->loadTexture("./Assets/Menu/Background.jpg", ' ', ICore::Color::white, ICore::Color::yellow, 612, 437)});
    _sprite.push_back({windowSize2, coreHandle->loadTexture("./Assets/Menu/Background.jpg", '>', ICore::Color::black, ICore::Color::red, 612, 437)});
    _sprite.push_back({windowSize3, coreHandle->loadTexture("./Assets/Menu/Background.jpg", '/', ICore::Color::black, ICore::Color::magenta, 612, 437)});
    _sprite.push_back({windowSize4, coreHandle->loadTexture("./Assets/Menu/Background.jpg", '|', ICore::Color::black, ICore::Color::magenta, 612, 437)});
    _sprite.push_back({windowSize5, coreHandle->loadTexture("./Assets/Menu/Background.jpg", '*', ICore::Color::black, ICore::Color::cyan, 612, 437)});

    coreHandle->setFramerate(20);
    coreHandle->setPixelsPerCell(8);
    _core = coreHandle;
}

void Menu::draw()
{
    _core->clearScreen(ICore::Color::black);
    for (int i = 0; i < _sprite.size(); i++)
        _core->renderSprite(_sprite[i]);
}

void Menu::update()
{
    ;
}

std::unique_ptr<IGameModule> gEpitechArcadeGetGameModuleHandle()
{
    return std::make_unique<Menu>();
}
