/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-arcade-alexandre.frantz
** File description:
** Texture
*/

#include "Texture.hpp"

ICore::Texture::Texture(std::unique_ptr<IDisplayModule::RawTexture> rawTexture, const std::string &filename, char character, ICore::Color characterColor, ICore::Color backgroundColor, std::size_t width, std::size_t height)
{
    setFilename(filename);
    setChar(character);
    setCharColor(characterColor);
    setBackColor(backgroundColor);
    setWidth(width);
    setHeight(height);
    _raw = std::move(rawTexture);
}

ICore::Texture::~Texture()
{
}

void ICore::Texture::setFilename(const std::string &filename)
{
    _filename = filename;
}

void ICore::Texture::setChar(char character)
{
    _character = character;
}

void ICore::Texture::setCharColor(ICore::Color characterColor)
{
    _characterColor = characterColor;
}

void ICore::Texture::setBackColor(ICore::Color backgroundColor)
{
    _backgroudColor = backgroundColor;
}

void ICore::Texture::setWidth(std::size_t width)
{
    _width = width;
}

void ICore::Texture::setHeight(std::size_t height)
{
    _height = height;
}

std::string ICore::Texture::getFilename() const
{
    return _filename;
}

char ICore::Texture::getChar() const
{
    return _character;
}

ICore::Color ICore::Texture::getCharColor() const
{
    return _characterColor;
}

ICore::Color ICore::Texture::getBackColor() const
{
    return _backgroudColor;
}

std::size_t ICore::Texture::getWidth() const
{
    return _width;
}

std::size_t ICore::Texture::getHeight() const
{
    return _height;
}

IDisplayModule::RawTexture *ICore::Texture::getRaw() const
{
    return _raw.get();
}
