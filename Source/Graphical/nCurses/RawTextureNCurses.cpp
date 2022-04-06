/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-arcade-alexandre.frantz
** File description:
** RawTexture
*/

#include "RawTextureNCurses.hpp"

RawTextureNCurses::RawTextureNCurses(char character, ICore::Color characterColor, ICore::Color backgroundColor, std::size_t width, std::size_t height)
{
    _character = character;
    _characterColor = characterColor;
    _backgroudColor = backgroundColor;
    _width = width;
    _height = height;
}

RawTextureNCurses::~RawTextureNCurses()
{
}

char RawTextureNCurses::getChar() const
{
    return _character;
}

IDisplayModule::Color RawTextureNCurses::getCharColor() const
{
    return _characterColor;
}

IDisplayModule::Color RawTextureNCurses::getBackColor() const
{
    return _backgroudColor;
}

std::size_t RawTextureNCurses::getWidth() const
{
    return _width;
}

std::size_t RawTextureNCurses::getHeight() const
{
    return _height;
}