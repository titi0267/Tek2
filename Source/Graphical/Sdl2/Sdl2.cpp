/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-arcade-alexandre.frantz
** File description:
** Sdl2
*/

#include "Sdl2.hpp"

Sdl2::Sdl2()
{
}

Sdl2::~Sdl2()
{
}

void Sdl2::setPixelsPerCell(std::uint32_t pixelsPerCell)
{
    _pixelsPerCell = pixelsPerCell;
}

std::uint32_t Sdl2::getPixelsPerCell()
{
    return _pixelsPerCell;
}

std::unique_ptr<IDisplayModule::RawTexture> Sdl2::loadTexture(const std::string &filename, char character, IDisplayModule::Color characterColor, IDisplayModule::Color backgroundColor, std::size_t width, std::size_t height)
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

void Sdl2::openWindow(IDisplayModule::Vector2u pixelsWantedWindowSize)
{

}

bool Sdl2::isButtonPressed(IDisplayModule::Button button)
{
    (void)button;
    return true;
}

IDisplayModule::MouseButtonReleaseEvent Sdl2::getMouseButtonReleaseEvent()
{
    IDisplayModule::MouseButtonReleaseEvent tmp;
    return tmp;
}

bool Sdl2::isClosing()
{
    return true;
}

void Sdl2::startTextInput()
{

}

std::string Sdl2::getTextInput()
{
    std::string tmp;
    return tmp;
}

void Sdl2::endTextInput()
{
    ;
}

void Sdl2::clearScreen(IDisplayModule::Color color)
{
    (void)color;
}

void Sdl2::renderSprite(IDisplayModule::Sprite sprite)
{
    (void)sprite;
}

void Sdl2::display()
{

}

void Sdl2::update()
{

}

std::unique_ptr<IDisplayModule> gEpitechArcadeGetDisplayModuleHandle()
{
    return std::make_unique<Sdl2>();
}