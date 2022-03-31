/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-arcade-alexandre.frantz
** File description:
** Texture
*/

#pragma once

#include "../../arcade-interface-master/ICore.hpp"
#include "../../arcade-interface-master/IDisplayModule.hpp"
#include "Core.hpp"

class ICore::Texture
{
    public:
        Texture();
        ~Texture();
    void setFilename(const std::string filename);
    void setChar(char character);
    void setCharColor(ICore::Color characterColor);
    void setBackColor(ICore::Color backgroundColor);
    void setWidth(std::size_t width);
    void setHeight(std::size_t height);
    std::string getFilename() const;
    char getChar() const;
    ICore::Color getCharColor() const;
    ICore::Color getBackColor() const;
    std::size_t getWidth() const;
    std::size_t getHeight() const;
    //IDisplayModule::RawTexture getRaw() const;

    protected:
        std::string _filename;
        char _character;
        ICore::Color _characterColor;
        ICore::Color _backgroudColor;
        std::size_t _width;
        std::size_t _height;
        //IDisplayModule::
};
