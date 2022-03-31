/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-arcade-alexandre.frantz
** File description:
** Sfml
*/

#include "Sfml.hpp"

Sfml::Sfml()
{
}

Sfml::~Sfml()
{
}

void Sfml::setPixelsPerCell(std::uint32_t pixelsPerCell)
{
    _pixelsPerCell = pixelsPerCell;
}

std::uint32_t Sfml::getPixelsPerCell()
{
    return _pixelsPerCell;
}

std::unique_ptr<IDisplayModule::RawTexture> Sfml::loadTexture(const std::string &filename, char character, IDisplayModule::Color characterColor, IDisplayModule::Color backgroundColor, std::size_t width, std::size_t height)
{
    std::unique_ptr<IDisplayModule::RawTexture> tmp;
    (void)filename;
    (void)character;
    (void)characterColor;
    (void)backgroundColor;
    (void)width;
    (void)height;
    return tmp;
}

void Sfml::openWindow(IDisplayModule::Vector2u pixelsWantedWindowSize)
{

}

bool Sfml::isButtonPressed(IDisplayModule::Button button)
{
    (void)button;
    return true;
}

IDisplayModule::MouseButtonReleaseEvent Sfml::getMouseButtonReleaseEvent()
{
    IDisplayModule::MouseButtonReleaseEvent tmp;
    return tmp;
}

bool Sfml::isClosing()
{
    return true;
}

void Sfml::startTextInput()
{

}

std::string Sfml::getTextInput()
{
    std::string tmp;
    return tmp;
}

void Sfml::endTextInput()
{
    ;
}

void Sfml::clearScreen(IDisplayModule::Color color)
{
    (void)color;
}

void Sfml::renderSprite(IDisplayModule::Sprite sprite)
{
    (void)sprite;
}

void Sfml::display()
{

}

void Sfml::update()
{

}

std::unique_ptr<IDisplayModule> gEpitechArcadeGetDisplayModuleHandle()
{
    return std::make_unique<Sfml>();
}