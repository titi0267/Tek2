/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-arcade-alexandre.frantz
** File description:
** RawTexture
*/

#pragma once

#include "../../../arcade-interface-master/IDisplayModule.hpp"
#include "../../Interface/Texture.hpp"
#include <iostream>
#include <memory>

class IRawTexture : public IDisplayModule::RawTexture
{
    public:
        virtual ~IRawTexture() = default;

    virtual char getChar() const = 0;
    virtual ICore::Color getCharColor() const = 0;
    virtual ICore::Color getBackColor() const = 0;
    virtual std::size_t getWidth() const = 0;
    virtual std::size_t getHeight() const = 0;
};

class RawTextureNCurses : public IRawTexture
{
    public:
        RawTextureNCurses(char character, ICore::Color characterColor, ICore::Color backgroundColor, std::size_t width, std::size_t height);
        ~RawTextureNCurses();

    char getChar() const;
    ICore::Color getCharColor() const;
    ICore::Color getBackColor() const;
    std::size_t getWidth() const;
    std::size_t getHeight() const;

    protected:
        char _character;
        IDisplayModule::Color _characterColor;
        IDisplayModule::Color _backgroudColor;
        std::size_t _width;
        std::size_t _height;
};
