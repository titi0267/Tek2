/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-arcade-alexandre.frantz
** File description:
** Ncurses
*/

#include "Ncurses.hpp"

Ncurses::Ncurses()
{
    
}

Ncurses::~Ncurses()
{
}

void Ncurses::setPixelsPerCell(std::uint32_t pixelsPerCell)
{
    _pixelsPerCell = pixelsPerCell;
}

std::uint32_t Ncurses::getPixelsPerCell()
{
    return _pixelsPerCell;
}

std::unique_ptr<IDisplayModule::RawTexture> Ncurses::loadTexture(const std::string &filename, char character, IDisplayModule::Color characterColor, IDisplayModule::Color backgroundColor, std::size_t width, std::size_t height)
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

void Ncurses::openWindow(IDisplayModule::Vector2u pixelsWantedWindowSize)
{
    (void)pixelsWantedWindowSize;
    return;
}

bool Ncurses::isButtonPressed(IDisplayModule::Button button)
{
    (void)button;
    return true;
}

IDisplayModule::MouseButtonReleaseEvent Ncurses::getMouseButtonReleaseEvent()
{
    IDisplayModule::MouseButtonReleaseEvent tmp;
    return tmp;
}

bool Ncurses::isClosing()
{
    return true;
}

void Ncurses::startTextInput()
{

}

std::string Ncurses::getTextInput()
{
    std::string tmp;
    return tmp;
}

void Ncurses::endTextInput()
{
    ;
}

void Ncurses::clearScreen(IDisplayModule::Color color)
{
    (void)color;
}

void Ncurses::renderSprite(IDisplayModule::Sprite sprite)
{
    (void)sprite;
}

void Ncurses::display()
{

}

void Ncurses::update()
{

}

std::unique_ptr<IDisplayModule> gEpitechArcadeGetDisplayModuleHandle()
{
    return std::make_unique<Ncurses>();
}
