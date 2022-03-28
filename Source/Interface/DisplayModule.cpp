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
    (void)pixelsPerCell;
}

std::uint32_t DisplayModule::getPixelsPerCell()
{
    std::uint32_t tmp;
    return tmp;
}

std::unique_ptr<DisplayModule::RawTexture> DisplayModule::loadTexture(const std::string &filename, char character, DisplayModule::Color characterColor, DisplayModule::Color backgroundColor, std::size_t width, std::size_t height)
{
    std::unique_ptr<DisplayModule::RawTexture> tmp;
    (void)filename;
    (void)character;
    (void)characterColor;
    (void)backgroundColor;
    (void)width;
    (void)height;
    return tmp;
}

void DisplayModule::openWindow(DisplayModule::Vector2u pixelsWantedWindowSize)
{

}

bool DisplayModule::isButtonPressed(DisplayModule::Button button)
{
    (void)button;
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

}

std::string DisplayModule::getTextInput()
{
    std::string tmp;
    return tmp;
}

void DisplayModule::endTextInput()
{

}

void DisplayModule::clearScreen(DisplayModule::Color color)
{
    (void)color;
}

void DisplayModule::renderSprite(DisplayModule::Sprite sprite)
{
    (void)sprite;
}

void DisplayModule::display()
{

}

void DisplayModule::update()
{

}
