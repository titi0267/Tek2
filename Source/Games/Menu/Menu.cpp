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

    coreHandle->openWindow(windowSize);
    _sprite.push_back({windowSize, coreHandle->loadTexture("./Assets/Menu/Background.jpg", ' ', ICore::Color::red, ICore::Color::blue, 612, 437)});
    _sprite.push_back({windowSize, coreHandle->loadTexture("./Assets/Menu/Background.jpg", ' ', ICore::Color::red, ICore::Color::blue, 612, 437)});
    coreHandle->setFramerate(10);
    coreHandle->setPixelsPerCell(8);
    _core = coreHandle;
}

void Menu::draw()
{
    for (int i = 0; i < _sprite.size(); i++)
        _core->renderSprite(_sprite[i]);
}

void Menu::update()
{
    ;
}