/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-arcade-alexandre.frantz
** File description:
** DisplayModule
*/

#include "DisplayModule.hpp"

DisplayModule::DisplayModule()
{
}

DisplayModule::~DisplayModule()
{
}

void DisplayModule::setPixelsPerCell(std::uint32_t pixelsPerCell)
{
    ;
}

std::uint32_t DisplayModule::getPixelsPerCell()
{
    std::uint32_t tmp;
    return tmp;
}

std::unique_ptr<IDisplayModule::RawTexture> DisplayModule::loadTexture(const std::string &filename, char character, IDisplayModule::Color characterColor, IDisplayModule::Color backgroundColor, std::size_t width, std::size_t height)
{
    std::unique_ptr<IDisplayModule::RawTexture> tmp;
    return tmp;
}

void DisplayModule::openWindow(IDisplayModule::Vector2u pixelsWantedWindowSize)
{
    ;
}

bool DisplayModule::isButtonPressed(IDisplayModule::Button button)
{
    return true;
}

IDisplayModule::MouseButtonReleaseEvent DisplayModule::getMouseButtonReleaseEvent()
{
    IDisplayModule::MouseButtonReleaseEvent tmp;
    return tmp;
}

bool DisplayModule::isClosing()
{
    return true;
}

void DisplayModule::startTextInput()
{
;
}

std::string DisplayModule::getTextInput()
{
    std::string tmp;
    return tmp;
}

void DisplayModule::endTextInput()
{
    ;
}

void DisplayModule::clearScreen(IDisplayModule::Color color)
{
    ;
}

void DisplayModule::renderSprite(IDisplayModule::Sprite sprite)
{
    ;
}

void DisplayModule::display()
{
    ;
}


void DisplayModule::update()
{
    ;
}