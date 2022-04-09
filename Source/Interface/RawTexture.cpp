/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-arcade-alexandre.frantz
** File description:
** RawTexture
*/

#include "RawTexture.hpp"

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

const std::string RawTextureNCurses::getFilename() const
{
    return "";
}

RawTextureSfml::RawTextureSfml(const std::string &filename, std::size_t width, std::size_t height)
{
    _filename = filename;
    _width = width;
    _height = height;
}

RawTextureSfml::~RawTextureSfml()
{
}

char RawTextureSfml::getChar() const
{
    return 'a';
}

IDisplayModule::Color RawTextureSfml::getCharColor() const
{
    return IDisplayModule::Color::black;
}

IDisplayModule::Color RawTextureSfml::getBackColor() const
{
    return IDisplayModule::Color::black;
}

const std::string RawTextureSfml::getFilename() const
{
    return _filename;
}

std::size_t RawTextureSfml::getWidth() const
{
    return _width;
}

std::size_t RawTextureSfml::getHeight() const
{
    return _height;
}

RawTextureSdl2::RawTextureSdl2(const std::string &filename, std::size_t width, std::size_t height)
{
    _filename = filename;
    _width = width;
    _height = height;
}

RawTextureSdl2::~RawTextureSdl2()
{
}

char RawTextureSdl2::getChar() const
{
    return 'a';
}

IDisplayModule::Color RawTextureSdl2::getCharColor() const
{
    return IDisplayModule::Color::black;
}

IDisplayModule::Color RawTextureSdl2::getBackColor() const
{
    return IDisplayModule::Color::black;
}

const std::string RawTextureSdl2::getFilename() const
{
    return _filename;
}

std::size_t RawTextureSdl2::getWidth() const
{
    return _width;
}

std::size_t RawTextureSdl2::getHeight() const
{
    return _height;
}